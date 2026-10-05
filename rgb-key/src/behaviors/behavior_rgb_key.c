#define DT_DRV_COMPAT zmk_behavior_rgb_key

#include <zephyr/device.h>
#include <zephyr/drivers/led_strip.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/util.h>
#include <errno.h>
#include <string.h>

#include <drivers/behavior.h>
#include <zmk/behavior.h>

#define RGB_KEY_LED_COUNT 27

static struct led_rgb pixels[RGB_KEY_LED_COUNT];

/*
 * ============================================================
 * CORES
 * ============================================================
 */

#define UG_R 51
#define UG_G 51
#define UG_B 51

#if IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)

static const struct led_rgb left_pixels[RGB_KEY_LED_COUNT] = {

    /* 0-5: underglow */
    { UG_R, UG_G, UG_B },
    { UG_R, UG_G, UG_B },
    { UG_R, UG_G, UG_B },
    { UG_R, UG_G, UG_B },
    { UG_R, UG_G, UG_B },
    { UG_R, UG_G, UG_B },

    /* 6: SPACE */
    { 255, 0, 255 },

    /* 7-12: B G T R F V */
    { 0, 128, 255 },
    { 0, 128, 255 },
    { 0, 128, 255 },
    { 0, 128, 255 },
    { 0, 128, 255 },
    { 0, 128, 255 },

    /* 13: LOWER */
    { 0, 255, 0 },

    /* 14: LGUI */
    { 255, 255, 0 },

    /* 15-23: C D E W S X Z A Q */
    { 0, 128, 255 },
    { 0, 128, 255 },
    { 0, 128, 255 },
    { 0, 128, 255 },
    { 0, 128, 255 },
    { 0, 128, 255 },
    { 0, 128, 255 },
    { 0, 128, 255 },
    { 0, 128, 255 },

    /* 24: TAB */
    { 255, 0, 0 },

    /* 25: LCTRL */
    { 255, 255, 0 },

    /* 26: LSHIFT */
    { 255, 255, 0 },
};

#else

static const struct led_rgb right_pixels[RGB_KEY_LED_COUNT] = {

    /* 0-5: underglow */
    { UG_R, UG_G, UG_B },
    { UG_R, UG_G, UG_B },
    { UG_R, UG_G, UG_B },
    { UG_R, UG_G, UG_B },
    { UG_R, UG_G, UG_B },
    { UG_R, UG_G, UG_B },

    /* 6: ENTER */
    { 255, 0, 255 },

    /* 7-12: N H Y U J M */
    { 0, 128, 255 },
    { 0, 128, 255 },
    { 0, 128, 255 },
    { 0, 128, 255 },
    { 0, 128, 255 },
    { 0, 128, 255 },

    /* 13: RAISE */
    { 0, 255, 0 },

    /* 14: RALT */
    { 255, 255, 0 },

    /* 15-23: COMMA DOT I O K FSLH SEMI L P */
    { 0, 128, 255 },
    { 0, 128, 255 },
    { 0, 128, 255 },
    { 0, 128, 255 },
    { 0, 128, 255 },
    { 0, 128, 255 },
    { 0, 128, 255 },
    { 0, 128, 255 },
    { 0, 128, 255 },

    /* 24: BSPC */
    { 255, 0, 0 },

    /* 25: SQT */
    { 255, 0, 0 },

    /* 26: ESC */
    { 255, 0, 0 },
};

#endif


/*
 * ============================================================
 * LED STRIP
 * ============================================================
 */

static const struct device *get_led_strip(void)
{
    const struct device *strip =
        DEVICE_DT_GET(DT_NODELABEL(led_strip));

    if (!device_is_ready(strip)) {
        return NULL;
    }

    return strip;
}


/*
 * ============================================================
 * APLICA CORES
 * ============================================================
 */

static int rgb_key_init(void)
{
    const struct device *strip = get_led_strip();

    if (strip == NULL) {
        return -ENODEV;
    }

#if IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
    memcpy(pixels, left_pixels, sizeof(pixels));
#else
    memcpy(pixels, right_pixels, sizeof(pixels));
#endif

    return led_strip_update_rgb(
        strip,
        pixels,
        RGB_KEY_LED_COUNT
    );
}


/*
 * ============================================================
 * DELAYED BOOT INITIALIZATION
 * ============================================================
 *
 * Esperamos o ZMK/RGB terminar completamente o boot.
 */

static struct k_work_delayable rgb_boot_work;

static void rgb_boot_work_handler(struct k_work *work)
{
    ARG_UNUSED(work);

    rgb_key_init();
}

static int rgb_key_behavior_init(const struct device *dev)
{
    ARG_UNUSED(dev);

    k_work_init_delayable(&rgb_boot_work, rgb_boot_work_handler);

    /*
     * 2 segundos depois da inicialização do comportamento.
     */
    k_work_schedule(
        &rgb_boot_work,
        K_SECONDS(2)
    );

    return 0;
}


/*
 * ============================================================
 * RGB KEY BEHAVIOR
 * ============================================================
 */

static int on_rgb_key_binding_pressed(
    struct zmk_behavior_binding *binding,
    struct zmk_behavior_binding_event event
)
{
    return rgb_key_set(
        binding->param1,
        binding->param2
    );
}

static int on_rgb_key_binding_released(
    struct zmk_behavior_binding *binding,
    struct zmk_behavior_binding_event event
)
{
    return ZMK_BEHAVIOR_OPAQUE;
}

static int rgb_key_set(uint32_t index, uint32_t color)
{
    const struct device *strip = get_led_strip();

    if (strip == NULL) {
        return -ENODEV;
    }

    if (index >= RGB_KEY_LED_COUNT) {
        return -EINVAL;
    }

    pixels[index].r = (color >> 16) & 0xFF;
    pixels[index].g = (color >> 8) & 0xFF;
    pixels[index].b = color & 0xFF;

    return led_strip_update_rgb(
        strip,
        pixels,
        RGB_KEY_LED_COUNT
    );
}


static const struct behavior_driver_api rgb_key_driver_api = {
    .locality = BEHAVIOR_LOCALITY_EVENT_SOURCE,
    .binding_pressed = on_rgb_key_binding_pressed,
    .binding_released = on_rgb_key_binding_released,
};


BEHAVIOR_DT_INST_DEFINE(
    0,
    rgb_key_behavior_init,
    NULL,
    NULL,
    NULL,
    APPLICATION,
    CONFIG_APPLICATION_INIT_PRIORITY,
    &rgb_key_driver_api
);