#define DT_DRV_COMPAT zmk_behavior_rgb_key

#include <zephyr/device.h>
#include <zephyr/drivers/led_strip.h>
#include <zephyr/sys/util.h>
#include <errno.h>
#include <string.h>

#include <drivers/behavior.h>
#include <zmk/behavior.h>

#define RGB_KEY_LED_COUNT 27

/*
 * ============================================================
 * LED BUFFER
 * ============================================================
 *
 * 0-5  = underglow
 * 6-26 = LEDs das teclas
 */
static struct led_rgb pixels[RGB_KEY_LED_COUNT];

/*
 * ============================================================         
 * CORES INICIAIS
 * ============================================================
 *
 * LEFT:
 *
 *  6  SPACE
 *  7  B
 *  8  G
 *  9  T
 * 10  R
 * 11  F
 * 12  V
 * 13  LOWER
 * 14  LGUI
 * 15  C
 * 16  D
 * 17  E
 * 18  W
 * 19  S
 * 20  X
 * 21  Z
 * 22  A
 * 23  Q
 * 24  TAB
 * 25  LCTRL
 * 26  LSHIFT
 *
 * RIGHT:
 *
 *  6  ENTER
 *  7  N
 *  8  H
 *  9  Y
 * 10  U
 * 11  J
 * 12  M
 * 13  RAISE
 * 14  RALT
 * 15  COMMA
 * 16  DOT
 * 17  I
 * 18  O
 * 19  K
 * 20  FSLH
 * 21  SEMI
 * 22  L
 * 23  P
 * 24  BSPC
 * 25  SQT
 * 26  ESC
 */

/*
 * Underglow:
 * branco com aproximadamente 20% de intensidade.
 */
#define UG_R 51
#define UG_G 51
#define UG_B 51

#if IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)

/*
 * ============================================================
 * LEFT HALF
 * ============================================================
 */

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

/*
 * ============================================================
 * RIGHT HALF
 * ============================================================
 */

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
 * RGB KEY BEHAVIOR
 * ============================================================
 *
 * param1 = índice do LED
 * param2 = 0xRRGGBB
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

static int rgb_key_behavior_init(const struct device *dev)
{
    ARG_UNUSED(dev);

    return rgb_key_init();
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