#include QMK_KEYBOARD_H
#include <string.h>
#include "raw_hid.h"
#include "print.h"

#define DRIVER_LED_UNDERGLOW_START 87

void led_init_configs(void);
void led_config_enable(int index, uint8_t r, uint8_t g, uint8_t b);

void led_sleep(void);
void led_wake(void);

int stored_led_mode = -1;

enum led_index {
    ESC, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, PRINTSCREEN, SCROLLLOCK, PAUSE,
    BACKTICK, _1, _2, _3, _4, _5, _6, _7, _8, _9, _0, HYPHEN, EQUALS, BACKSPACE, INSERT, HOME, PAGEUP,
    TAB, Q, W, E, R, T, Y, U, I, O, P, LEFTBRACKET, RIGHTBRACKET, BACKSLASH, DELETE, LED_INDEX_END, PAGEDOWN,
    CAPSLOCK, A, S, D, F, G, H, J, K, L, SEMICOLON, QUOTE, ENTER,
    LSHIFT, Z, X, C, V, B, N, M, COMMA, PERIOD, SLASH, RSHIFT, UP,
    LCTRL, LGUI, LALT, SPACE, RALT, FN, RGUI, RCTRL, LEFT, DOWN, RIGHT,
};

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

    TGT_SET, // set single-led config target
};

int keycode_to_led(uint16_t keycode)
{
    switch (keycode) {
        case KC_ESC: return ESC;
        case KC_F1: return F1;
        case KC_F2: return F2;
        case KC_F3: return F3;
        case KC_F4: return F4;
        case KC_F5: return F5;
        case KC_F6: return F6;
        case KC_F7: return F7;
        case KC_F8: return F8;
        case KC_F9: return F9;
        case KC_F10: return F10;
        case KC_F11: return F11;
        case KC_F12: return F12;
        case KC_PSCR: return PRINTSCREEN;
        case KC_GRV: return BACKTICK;
        case KC_1: return _1;
        case KC_2: return _2;
        case KC_3: return _3;
        case KC_4: return _4;
        case KC_5: return _5;
        case KC_6: return _6;
        case KC_7: return _7;
        case KC_8: return _8;
        case KC_9: return _9;
        case KC_0: return _0;
        case KC_MINS: return HYPHEN;
        case KC_EQL: return EQUALS;
        case KC_BSPC: return BACKSPACE;
        case KC_INS: return INSERT;
        case KC_HOME: return HOME;
        case KC_PGUP: return PAGEUP;
        case KC_TAB: return TAB;
        case KC_Q: return Q;
        case KC_W: return W;
        case KC_E: return E;
        case KC_R: return R;
        case KC_T: return T;
        case KC_Y: return Y;
        case KC_U: return U;
        case KC_I: return I;
        case KC_O: return O;
        case KC_P: return P;
        case KC_LBRC: return LEFTBRACKET;
        case KC_RBRC: return RIGHTBRACKET;
        case KC_BSLS: return BACKSLASH;
        case KC_DEL: return DELETE;
        case KC_END: return LED_INDEX_END;
        case KC_PGDN: return PAGEDOWN;
        case KC_A: return A;
        case KC_S: return S;
        case KC_D: return D;
        case KC_F: return F;
        case KC_G: return G;
        case KC_H: return H;
        case KC_J: return J;
        case KC_K: return K;
        case KC_L: return L;
        case KC_SCLN: return SEMICOLON;
        case KC_QUOT: return QUOTE;
        case KC_ENT: return ENTER;
        case KC_LSFT: return LSHIFT;
        case KC_Z: return Z;
        case KC_X: return X;
        case KC_C: return C;
        case KC_V: return V;
        case KC_B: return B;
        case KC_N: return N;
        case KC_M: return M;
        case KC_COMM: return COMMA;
        case KC_DOT: return PERIOD;
        case KC_SLSH: return SLASH;
        case KC_RSFT: return RSHIFT;
        case KC_UP: return UP;
        case KC_LCTL: return LCTRL;
        case KC_LGUI: return LGUI;
        case KC_LALT: return LALT;
        case KC_SPC: return SPACE;
        case KC_RALT: return RALT;
        case KC_RCTL: return RCTRL;
        case KC_LEFT: return LEFT;
        case KC_DOWN: return DOWN;
        case KC_RGHT: return RIGHT;
        default:
            return 0;
    }
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,             KC_PSCR, _______, BOOT, \
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,   KC_INS,  KC_HOME, KC_PGUP, \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,   KC_DEL,  KC_END,  KC_PGDN, \
        _______, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT, \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                              KC_UP, \
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, MO(1),   _______, KC_RCTL,            KC_LEFT, KC_DOWN, KC_RGHT \
    ),
    [1] = LAYOUT( // command mode
        _______, LED_M0,  LED_M1,  LED_M2,  LED_M3,  _______, _______, _______, _______, DBG_TOG, DBG_MTX, DBG_KBD, DBG_MOU,            _______, _______, _______, \
        _______, CNF_1,   CNF_2,   CNF_3,   CNF_4,   CNF_5,   CNF_6,   CNF_7,   CNF_8,   CNF_9,   CNF_0,   _______, _______, _______,   _______, _______, _______, \
        _______, _______, _______, CNF_E,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, \
        _______, CNF_A,   _______, CNF_D,   CNF_F,   _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, CNF_C,   _______, CNF_B,   _______, _______, _______, _______, _______, _______,                              _______, \
        _______, _______, _______,                   _______,                            _______, _______, TGT_SET, _______,            _______, _______, _______ \
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

uint32_t last_keypress;

void matrix_init_user(void) {
    // this doesn't shut the LEDs off, it just sets it to a static color,
    // otherwise the default is the rotating RGB which I assume has some
    // hardware cost (which is always thrown away by what we do in
    // rgb_matrix_indicators_user anyway)
    rgb_matrix_mode(RGB_MATRIX_NONE);
    led_init_configs();
    last_keypress = timer_read32();
};

// runtime color config
uint8_t r = 0;
uint8_t g = 0xff;
uint8_t b = 0xff;

void matrix_scan_user(void) {
    if (stored_led_mode == -1 && timer_elapsed32(last_keypress) > TIMEOUT)
        led_sleep();
};

void raw_hid_receive(uint8_t* data, uint8_t length)
{
    last_keypress = timer_read32();
    if (stored_led_mode != -1)
        led_wake();
}

uint32_t runtime_color_configval = 0;
uint32_t runtime_color_configpos = 0;

uint8_t led_mode = 1;

bool needs_target = false;
int led_target = -1;

void handle_runtime_color_config(uint16_t keycode) {
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

        if (led_target == -1)
        {
            r = _r; g = _g; b = _b;
        }
        else
        {
            led_config_enable(led_target, _r, _g, _b);
            led_target = -1;
        }

        runtime_color_configval = 0;
        runtime_color_configpos = 0;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    last_keypress = timer_read32();
    if (stored_led_mode != -1)
        led_wake();

    if (needs_target && record->event.pressed)
    {
        needs_target = false;
        led_target = keycode_to_led(keycode);
        return false;
    }

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
            if (record->event.pressed)
                led_mode = keycode - LED_M0;
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
            if (record->event.pressed)
                handle_runtime_color_config(keycode);
            return false;
        case TGT_SET:
            if (record->event.pressed)
                needs_target = true;
            return false;
        default:
            return true;
    }
}

#define CONFIG r, g, b
#define OFF 0, 0, 0

#define LED_MODE_ALL       0
#define LED_MODE_KEYS      1
#define LED_MODE_UNDERGLOW 2
#define LED_MODE_OFF       3

typedef struct
{
    bool enabled;

    uint8_t r;
    uint8_t g;
    uint8_t b;
} _led_config_t;

_led_config_t led_configs[DRIVER_LED_TOTAL];

void led_config_enable(int index, uint8_t r, uint8_t g, uint8_t b)
{
    led_configs[index].enabled = true;
    led_configs[index].r = r;
    led_configs[index].g = g;
    led_configs[index].b = b;
}

void led_init_configs()
{
    led_config_enable(CAPSLOCK, OFF);
    led_config_enable(SCROLLLOCK, OFF);
    led_config_enable(PAUSE, OFF);
    led_config_enable(RGUI, OFF);
    led_config_enable(ESC, RGB_WHITE);
    led_config_enable(TAB, RGB_WHITE);
    led_config_enable(LSHIFT, RGB_WHITE);
    led_config_enable(LCTRL, RGB_WHITE);
    led_config_enable(LGUI, RGB_WHITE);
    led_config_enable(LALT, RGB_WHITE);
    led_config_enable(RALT, RGB_WHITE);
    led_config_enable(FN, RGB_WHITE);
    led_config_enable(RCTRL, RGB_WHITE);
    led_config_enable(RSHIFT, RGB_WHITE);
    led_config_enable(ENTER, RGB_WHITE);
    led_config_enable(BACKSPACE, RGB_WHITE);
    led_config_enable(F5, RGB_WHITE);
    led_config_enable(F6, RGB_WHITE);
    led_config_enable(F7, RGB_WHITE);
    led_config_enable(F8, RGB_WHITE);
    led_config_enable(INSERT, RGB_WHITE);
    led_config_enable(HOME, RGB_WHITE);
    led_config_enable(PAGEUP, RGB_WHITE);
    led_config_enable(DELETE, RGB_WHITE);
    led_config_enable(PAGEDOWN, RGB_WHITE);
    led_config_enable(UP, RGB_WHITE);
    led_config_enable(DOWN, RGB_WHITE);
    led_config_enable(LEFT, RGB_WHITE);
    led_config_enable(RIGHT, RGB_WHITE);
    led_config_enable(PRINTSCREEN, RGB_WHITE);
    led_config_enable(LED_INDEX_END, RGB_WHITE);

#define _purp 0xff, 0x40, 0xff

    led_config_enable(_1, _purp);
    led_config_enable(_2, _purp);
    led_config_enable(_3, _purp);
    led_config_enable(_4, _purp);
    led_config_enable(_5, _purp);
    led_config_enable(_6, _purp);
    led_config_enable(_7, _purp);
    led_config_enable(_8, _purp);
    led_config_enable(_9, _purp);
    led_config_enable(_0, _purp);

    led_config_enable(ESC, RGB_GREEN);
    led_config_enable(SEMICOLON, RGB_GREEN);

#define _crysis 0, 0xff, 0x40

    led_config_enable(H, _crysis);
    led_config_enable(J, _crysis);
    led_config_enable(K, _crysis);
    led_config_enable(L, _crysis);
}

void led_config_disable(int index)
{
    led_configs[index].enabled = false;
}

void rgb_set_keys(uint8_t r, uint8_t g, uint8_t b)
{
    for (int i = 0; i < DRIVER_LED_UNDERGLOW_START; ++i)
        rgb_matrix_set_color(i, r, g, b);
}

void rgb_set_underglow(uint8_t r, uint8_t g, uint8_t b)
{
    for (int i = DRIVER_LED_UNDERGLOW_START; i < DRIVER_LED_TOTAL; ++i)
        rgb_matrix_set_color(i, r, g, b);
}

void rgb_apply_config(int min, int max_exclusive)
{
    for (int i = min; i < max_exclusive; ++i)
        if (led_configs[i].enabled)
            rgb_matrix_set_color(i, led_configs[i].r, led_configs[i].g, led_configs[i].b);
}

void rgb_matrix_indicators_user(void)
{
    if (led_mode == LED_MODE_ALL || led_mode == LED_MODE_KEYS)
    {
        rgb_set_keys(CONFIG);
        rgb_apply_config(0, DRIVER_LED_UNDERGLOW_START);
    }
    else
        rgb_set_keys(OFF);
    if (led_mode == LED_MODE_ALL || led_mode == LED_MODE_UNDERGLOW)
    {
        rgb_set_underglow(CONFIG);
        rgb_apply_config(DRIVER_LED_UNDERGLOW_START, DRIVER_LED_TOTAL);
    }
    else
        rgb_set_underglow(OFF);
}

void led_sleep()
{
    stored_led_mode = led_mode;
    led_mode = LED_MODE_OFF;
}

void led_wake()
{
    led_mode = stored_led_mode;
    stored_led_mode = -1;
}
