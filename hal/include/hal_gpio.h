#ifndef HAL_GPIO_H
#define HAL_GPIO_H

#include "io430.h"

#define hal_gpio_func_peripheral(port, pin)                             hal_gpio_func_peripheral_prep(port, pin) // set pin function to peripheral
#define hal_gpio_func_io(port, pin)                                     hal_gpio_func_io_prep(port, pin) // set pin function to I/O
#define hal_gpio_dir_output(port, pin)                                  hal_gpio_dir_output_prep(port, pin) // set pin direction to output
#define hal_gpio_dir_input(port, pin)                                   hal_gpio_dir_input_prep(port, pin) // set pin direction to input
#define hal_gpio_out_high(port, pin)                                    hal_gpio_out_high_prep(port, pin) // set pin output to high
#define hal_gpio_out_low(port, pin)                                     hal_gpio_out_low_prep(port, pin) // set pin output to low
#define hal_gpio_in(port, pin)                                          hal_gpio_in_prep(port, pin) // pin input state (zero for low, non-zero for high)

/* IAR preprocessor is stupid and doesn't resolve arguments well */
#define hal_gpio_func_peripheral_prep(port, pin)                             {P##port##SEL |= BIT##pin##;} // set pin function to peripheral
#define hal_gpio_func_io_prep(port, pin)                                     {P##port##SEL &= ~BIT##pin##;} // set pin function to I/O
#define hal_gpio_dir_output_prep(port, pin)                                  {P##port##DIR |= BIT##pin##;} // set pin direction to output
#define hal_gpio_dir_input_prep(port, pin)                                   {P##port##DIR &= ~BIT##pin##;} // set pin direction to input
#define hal_gpio_out_high_prep(port, pin)                                    {P##port##OUT |= BIT##pin##;} // set pin output to high
#define hal_gpio_out_low_prep(port, pin)                                     {P##port##OUT &= ~BIT##pin##;} // set pin output to low
#define hal_gpio_in_prep(port, pin)                                          (P##port##IN & BIT##pin##) // pin input state (zero for low, non-zero for high)

#endif