/* Copyright 2022 Jacky
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

// HELPER FUNCTIONS
// Definitions are below the QMK block
void set_layer_rgb(uint32_t layer);
inline uint8_t matrix_index(uint32_t row, uint32_t col);

// QMK

enum layers {
    _BASE=0, _FN0, _FN1, _FN2, _BABY
};

void keyboard_post_init_user(void) {
    rgb_matrix_enable();
    rgb_matrix_mode(RGB_MATRIX_RIVERFLOW);
    rgb_matrix_sethsv(116,255,255);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _FN0, _FN1, _FN2);
    set_layer_rgb(get_highest_layer(state));
    return state;
}

bool rgb_matrix_indicators_user(void) {
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(25,255,0,0);
        rgb_matrix_set_color(52,255,0,0);
        rgb_matrix_set_color(53,255,0,0);
        rgb_matrix_set_color(54,255,0,0);
    }
    return true;
}

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD)  },
    [_FN0] =  { ENCODER_CCW_CW(_______, _______)  },
    [_FN1] =  { ENCODER_CCW_CW(_______, _______)  },
    [_FN2] =  { ENCODER_CCW_CW(_______, _______)  },
    [_BABY] = { ENCODER_CCW_CW(XXXXXXX, XXXXXXX)  }
};
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_65_ansi_blocker(
    KC_ESC,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_MINS,    KC_EQL,     KC_BSPC,    KC_MUTE,
    KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_LBRC,    KC_RBRC,    KC_BSLS,    KC_DELETE,
    KC_LCTL,    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,                KC_ENT,     KC_PAGE_UP,
    KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_RSFT,                KC_UP,      KC_PAGE_DOWN,
    MO(_FN0),   KC_LGUI,    KC_LALT,                            KC_SPC,                             MO(_FN0),   MO(_FN1),                           KC_LEFT,    KC_DOWN,    KC_RIGHT
    ),
    [_FN0] = LAYOUT_65_ansi_blocker(
    KC_GRV,     KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,     KC_PSCR,    _______,
    KC_CAPS,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT,   _______,    _______,                _______,    _______,
    _______,    MS_BTN1,    MS_BTN2,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                _______,    QK_LLCK,
    _______,    _______,    _______,                            _______,                            _______,    _______,                            _______,    _______,    _______
    ),
    [_FN1] = LAYOUT_65_ansi_blocker(
    _______,    KC_F13,     KC_F14,     KC_F15,     KC_F16,     KC_F17,     KC_F18,     KC_F19,     KC_F20,     KC_F21,     KC_F22,     KC_F23,     KC_F24,    RGB_TOG,     _______,
    _______,    _______,    RM_SPDU,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    _______,    RM_SPDD,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                _______,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                RM_VALU,    _______,
    _______,    _______,    _______,                            _______,                            _______,    _______,                            RM_SATD,    RM_VALD,    RM_SATU
    ),
    [_FN2] = LAYOUT_65_ansi_blocker(
    QK_BOOT,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    TO(_BABY),  _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                _______,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                _______,    _______,
    _______,    _______,    _______,                            _______,                            _______,    _______,                            _______,    _______,    _______
    ),
    [_BABY] = LAYOUT_65_ansi_blocker(
    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    TO(_BASE),
    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,                XXXXXXX,    XXXXXXX,
    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,                XXXXXXX,    XXXXXXX,
    XXXXXXX,    XXXXXXX,    XXXXXXX,                            XXXXXXX,                            XXXXXXX,    XXXXXXX,                            XXXXXXX,    XXXXXXX,    XXXXXXX
    )
};


// HELPERS

void set_layer_rgb(uint32_t layer) {
    hsv_t curr = rgb_matrix_get_hsv();
    rgb_matrix_mode(RGB_MATRIX_RIVERFLOW);
    switch (layer) {
        case _BASE: {
            curr.h = 116;
            break;
        }
        case _BABY: {
            rgb_matrix_mode(RGB_MATRIX_MULTISPLASH);
            break;
        }
        case _FN0: {
            curr.h = 85;
            break;
        }
        case _FN1: {
            curr.h = 170;
            break;
        }
        case _FN2: {
            curr.h = 191;
            break;
        }
        default: {
            break;
        }
    }
    rgb_matrix_sethsv(curr.h,curr.s,curr.v);
}

inline uint8_t matrix_index(uint32_t row, uint32_t col) {
    return row * MATRIX_COLS + col;
}