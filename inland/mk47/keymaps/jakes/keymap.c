/* Copyright (C) 2023 jonylee@hfd
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

// RGB
#define DEFAULT_H 116
#define DEFAULT_S 255
#define DEFAULT_V 255

#define ROW_COUNT 12

// 

enum layers {
    BASE=0, // Alpha layer
    NUM,    //
    NAV,    //
    FN,     // 
    KEB,    //
    SEC,    //
    BABY    //
};

enum custom_keycodes {
    RM_RES = SAFE_RANGE, // Reset RGB to default
    WN_LEFT,             // Combos to navigate between virtual desktops 
    WN_RGHT,
    WN_UP,
    WN_DOWN
};

static hsv_t BASE_COL = {
    .h = 116,
    .s = 255,
    .v = 255
};

// HELPER DECLARATIONS
inline void set_layer_rgb(uint32_t layer);
inline void update_base_colo(int i);

// QMK OVERRIDES
// Startup function
void keyboard_post_init_user(void) {
    rgb_matrix_enable();
    rgb_matrix_mode(RGB_MATRIX_RIVERFLOW);
    rgb_matrix_sethsv(BASE_COL.h,BASE_COL.s,BASE_COL.v);
}

// Used for setting custom code for different keypresses
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case RM_HUEU: {
                rgb_matrix_increase_hue();
                update_base_colo(0);
                return false;
            }
            case RM_HUED: {
                rgb_matrix_decrease_hue();
                update_base_colo(0);
                return false;
            }
            case RM_SATU: {
                rgb_matrix_increase_sat();
                update_base_colo(1);
                return false;
            }
            case RM_SATD: {
                rgb_matrix_decrease_sat();
                update_base_colo(1);
                return false;
            }
            case RM_VALU: {
                rgb_matrix_increase_val();
                update_base_colo(2);
                return false;
            }
            case RM_VALD: {
                rgb_matrix_decrease_val();
                update_base_colo(2);
                return false;
            }
            case RM_RES: {
                BASE_COL.h = DEFAULT_H;
                BASE_COL.s = DEFAULT_S;
                BASE_COL.v = DEFAULT_V;
                rgb_matrix_sethsv(BASE_COL.h,BASE_COL.s,BASE_COL.v);
                rgb_matrix_mode(RGB_MATRIX_RIVERFLOW);
                
                return false;
            }
            case WN_LEFT: {
                tap_code16(C(G(KC_LEFT)));
                return false;
            }
            case WN_RGHT: {
                tap_code16(C(G(KC_RGHT)));
                return false;
            }
            case WN_UP: {
                tap_code16(C(G(KC_UP)));
                return false;
            }
            case WN_DOWN: {
                tap_code16(C(G(KC_DOWN)));
                return false;
            }
        }
    }
    return true;  // let QMK handle other keys
}

// Hook to change RGB per-key AFTER the current animation frame has been rendered
bool rgb_matrix_indicators_user(void) {
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(ROW_COUNT+0,255,0,0);
    }
    return true;
}

// Allows combinations of function modifiers 
layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, NUM, FN, SEC);
    set_layer_rgb(get_highest_layer(state));
    return state;
}


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // [_TEMPLATE] = LAYOUT_planck_mit(
    //     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    //     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    //     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    //     _______, _______, _______, _______, _______,     _______,      _______, _______, _______, _______, _______
    // ),
    //
    // [XTEMPLATE] = LAYOUT_planck_mit(
    //     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    // ),

    [BASE] = LAYOUT_planck_mit(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_QUOT,
        MO(NAV), KC_LGUI, KC_LALT, KC_LCTL, MO(NUM),      KC_SPC,      MO(FN),  MO(KEB), XXXXXXX, KC_DEL,  KC_RCTL
    ),

    [NUM] = LAYOUT_planck_mit(
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, XXXXXXX, 
        XXXXXXX, _______, _______, _______, MO(NUM),     _______,      MO(FN),  XXXXXXX, XXXXXXX, XXXXXXX, _______
    ),

    [NAV] = LAYOUT_planck_mit(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, WN_LEFT, WN_DOWN, WN_UP,   WN_RGHT, XXXXXXX, _______,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGDN, KC_PGUP, XXXXXXX, XXXXXXX, XXXXXXX,
        MO(NAV), _______, _______, _______, XXXXXXX,     _______,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______
    ),

    [FN] = LAYOUT_planck_mit(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11, KC_F12,
        KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, _______, _______, _______, MO(NUM),     _______,      MO(FN),  XXXXXXX, XXXXXXX, XXXXXXX, _______
    ),

    [KEB] = LAYOUT_planck_mit(
        RM_RES,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG,
        RM_NEXT, RM_HUEU, RM_SATU, RM_VALU, RM_SPDU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        RM_PREV, RM_HUED, RM_SATD, RM_VALD, RM_SPDD, XXXXXXX, XXXXXXX, KC_VOLD, KC_VOLU, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [SEC] = LAYOUT_planck_mit(
        QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TO(BABY),
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [BABY] = LAYOUT_planck_mit(
        TO(BASE),XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    )
};

// HELPER FUNCTION DEFINITIONS

void set_layer_rgb(uint32_t layer) {
    uint8_t diff = 0;
    rgb_matrix_mode(RGB_MATRIX_RIVERFLOW);
    switch (layer) {
        case BASE: {
            diff = 0;
            break;
        }
        case NUM: {
            diff = -31;
            break;
        }
        case NAV: {
            diff = 54;
            break;
        }
        case FN: {
            diff = 75;
            break;
        }
        case KEB: {
            diff = 107;
            break;
        }
        case SEC: {
            rgb_matrix_mode(RGB_MATRIX_MULTISPLASH);
            break;
        }
        case BABY: {
            rgb_matrix_mode(RGB_MATRIX_MULTISPLASH);
            break;
        }
        default: { // should be unreachable
            break;
        }
    }
    rgb_matrix_sethsv(BASE_COL.h+diff,BASE_COL.s,BASE_COL.v);
}

void update_base_colo(int i) {
    hsv_t curr = rgb_matrix_get_hsv();
    switch(i) {
        case 0: {
            BASE_COL.h = curr.h;
            break;
        }
        case 1: {
            BASE_COL.s = curr.s;
            break;
        }
        case 2: {
            BASE_COL.v = curr.v;
            break;
        }
        case 3: {
            BASE_COL = rgb_matrix_get_hsv();
            break;
        }
        default: {
            break;
        }
    }
}
// clang-format on

