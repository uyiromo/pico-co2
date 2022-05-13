#include "hardware/gpio.h"
#include "pico/binary_info.h"
#include "pico/multicore.h"
#include "pico/stdlib.h"
#include <stdio.h>

#include "led.h"
#include "sensor.h"

uint led_value;

void control_led()
{
    uint v;
    while (1) {
        v = led_value;
        LED_COLOR c = (v > 800) ? RED : GREEN;
        set_led(v, c);
    }

    return;
}

int main()
{
    stdio_init_all();

    /* Initialize */
    init_led();
    init_sensor();

    led_value = 0;
    multicore_launch_core1(control_led);
    while (true) {
        // Read MH-Z19C every 60 seconds
        uint c = read_concentration();
        led_value = (c > 0) ? c : led_value;

        sleep_ms(60 * 1000);
    }

    return 0;
}
