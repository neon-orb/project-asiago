#ifndef PS2
#define PS2

#include <stdbool.h>
#include "keyboard.h"

#define keycount 17

KeyEvent scanCodeSet1[] = { EVENT_NULL, { ESCAPE, PRESSED },

{ DIGIT1, PRESSED }, { DIGIT2, PRESSED }, { DIGIT3, PRESSED },
		{ DIGIT4, PRESSED }, { DIGIT5, PRESSED }, { DIGIT6, PRESSED }, { DIGIT7,
				PRESSED }, { DIGIT8, PRESSED }, { DIGIT9, PRESSED }, { DIGIT0,
				PRESSED },

		{ HYPHEN, PRESSED }, { EQUALS, PRESSED }, { BACKSPACE, PRESSED }, { TAB,
				PRESSED },

		{ Q, PRESSED }, { W, PRESSED }, { E, PRESSED }, { R, PRESSED }, { T,
				PRESSED }, { Y, PRESSED }, { U, PRESSED }, { I, PRESSED }, { O,
				PRESSED }, { P, PRESSED }, { LEFT_BRACKET, PRESSED }, {
				RIGHT_BRACKET, PRESSED }, { ENTER, PRESSED }, { LEFT_CONTROL,
				PRESSED }, { A, PRESSED }, { S, PRESSED }, { D, PRESSED }, { F,
				PRESSED }, { G, PRESSED }, { H, PRESSED }, { J, PRESSED }, { K,
				PRESSED }, { L, PRESSED }, { SEMICOLON, PRESSED }, {
				SINGLE_QUOTE, PRESSED }, { GRAVE, PRESSED }, { LEFT_SHIFT,
				PRESSED }, { BACK_SLASH, PRESSED }, { Z, PRESSED },
		{ X, PRESSED }, { C, PRESSED }, { V, PRESSED }, { B, PRESSED }, { N,
				PRESSED }, { M, PRESSED }, { COMMA, PRESSED },
		{ PERIOD, PRESSED }, { FORWARD_SLASH, PRESSED },
		{ RIGHT_SHIFT, PRESSED }, { NUMPAD_TIMES, PRESSED }, { LEFT_ALT,
				PRESSED }, { SPACE, PRESSED }, { CAPS_LOCK, PRESSED }, { F1,
				PRESSED }, { F2, PRESSED }, { F3, PRESSED }, { F4, PRESSED }, {
				F5, PRESSED }, { F6, PRESSED }, { F7, PRESSED },
		{ F8, PRESSED }, { F9, PRESSED }, { F10, PRESSED },
		{ NUM_LOCK, PRESSED }, { SCROLL_LOCK, PRESSED }, { NUMPAD7, PRESSED }, {
				NUMPAD8, PRESSED }, { NUMPAD9, PRESSED }, { NUMPAD_MINUS,
				PRESSED }, { NUMPAD4, PRESSED }, { NUMPAD5, PRESSED }, {
				NUMPAD6, PRESSED }, { NUMPAD_PLUS, PRESSED },
		{ NUMPAD1, PRESSED }, { NUMPAD2, PRESSED }, { NUMPAD3, PRESSED }, {
				NUMPAD0, PRESSED }, { NUMPAD_DECIMAL }, EVENT_NULL, EVENT_NULL, EVENT_NULL, {F11, PRESSED},{F12, PRESSED},EVENT_NULL, EVENT_NULL, EVENT_NULL, EVENT_NULL,


				// released
				{ ESCAPE, RELEASED },

				{ DIGIT1, RELEASED }, { DIGIT2, RELEASED }, { DIGIT3, RELEASED },
						{ DIGIT4, RELEASED }, { DIGIT5, RELEASED }, { DIGIT6, RELEASED }, { DIGIT7,
								RELEASED }, { DIGIT8, RELEASED }, { DIGIT9, RELEASED }, { DIGIT0,
								RELEASED },

						{ HYPHEN, RELEASED }, { EQUALS, RELEASED }, { BACKSPACE, RELEASED }, { TAB,
								RELEASED },

						{ Q, RELEASED }, { W, RELEASED }, { E, RELEASED }, { R, RELEASED }, { T,
								RELEASED }, { Y, RELEASED }, { U, RELEASED }, { I, RELEASED }, { O,
								RELEASED }, { P, RELEASED }, { LEFT_BRACKET, RELEASED }, {
								RIGHT_BRACKET, RELEASED }, { ENTER, RELEASED }, { LEFT_CONTROL,
								RELEASED }, { A, RELEASED }, { S, RELEASED }, { D, RELEASED }, { F,
								RELEASED }, { G, RELEASED }, { H, RELEASED }, { J, RELEASED }, { K,
								RELEASED }, { L, RELEASED }, { SEMICOLON, RELEASED }, {
								SINGLE_QUOTE, RELEASED }, { GRAVE, RELEASED }, { LEFT_SHIFT,
								RELEASED }, { BACK_SLASH, RELEASED }, { Z, RELEASED },
						{ X, RELEASED }, { C, RELEASED }, { V, RELEASED }, { B, RELEASED }, { N,
								RELEASED }, { M, RELEASED }, { COMMA, RELEASED },
						{ PERIOD, RELEASED }, { FORWARD_SLASH, RELEASED },
						{ RIGHT_SHIFT, RELEASED }, { NUMPAD_TIMES, RELEASED }, { LEFT_ALT,
								RELEASED }, { SPACE, RELEASED }, { CAPS_LOCK, RELEASED }, { F1,
								RELEASED }, { F2, RELEASED }, { F3, RELEASED }, { F4, RELEASED }, {
								F5, RELEASED }, { F6, RELEASED }, { F7, RELEASED },
						{ F8, RELEASED }, { F9, RELEASED }, { F10, RELEASED },
						{ NUM_LOCK, RELEASED }, { SCROLL_LOCK, RELEASED }, { NUMPAD7, RELEASED }, {
								NUMPAD8, RELEASED }, { NUMPAD9, RELEASED }, { NUMPAD_MINUS,
								RELEASED }, { NUMPAD4, RELEASED }, { NUMPAD5, RELEASED }, {
								NUMPAD6, RELEASED }, { NUMPAD_PLUS, RELEASED },
						{ NUMPAD1, RELEASED }, { NUMPAD2, RELEASED }, { NUMPAD3, RELEASED }, {
								NUMPAD0, RELEASED }, { NUMPAD_DECIMAL }, EVENT_NULL, EVENT_NULL, EVENT_NULL, {F11, RELEASED},{F12, RELEASED},
								EVENT_NULL, EVENT_NULL, EVENT_NULL//,

								// next set
								//{NUMPAD_ENTER, RELEASED},{RIGHT_CONTROL, RELEASED},EVENT_NULL, EVENT_NULL, EVENT_NULL,{NUMPAD_DIVIDE, RELEASED},EVENT_NULL, EVENT_NULL,{RIGHT_ALT, RELEASED},EVENT_NULL, EVENT_NULL, EVENT_NULL, EVENT_NULL, EVENT_NULL, EVENT_NULL,{HOME, RELEASED},{CURSOR_UP, RELEASED},{PAGE_UP, RELEASED},EVENT_NULL,{CURSOR_LEFT, RELEASED},EVENT_NULL, {CURSOR_RIGHT, RELEASED},EVENT_NULL,{END, RELEASED},{CURSOR_DOWN, RELEASED},{PAGE_DOWN, RELEASED},{INSERT, RELEASED},{DELETE, RELEASED},EVENT_NULL, EVENT_NULL, EVENT_NULL, {LEFT_GUI, RELEASED},{RIGHT_GUI, RELEASED},{APPS, RELEASED},EVENT_NULL, EVENT_NULL,

								// released
								//{NUMPAD_ENTER, RELEASED},{RIGHT_CONTROL, RELEASED},EVENT_NULL, EVENT_NULL, EVENT_NULL,{NUMPAD_DIVIDE, RELEASED},EVENT_NULL, EVENT_NULL,{RIGHT_ALT, RELEASED},EVENT_NULL, EVENT_NULL, EVENT_NULL, EVENT_NULL, EVENT_NULL, EVENT_NULL,{HOME, RELEASED},{CURSOR_UP, RELEASED},{PAGE_UP, RELEASED},EVENT_NULL,{CURSOR_LEFT, RELEASED},EVENT_NULL, {CURSOR_RIGHT, RELEASED},EVENT_NULL,{END, RELEASED},{CURSOR_DOWN, RELEASED},{PAGE_DOWN, RELEASED},{INSERT, RELEASED},{DELETE, RELEASED},EVENT_NULL, EVENT_NULL, EVENT_NULL, {LEFT_GUI, RELEASED},{RIGHT_GUI, RELEASED},{APPS, RELEASED},EVENT_NULL, EVENT_NULL
};

char scancodes[keycount] = { 'e', // escape
		'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 8, // backspace
		9, // tab
		'Q', 'W' }; // TODO finish this table, see http://wiki.osdev.org/Keyboard#Scan_Code_Set_1
bool keyspressed[keycount];

static inline void outb(uint16_t port, uint8_t val) {
	asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
	/* There's an outb %al, $imm8  encoding, for compile-time constant port numbers that fit in 8b.  (N constraint).
	 * Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
	 * The  outb  %al, %dx  encoding is the only option for all other cases.
	 * %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we had the port number a wider C type */
}

static inline uint8_t inb(uint16_t port) {
	uint8_t ret;
	asm volatile ( "inb %[port], %[ret]"
			: [ret] "=a"(ret) // using symbolic operand names as an example, mainly because they're not used in order
			: [port] "Nd"(port) );
	return ret;
}

uint8_t getScancode();

void ps2_readkeyboard();

void ps2_interrupt();

#endif
