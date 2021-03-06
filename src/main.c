// vim: ts=4 sw=4 sts=4
/* ----------------------------------------------------------------------------
 * main()
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#include <stdbool.h>
#include <stdint.h>
#include <util/delay.h>
#include "./lib-other/pjrc/usb_keyboard/usb_keyboard.h"
#include "./lib/key-functions/public.h"
#include "./keyboard/controller.h"
#include "./keyboard/layout.h"
#include "./keyboard/matrix.h"
#include "./main.h"

// ----------------------------------------------------------------------------

#define  MAX_ACTIVE_LAYERS  20

// ----------------------------------------------------------------------------

static bool _main_kb_is_pressed[KB_ROWS][KB_COLUMNS];
bool (*main_kb_is_pressed)[KB_ROWS][KB_COLUMNS] = &_main_kb_is_pressed;

static bool _main_kb_was_pressed[KB_ROWS][KB_COLUMNS];
bool (*main_kb_was_pressed)[KB_ROWS][KB_COLUMNS] = &_main_kb_was_pressed;

static bool main_kb_was_transparent[KB_ROWS][KB_COLUMNS];

uint8_t main_layers_pressed[KB_ROWS][KB_COLUMNS];

uint8_t main_loop_row;
uint8_t main_loop_col;

uint8_t main_arg_layer;
uint8_t main_arg_layer_offset;
uint8_t main_arg_row;
uint8_t main_arg_col;
bool    main_arg_is_pressed;
bool    main_arg_was_pressed;
bool    main_arg_any_non_trans_key_pressed;
bool    main_arg_trans_key_pressed;

// ----------------------------------------------------------------------------

/*
 * main()
 */
int main(void) {
	kb_init();  // does controller initialization too
    
	///////////////////////////////////////////////////////////////////////////
	// from kb_init()->teensy_init() (for reference)
	// onboard LED
	// (tied to GND for hardware convenience)
	// DDRD  &= ~(1<<6);  // set D(6) as input
	// PORTD &= ~(1<<6);  // set D(6) internal pull-up disabled

	// // (tied to Vcc for hardware convenience)
	// DDRB  &= ~(1<<4);  // set B(4) as input
	// PORTB &= ~(1<<4);  // set B(4) internal pull-up disabled
	///////////////////////////////////////////////////////////////////////////
	
	//from teensy-2.0.c file ( helpers )
	// #define  SET    |=
	// #define  CLEAR  &=~
	
	// more LED functionality (from someone's example) ////////////////////////
	// set internal pull-up off for all pins
	// PORTD &= ~(1<<4);
	// PORTD &= ~(1<<5);
	// PORTD &= ~(1<<6); this may be ground, as well, it is the onboard LED (so, probably dont touch)
    
	// set the pins as output
	// (because we cleared the applicable PORT bits above, the pins will now be driving low)
	// DDRD |= (1<<4);
	// DDRD |= (1<<5);
	// DDRD |= (1<<6);this may be ground, as well, it is the onboard LED (so, probably dont touch)
	///////////////////////////////////////////////////////////////////////////
	
	// ports I think I can use as per circuit diagram (as well as use PB5, PB6, PB7 for existing LOCKS)
	// PD4, PD5, PD7, PC7, PE6
	
	// LED ideas
	// get a 7 segment display for wiring convenience and display awesomeness
	// - when keyboard is plugged in, the 7 segment display could do a moving "snake" pattern
	//   * lightup/lightdown in kb_led_delay_usb_init() in keyboard's C file
	//  _
	// |_| - top 4 LEDs show current layer in binary format clockwise from top 1,2,4,8 (16 layers)
	// |_| - bottom 3 LEDs show capsLk, scrLk, numLk
	//
	// update: the display i got has a decimal point as well, so that makes 8 LEDs I could use,
	// and 8 ports open.  will have to find a use for the decimal.
	//
	// NOTE : some ports are digital while others are analog.  In the circuit diagram SVG, the
	//        LEDs have an indicator on the PWM (pulse width modultion) which is how the code gets
	//        different brightnesses. see teensy-2-0.md for detailed info
	//
	// NOTE : Look into using SoftPWM library to get digital pins to be able to set brightness
	//        of LEDs that are not on OCR pins

	kb_led_state_power_on();

	usb_init();
	while (!usb_configured());
	kb_led_delay_usb_init();  // give the OS time to load drivers, etc.

	kb_led_state_ready();

	for (;;) {
		// swap `main_kb_is_pressed` and `main_kb_was_pressed`, then update
		bool (*temp)[KB_ROWS][KB_COLUMNS] = main_kb_was_pressed;
		main_kb_was_pressed = main_kb_is_pressed;
		main_kb_is_pressed = temp;

		kb_update_matrix(*main_kb_is_pressed);

		// this loop is responsible to
		// - "execute" keys when they change state
		// - keep track of which layers the keys were on when they were pressed
		//   (so they can be released using the function from that layer)
		//
		// note
		// - everything else is the key function's responsibility
		//   - see the keyboard layout file ("keyboard/ergodox/layout/*.c") for
		//     which key is assigned which function (per layer)
		//   - see "lib/key-functions/public/*.c" for the function definitions
		#define row          main_loop_row
		#define col          main_loop_col
		#define layer        main_arg_layer
		#define is_pressed   main_arg_is_pressed
		#define was_pressed  main_arg_was_pressed
		for (row=0; row<KB_ROWS; row++) {
			for (col=0; col<KB_COLUMNS; col++) {
				is_pressed = (*main_kb_is_pressed)[row][col];
				was_pressed = (*main_kb_was_pressed)[row][col];

				if (is_pressed != was_pressed) {
					if (is_pressed) {
						layer = main_layers_peek(0);
						main_layers_pressed[row][col] = layer;
						main_arg_trans_key_pressed = false;
					} else {
						layer = main_layers_pressed[row][col];
						main_arg_trans_key_pressed = main_kb_was_transparent[row][col];
					}

					// set remaining vars, and "execute" key
					main_arg_row          = row;
					main_arg_col          = col;
					main_arg_layer_offset = 0;
					main_exec_key();
					main_kb_was_transparent[row][col] = main_arg_trans_key_pressed;
				}
			}
		}
		#undef row
		#undef col
		#undef layer
		#undef is_pressed
		#undef was_pressed

		// send the USB report (even if nothing's changed)
		usb_keyboard_send();
		usb_extra_consumer_send();
		_delay_ms(MAKEFILE_DEBOUNCE_TIME);

		// update LEDs
		if (keyboard_leds & (1<<0)) { kb_led_num_on(); }
		else { kb_led_num_off(); }
		if (keyboard_leds & (1<<1)) { kb_led_caps_on(); }
		else { kb_led_caps_off(); }
		if (keyboard_leds & (1<<2)) { kb_led_scroll_on(); }
		else { kb_led_scroll_off(); }
		if (keyboard_leds & (1<<3)) { kb_led_compose_on(); }
		else { kb_led_compose_off(); }
		if (keyboard_leds & (1<<4)) { kb_led_kana_on(); }
		else { kb_led_kana_off(); }

		// set layer indicator LEDS
		indicate_active_layer();
	}

	return 0;
}

// ----------------------------------------------------------------------------

// convenience macros (for the helper functions below)
#define  layer        main_arg_layer
#define  row          main_arg_row
#define  col          main_arg_col
#define  is_pressed   main_arg_is_pressed
#define  was_pressed  main_arg_was_pressed

// ----------------------------------------------------------------------------

/* ----------------------------------------------------------------------------
 * Layer Functions
 * ----------------------------------------------------------------------------
 * We keep track of which layer is foremost by placing it on a stack.  Layers
 * may appear in the stack more than once.  The base layer will always be
 * layer-0.  
 *
 * Implemented as a fixed size stack.
 * ------------------------------------------------------------------------- */

// ----------------------------------------------------------------------------

struct layers {
	uint8_t layer;
	uint8_t id;
	uint8_t sticky;
};

// ----------------------------------------------------------------------------

uint8_t       layers_head = 0;
struct layers layers[MAX_ACTIVE_LAYERS];
uint8_t       layers_ids_in_use[MAX_ACTIVE_LAYERS] = {true};

/*
 * Exec key
 * - Execute the keypress or keyrelease function (if it exists) of the key at
 *   the current possition.
 */
void main_exec_key(void) {
	void (*key_function)(void) =
		( (is_pressed)
		  ? kb_layout_press_get(layer, row, col)
		  : kb_layout_release_get(layer, row, col) );

	if (key_function)
		(*key_function)();

	// If the current layer is in the sticky once up state and a key defined
	//  for this layer (a non-transparent key) was pressed, pop the layer
	if (layers[layers_head].sticky == eStickyOnceUp && main_arg_any_non_trans_key_pressed)
		main_layers_pop_id(layers_head);
}

/*
 * peek()
 *
 * Arguments
 * - 'offset': the offset (down the stack) from the head element
 *
 * Returns
 * - success: the layer-number of the requested element (which may be 0)
 * - failure: 0 (default) (out of bounds)
 */
uint8_t main_layers_peek(uint8_t offset) {
	if (offset <= layers_head)
		return layers[layers_head - offset].layer;

	return 0;  // default, or error
}

uint8_t main_layers_peek_sticky(uint8_t offset) {
	if (offset <= layers_head)
		return layers[layers_head - offset].sticky;

	return 0;  // default, or error
}

/*
 * push()
 *
 * Arguments
 * - 'layer': the layer-number to push to the top of the stack
 *
 * Returns
 * - success: the id assigned to the newly added element
 * - failure: 0 (the stack was already full)
 */
uint8_t main_layers_push(uint8_t layer, uint8_t sticky) {
	// look for an available id
	for (uint8_t id=1; id<MAX_ACTIVE_LAYERS; id++) {
		// if one is found
		if (layers_ids_in_use[id] == false) {
			layers_ids_in_use[id] = true;
			layers_head++;
			layers[layers_head].layer = layer;
			layers[layers_head].id = id;
			layers[layers_head].sticky = sticky;
// TODO: indicate_active_layer here?
			return id;
		}
	}

	return 0;  // default, or error
}

/*
 * pop_id()
 *
 * Arguments
 * - 'id': the id of the element to pop from the stack
 */
void main_layers_pop_id(uint8_t id) {
	// look for the element with the id we want to pop
	for (uint8_t element=1; element<=layers_head; element++) {
		// if we find it
		if (layers[element].id == id) {
			// move all layers above it down one
			for (; element<layers_head; element++) {
				layers[element].layer = layers[element+1].layer;
				layers[element].id = layers[element+1].id;
			}
			// reinitialize the topmost (now unused) slot
			layers[layers_head].layer = 0;
			layers[layers_head].id = 0;
			// record keeping
			layers_ids_in_use[id] = false;
			layers_head--;
// TODO: indicate_active_layer here?
			return;
		}
	}
}

/*
 * get_offset_id()
 *
 * Arguments
 * - 'id': the id of the element you want the offset of
 *
 * Returns
 * - success: the offset (down the stack from the head element) of the element
 *   with the given id
 * - failure: 0 (default) (id unassigned)
 */
uint8_t main_layers_get_offset_id(uint8_t id) {
	// look for the element with the id we want to get the offset of
	for (uint8_t element=1; element<=layers_head; element++)
		// if we find it
		if (layers[element].id == id)
			return (layers_head - element);

	return 0;  // default, or error

}

/*
 * indicate_active_layer()
 * - indicates active layer in binary notation
 */
void indicate_active_layer() {
	if (layers[layers_head].layer & (1<<0)) { _kb_led_6_on(); }
	else { _kb_led_6_off();	}
	if (layers[layers_head].layer & (1<<1)) { _kb_led_5_on(); }
	else { _kb_led_5_off();	}
	if (layers[layers_head].layer & (1<<2)) { _kb_led_4_on(); }
	else { _kb_led_4_off();	}
}
/* ----------------------------------------------------------------------------
 * ------------------------------------------------------------------------- */

