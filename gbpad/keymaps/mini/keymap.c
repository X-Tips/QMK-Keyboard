#include QMK_KEYBOARD_H
#include "leds.c"
#include "timer.h"

extern MidiDevice midi_device;

enum custom_keycodes {
    KG_C3 = SAFE_RANGE,
    KG_D3, KG_E3, KG_F3, KG_G3,
    KG_A3, KG_B3, KG_C4, KG_D4, KG_E4,
    CHORD_I, CHORD_IV, CHORD_V, CHORD_VI, CHORD_II,
    KG_OCT_DN, KG_OCT_UP,
    SCALE_MAJOR, SCALE_MINOR, SCALE_PENT, SCALE_BLUES, SCALE_CUSTOM,
    CHORD_MAJ, CHORD_MIN, CHORD_7, CHORD_SUS4, CHORD_ADD9
};

static uint32_t boot_time = 0;
static bool boot_window = true;

static int8_t octave_offset = 0;
static uint8_t current_scale = 0;
static uint8_t chord_quality = 0;

static const uint8_t root_notes[5] = {48, 53, 55, 57, 50};
static const uint16_t scale_masks[5] = {0x0AB5, 0x05AF, 0x0529, 0x0C69, 0x0FFF};
static const uint8_t base_notes[10] = {48, 50, 52, 53, 55, 57, 59, 60, 62, 64};
static const uint8_t chord_table[5][4] = {{0, 4, 7, 255}, {0, 3, 7, 255}, {0, 4, 7, 10}, {0, 5, 7, 255}, {0, 4, 7, 14}};
static const uint16_t scale_keys[5] = {SCALE_MAJOR, SCALE_MINOR, SCALE_PENT, SCALE_BLUES, SCALE_CUSTOM};
static const uint16_t chord_keys[5] = {CHORD_MAJ, CHORD_MIN, CHORD_7, CHORD_SUS4, CHORD_ADD9};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        MI_C4,  MI_Cs4, MI_D4,  MI_Ds4, MI_E4,
        MI_F4,  MI_Fs4, MI_G4,  MI_Gs4, MI_A4,
        MI_As4, MI_B4,  MI_C5,  MI_Cs5, MI_D5,
        MI_Ds5, MI_E5,  MI_F5,  MI_Fs5, MI_G5
    ),
    [1] = LAYOUT(
        KG_C3, KG_D3, KG_E3, KG_F3, KG_G3,
        KG_A3, KG_B3, KG_C4, KG_D4, KG_E4,
        CHORD_I, CHORD_IV, CHORD_V, CHORD_VI, CHORD_II,
        MI_SUST, KG_OCT_DN, MO(1), KG_OCT_UP, KC_R
    ),
    [2] = LAYOUT(
        SCALE_MAJOR, SCALE_MINOR, SCALE_PENT, SCALE_BLUES, SCALE_CUSTOM,
        G(S(KC_UP)), G(S(KC_DOWN)), KC_M, KC_S, KC_U,
        CHORD_MAJ, CHORD_MIN, CHORD_7, CHORD_SUS4, CHORD_ADD9,
        G(KC_Z), G(S(KC_Z)), TO(0), G(KC_Q), KC_SPC
    ),
};

bool scale_filter(uint8_t note) {
    if (!current_scale) return true;
    return (scale_masks[current_scale - 1] >> (note % 12)) & 1;
}

void send_note(uint8_t base_note, bool on) {
    uint8_t note = base_note + octave_offset;
    if (!scale_filter(note)) return;
    
    uint8_t velocity = on ? 127 : 0;
    uint8_t channel = 0;
    
    midi_send_noteon(&midi_device, channel, note, velocity);
}

void send_chord(uint8_t idx, bool on) {
    uint8_t root = root_notes[idx];
    const uint8_t *intervals = chord_table[chord_quality];
    for (uint8_t i = 0; i < 4 && intervals[i] != 255; i++) {
        send_note(root + intervals[i], on);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool p = record->event.pressed;
    
    if (boot_window && record->event.pressed) {
        if (!readPin(A15)) {
            rgblight_toggle();
        }
        
        #ifdef NKRO_ENABLE
        if (!readPin(B5)) { 
            keymap_config.nkro = false;
            eeconfig_update_keymap(keymap_config.raw);
        }
        else if (!readPin(C14)) { 
            keymap_config.nkro = true;
            eeconfig_update_keymap(keymap_config.raw);
        }
        #endif
    }

    if (p && keycode == KG_OCT_DN && octave_offset > -24) { octave_offset -= 12; return false; }
    if (p && keycode == KG_OCT_UP && octave_offset < 24)  { octave_offset += 12; return false; }
    
    for (uint8_t i = 0; i < 5; i++) {
        if (keycode == scale_keys[i]) { if (p) current_scale = i + 1; return false; }
        if (keycode == chord_keys[i]) { if (p) chord_quality = i; return false; }
    }
    
    if (keycode >= KG_C3 && keycode <= KG_E4) {
        send_note(base_notes[keycode - KG_C3], p);
        return false;
    }
    
    switch (keycode) {
        case CHORD_I:  send_chord(0, p); return false;
        case CHORD_IV: send_chord(1, p); return false;
        case CHORD_V:  send_chord(2, p); return false;
        case CHORD_VI: send_chord(3, p); return false;
        case CHORD_II: send_chord(4, p); return false;
    }
    return true;
}

void keyboard_post_init_user(void) {
    boot_time = timer_read32();
}

void matrix_scan_user(void) {
    if (boot_window && timer_elapsed32(boot_time) > 2000) {
        boot_window = false;
    }
}
