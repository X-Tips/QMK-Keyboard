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
	  KC_1, KC_2, KC_3, KC_4, KC_5,                                             KC_6, KC_7, KC_8, KC_9, KC_0,  
		KC_Q, KC_W, KC_E, KC_R, KC_T,                                             KC_Y, KC_U, KC_I, KC_O, KC_P, 
		KC_A, KC_S, KC_D, KC_F, KC_G,                                             KC_H, KC_J, KC_K, KC_L, KC_ENT, 
		KC_Z, KC_X, KC_C, KC_V, KC_B,                                             KC_N, KC_M, LT(5, KC_COMM), LT(6, KC_DOT), KC_BSPC,
		LGUI_T(KC_DEL), LALT_T(KC_ESC), LCTL_T(KC_TAB), LT(1, KC_SPC), KC_LSFT,   KC_SPC, MO(2), LT(3, KC_TAB), LT(4, KC_ESC), KC_DEL), 

	[1] = LAYOUT( //Number & Punctuation
	  KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,                                        KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,  
		KC_7, KC_8, KC_9, KC_PDOT, KC_PPLS,                                       KC_PAST, KC_DLR, KC_COLN, KC_PIPE, KC_GRV, 
		KC_4, KC_5, KC_6, KC_0, KC_PMNS,                                          KC_PSLS, KC_HASH, KC_LCBR, KC_RCBR, KC_SCLN, 
		KC_1, KC_2, KC_3, KC_BSPC, KC_EQL,                                        KC_BSLS, KC_AMPR, KC_LABK, KC_RABK, KC_QUOT, 
		KC_LGUI, KC_LALT, KC_LCTL, TO(0), LSFT_T(KC_PENT),                        HYPR(KC_6), LGUI(KC_SPC), LAG(KC_8), LAG(KC_9), LAG(KC_0)),
                                                                              
	[2] = LAYOUT( //Punctuation & Arrow key                                     
	  KC_F11, KC_F12, XXXXXXX, XXXXXXX, XXXXXXX,                                XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   
		KC_TILD, KC_PERC, KC_UNDS, KC_CIRC, KC_PLUS,                              KC_ASTR, KC_HOME, KC_UP, KC_END, KC_PGUP, 
		KC_AT, KC_DQUO, KC_EXLM, KC_QUES, KC_MINS,                                KC_SLSH, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,
		KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN, KC_EQL,                               KC_BSLS, RSFT(KC_LEFT), RSFT(KC_UP), RSFT(KC_RGHT), CUT2HOME, 
		KC_RGUI, KC_LALT, KC_RCTL, KC_CAPS, KC_RSFT,                              MEH(KC_SLSH), TO(0), RSFT(KC_DOWN), CUTLINE, CUT2END),
                                                                              
	[3] = LAYOUT( //L:Quickly input -- R:Mouse & Webbrower Hotkeys              
	  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                              XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   
		HYPR(KC_Q), HYPR(KC_W), HYPR(KC_E), HYPR(KC_R), HYPR(KC_T),               LALT(KC_F4), LALT(KC_TAB), KC_MS_BTN1, KC_MS_UP, KC_MS_BTN2,  
		HYPR(KC_A), HYPR(KC_S), HYPR(KC_D), HYPR(KC_F), HYPR(KC_G),               LCTL(KC_W), LCTL(KC_T), KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, 
		HYPR(KC_Z), HYPR(KC_X), HYPR(KC_C), HYPR(KC_V), HYPR(KC_B),               RCS(KC_TAB), LCTL(KC_TAB), KC_MS_BTN4, KC_MS_BTN5, KC_MS_WH_UP, 
		HYPR(KC_1), HYPR(KC_2), HYPR(KC_3), HYPR(KC_4), HYPR(KC_5),               LALT(KC_HOME), LCTL(KC_R), TO(0), KC_MS_BTN3, KC_MS_WH_DOWN),
                                                                              
	[4] = LAYOUT( //Fn & Quickly Open File                                      
	  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                              XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   
		LCAG(KC_Q), KC_F21,  KC_F22,  KC_F23, KC_F24,                             KC_F9, KC_F10, KC_F11, KC_F12, LCAG(KC_P),  
		LCAG(KC_A), KC_F17,  KC_F18,  KC_F19, KC_F20,                             KC_F5, KC_F6, KC_F7, KC_F8, LCAG(KC_ENT), 
		LCAG(KC_Z), KC_F13,  KC_F14,  KC_F15, KC_F16,                             KC_F1, KC_F2, KC_F3, KC_F4, LCAG(KC_BSPC),  
		KC_RGUI,    KC_RALT, KC_RCTL, LCAG(KC_4), KC_RSFT,                        LCAG(KC_6), LCAG(KC_7), LCAG(KC_8), TO(0), XTIPS),
                                                                              
	[5] = LAYOUT( //L:Quickly input -- R:Music & Quickly operate                
	  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                              XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   
		RGB_HUI, RGB_MOD, RAG(KC_E), RAG(KC_R), RAG(KC_T),                        MEH(KC_MINS), MEH(KC_EQL), KC_INS, KC_APP, KC_NUM,
		RGB_SAI, RGB_SPI, RAG(KC_D), RAG(KC_F), RAG(KC_G),                        KC_VOLD, KC_VOLU, KC_PAUS, KC_PSCR, KC_SCRL,     
		RGB_VAI, RGB_TOG, RAG(KC_C), RAG(KC_V), RAG(KC_B),                        KC_MPRV, KC_MNXT, TO(0), RCS(KC_X), RCS(KC_O),
		KC_LGUI, KC_LALT, KC_LCTL, TT(8), KC_LSFT,                                KC_MUTE, KC_MPLY, MO(7), HYPR(KC_9), HYPR(KC_0)),
                                                                              
	[6] = LAYOUT( //App hotkeys                                                 
	  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                              XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   
		MEH(KC_Q), MEH(KC_W), MEH(KC_E), MEH(KC_R), MEH(KC_T),                    MEH(KC_Y), MEH(KC_U), MEH(KC_I), MEH(KC_O), MEH(KC_P), 
		MEH(KC_A), MEH(KC_S), MEH(KC_D), MEH(KC_F), MEH(KC_G),                    MEH(KC_H), MEH(KC_J), MEH(KC_K), MEH(KC_L), MEH(KC_ENT), 
		MEH(KC_Z), MEH(KC_X), MEH(KC_C), MEH(KC_V), MEH(KC_B),                    MEH(KC_N), MEH(KC_M), MEH(KC_COMM), TO(0), MEH(KC_BSPC), 
		MEH(KC_1), MEH(KC_2), MEH(KC_3), MEH(KC_4), MEH(KC_5),                    MEH(KC_6), MEH(KC_7), MEH(KC_8),MEH(KC_9), MEH(KC_0)),
                                                                              
	[7] = LAYOUT( //QK_BOOT, PC On/Off & Quickly input                          
	  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                              XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   
		LAG(KC_Q), LAG(KC_W), LAG(KC_E), LAG(KC_R), LAG(KC_T),                    LAG(KC_Y), LAG(KC_U), LAG(KC_I), LAG(KC_O), LAG(KC_P), 
		LAG(KC_A), LAG(KC_S), LAG(KC_D), LAG(KC_F), LAG(KC_G),                    LAG(KC_H), LAG(KC_J), LAG(KC_K), LAG(KC_L), LAG(KC_ENT), 
		LAG(KC_Z), LAG(KC_X), LAG(KC_C), LAG(KC_V), LAG(KC_B),                    LAG(KC_N), LAG(KC_M), LAG(KC_COMM), LAG(KC_DOT), LAG(KC_BSPC),  
		LAG(KC_1), LAG(KC_2), LAG(KC_3), LAG(KC_4), LAG(KC_5),                    LAG(KC_6), QK_BOOT, TO(0), MEH(KC_LBRC), MEH(KC_RBRC))
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

