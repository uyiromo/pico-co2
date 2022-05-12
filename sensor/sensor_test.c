#include "hardware/gpio.h"
#include "pico/binary_info.h"
#include "pico/multicore.h"
#include "pico/stdlib.h"
#include <stdio.h>

#include "sensor.h"

int main()
{
    stdio_init_all();

    /* Initialize sensor Pins */
    init_sensor();

    while (true) {
        /* read concentration */
        int concentration = read_concentration();
        printf("current concentration: %d\n", concentration);

        sleep_ms(100);
    }

    return 0;
}
