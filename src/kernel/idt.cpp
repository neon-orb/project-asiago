/* idt.c - Sets up the IDT */
/* Copyright (C) 2016  Chris Smith */

/* This program is free software: you can redistribute it and/or modify */
/* it under the terms of the GNU General Public License as published by */
/* the Free Software Foundation, either version 3 of the License, or */
/* (at your option) any later version. */

/* This program is distributed in the hope that it will be useful, */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the */
/* GNU General Public License for more details. */

/* You should have received a copy of the GNU General Public License */
/* along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#include <kernel/idt.h>

#include <int.h>
#include <kernel/ports.h>
#include <log.h>
#include <utils/utils.h>

/*********** ------------------------- THIS CRAP WILL BE REMOVED LATER ---------------------------- *********************/

#define DO_DEBUG_LOGGING 1

#define LOG_COMPLETE	1
#define LOG_FAIL		2
#define LOG_WARN		3
#define LOG_INFO		4
#define LOG_DEBUG		5
#define LOG_INTERNALS	6
#define LOG_UNKN		0
// Low level
void log_low(const char * str);
void low_printname();
void text_console_init();
// High level
void printk(int severity, char * type, const char *fmt, ...);
void logging_printbestunit(uint32 bytes, uint8 newline);

void printk(int severity, char* type, const char* fmt, ...) {
	/*switch(severity) {
	 case LOG_COMPLETE:
	 text_console_change_color(0xA);
	 break;
	 case LOG_FAIL:
	 text_console_change_color(0x4);
	 break;
	 case LOG_WARN:
	 text_console_change_color(0xE);
	 break;
	 case LOG_INFO:
	 text_console_change_color(0xB);
	 break;
	 case LOG_DEBUG:
	 text_console_change_color(0xD);
	 break;
	 case LOG_INTERNALS:
	 text_console_change_color(0xD);
	 break;
	 case LOG_UNKN:
	 default: // LOG_UNKN
	 text_console_change_color(0x8);
	 break;
	 }
	 printf("%s: ",type);
	 text_console_reset_color();
	 va_list args;
	 va_start(args, fmt);
	 vprintf(fmt,args);
	 va_end(args);*/
	//log(fmt);
}

/********************** ------------------------- END TO REMOVE CRAP ------------------- **********************/

struct idt_entry {
	uint16 baseLow;
	uint16 selector;
	uint8 reservedIst;
	uint8 flags;
	uint16 baseMid;
	uint32 baseHigh;
	uint32 reserved;
}__attribute__((packed));

struct idt_ptr {
	uint16 limit;
	uint64 base;
}__attribute__((packed));

///Installs all irqs
void irq_install();

extern "C" void isr0();
extern "C" void isr1();
extern "C" void isr2();
extern "C" void isr3();
extern "C" void isr4();
extern "C" void isr5();
extern "C" void isr6();
extern "C" void isr7();
extern "C" void isr8();
extern "C" void isr9();
extern "C" void isr10();
extern "C" void isr11();
extern "C" void isr12();
extern "C" void isr13();
extern "C" void isr14();
extern "C" void isr15();
extern "C" void isr16();
extern "C" void isr17();
extern "C" void isr18();
extern "C" void isr19();
extern "C" void isr20();
extern "C" void isr21();
extern "C" void isr22();
extern "C" void isr23();
extern "C" void isr24();
extern "C" void isr25();
extern "C" void isr26();
extern "C" void isr27();
extern "C" void isr28();
extern "C" void isr29();
extern "C" void isr30();
extern "C" void isr31();
extern "C" void isr100();

extern "C" void irq0();
extern "C" void irq1();
extern "C" void irq2();
extern "C" void irq3();
extern "C" void irq4();
extern "C" void irq5();
extern "C" void irq6();
extern "C" void irq7();
extern "C" void irq8();
extern "C" void irq9();
extern "C" void irq10();
extern "C" void irq11();
extern "C" void irq12();
extern "C" void irq13();
extern "C" void irq14();
extern "C" void irq15();

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel,
		unsigned char flags);
extern "C" void idt_flush();

struct idt_entry idt_entries[256];
struct idt_ptr idt_ptr;

///Inits interrupt services
void idt_init_isrs() {
	idt_set_gate(0, (uint64) isr0, 0x08, 0x8E);
	idt_set_gate(1, (uint64) isr1, 0x08, 0x8E);
	idt_set_gate(2, (uint64) isr2, 0x08, 0x8E);
	idt_set_gate(3, (uint64) isr3, 0x08, 0x8E);
	idt_set_gate(4, (uint64) isr4, 0x08, 0x8E);
	idt_set_gate(5, (uint64) isr5, 0x08, 0x8E);
	idt_set_gate(6, (uint64) isr6, 0x08, 0x8E);
	idt_set_gate(7, (uint64) isr7, 0x08, 0x8E);

	idt_set_gate(8, (uint64) isr8, 0x08, 0x8E);
	idt_set_gate(9, (uint64) isr9, 0x08, 0x8E);
	idt_set_gate(10, (uint64) isr10, 0x08, 0x8E);
	idt_set_gate(11, (uint64) isr11, 0x08, 0x8E);
	idt_set_gate(12, (uint64) isr12, 0x08, 0x8E);
	idt_set_gate(13, (uint64) isr13, 0x08, 0x8E);
	idt_set_gate(14, (uint64) isr14, 0x08, 0x8E);
	idt_set_gate(15, (uint64) isr15, 0x08, 0x8E);

	idt_set_gate(16, (uint64) isr16, 0x08, 0x8E);
	idt_set_gate(17, (uint64) isr17, 0x08, 0x8E);
	idt_set_gate(18, (uint64) isr18, 0x08, 0x8E);
	idt_set_gate(19, (uint64) isr19, 0x08, 0x8E);
	idt_set_gate(20, (uint64) isr20, 0x08, 0x8E);
	idt_set_gate(21, (uint64) isr21, 0x08, 0x8E);
	idt_set_gate(22, (uint64) isr22, 0x08, 0x8E);
	idt_set_gate(23, (uint64) isr23, 0x08, 0x8E);

	idt_set_gate(24, (uint64) isr24, 0x08, 0x8E);
	idt_set_gate(25, (uint64) isr25, 0x08, 0x8E);
	idt_set_gate(26, (uint64) isr26, 0x08, 0x8E);
	idt_set_gate(27, (uint64) isr27, 0x08, 0x8E);
	idt_set_gate(28, (uint64) isr28, 0x08, 0x8E);
	idt_set_gate(29, (uint64) isr29, 0x08, 0x8E);
	idt_set_gate(30, (uint64) isr30, 0x08, 0x8E);
	idt_set_gate(31, (uint64) isr31, 0x08, 0x8E);
	//Syscall
	idt_set_gate(0x64, (uint64) isr100, 0x08, 0x8E);
}

///Sets a gate in the IDT
void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel,
		unsigned char flags) {
	idt_entries[num].baseLow = base & 0xFFFF;
	idt_entries[num].baseMid = (base >> 16) & 0xFFFF;
	idt_entries[num].baseHigh = (base >> 32) & 0xFFFFFFFF;

	idt_entries[num].selector = sel;
	idt_entries[num].flags = flags;

	idt_entries[num].reservedIst = 0;
	idt_entries[num].reserved = 0;
}

///Table of all exception messages
const char *exception_messages[] = { "Division By Zero", "Debug",
		"Non Maskable Interrupt", "Breakpoint", "Into Detected Overflow",
		"Out of Bounds", "Invalid Opcode", "No Coprocessor",

		"Double Fault", "Coprocessor Segment Overrun", "Bad TSS",
		"Segment Not Present", "Stack Fault", "General Protection Fault",
		"Page Fault", "Unknown Interrupt",

		"Coprocessor Fault", "Alignment Check", "Machine Check", "Reserved",
		"Reserved", "Reserved", "Reserved", "Reserved",

		"Reserved", "Reserved", "Reserved", "Reserved", "Reserved", "Reserved",
		"Reserved", "Reserved" };
/// Function pointer array of interrupt handlers
interrupt_handler_t interrupt_handlers[0xff];

/*
 unsigned int gs, fs, es, ds;      // pushed the segs last
 unsigned int edi, esi, ebp, useless_value, ebx, edx, ecx, eax;  // pushed by pusha. useless value is esp
 unsigned int int_no, err_code;    // our 'push byte #' and ecodes do this
 unsigned int eip, cs, eflags, useresp, ss; //pushed by the processor automatically
 */
//Handles interrupts
extern "C" void fault_handler(struct regs *r) {
	if (interrupt_handlers[r->int_no] != 0) {
		interrupt_handlers[r->int_no](r);
		return;
	} else {
		printk(LOG_FAIL, "fault", "code     | %d (error %d),(%s)\n", r->int_no,
				r->err_code, exception_messages[r->int_no]);
		printk(LOG_FAIL, "fault",
				"segment  | gs:0x%x fs:0x%x es:0x%x ds:0x%x cs:0x%x ss:0x%x\n",
				r->gs, r->fs, r->es, r->ds, r->cs, r->ss);
		printk(LOG_FAIL, "fault", "stack    | esp: 0x%x ebp: 0x%x uesp: 0x%x\n",
				r->useless_value, r->ebp, r->useresp);
		printk(LOG_FAIL, "fault",
				"gp regs  | eax: 0x%x ebx: 0x%x ecx: 0x%x edx: 0x%x\n", r->eax,
				r->ebx, r->ecx, r->edx);
		printk(LOG_FAIL, "fault",
				".......  | esi: 0x%x edi: 0x%x eip: 0x%x eflags: 0x%x \n",
				r->esi, r->edi, r->eip, r->eflags);
		log(L"Unassigned interrupt!\n");
	}
	if (r->int_no < 32) {
		printk(LOG_FAIL, "fault", "code     | %d (error %d),(%s)\n", r->int_no,
				r->err_code, exception_messages[r->int_no]);
		printk(LOG_FAIL, "fault",
				"segment  | gs:0x%x fs:0x%x es:0x%x ds:0x%x cs:0x%x ss:0x%x\n",
				r->gs, r->fs, r->es, r->ds, r->cs, r->ss);
		printk(LOG_FAIL, "fault", "stack    | esp: 0x%x ebp: 0x%x uesp: 0x%x\n",
				r->useless_value, r->ebp, r->useresp);
		printk(LOG_FAIL, "fault",
				"gp regs  | eax: 0x%x ebx: 0x%x ecx: 0x%x edx: 0x%x\n", r->eax,
				r->ebx, r->ecx, r->edx);
		printk(LOG_FAIL, "fault",
				".......  | esi: 0x%x edi: 0x%x eip: 0x%x eflags: 0x%x \n",
				r->esi, r->edi, r->eip, r->eflags);
		log(L"Interrupt fault");
	}
}

/** This installs a custom IRQ handler for the given IRQ **/
void register_interrupt_handler(uint8 n, interrupt_handler_t h) {
	interrupt_handlers[n] = h;

}

/** This clears the handler for a given IRQ **/
void deregister_interrupt_handler(uint8 n) {
	interrupt_handlers[n] = 0;
}
///Remaps the irq's in the PIC
void irq_remap(void) {
	uint8 always0; /* This will ALWAYS be set to 0! */
	outb(0x20, 0x11);
	outb(0xA0, 0x11);
	outb(0x21, 0x20);
	outb(0xA1, 0x28);
	outb(0x21, 0x04);
	outb(0xA1, 0x02);
	outb(0x21, 0x01);
	outb(0xA1, 0x01);
	outb(0x21, 0x0);
	outb(0xA1, 0x0);
}

void irq_install() {
	irq_remap();
	idt_set_gate(32, (uint64) irq0, 0x08, 0x8E);
	idt_set_gate(33, (uint64) irq1, 0x08, 0x8E);
	idt_set_gate(34, (uint64) irq2, 0x08, 0x8E);
	idt_set_gate(35, (uint64) irq3, 0x08, 0x8E);
	idt_set_gate(36, (uint64) irq4, 0x08, 0x8E);
	idt_set_gate(37, (uint64) irq5, 0x08, 0x8E);
	idt_set_gate(38, (uint64) irq6, 0x08, 0x8E);
	idt_set_gate(39, (uint64) irq7, 0x08, 0x8E);
	idt_set_gate(40, (uint64) irq8, 0x08, 0x8E);
	idt_set_gate(41, (uint64) irq9, 0x08, 0x8E);
	idt_set_gate(42, (uint64) irq10, 0x08, 0x8E);
	idt_set_gate(43, (uint64) irq11, 0x08, 0x8E);
	idt_set_gate(44, (uint64) irq12, 0x08, 0x8E);
	idt_set_gate(45, (uint64) irq13, 0x08, 0x8E);
	idt_set_gate(46, (uint64) irq14, 0x08, 0x8E);
	idt_set_gate(47, (uint64) irq15, 0x08, 0x8E);
	return;
}
///Handles IRQ's
extern "C" void irq_handler(struct regs *r) {
	/* This is a blank function pointer */
	if (interrupt_handlers[r->int_no] != 0) {
		interrupt_handlers[r->int_no](r);
	} else {
		//printk(LOG_WARN, "irq", "Recieved unhandled interrupt %d (IRQ%d)\n",r->int_no, r->int_no - 32);
		//log("Unhandled interrupt");
	}
	/* If the IDT entry that was invoked was greater than 40
	 *  (meaning IRQ8 - 15), then we need to send an EOI to
	 *  the slave controller */
	if (r->int_no >= 40) {
		outb(0xA0, 0x20);
	}

	/* In either case, we need to send an EOI to the master
	 *  interrupt controller too */
	outb(0x20, 0x20);
}

void init_idt() {
	idt_ptr.limit = sizeof(struct idt_entry) * 256 - 1;
	idt_ptr.base = (uint64) &idt_entries;

	memset((uint8*) &idt_entries, 0, sizeof(struct idt_entry) * 256);

	idt_init_isrs();
	idt_flush();
	irq_install();
}
