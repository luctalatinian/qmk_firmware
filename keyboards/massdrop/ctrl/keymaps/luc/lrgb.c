#include QMK_KEYBOARD_H

#include "lled.h"
#include "lrgb.h"

void lrgb_set_keys_grey(uint8_t r, uint8_t g, uint8_t b)
{
    rgb_matrix_set_color(LLI_F1, r, g, b);
    rgb_matrix_set_color(LLI_F2, r, g, b);
    rgb_matrix_set_color(LLI_F3, r, g, b);
    rgb_matrix_set_color(LLI_F4, r, g, b);

    rgb_matrix_set_color(LLI_F9, r, g, b);
    rgb_matrix_set_color(LLI_F10, r, g, b);
    rgb_matrix_set_color(LLI_F11, r, g, b);
    rgb_matrix_set_color(LLI_F12, r, g, b);

    rgb_matrix_set_color(LLI_1, r, g, b);
    rgb_matrix_set_color(LLI_2, r, g, b);
    rgb_matrix_set_color(LLI_3, r, g, b);
    rgb_matrix_set_color(LLI_4, r, g, b);
    rgb_matrix_set_color(LLI_5, r, g, b);
    rgb_matrix_set_color(LLI_6, r, g, b);
    rgb_matrix_set_color(LLI_7, r, g, b);
    rgb_matrix_set_color(LLI_8, r, g, b);
    rgb_matrix_set_color(LLI_9, r, g, b);
    rgb_matrix_set_color(LLI_0, r, g, b);

    rgb_matrix_set_color(LLI_BACKTICK, r, g, b);
    rgb_matrix_set_color(LLI_HYPHEN, r, g, b);
    rgb_matrix_set_color(LLI_EQUALS, r, g, b);

    rgb_matrix_set_color(LLI_A, r, g, b);
    rgb_matrix_set_color(LLI_B, r, g, b);
    rgb_matrix_set_color(LLI_C, r, g, b);
    rgb_matrix_set_color(LLI_D, r, g, b);
    rgb_matrix_set_color(LLI_E, r, g, b);
    rgb_matrix_set_color(LLI_F, r, g, b);
    rgb_matrix_set_color(LLI_G, r, g, b);
    rgb_matrix_set_color(LLI_I, r, g, b);
    rgb_matrix_set_color(LLI_M, r, g, b);
    rgb_matrix_set_color(LLI_N, r, g, b);
    rgb_matrix_set_color(LLI_O, r, g, b);
    rgb_matrix_set_color(LLI_P, r, g, b);
    rgb_matrix_set_color(LLI_Q, r, g, b);
    rgb_matrix_set_color(LLI_R, r, g, b);
    rgb_matrix_set_color(LLI_S, r, g, b);
    rgb_matrix_set_color(LLI_T, r, g, b);
    rgb_matrix_set_color(LLI_U, r, g, b);
    rgb_matrix_set_color(LLI_V, r, g, b);
    rgb_matrix_set_color(LLI_W, r, g, b);
    rgb_matrix_set_color(LLI_X, r, g, b);
    rgb_matrix_set_color(LLI_Y, r, g, b);
    rgb_matrix_set_color(LLI_Z, r, g, b);

    rgb_matrix_set_color(LLI_LEFTBRACKET, r, g, b);
    rgb_matrix_set_color(LLI_RIGHTBRACKET, r, g, b);
    rgb_matrix_set_color(LLI_BACKSLASH, r, g, b);
    rgb_matrix_set_color(LLI_SEMICOLON, r, g, b);
    rgb_matrix_set_color(LLI_QUOTE, r, g, b);
    rgb_matrix_set_color(LLI_COMMA, r, g, b);
    rgb_matrix_set_color(LLI_PERIOD, r, g, b);
    rgb_matrix_set_color(LLI_SLASH, r, g, b);
    rgb_matrix_set_color(LLI_SPACE, r, g, b);
}

void lrgb_set_keys_vim(uint8_t r, uint8_t g, uint8_t b)
{
    rgb_matrix_set_color(LLI_H, r, g, b);
    rgb_matrix_set_color(LLI_J, r, g, b);
    rgb_matrix_set_color(LLI_K, r, g, b);
    rgb_matrix_set_color(LLI_L, r, g, b);
}

void lrgb_set_keys_black(uint8_t r, uint8_t g, uint8_t b)
{
    rgb_matrix_set_color(LLI_CAPSLOCK, r, g, b);
    rgb_matrix_set_color(LLI_SCROLLLOCK, r, g, b);
    rgb_matrix_set_color(LLI_PAUSE, r, g, b);
    rgb_matrix_set_color(LLI_RGUI, r, g, b);
    rgb_matrix_set_color(LLI_ESC, r, g, b);
    rgb_matrix_set_color(LLI_TAB, r, g, b);
    rgb_matrix_set_color(LLI_LSHIFT, r, g, b);
    rgb_matrix_set_color(LLI_LCTRL, r, g, b);
    rgb_matrix_set_color(LLI_LGUI, r, g, b);
    rgb_matrix_set_color(LLI_LALT, r, g, b);
    rgb_matrix_set_color(LLI_RALT, r, g, b);
    rgb_matrix_set_color(LLI_FN, r, g, b);
    rgb_matrix_set_color(LLI_RCTRL, r, g, b);
    rgb_matrix_set_color(LLI_RSHIFT, r, g, b);
    rgb_matrix_set_color(LLI_ENTER, r, g, b);
    rgb_matrix_set_color(LLI_BACKSPACE, r, g, b);
    rgb_matrix_set_color(LLI_F5, r, g, b);
    rgb_matrix_set_color(LLI_F6, r, g, b);
    rgb_matrix_set_color(LLI_F7, r, g, b);
    rgb_matrix_set_color(LLI_F8, r, g, b);
    rgb_matrix_set_color(LLI_INSERT, r, g, b);
    rgb_matrix_set_color(LLI_HOME, r, g, b);
    rgb_matrix_set_color(LLI_PAGEUP, r, g, b);
    rgb_matrix_set_color(LLI_DELETE, r, g, b);
    rgb_matrix_set_color(LLI_PAGEDOWN, r, g, b);
    rgb_matrix_set_color(LLI_UP, r, g, b);
    rgb_matrix_set_color(LLI_DOWN, r, g, b);
    rgb_matrix_set_color(LLI_LEFT, r, g, b);
    rgb_matrix_set_color(LLI_RIGHT, r, g, b);
    rgb_matrix_set_color(LLI_PRINTSCREEN, r, g, b);
    rgb_matrix_set_color(LLI_END, r, g, b);
}

void lrgb_set_underglow_back(uint8_t r, uint8_t g, uint8_t b)
{
    for (int i = DRIVER_LED_UNDERGLOW_START+13; i < DRIVER_LED_TOTAL; ++i)
        rgb_matrix_set_color(i, r, g, b);
}

void lrgb_set_underglow_status()
{
    for (int i = DRIVER_LED_UNDERGLOW_START; i < DRIVER_LED_UNDERGLOW_START+13; ++i)
        rgb_matrix_set_color(i, RGB_OFF);
}

