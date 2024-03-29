/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include <stdio.h>
#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif

enum layers { _QWERTY = 0, _LOWER, _RAISE, _ADJUST,_GAMING };

uint16_t       sleep_timer       = 0;
int8_t         rgb_enabled       = 0;
int8_t         keyboard_in_sleep = 0;
const uint16_t sleep_timeout     = 60000;

void keyboard_sleep(void) {
    keyboard_in_sleep = 1;
    if (rgb_enabled) {
        rgblight_disable_noeeprom();
    }
}

void keyboard_wakeup(void) {
    keyboard_in_sleep = 0;
    if (rgb_enabled) {
        rgblight_enable_noeeprom();
    }
}

// windows only
enum custom_keycodes {
    LNG_SW = SAFE_RANGE,
    CLRPCK,   // powertoys color picker
    VSC,      // 3 pinned item on taskbar
    CHROME,   // 6 pinned item on taskbar
    TERMINAL, // 2 pinned app on taskbar
    EXPLORER, // 1 pinned app on taskbar
    SCRCUT,   // screenshot using win+shift+s
};

#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_LA_EQL LALT_T(KC_EQL)

// #define QUO_RCT MT(MOD_RCTL, KC_QUOT)
// #define BSL_RAL MT(MOD_LALT, KC_BSLS)
// #define LBR_RGU MT(MOD_LGUI, KC_LBRC)
#define RBR_LGU MT(MOD_RGUI, KC_RBRC)
#define MIN_LAL MT(MOD_LALT, KC_MINUS)
#define GRV_LCT MT(MOD_LCTL, KC_GRV)
#define BSP_RSH MT(MOD_RSFT, KC_BSPC)
#define SPC_LSH MT(MOD_LSFT, KC_SPC)
#define DEL_RSE LT(_RAISE, KC_DEL)
#define TAB_RSE LT(_RAISE, KC_TAB)
#define ENT_LWR LT(_LOWER, KC_ENT)
#define ESC_LWR LT(_LOWER, KC_ESC)
#define BSPC_ADJ LT(_ADJUST, KC_BSPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT_split_3x6_3(

        RBR_LGU, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC,

        GRV_LCT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,

        MIN_LAL, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_BSLS,

        TAB_RSE, SPC_LSH, ENT_LWR, ESC_LWR, BSP_RSH, DEL_RSE

        ),

    [_LOWER] = LAYOUT_split_3x6_3(

        KC_LGUI, EXPLORER, CHROME, VSC, TERMINAL, KC_F5, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_RGUI,

        KC_LCTL, KC_NO, KC_NO, KC_NO, KC_F2, CLRPCK, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_RCTL,

        KC_LA_EQL, KC_NO, KC_NO, KC_NO, KC_NO, LNG_SW, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_RALT,

        KC_MPRV, KC_MPLY, KC_MNXT, KC_TRNS, KC_TRNS, KC_TRNS

        ),

    [_RAISE] = LAYOUT_split_3x6_3(

        KC_LGUI, KC_PAST, KC_7, KC_8, KC_9, KC_PPLS, KC_VOLU, KC_HOME, KC_UP, KC_PGUP, KC_NO, KC_RGUI,

        KC_LCTL, KC_PSLS, KC_4, KC_5, KC_6, KC_PMNS, KC_MUTE, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_RCTL,

        KC_LA_EQL, KC_0, KC_1, KC_2, KC_3, KC_PDOT, KC_VOLD, KC_END, KC_MUTE, KC_PGDN, KC_NO, KC_RALT,

        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS

        ),

    [_ADJUST] = LAYOUT_split_3x6_3( 

        SCRCUT, KC_F1, KC_F2, KC_F3, KC_F4, KC_NO, KC_NUM, TG(4), KC_NO, KC_NO, KC_NO, RGB_TOG,

        KC_NO, KC_F5, KC_F6, KC_F7, KC_F8, KC_NO, KC_SCRL, KC_NO, RGB_VAI, RGB_SAI, RGB_HUI, RGB_MOD,

        KC_NO, KC_F9, KC_F10, KC_F11, KC_F12, KC_NO, KC_CAPS, KC_NO, RGB_VAD, RGB_SAD, RGB_HUD, RGB_RMOD,

        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS

        ),

    [_GAMING] = LAYOUT_split_3x6_3(

        KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, TG(4),

        KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_RSFT,

        KC_LALT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RALT,

        KC_LCTL, KC_SPACE, KC_ENT, KC_TAB, KC_BSPC, KC_DEL
    )

};

void switchNumLock(bool trigger) {
    if (trigger) {
        tap_code(KC_NUM);
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _QWERTY:
            switchNumLock(host_keyboard_led_state().num_lock);
            break;
        case _LOWER:
            switchNumLock(host_keyboard_led_state().num_lock);
            break;
        case _RAISE:
            switchNumLock(!host_keyboard_led_state().num_lock);
            break;
        case _ADJUST:
            switchNumLock(host_keyboard_led_state().num_lock);
            break;
        default:
            switchNumLock(host_keyboard_led_state().num_lock);
            break;
    }
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

// all icons for the layer states
void render_base(void) {
    static const char PROGMEM base[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xF0, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00,
    };
    oled_write_raw_P(base, 96);
}
void render_lower(void) {
    static const char PROGMEM lower[] = {
        0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x01, 0x03, 0x07, 0x0F, 0x1E, 0x3E, 0x7C, 0xFC, 0xF8, 0xF8, 0xF0, 0xF0, 0xE0, 0xE0, 0xC0, 0x80, 0x80, 0xC0, 0xE0, 0xE0, 0xF0, 0xF0, 0xF8, 0xF8, 0xFC, 0x7C, 0x3E, 0x1E, 0x0F, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF, 0xFF, 0x7F, 0x3F, 0x1F, 0x0F, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };
    oled_write_raw_P(lower, 96);
}
void render_raise(void) {
    static const char PROGMEM raise[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFC, 0xF8, 0xF0, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xE0, 0x70, 0x78, 0x3C, 0x3E, 0x1F, 0x1F, 0x0F, 0x0F, 0x07, 0x07, 0x03, 0x03, 0x01, 0x00, 0x00, 0x01, 0x03, 0x03, 0x07, 0x07, 0x0F, 0x0F, 0x1F, 0x1F, 0x3E, 0x3C, 0x78, 0x70, 0xE0, 0xC0,
    };
    oled_write_raw_P(raise, 96);
}

void render_adjust(void) {
    static const char PROGMEM adjust[] = {0x00, 0x00, 0x00, 0x60, 0xF8, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xF8, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x1F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x1F, 0x06, 0x00, 0x00, 0x00};
    oled_write_raw_P(adjust, 96);
}

void render_gaming(void) {
    static const char PROGMEM gaming[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xF0, 0xF0, 0xF0, 0xE0, 0xC0, 0x80,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0F, 0x0F,
    0x0F, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; oled_write_raw_P(gaming, 96);
}

// void render_gaming_lower(void) {
//     static const char PROGMEM gaming_lower[] = {0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xF0, 0xF0, 0xF0, 0xE0, 0xC0,
//     0x80, 0x00, 0x00, 0x00, 0x20, 0xDE, 0x20, 0x00, 0x08, 0xF6, 0x08, 0x00,
//     0x04, 0xFA, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0F,
//     0x0F, 0x0F, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; oled_write_raw_P(gaming_lower,
//     96);
// }

static void render_status(void) {
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            render_base();
            break;
        case _LOWER:
            render_lower();
            break;
        case _RAISE:
            render_raise();
            break;
        case _ADJUST:
            render_adjust();
            break;
        case _GAMING:
            render_gaming();
            break;
    }
}

// WPM-responsive animation stuff here
#    define IDLE_FRAMES 5
#    define IDLE_SPEED 35 // below this wpm value your animation will idle

#    define PREP_FRAMES 2

#    define TAP_FRAMES 5
#    define TAP_SPEED 50

#    define ANIM_FRAME_DURATION 100 // how long each frame lasts in ms
#    define ANIM_SIZE \
        416 // number of bytes in array, minimize for adequate firmware size, max is
            // 1024

uint32_t anim_timer         = 0;
uint32_t anim_sleep         = 0;
uint8_t  current_idle_frame = 0;
uint8_t  current_prep_frame = 0;
uint8_t  current_tap_frame  = 0;

// Images credit u/kekboii
static void render_anim(void) {
    static const char PROGMEM idle[IDLE_FRAMES][ANIM_SIZE] = {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xe0, 0xf0, 0x80, 0x00, 0x80, 0xf0, 0xf8, 0x0c, 0x06, 0x82, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x00, 0xff, 0xff, 0xf3, 0xf0, 0xc0, 0xc1, 0xe0, 0xff, 0xff, 0xff, 0xfe, 0x7f, 0x63, 0x30, 0xf8, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x08, 0x10, 0x00, 0x04, 0x03, 0x03, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x6f, 0x47, 0xe0,
                                                               0xf8, 0xc0, 0xc1, 0xe0, 0xf0, 0xf8, 0xfc, 0x1f, 0x0e, 0x00, 0xc3, 0xe1, 0x30, 0x00, 0x00, 0xc1, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe7, 0xf3, 0xf9, 0xfc, 0xe0, 0xf3, 0xf9, 0x3c, 0x4e, 0xb0, 0xdf, 0xff, 0xe7, 0xe1, 0xe0, 0xff, 0xff, 0x00, 0xf8, 0x1e, 0x87, 0xc3, 0xe0, 0xf8, 0x0e, 0x24, 0x28, 0x0f, 0xc0, 0x70, 0x10, 0x20, 0xff, 0x0f, 0x77, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7e, 0x3f, 0x0f, 0x07, 0x03, 0x03, 0x01, 0x01, 0xc7, 0x7c, 0x03, 0xf8, 0xfc, 0x07, 0xf3, 0xe0, 0x38, 0x38, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x3e, 0x78, 0xf9, 0xbb, 0x63, 0xb1, 0x60, 0xe4, 0xc6, 0xc0, 0xe0, 0x20, 0xb0, 0x98, 0xcc, 0x67, 0xb0, 0xfc, 0x67, 0x01, 0x1e, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x7f, 0x0e, 0x5c, 0x3b, 0x86, 0xcc, 0xd9, 0x92, 0xb2, 0xf2, 0xf2, 0xf3, 0x19, 0xcc, 0xe6, 0xc6, 0x93, 0xf4, 0x8c, 0xb9, 0x83,
                                                               0xce, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8e, 0x8e, 0x86, 0xc6, 0x83, 0x81, 0xc6, 0x0e, 0x1e, 0x3e, 0x79, 0x77, 0xed, 0xe8, 0xc0, 0xc1, 0x81, 0x80, 0x06, 0x0e, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0xfd, 0xfb, 0x56, 0x25, 0x63, 0x0b, 0x18, 0x1c, 0x0f, 0x0f, 0x03, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x34, 0x24, 0x28, 0x00, 0x00, 0x18, 0x24, 0x18, 0x00, 0x00, 0x04, 0x34, 0x0c, 0x00, 0x00, 0x04, 0x34, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
                                                              {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0x40, 0x40, 0x20, 0x20, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xe1, 0xf0, 0x80, 0x00, 0x80, 0xf0, 0xe0, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xf3, 0xf0, 0xc0, 0xc1, 0xe0, 0xff, 0xff, 0xff, 0xfe, 0x7f, 0x63, 0x30, 0x18, 0x00, 0x00, 0x00, 0x80, 0x00, 0x10, 0x08, 0x00, 0x4c, 0x08, 0x10, 0x00, 0x00, 0x00, 0x60, 0xc0, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x6f, 0x47, 0xe0,
                                                               0xf8, 0xc0, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0x1f, 0x0e, 0x00, 0x80, 0x00, 0x00, 0x04, 0x06, 0x06, 0x02, 0x02, 0x02, 0x01, 0x00, 0xe7, 0xf3, 0xf9, 0xfc, 0xe0, 0xf3, 0xf9, 0x3c, 0x4e, 0xb0, 0xdf, 0xff, 0xe7, 0xe1, 0xe0, 0xff, 0xff, 0x00, 0xf8, 0x1e, 0x87, 0xc3, 0xe0, 0xf8, 0x0e, 0x04, 0x00, 0x00, 0xc0, 0x70, 0x10, 0x20, 0xff, 0x0f, 0x77, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7e, 0x3f, 0x0f, 0x07, 0x03, 0x03, 0x01, 0x01, 0xc7, 0x7c, 0x03, 0xf8, 0xfc, 0x07, 0xf3, 0xe0, 0x38, 0x38, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x3e, 0x78, 0xf9, 0xbb, 0x63, 0xb1, 0x60, 0xe4, 0xc6, 0xc0, 0xe0, 0x20, 0xb0, 0x98, 0xcc, 0x67, 0xb0, 0xfc, 0x67, 0x01, 0x1e, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x7f, 0x0e, 0x5c, 0x3b, 0x86, 0xcc, 0xd9, 0x92, 0xb2, 0xf2, 0xf2, 0xf3, 0x19, 0xcc, 0xe6, 0xc6, 0x93, 0xf4, 0x8c, 0xb9, 0x83,
                                                               0xce, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8e, 0x8e, 0x86, 0xc6, 0x83, 0x81, 0xc6, 0x0e, 0x1e, 0x3e, 0x79, 0x77, 0xed, 0xe8, 0xc0, 0xc1, 0x81, 0x80, 0x06, 0x0e, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0xfd, 0xfb, 0x56, 0x25, 0x63, 0x0b, 0x18, 0x1c, 0x0f, 0x0f, 0x03, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x34, 0x24, 0x28, 0x00, 0x00, 0x18, 0x24, 0x18, 0x00, 0x00, 0x04, 0x34, 0x0c, 0x00, 0x00, 0x04, 0x34, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
                                                              {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x40, 0x40, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xe3, 0xf7, 0x9c, 0x00, 0x80, 0xc0, 0x03, 0x00, 0x0c, 0x8e, 0xc2, 0xf6, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x0c, 0xff, 0xff, 0xf3, 0xf0, 0xc0, 0xc1, 0xe0, 0xff, 0xfe, 0xfe, 0xfe, 0x7f, 0x6f, 0xb7, 0xf9, 0x00, 0x00, 0x00, 0xc0, 0x60, 0x78, 0x18, 0x0c, 0x4c, 0x00, 0x00, 0x00, 0xc0, 0x80, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x6f, 0x47, 0xe0,
                                                               0xf8, 0xc0, 0xc3, 0xe1, 0xf0, 0xf8, 0xfc, 0x1f, 0x0e, 0x00, 0x80, 0x30, 0x78, 0x3e, 0x06, 0x02, 0xa2, 0x13, 0x00, 0x00, 0x00, 0xe7, 0xf3, 0xf9, 0xfc, 0xe0, 0xf3, 0xf9, 0x3c, 0x4e, 0xb0, 0xdf, 0xff, 0xe7, 0xe1, 0xe0, 0xff, 0xff, 0x00, 0xf8, 0x1e, 0x87, 0xc3, 0xe0, 0xf8, 0x0e, 0x1f, 0x13, 0x01, 0x00, 0x00, 0x00, 0x00, 0xff, 0x0f, 0x77, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7e, 0x3f, 0x0f, 0x07, 0x03, 0x03, 0x01, 0x01, 0xc7, 0x7c, 0x03, 0xf8, 0xfc, 0x07, 0xf3, 0xe0, 0x38, 0x38, 0x0f, 0x06, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x3e, 0x78, 0xf9, 0xbb, 0x63, 0xb1, 0x60, 0xe4, 0xc6, 0xc0, 0xe0, 0x20, 0xb0, 0x98, 0xcc, 0x67, 0xb0, 0xfc, 0x67, 0x01, 0x1e, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x7f, 0x0e, 0x5c, 0x3b, 0x86, 0xcc, 0xd9, 0x92, 0xb2, 0xf2, 0xf2, 0xf3, 0x19, 0xcc, 0xe6, 0xc6, 0x93, 0xf4, 0x8c, 0xb9, 0x83,
                                                               0xce, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8e, 0x8e, 0x86, 0xc6, 0x83, 0x81, 0xc6, 0x0e, 0x1e, 0x3e, 0x79, 0x77, 0xed, 0xe8, 0xc0, 0xc1, 0x81, 0x80, 0x06, 0x0e, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0xfd, 0xfb, 0x56, 0x25, 0x63, 0x0b, 0x18, 0x1c, 0x0f, 0x0f, 0x03, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x34, 0x24, 0x28, 0x00, 0x00, 0x18, 0x24, 0x18, 0x00, 0x00, 0x04, 0x34, 0x0c, 0x00, 0x00, 0x04, 0x34, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
                                                              {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0x80, 0x00, 0x80, 0xc0, 0x08, 0x04, 0x06, 0x80, 0xc1, 0x51, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x60, 0x00, 0xfe, 0xff, 0xf3, 0xf0, 0xc0, 0xc1, 0xe0, 0xff, 0xfe, 0xfe, 0xfe, 0x7f, 0x63, 0xb0, 0xf8, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf0, 0x00, 0x80, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x03, 0x01, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x6f, 0x47, 0xe0,
                                                               0xf8, 0xc0, 0xc3, 0xe1, 0xf0, 0xf8, 0xfc, 0x1f, 0x0f, 0x00, 0xc0, 0xf0, 0x78, 0x3a, 0x06, 0x00, 0xe0, 0x30, 0x00, 0x00, 0x00, 0xe7, 0xf3, 0xf9, 0xfc, 0xe0, 0xf3, 0xf9, 0x3c, 0x4e, 0xb0, 0xdf, 0xff, 0xe7, 0xe1, 0xe0, 0xff, 0xff, 0x00, 0xf8, 0x1e, 0x87, 0xc3, 0xe0, 0xf8, 0x0e, 0x03, 0x18, 0x08, 0x00, 0x00, 0x00, 0x00, 0xff, 0x0f, 0x77, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7e, 0x3f, 0x0f, 0x07, 0x03, 0x03, 0x01, 0x01, 0xc7, 0x7c, 0x03, 0xf8, 0xfc, 0x07, 0xf3, 0xe0, 0x38, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x3e, 0x78, 0xf9, 0xbb, 0x63, 0xb1, 0x60, 0xe4, 0xc6, 0xc0, 0xe0, 0x20, 0xb0, 0x98, 0xcc, 0x67, 0xb0, 0xfc, 0x67, 0x01, 0x1e, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x7f, 0x0e, 0x5c, 0x3b, 0x86, 0xcc, 0xd9, 0x92, 0xb2, 0xf2, 0xf2, 0xf3, 0x19, 0xcc, 0xe6, 0xc6, 0x93, 0xf4, 0x8c, 0xb9, 0x83,
                                                               0xce, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8e, 0x8e, 0x86, 0xc6, 0x83, 0x81, 0xc6, 0x0e, 0x1e, 0x3e, 0x79, 0x77, 0xed, 0xe8, 0xc0, 0xc1, 0x81, 0x80, 0x06, 0x0e, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0xfd, 0xfb, 0x56, 0x25, 0x63, 0x0b, 0x18, 0x1c, 0x0f, 0x0f, 0x03, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x34, 0x24, 0x28, 0x00, 0x00, 0x18, 0x24, 0x18, 0x00, 0x00, 0x04, 0x34, 0x0c, 0x00, 0x00, 0x04, 0x34, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
                                                              {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xf0, 0xf8, 0x0c, 0x0e, 0x82, 0x83, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0x9c, 0xf6, 0xe2, 0xc0, 0xc0, 0xc0, 0xe0, 0xff, 0xff, 0xff, 0xfe, 0x7f, 0x61, 0xb0, 0xf8, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x00, 0x00, 0x80, 0xc0, 0x00, 0x00, 0x00, 0x04, 0x03, 0x03, 0x01, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x6f, 0x47, 0xe0,
                                                               0xf8, 0xc0, 0xc3, 0xe1, 0xf0, 0xf8, 0xfc, 0x1f, 0x00, 0x00, 0xc3, 0xf1, 0x38, 0x10, 0x00, 0xc0, 0xe0, 0x30, 0x00, 0x00, 0x00, 0xe7, 0xf3, 0xf9, 0xfc, 0xe0, 0xf3, 0xf9, 0x3c, 0x4e, 0xb0, 0xdf, 0xff, 0xe7, 0xe1, 0xe0, 0xff, 0xff, 0x00, 0xf8, 0x1e, 0x87, 0xc3, 0xc0, 0xf8, 0x00, 0x20, 0x3f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0xff, 0x0f, 0x77, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7e, 0x3f, 0x0f, 0x07, 0x03, 0x03, 0x01, 0x01, 0xc7, 0x7c, 0x03, 0xf8, 0xfc, 0x07, 0xf3, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x3e, 0x78, 0xf9, 0xbb, 0x63, 0xb1, 0x60, 0xe4, 0xc6, 0xc0, 0xe0, 0x20, 0xb0, 0x98, 0xcc, 0x67, 0xb0, 0xfc, 0x67, 0x01, 0x1e, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x7f, 0x0e, 0x5c, 0x3b, 0x86, 0xcc, 0xd9, 0x92, 0xb2, 0xf2, 0xf2, 0xf3, 0x19, 0xcc, 0xe6, 0xc6, 0x93, 0xf4, 0x8c, 0xb9, 0x83,
                                                               0xce, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8e, 0x8e, 0x86, 0xc6, 0x83, 0x81, 0xc6, 0x0e, 0x1e, 0x3e, 0x79, 0x77, 0xed, 0xe8, 0xc0, 0xc1, 0x81, 0x80, 0x06, 0x0e, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0xfd, 0xfb, 0x56, 0x25, 0x63, 0x0b, 0x18, 0x1c, 0x0f, 0x0f, 0x03, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x34, 0x24, 0x28, 0x00, 0x00, 0x18, 0x24, 0x18, 0x00, 0x00, 0x04, 0x34, 0x0c, 0x00, 0x00, 0x04, 0x34, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};



    static const char PROGMEM prep[PREP_FRAMES][ANIM_SIZE] = {{0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xf0, 0xf8,
    0x0c, 0x0e, 0x82, 0x83, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0x9c, 0xf6,
    0xe2, 0xc0, 0xc0, 0xc0, 0xe0, 0x1f, 0x1f, 0x1f, 0xfe, 0xff, 0xfd, 0x1c,
    0x0c, 0x0c, 0x74, 0x3c, 0x00, 0x00, 0x80, 0xf0, 0x18, 0x00, 0x60, 0x30,
    0x00, 0x04, 0x03, 0x03, 0x01, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f,
    0x7f, 0xe0, 0xe0, 0xc0, 0xe3,
                                                               0xe1, 0xc0,
                                                               0xc0, 0xe3,
                                                               0x60, 0x60,
                                                               0x60, 0x82,
                                                               0x03, 0x03,
                                                               0x43, 0xe0,
                                                               0x38, 0x10,
                                                               0x02, 0xc0,
                                                               0xe0, 0x30,
                                                               0x00, 0x00,
                                                               0x00, 0xe7,
                                                               0xf3, 0xf9,
                                                               0xfc, 0xfc,
                                                               0xee, 0xf0,
                                                               0x3f, 0x5f,
                                                               0xa7, 0xc1,
                                                               0xe0, 0xff,
                                                               0xff, 0xe0,
                                                               0xf8, 0xfe,
                                                               0x07, 0xe3,
                                                               0x00, 0x80,
                                                               0xc0, 0xc0,
                                                               0xf8, 0x00,
                                                               0x20, 0x3f,
                                                               0x1f, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x77, 0x07,
                                                               0xff, 0x7f,
                                                               0x5f, 0x9f,
                                                               0x31, 0x70,
                                                               0x06, 0x07,
                                                               0x1f, 0x40,
                                                               0x20, 0xae,
                                                               0x2c, 0x2c,
                                                               0xce, 0x0e,
                                                               0x89, 0x10,
                                                               0x01, 0xc0,
                                                               0x60, 0x10,
                                                               0x00, 0x60,
                                                               0xe0, 0xc0,
                                                               0xc0, 0xe0,
                                                               0x20, 0xa0,
                                                               0x9e, 0xdf,
                                                               0x7f, 0xae,
                                                               0xec, 0x6d,
                                                               0x00, 0x02,
                                                               0x0c, 0x00,
                                                               0x1e, 0x04,
                                                               0x09, 0x0a,
                                                               0x09, 0x08,
                                                               0x17, 0x00,
                                                               0x02, 0x10,
                                                               0x18, 0x13,
                                                               0x00, 0x04,
                                                               0x06, 0xf9,
                                                               0x72, 0x12,
                                                               0x52, 0x32,
                                                               0x93, 0xd9,
                                                               0xcc, 0x86,
                                                               0xa6, 0xf3,
                                                               0xf4, 0xec,
                                                               0x19, 0xc3,
                                                               0xee, 0xd8,
                                                               0x80, 0x60,
                                                               0x80, 0xa0,
                                                               0x00, 0x40,
                                                               0x60, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x8e, 0x8e,
                                                               0x86, 0xc6,
                                                               0x83, 0x01,
                                                               0x02, 0x02,
                                                               0x70, 0x78,
                                                               0x01, 0x83,
                                                               0xe7, 0xef,
                                                               0x6e, 0x1d,
                                                               0x3d, 0x38,
                                                               0x38, 0x30,
                                                               0x10, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0xfd, 0xfd,
                                                               0xfb, 0x56,
                                                               0x25, 0x60,
                                                               0x00, 0x10,
                                                               0x10, 0x01,
                                                               0x01, 0x01,
                                                               0x01, 0x01,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x30, 0x20,
                                                               0x24, 0x04,
                                                               0x08, 0x10,
                                                               0x20, 0x18,
                                                               0x04, 0x08,
                                                               0x00, 0x30,
                                                               0x04, 0x04,
                                                               0x0c, 0x00,
                                                               0x30, 0x04,
                                                               0x04, 0x0c,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00},
                                                              {0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x80, 0x80, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x80, 0xc0,
                                                              0xc0, 0x80, 0x00,
                                                              0x80, 0xc0, 0x08,
                                                              0x04, 0x06, 0x80,
                                                              0xc1, 0x51, 0x70,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0xc0, 0x60,
                                                              0x00, 0xfe, 0xff,
                                                              0xf3, 0xf0, 0xc0,
                                                              0xc1, 0xe0, 0xff,
                                                              0x1e, 0x1e, 0x1e,
                                                              0x1f, 0x03, 0xd0,
                                                              0xd8, 0xc0, 0xc0,
                                                              0xc0, 0x40, 0xc0,
                                                              0x10, 0x00, 0x00,
                                                              0x80, 0xc0, 0xc0,
                                                              0x00, 0x00, 0x03,
                                                              0x01, 0x00, 0x00,
                                                              0xff, 0xff, 0xff,
                                                              0xff, 0xff, 0xff,
                                                              0xff, 0xff, 0x00,
                                                              0x00, 0x80,
                                                               0x80, 0x80,
                                                               0xdf, 0x8f,
                                                               0xc1, 0xf0,
                                                               0x80, 0x87,
                                                               0xc3, 0xe0,
                                                               0xf0, 0xf8,
                                                               0x3f, 0x1f,
                                                               0x01, 0x80,
                                                               0xe1, 0x30,
                                                               0x00, 0x00,
                                                               0x00, 0xfc,
                                                               0x1e, 0x27,
                                                               0xd8, 0xef,
                                                               0xff, 0xf3,
                                                               0xf0, 0xf0,
                                                               0xff, 0xff,
                                                               0x00, 0xfc,
                                                               0x0f, 0x43,
                                                               0xe1, 0xf0,
                                                               0x00, 0x00,
                                                               0x00, 0x01,
                                                               0x01, 0x00,
                                                               0xf8, 0x0e,
                                                               0x03, 0x18,
                                                               0x08, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0xff,
                                                               0x7c, 0x3f,
                                                               0x1f, 0x07,
                                                               0x03, 0x01,
                                                               0x01, 0x00,
                                                               0x00, 0x63,
                                                               0x3e, 0x01,
                                                               0x7c, 0x7e,
                                                               0x03, 0x79,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0xe0, 0x38,
                                                               0x08, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0xfd,
                                                               0x3e, 0x78,
                                                               0xf9, 0xbb,
                                                               0x63, 0xb1,
                                                               0x60, 0xe4,
                                                               0xc6, 0xc0,
                                                               0xe0, 0x20,
                                                               0xb0, 0x90,
                                                               0xc4, 0x67,
                                                               0xb0, 0xf4,
                                                               0x67, 0x01,
                                                               0x16, 0x03,
                                                               0x01, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x1f,
                                                               0x1f, 0x0e,
                                                               0x1c, 0x1b,
                                                               0x06, 0x4c,
                                                               0x59, 0x12,
                                                               0x32, 0x72,
                                                               0x72, 0x73,
                                                               0x19, 0x4c,
                                                               0x66, 0x46,
                                                               0x13, 0x74,
                                                               0x0c, 0x39,
                                                               0x03, 0x4e,
                                                               0x78, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x32,
                                                               0x19, 0x0c,
                                                               0x36, 0x76,
                                                               0xf4, 0xf5,
                                                               0xcf, 0xbf,
                                                               0x6f, 0x40,
                                                               0x06, 0x0f,
                                                               0x0e, 0x00,
                                                               0x00, 0x00,
                                                               0x80, 0x06,
                                                               0x0e, 0x06,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0xfe,
                                                               0xfc, 0xfc,
                                                               0x56, 0x20,
                                                               0x60, 0x09,
                                                               0x1b, 0x1b,
                                                               0x0f, 0x0f,
                                                               0x06, 0x06,
                                                               0x04, 0x01,
                                                               0x01, 0x01,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x30,
                                                               0x20, 0x20,
                                                               0x04, 0x04,
                                                               0x18, 0x20,
                                                               0x10, 0x08,
                                                               0x04, 0x08,
                                                               0x30, 0x00,
                                                               0x04, 0x04,
                                                               0x0c, 0x30,
                                                               0x00, 0x04,
                                                               0x04, 0x0c,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00}};
    static const char PROGMEM tap[TAP_FRAMES][ANIM_SIZE]   = {{0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x10, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x80, 0xc0, 0xc0, 0xe0, 0xf0, 0x80, 0x00, 0x80, 0xf0, 0xf8,
    0x0c, 0x06, 0x82, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x00, 0xff, 0xff,
    0xf3, 0xf0, 0xc0, 0xc1, 0xe0, 0xff, 0xff, 0xff, 0xfe, 0x7f, 0x63, 0x30,
    0xf8, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x08, 0x10,
    0x00, 0x04, 0x03, 0x03, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xef, 0xc7, 0xe0,
                                                               0xf8, 0xc0,
                                                               0xc1, 0xe0,
                                                               0xf0, 0xf8,
                                                               0xfc, 0x1f,
                                                               0x0e, 0x00,
                                                               0xc3, 0xe1,
                                                               0x30, 0x00,
                                                               0x00, 0xc1,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0xff,
                                                               0xff, 0xff,
                                                               0xff, 0xff,
                                                               0xff, 0xff,
                                                               0x3f, 0x4f,
                                                               0xbf, 0xdf,
                                                               0xff, 0xe7,
                                                               0xe1, 0xe0,
                                                               0xff, 0xff,
                                                               0x00, 0xf8,
                                                               0x1e, 0x87,
                                                               0xc3, 0xe0,
                                                               0xf8, 0x0e,
                                                               0x24, 0x28,
                                                               0x0f, 0x40,
                                                               0x70, 0x10,
                                                               0x20, 0x77,
                                                               0x07, 0xff,
                                                               0x7f, 0x5f,
                                                               0x9f, 0x31,
                                                               0x70, 0x06,
                                                               0x07, 0x1f,
                                                               0x40, 0x20,
                                                               0xae, 0x2c,
                                                               0x2c, 0xce,
                                                               0x0e, 0x89,
                                                               0x10, 0x01,
                                                               0xc0, 0x60,
                                                               0x10, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0xfe,
                                                               0x3f, 0x1f,
                                                               0x0e, 0x6c,
                                                               0x4d, 0x00,
                                                               0x02, 0x0c,
                                                               0xc0, 0x9e,
                                                               0xa4, 0xa9,
                                                               0xaa, 0xa9,
                                                               0x88, 0x97,
                                                               0x40, 0x02,
                                                               0x10, 0xf8,
                                                               0x73, 0x60,
                                                               0x04, 0x06,
                                                               0x01, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x77,
                                                               0x66, 0x0c,
                                                               0x09, 0x80,
                                                               0x8c, 0xfb,
                                                               0xc1, 0x88,
                                                               0x18, 0x70,
                                                               0x20, 0x42,
                                                               0x02, 0x02,
                                                               0x06, 0x0e,
                                                               0x03, 0x22,
                                                               0x32, 0x19,
                                                               0x00, 0x04,
                                                               0x06, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0xc7,
                                                               0xc2, 0xc0,
                                                               0xc0, 0xa4,
                                                               0x61, 0xc5,
                                                               0xe1, 0xe4,
                                                               0x0c, 0x1f,
                                                               0x9e, 0x3c,
                                                               0x78, 0x70,
                                                               0xf0, 0xe0,
                                                               0xc0, 0x40,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x3c,
                                                               0x3e, 0x7e,
                                                               0x7c, 0x31,
                                                               0x03, 0x12,
                                                               0x35, 0x0c,
                                                               0x1c, 0x0e,
                                                               0x07, 0x01,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x34, 0x24,
                                                               0x28, 0x00,
                                                               0x00, 0x18,
                                                               0x24, 0x18,
                                                               0x00, 0x00,
                                                               0x04, 0x34,
                                                               0x0c, 0x00,
                                                               0x00, 0x04,
                                                               0x34, 0x0c,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00},
                                                              {0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0xe0, 0x70, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0xc0,
                                                              0xc0, 0x40, 0x40,
                                                              0x20, 0x20, 0x80,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x80,
                                                              0xc0, 0xc0, 0xe1,
                                                              0xf0, 0x80, 0x00,
                                                              0x80, 0xf0, 0xe0,
                                                              0x00, 0x00, 0x80,
                                                              0x80, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0xff, 0xff,
                                                              0xf3, 0xf0, 0xc0,
                                                              0xc1, 0xe0, 0xff,
                                                              0xff, 0xff, 0xfe,
                                                              0x7f, 0x63, 0x30,
                                                              0x18, 0x00, 0x00,
                                                              0x00, 0x80, 0x00,
                                                              0x10, 0x08, 0x00,
                                                              0x4c, 0x08, 0x10,
                                                              0x00, 0x00, 0x00,
                                                              0x60, 0xc0, 0x00,
                                                              0xff, 0xff, 0xff,
                                                              0xff, 0xff, 0xff,
                                                              0xff, 0xff, 0xef,
                                                              0xc7, 0xe0,
                                                               0xf8, 0xc0,
                                                               0xc0, 0xe0,
                                                               0xf0, 0xf8,
                                                               0xfc, 0x1f,
                                                               0x0e, 0x00,
                                                               0x80, 0x00,
                                                               0x00, 0x04,
                                                               0x06, 0x06,
                                                               0x02, 0x02,
                                                               0x02, 0x01,
                                                               0x00, 0xff,
                                                               0xff, 0xff,
                                                               0xff, 0xff,
                                                               0xff, 0xff,
                                                               0x3f, 0x4f,
                                                               0xbf, 0xdf,
                                                               0xff, 0xe7,
                                                               0xe1, 0xe0,
                                                               0xff, 0xff,
                                                               0x00, 0xf8,
                                                               0x1e, 0x87,
                                                               0xc3, 0xe0,
                                                               0xf8, 0x0e,
                                                               0x04, 0x00,
                                                               0x00, 0x40,
                                                               0x70, 0x10,
                                                               0x20, 0x77,
                                                               0x07, 0xff,
                                                               0x7f, 0x5f,
                                                               0x9f, 0x31,
                                                               0x70, 0x06,
                                                               0x07, 0x1f,
                                                               0x40, 0x20,
                                                               0xae, 0x2c,
                                                               0x2c, 0xce,
                                                               0x0e, 0x89,
                                                               0x10, 0x01,
                                                               0xc0, 0x60,
                                                               0x10, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0xfe,
                                                               0x3f, 0x1f,
                                                               0x0e, 0x6c,
                                                               0x4d, 0x00,
                                                               0x02, 0x0c,
                                                               0xc0, 0x9e,
                                                               0xa4, 0xa9,
                                                               0xaa, 0xa9,
                                                               0x88, 0x97,
                                                               0x40, 0x02,
                                                               0x10, 0xf8,
                                                               0x73, 0x60,
                                                               0x04, 0x06,
                                                               0x01, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x77,
                                                               0x66, 0x0c,
                                                               0x09, 0x80,
                                                               0x8c, 0xfb,
                                                               0xc1, 0x88,
                                                               0x18, 0x70,
                                                               0x20, 0x42,
                                                               0x02, 0x02,
                                                               0x06, 0x0e,
                                                               0x03, 0x22,
                                                               0x32, 0x19,
                                                               0x00, 0x04,
                                                               0x06, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0xc7,
                                                               0xc2, 0xc0,
                                                               0xc0, 0xa4,
                                                               0x61, 0xc5,
                                                               0xe1, 0xe4,
                                                               0x0c, 0x1f,
                                                               0x9e, 0x3c,
                                                               0x78, 0x70,
                                                               0xf0, 0xe0,
                                                               0xc0, 0x40,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x3c,
                                                               0x3e, 0x7e,
                                                               0x7c, 0x31,
                                                               0x03, 0x12,
                                                               0x35, 0x0c,
                                                               0x1c, 0x0e,
                                                               0x07, 0x01,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x34, 0x24,
                                                               0x28, 0x00,
                                                               0x00, 0x18,
                                                               0x24, 0x18,
                                                               0x00, 0x00,
                                                               0x04, 0x34,
                                                               0x0c, 0x00,
                                                               0x00, 0x04,
                                                               0x34, 0x0c,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00},
                                                              {0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x80, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x80, 0x00,
                                                              0x40, 0x40, 0x20,
                                                              0x20, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x80,
                                                              0xc0, 0xc0, 0xe3,
                                                              0xf7, 0x9c, 0x00,
                                                              0x80, 0xc0, 0x03,
                                                              0x00, 0x0c, 0x8e,
                                                              0xc2, 0xf6, 0xfc,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x08,
                                                              0x0c, 0xff, 0xff,
                                                              0xf3, 0xf0, 0xc0,
                                                              0xc1, 0xe0, 0xff,
                                                              0xfe, 0xfe, 0xfe,
                                                              0x7f, 0x6f, 0xb7,
                                                              0xf9, 0x00, 0x00,
                                                              0x00, 0xc0, 0x60,
                                                              0x78, 0x18, 0x0c,
                                                              0x4c, 0x00, 0x00,
                                                              0x00, 0xc0, 0x80,
                                                              0x00, 0x00, 0x00,
                                                              0xff, 0xff, 0xff,
                                                              0xff, 0xff, 0xff,
                                                              0xff, 0xff, 0xef,
                                                              0xc7, 0xe0,
                                                               0xf8, 0xc0,
                                                               0xc3, 0xe1,
                                                               0xf0, 0xf8,
                                                               0xfc, 0x1f,
                                                               0x0e, 0x00,
                                                               0x80, 0x30,
                                                               0x78, 0x3e,
                                                               0x06, 0x02,
                                                               0xa2, 0x13,
                                                               0x00, 0x00,
                                                               0x00, 0xff,
                                                               0xff, 0xff,
                                                               0xff, 0xff,
                                                               0xff, 0xff,
                                                               0x3f, 0x4f,
                                                               0xbf, 0xdf,
                                                               0xff, 0xe7,
                                                               0xe1, 0xe0,
                                                               0xff, 0xff,
                                                               0x00, 0xf8,
                                                               0x1e, 0x87,
                                                               0xc3, 0xe0,
                                                               0xf8, 0x0e,
                                                               0x1f, 0x13,
                                                               0x01, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x77,
                                                               0x07, 0xff,
                                                               0x7f, 0x5f,
                                                               0x9f, 0x31,
                                                               0x70, 0x06,
                                                               0x07, 0x1f,
                                                               0x40, 0x20,
                                                               0xae, 0x2c,
                                                               0x2c, 0xce,
                                                               0x0e, 0x89,
                                                               0x10, 0x01,
                                                               0xc0, 0x60,
                                                               0x10, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0xfe,
                                                               0x3f, 0x1f,
                                                               0x0e, 0x6c,
                                                               0x4d, 0x00,
                                                               0x02, 0x0c,
                                                               0xc0, 0x9e,
                                                               0xa4, 0xa9,
                                                               0xaa, 0xa9,
                                                               0x88, 0x97,
                                                               0x40, 0x02,
                                                               0x10, 0xf8,
                                                               0x73, 0x60,
                                                               0x04, 0x06,
                                                               0x01, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x77,
                                                               0x66, 0x0c,
                                                               0x09, 0x80,
                                                               0x8c, 0xfb,
                                                               0xc1, 0x88,
                                                               0x18, 0x70,
                                                               0x20, 0x42,
                                                               0x02, 0x02,
                                                               0x06, 0x0e,
                                                               0x03, 0x22,
                                                               0x32, 0x19,
                                                               0x00, 0x04,
                                                               0x06, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0xc7,
                                                               0xc2, 0xc0,
                                                               0xc0, 0xa4,
                                                               0x61, 0xc5,
                                                               0xe1, 0xe4,
                                                               0x0c, 0x1f,
                                                               0x9e, 0x3c,
                                                               0x78, 0x70,
                                                               0xf0, 0xe0,
                                                               0xc0, 0x40,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x3c,
                                                               0x3e, 0x7e,
                                                               0x7c, 0x31,
                                                               0x03, 0x12,
                                                               0x35, 0x0c,
                                                               0x1c, 0x0e,
                                                               0x07, 0x01,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x34, 0x24,
                                                               0x28, 0x00,
                                                               0x00, 0x18,
                                                               0x24, 0x18,
                                                               0x00, 0x00,
                                                               0x04, 0x34,
                                                               0x0c, 0x00,
                                                               0x00, 0x04,
                                                               0x34, 0x0c,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00},
                                                              {0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x80, 0x80, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x80, 0xc0,
                                                              0xc0, 0x80, 0x00,
                                                              0x80, 0xc0, 0x08,
                                                              0x04, 0x06, 0x80,
                                                              0xc1, 0x51, 0x70,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0xc0, 0x60,
                                                              0x00, 0xfe, 0xff,
                                                              0xf3, 0xf0, 0xc0,
                                                              0xc1, 0xe0, 0xff,
                                                              0xfe, 0xfe, 0xfe,
                                                              0x7f, 0x63, 0xb0,
                                                              0xf8, 0x00, 0x00,
                                                              0x00, 0xc0, 0xe0,
                                                              0xf0, 0x00, 0x80,
                                                              0xc0, 0x00, 0x00,
                                                              0x00, 0x00, 0x03,
                                                              0x01, 0x00, 0x00,
                                                              0xff, 0xff, 0xff,
                                                              0xff, 0xff, 0xff,
                                                              0xff, 0xff, 0xef,
                                                              0xc7, 0xe0,
                                                               0xf8, 0xc0,
                                                               0xc3, 0xe1,
                                                               0xf0, 0xf8,
                                                               0xfc, 0x1f,
                                                               0x0f, 0x00,
                                                               0xc0, 0xf0,
                                                               0x78, 0x3a,
                                                               0x06, 0x00,
                                                               0xe0, 0x30,
                                                               0x00, 0x00,
                                                               0x00, 0xff,
                                                               0xff, 0xff,
                                                               0xff, 0xff,
                                                               0xff, 0xff,
                                                               0x3f, 0x4f,
                                                               0xbf, 0xdf,
                                                               0xff, 0xe7,
                                                               0xe1, 0xe0,
                                                               0xff, 0xff,
                                                               0x00, 0xf8,
                                                               0x1e, 0x87,
                                                               0xc3, 0xe0,
                                                               0xf8, 0x0e,
                                                               0x03, 0x18,
                                                               0x08, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x77,
                                                               0x07, 0xff,
                                                               0x7f, 0x5f,
                                                               0x9f, 0x31,
                                                               0x70, 0x06,
                                                               0x07, 0x1f,
                                                               0x40, 0x20,
                                                               0xae, 0x2c,
                                                               0x2c, 0xce,
                                                               0x0e, 0x89,
                                                               0x10, 0x01,
                                                               0xc0, 0x60,
                                                               0x10, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0xfe,
                                                               0x3f, 0x1f,
                                                               0x0e, 0x6c,
                                                               0x4d, 0x00,
                                                               0x02, 0x0c,
                                                               0xc0, 0x9e,
                                                               0xa4, 0xa9,
                                                               0xaa, 0xa9,
                                                               0x88, 0x97,
                                                               0x40, 0x02,
                                                               0x10, 0xf8,
                                                               0x73, 0x60,
                                                               0x04, 0x06,
                                                               0x01, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x77,
                                                               0x66, 0x0c,
                                                               0x09, 0x80,
                                                               0x8c, 0xfb,
                                                               0xc1, 0x88,
                                                               0x18, 0x70,
                                                               0x20, 0x42,
                                                               0x02, 0x02,
                                                               0x06, 0x0e,
                                                               0x03, 0x22,
                                                               0x32, 0x19,
                                                               0x00, 0x04,
                                                               0x06, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0xc7,
                                                               0xc2, 0xc0,
                                                               0xc0, 0xa4,
                                                               0x61, 0xc5,
                                                               0xe1, 0xe4,
                                                               0x0c, 0x1f,
                                                               0x9e, 0x3c,
                                                               0x78, 0x70,
                                                               0xf0, 0xe0,
                                                               0xc0, 0x40,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x3c,
                                                               0x3e, 0x7e,
                                                               0x7c, 0x31,
                                                               0x03, 0x12,
                                                               0x35, 0x0c,
                                                               0x1c, 0x0e,
                                                               0x07, 0x01,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x34, 0x24,
                                                               0x28, 0x00,
                                                               0x00, 0x18,
                                                               0x24, 0x18,
                                                               0x00, 0x00,
                                                               0x04, 0x34,
                                                               0x0c, 0x00,
                                                               0x00, 0x04,
                                                               0x34, 0x0c,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00},
                                                              {0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x80, 0xc0, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0xc0, 0xf0, 0xf8,
                                                              0x0c, 0x0e, 0x82,
                                                              0x83, 0x03, 0x01,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x00, 0x00, 0x00,
                                                              0x80, 0xc0, 0xe0,
                                                              0xf0, 0x9c, 0xf6,
                                                              0xe2, 0xc0, 0xc0,
                                                              0xc0, 0xe0, 0xff,
                                                              0xff, 0xff, 0xfe,
                                                              0x7f, 0x61, 0xb0,
                                                              0xf8, 0x00, 0x00,
                                                              0x00, 0x80, 0xc0,
                                                              0x00, 0x00, 0x80,
                                                              0xc0, 0x00, 0x00,
                                                              0x00, 0x04, 0x03,
                                                              0x03, 0x01, 0x00,
                                                              0xff, 0xff, 0xff,
                                                              0xff, 0xff, 0xff,
                                                              0xff, 0xff, 0xef,
                                                              0xc7, 0xe0,
                                                               0xf8, 0xc0,
                                                               0xc3, 0xe1,
                                                               0xf0, 0xf8,
                                                               0xfc, 0x1f,
                                                               0x00, 0x00,
                                                               0xc3, 0xf1,
                                                               0x38, 0x10,
                                                               0x00, 0xc0,
                                                               0xe0, 0x30,
                                                               0x00, 0x00,
                                                               0x00, 0xff,
                                                               0xff, 0xff,
                                                               0xff, 0xff,
                                                               0xff, 0xff,
                                                               0x3f, 0x4f,
                                                               0xbf, 0xdf,
                                                               0xff, 0xe7,
                                                               0xe1, 0xe0,
                                                               0xff, 0xff,
                                                               0x00, 0xf8,
                                                               0x1e, 0x87,
                                                               0xc3, 0xc0,
                                                               0xf8, 0x00,
                                                               0x20, 0x3f,
                                                               0x1f, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x77,
                                                               0x07, 0xff,
                                                               0x7f, 0x5f,
                                                               0x9f, 0x31,
                                                               0x70, 0x06,
                                                               0x07, 0x1f,
                                                               0x40, 0x20,
                                                               0xae, 0x2c,
                                                               0x2c, 0xce,
                                                               0x0e, 0x89,
                                                               0x10, 0x01,
                                                               0xc0, 0x60,
                                                               0x10, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0xfe,
                                                               0x3f, 0x1f,
                                                               0x0e, 0x6c,
                                                               0x4d, 0x00,
                                                               0x02, 0x0c,
                                                               0xc0, 0x9e,
                                                               0xa4, 0xa9,
                                                               0xaa, 0xa9,
                                                               0x88, 0x97,
                                                               0x40, 0x02,
                                                               0x10, 0xf8,
                                                               0x73, 0x60,
                                                               0x04, 0x06,
                                                               0x01, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x77,
                                                               0x66, 0x0c,
                                                               0x09, 0x80,
                                                               0x8c, 0xfb,
                                                               0xc1, 0x88,
                                                               0x18, 0x70,
                                                               0x20, 0x42,
                                                               0x02, 0x02,
                                                               0x06, 0x0e,
                                                               0x03, 0x22,
                                                               0x32, 0x19,
                                                               0x00, 0x04,
                                                               0x06, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0xc7,
                                                               0xc2, 0xc0,
                                                               0xc0, 0xa4,
                                                               0x61, 0xc5,
                                                               0xe1, 0xe4,
                                                               0x0c, 0x1f,
                                                               0x9e, 0x3c,
                                                               0x78, 0x70,
                                                               0xf0, 0xe0,
                                                               0xc0, 0x40,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x3c,
                                                               0x3e, 0x7e,
                                                               0x7c, 0x31,
                                                               0x03, 0x12,
                                                               0x35, 0x0c,
                                                               0x1c, 0x0e,
                                                               0x07, 0x01,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x34, 0x24,
                                                               0x28, 0x00,
                                                               0x00, 0x18,
                                                               0x24, 0x18,
                                                               0x00, 0x00,
                                                               0x04, 0x34,
                                                               0x0c, 0x00,
                                                               0x00, 0x04,
                                                               0x34, 0x0c,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00, 0x00,
                                                               0x00}};

    void animation_phase(void) {
        switch (get_highest_layer(layer_state)) {
            case _QWERTY:
                current_idle_frame = (current_idle_frame + 1) % IDLE_FRAMES;
                oled_write_raw_P(idle[abs((IDLE_FRAMES - 1) - current_idle_frame)], ANIM_SIZE);
                break;
            case _LOWER:
                current_tap_frame = (current_tap_frame + 1) % TAP_FRAMES;
                oled_write_raw_P(tap[abs((TAP_FRAMES - 1) - current_tap_frame)],
                ANIM_SIZE); break;
            case _RAISE:
                current_prep_frame = (current_prep_frame + 1) % PREP_FRAMES;
                oled_write_raw_P(prep[abs((PREP_FRAMES - 1) - current_prep_frame)],
                ANIM_SIZE); break;
            default:
                current_idle_frame = (current_idle_frame + 1) % IDLE_FRAMES;
                oled_write_raw_P(idle[abs((IDLE_FRAMES - 1) - current_idle_frame)], ANIM_SIZE);
                break;
        }
    }

    if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
        anim_timer = timer_read32();

        animation_phase();
    }
}

void render_logo(void) {
    static const char PROGMEM logo[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0xf8, 0xf8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xf8, 0xf8, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x3f, 0x30, 0x30, 0x30, 0x31, 0x31, 0x30, 0x30, 0x30, 0x3f, 0x3f, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xfe, 0x06, 0x06, 0x06, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc7, 0xc7, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x80, 0x80, 0x80, 0x8f, 0x8f, 0x80, 0x80, 0x80, 0xf8, 0xf8, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe1, 0xf1, 0x71, 0x71, 0x71, 0x71, 0x71, 0x71, 0x71, 0x71, 0x71, 0x71, 0x70, 0x70, 0x70, 0x7f, 0x7f, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x70, 0x70, 0x70, 0x70, 0x70, 0x7f, 0x7f, 0x7f, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x00, 0x00, 0x00, 0x7f, 0x7f, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xfe, 0x00, 0x00, 0x00, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0xfe, 0xfe, 0xfe, 0x0e, 0x0e, 0x0e, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0xfe, 0xfe, 0x0e, 0x0e, 0x0e, 0x8e, 0x8e, 0x8e, 0x8e, 0x8e, 0x8e, 0x8e, 0x8e, 0x8e, 0x8e, 0x8f, 0x87, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x01, 0x01, 0x01, 0xf1, 0xf1, 0x01, 0x01, 0x01, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0xe3, 0xe3, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x60, 0x60, 0x60, 0x7f, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0xfc, 0xfc, 0x0c, 0x0c, 0x0c, 0x8c, 0x8c, 0x0c, 0x0c, 0x0c, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1f, 0x1f, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    oled_write_raw_P(logo, sizeof(logo));
}

bool oled_task_user(void) {
    if (keyboard_in_sleep) {
        oled_off();
        return false;
    }

    if (is_keyboard_master()) {
        render_anim();
        oled_set_cursor(0, 13);
        render_status();
    } else {
        render_logo();
        oled_scroll_left();
    }

    return false;
}
#endif

#ifdef RGBLIGHT_ENABLE
// Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

void keyboard_post_init_user(void) {
    switchNumLock(host_keyboard_led_state().num_lock);
    if (rgblight_is_enabled()) {
        rgb_enabled = 1;
    }
}

void matrix_scan_user(void) {
    if (is_keyboard_master()) {
        if (keyboard_in_sleep == 0 && timer_elapsed(sleep_timer) >= sleep_timeout) {
            keyboard_sleep();
        }
    }
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        default:
            return TAPPING_TERM;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
// #ifdef CONSOLE_ENABLE
//     uprintf("0x%04X,%u,%u,%u,%b,0x%02X,0x%02X,%u\n", keycode, record->event.key.row, record->event.key.col, get_highest_layer(layer_state), record->event.pressed, get_mods(), get_oneshot_mods(), record->tap.count);
// #endif

    if (is_keyboard_master()) {
        sleep_timer = timer_read();
        if (keyboard_in_sleep) {
            keyboard_wakeup();
        }
    }

    switch (keycode) {
        case RGB_TOG:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                if (rgblight_is_enabled()) {
                    rgb_enabled = 0;
                } else {
                    rgb_enabled = 1;
                }
            }
#endif
            return true;
            break;

        case CLRPCK:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_LSFT(SS_TAP(X_C))));
            }
            break;

        case LNG_SW:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_TAP(X_SPC)));
            }
            break;

        case CHROME:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_TAP(X_6)));
            }
            break;

        case VSC:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_TAP(X_3)));
            }
            break;

        case TERMINAL:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_TAP(X_2)));
            }
            break;

        case EXPLORER:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_TAP(X_1)));
            }
            break;

        case SCRCUT:
            if (record->event.pressed) {
                // when keycode SCRCUT is pressed
                SEND_STRING(SS_LGUI(SS_LSFT(SS_TAP(X_S))));
            } else {
                // when keycode SCRCUT is released
            }
            break;
    }

    return true;
}
