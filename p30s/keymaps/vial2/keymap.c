#include QMK_KEYBOARD_H
#include "leds.c"

enum custom_keycodes {
    CUT2HOME = SAFE_RANGE,
    CUT2END, ALL_COPY, ALL_CUT, ALL_PASTE, XTIPS,
};

void keyboard_pre_init_user(void) {
    setPinOutput(WS2812_DI_PIN); writePinLow(WS2812_DI_PIN); wait_us(100); //复位引脚50以上，避免首灯异常亮绿
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
		MEH_T(KC_Q),     KC_W,            KC_E,            KC_R,            KC_T,            KC_Y,            KC_U,            KC_I,            KC_O,            MEH_T(KC_P),
		KC_A,            LALT_T(KC_S),    LCTL_T(KC_D),    LSFT_T(KC_F),    LGUI_T(KC_G),    RGUI_T(KC_H),    RSFT_T(KC_J),    RCTL_T(KC_K),    RALT_T(KC_L),    KC_ENT,
		KC_Z,            KC_X,            LT(3, KC_C),     LT(1, KC_V),     LT(4, KC_B),     LT(5, KC_N),     LT(2, KC_M),     LT(6, KC_SPC),   KC_DEL,          KC_BSPC
    ),

	[1] = LAYOUT(
		KC_7,            KC_8,            KC_9,            KC_PDOT,         KC_PPLS,         KC_ASTR,         KC_DLR,          KC_COLN,         KC_PIPE,         KC_GRV,
		KC_4,            KC_5,            KC_6,            KC_0,            KC_PMNS,         RGUI_T(KC_SLSH), RSFT_T(KC_EQL),  RCTL_T(KC_COMM), RALT_T(KC_DOT),  KC_AMPR,
		KC_1,            KC_2,            KC_3,            TO(0),           MEH_T(KC_PENT),  KC_CAPS,         LGUI(KC_SPC),    KC_LABK,         KC_RABK,         CUT2END
    ),

	[2] = LAYOUT(
		KC_TILD,         KC_PERC,         KC_UNDS,         KC_CIRC,         KC_LCBR,         KC_RCBR,         KC_HOME,         KC_UP,           KC_END,          KC_PGUP,
		KC_HASH,         LALT_T(KC_QUOT), LCTL_T(KC_SCLN), LSFT_T(KC_BSLS), LGUI_T(KC_LBRC), KC_RBRC,         KC_LEFT,         KC_DOWN,         KC_RGHT,         KC_PGDN,
		KC_AT,           KC_DQUO,         KC_EXLM,         KC_QUES,         KC_LPRN,         KC_RPRN,         TO(0),           KC_TAB,          KC_ESC,          CUT2HOME
    ),

    [3] = LAYOUT( // Hotkeys
        ALL_CUT,         ALL_COPY,        ALL_PASTE,       RCS(KC_1),       KC_VOLD,         KC_VOLU,         LGUI(KC_EQL),    LGUI(KC_UP),     LCTL(KC_PLUS),   LCTL(KC_TAB),
        LCTL(KC_X),      LCTL(KC_C),      LCTL(KC_V),      RCS(KC_O),       KC_MPRV,         KC_MNXT,         LGUI(KC_ESC),    LGUI(KC_RGHT),   LCTL(KC_0),      C(S(KC_TAB)),
        LALT(KC_Z),      LCTL(KC_Y),      TO(0),           C(A(KC_A)),      KC_MUTE,         KC_MPLY,         LGUI(KC_MINS),   LGUI(KC_DOWN),   LCTL(KC_MINS),   LALT(KC_TAB)
    ),

    [4] = LAYOUT( // Fn & Mouse & Media
        KC_F7,           KC_F8,           KC_F9,           KC_F10,          KC_F11,          KC_F12,          KC_MS_WH_UP,     KC_MS_BTN1,      KC_MS_UP,        KC_MS_BTN2,
        KC_F1,           KC_F2,           KC_F3,           KC_F4,           KC_F5,           KC_F6,           KC_MS_WH_DOWN,   KC_MS_LEFT,      KC_MS_DOWN,      KC_MS_RIGHT,
        XXXXXXX,         KC_LCTL,         KC_LALT,         KC_LGUI,         KC_LSFT,         XXXXXXX,         KC_MS_BTN3,      TO(0),           KC_MS_BTN4,      KC_MS_BTN5
    ),

    [5] = LAYOUT(
        XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,
        XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,
        XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX
    ),

    [6] = LAYOUT( // Software hotkeys
        XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,
        XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,
        XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         MO(7)
    ),

    [7] = LAYOUT( // KB Bootkey & Sys Reboot,Shutdown & Others
        XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XTIPS,
        XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         RGB_TOG,
        KC_APP,          KC_PSCR,         KC_NUM,          KC_SCRL,         KC_PAUS,         KC_INS,          QK_BOOT,         MEH(KC_LBRC),    MEH(KC_RBRC),    TO(0)
    ),

    [8] = LAYOUT(
        XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,
        XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,
        XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) return true;

    switch (keycode) {
        case CUT2HOME: tap_code16(LSFT(LGUI(KC_LEFT))); tap_code16(LGUI(KC_C)); tap_code16(KC_BSPC); return false;
        case CUT2END: tap_code16(LSFT(LGUI(KC_RGHT))); tap_code16(LGUI(KC_C)); tap_code16(KC_DEL); return false;
        case ALL_COPY: tap_code16(LGUI(KC_A)); tap_code16(LGUI(KC_C)); return false;
        case ALL_CUT: tap_code16(LGUI(KC_A)); tap_code16(LGUI(KC_X)); return false;
        case ALL_PASTE: tap_code16(LGUI(KC_A)); tap_code16(LGUI(KC_V)); return false;
        case XTIPS: send_string("X.Tips"); return false;
    }
    return true;
}