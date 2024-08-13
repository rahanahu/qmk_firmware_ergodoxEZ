// Copyright 2021 JasonRen(biu)
// Copyright 2022 Drashna Jael're (@Drashna Jael're)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#define MT_SS MT(MOD_LSFT, KC_SPACE)
#include <keymap_japanese.h>

enum Layer_name {
    HOME,
    SANDS,
    FUNC,
    MODS
};


uint16_t hold_timers[MATRIX_ROWS][MATRIX_COLS];


enum custom_keycodes {
  //--layers--
  // layouts

  // os

  // lang

  CK_C_MHE = SAFE_RANGE,
  CK_SANDS,
};

void type_code(uint8_t keycode){
  register_code (keycode);
  unregister_code (keycode);
};

void set_eisu(void){
  type_code (JP_MHEN);
  type_code (KC_LNG2);
};

void set_kana(void){
  type_code (JP_HENK);
  type_code (KC_LNG1);
};

bool is_tap (keyrecord_t *record) {
  return hold_timers[record->event.key.row][record->event.key.col]
  && timer_elapsed (hold_timers[record->event.key.row][record->event.key.col]) < TAPPING_TERM;
}

void mod_tap_action(keyrecord_t *record, uint8_t mod, void (*cb)(void) ) {
  if (record->event.pressed) {
    add_mods(MOD_BIT(mod));
  } else {
    if (is_tap(record)) {
      del_mods(MOD_BIT(mod));
      cb();
    } else {
      unregister_code(mod);
    }
  }
}
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MT_SS:
            return 90; 
        default:
            return TAPPING_TERM;
    }
}
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MT_SS:
            // Immediately select the hold action when another key is tapped.
            return true;
        default:
            // Do not select the hold action when another key is tapped.
            return false;
    }
}
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // record pressed timer
  if (record->event.pressed) {
    hold_timers[record->event.key.row][record->event.key.col] = timer_read();
  }

  switch (keycode) {
    //--layers--

    //layout

    //os

    // langs
    case CK_C_MHE:
      mod_tap_action(record, KC_RCTL, set_eisu);
      return false;
      break;

    // Ctrl-Q -> Alt-F4
    case KC_D:
      if (
        record->event.pressed
        && (get_mods() & MOD_BIT(KC_RCTL))
      ) {
        clear_keyboard();
        del_mods(MOD_BIT(KC_RCTL));
        type_code(KC_DEL);
        add_mods(MOD_BIT(KC_RCTL));
        return false;
      }
      break;
    // C-a -> HOME
    case KC_A:
      if (
        record->event.pressed
        && (get_mods() & MOD_BIT(KC_RCTL))
      ) {
        clear_keyboard();
        del_mods(MOD_BIT(KC_RCTL));
        type_code(KC_HOME);
        add_mods(MOD_BIT(KC_RCTL));
        return false;
      }
      break; 
    // C-e -> END
    case KC_E:
      if (
        record->event.pressed
        && (get_mods() & MOD_BIT(KC_RCTL))
      ) {
        clear_keyboard();
        del_mods(MOD_BIT(KC_RCTL));
        type_code(KC_END);
        add_mods(MOD_BIT(KC_RCTL));
        return false;
      }
      break; 

    // C-k -> kill line
    case KC_K:
      if (
        record->event.pressed
        && (get_mods() & MOD_BIT(KC_RCTL))
      ) {
        clear_keyboard();
        del_mods(MOD_BIT(KC_RCTL));
        type_code(KC_HOME);
        add_mods(MOD_BIT(KC_LSFT));
        type_code(KC_END);
        del_mods(MOD_BIT(KC_LSFT));
        type_code(KC_DEL);
        add_mods(MOD_BIT(KC_RCTL));
        return false;
      }
      break;
    // RCTL + ,(<) -> [
    case KC_COMM:
      if (
        record->event.pressed
        && (get_mods() & MOD_BIT(KC_RCTL))
      ) {
        bool shift_pressed = get_mods() & MOD_MASK_SHIFT;
        clear_keyboard();
        del_mods(MOD_BIT(KC_RCTL));
        if (shift_pressed){
          register_code(KC_LSFT);
          type_code(JP_LBRC);
          unregister_code(KC_LSFT);
          add_mods(MOD_BIT(KC_LSFT));
        }else{
          type_code(JP_LBRC);
        }
        add_mods(MOD_BIT(KC_RCTL));
        return false;
      }
      break;
    // RCTL + .(>) -> ]
    case KC_DOT:
      if (
        record->event.pressed
        && (get_mods() & MOD_BIT(KC_RCTL))
      ) {
        bool shift_pressed = get_mods() & MOD_MASK_SHIFT;
        clear_keyboard();
        del_mods(MOD_BIT(KC_RCTL));
        if (shift_pressed){
          register_code(KC_LSFT);
          type_code(JP_RBRC);
          unregister_code(KC_LSFT);
          add_mods(MOD_BIT(KC_LSFT));
        }else{
          type_code(JP_RBRC);
        }
        add_mods(MOD_BIT(KC_RCTL));
        return false;
      }
      break; 
    default:
        break;
  }
  return true;
}

// void matrix_scan_user(void) {
//     for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
//         for (uint8_t j = 0; j < MATRIX_COLS; j++) {
//             if (matrix_is_on(i, j)) {
//                 uint8_t led_index = g_led_config.matrix_co[i][j];
//                 if (led_index != NO_LED) {
//                     rgb_matrix_set_color(led_index, 255, 0, 0);  // 赤色に点灯
//                 }
//             }
//         }
//     }
// }

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,-------------------------------------------------.           ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Del    |   Q  |   W  |   E  |   R  |   T  |  L1  |           |  L1  |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | BkSp   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |; / L2|' / Cmd |
 * |--------+------+------+------+------+------| Hyper|           | Meh  |------+------+------+------+------+--------|
 * | LShift |Z/Ctrl|   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |//Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Grv/L1|  '"  |AltShf| Left | Right|                                       |  Up  | Down |   [  |   ]  | ~L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | App  | LGui |       | Alt  |Ctrl/Esc|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 *                                 |      |ace   | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
LAYOUT_ergodox(
        // left hand
        KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5, TG(SANDS),
        KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T, C(KC_INS),
        KC_LCTL,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,
        KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, S(KC_INS),
        MO(FUNC), KC_GRV, KC_LALT, KC_LEFT, KC_RGHT,
                                                      KC_DEL,   KC_HOME,
                                                                KC_END,
                                             KC_SPC,  KC_RCTL,  CK_C_MHE,
        // right hand
        JP_AT,   KC_6,   KC_7,    KC_8,    KC_9,    KC_0,     JP_YEN,
        JP_CIRC, KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,     JP_BSLS,
                 KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,
        JP_MINS, KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  JP_BSLS,
                         KC_UP,   KC_DOWN, JP_LBRC, JP_RBRC,  MO(MODS),
        KC_PGUP, KC_LWIN,
        KC_PGDN,
        JP_HENK, KC_BSPC, KC_ENT
    ),

LAYOUT_ergodox(
        // left hand
        KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5, TG(SANDS),
        KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T, C(KC_INS),
        KC_LCTL,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,
        KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, S(KC_INS),
        MO(FUNC), KC_GRV, KC_LALT, KC_LEFT, KC_RGHT,
                                                      KC_DEL,   KC_HOME,
                                                                KC_END,
                                             MT_SS,  KC_RCTL,  JP_MHEN,
        // right hand
        JP_AT,   KC_6,   KC_7,    KC_8,    KC_9,    KC_0,     JP_YEN,
        JP_CIRC, KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,     JP_BSLS,
                 KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,
        JP_MINS, KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  JP_BSLS,
                         KC_UP,   KC_DOWN, JP_LBRC, JP_RBRC,  MO(MODS),
        KC_PGUP, KC_LWIN,
        KC_PGDN,
        JP_HENK, KC_BSPC, KC_ENT
    ),


/* Keymap 1: Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      |      |                                       |      |    . |   0  |   =  |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |Animat|      |       |Toggle|      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |Bright|Bright|      |       |      |Hue-  |Hue+  |
 *                                 |ness- |ness+ |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
LAYOUT_ergodox(
       // left hand
       KC_TRNS,  KC_F1,    KC_F2,    KC_F3,    KC_F4,     KC_F5,    KC_TRNS,
       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  C(A(KC_DEL)),
       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,
       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,
       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                                                          KC_TRNS,KC_TRNS,
                                                                  KC_TRNS,
                                                  KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_TRNS, KC_TRNS, KC_7,   KC_8,    KC_9,    KC_ASTR, KC_F12,
                KC_TRNS, KC_4,   KC_5,    KC_6,    KC_PLUS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_1,   KC_2,    KC_3,    KC_BSLS, KC_TRNS,
                         KC_TRNS,KC_TRNS, KC_DOT,  KC_NUM,  KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_KP_0
    ),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
LAYOUT_ergodox(
       // left hand
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, RGB_MOD,
                                                    RGB_VAI,
                                  KC_TRNS, KC_TRNS, RGB_VAD,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_VOLU, KC_VOLD, KC_TRNS, KC_TRNS, KC_TRNS,
       RGB_TOG, KC_TRNS,
       RGB_HUI,
       RGB_HUD, KC_TRNS, KC_WBAK
    ),
};
