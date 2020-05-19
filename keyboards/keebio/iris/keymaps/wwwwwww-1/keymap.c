#include QMK_KEYBOARD_H


#define _WORKMAN 0
#define _SYMBOL 1
#define _ARROW 2
#define _ADJUST 3
#define RGB_RMD RGB_RMOD
#define OS_LSFT OSM(MOD_LSFT)
#define OS_LCTL OSM(MOD_LCTL)
#define OS_RGUI OSM(MOD_RGUI)
#define OS_RALT OSM(MOD_RALT)
#define OS_SYM OSL(_SYMBOL)
#define TAB_AR LT(_ARROW, KC_TAB)

uint16_t lower_timer;
uint16_t raise_timer;
bool queue = true;

enum custom_keycodes {
  WORKMAN = SAFE_RANGE,
  SYMBOL,
  ARROW,
  ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_WORKMAN] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_MINS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_GRV,  KC_Q,    KC_D,    KC_R,    KC_W,    KC_B,                               KC_J,    KC_F,    KC_U,    KC_P,    KC_SCLN, KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     TAB_AR,  KC_A,    KC_S,    KC_H,    KC_T,    KC_G,                               KC_Y,    KC_N,    KC_E,    KC_O,    KC_I,    KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     OS_SYM,  KC_Z,    KC_X,    KC_M,    KC_C,    KC_V,    KC_ESC,           ARROW,   KC_K,    KC_L,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    OS_LCTL, OS_LSFT, KC_SPC,                    KC_ENT,  OS_RGUI, OS_RALT
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_SYMBOL] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            _______, KC_7,    KC_8,    KC_9,    _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            KC_LBRC, KC_P4,   KC_P5,   KC_P6,   KC_PLUS, KC_EQL,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______, _______,          _______, KC_RBRC, KC_P1,   KC_P2,   KC_P3,   KC_MINS, KC_UNDS,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, KC_P0
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_ARROW] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            _______, KC_HOME, KC_END,  _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     SYMBOL,  _______, _______, _______, _______, _______, _______,          _______, _______, KC_PGDN, KC_PGUP, _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_ADJUST] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     RESET,   _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, WORKMAN, DM_REC1, DM_REC2, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, DM_PLY1, DM_PLY2, DM_RSTP,                            RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______, _______,          _______, _______, RGB_RMD, RGB_HUD, RGB_SAD, RGB_VAD, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
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
    case SYMBOL:
      if (record->event.pressed) {
	if (layer_state_is(_SYMBOL)) {
	  layer_clear();
	  update_tri_layer(_SYMBOL, _ARROW, _ADJUST);
	} else {
	  layer_on(_SYMBOL);
	  update_tri_layer(_SYMBOL, _ARROW, _ADJUST);
	  lower_timer = timer_read();
	}
      } else {
	if (timer_elapsed(lower_timer) > 100) {
	  layer_off(_SYMBOL);
	  update_tri_layer(_SYMBOL, _ARROW, _ADJUST);
	}
      }
      return false;
      break;
    case ARROW:
      if (record->event.pressed) {
	if (layer_state_is(_ARROW)) {
	  layer_clear();
	  update_tri_layer(_SYMBOL, _ARROW, _ADJUST);
	} else {
	  layer_on(_ARROW);
	  update_tri_layer(_SYMBOL, _ARROW, _ADJUST);
	  raise_timer = timer_read();
	}
      } else {
	if (timer_elapsed(raise_timer) > 100) {
	  layer_off(_ARROW);
	  update_tri_layer(_SYMBOL, _ARROW, _ADJUST);
	}
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
    case KC_ESC:
      queue = true;
      if (record->event.pressed) {
	if (get_oneshot_mods() && !has_oneshot_mods_timed_out()) {
	  clear_oneshot_mods();
	  queue = false;
	}
      }
      return queue;
      break;
  }
  return true;
}

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == 1) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
}

const rgblight_segment_t PROGMEM my_shift_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {5, 1, HSV_RED}
);

const rgblight_segment_t PROGMEM my_gui_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {6, 1, HSV_PURPLE}
);

const rgblight_segment_t PROGMEM my_ctrl_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_BLUE}
);

const rgblight_segment_t PROGMEM my_alt_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {11, 1, HSV_GREEN}
);

const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 6, HSV_GOLD}
);

const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {6, 6, HSV_SPRINGGREEN}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_layer1_layer,
    my_layer2_layer,
    my_gui_layer,
    my_shift_layer,
    my_ctrl_layer,
    my_alt_layer
);

void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers;
    set_single_persistent_default_layer(_WORKMAN);
    layer_clear();
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _SYMBOL));
    rgblight_set_layer_state(1, layer_state_cmp(state, _ARROW));
    return state;
}

void oneshot_mods_changed_user(uint8_t mods) {
    rgblight_set_layer_state(2, mods & MOD_MASK_GUI);
    rgblight_set_layer_state(3, mods & MOD_MASK_SHIFT);
    rgblight_set_layer_state(4, mods & MOD_MASK_CTRL);
    rgblight_set_layer_state(5, mods & MOD_MASK_ALT);
}

