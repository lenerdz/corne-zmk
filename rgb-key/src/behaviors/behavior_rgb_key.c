#define DT_DRV_COMPAT zmk_behavior_rgb_key

#include <zephyr/device.h>
#include <zephyr/drivers/led_strip.h>
#include <zephyr/sys/util.h>
#include <errno.h>

#include <drivers/behavior.h>
#include <zmk/behavior.h>

#define RGB_KEY_LED_COUNT 27

/*
 * Cada metade do Corne possui:
 *
 * 0  - 5   = underglow
 * 6  - 26  = LEDs das teclas
 *
 * O firmware de cada metade possui seu próprio array.
 */
static struct led_rgb pixels[RGB_KEY_LED_COUNT] = {
    /* 0-5: underglow */
    { 51, 51, 51 },
    { 51, 51, 51 },
    { 51, 51, 51 },
    { 51, 51, 51 },
    { 51, 51, 51 },
    { 51, 51, 51 },

    /* 6-26: key LEDs */
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 }
};

static const struct device *get_led_strip(void)
{
    const struct device *strip =
        DEVICE_DT_GET(DT_NODELABEL(led_strip));

    if (!device_is_ready(strip)) {
        return NULL;
    }

    return strip;
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

    /*
     * param1 = índice do LED
     * param2 = RGB no formato 0xRRGGBB
     */

    pixels[index].r = (color >> 16) & 0xFF;
    pixels[index].g = (color >> 8) & 0xFF;
    pixels[index].b = color & 0xFF;

    return led_strip_update_rgb(
        strip,
        pixels,
        RGB_KEY_LED_COUNT
    );
}

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

static const struct behavior_driver_api rgb_key_driver_api = {
    .locality = BEHAVIOR_LOCALITY_EVENT_SOURCE,
    .binding_pressed = on_rgb_key_binding_pressed,
    .binding_released = on_rgb_key_binding_released,
};

BEHAVIOR_DT_INST_DEFINE(
    0,
    NULL,
    NULL,
    NULL,
    NULL,
    POST_KERNEL,
    CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,
    &rgb_key_driver_api
);