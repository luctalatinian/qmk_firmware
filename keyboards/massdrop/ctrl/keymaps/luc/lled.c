#include QMK_KEYBOARD_H

#include "lled.h"

lled_index lled_kctoi(uint16_t keycode)
{
    switch (keycode) {
        case KC_ESC: return LLI_ESC;
        case KC_F1: return LLI_F1;
        case KC_F2: return LLI_F2;
        case KC_F3: return LLI_F3;
        case KC_F4: return LLI_F4;
        case KC_F5: return LLI_F5;
        case KC_F6: return LLI_F6;
        case KC_F7: return LLI_F7;
        case KC_F8: return LLI_F8;
        case KC_F9: return LLI_F9;
        case KC_F10: return LLI_F10;
        case KC_F11: return LLI_F11;
        case KC_F12: return LLI_F12;
        case KC_PSCR: return LLI_PRINTSCREEN;
        case KC_GRV: return LLI_BACKTICK;
        case KC_1: return LLI_1;
        case KC_2: return LLI_2;
        case KC_3: return LLI_3;
        case KC_4: return LLI_4;
        case KC_5: return LLI_5;
        case KC_6: return LLI_6;
        case KC_7: return LLI_7;
        case KC_8: return LLI_8;
        case KC_9: return LLI_9;
        case KC_0: return LLI_0;
        case KC_MINS: return LLI_HYPHEN;
        case KC_EQL: return LLI_EQUALS;
        case KC_BSPC: return LLI_BACKSPACE;
        case KC_INS: return LLI_INSERT;
        case KC_HOME: return LLI_HOME;
        case KC_PGUP: return LLI_PAGEUP;
        case KC_TAB: return LLI_TAB;
        case KC_Q: return LLI_Q;
        case KC_W: return LLI_W;
        case KC_E: return LLI_E;
        case KC_R: return LLI_R;
        case KC_T: return LLI_T;
        case KC_Y: return LLI_Y;
        case KC_U: return LLI_U;
        case KC_I: return LLI_I;
        case KC_O: return LLI_O;
        case KC_P: return LLI_P;
        case KC_LBRC: return LLI_LEFTBRACKET;
        case KC_RBRC: return LLI_RIGHTBRACKET;
        case KC_BSLS: return LLI_BACKSLASH;
        case KC_DEL: return LLI_DELETE;
        case KC_END: return LLI_END;
        case KC_PGDN: return LLI_PAGEDOWN;
        case KC_A: return LLI_A;
        case KC_S: return LLI_S;
        case KC_D: return LLI_D;
        case KC_F: return LLI_F;
        case KC_G: return LLI_G;
        case KC_H: return LLI_H;
        case KC_J: return LLI_J;
        case KC_K: return LLI_K;
        case KC_L: return LLI_L;
        case KC_SCLN: return LLI_SEMICOLON;
        case KC_QUOT: return LLI_QUOTE;
        case KC_ENT: return LLI_ENTER;
        case KC_LSFT: return LLI_LSHIFT;
        case KC_Z: return LLI_Z;
        case KC_X: return LLI_X;
        case KC_C: return LLI_C;
        case KC_V: return LLI_V;
        case KC_B: return LLI_B;
        case KC_N: return LLI_N;
        case KC_M: return LLI_M;
        case KC_COMM: return LLI_COMMA;
        case KC_DOT: return LLI_PERIOD;
        case KC_SLSH: return LLI_SLASH;
        case KC_RSFT: return LLI_RSHIFT;
        case KC_UP: return LLI_UP;
        case KC_LCTL: return LLI_LCTRL;
        case KC_LGUI: return LLI_LGUI;
        case KC_LALT: return LLI_LALT;
        case KC_SPC: return LLI_SPACE;
        case KC_RALT: return LLI_RALT;
        case KC_RCTL: return LLI_RCTRL;
        case KC_LEFT: return LLI_LEFT;
        case KC_DOWN: return LLI_DOWN;
        case KC_RGHT: return LLI_RIGHT;
        default:
            return 0;
    }
}
