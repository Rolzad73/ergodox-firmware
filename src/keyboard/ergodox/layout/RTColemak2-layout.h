/* ----------------------------------------------------------------------------
 * ergoDOX : layout : DEFAULT : exports
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#ifndef KEYBOARD__ERGODOX__LAYOUT__DEFAULT_h
	#define KEYBOARD__ERGODOX__LAYOUT__DEFAULT_h

	#include "../controller.h"

	// --------------------------------------------------------------------

	// NOTE : change these depending on which LED # in the 7 Segment display they use
	// NOTE : also add "current layer" display functions
	//  _
	// |_| - top 4 LEDs show current layer in binary format clockwise from top 1,2,4,8 (16 layers)
	// |_| - bottom 3 LEDs show capsLk, scrLk, numLk
	
	#define kb_led_num_on()      _kb_led_1_on()
	#define kb_led_num_off()     _kb_led_1_off()
	#define kb_led_caps_on()     _kb_led_2_on()
	#define kb_led_caps_off()    _kb_led_2_off()
	#define kb_led_scroll_on()   _kb_led_3_on()
	#define kb_led_scroll_off()  _kb_led_3_off()

	// --------------------------------------------------------------------

	#include "./RTColemak2-led-control.h"
	#include "./default--matrix-control.h"

#endif

