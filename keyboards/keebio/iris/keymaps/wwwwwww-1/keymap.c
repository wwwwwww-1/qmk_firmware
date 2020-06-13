#include QMK_KEYBOARD_H

#define ____    KC_TRNS
#define ______  KC_TRNS
#define RGB_RMD RGB_RMOD
#define OS_LSFT OSM(MOD_LSFT)
#define OS_LCTL OSM(MOD_LCTL)
#define OS_RGUI OSM(MOD_RGUI)
#define OS_RALT OSM(MOD_RALT)
#define TG_NUM  TG(_NUMPAD) //temp key, will eventually want to do more than just toggle layer
#define TAB_AR  LT(_ARROW, KC_TAB)
#define TD_NXPR TD(CT_NEXT_PREV)
#define GUI_SYM TD(CT_GUI_SYMBOL)

static bool pass_esc = true;

enum my_layers {
  _WORKMAN = 0,
  _NUMPAD,
  _ARROW,
  _SYMBOL,
  _ADJUST
};

enum custom_keycodes {
  WORKMAN = SAFE_RANGE,
  ENC_MOD
};

enum tapdance_states {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4
};

enum tapdance_keycodes {
  CT_NEXT_PREV = 0,
  CT_GUI_SYMBOL
};

typedef struct {
  bool is_press_action;
  int state;
} tap;

int cur_dance (qk_tap_dance_state_t *state);

void guisym_finished (qk_tap_dance_state_t *state, void *user_data);
void guisym_reset (qk_tap_dance_state_t *state, void *user_data);

qk_tap_dance_action_t tap_dance_actions[] = {
  [CT_NEXT_PREV] = ACTION_TAP_DANCE_DOUBLE(KC_MNXT, KC_MPRV),
  [CT_GUI_SYMBOL] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, guisym_finished, guisym_reset, 200)
};

const rgblight_segment_t PROGMEM my_ctrl_layer[] = RGBLIGHT_LAYER_SEGMENTS( {0, 1, HSV_BLUE} );
const rgblight_segment_t PROGMEM my_gui_layer[] = RGBLIGHT_LAYER_SEGMENTS( {5, 1, HSV_GREEN} );
const rgblight_segment_t PROGMEM my_shift_layer[] = RGBLIGHT_LAYER_SEGMENTS( {6, 1, HSV_RED} );
const rgblight_segment_t PROGMEM my_alt_layer[] = RGBLIGHT_LAYER_SEGMENTS( {11, 1, HSV_PURPLE} );
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS( {0, 6, HSV_GOLD} );
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS( {6, 6, HSV_SPRINGGREEN} );

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_layer1_layer,
    my_layer2_layer,
    my_gui_layer,
    my_shift_layer,
    my_ctrl_layer,
    my_alt_layer
);

// New encoder code
typedef enum {
    ENC_MODE_VOLUME = 0,
    ENC_MODE_WORD_NAV,
//    ENC_MODE_LEFT_RIGHT,
//    ENC_MODE_UP_DOWN,
//    ENC_MODE_PAGING,
    _ENC_MODE_LAST  // Do not use, except for looping through enum values
} encoder_mode_t;

encoder_mode_t encoder_mode;

void cycle_encoder_mode(bool reverse);
void encoder_action_volume(uint8_t clockwise);
void encoder_action_word_nav(uint8_t clockwise);
//void encoder_action_left_right(uint8_t clockwise);
//void encoder_action_up_down(uint8_t clockwise);
//void encoder_action_paging(uint8_t clockwise);
void encoder_action(encoder_mode_t mode, uint8_t clockwise);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_WORKMAN] = LAYOUT(
    TD_NXPR, KC_1, KC_2, KC_3, KC_4, KC_5,                  KC_6, KC_7, KC_8,    KC_9,   KC_0,    KC_MPLY,
    KC_GRV,  KC_Q, KC_D, KC_R, KC_W, KC_B,                  KC_J, KC_F, KC_U,    KC_P,   KC_SCLN, KC_BSPC,
    TAB_AR,  KC_A, KC_S, KC_H, KC_T, KC_G,                  KC_Y, KC_N, KC_E,    KC_O,   KC_I,    KC_QUOT,
    TG_NUM,  KC_Z, KC_X, KC_M, KC_C, KC_V, KC_ESC, ENC_MOD, KC_K, KC_L, KC_COMM, KC_DOT, KC_SLSH, KC_BSLS,
                      OS_LCTL, GUI_SYM, KC_SPC,        OS_LSFT, KC_ENT, OS_RALT
  ),

  [_NUMPAD] = LAYOUT(
    _______, ____, ____, ____, ____, ____,                  ____, ______, ______, ______, _______, _______,
    _______, ____, ____, ____, ____, ____,                  ____, KC_P7,  KC_P8,  KC_P9,  KC_EQL,  _______,
    _______, ____, ____, ____, ____, ____,                  ____, KC_P4,  KC_P5,  KC_P6,  KC_PLUS, _______,
    _______, ____, ____, ____, ____, ____, ______,  ______, ____, KC_P1,  KC_P2,  KC_P3,  KC_MINS, _______,
                    _______, _______, _______,         _______, _______, KC_P0
  ),

  [_ARROW] = LAYOUT(
    _______, ____, ____, ____, ____, ____,                  _______, _______, _______, _______, ____, _______,
    _______, ____, ____, ____, ____, ____,                  _______, KC_HOME, KC_END,  _______, ____, _______,
    _______, ____, ____, ____, ____, ____,                  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, ____, MO(_ADJUST),
    _______, ____, ____, ____, ____, ____, ______,  ______, _______, KC_PGDN, KC_PGUP, _______, ____, _______,
                    _______, _______, _______,         _______, _______, _______
  ),

  [_SYMBOL] = LAYOUT(
    ____, _______, ______, _______, _______, _______,              _______, _______, _______, _______, _______, _______,
    ____, KC_EXLM, KC_AT,  KC_HASH, KC_DLR,  KC_PERC,              KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
    ____, _______, ______, KC_EQL,  KC_MINS, KC_LBRC,              KC_RBRC, _______, _______, _______, _______, _______,
    ____, _______, ______, KC_PLUS, KC_UNDS, KC_LCBR, ____,  ____, KC_RCBR, _______, _______, _______, _______, _______,
                              _______, _______, _______,       _______, _______, _______
  ),

  [_ADJUST] = LAYOUT(
    RESET,  ____, _______, _______, _______, _______,              _______, _______, _______, _______, _______, _______,
    ______, ____, WORKMAN, DM_REC1, DM_REC2, _______,              _______, _______, _______, _______, _______, _______,
    ______, ____, _______, DM_PLY1, DM_PLY2, DM_RSTP,              RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, _______,
    ______, ____, _______, _______, _______, _______, ____,  ____, _______, RGB_RMD, RGB_HUD, RGB_SAD, RGB_VAD, _______,
                              _______, _______, _______,       _______, _______, _______
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case WORKMAN:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_WORKMAN);
      }
      return false;
      break;
    case KC_ESC:
      pass_esc = true;
      if (record->event.pressed) {
        if (get_oneshot_mods() && !has_oneshot_mods_timed_out()) {
          clear_oneshot_mods();
          pass_esc = false;
        }
        if (layer_state_is(_SYMBOL)) {
          layer_off(_SYMBOL);
          pass_esc = false;
        }
      }
      return pass_esc;
      break;
    case ENC_MOD:
      if (record->event.pressed) {
        cycle_encoder_mode(false);
      }
      return false;
      break;
  }
  return true;
}

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    else if (index == 1) {
        encoder_action(encoder_mode, clockwise);
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _SYMBOL));
    rgblight_set_layer_state(1, layer_state_cmp(state, _NUMPAD));
    return state;
}

void oneshot_mods_changed_user(uint8_t mods) {
    rgblight_set_layer_state(2, mods & MOD_MASK_GUI);
    rgblight_set_layer_state(3, mods & MOD_MASK_SHIFT);
    rgblight_set_layer_state(4, mods & MOD_MASK_CTRL);
    rgblight_set_layer_state(5, mods & MOD_MASK_ALT);
}

void keyboard_post_init_user(void) {
    encoder_mode = ENC_MODE_VOLUME;
    rgblight_layers = my_rgb_layers;
    set_single_persistent_default_layer(_WORKMAN);
    layer_clear();
}

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (!state->pressed) {
      return SINGLE_TAP;
    } else {
      return SINGLE_HOLD;
    }
  } else if (state->count == 2) {
    if (state->pressed) {
      return DOUBLE_HOLD;
    } else {
      return DOUBLE_TAP;
    }
  }
  else return 8;
}

// GUI_SYM tapdance functions
static tap guisym_tap_state = {
  .is_press_action = true,
  .state = 0
};

void guisym_finished (qk_tap_dance_state_t *state, void *user_data) {
  guisym_tap_state.state = cur_dance(state);
  switch (guisym_tap_state.state) {
    case SINGLE_TAP: 
      set_oneshot_mods(MOD_LGUI | get_oneshot_mods());
      break;
    case SINGLE_HOLD: 
      register_code(KC_LGUI);
      break;
    case DOUBLE_TAP: 
      set_oneshot_layer(_SYMBOL, ONESHOT_START);
      clear_oneshot_layer_state(ONESHOT_PRESSED);
      break;
    case DOUBLE_HOLD:
      layer_on(_SYMBOL);
      break;
  }
}

void guisym_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (guisym_tap_state.state) {
    case SINGLE_HOLD:
      unregister_code(KC_LGUI);
      break;
    case DOUBLE_HOLD:
      layer_off(_SYMBOL);
      break;
  }
  guisym_tap_state.state = 0;
}

// New encoder code
void cycle_encoder_mode(bool reverse) {
    if (reverse) {
        encoder_mode = (encoder_mode == 0) ? (_ENC_MODE_LAST - 1) : (encoder_mode - 1);
    } else {
        encoder_mode = (encoder_mode == (_ENC_MODE_LAST - 1)) ? 0 : (encoder_mode + 1);
    }
}

void encoder_action_volume(uint8_t clockwise) {
    if (clockwise) {
        tap_code(KC_VOLU);
    } else {
        tap_code(KC_VOLD);
    }
}

void encoder_action_word_nav(uint8_t clockwise) {
    if (clockwise) {
        tap_code16(C(KC_RIGHT));
    } else {
        tap_code16(C(KC_LEFT));
    }
}

void encoder_action(encoder_mode_t mode, uint8_t clockwise) {
    switch (mode) {
        case ENC_MODE_VOLUME:
            encoder_action_volume(clockwise);
            break;
        case ENC_MODE_WORD_NAV:
            encoder_action_word_nav(clockwise);
            break;
//        case ENC_MODE_LEFT_RIGHT:
//            encoder_action_left_right(clockwise);
//            break;
//        case ENC_MODE_UP_DOWN:
//            encoder_action_up_down(clockwise);
//            break;
//        case ENC_MODE_PAGING:
//            encoder_action_paging(clockwise);
//            break;
        default:
            encoder_action_volume(clockwise);
    }
}

