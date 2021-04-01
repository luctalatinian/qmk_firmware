#include QMK_KEYBOARD_H

#include "lrgb.h"

void matrix_init_user(void);
void matrix_scan_user(void);
void rgb_matrix_indicators_user(void);
void raw_hid_receive(uint8_t* data, uint8_t length);
bool process_record_user(uint16_t keycode, keyrecord_t *record);

uint32_t boot_press_timer;

enum ctrl_keycodes
{
    KC_BT__ = SAFE_RANGE, // flash mode
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,             KC_PSCR, _______, KC_BT__, \
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,   KC_INS,  KC_HOME, KC_PGUP, \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,   KC_DEL,  KC_END,  KC_PGDN, \
        _______, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT, \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                              KC_UP, \
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, _______, _______, KC_RCTL,            KC_LEFT, KC_DOWN, KC_RGHT \
    ),
    /*
    [X] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                              _______, \
        _______, _______, _______,                   _______,                            _______, _______, _______, _______,            _______, _______, _______ \
    ),
    */
};


void matrix_init_user() {}

void matrix_scan_user() {}

void rgb_matrix_indicators_user()
{
    lrgb_set_keys_grey(RGB_CYAN);
    lrgb_set_keys_black(RGB_WHITE);
    lrgb_set_underglow_back(0, 0xff, 0x80);
    lrgb_set_underglow_status();
}

void raw_hid_receive(uint8_t* data, uint8_t length) {}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_BT__:
            if (record->event.pressed) {
                boot_press_timer = timer_read32();
            } else {
                if (timer_elapsed32(boot_press_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        default:
            return true;
    }
}
