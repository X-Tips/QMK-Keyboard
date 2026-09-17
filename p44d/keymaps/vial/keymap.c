#include QMK_KEYBOARD_H
#include "leds.c"

void keyboard_pre_init_user(void) {
    setPinOutput(WS2812_DI_PIN); writePinLow(WS2812_DI_PIN); wait_us(100); //复位引脚50以上，避免首灯异常亮绿
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT( // Alphabet
        KC_Q,          KC_W,          KC_E,          KC_R,          KC_T,            KC_VOLD,       KC_VOLU,           KC_Y,          KC_U,          KC_I,          KC_O,          KC_P,
        KC_A,          KC_S,          KC_D,          KC_F,          KC_G,            KC_MPLY,       KC_MNXT,           KC_H,          KC_J,          KC_K,          KC_L,          KC_ENT,
        KC_Z,          KC_X,          KC_C,          KC_V,          KC_B,            LCTL(KC_V),    LCTL(KC_Z),        KC_N,          KC_M,          KC_COMM,       KC_DOT,        KC_BSPC,
        LGUI_T(KC_DEL),LALT_T(KC_ESC),LCTL_T(KC_TAB),LT(1, KC_SPC), KC_LSFT,         LCTL(KC_C),    LCTL(KC_X),        KC_SPC,        MO(2),         LT(3, KC_TAB), KC_ESC,        KC_DEL
    ),

    [1] = LAYOUT( // Number & Punctuation
        KC_7,          KC_8,          KC_9,          KC_PDOT,       KC_PPLS,          HYPR(KC_VOLD), HYPR(KC_VOLU),     KC_PAST,       KC_DLR,        KC_COLN,       KC_PIPE,       KC_GRV,
        KC_4,          KC_5,          KC_6,          KC_0,          KC_PMNS,          HYPR(KC_MPLY), HYPR(KC_MNXT),     KC_PSLS,       KC_HASH,       KC_LCBR,       KC_RCBR,       KC_SCLN,
        KC_1,          KC_2,          KC_3,          KC_BSPC,       KC_EQL,           LGUI(KC_MINS), LGUI(KC_EQL),      KC_BSLS,       KC_AMPR,       KC_LABK,       KC_RABK,       KC_QUOT,
        KC_RGUI,       KC_LALT,       KC_RCTL,       TO(0),         LSFT_T(KC_PENT),  LGUI(KC_ESC),  LGUI(KC_ESC),      RAG(KC_6),     LGUI(KC_SPC),  RAG(KC_8),     RAG(KC_9),     RAG(KC_0)
    ),

    [2] = LAYOUT( // Punctuation & Arrow key
        KC_TILD,       KC_PERC,       KC_UNDS,       KC_CIRC,       KC_PLUS,          MEH(KC_VOLD),  MEH(KC_VOLU),      KC_ASTR,       KC_HOME,       KC_UP,         KC_END,        KC_PGUP,
        KC_AT,         KC_DQUO,       KC_EXLM,       KC_QUES,       KC_MINS,          MEH(KC_MPLY),  MEH(KC_MNXT),      KC_SLSH,       KC_LEFT,       KC_DOWN,       KC_RGHT,       KC_PGDN,
        KC_LBRC,       KC_RBRC,       KC_LPRN,       KC_RPRN,       KC_EQL,           LCTL(KC_MINS), LCTL(KC_PLUS),     KC_BSLS,       RSFT(KC_LEFT), RSFT(KC_UP),   RSFT(KC_RGHT), XXXXXXX,
        KC_RGUI,       KC_LALT,       KC_RCTL,       KC_CAPS,       KC_RSFT,          LCTL(KC_0),    LCTL(KC_0),        MEH(KC_SLSH),  TO(0),         RSFT(KC_DOWN), XXXXXXX,       XXXXXXX
    ),

    [3] = LAYOUT( // F-keys
        XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,          XXXXXXX,       XXXXXXX,           XXXXXXX,       KC_F1,         KC_F2,         KC_F3,         KC_F4,
        XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,          XXXXXXX,       XXXXXXX,           XXXXXXX,       KC_F5,         KC_F6,         KC_F7,         KC_F8,
        XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,          XXXXXXX,       XXXXXXX,           XXXXXXX,       KC_F9,         KC_F10,        KC_F11,        KC_F12,
        KC_RGUI,       KC_LALT,       KC_RCTL,       XXXXXXX,       KC_RSFT,          XXXXXXX,       XXXXXXX,           XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX
)
};