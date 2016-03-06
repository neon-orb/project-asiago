#ifndef VGA_H_
#define VGA_H_

#include "../../utils/utils.h"
#include "../../kernel/ports.h"

/* Hardware text mode color constants. */
typedef enum {
	COLOR_BLACK = 0,
	COLOR_BLUE = 1,
	COLOR_GREEN = 2,
	COLOR_CYAN = 3,
	COLOR_RED = 4,
	COLOR_MAGENTA = 5,
	COLOR_BROWN = 6,
	COLOR_LIGHT_GREY = 7,
	COLOR_DARK_GREY = 8,
	COLOR_LIGHT_BLUE = 9,
	COLOR_LIGHT_GREEN = 10,
	COLOR_LIGHT_CYAN = 11,
	COLOR_LIGHT_RED = 12,
	COLOR_LIGHT_MAGENTA = 13,
	COLOR_LIGHT_BROWN = 14,
	COLOR_WHITE = 15
} VGAColor;

// FIX TO -Wimplicit-function-declaration WARNING
void terminal_backup();
void terminal_newline();

uint8_t make_color(VGAColor fg, VGAColor bg) {
	return fg | bg << 4;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

static const int TAB_SIZE = 2;

static size_t terminalRow;
static size_t terminalColumn;
static uint8_t terminalColor;
static uint16_t* terminalBuffer;

static uint16_t entry(char c, uint8_t color) {
	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}

static void update_cursor() {
	unsigned short position = (terminalRow * VGA_WIDTH) + terminalColumn;

	// cursor LOW port to vga INDEX register
	outb(0x3D4, 0x0F);
	outb(0x3D5, (unsigned char) (position & 0xFF));
	// cursor HIGH port to vga INDEX register
	outb(0x3D4, 0x0E);
	outb(0x3D5, (unsigned char) ((position >> 8) & 0xFF));
}

void terminal_initialize() {
	terminalRow = 0;
	terminalColumn = 0;
	terminalColor = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
	terminalBuffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminalBuffer[index] = entry(' ', terminalColor);
		}
	}
}

void terminal_setcolor(uint8_t color) {
	terminalColor = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminalBuffer[index] = entry(c, color);
}

static void shiftUp() {
	for (unsigned int i = VGA_WIDTH; i < VGA_WIDTH * VGA_HEIGHT; i +=
			VGA_WIDTH) {
		// FIXME when shifting up, only the left half of the screen is moved
		memcpy(&terminalBuffer[i - VGA_WIDTH], &terminalBuffer[i], VGA_WIDTH);
	}
}

void terminal_putchar(char c) {
	if (c == '\n') {
		// new line
		terminal_newline();
		return;
	} else if (c == 8) {
		// backspace
		terminal_backup();
		terminal_putchar(' ');
		terminal_backup();
	} else if (c == 9) {
		// tab
		for (int i = 0; i < TAB_SIZE; i++) { // FIXME backspacing will only delete part of the tab, not a real tab
			terminal_putchar(' ');
		}
	} else {
		// regular characters
		terminal_putentryat(c, terminalColor, terminalColumn, terminalRow);
		if (++terminalColumn == VGA_WIDTH) {
			terminalColumn = 0;
			if (++terminalRow == VGA_HEIGHT) {
				shiftUp();
				terminalRow--;
				for (unsigned int column = 0; column < VGA_WIDTH; column++) {
					terminal_putentryat(' ', terminalColor, column, terminalRow);
				}
			}
		}
	}
	update_cursor();
}

void terminal_backup() {
	if (--terminalColumn == (unsigned) -1) {
		terminalColumn = VGA_WIDTH - 1;
		if (--terminalRow == (unsigned) -1) {
			terminalRow = VGA_HEIGHT - 1;
		}
	}
}

void terminal_writeString(const char* data) {
	size_t datalen = strlen(data);
	for (size_t i = 0; i < datalen; i++) {
		char c = data[i];
		if (c == '\n') {
			// new line
			terminal_newline();
		} else if (c == 8) {
			// backspace
			//terminal_backup();
			terminalRow = 0;
			terminalColumn = 0;
			terminal_putchar(' ');
		} else if (c == 9) {
			// tab
			for (int i = 0; i < TAB_SIZE; i++) { // FIXME backspacing will only delete part of the tab, not a real tab
				terminal_putchar(' ');
			}
		} else {
			// regular characters
			terminal_putchar(c);
		}
	}
}

void terminal_newline() {
	for (size_t x = terminalColumn; x < VGA_WIDTH; x++) {
		terminal_putchar(' ');
	}
}

#endif /* VGA_H_ */
