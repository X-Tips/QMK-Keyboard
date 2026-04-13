#include QMK_KEYBOARD_H

// ==================== SOCD ====================
static uint8_t socd_state;
static uint8_t socd_mode;

static inline uint8_t key_idx(uint16_t k) {
    return (k == KC_A) ? 0 : (k == KC_D) ? 1 : (k == KC_W) ? 2 : 3;
}

static inline uint8_t axis_pair(uint8_t i) {
    return (i & 2) | ((i & 1) ^ 1);
}

static inline bool is_pressed(uint8_t i) {
    return (socd_state >> (i * 2 + 1)) & 1;
}

static inline void set_press(uint8_t i, bool p) {
    uint8_t shift = i * 2 + 1;
    socd_state = (socd_state & ~(1 << shift)) | (p << shift);
}

static inline void set_first(uint8_t i, bool f) {
    uint8_t shift = i * 2;
    socd_state = (socd_state & ~(1 << shift)) | (f << shift);
}

static void socd_handle(uint8_t idx, bool p) {
    uint8_t o = axis_pair(idx);
    bool op = is_pressed(o);
    set_press(idx, p);
    
    const uint16_t K[4] = {KC_A, KC_D, KC_W, KC_S};
    uint8_t n = idx & ~1, y = idx | 1;
    
    switch (socd_mode) {
        case 0: // NEUTRAL
            if (p && op) { unregister_code(K[n]); unregister_code(K[y]); }
            else if (!p && op) register_code(K[o]);
            else if (p) register_code(K[idx]);
            else unregister_code(K[idx]);
            break;
        case 1: // LAST
            if (p && op) { unregister_code(K[o]); register_code(K[idx]); }
            else if (!p && op) { unregister_code(K[idx]); register_code(K[o]); }
            break;
        case 2: // UP
            if (idx < 2) {
                if (p && op) { unregister_code(K[n]); unregister_code(K[y]); }
                else if (!p && op) register_code(K[o]);
                else if (p) register_code(K[idx]);
                else unregister_code(K[idx]);
            } else if (idx == 2) {
                if (p) { unregister_code(KC_S); register_code(KC_W); }
                else { unregister_code(KC_W); if (is_pressed(3)) register_code(KC_S); }
            } else {
                if (p && !is_pressed(2)) register_code(KC_S);
                else if (!p) unregister_code(KC_S);
            }
            break;
        case 3: // FIRST
            if (p) {
                if (!op) { set_first(idx, 1); set_press(o, 0); }
                register_code(K[idx]);
            } else {
                unregister_code(K[idx]);
                if (op && !((socd_state >> (o * 2)) & 1)) { set_first(o, 1); register_code(K[o]); }
            }
            break;
    }
}

// ========================================
static bool turbo_enable = false;
static uint16_t turbo_key = 0;
static uint16_t turbo_interval = 16;
static uint32_t last_turbo_time;

// ========================================
static void run_macro_1(bool p) {
    if (p) {
        register_code(KC_U); register_code(KC_I); register_code(KC_O);
    } else {
        unregister_code(KC_U); unregister_code(KC_I); unregister_code(KC_O);
    }
}

static void run_macro_2(bool p) {
    if (p) {
        register_code(KC_J); register_code(KC_K); register_code(KC_L);
    } else {
        unregister_code(KC_J); unregister_code(KC_K); unregister_code(KC_L);
    }
}

static void run_macro_3(bool p) {
    if (p) {
        register_code(KC_L); register_code(KC_SCLN);
    } else {
        unregister_code(KC_L); unregister_code(KC_SCLN);
    }
}

// ========================================
const rgblight_segment_t PROGMEM capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_CYAN});
const rgblight_segment_t PROGMEM layer_1[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_WHITE});
const rgblight_segment_t PROGMEM layer_2[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_CYAN});
const rgblight_segment_t PROGMEM layer_3[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_BLUE});
const rgblight_segment_t PROGMEM layer_4[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_PURPLE});
const rgblight_segment_t PROGMEM layer_5[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_ORANGE});
const rgblight_segment_t PROGMEM layer_6[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_TEAL});
const rgblight_segment_t PROGMEM layer_7[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_MAGENTA});
const rgblight_segment_t PROGMEM layer_8[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_GOLD});

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    capslock_layer, layer_1, layer_2, layer_3, layer_4, layer_5, layer_6, layer_7, layer_8
);

// ========================================
static uint32_t boot_time;
static bool booted;

void keyboard_post_init_user(void) {
    boot_time = timer_read32();
    rgblight_layers = my_rgb_layers;
}

void matrix_scan_user(void) {
    if (!booted && timer_elapsed32(boot_time) > 2000) {
        booted = true;
    }
    
    if (turbo_key && timer_elapsed32(last_turbo_time) >= turbo_interval) {
        tap_code(turbo_key);
        last_turbo_time = timer_read32();
    }
}

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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool p = record->event.pressed;
    
    // rgblight_toggle
        if (!booted && p) {
        if (!readPin(GP6)) rgblight_toggle();
        #ifdef NKRO_ENABLE
        if (!readPin(GP20)) { keymap_config.nkro = 0; eeconfig_update_keymap(keymap_config.raw); }
        else if (!readPin(GP13)) { keymap_config.nkro = 1; eeconfig_update_keymap(keymap_config.raw); }
        #endif
    }
    
    // SOCD
    if (keycode == KC_A || keycode == KC_D || keycode == KC_W || keycode == KC_S) {
        socd_handle(key_idx(keycode), p);
        return false;
    }
    
    // (LALT)
    if (keycode == KC_LALT) {
        if (p) {
            turbo_enable = true;
            if (turbo_key) last_turbo_time = timer_read32();
        } else {
            turbo_enable = false;
            turbo_key = 0;
        }
        return false;
    }
    
    // 
    if (turbo_enable && (keycode == KC_U || keycode == KC_I || keycode == KC_O || 
                         keycode == KC_P || keycode == KC_J || keycode == KC_K || 
                         keycode == KC_L || keycode == KC_SCLN)) {
        if (p) {
            turbo_key = keycode;
            last_turbo_time = timer_read32();
            tap_code(keycode);
        } else {
            if (turbo_key == keycode) turbo_key = 0;
        }
        return false;
    }
    
    // (F1-F7)
    if (IS_LAYER_ON(1) && p) {
        switch (keycode) {
            case KC_F13: socd_mode = 0; return false;  // NEUTRAL
            case KC_F14: socd_mode = 1; return false;  // LAST
            case KC_F15: socd_mode = 2; return false;  // UP
            case KC_F16: socd_mode = 3; return false;  // FIRST
            case KC_F17: turbo_interval = 16; return false;  // 60Hz
            case KC_F18: turbo_interval = 33; return false;  // 30Hz
            case KC_F19: turbo_interval = 50; return false;  // 20Hz
        }
    }
    
    // (F21/F22/F23)
        if (layer_state_is(0)) {
        if (keycode == KC_F21) { run_macro_1(p); return false; }
        if (keycode == KC_F22) { run_macro_2(p); return false; }
        if (keycode == KC_F23) { run_macro_3(p); return false; }
    }
    
    return true;
}

// ========================================
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        MO(1),   KC_W,    KC_F24,  KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_J,    KC_K,    KC_L,    KC_SCLN,
        KC_ENT,  KC_ESC,  KC_HOME, KC_LALT, KC_F21,  KC_F22,  KC_F23),
    
    [1] = LAYOUT(
        TO(0),   XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD, KC_VOLU, RGB_TOG,
        KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,
        TO(2),   TO(3),   TO(4),   TO(5),   TO(6),   TO(7),   TO(8)),
    
    [2] = LAYOUT(
        TO(0),   KC_PAST, KC_PSLS, KC_P7,   KC_P8,   KC_P9,   KC_BSPC,
        KC_ESC,  KC_PPLS, KC_PMNS, KC_P4,   KC_P5,   KC_P6,   KC_PENT,
        KC_TAB,  KC_PEQL, KC_PDOT, KC_P1,   KC_P2,   KC_P3,   KC_P0),
    
    [3] = LAYOUT(
        TO(0),   MI_Cs4,  MI_Ds4,  MI_Fs4,  MI_Gs4,  MI_As4,  MI_C5,
        MI_C4,   MI_D4,   MI_E4,   MI_F4,   MI_G4,   MI_A4,   MI_B4,
        MI_C5,   MI_Cs5,  MI_D5,   MI_Ds5,  MI_E5,   MI_F5,   MI_Fs5),
    
    [4] = LAYOUT(
        TO(0),   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),
    
    [5] = LAYOUT(
        TO(0),   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),
    
    [6] = LAYOUT(
        TO(0),   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),
    
    [7] = LAYOUT(
        TO(0),   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),
    
    [8] = LAYOUT(
        TO(0),   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),
};