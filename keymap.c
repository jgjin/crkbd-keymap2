#include QMK_KEYBOARD_H

enum layers {
    _QWERTY,
    _RAISE,
    _LOWER
};
#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    QUOTE,
    NINE,
    ZERO,
    SIGN,
    RGB_CUD,
    RGB_SMP,
    RGB_WDE,
    RGB_SPL
};

#define LALTT LALT_T(KC_BSPC)
#define RCMDT RCMD_T(KC_DEL)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_ESC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,   QUOTE,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LEFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RGHT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            LALTT, KC_LSFT,   LOWER,      RAISE,  KC_SPC,   RCMDT
                                      //`--------------------------'  `--------------------------'

  ),

  [_RAISE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,  KC_GRV, KC_LCBR, KC_LPRN, KC_LBRC, KC_LABK,                      KC_RABK, KC_RBRC, KC_RPRN, KC_RCBR, KC_BSLS, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    NINE,    ZERO,    SIGN,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LEFT, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, XXXXXXX,                      XXXXXXX, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_RGHT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            LALTT, KC_LSFT,  KC_ENT,    XXXXXXX,  KC_SPC,   RCMDT
                                      //`--------------------------'  `--------------------------'
  ),

  [_LOWER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, RGB_TOG, RGB_CUD, RGB_SMP, RGB_WDE, RGB_SPL,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LEFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RGHT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            LALTT, KC_LSFT, XXXXXXX,     KC_ENT,  KC_SPC,   RCMDT
                                      //`--------------------------'  `--------------------------'
  )
};

void keyboard_post_init_user(void) {
    rgb_matrix_disable();
    rgb_matrix_sethsv(192, 192, 128);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    const uint8_t mod_state = get_mods();
    uint16_t custom_keycode;
    switch (keycode) {
    case QUOTE: ;
        custom_keycode = KC_DOUBLE_QUOTE;
        if (mod_state & MOD_MASK_SHIFT) {
            if (record->event.pressed) {
                set_mods(mod_state & ~MOD_MASK_SHIFT);
                tap_code(KC_QUOTE);
                set_mods(mod_state);
            }
        } else {
            if (record->event.pressed) {
                register_code16(custom_keycode);
            } else {
                unregister_code16(custom_keycode);
            }
        }
        return false;
    case NINE: ;
        custom_keycode = KC_9;
        if (mod_state & MOD_MASK_SHIFT) {
            if (record->event.pressed) {
                tap_code(KC_MINUS);  // KC_UNDERSCORE
            }
        } else {
            if (record->event.pressed) {
                register_code16(custom_keycode);
            } else {
                unregister_code16(custom_keycode);
            }
        }
        return false;
    case ZERO: ;
        custom_keycode = KC_0;
        if (mod_state & MOD_MASK_SHIFT) {
            if (record->event.pressed) {
                set_mods(mod_state & ~MOD_MASK_SHIFT);
                tap_code(KC_EQUAL);
                set_mods(mod_state);
            }
        } else {
            if (record->event.pressed) {
                register_code16(custom_keycode);
            } else {
                unregister_code16(custom_keycode);
            }
        }
        return false;
    case SIGN: ;
        custom_keycode = KC_MINUS;
        if (mod_state & MOD_MASK_SHIFT) {
            if (record->event.pressed) {
                tap_code(KC_EQUAL);  // KC_PLUS
            }
        } else {
            if (record->event.pressed) {
                register_code16(custom_keycode);
            } else {
                unregister_code16(custom_keycode);
            }
        }
        return false;
    case RGB_CUD: ;
        if (record->event.pressed) {
            rgb_matrix_mode(RGB_MATRIX_CYCLE_UP_DOWN);
        }
        return false;
    case RGB_SMP: ;
        if (record->event.pressed) {
            rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE_SIMPLE);
        }
        return false;
    case RGB_WDE: ;
        if (record->event.pressed) {
            rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE);
        }
        return false;
    case RGB_SPL: ;
        if (record->event.pressed) {
            rgb_matrix_mode(RGB_MATRIX_SOLID_MULTISPLASH);
        }
        return false;
    }
    return true;
}
