#include QMK_KEYBOARD_H
#include <string.h>
#include "raw_hid.h"
#include "print.h"

enum ctrl_keycodes {
    BOOT = SAFE_RANGE, // Restart into bootloader after hold timeout
    LED_M0,            // LED mode 0 (all)
    LED_M1,            // LED mode 1 (keys only)
    LED_M2,            // LED mode 2 (surrounding only)
    LED_M3,            // LED mode 3 (off)

    // configuration block
    CNF_0,
    CNF_1,
    CNF_2,
    CNF_3,
    CNF_4,
    CNF_5,
    CNF_6,
    CNF_7,
    CNF_8,
    CNF_9,
    CNF_A,
    CNF_B,
    CNF_C,
    CNF_D,
    CNF_E,
    CNF_F,

    DBG_TOG,               //DEBUG Toggle On / Off
    DBG_MTX,              //DEBUG Toggle Matrix Prints
    DBG_KBD,               //DEBUG Toggle Keyboard Prints
    DBG_MOU,               //DEBUG Toggle Mouse Prints
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,             KC_PSCR, KC_SLCK, BOOT, \
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,   KC_INS,  KC_HOME, KC_PGUP, \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,   KC_DEL,  KC_END,  KC_PGDN, \
        TG(1),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT, \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                              KC_UP, \
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, MO(2),   KC_APP,  KC_RCTL,            KC_LEFT, KC_DOWN, KC_RGHT \
    ),
    [1] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, \
        _______, S(KC_Q), S(KC_W), S(KC_E), S(KC_R), S(KC_T), S(KC_Y), S(KC_U), S(KC_I), S(KC_O), S(KC_P), _______, _______, _______,   _______, _______, _______, \
        TG(1),   S(KC_A), S(KC_S), S(KC_D), S(KC_F), S(KC_G), S(KC_H), S(KC_J), S(KC_K), S(KC_L), _______, _______, _______, \
        _______, S(KC_Z), S(KC_X), S(KC_C), S(KC_V), S(KC_B), S(KC_N), S(KC_M), _______, _______, _______, _______,                              _______, \
        _______, _______, _______,                   _______,                            _______, _______, _______, _______,            _______, _______, _______ \
    ),
    [2] = LAYOUT( // command mode
        _______, LED_M0,  LED_M1,  LED_M2,  LED_M3,  _______, _______, _______, _______, DBG_TOG, DBG_MTX, DBG_KBD, DBG_MOU,            _______, _______, _______, \
        _______, CNF_1,   CNF_2,   CNF_3,   CNF_4,   CNF_5,   CNF_6,   CNF_7,   CNF_8,   CNF_9,   CNF_0,   _______, _______, _______,   _______, _______, _______, \
        _______, _______, _______, CNF_E,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, \
        _______, CNF_A,   _______, CNF_D,   CNF_F,   _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, CNF_C,   _______, CNF_B,   _______, _______, _______, _______, _______, _______,                              _______, \
        _______, _______, _______,                   _______,                            _______, _______, _______, _______,            _______, _______, _______ \
    ),
    /*
    [X] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, NK_TOGG, _______, _______, _______, _______, _______,                              _______, \
        _______, _______, _______,                   _______,                            _______, _______, _______, _______,            _______, _______, _______ \
    ),
    */
};


const uint32_t TIMEOUT = 1000*60*15; // 15 minutes

void matrix_init_user(void) {
};

void matrix_scan_user(void) {
};

#define LED_ID0_FNKEYS   0b00000000000000000001111111111110
#define LED_ID1_LETTERS  0b00001111111110000000111111111100
#define LED_ID2_LETTERS  0b00000000000000000000000001111111
#define LED_ID1_CAPSLOCK 0b00000000000001000000000000000000


void raw_hid_receive(uint8_t* data, uint8_t length)
{
    dprintf("raw_hid_receive\n");
}

//uint32_t runtime_color_configval = 0;
//uint32_t runtime_color_configpos = 0;

void handle_runtime_color_config(uint16_t keycode) {
  //uint16_t v = keycode - CNF_0;
  //runtime_color_configval |= v << (runtime_color_configpos++ * 4);
  //if (runtime_color_configpos == 6) {
  //    led_base.r = (runtime_color_configval >>  0) & 0xff;
  //    led_base.g = (runtime_color_configval >>  8) & 0xff;
  //    led_base.b = (runtime_color_configval >> 16) & 0xff;

  //    led_base.r = ((led_base.r&0x0f)<<4) | ((led_base.r&0xf0)>>4);
  //    led_base.g = ((led_base.g&0x0f)<<4) | ((led_base.g&0xf0)>>4);
  //    led_base.b = ((led_base.b&0x0f)<<4) | ((led_base.b&0xf0)>>4);

  //    led_instructions[0] = led_base;

  //    runtime_color_configval = 0;
  //    runtime_color_configpos = 0;
  //}
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;
        case DBG_MTX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;
        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
            return false;
        case BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        case LED_M0:
        case LED_M1:
        case LED_M2:
        case LED_M3:
            return false;
        case CNF_0:
        case CNF_1:
        case CNF_2:
        case CNF_3:
        case CNF_4:
        case CNF_5:
        case CNF_6:
        case CNF_7:
        case CNF_8:
        case CNF_9:
        case CNF_A:
        case CNF_B:
        case CNF_C:
        case CNF_D:
        case CNF_E:
        case CNF_F:
            // never in one's life has case fallthrough been this relevant
            if (record->event.pressed) {
                handle_runtime_color_config(keycode);
            }
            return false;
        default:
            return true;
    }
}

void rgb_matrix_indicators_user(void) {
    rgb_matrix_set_color_all(0, 0xff, 0xff);
}
