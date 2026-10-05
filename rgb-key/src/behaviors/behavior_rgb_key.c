/*
 * Copyright (c) 2026
 *
 * SPDX-License-Identifier: MIT
 */

#define DT_DRV_COMPAT zmk_behavior_rgb_key

#include <zephyr/device.h>
#include <zephyr/drivers/led_strip.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/util.h>

#include <drivers/behavior.h>
#include <zmk/behavior.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

/*
 * Each half of the Corne has its own local led_strip device.
 *
 * The behavior uses BEHAVIOR_LOCALITY_EVENT_SOURCE, so when a key
 * on the left half invokes the behavior, the left half executes it;
 * when a key on the right invokes it, the right half executes it.
 */
static struct led_rgb rgb_pixels[27];

static int rgb_key_set_pixel(uint32_t index, uint32_t packed_rgb) {
    const struct device *led_strip = DEVICE_DT_GET(DT_NODELABEL(led_strip));

    if (!device_is_ready(led_strip)) {
        LOG_ERR("RGB LED strip is not ready");
        return -ENODEV;
    }

    if (index >= ARRAY_SIZE(rgb_pixels)) {
        LOG_ERR("Invalid RGB LED index: %u", index);
        return -EINVAL;
    }

    /*
     * param2 format:
     *
     * 0xRRGGBB
     */
    rgb_pixels[index].r = (packed_rgb >> 16) & 0xFF;
    rgb_pixels[index].g = (packed_rgb >> 8) & 0xFF;
    rgb_pixels[index].b = packed_rgb & 0xFF;

    return led_strip_update_rgb(
        led_strip,
        rgb_pixels,
        ARRAY_SIZE(rgb_pixels)
    );
}

static int on_rgb_key_binding_pressed(
    struct zmk_behavior_binding *binding,
    struct zmk_behavior_binding_event event
) {
    ARG_UNUSED(event);

    return rgb_key_set_pixel(
        binding->param1,
        binding->param2
    );
}

static int on_rgb_key_binding_released(
    struct zmk_behavior_binding *binding,
    struct zmk_behavior_binding_event event
) {
    ARG_UNUSED(binding);
    ARG_UNUSED(event);

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