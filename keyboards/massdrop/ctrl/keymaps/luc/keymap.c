#include QMK_KEYBOARD_H

#include "lcol.h"
#include "lrgb.h"
#include "ltimer.h"
#include "print.h"

typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} userdata_rgb;

void matrix_init_user(void);
void matrix_scan_user(void);
void rgb_matrix_indicators_user(void);
void raw_hid_receive(uint8_t* data, uint8_t length);
bool process_record_user(uint16_t keycode, keyrecord_t *record);

void handle_runtime_color_config(uint16_t keycode);
void reset_led_groups(void);

uint32_t boot_press_timer;

lcol_list *target_led_groups;

uint32_t runtime_color_configval = 0;
uint32_t runtime_color_configpos = 0;

lrgb_group_config config_grey = LRGB_GROUP_INIT(0, 0xff, 0xff);
lrgb_group_config config_black = LRGB_GROUP_INIT(0xff, 0xff, 0xff);
lrgb_group_config config_vim = LRGB_GROUP_INIT(0, 0xff, 0);
lrgb_group_config config_underglow = LRGB_GROUP_INIT(0, 0xff, 0x80);

enum ctrl_keycodes
{
    KC_BT__ = SAFE_RANGE, // flash mode

    KC_SLG0, // set led group 0 (grey)
    KC_SLG1, // set led group 1 (black)
    KC_SLG2, // set led group 2 (vim)
    KC_SLG3, // set led group 3 (underglow)

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

    KC_RSLG, // reset led groups

    KC_TDBG, // toggle debug
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,             KC_PSCR, _______, KC_BT__, \
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,   KC_INS,  KC_HOME, KC_PGUP, \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,   KC_DEL,  KC_END,  KC_PGDN, \
        _______, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT, \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                              KC_UP, \
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, MO(1),   _______, KC_RCTL,            KC_LEFT, KC_DOWN, KC_RGHT \
    ),
    [1] = LAYOUT(
        KC_RSLG, KC_SLG0, KC_SLG1, KC_SLG2, KC_SLG3, _______, _______, _______, _______, _______, _______, _______, _______,            _______, _______, _______, \
        KC_TDBG, CNF_1,   CNF_2,   CNF_3,   CNF_4,   CNF_5,   CNF_6,   CNF_7,   CNF_8,   CNF_9,   CNF_0,   _______, _______, _______,   _______, _______, _______, \
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
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                              _______, \
        _______, _______, _______,                   _______,                            _______, _______, _______, _______,            _______, _______, _______ \
    ),
    */
};

bool lled_enable = true;

void test_blink(void)
{
    lled_enable = !lled_enable;
}

void matrix_init_user()
{
    rgb_matrix_mode(RGB_MATRIX_NONE);

    target_led_groups = lcol_list_new();

    ltimer_init();
    ltimer_set_interval(test_blink, 500);
}

void matrix_scan_user()
{
    ltimer_select();
}

void rgb_matrix_indicators_user()
{
    if (!lled_enable)
    {
        rgb_matrix_set_color_all(0,0,0);
        return;
    }

    lrgb_set_keys_grey(LRGB_GROUP_EXPAND(config_grey));
    lrgb_set_keys_black(LRGB_GROUP_EXPAND(config_black));
    lrgb_set_keys_vim(LRGB_GROUP_EXPAND(config_vim));
    lrgb_set_underglow_back(LRGB_GROUP_EXPAND(config_underglow));
    lrgb_set_underglow_status(runtime_color_configpos);
}

void raw_hid_receive(uint8_t* data, uint8_t length) {}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_SLG0: case KC_SLG1: case KC_SLG2: case KC_SLG3:
            if (record->event.pressed)
                lcol_list_push(target_led_groups, (void*)(keycode - KC_SLG0));
            return false;
        case CNF_0: case CNF_1: case CNF_2: case CNF_3:
        case CNF_4: case CNF_5: case CNF_6: case CNF_7:
        case CNF_8: case CNF_9: case CNF_A: case CNF_B:
        case CNF_C: case CNF_D: case CNF_E: case CNF_F:
            // never in one's life has case fallthrough been this relevant
            if (record->event.pressed)
                handle_runtime_color_config(keycode);
            return false;
        case KC_RSLG:
            reset_led_groups();
            return false;
        case KC_BT__:
            if (record->event.pressed) {
                boot_press_timer = timer_read32();
            } else {
                if (timer_elapsed32(boot_press_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        case KC_TDBG:
            if (record->event.pressed)
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            return false;
        default:
            return true;
    }
}

void lambda_apply_target_config(lcol_node* n, void *userdata)
{
    int target_led_group = (int)n->data;
    userdata_rgb rgb = *(userdata_rgb*)userdata;
    uint8_t _r = rgb.r;
    uint8_t _g = rgb.g;
    uint8_t _b = rgb.b;

    if (target_led_group == 0) // grey
    {
        config_grey.r = _r;
        config_grey.g = _g;
        config_grey.b = _b;
    }
    else if (target_led_group == 1) // black
    {
        config_black.r = _r;
        config_black.g = _g;
        config_black.b = _b;
    }
    else if (target_led_group == 2) // vim
    {
        config_vim.r = _r;
        config_vim.g = _g;
        config_vim.b = _b;
    }
    else if (target_led_group == 3) // underglow
    {
        config_underglow.r = _r;
        config_underglow.g = _g;
        config_underglow.b = _b;
    }
}

void handle_runtime_color_config(uint16_t keycode)
{
    uint16_t v = keycode - CNF_0;
    runtime_color_configval |= v << (runtime_color_configpos++ * 4);
    if (runtime_color_configpos == 6) {
        int _r = (runtime_color_configval >>  0) & 0xff;
        int _g = (runtime_color_configval >>  8) & 0xff;
        int _b = (runtime_color_configval >> 16) & 0xff;

        // human-readable version has the nibbles swapped from what they should be
        _r = ((_r&0x0f)<<4) | ((_r&0xf0)>>4);
        _g = ((_g&0x0f)<<4) | ((_g&0xf0)>>4);
        _b = ((_b&0x0f)<<4) | ((_b&0xf0)>>4);

        userdata_rgb userdata = {.r = _r, .g = _g, .b = _b};
        if (target_led_groups->head != NULL)
            lcol_list_foreach(target_led_groups, lambda_apply_target_config, &userdata);

        lcol_list_clear(target_led_groups);

        runtime_color_configval = 0;
        runtime_color_configpos = 0;
    }
}

void reset_led_groups()
{
    lrgb_group_config_set(&config_grey,      0,    0xff, 0xff);
    lrgb_group_config_set(&config_black,     0xff, 0xff, 0xff);
    lrgb_group_config_set(&config_vim,       0,    0xff,    0);
    lrgb_group_config_set(&config_underglow, 0,    0xff, 0x80);
}
