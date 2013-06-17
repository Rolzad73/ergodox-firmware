/* ----------------------------------------------------------------------------
 * ergoDOX : controller : Teensy 2.0 specific exports : LED control
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#ifndef KEYBOARD__ERGODOX__CONTROLLER__TEENSY_2_0__LED_h
	#define KEYBOARD__ERGODOX__CONTROLLER__TEENSY_2_0__LED_h

	#include <stdint.h>
	#include <avr/io.h>  // for the register macros

	// --------------------------------------------------------------------

	#define _kb_led_1_on()           (DDRB |=  (1<<5))
	#define _kb_led_1_off()          (DDRB &= ~(1<<5))
	#define _kb_led_1_set(n)         (OCR1A = (uint8_t)(n))
	#define _kb_led_1_set_percent(n) (OCR1A = (uint8_t)((n) * 0xFF))

	#define _kb_led_2_on()           (DDRB |=  (1<<6))
	#define _kb_led_2_off()          (DDRB &= ~(1<<6))
	#define _kb_led_2_set(n)         (OCR1B = (uint8_t)(n))
	#define _kb_led_2_set_percent(n) (OCR1B = (uint8_t)((n) * 0xFF))

	#define _kb_led_3_on()           (DDRB |=  (1<<7))
	#define _kb_led_3_off()          (DDRB &= ~(1<<7))
	#define _kb_led_3_set(n)         (OCR1C = (uint8_t)(n))
	#define _kb_led_3_set_percent(n) (OCR1C = (uint8_t)((n) * 0xFF))

	// 3 more LEDs
	// TODO : get the correct ports to use
	// ports I think I can use as per circuit diagram (as well as use PB5, PB6, PB7 for existing LOCKS)
	// PD4, PD5, PD7, PC7, PE6
	// NOTE : do not use - > PB4 is +v and PD6 is ground
	// NOTE : will want to figure out "set_percent(n)" for theses as well
	// #define _kb_led_4_on()           (PORTD |=  (1<<4))
	// #define _kb_led_4_off()          (PORTD &= ~(1<<4))
	// #define _kb_led_5_on()           (PORTD |=  (1<<5))
	// #define _kb_led_5_off()          (PORTD &= ~(1<<6))
	// #define _kb_led_6_on()           (PORTD |=  (1<<7))
	// #define _kb_led_6_off()          (PORTD &= ~(1<<7))
	// #define _kb_led_7_on()           (PORTC |=  (1<<7))
	// #define _kb_led_7_off()          (PORTC &= ~(1<<7))

	#define _kb_led_all_on() do {	\
		_kb_led_1_on();		\
		_kb_led_2_on();		\
		_kb_led_3_on();		\
		} while(0)

	#define _kb_led_all_off() do {	\
		_kb_led_1_off();	\
		_kb_led_2_off();	\
		_kb_led_3_off();	\
		} while(0)

	#define _kb_led_all_set(n) do {	\
		_kb_led_1_set(n);	\
		_kb_led_2_set(n);	\
		_kb_led_3_set(n);	\
		} while(0)

	#define _kb_led_all_set_percent(n) do {	\
		_kb_led_1_set_percent(n);	\
		_kb_led_2_set_percent(n);	\
		_kb_led_3_set_percent(n);	\
		} while(0)

#endif

