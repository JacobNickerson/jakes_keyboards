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

// RGB
#define DEFAULT_H 116
#define DEFAULT_S 255
#define DEFAULT_V 255

// HELPER FUNCTIONS
// Definitions are below the QMK block
void set_layer_rgb(uint32_t layer);
void update_base_colo(int i);
inline uint8_t matrix_index(uint32_t row, uint32_t col);

// QMK
enum layers {
    _BASE=0, _FN0, _FN1, _FN2, _BABY
};

static hsv_t BASE_COL = {
    .h = DEFAULT_H,
    .s = DEFAULT_S,
    .v = DEFAULT_V
};

// NOTE: Custom keycodes defined in al68.h to work with the yunzii provided source

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

bool rgb_matrix_indicators_user(void) {
    if (host_keyboard_led_state().caps_lock) {
		rgb_matrix_set_color(25,255,0,0);
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
            case WN_1: {
                tap_code16(G(KC_1));
                return false;
            }
            case WN_2: {
                tap_code16(G(KC_2));
                return false;
            }
            case WN_3: {
                tap_code16(G(KC_3));
                return false;
            }
            case WN_4: {
                tap_code16(G(KC_4));
                return false;
            }
            case WN_5: {
                tap_code16(G(KC_5));
                return false;
            }
            case WN_S: {
                tap_code16(G(KC_S));
                return false;
            }
            case WNMV_1: {
                tap_code16(G(S(KC_1)));
                return false;
            }
            case WNMV_2: {
                tap_code16(G(S(KC_2)));
                return false;
            }
            case WNMV_3: {
                tap_code16(G(S(KC_3)));
                return false;
            }
            case WNMV_4: {
                tap_code16(G(S(KC_4)));
                return false;
            }
            case WNMV_5: {
                tap_code16(G(S(KC_5)));
                return false;
            }
            case WNMV_S: {
                tap_code16(G(S(KC_S)));
                return false;
            }
        }
    }
    return true;  // let QMK handle other keys
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_65_ansi_blocker(
    KC_ESC,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_MINS,    KC_EQL,     KC_BSPC,    KC_MUTE,
    MO(_FN0),   KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_LBRC,    KC_RBRC,    KC_BSLS,    KC_PGUP,
    KC_TAB,     KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,                KC_ENT,     KC_PGDN,
    KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_RSFT,                KC_UP,      KC_DEL,
    KC_LCTL,    KC_LGUI,    KC_LALT,                            KC_SPC,                             MO(_FN0),   MO(_FN1),                           KC_LEFT,    KC_DOWN,    KC_RIGHT
    ),
    [_FN0] = LAYOUT_65_ansi_blocker(
    KC_GRV,     KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,     KC_PSCR,    _______,
    WNMV_S,     WNMV_1,     WNMV_2,     WNMV_3,     WNMV_4,     WNMV_5,     WN_LEFT,    WN_DOWN,    WN_UP,      WN_RGHT,    _______,    _______,    _______,    _______,    _______,
    WN_S,       WN_1,       WN_2,       WN_3,       WN_4,       WN_5,       KC_LEFT,    KC_DOWN,    KC_UP,      KC_RGHT,    _______,    _______,                _______,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                _______,    QK_LLCK,
    _______,    _______,    _______,                            _______,                            _______,    _______,                            _______,    _______,    _______
    ),
    [_FN1] = LAYOUT_65_ansi_blocker(
    // TODO: Find replacement for RGB_TOG
    RM_RES,     KC_F13,     KC_F14,     KC_F15,     KC_F16,     KC_F17,     KC_F18,     KC_F19,     KC_F20,     KC_F21,     KC_F22,     KC_F23,     KC_F24,     XXXXXXX,    _______,
    _______,    RM_NEXT,    RM_HUEU,    RM_SATU,    RM_VALU,    RM_SPDU,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    KC_CAPS,    RM_PREV,    RM_HUED,    RM_SATD,    RM_VALD,    RM_SPDD,    _______,    _______,    _______,    _______,    _______,    _______,                _______,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                RM_VALU,    _______,
    _______,    _______,    _______,                            _______,                            _______,    _______,                            RM_SATD,    RM_VALD,    RM_SATU
    ),
    [_FN2] = LAYOUT_65_ansi_blocker(
    QK_BOOT,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    TO(_BABY),  XXXXXXX,
    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,                XXXXXXX,    XXXXXXX,
    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,                XXXXXXX,    XXXXXXX,
    XXXXXXX,    XXXXXXX,    XXXXXXX,                            XXXXXXX,                            XXXXXXX,    XXXXXXX,                            XXXXXXX,    XXXXXXX,    XXXXXXX
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
    uint8_t diff = 0;
    if (layer == _BABY) {
        rgb_matrix_mode(RGB_MATRIX_CYCLE_OUT_IN_DUAL);
    } else {
        static uint8_t colors[] = {
            0,
            -31,
            54,
            75,
            107,
            153
        };
        diff = colors[layer];
    }
    rgb_matrix_sethsv(BASE_COL.h+diff,BASE_COL.s,BASE_COL.v);
    if (layer != _BABY) { rgb_matrix_mode(RGB_MATRIX_RIVERFLOW); }
}

void update_base_colo(int i) {
    hsv_t curr = rgb_matrix_get_hsv();
    switch(i) {
        case 0: {
            BASE_COL.h = curr.h;
            break;
        }
        case 1:{
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

inline uint8_t matrix_index(uint32_t row, uint32_t col) {
    return row * MATRIX_COLS + col;
}