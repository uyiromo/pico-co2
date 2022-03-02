#include "hardware/gpio.h"
#include "pico/binary_info.h"
#include "pico/multicore.h"
#include "pico/stdlib.h"
#include <stdio.h>

#include "led.h"

uint led_value;

void control_led()
{
    uint v;
    while (1) {
        v = led_value;
        LED_COLOR c = (v % 2 == 0) ? GREEN : RED;
        set_led(v, c);
    }

    return;
}

int main()
{
    stdio_init_all();

    /* Initialize LED Pins */
    init_led();

    led_value = 0;
    multicore_launch_core1(control_led);
    while (1) {
        ++led_value;
        sleep_ms(1000);
    }

    return 0;
}
