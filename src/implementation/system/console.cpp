/*
 * console.cpp
 *
 *  Created on: Sep 8, 2016
 *      Author: chris13524
 */

#include <implementation/system/console.h>

#include <memory.h>
#include <log.h>
#include <mish.h>
#include <modules/modules.h>
#include <modules/screen/screen.h>
#include <kernel/events.h>

extern uint8 mishStart; // &mishStart - start of Mish code
extern uint8 mishEnd; // &mishEnd - end of Mish code

List<wchar_t> line;

static void printShell() {
	screen_terminal_setForegroundColor(EFI_LIGHTBLUE);
	screen_terminal_writeString(L"> ");
	screen_terminal_resetForegroundColor();
}

void keyboardHandler(EFI_INPUT_KEY keyEvent) {
	if (keyEvent.UnicodeChar > 0) {
		if (keyEvent.UnicodeChar == 0xD) { // carriage return
			screen_terminal_writeString(L"\n\r");
			wchar_t* str = (wchar_t*) create(line.size() * 2 + 1);

			Iterator<wchar_t> stringIterator = line.iterator();
			uint64 strIndex = 0;
			while (stringIterator.hasNext()) {
				str[strIndex] = stringIterator.next();
				strIndex++;
			}
			str[strIndex] = NULL; // null terminate
			line.clear();

			Code* code = mish_compile(str);
			delete str;

			if (code != NULL) {
				mish_execute(code);
				delete code;
			}

			printShell();
		} else if (keyEvent.UnicodeChar == 0x8) { // backspace
			if (line.size() == 0) {
				return;
			}
			screen_terminal_writeString(keyEvent.UnicodeChar);
			line.remove(line.size() - 1);
		} else {
			screen_terminal_writeString(keyEvent.UnicodeChar);
			line.add(keyEvent.UnicodeChar);
		}
	}
}

void console() {
	eventHandler_keyboard = keyboardHandler;

	// convert to 16-bit string
	uint64 charCount = &mishEnd - &mishStart;
	wchar_t* sourceCode = (wchar_t*) create(charCount * 2 + 1);
	for (uint64 i = 0; i < charCount; i++) {
		sourceCode[i] = (wchar_t) ((&mishStart)[i]);
	}
	sourceCode[charCount] = 0; // NULL terminate

	Code* code = mish_compile(sourceCode);
	delete sourceCode;

	if (code != NULL) {
		mish_execute(code);
		delete code;
	}

	printShell();
}