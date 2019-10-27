#include <stdint.h>

void timer0_init(void);
void timer0_isr(void);
uint32_t timer0_get_ticks(void);
uint32_t timer0_get_seconds(void);
uint64_t timer0_get_time_ms(void);
uint64_t timer0_get_time_ticks(void);