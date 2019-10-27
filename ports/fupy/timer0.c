#include "timer0.h"
#include "irq.h"
#include "generated/csr.h"

static uint32_t elapsed_seconds = 0;

void timer0_init(void) {
    int t;

    /* Configure timer in periodic mode with a 1s period. */
    timer0_en_write(0);
    timer0_ev_pending_write(timer0_ev_pending_read());
    timer0_ev_enable_write(1);
    irq_setmask(irq_getmask() | (1 << TIMER0_INTERRUPT));
    t = CONFIG_CLOCK_FREQUENCY;
    timer0_load_write(t);
    timer0_reload_write(t);
    timer0_en_write(1);
}

void timer0_isr(void) {
    elapsed_seconds += 1;
    timer0_ev_pending_write(1);
}

uint32_t timer0_get_ticks(void) {
    timer0_update_value_write(1);
    return timer0_reload_read() - timer0_value_read();
}

uint32_t timer0_get_seconds(void) {
    return elapsed_seconds;
}

uint64_t timer0_get_time_ticks(void) {
    uint64_t ticks = timer0_get_ticks();
    uint64_t s = elapsed_seconds;
    return s * CONFIG_CLOCK_FREQUENCY + ticks;
}