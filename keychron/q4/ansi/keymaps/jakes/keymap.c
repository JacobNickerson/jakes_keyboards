/* Copyright 2022 @ Keychron (https://www.keychron.com)
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

// clang-format off

enum layers {
    _WIN,
    _MAC,
    _FN0,
    _FN1,
    _FN2,
    _BABY
};

enum custom_keycodes {
    RM_RES = SAFE_RANGE
};

static hsv_t BASE_COL = {
    .h = 116,
    .s = 255,
    .v = 255
};

// HELPER FUNCTIONS
// Definitions are below the QMK block
inline void set_layer_rgb(uint32_t layer);
inline void update_base_col(int i);

// QMK OVERRIDES

void keyboard_post_init_user(void) {
    rgb_matrix_enable();
    rgb_matrix_mode(RGB_MATRIX_RIVERFLOW);
    rgb_matrix_sethsv(BASE_COL.h,BASE_COL.s,BASE_COL.v);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _FN0, _FN1, _FN2);
    set_layer_rgb(get_highest_layer(state));
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case RM_HUEU: {
                rgb_matrix_increase_hue();    // normal QMK handling
                update_base_col(0);
                return false;  // we handled it, don’t run default processing
            }
            case RM_HUED: {
                rgb_matrix_decrease_hue();
                update_base_col(0);
                return false;
            }
            case RM_SATU: {
                rgb_matrix_increase_sat();    // normal QMK handling
                update_base_col(1);
                return false;  // we handled it, don’t run default processing
            }
            case RM_SATD: {
                rgb_matrix_decrease_sat();
                update_base_col(1);
                return false;
            }
            case RM_VALU: {
                rgb_matrix_increase_val();    // normal QMK handling
                update_base_col(2);
                return false;  // we handled it, don’t run default processing
            }
            case RM_VALD: {
                rgb_matrix_decrease_val();
                update_base_col(2);
                return false;
            }
            case RM_RES: {
                BASE_COL.h = 116;
                BASE_COL.s = 255;
                BASE_COL.v = 255;
                rgb_matrix_sethsv(BASE_COL.h,BASE_COL.s,BASE_COL.v);
                return false;
            }
        }
    }
    return true;  // let QMK handle other keys
}

// KEYMAP

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // [TEMPLATE] = LAYOUT_ansi_61(
    //     _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______,  _______,
    //     _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______,  _______,
    //     _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,            _______,
    //     _______,           _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,            _______,
    //     _______, _______,  _______,                            _______,                            _______,  _______,  _______,  _______),

    [_WIN] = LAYOUT_ansi_61(
        KC_ESC,  KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,
        KC_TAB,  KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,
        KC_LCTL, KC_A,     KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,            KC_ENT,
        KC_LSFT,           KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH,            KC_RSFT,
        MO(_FN0),KC_LGUI,  KC_LALT,                            KC_SPC,                             MO(_FN0), MO(_FN1), KC_RALT,  KC_RCTL),

    [_MAC] = LAYOUT_ansi_61(
        _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______,  _______,
        _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______,  _______,
        _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,            _______,
        _______,           _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,            _______,
        _______, _______,  _______,                            _______,                            _______,  _______,  _______,  _______),

    [_FN0] = LAYOUT_ansi_61(
        KC_GRV,  KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,   KC_DEL,
        KC_CAPS, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  KC_PGDN,  KC_PGUP,  KC_PSCR,
        _______, _______,  _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,  _______,            _______,
        _______,           _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,            _______,
        _______, _______,  _______,                            _______,                            _______,  _______,  _______,  _______),
        // KC_TILD, KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,   _______,
        // RM_TOGG, RM_NEXT,  RM_VALU, RM_HUEU, RM_SATU, RM_SPDU, _______, _______, _______, _______, _______,  _______,  _______,  _______,
        // _______, RM_PREV,  RM_VALD, RM_HUED, RM_SATD, RM_SPDD, _______, _______, _______, _______, _______,  _______,            _______,
        // _______,           _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,            _______,
        // _______, _______,  _______,                            _______,                            _______,  _______,  _______,  _______)

    [_FN1] = LAYOUT_ansi_61(
        _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  KC_VOLD,  KC_VOLU,  RGB_TOG,
        RM_RES,  RM_NEXT,  RM_HUEU, RM_SATU, RM_VALU, RM_SPDU, _______, _______, _______, _______, _______,  _______,  _______,  _______,
        _______, RM_PREV,  RM_HUED, RM_SATD, RM_VALD, RM_SPDD, _______, _______, _______, _______, _______,  _______,            _______,
        _______,           _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,            _______,
        _______, _______,  _______,                            _______,                            _______,  _______,  _______,  _______),
        // KC_GRV,  KC_BRID,  KC_BRIU, KC_NO,   KC_NO,   RM_VALD, RM_VALU, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE,  KC_VOLD,  KC_VOLU,  RM_NEXT,
        // RM_TOGG, RM_NEXT,  RM_VALU, RM_HUEU, RM_SATU, RM_SPDU, _______, _______, _______, _______, KC_INS,   KC_PGUP,  KC_HOME,  _______,
        // _______, RM_PREV,  RM_VALD, RM_HUED, RM_SATD, RM_SPDD, _______, _______, KC_UP,   KC_NO,   KC_PGDN,  KC_END,             _______,
        // _______,           _______, _______, _______, _______, _______, NK_TOGG, KC_LEFT, KC_DOWN, KC_RIGHT, KC_DEL,             _______,
        // _______, _______,  _______,                            _______,                            _______,  _______,  _______,  _______),

    [_FN2] = LAYOUT_ansi_61(
        QK_BOOT, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______,  TO(_BABY),
        _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______,  _______,
        _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,            _______,
        _______,           _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,            _______,
        _______, _______,  _______,                            _______,                            _______,  _______,  _______,  _______),

    [_BABY] = LAYOUT_ansi_61(
        TO(_WIN), XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,            XXXXXXX,
        XXXXXXX,            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,            XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,                            XXXXXXX,                            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX)
};

// HELPER FUNCTION DEFINITIONS

void set_layer_rgb(uint32_t layer) {
    uint8_t diff = 0;
    rgb_matrix_mode(RGB_MATRIX_RIVERFLOW);
    switch (layer) {
        case _MAC: {
            // fallthrough
        }
        case _WIN: {
            diff = 0;
            break;
        }
        case _FN0: {
            diff = -31;
            break;
        }
        case _FN1: {
            diff = 54;
            break;
        }
        case _FN2: {
            diff = 75;
            break;
        }
        case _BABY: {
            rgb_matrix_mode(RGB_MATRIX_MULTISPLASH);
            break;
        }
        default: { // should be unreachable
            break;
        }
    }
    rgb_matrix_sethsv(BASE_COL.h+diff,BASE_COL.s,BASE_COL.v);
}

void update_base_col(int i) {
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

    // DEPRECATED CUS I AINT GOTTA MAC
    // [MAC_BASE] = LAYOUT_ansi_61(
    //     KC_ESC,  KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,
    //     KC_TAB,  KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,
    //     KC_CAPS, KC_A,     KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,            KC_ENT,
    //     KC_LSFT,           KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH,            KC_RSFT,
    //     KC_LCTL, KC_LOPT,  KC_LCMD,                            KC_SPC,                             KC_RCMD,  MO(_FN1), MO(_FN3), KC_RCTL),
