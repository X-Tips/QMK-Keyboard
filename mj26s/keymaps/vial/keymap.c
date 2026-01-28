#include QMK_KEYBOARD_H
#include "leds.c"
#include "timer.h"
#include "eeconfig.h"

static uint8_t saved_default_layer = 0;
#define EEPROM_DEFAULT_LAYER_ADDR ((uint8_t*)10)

static uint32_t boot_time = 0;
static bool boot_window = true;

void keyboard_post_init_user(void) {
    boot_time = timer_read32();
    
    saved_default_layer = eeprom_read_byte(EEPROM_DEFAULT_LAYER_ADDR);
    
    if (saved_default_layer > 1) {
        saved_default_layer = 0;
        eeprom_update_byte(EEPROM_DEFAULT_LAYER_ADDR, saved_default_layer);
    }
    
    default_layer_set(1UL << saved_default_layer);
    layer_move(saved_default_layer);
}

void matrix_scan_user(void) {
    if (boot_window && timer_elapsed32(boot_time) > 2000) {
        boot_window = false;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (boot_window && record->event.pressed) {
        if (!readPin(B5)) {
            rgblight_toggle();
        }
        
        if (!readPin(B3)) {
            saved_default_layer = (saved_default_layer == 0) ? 1 : 0;
            eeprom_update_byte(EEPROM_DEFAULT_LAYER_ADDR, saved_default_layer);
            default_layer_set(1UL << saved_default_layer);
            layer_move(saved_default_layer);
        }
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_A,    KC_B,    KC_C,    KC_D,    KC_E,    KC_F,    KC_G,    KC_H,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,
        KC_5,    KC_1,    KC_3,    KC_ENT,  KC_RSFT, KC_BSPC, KC_RCTL, KC_LCTL, KC_LALT, KC_SPC,  KC_LSFT, KC_Z,    KC_N
    ),
    
    [1] = LAYOUT(
        KC_A,    KC_B,    KC_C,    KC_D,    KC_E,    KC_F,    KC_G,    KC_H,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,
        KC_P5,   KC_P1,   KC_P3,   KC_ENT,  KC_RSFT, KC_BSPC, KC_RCTL, KC_LCTL, KC_LALT, KC_SPC,  KC_LSFT, KC_Z,    KC_N
    ),
    
    [2] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ),
    
    [3] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ),
    
    [4] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ),
    
    [5] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ),
    
    [6] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ),
    
    [7] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ),
    
    [8] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    )
};