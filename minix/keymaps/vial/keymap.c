#include QMK_KEYBOARD_H
#include <stdio.h>
#include "leds.c"

enum custom_keycodes {   //must be declared before keymaps[] array
    CUT2HOME = SAFE_RANGE,
    CUT2END,
    CUTLINE,
    XTIPS,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT( //Alphabet
		LT(6, KC_Q), KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, 
		KC_A, KC_S, KC_D, LT(3, KC_F), LT(5, KC_G), KC_H, LT(4, KC_J), KC_K, KC_L, KC_ENT, 
		LCTL_T(KC_Z), LGUI_T(KC_X), LALT_T(KC_C), LT(1, KC_V), LSFT_T(KC_B), RSFT_T(KC_N), LT(2, KC_M), RALT_T(KC_SPC), RGUI_T(KC_DEL), RCTL_T(KC_BSPC)), 

	[1] = LAYOUT( //Numpad and Punctuation
		KC_7, KC_8, KC_9, KC_PDOT, KC_PLUS, KC_ASTR, KC_DLR, KC_COLN, KC_PIPE, KC_GRV, 
		KC_4, KC_5, KC_6, KC_0, KC_MINS, KC_SLSH, KC_HASH, KC_LCBR, KC_RCBR, KC_SCLN, 
		KC_1, KC_2, KC_3, TO(0), KC_PENT, KC_CAPS, LGUI(KC_SPC), KC_COMM, KC_DOT, CUT2END),

	[2] = LAYOUT( //Punctuation and Arrow key
		KC_TILD, KC_PERC, KC_UNDS, KC_CIRC, KC_LABK, KC_RABK, KC_HOME, KC_UP, KC_END, KC_PGUP, 
		KC_AT, KC_DQUO, KC_EXLM, KC_QUES, KC_LPRN, KC_RPRN, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, 
		LCTL_T(KC_LBRC), LGUI_T(KC_RBRC), LALT_T(KC_QUOT), KC_AMPR, LSFT_T(KC_EQL), KC_BSLS, TO(0), KC_ESC, KC_TAB, CUT2HOME), 

	[3] = LAYOUT( //Hotkeys
		LALT(KC_F4), LCTL(KC_W), LCTL(KC_T), LCTL(KC_R), LCTL(KC_X), LCTL(KC_Y), LGUI(KC_EQL), LGUI(KC_UP), LCTL(KC_PLUS), LCAG(KC_8), 
		LALT(KC_TAB), RCS(KC_TAB), LCTL(KC_TAB), TO(0), LCTL(KC_V), MEH(KC_SLSH), LGUI(KC_ESC), LGUI(KC_RGHT), LCTL(KC_0), LCAG(KC_9), 
		LALT(KC_HOME), LALT(KC_LEFT), LALT(KC_RGHT), RCS(KC_O), LCTL(KC_C), LCTL(KC_Z), LGUI(KC_MINS), LGUI(KC_DOWN), LCTL(KC_MINS), LCAG(KC_0)),

	[4] = LAYOUT( //Fn & Mouse & Media
		KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_MS_WH_UP, KC_MS_BTN1, KC_MS_UP, KC_MS_BTN2, 
		KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, TO(0), KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT,  
		KC_LCTL, KC_LGUI, KC_LALT, RCS(KC_X), KC_LSFT, KC_RSFT, KC_MS_WH_DOWN, KC_MS_BTN4, KC_MS_BTN5, KC_MS_BTN3),
		
	[5] = LAYOUT( //Media & LCEDA
		LCAG(KC_Q), LCAG(KC_W), MEH(KC_EQL), KC_VOLU, KC_MPRV, LCAG(KC_Y), LCAG(KC_U), LCAG(KC_I), LCAG(KC_O), LCAG(KC_P), 
		LCAG(KC_A), LCAG(KC_S), KC_MUTE, KC_MPLY, TO(0), LCAG(KC_H), LCAG(KC_J), LCAG(KC_K), LCAG(KC_L), LCAG(KC_ENT),  
		LCAG(KC_Z), LCAG(KC_X), MEH(KC_MINS), KC_VOLD, KC_MNXT, LCAG(KC_N), LCAG(KC_M), LCAG(KC_COMM), LCAG(KC_DOT), LCAG(KC_BSPC)),

	[6] = LAYOUT( //Software hotkeys
		TO(0), MEH(KC_W), MEH(KC_E), MEH(KC_R), MEH(KC_T), MEH(KC_Y), MEH(KC_U), MEH(KC_I), MEH(KC_O), MEH(KC_P), 
		MEH(KC_A), MEH(KC_S), MEH(KC_D), MEH(KC_F), MEH(KC_G), MEH(KC_H), MEH(KC_J), MEH(KC_K), MEH(KC_L), MEH(KC_ENT), 
		RGB_TOG, MEH(KC_X), MEH(KC_C), MEH(KC_V), MEH(KC_B), MEH(KC_N), MEH(KC_M), MEH(KC_COMM), MEH(KC_BSPC), MO(7)),

	[7] = LAYOUT( //KB Bootkey & Sys Reboot,Shutdown & Others
		HYPR(KC_Q), HYPR(KC_W), HYPR(KC_E), HYPR(KC_R), HYPR(KC_T), HYPR(KC_Y), HYPR(KC_U), HYPR(KC_I), HYPR(KC_O), HYPR(KC_P), 
		HYPR(KC_A), HYPR(KC_S), HYPR(KC_D), HYPR(KC_F), HYPR(KC_G), HYPR(KC_H), HYPR(KC_J), HYPR(KC_K), HYPR(KC_L), QK_BOOT, 
		HYPR(KC_Z), HYPR(KC_X), HYPR(KC_C), HYPR(KC_V), HYPR(KC_B), HYPR(KC_N), HYPR(KC_M), MEH(KC_LBRC), MEH(KC_RBRC), TO(0))
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case CUT2HOME:
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LSFT) SS_TAP(X_HOME) SS_UP(X_LSFT) SS_RCTL("c") SS_TAP(X_BSPC));
        }
        break;
    case CUT2END:
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LSFT) SS_TAP(X_END) SS_UP(X_LSFT) SS_RCTL("c") SS_TAP(X_DEL));
        }
        break;
    case CUTLINE:
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_HOME) SS_DOWN(X_LSFT) SS_TAP(X_END) SS_TAP(X_RIGHT) SS_UP(X_LSFT) SS_RCTL("c") SS_TAP(X_DEL));
        }
        break;
    case XTIPS:
        if (record->event.pressed) {
            SEND_STRING("X.Tips");
        }
        break;
    }
    return true;
};
