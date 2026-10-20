/*
 * GeminiPR steno keys, for the &stn behavior.
 *
 * SPDX-License-Identifier: MIT
 *
 * The number of each key is its place in the GeminiPR packet: 6 bytes of 7
 * keys each, in the order below (byte = number / 7, bit = 6 - number % 7).
 * The packet is
 *
 *   byte 0: Fn  #1  #2  #3  #4  #5  #6
 *   byte 1: S1- S2- T-  K-  P-  W-  H-
 *   byte 2: R-  A-  O-  *1  *2  res res
 *   byte 3: pwr *3  *4  -E  -U  -F  -R
 *   byte 4: -P  -B  -L  -G  -T  -S  -D
 *   byte 5: #7  #8  #9  #A  #B  #C  -Z
 *
 * and the most significant bit of byte 0 is set to mark the start of a packet.
 * The default Gemini PR key map of Plover turns S1 and S2 into S-, every
 * number key into the number bar and every star key into the star.
 *
 * The names are the ones QMK uses (STN_TL is T- and STN_TR is -T, and so on),
 * so a steno layout written for QMK reads the same here.
 *
 * Plain #define lines only: this file is read by the devicetree preprocessor
 * and by C.
 */

#ifndef DT_BINDINGS_STENO_GEMINI_H
#define DT_BINDINGS_STENO_GEMINI_H

#define STN_FN 0
#define STN_N1 1
#define STN_N2 2
#define STN_N3 3
#define STN_N4 4
#define STN_N5 5
#define STN_N6 6

#define STN_S1 7
#define STN_S2 8
#define STN_TL 9
#define STN_KL 10
#define STN_PL 11
#define STN_WL 12
#define STN_HL 13

#define STN_RL 14
#define STN_A 15
#define STN_O 16
#define STN_ST1 17
#define STN_ST2 18
#define STN_RES1 19
#define STN_RES2 20

#define STN_PWR 21
#define STN_ST3 22
#define STN_ST4 23
#define STN_E 24
#define STN_U 25
#define STN_FR 26
#define STN_RR 27

#define STN_PR 28
#define STN_BR 29
#define STN_LR 30
#define STN_GR 31
#define STN_TR 32
#define STN_SR 33
#define STN_DR 34

#define STN_N7 35
#define STN_N8 36
#define STN_N9 37
#define STN_NA 38
#define STN_NB 39
#define STN_NC 40
#define STN_ZR 41

#define STN_KEY_COUNT 42

#endif /* DT_BINDINGS_STENO_GEMINI_H */
