#include QMK_KEYBOARD_H
#include "leds.c"

enum custom_keycodes {   //must be declared before keymaps[] array
    L_RBRC = SAFE_RANGE,
    L_RPRN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
		LT(5,KC_ESC), 	 KC_Q,    		    KC_W,             KC_E,           KC_R,          KC_T, 
		LT(4,KC_TAB), 	 KC_A,    		    KC_S,             KC_D,           KC_F,          KC_G, 
		LT(3,KC_DEL), 	 KC_Z,    		    KC_X,             KC_C,           KC_V,          KC_B, 
		LGUI_T(KC_QUOT), LALT_T(KC_SCLN), LSFT_T(KC_COMM),  LCTL_T(KC_DOT), LT(1, KC_SPC), LT(2, KC_ENT)), 

	[1] = LAYOUT( 
    L_RPRN,  KC_7,    KC_8,    KC_9,    KC_PDOT, KC_PLUS,
    L_RBRC,  KC_4,    KC_5,    KC_6,    KC_0,    KC_MINS,
    KC_PIPE, KC_1,    KC_2,    KC_3,    KC_BSPC, KC_PAST,
    KC_BSLS, KC_UNDS, KC_QUES, KC_EQL,  TO(0),   KC_SLSH),
    
	[2] = LAYOUT( 
		KC_MS_LEFT, KC_MS_UP,   KC_MS_RIGHT, KC_LEFT,       KC_UP,   KC_RGHT,     
		KC_MS_BTN1, KC_MS_DOWN, KC_MS_BTN2,  KC_MS_WH_UP,   KC_DOWN, KC_HOME, 
		KC_MS_BTN4, KC_MS_BTN5, KC_MS_BTN3,  KC_MS_WH_DOWN, KC_PGUP, KC_END, 
		KC_LGUI,    KC_LALT,    KC_LSFT,     KC_LCTL,       KC_PGDN, TO(0)), 

	[3] = LAYOUT( 
    G(KC_MINS), G(KC_EQL), KC_F9,   KC_F10,  KC_F11,  KC_F12,
    G(KC_LEFT), G(KC_RGHT),KC_F5,   KC_F6,   KC_F7,   KC_F8, 
    TO(0),      A(KC_F4),  KC_F1,   KC_F2,   KC_F3,   KC_F4, 
		KC_LGUI,    KC_LALT,   KC_LSFT, KC_LCTL, MO(6),   MO(7)), 

	[4] = LAYOUT( 
    KC_GRV,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    
    TO(0),   KC_H,    KC_J,    KC_K,    KC_L,    KC_DQUO, 
    KC_TILD, KC_N,    KC_M,    KC_LT,   KC_GT,   KC_COLN,
    KC_RGUI, KC_RALT, KC_RSFT, KC_RCTL, MO(8),   KC_CAPS),  

	[5] = LAYOUT( 
    TO(0),   KC_MPRV, KC_VOLU,      C(KC_PPLS), A(KC_RGHT), G(KC_PPLS), 
    TO(4),   KC_MPLY, KC_MUTE,      C(KC_0),    C(KC_W),    G(KC_ESC),    
    TO(3),   KC_MNXT, KC_VOLD,      C(KC_MINS), A(KC_LEFT), G(KC_MINS), 
		KC_CALC, KC_MSEL, C(S(KC_ESC)), G(KC_L),    TO(1),      TO(2)), 

	[6] = LAYOUT( 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX), 

	[7] = LAYOUT( 
		QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX), 

	[8] = LAYOUT( 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case L_RBRC:
        if (record->event.pressed) {
            SEND_STRING("[]" SS_TAP(X_LEFT));
        }
        break;
    case L_RPRN:
        if (record->event.pressed) {
            SEND_STRING("{}" SS_TAP(X_LEFT));
        }
        break;
    }
    return true;
};
