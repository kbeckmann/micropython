#include "uart.h"
#include "lib/utils/interrupt_char.h"
#include "timer0.h"
#include "generated/csr.h"
#include "py/mpconfig.h"
#include "py/runtime.h"

// Receive single character
static inline int mp_hal_stdin_rx_chr(void) {
    return uart_read();
}

// Send string of given length
static inline void mp_hal_stdout_tx_strn(const char *str, mp_uint_t len) {
    while (len--) {
               uart_write(*str++);
    }
}

static inline mp_uint_t mp_hal_ticks_ms(void) {
    mp_uint_t elapsed_us = timer0_get_ticks() / (CONFIG_CLOCK_FREQUENCY / 1000);
    return timer0_get_seconds() * 1000 + elapsed_us;
}

static inline mp_uint_t mp_hal_ticks_us(void) {
    mp_uint_t elapsed_us = timer0_get_ticks() / (CONFIG_CLOCK_FREQUENCY / 1000000);
    return timer0_get_seconds() * 1000000 + elapsed_us;
}

static inline mp_uint_t mp_hal_ticks_cpu(void) {
    return timer0_get_seconds() * CONFIG_CLOCK_FREQUENCY + timer0_get_ticks();
}

static inline void mp_hal_delay_ms(mp_uint_t ms) {
    const mp_uint_t t0 = mp_hal_ticks_ms();
    while (mp_hal_ticks_ms() - t0 < ms) {
        MICROPY_EVENT_POLL_HOOK
    }
}

static inline void mp_hal_delay_us(mp_uint_t us) {
    const mp_uint_t t0 = mp_hal_ticks_us();
    while (mp_hal_ticks_us() - t0 < us) {
        MICROPY_EVENT_POLL_HOOK
    }
}
