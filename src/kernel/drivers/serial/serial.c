#include <drivers/serial/serial.h>
#include <arch/i386/interrupt/pic.h>
#include <arch/i386/interrupt/irq.h>
#include <arch/i386/stdint.h>
#include <arch/i386/io.h>

static void com1_irq_handler(struct regs *r);
static void tx_out(void);
static inline uint8_t are_interrupts_enabled(void);
static void serial_poll_putc(char c);

static volatile uint8_t tx_head = 0;
static volatile uint8_t tx_tail = 0;
static char tx_buffer[TX_BUFFER_SIZE];

static inline uint8_t are_interrupts_enabled(void)
{
	uint32_t flags;
	__asm__ volatile(
		"pushf\n\t"
		"pop %0" : "=r"(flags)
		);
	return (flags & 0x200) != 0;
}

void serial_init(void)
{
	ns16550_init();
	irq_install_handler(4, com1_irq_handler);
	pic_enable_irq(4);

}

void serial_putc(char c)
{
	if (c == '\n') {
		serial_putc('\r');
	}

	if (!are_interrupts_enabled()) {
		serial_poll_putc(c);
		return;
	}

	tx_buffer[tx_head] = c;
	tx_head = (tx_head + 1) % TX_BUFFER_SIZE;

	// Enable TX interrupt
	outb(COM1_PORT + IER, 0x02);

}

void serial_puts(const char *str)
{
	for (int i = 0; str[i] != '\0'; i++) {
		serial_putc(str[i]);
	}
}

static void serial_poll_putc(char c)
{
	while ((inb(COM1_PORT + LSR) & 0x20) == 0);
	outb(COM1_PORT + THR, c);
}

static void tx_out(void)
{
		if (tx_head != tx_tail) {
			outb(COM1_PORT + THR, tx_buffer[tx_tail]);

			tx_tail = (tx_tail + 1) % TX_BUFFER_SIZE;
		}

		if (tx_head == tx_tail) {
			outb(COM1_PORT + IER, 0x00);

		}

}

static void com1_irq_handler(struct regs *r)
{
	(void)r; // not used yet

	uint8_t isr = inb(COM1_PORT + ISR);

	if ((isr & 0x0E) == 0x02) {
		tx_out();
	}
}
