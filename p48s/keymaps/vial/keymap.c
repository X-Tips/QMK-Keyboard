#include QMK_KEYBOARD_H
#include "leds.c"

enum custom_keycodes {   //must be declared before keymaps[] array
    CUT2HOME = SAFE_RANGE,
    CUT2END,
    CUTLINE,
    XTIPS,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT( //Alphabet
		KC_Q, KC_W, KC_E, KC_R, KC_T,                              						    KC_VOLD, KC_VOLU,               KC_Y, KC_U, KC_I, KC_O, KC_P, 
		KC_A, KC_S, KC_D, KC_F, KC_G,                              						    KC_MPLY, KC_MNXT,               KC_H, KC_J, KC_K, KC_L, KC_ENT, 
		KC_Z, KC_X, KC_C, KC_V, KC_B,                              						    LCTL(KC_V), LCTL(KC_Z),         KC_N, KC_M, LT(5, KC_COMM), LT(6, KC_DOT), KC_BSPC,
		LGUI_T(KC_DEL), LALT_T(KC_ESC), LCTL_T(KC_TAB), LT(1, KC_SPC), KC_LSFT,   LCTL(KC_C), LCTL(KC_X),         KC_SPC, MO(2), LT(3, KC_TAB), LT(4, KC_ESC), KC_DEL), 

	[1] = LAYOUT( //Number & Punctuation
		KC_7, KC_8, KC_9, KC_PDOT, KC_PPLS,                         					    HYPR(KC_VOLD), HYPR(KC_VOLU),   KC_PAST, KC_DLR, KC_COLN, KC_PIPE, KC_GRV, 
		KC_4, KC_5, KC_6, KC_0, KC_PMNS,                            					    HYPR(KC_MPLY), HYPR(KC_MNXT),   KC_PSLS, KC_HASH, KC_LCBR, KC_RCBR, KC_SCLN, 
		KC_1, KC_2, KC_3, KC_BSPC,KC_EQL,                         					      LGUI(KC_MINS), LGUI(KC_EQL),    KC_BSLS, KC_AMPR, KC_LABK, KC_RABK, KC_QUOT, 
		KC_RGUI, KC_LALT, KC_RCTL, TO(0), LSFT_T(KC_PENT),                        LGUI(KC_ESC), LGUI(KC_ESC),     RAG(KC_6), LGUI(KC_SPC), RAG(KC_8), RAG(KC_9), RAG(KC_0)),
                                                                              
	[2] = LAYOUT( //Punctuation & Arrow key                                     
		KC_TILD, KC_PERC, KC_UNDS, KC_CIRC, KC_PLUS,                					    MEH(KC_VOLD), MEH(KC_VOLU),     KC_ASTR, KC_HOME, KC_UP, KC_END, KC_PGUP, 
		KC_AT, KC_DQUO, KC_EXLM, KC_QUES, KC_MINS,                  					    MEH(KC_MPLY), MEH(KC_MNXT),     KC_SLSH, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,
		KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN, KC_EQL,                 					    LCTL(KC_MINS), LCTL(KC_PLUS),   KC_BSLS, RSFT(KC_LEFT), RSFT(KC_UP), RSFT(KC_RGHT), CUT2HOME, 
		KC_RGUI, KC_LALT, KC_RCTL, KC_CAPS, KC_RSFT,                					    LCTL(KC_0), LCTL(KC_0),         MEH(KC_SLSH), TO(0), RSFT(KC_DOWN), CUTLINE, CUT2END),
                                                                              
	[3] = LAYOUT( //L:Quickly input -- R:Mouse & Webbrower Hotkeys              
		HYPR(KC_Q), HYPR(KC_W), HYPR(KC_E), HYPR(KC_R), HYPR(KC_T), 					    HYPR(KC_HOME), HYPR(KC_END),    HYPR(KC_Y), HYPR(KC_U), KC_MS_BTN1, KC_MS_UP, KC_MS_BTN2,  
		HYPR(KC_A), HYPR(KC_S), HYPR(KC_D), HYPR(KC_F), HYPR(KC_G), 					    HYPR(KC_PGUP), HYPR(KC_PGDN),   HYPR(KC_H), HYPR(KC_J), KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, 
		HYPR(KC_Z), HYPR(KC_X), HYPR(KC_C), HYPR(KC_V), HYPR(KC_B), 					    LGUI(KC_DOWN), LGUI(KC_UP),     HYPR(KC_N), HYPR(KC_M), KC_MS_BTN4, KC_MS_BTN5, KC_MS_WH_UP, 
		HYPR(KC_1), HYPR(KC_2), HYPR(KC_3), HYPR(KC_4), HYPR(KC_5), 					    LGUI(KC_LEFT), LGUI(KC_RGHT),   HYPR(KC_6), HYPR(KC_7), TO(0), KC_MS_BTN3, KC_MS_WH_DOWN),
                                                                              
	[4] = LAYOUT( //Fn & Quickly Open File                                      
		KC_F21,  KC_F22,  KC_F23, KC_F24, LCAG(KC_Q),                             LCAG(KC_HOME), LCAG(KC_END),    LCAG(KC_P), KC_F9, KC_F10, KC_F11, KC_F12,  
		KC_F17,  KC_F18,  KC_F19, KC_F20, LCAG(KC_A),                             LCAG(KC_PGUP), LCAG(KC_PGDN),   LCAG(KC_ENT),  KC_F5, KC_F6, KC_F7, KC_F8, 
		KC_F13,  KC_F14,  KC_F15, KC_F16, LCAG(KC_Z),                             LCAG(KC_DOWN), LCAG(KC_UP),     LCAG(KC_BSPC), KC_F1, KC_F2, KC_F3, KC_F4,  
		KC_RGUI,    KC_RALT, KC_RCTL, LCAG(KC_4), KC_RSFT,                        LCAG(KC_LEFT), LCAG(KC_RGHT),   LCAG(KC_6), LCAG(KC_7), LCAG(KC_8), TO(0), XTIPS),
                                                                              
	[5] = LAYOUT( //L:Quickly input -- R:Music & Quickly operate                
		RGB_HUI, RGB_MOD, RAG(KC_E), RAG(KC_R), RAG(KC_T),                        RAG(KC_HOME), RAG(KC_END),      MEH(KC_MINS), MEH(KC_EQL), KC_INS, KC_APP, KC_NUM,
		RGB_SAI, RGB_SPI, RAG(KC_D), RAG(KC_F), RAG(KC_G),                        RAG(KC_PGUP), RAG(KC_PGDN),     KC_VOLD, KC_VOLU, KC_PAUS, KC_PSCR, KC_SCRL,     
		RGB_VAI, RGB_TOG, RAG(KC_C), RAG(KC_V), RAG(KC_B),                        RAG(KC_DOWN), RAG(KC_UP),       KC_MPRV, KC_MNXT, TO(0), RCS(KC_X), RCS(KC_O),
		KC_LGUI, KC_LALT, KC_LCTL, TT(8), KC_LSFT,                                RAG(KC_LEFT), RAG(KC_RGHT),     KC_MUTE, KC_MPLY, MO(7), HYPR(KC_9), HYPR(KC_0)),
                                                                                                              
	[6] = LAYOUT( //App hotkeys                                                                                 
		MEH(KC_Q), MEH(KC_W), MEH(KC_E), MEH(KC_R), MEH(KC_T),                    MEH(KC_HOME), MEH(KC_END),      MEH(KC_Y), MEH(KC_U), MEH(KC_I), MEH(KC_O), MEH(KC_P), 
		MEH(KC_A), MEH(KC_S), MEH(KC_D), MEH(KC_F), MEH(KC_G),                    MEH(KC_PGUP), MEH(KC_PGDN),     MEH(KC_H), MEH(KC_J), MEH(KC_K), MEH(KC_L), MEH(KC_ENT), 
		MEH(KC_Z), MEH(KC_X), MEH(KC_C), MEH(KC_V), MEH(KC_B),                    MEH(KC_DOWN), MEH(KC_UP),       MEH(KC_N), MEH(KC_M), MEH(KC_COMM), TO(0), MEH(KC_BSPC), 
		MEH(KC_1), MEH(KC_2), MEH(KC_3), MEH(KC_4), MEH(KC_5),                    MEH(KC_LEFT), MEH(KC_RGHT),     MEH(KC_6), MEH(KC_7), MEH(KC_8),MEH(KC_9), MEH(KC_0)),
                                                                              
	[7] = LAYOUT( //QK_BOOT, PC On/Off & Quickly input                          
		LAG(KC_Q), LAG(KC_W), LAG(KC_E), LAG(KC_R), LAG(KC_T),                    LAG(KC_HOME), LAG(KC_END),      LAG(KC_Y), LAG(KC_U), LAG(KC_I), LAG(KC_O), LAG(KC_P), 
		LAG(KC_A), LAG(KC_S), LAG(KC_D), LAG(KC_F), LAG(KC_G),                    LAG(KC_PGUP), LAG(KC_PGDN),     LAG(KC_H), LAG(KC_J), LAG(KC_K), LAG(KC_L), LAG(KC_ENT), 
		LAG(KC_Z), LAG(KC_X), LAG(KC_C), LAG(KC_V), LAG(KC_B),                    LAG(KC_DOWN), LAG(KC_UP),       LAG(KC_N), LAG(KC_M), LAG(KC_COMM), LAG(KC_DOT), LAG(KC_BSPC),  
		LAG(KC_1), LAG(KC_2), LAG(KC_3), LAG(KC_4), LAG(KC_5),                    LAG(KC_LEFT), LAG(KC_RGHT),     LAG(KC_6), QK_BOOT, TO(0), MEH(KC_LBRC), MEH(KC_RBRC)),
                                                                                                              
	[8] = LAYOUT( //R:Keypad                                                                                    
		KC_Q, KC_W, KC_E, KC_R, KC_T,                                             XXXXXXX, XXXXXXX,               KC_PPLS, KC_P7, KC_P8, KC_P9, KC_PDOT, 
		KC_A, KC_S, KC_D, KC_F, KC_G,                                             XXXXXXX, XXXXXXX,               KC_PMNS, KC_P4, KC_P5, KC_P6, KC_P0,           
		KC_Z, KC_X, KC_C, KC_V, KC_B,                                             LCTL(KC_V), LCTL(KC_Z),         KC_PAST, KC_P1, KC_P2, KC_P3, KC_BSPC,   
		KC_RGUI, KC_RALT, KC_RCTL, TO(0), KC_RSFT,                                LCTL(KC_C), LCTL(KC_X),         KC_PSLS, LSFT_T(KC_PENT), KC_ESC, KC_TAB, KC_DEL)
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
