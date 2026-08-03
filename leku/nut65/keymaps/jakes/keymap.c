// Copyright 2024 sdk66 (@sdk66)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "rgb_record/rgb_record.h"

// RGB
#define DEFAULT_H 116
#define DEFAULT_S 255
#define DEFAULT_V 255
static HSV BASE_COL = {
    .h = DEFAULT_H,
    .s = DEFAULT_S,
    .v = DEFAULT_V
};

// HELPER FUNCTIONS
// Definitions are below the QMK block
void set_layer_rgb(uint32_t layer);
void update_base_colo(int i);
inline uint8_t matrix_index(uint32_t row, uint32_t col);

// QMK
enum custom_keycodes {
    RM_RES = SAFE_RANGE, // Reset RGB to default
    // Keys for navigating virtual desktops
    WN_LEFT, WN_RGHT, WN_UP, WN_DOWN,
    WN_1, WN_2, WN_3, WN_4, WN_5,
    WN_6, WN_7, WN_8, WN_9, WN_0, WN_S,
    WNMV_1, WNMV_2, WNMV_3, WNMV_4, WNMV_5,
    WNMV_6, WNMV_7, WNMV_8, WNMV_9, WNMV_0, WNMV_S
};

enum layers {
    _BASE=0, _FN0, _FN1, _FN2, _BABY
};

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

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_ESC,   KC_1,       KC_2,       KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,       KC_MINS,  KC_EQL,   KC_BSPC,   KC_MUTE,
        KC_LALT,  KC_Q,       KC_W,       KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,       KC_LBRC,  KC_RBRC,  KC_BSLS,   KC_PGUP,
        KC_TAB,   KC_A,       KC_S,       KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,    KC_QUOT,            KC_ENT,    KC_PGDN,
        KC_LSFT,  KC_Z,       KC_X,       KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,    KC_RSFT,            KC_UP,     KC_DEL,
        KC_LCTL,  KC_LGUI,    MO(_FN0),                       KC_SPC,                       MO(_FN0), MO(_FN1),                       KC_LEFT,  KC_DOWN,   KC_RIGHT,

        KC_NO,    KC_NO,      KC_NO,      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,      KC_NO,    KC_NO,    KC_NO,     KC_NO
    ),  

    [_FN0] = LAYOUT(
        KC_GRV,   KC_F1,      KC_F2,      KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,     KC_F11,   KC_F12,   _______,   _______,
        WNMV_S,   WNMV_1,     WNMV_2,     WNMV_3,   WNMV_4,   WNMV_5,   WNMV_6,   WNMV_7,   WNMV_8,   WNMV_9,   WNMV_0,     _______,  _______,  _______,   KC_PSCR,
        WN_S,     WN_1,       WN_2,       WN_3,     WN_4,     WN_5,     WN_6,     WN_7,     WN_8,     WN_9,     WN_0,       _______,            _______,   _______,
        _______,  _______,    _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,            KC_VOLU,   _______,
        _______,  _______,    _______,                        _______,                      _______,  _______,                        _______,  KC_VOLD,   _______,

        KC_NO,    KC_NO,      KC_NO,      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,      KC_NO,    KC_NO,    KC_NO,     KC_NO
    ),

    [_FN1] = LAYOUT(
        RM_RES,   KC_F13,     KC_F14,     KC_F15,   KC_F16,   KC_F17,   KC_F18,   KC_F19,   KC_F20,   KC_F21,   KC_F22,     KC_F23,   KC_F24,   RM_TOGG,   _______,
        _______,  RM_NEXT,    RM_HUEU,    RM_SATU,  RM_VALU,  RM_SPDU,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,   _______,
        KC_CAPS,  RM_PREV,    RM_HUED,    RM_SATD,  RM_VALD,  RM_SPDD,  _______,  _______,  _______,  _______,  _______,    _______,            _______,   _______,
        _______,  _______,    _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,            RM_VALU,   _______,
        _______,  _______,    _______,                        _______,                      _______,  _______,                        RM_SATD,  RM_VALD,   RM_SATU,

        KC_NO,    KC_NO,      KC_NO,      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,      KC_NO,    KC_NO,    KC_NO,     KC_NO
    ),  

    [_FN2] = LAYOUT(
        QK_BOOT,  XXXXXXX,    XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,  XXXXXXX,  TO(_BABY), XXXXXXX,
        XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,
        XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,            XXXXXXX,   XXXXXXX,
        XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,            XXXXXXX,   XXXXXXX,
        XXXXXXX,  XXXXXXX,    XXXXXXX,                        XXXXXXX,                      XXXXXXX,  XXXXXXX,                        XXXXXXX,  XXXXXXX,   XXXXXXX,

        KC_NO,    KC_NO,      KC_NO,      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,      KC_NO,    KC_NO,    KC_NO,     KC_NO
    ),

    [_BABY] = LAYOUT(
        XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,   TO(_BASE),
        XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,
        XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,            XXXXXXX,   XXXXXXX,
        XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,            XXXXXXX,   XXXXXXX,
        XXXXXXX,  XXXXXXX,    XXXXXXX,                        XXXXXXX,                      XXXXXXX,  XXXXXXX,                        XXXXXXX,  XXXXXXX,   XXXXXXX,

        KC_NO,    KC_NO,      KC_NO,      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,      KC_NO,    KC_NO,    KC_NO,     KC_NO
    )
};

const uint16_t PROGMEM rgbrec_default_effects[RGBREC_CHANNEL_NUM][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        ________, ________,   ________,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________, 
        ________, ________,   ________,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________, 
        ________, ________,   ________,   ________, ________, ________, ________, ________, ________, ________, ________,   ________,           ________,  ________,
        ________,             ________,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________,
        ________, ________,   ________,                       ________,                                         ________,   ________, ________, ________,  ________,
        ________, ________,   ________,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________
        ),

    [1] = LAYOUT(
        ________, ________,   ________,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________, 
        ________, ________,   ________,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________, 
        ________, ________,   ________,   ________, ________, ________, ________, ________, ________, ________, ________,   ________,           ________,  ________,
        ________,             ________,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________,
        ________, ________,   ________,                       ________,                                         ________,   ________, ________, ________,  ________,
        ________, ________,   ________,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________
        ),

    [2] = LAYOUT(
        ________, ________,   ________,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________, 
        ________, ________,   ________,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________, 
        ________, ________,   ________,   ________, ________, ________, ________, ________, ________, ________, ________,   ________,           ________,  ________,
        ________,             ________,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________,
        ________, ________,   ________,                       ________,                                         ________,   ________, ________, ________,  ________,
        ________, ________,   ________,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________
        ),
};

#define WN(N)                  \
    case WN_##N: {             \
        tap_code16(G(KC_##N)); \
        return false;          \
    }
#define WNMV(N)                   \
    case WNMV_##N: {              \
        tap_code16(G(S(KC_##N))); \
        return false;             \
    }
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
            WN(1)
            WN(2)
            WN(3)
            WN(4)
            WN(5)
            WN(6)
            WN(7)
            WN(8)
            WN(9)
            WN(0)
            WN(S)
            WNMV(1)
            WNMV(2)
            WNMV(3)
            WNMV(4)
            WNMV(5)
            WNMV(6)
            WNMV(7)
            WNMV(8)
            WNMV(9)
            WNMV(0)
            WNMV(S)
        }
    }
    return true;  // let QMK handle other keys
}

// clang-format on

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
    HSV curr = rgb_matrix_get_hsv();
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