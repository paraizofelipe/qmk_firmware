#include QMK_KEYBOARD_H
#include "cyberpunk_logo.h"
#include "timer.h"
#include "rgblight.h"

#define ANIMATION_FRAME_DURATION 100
#define ANIMATION_PAUSE_DURATION 10000

#define SEQUENCE_LENGTH 10

enum sofle_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _QWERTY,
    _COLEMAK,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
    KC_QWERTY = QK_USER,
    KC_COLEMAK,
    KC_PRVWD,
    KC_NXTWD,
    KC_LSTRT,
    KC_LEND
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0,
        KC_MINS, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O,
        KC_P, KC_BSPC, KC_GRV, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K,
        KC_L, KC_SCLN, KC_QUOT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_MUTE,
        KC_NO, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_LGUI, KC_LALT,
        KC_LCTL, TL_LOWR, KC_SPC, KC_ENT, TL_UPPR, KC_EQL, KC_LBRC, KC_RBRC),
    [_COLEMAK] =
        LAYOUT(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9,
               KC_0, KC_MINS, KC_TAB, KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L,
               KC_U, KC_Y, KC_SCLN, KC_BSPC, KC_GRV, KC_A, KC_R, KC_S, KC_T,
               KC_D, KC_H, KC_N, KC_E, KC_I, KC_O, KC_QUOT, KC_LSFT, KC_Z, KC_X,
               KC_C, KC_V, KC_B, KC_MUTE, KC_NO, KC_K, KC_M, KC_COMM, KC_DOT,
               KC_SLSH, KC_RSFT, KC_LGUI, KC_LALT, KC_LCTL, TL_LOWR, KC_SPC,
               KC_ENT, TL_UPPR, KC_RCTL, KC_RALT, KC_RGUI),
    [_RAISE] = LAYOUT(
        KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9,
        KC_F10, KC_F11, KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8,
        KC_9, KC_0, KC_F12, KC_TRNS, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,
        KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE, KC_TRNS, KC_EQL,
        KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, KC_TRNS, KC_TRNS, KC_LBRC, KC_RBRC,
        KC_SCLN, KC_COLN, KC_BSLS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
    [_LOWER] =
        LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_INS,
               KC_PSCR, KC_APP, KC_NO, KC_NO, KC_PGUP, KC_PPLS, KC_PGDN,
               LCTL(KC_RGHT), LCTL(KC_BSPC), KC_DEL, KC_TRNS, KC_LALT, KC_LCTL,
               KC_LSFT, KC_NO, KC_CAPS, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO,
               KC_BSPC, KC_TRNS, LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V),
               KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_PEQL, KC_NO, KC_END, KC_NO,
               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)};

static uint8_t current_color_index = 0;
static uint8_t brightness = 255;

#define COLOR_PALETTE_SIZE (sizeof(color_palette) / sizeof(color_palette[0]))

const uint8_t PROGMEM color_palette[][3] = {
    {HSV_RED},
    {HSV_ORANGE},
    {HSV_YELLOW},
    {HSV_GREEN},
    {HSV_CYAN},
    {HSV_BLUE},
    {HSV_PURPLE},
    {HSV_WHITE}
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        case KC_COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;
        case KC_PRVWD:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_LEFT);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                }
            }
            break;
        case KC_NXTWD:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_RIGHT);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                }
            }
            break;
        case KC_LSTRT:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    // CMD-arrow on Mac, but we have CTL and GUI swapped
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                } else {
                    register_code(KC_HOME);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_code(KC_HOME);
                }
            }
            break;
        case KC_LEND:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    // CMD-arrow on Mac, but we have CTL and GUI swapped
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                } else {
                    register_code(KC_END);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_code(KC_END);
                }
            }
            break;
        case KC_RSFT:
            if (record->event.pressed) {
                current_color_index = (current_color_index + 1) % COLOR_PALETTE_SIZE;
                rgblight_sethsv_noeeprom(
                    pgm_read_byte(&color_palette[current_color_index][0]),
                    pgm_read_byte(&color_palette[current_color_index][1]),
                    brightness
                );
            }
            return false;
    }
    return true;
}

// #ifdef OLED_ENABLE
// oled_rotation_t oled_init_user(oled_rotation_t rotation) {
//     if (!is_keyboard_master()) {
//         return OLED_ROTATION_270;  // flips the display 180 degrees if
//         offhand
//     }
//     return rotation;
// }
// #endif

void render_layer_state(void) {
    oled_set_cursor(32, 0);
    oled_write_P(PSTR(">>V<<\n\n"), false);

    oled_write_P(PSTR("Layer\n"), false);
    switch (biton32(layer_state)) {
        case 0:
            oled_write_P(PSTR("QWERT\n"), false);
            break;
        case 3:
            oled_write_P(PSTR("LOWER\n"), false);
            break;
        case 2:
            oled_write_P(PSTR("RAISE\n"), false);
            break;
        default:
            oled_write_P(PSTR("NaN "), false);
            break;
    }
}

const uint8_t frame_sequence[SEQUENCE_LENGTH] = {
    0, 1, 2, 3, 2, 1, 0,  // Animação: 0,1,2,3,2,1,0
    0, 1, 0               // Pausas e frame especial: 0 (5s), 5 (5s), 0
};

const uint16_t frame_durations[SEQUENCE_LENGTH] = {100, 100, 100,  100, 100,
                                                   100, 100, 5000, 100, 5000};

uint32_t last_step_timer = 0;
uint8_t current_step = 0;

static void render_cyberpunk_logo(void) {
    if (last_step_timer == 0) {
        last_step_timer = timer_read32();
    }

    if (timer_elapsed32(last_step_timer) > frame_durations[current_step]) {
        current_step++;
        if (current_step >= SEQUENCE_LENGTH) {
            current_step = 0;
        }
        last_step_timer = timer_read32();
    }

    oled_clear();
    oled_write_raw_P(cyberpunk_glitch[frame_sequence[current_step]],
                     sizeof(cyberpunk_glitch[0]));
}

static void render_relic(void) {
    static const char PROGMEM relic[] = {
        0x00, 0x00, 0xf8, 0xfc, 0xfe, 0xfe, 0x1e, 0x9e, 0xde, 0xde, 0xde, 0xde,
        0xde, 0xde, 0xde, 0xde, 0xde, 0xde, 0xde, 0xde, 0xde, 0xde, 0xde, 0xde,
        0x9e, 0x1e, 0xfe, 0xfe, 0xfc, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x3f,
        0x3f, 0x3f, 0x3c, 0x3c, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0xbd, 0xfd,
        0xfd, 0xf9, 0xf1, 0x01, 0x01, 0x83, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff,
        0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xfe, 0xfe, 0xfc, 0x00, 0x00,
        0x00, 0x00, 0xf8, 0xfc, 0xfe, 0xff, 0x8f, 0x07, 0x73, 0xf9, 0xfc, 0xfe,
        0x9f, 0x0f, 0x07, 0x03, 0x01, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
        0x00, 0x00, 0x1f, 0x3f, 0x7f, 0x7f, 0x78, 0x78, 0x78, 0x78, 0x78, 0x79,
        0x7b, 0x7f, 0x7f, 0x7f, 0x7c, 0x38, 0x01, 0x03, 0x0f, 0x1f, 0x3e, 0x7c,
        0x78, 0x78, 0x7f, 0x7f, 0x3f, 0x1f, 0x00, 0x00};

    oled_write_raw_P(relic, sizeof(relic));
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_relic();
        render_layer_state();
    } else {
        render_cyberpunk_logo();
    }
    return false;
}

#ifdef RGBLIGHT_ENABLE
void keyboard_post_init_user(void) {
    rgblight_enable();  // Ativa o RGB Underglow
    rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);  // Define a luz estática
    rgblight_sethsv(0, 255, 255);  // Azul: HUE=170, Saturação=255, Brilho=255}
}
#endif

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 1) {
        if (clockwise) {
            if (brightness < 255) {
                brightness += 16;
            }
        } else {
            if (brightness > 0) {
                brightness -= 16;
            }
        }
        rgblight_sethsv_noeeprom(
            pgm_read_byte(&color_palette[current_color_index][0]),
            pgm_read_byte(&color_palette[current_color_index][1]),
            brightness
        );
        return false;
    } else if (index == 0) {
        if (clockwise) {
            // Add your logic for the right knob rotation if needed
        } else {
            // Add your logic for the right knob rotation if needed
        }
    }
    return true;
}
