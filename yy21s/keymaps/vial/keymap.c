#include QMK_KEYBOARD_H
#include "leds.c"

#include "timer.h"

static uint32_t boot_time = 0;
static bool boot_window = true;
static uint8_t pending_layer = 0xFF;

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
        if (!readPin(B4)) {
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
        if (!readPin(A15)) {
		        pending_layer = 1;
		        default_layer_set(1UL << pending_layer);
		        eeconfig_update_default_layer(default_layer_state);
            layer_move(pending_layer);
		        return false;
		    }
        
        if (!readPin(A0)) {
		        pending_layer = 2;
		        default_layer_set(1UL << pending_layer);
		        eeconfig_update_default_layer(default_layer_state);
            layer_move(pending_layer);
		        return false;
		    }
*/        
        #ifdef NKRO_ENABLE
        if (!readPin(B5)) { 
            keymap_config.nkro = false;
            eeconfig_update_keymap(keymap_config.raw);
        }
        else if (!readPin(A2)) { 
            keymap_config.nkro = true;
            eeconfig_update_keymap(keymap_config.raw);
        }
        #endif
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
		KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U,
		KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J,
		KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M),

	[1] = LAYOUT(
		KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U,
		KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J,
		KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M),

	[2] = LAYOUT(
		KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U,
		KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J,
		KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M),

	[3] = LAYOUT(
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),

	[4] = LAYOUT(
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),

	[5] = LAYOUT(
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),

	[6] = LAYOUT(
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),

	[7] = LAYOUT(
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),

	[8] = LAYOUT(
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX)
};