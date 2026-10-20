/*
 * &stn: GeminiPR steno keys.
 *
 * Every steno key is a key of the keymap bound to &stn <STN_*> (see
 * include/dt-bindings/steno/gemini.h). Pressing one adds its bit to the chord
 * being typed; when the last key of the chord is released, the chord leaves as
 * one 6 byte GeminiPR packet on the CDC ACM serial port labelled gemini_uart,
 * which Plover reads with its "Gemini PR" machine. Nothing is typed on the
 * computer, so no letters leak while Plover is closed.
 *
 * The behavior has central locality: the keymap runs on the half that talks to
 * the computer, which is also the half with the serial port. The other half
 * builds the same code without the port, and never runs it.
 *
 * SPDX-License-Identifier: MIT
 */

#define DT_DRV_COMPAT zmk_behavior_steno_gemini

#include <string.h>

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/util.h>

#include <drivers/behavior.h>
#include <zmk/behavior.h>

#include <dt-bindings/steno/gemini.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#if DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT)

#define STN_PACKET_LEN 6
#define STN_KEYS_PER_BYTE 7
#define STN_PACKET_START 0x80

BUILD_ASSERT(STN_KEY_COUNT == STN_PACKET_LEN * STN_KEYS_PER_BYTE,
             "GeminiPR packets carry 6 bytes of 7 keys");

#if DT_NODE_HAS_STATUS(DT_NODELABEL(gemini_uart), okay)
#define STN_HAS_UART 1
static const struct device *const stn_uart = DEVICE_DT_GET(DT_NODELABEL(gemini_uart));
#endif

static K_MUTEX_DEFINE(stn_lock);

/* How many physical keys hold each steno key down right now */
static uint8_t stn_held[STN_KEY_COUNT];
/* How many steno keys are down in total */
static uint16_t stn_held_total;
/* Every key that went down since the chord started, in the layout of the packet */
static uint8_t stn_chord[STN_PACKET_LEN];

static void stn_send(const uint8_t chord[STN_PACKET_LEN]) {
#ifdef STN_HAS_UART
    uint8_t packet[STN_PACKET_LEN];

    if (!device_is_ready(stn_uart)) {
        LOG_WRN("steno: the GeminiPR serial port is not ready");
        return;
    }

#if IS_ENABLED(CONFIG_UART_LINE_CTRL)
    /*
     * DTR is high only while the host has the port open. Without this check the
     * packets would pile up in the USB buffer while nobody listens and reach
     * Plover later, as chords nobody typed.
     */
    uint32_t dtr = 0;

    if (uart_line_ctrl_get(stn_uart, UART_LINE_CTRL_DTR, &dtr) != 0 || dtr == 0) {
        LOG_DBG("steno: the host has not opened the GeminiPR port, chord dropped");
        return;
    }
#endif

    memcpy(packet, chord, sizeof(packet));
    packet[0] |= STN_PACKET_START;

    /* Fills the TX ring buffer of the CDC ACM driver and returns: it never blocks */
    int sent = uart_fifo_fill(stn_uart, packet, sizeof(packet));

    if (sent != (int)sizeof(packet)) {
        LOG_WRN("steno: only %d of %d bytes of the chord were queued", sent,
                (int)sizeof(packet));
    }
#else
    ARG_UNUSED(chord);
#endif
}

static int stn_binding_pressed(struct zmk_behavior_binding *binding,
                               struct zmk_behavior_binding_event event) {
    const uint32_t key = binding->param1;

    if (key >= STN_KEY_COUNT) {
        LOG_ERR("steno: key %u is not a GeminiPR key", (unsigned int)key);
        return -EINVAL;
    }

    k_mutex_lock(&stn_lock, K_FOREVER);
    if (stn_held[key] < UINT8_MAX) {
        stn_held[key]++;
        stn_held_total++;
    }
    stn_chord[key / STN_KEYS_PER_BYTE] |= BIT(STN_KEYS_PER_BYTE - 1 - (key % STN_KEYS_PER_BYTE));
    k_mutex_unlock(&stn_lock);

    LOG_DBG("steno: key %u down at position %d", (unsigned int)key, (int)event.position);
    return ZMK_BEHAVIOR_OPAQUE;
}

static int stn_binding_released(struct zmk_behavior_binding *binding,
                                struct zmk_behavior_binding_event event) {
    const uint32_t key = binding->param1;
    uint8_t chord[STN_PACKET_LEN];
    bool done = false;

    if (key >= STN_KEY_COUNT) {
        return -EINVAL;
    }

    k_mutex_lock(&stn_lock, K_FOREVER);
    if (stn_held[key] == 0) {
        /*
         * A release with no press behind it. ZMK sends the release to the binding that took the
         * press, so this should not happen; ignoring it keeps a stray release from sending an
         * empty chord to Plover.
         */
        k_mutex_unlock(&stn_lock);
        LOG_WRN("steno: key %u released without being pressed", (unsigned int)key);
        return ZMK_BEHAVIOR_OPAQUE;
    }

    stn_held[key]--;
    stn_held_total--;
    if (stn_held_total == 0) {
        /* Last key up: the chord is complete */
        memcpy(chord, stn_chord, sizeof(chord));
        memset(stn_chord, 0, sizeof(stn_chord));
        for (size_t i = 0; i < sizeof(chord); i++) {
            if (chord[i] != 0) {
                done = true;
            }
        }
    }
    k_mutex_unlock(&stn_lock);

    LOG_DBG("steno: key %u up at position %d", (unsigned int)key, (int)event.position);

    if (done) {
        stn_send(chord);
    }
    return ZMK_BEHAVIOR_OPAQUE;
}

#if IS_ENABLED(CONFIG_ZMK_BEHAVIOR_METADATA)

#define STN_VALUE(name, key)                                                                       \
    {                                                                                              \
        .display_name = name,                                                                      \
        .type = BEHAVIOR_PARAMETER_VALUE_TYPE_VALUE,                                               \
        .value = key,                                                                              \
    }

/* What ZMK Studio offers for the parameter. All number keys are the same key to Plover. */
static const struct behavior_parameter_value_metadata stn_param_values[] = {
    STN_VALUE("S1-", STN_S1),   STN_VALUE("S2-", STN_S2),  STN_VALUE("T-", STN_TL),
    STN_VALUE("K-", STN_KL),    STN_VALUE("P-", STN_PL),   STN_VALUE("W-", STN_WL),
    STN_VALUE("H-", STN_HL),    STN_VALUE("R-", STN_RL),   STN_VALUE("A-", STN_A),
    STN_VALUE("O-", STN_O),     STN_VALUE("*1", STN_ST1),  STN_VALUE("*2", STN_ST2),
    STN_VALUE("*3", STN_ST3),   STN_VALUE("*4", STN_ST4),  STN_VALUE("-E", STN_E),
    STN_VALUE("-U", STN_U),     STN_VALUE("-F", STN_FR),   STN_VALUE("-R", STN_RR),
    STN_VALUE("-P", STN_PR),    STN_VALUE("-B", STN_BR),   STN_VALUE("-L", STN_LR),
    STN_VALUE("-G", STN_GR),    STN_VALUE("-T", STN_TR),   STN_VALUE("-S", STN_SR),
    STN_VALUE("-D", STN_DR),    STN_VALUE("-Z", STN_ZR),   STN_VALUE("#", STN_N1),
};

static const struct behavior_parameter_metadata_set stn_param_metadata_set[] = {{
    .param1_values = stn_param_values,
    .param1_values_len = ARRAY_SIZE(stn_param_values),
}};

static const struct behavior_parameter_metadata stn_metadata = {
    .sets_len = ARRAY_SIZE(stn_param_metadata_set),
    .sets = stn_param_metadata_set,
};

#endif // IS_ENABLED(CONFIG_ZMK_BEHAVIOR_METADATA)

static const struct behavior_driver_api stn_driver_api = {
    .locality = BEHAVIOR_LOCALITY_CENTRAL,
    .binding_pressed = stn_binding_pressed,
    .binding_released = stn_binding_released,
#if IS_ENABLED(CONFIG_ZMK_BEHAVIOR_METADATA)
    .parameter_metadata = &stn_metadata,
#endif // IS_ENABLED(CONFIG_ZMK_BEHAVIOR_METADATA)
};

#define STN_INST(n)                                                                                \
    BEHAVIOR_DT_INST_DEFINE(n, NULL, NULL, NULL, NULL, POST_KERNEL,                                \
                            CONFIG_KERNEL_INIT_PRIORITY_DEFAULT, &stn_driver_api);

DT_INST_FOREACH_STATUS_OKAY(STN_INST)

#endif /* DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT) */
