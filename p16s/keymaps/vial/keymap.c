#include QMK_KEYBOARD_H
#include "leds.c"

enum custom_keycodes {   //must be declared before keymaps[] array
    KC_LRCBR = SAFE_RANGE,
    KC_LRBRC,
    KC_LRPRN,
};

// Plug in keyboard, press a key within 2 seconds to toggle RGB light or NKRO... 2025-12-26
#include "timer.h"

static uint32_t boot_time = 0;
static bool boot_window = true;

void keyboard_post_init_user(void) {
    boot_time = timer_read32();
}

void matrix_scan_user(void) {
    if (boot_window && timer_elapsed32(boot_time) > 2000) {
        boot_window = false;
    }
}
// End of RGB_Toggle or NKRO...

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
		KC_PPLS, KC_7,          KC_8, KC_9,
		KC_PMNS, KC_4,          KC_5, KC_6, 
		KC_PAST, KC_1,          KC_2, KC_3,
		KC_PSLS, LT(1, KC_ENT), KC_0, KC_PDOT), 

	[1] = LAYOUT(
		KC_LRCBR, KC_HOME, KC_UP,   KC_END, 
		KC_LRBRC, KC_LEFT, KC_EQL,  KC_RGHT, 
		KC_LRPRN, KC_PGUP, KC_DOWN, KC_PGDN, 
		KC_ESC,   TO(0),   KC_BSPC, KC_DEL), 

	[2] = LAYOUT(
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX), 

	[3] = LAYOUT(
		RGB_TOG, XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX), 

	[4] = LAYOUT(
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX), 

	[5] = LAYOUT(
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX), 

	[6] = LAYOUT(
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX), 

	[7] = LAYOUT( 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX), 

	[8] = LAYOUT( 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX)
}; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (boot_window && record->event.pressed) {  // RGB_Toggle, NKRO
        if (!readPin(A10)) {
            rgblight_toggle();
        }
        
        #ifdef NKRO_ENABLE
        if (!readPin(B5)) { 
            keymap_config.nkro = false;
            eeconfig_update_keymap(keymap_config.raw);
        }
        else if (!readPin(B7)) { 
            keymap_config.nkro = true;
            eeconfig_update_keymap(keymap_config.raw);
        }
        #endif
    }
    
    switch (keycode) {
    case KC_LRCBR:
        if (record->event.pressed) {
            SEND_STRING("{}" SS_TAP(X_LEFT));
        }
        break;
    case KC_LRBRC:
        if (record->event.pressed) {
            SEND_STRING("[]" SS_TAP(X_LEFT));
        }
        break;
    case KC_LRPRN:
        if (record->event.pressed) {
            SEND_STRING("()" SS_TAP(X_LEFT));
        }
        break;
    }
    return true;
}