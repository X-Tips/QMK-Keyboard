#include QMK_KEYBOARD_H
#include "timer.h"

static uint32_t boot_time = 0;
static bool boot_window = true;

const rgblight_segment_t PROGMEM capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_CYAN});
const rgblight_segment_t PROGMEM layer_1[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_WHITE});
const rgblight_segment_t PROGMEM layer_2[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_WHITE});
const rgblight_segment_t PROGMEM layer_3[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_WHITE});
const rgblight_segment_t PROGMEM layer_4[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_WHITE});
const rgblight_segment_t PROGMEM layer_5[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_PURPLE});
const rgblight_segment_t PROGMEM layer_6[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_ORANGE});
const rgblight_segment_t PROGMEM layer_7[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_BLUE});
const rgblight_segment_t PROGMEM layer_8[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_PINK});

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    capslock_layer, layer_1, layer_2, layer_3, layer_4, layer_5, layer_6, layer_7, layer_8
);

layer_state_t layer_state_set_user(layer_state_t state) {
    for (uint8_t i = 0; i < 8; i++) {
        rgblight_set_layer_state(i + 1, layer_state_cmp(state, i + 1));
    }
    return state;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}

void keyboard_post_init_user(void) {
    boot_time = timer_read32();
    
    if (!eeconfig_is_enabled()) {
        eeconfig_init();
    }
    
    rgblight_layers = my_rgb_layers;
}

void matrix_scan_user(void) {
    if (boot_window && timer_elapsed32(boot_time) > 2000) {
        boot_window = false;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (boot_window && record->event.pressed) {
        if (readPin(GP6) == 0) {
            rgblight_toggle();
        }

#ifdef NKRO_ENABLE
        if (readPin(GP13) == 0) { 
            keymap_config.nkro = false;
            eeconfig_update_keymap(keymap_config.raw);
        }
        else if (readPin(GP20) == 0) { 
            keymap_config.nkro = true;
            eeconfig_update_keymap(keymap_config.raw);
        }
#endif
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U,
        KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J,
        KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M),

    [1] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______),

    [2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______),

    [3] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______),

    [4] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______),

    [5] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______),

    [6] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______),

    [7] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______),

    [8] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______)
};