#include QMK_KEYBOARD_H
#include "version.h"
#include "keymap_french.h"

bool is_alt_tab_active = false;    // ADD this near the begining of keymap.c
uint16_t alt_tab_timer = 0;        // we will be using them soon.

enum layers {
    BASE, // default layer
    SYMB, // symbols
    MEDIA,  // media keys
};

enum custom_keycodes {
  CS_CUT = SAFE_RANGE,
  CS_COPY,
  CS_PASTE,
  CS_ALT_TAB
};

enum {
  TD_U = 0,
  TD_A,
  TD_E
};

void dance_a_accent_finished(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1:
		register_code(FR_AGRV);
		break;
	case 2:
		register_mods(MOD_BIT(KC_RALT));
		register_code(FR_AGRV);
		break;
  }
}

void dance_a_accent_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1:
		unregister_code(FR_AGRV);
		break;
	case 2:
		unregister_mods(MOD_BIT(KC_RALT));
		unregister_code(FR_AGRV);
		break;
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_U] = ACTION_TAP_DANCE_DOUBLE(KC_U, FR_UGRV),
  [TD_E] = ACTION_TAP_DANCE_DOUBLE(FR_EACU, FR_EGRV),
  [TD_A] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_a_accent_finished, dance_a_accent_reset)
};
/*
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[BASE] = LAYOUT_ergodox_pretty(
  // left hand
  KC_ESC,          			FR_AMPR,     FR_EACU,       FR_DQUO, FR_QUOT, FR_LPRN, KC_INS,              KC_DEL,       FR_MINS, FR_EGRV, FR_UNDS, FR_CCED, FR_AGRV,  FR_CIRC,
  KC_TAB,          			FR_A,        FR_Z,          KC_E,    KC_R,    KC_T,    CS_COPY,              CS_CUT,       KC_Y,    TD(TD_U),    KC_I,    KC_O,    KC_P,     FR_DLR,
  MO(MEDIA),      			FR_Q,        KC_S,          KC_D,    KC_F,    KC_G,                                       KC_H,    KC_J,    KC_K,    KC_L,    FR_M,     MO(MEDIA),
  MT(MOD_LSFT, FR_LPRN),    FR_W, 		  KC_X,         KC_C,    KC_V,    KC_B,    CS_PASTE,             KC_TRNS,      KC_N,    FR_COMM, FR_SCLN, FR_COLN, KC_UP,    MT(MOD_RSFT, FR_RPRN),
  KC_LCTL, 		  			KC_LGUI, 	  KC_LALT, 	    FR_EXLM, MO(SYMB),                               KC_RALT, KC_RCTRL,KC_LEFT, KC_DOWN, KC_RIGHT,
																			 FR_EQL,  FR_SLSH,   CS_ALT_TAB,      KC_TRNS,
																					  FR_RABK,   KC_HOME,
																	 KC_SPC, KC_BSPC, FR_LABK,   KC_END,       KC_TRNS, KC_ENT
),

[SYMB] = LAYOUT_ergodox_pretty(
  // left hand
  KC_ESC,  	KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_MUTE,     KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  KC_TRNS, TD(TD_A),FR_LBRC, TD(TD_E), FR_LABK, FR_RABK, KC_VOLU,     KC_TRNS, KC_UP,   KC_KP_7, KC_KP_8, KC_KP_9,    FR_ASTR, KC_F12,
  KC_TRNS, FR_LCBR, FR_RCBR, FR_RBRC, FR_PIPE, FR_GRV,                        KC_DOWN, KC_KP_4, KC_KP_5, KC_KP_6,    KC_PLUS, KC_TRNS,
  KC_TRNS, FR_DLR,  FR_PERC, FR_ASTR, FR_HASH, FR_TILD, KC_TRNS,     KC_TRNS, KC_AMPR, KC_KP_1, KC_KP_2, KC_KP_3,    KC_BSLS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                         KC_KP_DOT,KC_KP_0,FR_COMM, KC_EQL,  KC_TRNS,
                                               KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS,
                                                        KC_TRNS,     KC_TRNS,
                                      KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS
),

[MEDIA] = LAYOUT_ergodox_pretty(
  // left hand
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET,
  KC_TRNS, KC_TRNS, KC_TRNS, FR_EGRV, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,                                         KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,

                                               KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS,
                                                        KC_TRNS,     KC_TRNS,
                                      KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_WBAK
),
};
*/
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case CS_CUT:
		if (record->event.pressed) {
			SEND_STRING(SS_LCTL("x"));
		}
	  break;
      case CS_COPY:
		if (record->event.pressed) {
			SEND_STRING(SS_LCTL("c"));
		}
	  break;
      case CS_PASTE:
		if (record->event.pressed) {
			SEND_STRING(SS_LCTL("v"));
		}
	  break;	 
    case CS_ALT_TAB:
      if (record->event.pressed) {
    	register_code(KC_LALT);
		   tap_code(KC_TAB);
		   unregister_code(KC_LALT);
		  }  
      break;
    }
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

// Runs whenever there is a layer state change.
layer_state_t layer_state_set_user(layer_state_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  uint8_t layer = get_highest_layer(state);
  switch (layer) {
      case 0:
        #ifdef RGBLIGHT_COLOR_LAYER_0
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
        #endif
        break;
      case 1:
        ergodox_right_led_1_on();
        #ifdef RGBLIGHT_COLOR_LAYER_1
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
        break;
      case 2:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
        break;
      case 3:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_3
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
        #endif
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_5
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
        #endif
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_6
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_7
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_7);
        #endif
        break;
      default:
        break;
    }

  return state;
};

#include "keymap.inc"