#ifndef HAL_TIMER_H
#define HAL_TIMER_H

extern volatile unsigned long hal_timer_ticks; // number of miliseconds since boot

void hal_timer_init(void);

#endif