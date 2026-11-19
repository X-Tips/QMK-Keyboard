#include QMK_KEYBOARD_H
#include "leds.c"

enum custom_keycodes {
    CUT2HOME = SAFE_RANGE, CUT2END, ALL_COPY, ALL_CUT, ALL_PASTE, XTIPS,
};

void keyboard_pre_init_user(void) {
    setPinOutput(WS2812_DI_PIN); writePinLow(WS2812_DI_PIN); wait_us(100); //复位引脚50以上，避免首灯异常亮绿
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT( // Alphabet
        LT(3, KC_Q),     KC_W,            KC_E,            KC_R,            KC_T,            KC_Y,            KC_U,            KC_I,            KC_O,            LT(4, KC_P),
        KC_A,            KC_S,            KC_D,            KC_F,            KC_G,            KC_H,            KC_J,            KC_K,            KC_L,            KC_ENT,
        LCTL_T(KC_Z),    LALT_T(KC_X),    LGUI_T(KC_C),    RSFT_T(KC_V),    LT(1, KC_B),     LT(2, KC_N),     LSFT_T(KC_M),    RGUI_T(KC_SPC),  RALT_T(KC_DEL),  RCTL_T(KC_BSPC)
    ),

    [1] = LAYOUT( // Numpad and Punctuation
        KC_7,            KC_8,            KC_9,            KC_PDOT,         KC_PLUS,         KC_ASTR,         KC_AMPR,         KC_COLN,         KC_PIPE,         KC_CIRC,
        KC_4,            KC_5,            KC_6,            KC_0,            KC_MINS,         KC_SLSH,         KC_EQL,          KC_LT,           KC_GT,           KC_UNDS,
        KC_1,            KC_2,            KC_3,            KC_PENT,         TO(0),           LGUI(KC_SPC),    RSFT_T(KC_BSLS), RGUI_T(KC_COMM), RALT_T(KC_DOT),  RCTL_T(KC_SCLN)
    ),

    [2] = LAYOUT( // Punctuation and Arrow key
        KC_TILD,         KC_PERC,         KC_LPRN,         KC_RPRN,         KC_DLR,          KC_HASH,         KC_HOME,         KC_UP,           KC_END,          KC_PGUP,
        KC_AT,           KC_DQUO,         KC_LCBR,         KC_RCBR,         KC_EXLM,         KC_QUES,         KC_LEFT,         KC_DOWN,         KC_RGHT,         KC_PGDN,
        LCTL_T(KC_GRV),  LALT_T(KC_QUOT), LGUI_T(KC_LBRC), LSFT_T(KC_RBRC), KC_CAPS,         TO(0),           KC_ESC,          KC_TAB,          CUT2END,         CUT2HOME
    ),

    [3] = LAYOUT( // Hotkeys
        XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,
        XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,
        XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX
    ),

    [4] = LAYOUT( // Fn & Mouse & Media
        XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,
        XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,
        XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX
    ),

    [5] = LAYOUT(
        XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,
        XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,
        XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX
    ),

    [6] = LAYOUT(
        XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,
        XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,
        XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX
    ),

    [7] = LAYOUT( //自定义短语
        HYPR(KC_Q),      HYPR(KC_W),      HYPR(KC_E),      HYPR(KC_R),      HYPR(KC_T),      HYPR(KC_Y),      HYPR(KC_U),      HYPR(KC_I),      HYPR(KC_O),      HYPR(KC_P),
        HYPR(KC_A),      HYPR(KC_S),      HYPR(KC_D),      HYPR(KC_F),      HYPR(KC_G),      HYPR(KC_H),      HYPR(KC_J),      HYPR(KC_K),      HYPR(KC_L),      HYPR(KC_ENT),
        HYPR(KC_Z),      HYPR(KC_X),      HYPR(KC_C),      HYPR(KC_V),      HYPR(KC_B),      HYPR(KC_N),      HYPR(KC_M),      HYPR(KC_COMM),   HYPR(KC_DOT),    HYPR(KC_BSPC)
    ),

    [8] = LAYOUT( //Apps Hotkeys
        MEH(KC_Q),       MEH(KC_W),       MEH(KC_E),       MEH(KC_R),       MEH(KC_T),       MEH(KC_Y),       MEH(KC_U),       MEH(KC_I),       MEH(KC_O),       MEH(KC_P),
        MEH(KC_A),       MEH(KC_S),       MEH(KC_D),       MEH(KC_F),       MEH(KC_G),       MEH(KC_H),       MEH(KC_J),       MEH(KC_K),       MEH(KC_L),       MEH(KC_ENT),
        MEH(KC_Z),       MEH(KC_X),       MEH(KC_C),       MEH(KC_V),       MEH(KC_B),       MEH(KC_N),       MEH(KC_M),       MEH(KC_COMM),    MEH(KC_DOT),     MEH(KC_BSPC)
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