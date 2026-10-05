#define DT_DRV_COMPAT zmk_behavior_rgb_key

#include <zephyr/device.h>
#include <zephyr/drivers/led_strip.h>
#include <zephyr/sys/util.h>
#include <errno.h>

#include <drivers/behavior.h>
#include <zmk/behavior.h>

#define RGB_KEY_LED_COUNT 27

static struct led_rgb pixels[RGB_KEY_LED_COUNT];

static uint8_t test_index = 0;

static const struct device *get_led_strip(void)
{
    const struct device *strip =
        DEVICE_DT_GET(DT_NODELABEL(led_strip));

    if (!device_is_ready(strip)) {
        return NULL;
    }

    return strip;
}

static int show_test_led(uint8_t index)
{
    const struct device *strip = get_led_strip();

    if (strip == NULL) {
        return -ENODEV;
    }

    /* Apaga todos */
    for (int i = 0; i < RGB_KEY_LED_COUNT; i++) {
        pixels[i].r = 0;
        pixels[i].g = 0;
        pixels[i].b = 0;
    }

    /* LED atual = vermelho */
    pixels[index].r = 255;

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
    int ret = show_test_led(test_index);

    if (ret != 0) {
        return ret;
    }

    test_index++;

    if (test_index >= RGB_KEY_LED_COUNT) {
        test_index = 0;
    }

    return ZMK_BEHAVIOR_OPAQUE;
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