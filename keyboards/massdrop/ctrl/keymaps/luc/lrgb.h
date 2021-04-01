#include QMK_KEYBOARD_H

#define DRIVER_LED_UNDERGLOW_START 87
#define STATUS_LED_BOOT DRIVER_LED_UNDERGLOW_START + 1
#define STATUS_LED_CONFIG_START DRIVER_LED_UNDERGLOW_START + 11

typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} lrgb_group_config;

#define LRGB_GROUP_INIT(_r, _g, _b) { .r = _r, .g = _g, .b = _b }

#define LRGB_GROUP_EXPAND(x) x.r, x.g, x.b

#define LRGB_GROUP_EXPAND_HEAP(x) x->r, x->g, x->b

void lrgb_group_config_set(lrgb_group_config *cfg, uint8_t r, uint8_t g, uint8_t b);

void lrgb_set_keys_grey(uint8_t r, uint8_t g, uint8_t b);

void lrgb_set_keys_vim(uint8_t r, uint8_t g, uint8_t b);

void lrgb_set_keys_black(uint8_t r, uint8_t g, uint8_t b);

void lrgb_set_underglow_back(uint8_t r, uint8_t g, uint8_t b);

void lrgb_set_underglow_status(int runtime_color_configpos);
