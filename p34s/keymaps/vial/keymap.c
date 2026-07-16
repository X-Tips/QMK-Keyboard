#include QMK_KEYBOARD_H
#include "leds.c"

void keyboard_pre_init_user(void) {
    setPinOutput(WS2812_DI_PIN); writePinLow(WS2812_DI_PIN); wait_us(100); //复位引脚避免首灯异常亮绿
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT( //Alphabet
		LT(6, KC_Q), KC_W, KC_E, KC_R, KC_T,                               KC_Y, KC_U, KC_I, KC_O, KC_P,
		KC_A, KC_S, KC_D, KC_F, KC_G,                                      KC_H,  KC_J, KC_K, KC_L, KC_ENT,
		LCTL_T(KC_Z), LALT_T(KC_X), LGUI_T(KC_C), LSFT_T(KC_V), KC_B,      KC_N, RSFT_T(KC_M), RGUI_T(KC_COMM), RALT_T(KC_DOT), RCTL_T(KC_BSPC),
		XXXXXXX, XXXXXXX, XXXXXXX, MO(1), KC_DEL,                          KC_SPC, MO(2), XXXXXXX, XXXXXXX, XXXXXXX),

	[1] = LAYOUT( //Numpad and Punctuation
		KC_7, KC_8, KC_9, KC_PDOT, KC_PPLS,                                KC_PAST, KC_EXLM, KC_AT, KC_HASH, KC_DLR,
		KC_4, KC_5, KC_6, KC_0, KC_PMNS,                                   KC_PSLS, KC_PERC, KC_CIRC, KC_AMPR, KC_QUES,
		KC_1, KC_2, KC_3, KC_BSPC, KC_EQL,                                 KC_BSLS, KC_UNDS, KC_PIPE, KC_COLN, KC_DQUO,
		XXXXXXX, XXXXXXX, XXXXXXX, TO(0), KC_PENT,                         MO(3), LGUI(KC_SPC), XXXXXXX, XXXXXXX, XXXXXXX),

	[2] = LAYOUT( //Punctuation and Arrow key
		KC_F9, KC_F10, KC_F11, KC_F12, KC_TILD,                            KC_GRV, KC_HOME, KC_UP, KC_END, KC_PGUP,
		KC_F5, KC_F6, KC_F7, KC_F8, KC_LPRN,                               KC_RPRN, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,
		KC_F1, KC_F2, KC_F3, KC_F4, KC_LCBR,                               KC_RCBR, KC_LBRC, KC_RBRC, KC_SCLN, KC_QUOT,
		XXXXXXX, XXXXXXX, XXXXXXX, KC_CAPS, KC_ESC,                        KC_TAB, TO(0), XXXXXXX, XXXXXXX, XXXXXXX),

	[3] = LAYOUT( //App hotkeys
		MEH(KC_Q), MEH(KC_W), MEH(KC_E), MEH(KC_R), MEH(KC_T),             MEH(KC_Y), MEH(KC_U), MEH(KC_I), MEH(KC_O), MEH(KC_P),
		MEH(KC_A), MEH(KC_S), MEH(KC_D), MEH(KC_F), MEH(KC_G),             MEH(KC_H), MEH(KC_J), MEH(KC_K), MEH(KC_L), MEH(KC_ENT),
		MEH(KC_Z), MEH(KC_Z), MEH(KC_C), MEH(KC_V), MEH(KC_B),             MEH(KC_N), MEH(KC_M), MEH(KC_COMM), MEH(KC_DOT), MEH(KC_BSPC),
		XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT, MEH(KC_LBRC),                  TO(0), MEH(KC_RBRC), XXXXXXX, XXXXXXX, XXXXXXX),

	[4] = LAYOUT( //App hotkeys
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),

	[5] = LAYOUT( //KB Bootkey & Sys Reboot,Shutdown & Others
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),

	[6] = LAYOUT( //KB Bootkey & Sys Reboot,Shutdown & Others
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX, RGB_TOG, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX)
};

