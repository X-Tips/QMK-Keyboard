#include QMK_KEYBOARD_H
#include <stdio.h>
#include "leds.c"

enum custom_keycodes {
    CUT2HOME = SAFE_RANGE, CUT2END, ALL_COPY, ALL_CUT, ALL_PASTE, XTIPS,
};

void keyboard_pre_init_user(void) {
    setPinOutput(WS2812_DI_PIN); writePinLow(WS2812_DI_PIN); wait_us(100); //复位引脚50以上，避免首灯异常亮绿
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT( // Alphabet
        LT(6, KC_Q),     KC_W,            KC_E,            KC_R,            KC_T,            KC_Y,            KC_U,            KC_I,            KC_O,            KC_P,
        KC_A,            KC_S,            KC_D,            LT(3, KC_F),     KC_G,            KC_H,            LT(4, KC_J),     KC_K,            KC_L,            KC_ENT,
        LCTL_T(KC_Z),    LGUI_T(KC_X),    LALT_T(KC_C),    LT(1, KC_V),     LSFT_T(KC_B),    RSFT_T(KC_N),    LT(2, KC_M),     RALT_T(KC_SPC),  RGUI_T(KC_DEL),  RCTL_T(KC_BSPC)
    ),

    [1] = LAYOUT( // Numpad and Punctuation
        KC_7,            KC_8,            KC_9,            KC_PDOT,         KC_PLUS,         KC_ASTR,         KC_DLR,          KC_COLN,         KC_PIPE,         KC_GRV,
        KC_4,            KC_5,            KC_6,            KC_0,            KC_MINS,         KC_SLSH,         KC_HASH,         KC_LCBR,         KC_RCBR,         KC_SCLN,
        KC_1,            KC_2,            KC_3,            TO(0),           KC_PENT,         KC_CAPS,         LGUI(KC_SPC),    KC_COMM,         KC_DOT,          CUT2END
    ),

    [2] = LAYOUT( // Punctuation and Arrow key
        KC_TILD,         KC_PERC,         KC_UNDS,         KC_CIRC,         KC_LABK,         KC_RABK,         KC_HOME,         KC_UP,           KC_END,          KC_PGUP,
        KC_AT,           KC_DQUO,         KC_EXLM,         KC_QUES,         KC_LPRN,         KC_RPRN,         KC_LEFT,         KC_DOWN,         KC_RGHT,         KC_PGDN,
        LCTL_T(KC_LBRC), LGUI_T(KC_RBRC), LALT_T(KC_QUOT), KC_AMPR,         LSFT_T(KC_EQL),  KC_BSLS,         TO(0),           KC_ESC,          KC_TAB,          CUT2HOME
    ),

    [3] = LAYOUT( // Hotkeys
        ALL_CUT,         ALL_COPY,        ALL_PASTE,       RCS(KC_1),       KC_VOLD,         KC_VOLU,         LGUI(KC_EQL),    LGUI(KC_UP),     LCTL(KC_PLUS),   LCTL(KC_TAB),
        LCTL(KC_X),      LCTL(KC_C),      LCTL(KC_V),      TO(0),           KC_MPRV,         KC_MNXT,         LGUI(KC_ESC),    LGUI(KC_RGHT),   LCTL(KC_0),      C(S(KC_TAB)),
        LALT(KC_Z),      LCTL(KC_Y),      C(A(KC_A)),      RCS(KC_O),       KC_MUTE,         KC_MPLY,         LGUI(KC_MINS),   LGUI(KC_DOWN),   LCTL(KC_MINS),   LALT(KC_TAB)
    ),

    [4] = LAYOUT( // Fn & Mouse & Media
        KC_F7,           KC_F8,           KC_F9,           KC_F10,          KC_F11,          KC_F12,          KC_MS_WH_UP,     KC_MS_BTN1,      KC_MS_UP,        KC_MS_BTN2,
        KC_F1,           KC_F2,           KC_F3,           KC_F4,           KC_F5,           KC_F6,           TO(0),           KC_MS_LEFT,      KC_MS_DOWN,      KC_MS_RIGHT,
        KC_LCTL,         KC_LGUI,         KC_LALT,         XXXXXXX,         KC_LSFT,         XXXXXXX,         KC_MS_WH_DOWN,   KC_MS_BTN4,      KC_MS_BTN5,      KC_MS_BTN3
    ),

    [5] = LAYOUT(
        XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,
        XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,
        XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX
    ),

    [6] = LAYOUT( // Software hotkeys
        TO(0),           MEH(KC_W),       MEH(KC_E),       MEH(KC_R),       MEH(KC_T),       MEH(KC_Y),       MEH(KC_U),       MEH(KC_I),       MEH(KC_O),       MEH(KC_P),
        MEH(KC_A),       MEH(KC_S),       MEH(KC_D),       MEH(KC_F),       MEH(KC_G),       MEH(KC_H),       MEH(KC_J),       MEH(KC_K),       MEH(KC_L),       MEH(KC_ENT),
        MEH(KC_Z),       MEH(KC_X),       MEH(KC_C),       MEH(KC_V),       MEH(KC_B),       MEH(KC_N),       MEH(KC_M),       MEH(KC_COMM),    MEH(KC_BSPC),    MO(7)
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