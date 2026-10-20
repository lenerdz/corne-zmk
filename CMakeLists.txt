# Local Zephyr module of this config repository (see zephyr/module.yml).
# ZMK's build workflow passes the repository root as ZMK_EXTRA_MODULES when
# zephyr/module.yml exists, so everything here is built with the firmware.
#
# SPDX-License-Identifier: MIT

zephyr_library()

# The &stn behavior (GeminiPR steno over a second USB serial port). Built only
# when the keymap declares a zmk,behavior-steno-gemini node; see Kconfig.
zephyr_library_sources_ifdef(CONFIG_ZMK_STENO_GEMINI src/behavior_steno_gemini.c)

# ZMK app headers (drivers/behavior.h, zmk/behavior.h)
zephyr_library_include_directories(${APPLICATION_SOURCE_DIR}/include)

# dt-bindings/steno/gemini.h is shared by the keymap and the C code
zephyr_include_directories(include)
