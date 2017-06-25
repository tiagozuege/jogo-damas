#include <io.h>
#include <serial.h>
#include <stdint.h>

#define S0                  0x03F8 /* Serial port 0 address */

#define SERIAL_RX           0x00 /* In:	Receive buffer (DLAB=0) */
#define SERIAL_TX           0x00 /* Out: Transmit buffer (DLAB=0) */
#define SERIAL_DLL          0x00 /* Out: Divisor Latch Low (DLAB=1) */
#define SERIAL_DLM          0x01 /* Out: Divisor Latch High (DLAB=1) */
#define SERIAL_IER          0x01 /* Out: Interrupt Enable Register */
#define SERIAL_IER_RDI      0x01 /* Enable receiver data interrupt */
#define SERIAL_IIR          0x02 /* In:	Interrupt ID Register */
#define SERIAL_FCR          0x02 /* Out: FIFO Control Register */
#define SERIAL_LCR          0x03 /* Out: Line Control Register */
#define	SERIAL_LCR_DLAB     0x80 /* Divisor latch access bit */
#define	SERIAL_LCR_WLEN8    0x03 /* Wordlength: 8 bits */
#define SERIAL_MCR          0x04 /* Out: Modem Control Register */
#define	SERIAL_MCR_RTS      0x02 /* RTS complement */
#define	SERIAL_MCR_DTR      0x01 /* DTR complement */
#define	SERIAL_MCR_OUT2     0x08 /* Out2 complement */
#define SERIAL_LSR          0x05 /* In:	Line Status Register */
#define SERIAL_LSR_DATA     0x01 /* Data available */
#define SERIAL_LSR_TXRDY    0x20 /* Transmit buffer available */
#define SERIAL_LSR_TSRE     0x40 /* Transmitter off */

void serial_putc(int c)
{
	int i;

	for (i = 0; !(inb(S0 + SERIAL_LSR) & SERIAL_LSR_TXRDY) && i < 12800; i++);

	outb(S0 + SERIAL_TX, c);
}

void serial_init(void)
{
	/* Turn off the FIFO. */
	outb(S0 + SERIAL_FCR, 0);

	/* Set speed. Requires DLAB latch. */
	outb(S0 + SERIAL_LCR, SERIAL_LCR_DLAB);
	outb(S0 + SERIAL_DLL, (uint8_t) (115200 / 9600));
	outb(S0 + SERIAL_DLM, 0);

	/* 8 data bits, 1 stop bit, parity off. Turn off DLAB latch. */
	outb(S0 + SERIAL_LCR, SERIAL_LCR_WLEN8 & ~SERIAL_LCR_DLAB);

	/* No modem controls. */
	outb(S0 + SERIAL_MCR, 0);

	/* Enable rcv interrupts. */
	outb(S0 + SERIAL_IER, SERIAL_IER_RDI);

    /* Clear any preexisting overrun indication and interrupts. */
	(void) inb(S0 + SERIAL_IIR);
	(void) inb(S0 + SERIAL_RX);
}

