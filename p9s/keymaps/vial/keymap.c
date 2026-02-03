#include QMK_KEYBOARD_H
#include "timer.h"

static uint32_t boot_time = 0;
static bool boot_window = true;
static uint8_t pending_layer = 0xFF;
static bool was_layer_8_active = false;

void keyboard_post_init_user(void) {
    boot_time = timer_read32();
    
    if (!eeconfig_is_enabled()) {
        eeconfig_init();
        default_layer_set(1UL << 0);
        eeconfig_update_default_layer(default_layer_state);
    } else {
        default_layer_set(eeconfig_read_default_layer());
    }
    
    uint8_t default_layer = get_highest_layer(default_layer_state);
    layer_move(default_layer);
}

void matrix_scan_user(void) {
    if (boot_window && timer_elapsed32(boot_time) > 2000) {
        boot_window = false;
    }
    
    bool is_layer_8_active = IS_LAYER_ON(8);
    
    if (was_layer_8_active && !is_layer_8_active) {
        if (pending_layer != 0xFF) {
            layer_move(pending_layer);
            pending_layer = 0xFF;
        }
    }
    
    was_layer_8_active = is_layer_8_active;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (boot_window && record->event.pressed) {
        if (!readPin(A14)) {
            rgblight_toggle();
        }
        
        #ifdef NKRO_ENABLE
        if (!readPin(B3)) { 
            keymap_config.nkro = false;
            eeconfig_update_keymap(keymap_config.raw);
        }
        else if (!readPin(C13)) { 
            keymap_config.nkro = true;
            eeconfig_update_keymap(keymap_config.raw);
        }
        #endif
    }

    if (record->event.pressed && IS_QK_DEF_LAYER(keycode)) { 
        pending_layer = keycode - QK_DEF_LAYER;
        default_layer_set(1UL << pending_layer);
        eeconfig_update_default_layer(default_layer_state);
        return false;
    }

    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        LT(8,KC_MUTE), KC_VOLU, C(S(KC_SLSH)),
        KC_MPRV, KC_MPLY, KC_MNXT, 
        C(S(KC_COMM)), KC_VOLD, C(S(KC_DOT))
    ), 

    [1] = LAYOUT(
        LT(8,KC_MUTE), KC_VOLU, C(A(KC_R)),
        KC_MPRV, KC_MPLY, KC_MNXT, 
        C(A(KC_L)), KC_VOLD, C(A(KC_D))
    ), 

    [2] = LAYOUT(
        LT(8,KC_MUTE), KC_VOLU, C(A(KC_F)),
        KC_MPRV, KC_MPLY, KC_MNXT, 
        C(A(KC_J)), KC_VOLD, C(A(KC_K))
    ), 

    [3] = LAYOUT(
        LT(8,KC_MUTE), KC_VOLU, A(S(KC_SLSH)),
        KC_MPRV, KC_MPLY, KC_MNXT, 
        A(S(KC_COMMA)), KC_VOLD, A(S(KC_DOT))
    ), 

    [4] = LAYOUT(
        LT(8,KC_MUTE), KC_VOLU, C(A(S(KC_SLSH))),
        KC_MPRV, KC_MPLY, KC_MNXT, 
        C(A(S(KC_COMM))), KC_VOLD, C(A(S(KC_DOT)))
    ), 

    [5] = LAYOUT(
        LT(8,KC_MUTE), KC_VOLU, C(S(KC_1)),
        KC_MPRV, KC_MPLY, KC_MNXT, 
        C(S(KC_2)), KC_VOLD, C(S(KC_3))
    ), 

    [6] = LAYOUT(
        LT(8,KC_MUTE), KC_VOLU, A(S(KC_4)),
        KC_MPRV, KC_MPLY, KC_MNXT, 
        A(S(KC_5)), KC_VOLD, A(S(KC_6))
    ), 

    [7] = LAYOUT( 
        XXXXXXX, XXXXXXX, XXXXXXX, 
        XXXXXXX, XXXXXXX, XXXXXXX, 
        XXXXXXX, XXXXXXX, XXXXXXX
    ), 

    [8] = LAYOUT( 
        XXXXXXX, DF(0), RGB_TOG, 
        DF(1), DF(2), RGB_VAI, 
        DF(3), DF(4), RGB_VAD
    )
};