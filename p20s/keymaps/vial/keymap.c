#include QMK_KEYBOARD_H
#include "leds.c"

// Plug in keyboard, press top-right key within 2 seconds to toggle RGB light or NKRO. 2025-12-26
#include "timer.h"

static uint32_t boot_time = 0;
static bool boot_window = true;

void keyboard_pre_init_user(void) {
    setPinOutput(WS2812_DI_PIN); writePinLow(WS2812_DI_PIN); wait_us(100); //复位引脚50以上，避免首灯异常亮绿
}

void keyboard_post_init_user(void) {
    boot_time = timer_read32();
}

void matrix_scan_user(void) {
    if (boot_window && timer_elapsed32(boot_time) > 2000) {
        boot_window = false;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (boot_window && record->event.pressed) {
        // if (keycode == KC_VOLU) {
        if (!readPin(A15)) {
            rgblight_toggle();
        }

		if (!readPin(A2)) {
			layer_move(8);
			rgblight_enable();
			return false;
		}

        #ifdef NKRO_ENABLE
        if (!readPin(B5)) {
            keymap_config.nkro = false;
            eeconfig_update_keymap(keymap_config.raw);
        }
        else if (!readPin(C14)) {
            keymap_config.nkro = true;
            eeconfig_update_keymap(keymap_config.raw);
        }
        #endif
    }
    return true;
}
// End of RGB_Toggle, NKRO_ON, NKRO_OFF

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
		TG(1), KC_F, LT(3, KC_E), KC_VOLD, KC_VOLU,
		KC_Y, KC_U, KC_I, KC_O, KC_P,
		KC_H, KC_J, KC_K, KC_L, KC_SCLN,
		KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH),

	[1] = LAYOUT(
		TG(1), KC_W, LT(3, KC_E), KC_MINS, KC_PLUS,
		KC_A, KC_S, KC_D, KC_Q, KC_ENT,
		KC_LSFT, KC_Z, KC_F, KC_UP, KC_TAB,
		KC_ESC, KC_SPC, KC_LEFT, KC_DOWN, KC_RGHT),

	[2] = LAYOUT(
		KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,
		KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,
		KC_6, KC_7, KC_8, KC_9, KC_0,
		KC_1, KC_2, KC_3, KC_4, KC_5),

	[3] = LAYOUT(
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, NK_OFF,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, NK_ON),

	[4] = LAYOUT(
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),

	[5] = LAYOUT(
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),

	[6] = LAYOUT(
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),

	[7] = LAYOUT(
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),

	[8] = LAYOUT(
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		RGB_RMOD, RM_ON,  RM_HUEU, RGB_SAI, RGB_VAI,
		TO(0),    RM_OFF, RM_HUED, RGB_SAD, RGB_VAD)
};
