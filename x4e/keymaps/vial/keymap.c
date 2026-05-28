#include QMK_KEYBOARD_H
#include <stdio.h>
#include "leds.c"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT( //Alphabet
		KC_Q, KC_W, KC_E, KC_R, KC_T,                                             KC_Y, KC_U, KC_I, KC_O, KC_P, 
		KC_A, KC_S, KC_D, KC_F, KC_G,                                             KC_H, KC_J, KC_K, KC_L, KC_ENT, 
		KC_Z, KC_X, KC_C, KC_V, KC_B,                                             KC_N, KC_M, LT(5, KC_COMM), LT(6, KC_DOT), KC_BSPC,
		LGUI(KC_ESC), LT(3, KC_ESC), LCTL_T(KC_DEL), KC_LSFT, LT(1, KC_SPC), 			LT(2, KC_SPC), KC_LALT, LGUI(KC_DEL), LT(4, KC_TAB), KC_MPLY),

	[1] = LAYOUT( //Number & Punctuation
		KC_7, KC_8, KC_9, KC_PDOT, KC_PPLS,                                       KC_PAST, KC_DLR, KC_COLN, KC_PIPE, KC_GRV, 
		KC_4, KC_5, KC_6, KC_0, KC_PMNS,                                          KC_PSLS, KC_HASH, KC_LCBR, KC_RCBR, KC_SCLN, 
		KC_1, KC_2, KC_3, KC_BSPC, KC_EQL,                                        KC_BSLS, KC_AMPR, KC_LABK, KC_RABK, KC_QUOT, 
		LCTL(KC_0), KC_ESC, KC_RCTL, LSFT_T(KC_PENT), TO(0), 											LGUI(KC_SPC), KC_RALT, KC_RGUI, KC_TAB, KC_MUTE),
                                                                              
	[2] = LAYOUT( //Punctuation & Arrow key                                     
		KC_TILD, KC_PERC, KC_UNDS, KC_CIRC, KC_PLUS,                              KC_ASTR, KC_HOME, KC_UP, KC_END, KC_PGUP, 
		KC_AT, KC_DQUO, KC_EXLM, KC_QUES, KC_MINS,                                KC_SLSH, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,
		KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN, KC_EQL,                               KC_BSLS, RSFT(KC_LEFT), RSFT(KC_RGHT), RSFT(KC_UP), RSFT(KC_DOWN),  
		LCTL(KC_0), KC_ESC, KC_RCTL, KC_RSFT, KC_CAPS, 											      TO(0), KC_RALT, KC_RGUI, RSFT(KC_DOWN), KC_MUTE),
                                                                              
	[3] = LAYOUT( //L:Hotkeys -- R:Mouse             
		MEH(KC_Q), MEH(KC_W), MEH(KC_E), MEH(KC_R), MEH(KC_T),                    MEH(KC_Y), MEH(KC_U), KC_MS_BTN1, KC_MS_UP, KC_MS_BTN2,  
		MEH(KC_A), MEH(KC_S), MEH(KC_D), MEH(KC_F), MEH(KC_G),                    MEH(KC_H), MEH(KC_J), KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, 
		MEH(KC_Z), MEH(KC_X), MEH(KC_C), MEH(KC_V), MEH(KC_B),                    MEH(KC_N), MEH(KC_M), KC_MS_BTN4, KC_MS_WH_UP, KC_MS_BTN5, 
		XXXXXXX, TO(0), MEH(KC_3), MEH(KC_4), MEH(KC_5),                          MEH(KC_6), MEH(KC_7), KC_MS_BTN3, KC_MS_WH_DOWN, XXXXXXX),
                                                                              
	[4] = LAYOUT( //Fn                                       
		LCAG(KC_Q), KC_F21,  KC_F22,  KC_F23, KC_F24,                             KC_F9, KC_F10, KC_F11, KC_F12, LCAG(KC_P),  
		LCAG(KC_A), KC_F17,  KC_F18,  KC_F19, KC_F20,                             KC_F5, KC_F6, KC_F7, KC_F8, LCAG(KC_ENT), 
		LCAG(KC_Z), KC_F13,  KC_F14,  KC_F15, KC_F16,                             KC_F1, KC_F2, KC_F3, KC_F4, LCAG(KC_BSPC),  
		XXXXXXX, KC_ESC, KC_RCTL, KC_RSFT, KC_SPC, 											          KC_SPC, KC_RALT, KC_RGUI, TO(0), XXXXXXX),
                                                                              
	[5] = LAYOUT( // 
	  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 															XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
	  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 															XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
	  XXXXXXX, RGB_TOG, XXXXXXX, XXXXXXX, XXXXXXX, 															XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
	  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 															XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX), 
                                                                              
	[6] = LAYOUT( //                                                 
	  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 															XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
	  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 															XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
	  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 															XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
	  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 															XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX), 
                                                                              
	[7] = LAYOUT( //                          
	  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 															XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
	  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 															XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
	  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 															XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
	  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 															XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX), 
                                                                              
	[8] = LAYOUT( //                                                   
	  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 															XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
	  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 															XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
	  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 															XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
	  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 															XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX) 
}; 

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(LGUI(KC_MINS), LGUI(KC_EQL)), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(LCTL(KC_MINS), LCTL(KC_PLUS)), ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
    [2] = { ENCODER_CCW_CW(LCTL(KC_MINS), LCTL(KC_PLUS)), ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
    [3] = { ENCODER_CCW_CW(KC_UP, KC_DOWN), ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
    [4] = { ENCODER_CCW_CW(KC_UP, KC_DOWN), ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
    [5] = { ENCODER_CCW_CW(KC_UP, KC_DOWN), ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
    [6] = { ENCODER_CCW_CW(KC_UP, KC_DOWN), ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
    [7] = { ENCODER_CCW_CW(KC_UP, KC_DOWN), ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
    [8] = { ENCODER_CCW_CW(KC_UP, KC_DOWN), ENCODER_CCW_CW(KC_LEFT, KC_RGHT) }
};
#endif
