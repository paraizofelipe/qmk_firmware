// Copyright 2024 Santosh Kumar (@santosh)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define TRI_LAYER_LOWER_LAYER 2
#define TRI_LAYER_UPPER_LAYER 3
#define TRI_LAYER_ADJUST_LAYER 4
#define SPLIT_USB_DETECT

#ifdef RGBLIGHT_ENABLE

#undef RGBLIGHT_LED_COUNT
#undef RGBLED_SPLIT
#define RGBLED_SPLIT \
    { 36, 36 }

#define RGBLIGHT_LED_COUNT 72
#undef RGBLIGHT_LIMIT_VAL
#define SPLIT_TRANSPORT_MIRROR
#define RGBLIGHT_LIMIT_VAL 255
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17

#endif
