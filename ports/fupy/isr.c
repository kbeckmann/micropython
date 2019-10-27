#include <generated/csr.h>
#include <irq.h>
#include <uart.h>
#include <timer0.h>

void isr(void)
{
	unsigned int irqs;

	irqs = irq_pending() & irq_getmask();

	if(irqs & (1 << UART_INTERRUPT))
		uart_isr();

	if(irqs & (1 << TIMER0_INTERRUPT))
		timer0_isr();
}
