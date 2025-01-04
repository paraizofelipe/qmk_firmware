// Copyright 2024 Santosh Kumar (@santosh)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define TRI_LAYER_LOWER_LAYER 2
#define TRI_LAYER_UPPER_LAYER 3
#define TRI_LAYER_ADJUST_LAYER 4
#define SPLIT_USB_DETECT

#ifdef RGBLIGHT_ENABLE
#undef RGBLIGHT_LED_COUNT

// #define RGBLIGHT_ANIMATIONS     // Ativa animações RGB opcionalmente
// #define RGBLIGHT_LIMIT_VAL 255  // Define o brilho máximo (255 é o valor
// máximo) #define RGBLIGHT_HUE_STEP 10  // Incremento de tonalidade #define
// RGBLIGHT_SAT_STEP 17  // Incremento de saturação #define RGBLIGHT_VAL_STEP 17
#undef RGBLED_SPLIT
#define RGBLED_SPLIT \
    { 6, 6 }  // haven't figured out how to use this yet

#define RGBLIGHT_LED_COUNT 12
#undef RGBLIGHT_LIMIT_VAL
#define RGBLIGHT_LIMIT_VAL 255
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17
#endif
