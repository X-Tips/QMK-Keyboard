#include QMK_KEYBOARD_H
#include "leds.c"

// ============== 配置 ==============
enum {
    BOOT_MS = 2000,
    TURBO_INTERVAL_DEFAULT = 16,  // 约60Hz
};

// SOCD 模式: 0=NEUTRAL, 1=LAST, 2=UP, 3=FIRST
static uint8_t socd_mode;
static uint8_t socd_state;

// 连发状态
static bool turbo_enable = false;
static uint16_t turbo_key = 0;
static uint16_t turbo_interval = TURBO_INTERVAL_DEFAULT;
static uint32_t last_turbo_time;

static uint32_t boot_time;
static bool boot_active = true;

// ============== 工具函数 ==============
static inline uint8_t key_idx(uint16_t k) {
    return (k == KC_A) ? 0 : (k == KC_D) ? 1 : (k == KC_W) ? 2 : (k == KC_S) ? 3 : 4;
}

static inline uint8_t axis_pair(uint8_t idx) {
    return (idx & 2) | ((idx & 1) ^ 1);
}

static inline bool is_pressed(uint8_t idx) {
    return (socd_state >> (idx * 2 + 1)) & 1;
}

static inline void set_pressed(uint8_t idx, bool p) {
    uint8_t shift = idx * 2 + 1;
    socd_state = (socd_state & ~(1 << shift)) | (p << shift);
}

static inline void set_first(uint8_t idx, bool f) {
    uint8_t shift = idx * 2;
    socd_state = (socd_state & ~(1 << shift)) | (f << shift);
}

// ============== SOCD 处理 ==============
static void socd_handle(uint8_t idx, bool p) {
    uint8_t o = axis_pair(idx);
    bool op = is_pressed(o);
    set_pressed(idx, p);
    
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
                if (!op) { set_first(idx, 1); set_pressed(o, 0); }
                register_code(K[idx]);
            } else {
                unregister_code(K[idx]);
                if (op && !((socd_state >> (o * 2)) & 1)) { set_first(o, 1); register_code(K[o]); }
            }
            break;
    }
}

// ============== 宏处理 ==============
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

// ============== QMK 回调 ==============
void keyboard_post_init_user(void) {
    boot_time = timer_read32();
}

void matrix_scan_user(void) {
    if (boot_active && timer_elapsed32(boot_time) > BOOT_MS)
        boot_active = false;
    
    if (turbo_key && timer_elapsed32(last_turbo_time) >= turbo_interval) {
        tap_code(turbo_key);
        last_turbo_time = timer_read32();
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool p = record->event.pressed;
    
    // ========== 启动检测 ==========
    if (boot_active && p) {
        if (!readPin(B4)) rgblight_toggle();
        if (!readPin(A14)) {
            default_layer_set(1);
            eeconfig_update_default_layer(1);
            layer_move(0);
            return false;
        }
        #ifdef NKRO_ENABLE
        if (!readPin(B5)) { keymap_config.nkro = 0; eeconfig_update_keymap(keymap_config.raw); }
        else if (!readPin(A2)) { keymap_config.nkro = 1; eeconfig_update_keymap(keymap_config.raw); }
        #endif
    }
    
    // ========== 连发使能键 (LALT) ==========
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
    
    // ========== 攻击键连发处理 ==========
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
    
    // ========== SOCD 键 ==========
    if (keycode == KC_A || keycode == KC_D || keycode == KC_W || keycode == KC_S) {
        socd_handle(key_idx(keycode), p);
        return false;
    }
    
    // ========== 宏键 (F21/F22/F23) ==========
		if (layer_state_is(0)) {
		    if (keycode == KC_F21) { run_macro_1(p); return false; }
		    if (keycode == KC_F22) { run_macro_2(p); return false; }
		    if (keycode == KC_F23) { run_macro_3(p); return false; }
		}    
		
    // ========== 层1功能键 (F1-F7) ==========
    if (IS_LAYER_ON(1) && p) {
        switch (keycode) {
            // SOCD模式切换 (F1-F4)
            case KC_F1: socd_mode = 0; return false;  // NEUTRAL
            case KC_F2: socd_mode = 1; return false;  // LAST
            case KC_F3: socd_mode = 2; return false;  // UP
            case KC_F4: socd_mode = 3; return false;  // FIRST
            // 连发频率切换 (F5-F7)
            case KC_F5: turbo_interval = 16; return false;  // 60Hz
            case KC_F6: turbo_interval = 33; return false;  // 30Hz
            case KC_F7: turbo_interval = 50; return false;  // 20Hz
        }
    }
    
    return true;
}

// ============== 键位映射 ==============
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // 层0: 主层 - 格斗布局
    [0] = LAYOUT(
        MO(1),   KC_W,    KC_F24,  KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_J,    KC_K,    KC_L,    KC_SCLN,
        KC_ENT,  KC_ESC,  KC_HOME, KC_LALT, KC_F21,  KC_F22,  KC_F23),
    
    // 层1: 配置层 - SOCD模式 + 连发频率 (使用F1-F7)
    [1] = LAYOUT(
        TO(0),   XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD, KC_VOLU, RGB_TOG,
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,
        TO(2),   TO(3),   TO(4),   TO(5),   TO(6),   TO(7),   TO(8)),
    
    // 层2: 数字小键盘
    [2] = LAYOUT(
        TO(0),   KC_PAST, KC_PSLS, KC_P7,   KC_P8,   KC_P9,   KC_BSPC,
        KC_ESC,  KC_PPLS, KC_PMNS, KC_P4,   KC_P5,   KC_P6,   KC_PENT,
        KC_TAB,  KC_PEQL, KC_PDOT, KC_P1,   KC_P2,   KC_P3,   KC_P0),
    
    // 层3: MIDI钢琴层
    [3] = LAYOUT(
        TO(0),   MI_Cs4,  MI_Ds4,  MI_Fs4,  MI_Gs4,  MI_As4,  MI_C5,
        MI_C4,   MI_D4,   MI_E4,   MI_F4,   MI_G4,   MI_A4,   MI_B4,
        MI_C5,   MI_Cs5,  MI_D5,   MI_Ds5,  MI_E5,   MI_F5,   MI_Fs5),
    
    // 层4-8: 预留
    [4] = LAYOUT(
        TO(0),   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),
    
    [5] = LAYOUT(
        TO(0),   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),
    
    [6] = LAYOUT(
        TO(0),   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),
    
    [7] = LAYOUT(
        TO(0),   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),
    
    [8] = LAYOUT(
        TO(0),   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),
};