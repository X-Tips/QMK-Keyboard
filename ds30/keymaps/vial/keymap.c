#include QMK_KEYBOARD_H
#include "leds.c"

enum { KC_LRBRC = SAFE_RANGE, KC_LRPRN, K_1_6, K_2_7, K_3_8, K_4_9, K_5_0 };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        LT(6,KC_ESC),   K_1_6,    K_2_7,    K_3_8,    K_4_9,    K_5_0,
        LT(5,KC_TAB),   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T, 
        LT(4,KC_BSPC),  KC_A,     KC_S,     KC_D,     KC_F,     KC_G, 
        LT(3,KC_DEL),   KC_Z,     KC_X,     KC_C,     KC_V,     KC_B, 
        LGUI_T(KC_QUOT), LALT_T(KC_SCLN), LSFT_T(KC_COMM), LCTL_T(KC_DOT), LT(1,KC_SPC), LT(2,KC_ENT)), 

    [1] = LAYOUT( 
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,
        KC_LRPRN,KC_7,    KC_8,    KC_9,    KC_PDOT, KC_PLUS,
        KC_LRBRC,KC_4,    KC_5,    KC_6,    KC_0,    KC_MINS,
        KC_PIPE, KC_1,    KC_2,    KC_3,    KC_BSPC, KC_PAST,
        KC_BSLS, KC_UNDS, KC_QUES, KC_EQL,  TO(0),   KC_SLSH),
    
    [2] = LAYOUT( 
        KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        KC_MS_L, KC_MS_U, KC_MS_R, KC_LEFT, KC_UP,   KC_RGHT,     
        KC_BTN1, KC_MS_D, KC_BTN2, KC_WH_U, KC_DOWN, KC_HOME, 
        KC_BTN4, KC_BTN5, KC_BTN3, KC_WH_D, KC_PGUP, KC_END, 
        KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, KC_PGDN, TO(0)), 

    [3] = LAYOUT( 
        KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18, 
        G(KC_MINS),G(KC_EQL),XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
        G(KC_LEFT),G(KC_RGHT),XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
        TO(0),   A(KC_F4),XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
        KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, MO(7),   MO(8)), 

    [4] = LAYOUT( 
        KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,
        KC_GRV,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    
        TO(0),   KC_H,    KC_J,    KC_K,    KC_L,    KC_DQUO, 
        KC_TILD, KC_N,    KC_M,    KC_LT,   KC_GT,   KC_COLN,
        KC_RGUI, KC_RALT, KC_RSFT, KC_RCTL, XXXXXXX, KC_CAPS),  

    [5] = LAYOUT( 
        KC_INS,  KC_APP,  KC_NUM,  KC_PAUS, KC_PSCR, KC_SCRL,
        TO(0),   KC_MPRV, KC_VOLU, C(KC_PPLS), A(KC_RGHT), G(KC_PPLS), 
        TO(4),   KC_MPLY, KC_MUTE, C(KC_0), C(KC_W), G(KC_ESC),    
        TO(3),   KC_MNXT, KC_VOLD, C(KC_MINS), A(KC_LEFT), G(KC_MINS), 
        KC_CALC, KC_MSEL, C(S(KC_ESC)), G(KC_L), TO(1), TO(2)), 

    [6] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),

    [7] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),

    [8] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT, XXXXXXX)
};

// 长按状态管理
static struct { uint16_t timer; bool triggered; uint8_t idx; } lp = {0, false, 0};
static const uint16_t short_keys[] = {KC_1, KC_2, KC_3, KC_4, KC_5};
static const uint16_t long_keys[]  = {KC_6, KC_7, KC_8, KC_9, KC_0};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_LRBRC || keycode == KC_LRPRN) {
        if (record->event.pressed) {
            SEND_STRING((keycode == KC_LRBRC) ? "[]" : "{}" SS_TAP(X_LEFT));
        }
        return false;
    }
    
    if (keycode >= K_1_6 && keycode <= K_5_0) {
        uint8_t idx = keycode - K_1_6;
        if (record->event.pressed) {
            lp.timer = record->event.time;
            lp.triggered = false;
            lp.idx = idx;
        } else {
            if (!lp.triggered && lp.idx == idx) {
                tap_code(short_keys[idx]);
            }
            lp.timer = 0;
            lp.triggered = false;
        }
        return false;
    }
    return true;
}

void matrix_scan_user(void) {
    if (lp.timer && timer_elapsed(lp.timer) > 200 && !lp.triggered) {
        tap_code(long_keys[lp.idx]);
        lp.triggered = true;
        lp.timer = 0;
    }
}