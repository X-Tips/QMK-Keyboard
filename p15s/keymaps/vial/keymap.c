#include QMK_KEYBOARD_H
#include "leds.c"

// Plug in keyboard, press top-right key within 2 seconds to toggle RGB light or NKRO.... 2025-12-26
#include "timer.h"

static uint32_t boot_time = 0;
static bool boot_window = true;
static uint8_t pending_layer = 0xFF;

void keyboard_pre_init_user(void) {
    setPinOutput(WS2812_DI_PIN);   // 设置数据线为输出模式
    writePinLow(WS2812_DI_PIN);    // 拉低电平
    wait_us(100);       // 保持拉低 100 微秒（远大于 50 微秒的复位要求）
}

void keyboard_post_init_user(void) {
	boot_time = timer_read32();
	
    if (!eeconfig_is_enabled()) {
        eeconfig_init();
        default_layer_set(1UL << 0);
        eeconfig_update_default_layer(default_layer_state);
    } else {
        default_layer_set(eeconfig_read_default_layer());
    }
    
    uint8_t default_layer = get_highest_layer(default_layer_state);
    layer_move(default_layer);
}

void matrix_scan_user(void) {
    if (boot_window && timer_elapsed32(boot_time) > 2000) {
        boot_window = false;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (boot_window && record->event.pressed) {
        if (!readPin(A15)) {
            rgblight_toggle();
        }
        
        if (!readPin(A14)) {
		        pending_layer = 0;
		        default_layer_set(1UL << pending_layer);
		        eeconfig_update_default_layer(default_layer_state);
            layer_move(pending_layer);
		        return false;
		    }
/*
        if (!readPin(B3)) {
		        pending_layer = 1;
		        default_layer_set(1UL << pending_layer);
		        eeconfig_update_default_layer(default_layer_state);
            layer_move(pending_layer);
		        return false;
		    }
        if (!readPin(C13)) {
		        pending_layer = 2;
		        default_layer_set(1UL << pending_layer);
		        eeconfig_update_default_layer(default_layer_state);
            layer_move(pending_layer);
		        return false;
		    }
*/        
        #ifdef NKRO_ENABLE
        if (!readPin(B4)) { 
            keymap_config.nkro = false;
            eeconfig_update_keymap(keymap_config.raw);
        }
        else if (!readPin(B5)) { 
            keymap_config.nkro = true;
            eeconfig_update_keymap(keymap_config.raw);
        }
        #endif
    }
    return true;
}
// End of RGB_Toggle, NKRO_ON, NKRO_OFF...

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
		KC_Y, KC_U, KC_I, KC_O, KC_P, RGB_TOG,
		KC_H, KC_J, KC_K, KC_L, KC_SCLN, XXXXXXX, 
		KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, XXXXXXX), 

	[1] = LAYOUT(
		KC_Y, KC_U, KC_I, KC_O, KC_P, RGB_TOG,
		KC_H, KC_J, KC_K, KC_L, KC_SCLN, XXXXXXX, 
		KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, XXXXXXX), 

	[2] = LAYOUT(
		KC_Y, KC_U, KC_I, KC_O, KC_P, RGB_TOG,
		KC_H, KC_J, KC_K, KC_L, KC_SCLN, XXXXXXX, 
		KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, XXXXXXX), 

	[3] = LAYOUT(
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX), 

	[4] = LAYOUT(
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX), 

	[5] = LAYOUT(
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX), 

	[6] = LAYOUT(
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX), 

	[7] = LAYOUT( 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX), 

	[8] = LAYOUT( 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX)
}; 
