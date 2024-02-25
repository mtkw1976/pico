#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"
#include "hardware/divider.h"

// UART defines
// By default the stdout UART is `uart0`, so we will use the second one
#define UART_ID uart1
#define BAUD_RATE 9600

// Use pins 4 and 5 for UART1
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define UART_TX_PIN 4
#define UART_RX_PIN 5

// GPIO defines
#define LED_RED 10
#define LED_GREEN 11
#define LED_BLUE 12
#define GP13 13
#define GP14 14
#define GP15 15

int main()
{
    bool led_red_state, led_green_state, led_blue_state;
    uint32_t gpio_in_value;

    stdio_init_all();
#if 0 /* you should not use it for USB UART */
    // Set up our UART
    uart_init(UART_ID, BAUD_RATE);
    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
#endif    

    // GPIO initialisation.
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_init(GP13);
    gpio_set_dir(GP13, GPIO_IN);
    gpio_pull_up(GP13);
    gpio_init(GP14);
    gpio_set_dir(GP14, GPIO_IN);
    gpio_pull_up(GP14);
    gpio_init(GP15);
    gpio_set_dir(GP15, GPIO_IN);
    gpio_pull_up(GP15);
   
 #if 0 /* no use */
    // Example of using the HW divider. The pico_divider library provides a more user friendly set of APIs 
    // over the divider (and support for 64 bit divides), and of course by default regular C language integer
    // divisions are redirected thru that library, meaning you can just use C level `/` and `%` operators and
    // gain the benefits of the fast hardware divider.
    int32_t dividend = 123456;
    int32_t divisor = -321;
    // This is the recommended signed fast divider for general use.
    divmod_result_t result = hw_divider_divmod_s32(dividend, divisor);
    printf("%d/%d = %d remainder %d\n", dividend, divisor, to_quotient_s32(result), to_remainder_s32(result));
    // This is the recommended unsigned fast divider for general use.
    int32_t udividend = 123456;
    int32_t udivisor = 321;
    divmod_result_t uresult = hw_divider_divmod_u32(udividend, udivisor);
    printf("%d/%d = %d remainder %d\n", udividend, udivisor, to_quotient_u32(uresult), to_remainder_u32(uresult));
#endif

    while (true) {
        led_red_state   = gpio_get(GP13);
        led_green_state = gpio_get(GP14);
        led_blue_state  = gpio_get(GP15);
        if (led_red_state == false) {
            gpio_put(LED_RED, 1);
        }
        else {
            gpio_put(LED_RED, 0);
        }
        if (led_green_state == false) {
            gpio_put(LED_GREEN, 1);
        }
        else {
            gpio_put(LED_GREEN, 0);
        }
        if (led_blue_state == false) {
            gpio_put(LED_BLUE, 1);
        }
        else {
            gpio_put(LED_BLUE, 0);
        }
        gpio_in_value = gpio_get_all();
        printf("GPIO IN : 0x%08x.\n", gpio_in_value);
    }

    return 0;
}
