// Copyright 2021 JasonRen(biu)
// Copyright 2022 Drashna Jael're (@Drashna Jael're)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include <keymap_japanese.h>

#define L0 0 // default layer
#define L1 1
#define MODL 2


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌──────┬───┬───┬───┬───┬───┬───┐                     ┌───┬───┬───┬───┬───┬───┬──────┐
     * │ `    │ 1 │ 2 │ 3 │ 4 │ 5 │ = │         ^           │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │    - │
     * ├──────┼───┼───┼───┼───┼───┼───┤                     ├───┼───┼───┼───┼───┼───┼──────┤
     * │ Tab  │ Q │ W │ E │ R │ T │ = │                     │ Y │ Y │ U │ I │ O │ P │    \ │
     * ├──────┼───┼───┼───┼───┼───┤   │                     │   ├───┼───┼───┼───┼───┼──────┤
     * │Escape│ A │ S │ D │ F │ G ├───┤                     ├───┤ H │ J │ K │ L │ ; │    ' │
     * ├──────┼───┼───┼───┼───┼───┤   │                     │   ├───┼───┼───┼───┼───┼──────┤
     * │Shift │ Z │ X │ C │ V │ B │ B │                     │ N │ N │ M │ , │ . │ / │ Shift│
     * └──┬───┼───┼───┼───┼───┼───┴───┘ ┌───┬───┐ ┌───┬───┐ └───┴───┼───┼───┼───┼───┼───┬──┘
     *    │Ctl│F4 │F5 │GUI│Alt│         │ C │ V │ │Alt│ A │         │ ← │ ↓ │ ↑ │ → │GUI│
     *    └───┴───┴───┴───┴───┘     ┌───┼───┼───┤ ├───┼───┼───┐     └───┴───┴───┴───┴───┘
     *                              │   │   │PgU│ │PgD│   │   │
     *                              │Bsp│Bsp├───┤ ├───┤Ent│   │
     *                              │   │   │Del│ │Ctl│   │   │
     *                              └───┴───┴───┘ └───┴───┴───┘
     */
    [L0] = LAYOUT_ergodox_pretty(
        KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5, TG(L1),             JP_AT,   KC_6,   KC_7,    KC_8,    KC_9,    KC_0,     JP_CIRC,          
        KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T, C(KC_INS),          JP_CIRC, KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,     JP_BSLS,    
        KC_LCTL,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                              KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,       
        KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, S(KC_INS),          JP_MINS, KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  JP_BSLS,   
        MO(L1),   KC_GRV, KC_LALT, KC_LEFT, KC_RGHT,                                            KC_UP,   KC_DOWN, JP_LBRC, JP_RBRC,  MO(MODL),    
                                                      KC_DEL,   KC_HOME,       KC_PGUP, KC_LWIN,    
                                                                KC_END,        KC_PGDN,   
                                             KC_SPC,  KC_RCTL,  JP_MHEN,       JP_HENK, KC_BSPC, KC_ENT    
    ),

    [L1] = LAYOUT_ergodox_pretty(
       KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   TG(L0),          KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,     KC_F10,  KC_F11,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, C(A(KC_DEL)),    KC_TRNS, KC_TRNS, KC_KP_7, KC_KP_8, KC_KP_9,   KC_TRNS, KC_F12,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                           KC_TRNS, KC_KP_4, KC_KP_5, KC_KP_6,   KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_KP_1, KC_KP_2, KC_KP_3,   KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                             KC_TRNS, KC_TRNS, KC_KP_DOT, KC_TRNS,  KC_TRNS,
                                                      KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS,
                                                               KC_TRNS,       KC_TRNS,
                                             KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS, KC_KP_0
    )
};
