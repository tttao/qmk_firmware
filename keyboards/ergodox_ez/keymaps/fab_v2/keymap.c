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