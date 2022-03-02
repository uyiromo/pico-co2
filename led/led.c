#include "led.h"

/*
 * Mask for ALL LED GPIO
 */
#define MASK_LED_PIN_ALL                                                       \
    (0x1 << LED_PIN_1) | (0x1 << LED_PIN_2) | (0x1 << LED_PIN_3) |             \
        (0x1 << LED_PIN_4) | (0x1 << LED_PIN_5) | (0x1 << LED_PIN_6) |         \
        (0x1 << LED_PIN_7) | (0x1 << LED_PIN_8) | (0x1 << LED_PIN_9) |         \
        (0x1 << LED_PIN_10) | (0x1 << LED_PIN_11) | (0x1 << LED_PIN_12) |      \
        (0x1 << LED_PIN_13) | (0x1 << LED_PIN_14) | (0x1 << LED_PIN_15) |      \
        (0x1 << LED_PIN_16)

/*
 * Mask for LED DIGs
 */
#define MASK_RED_DIG_ALL                                                       \
    ((MASK_RED_DIG1) | (MASK_RED_DIG2) | (MASK_RED_DIG3) | (MASK_RED_DIG4))
#define MASK_GRN_DIG_ALL                                                       \
    ((MASK_GRN_DIG1) | (MASK_GRN_DIG2) | (MASK_GRN_DIG3) | (MASK_GRN_DIG4))

/*
 * arrays for iteration
 */
const uint LED_MASK[16] = {LED_MASK_0, LED_MASK_1, LED_MASK_2, LED_MASK_3,
                           LED_MASK_4, LED_MASK_5, LED_MASK_6, LED_MASK_7,
                           LED_MASK_8, LED_MASK_9, LED_MASK_A, LED_MASK_B,
                           LED_MASK_C, LED_MASK_D, LED_MASK_E, LED_MASK_F};
const uint RED_MASK[4] = {
    MASK_GRN_DIG_ALL | MASK_RED_DIG2 | MASK_RED_DIG3 | MASK_RED_DIG4,
    MASK_GRN_DIG_ALL | MASK_RED_DIG1 | MASK_RED_DIG3 | MASK_RED_DIG4,
    MASK_GRN_DIG_ALL | MASK_RED_DIG1 | MASK_RED_DIG2 | MASK_RED_DIG4,
    MASK_GRN_DIG_ALL | MASK_RED_DIG1 | MASK_RED_DIG2 | MASK_RED_DIG3,
};
const uint GRN_MASK[4] = {
    MASK_RED_DIG_ALL | MASK_GRN_DIG2 | MASK_GRN_DIG3 | MASK_GRN_DIG4,
    MASK_RED_DIG_ALL | MASK_GRN_DIG1 | MASK_GRN_DIG3 | MASK_GRN_DIG4,
    MASK_RED_DIG_ALL | MASK_GRN_DIG1 | MASK_GRN_DIG2 | MASK_GRN_DIG4,
    MASK_RED_DIG_ALL | MASK_GRN_DIG1 | MASK_GRN_DIG2 | MASK_GRN_DIG3,
};
const uint MASK_DIG_ALL = MASK_RED_DIG_ALL | MASK_GRN_DIG_ALL;

/**
 * @brief Initialize GPIO pins connected to OSL40363-LRYG
 *
 * @details call `gpio_init_mask()`, then call `gpio_set_dir_out_masked()`
 *          LED Pins are defined in `MASK_LED_PIN_ALL`
 *
 * @param None
 * @return None
 *
 */
void init_led()
{
    gpio_init_mask(MASK_LED_PIN_ALL);
    gpio_set_dir_out_masked(MASK_LED_PIN_ALL);

    return;
}

/**
 * @brief Get BCD from the given value
 *
 * @details Generate BCD from the given `value`
 *          BCD is stored in the given `buf`
 *
 *
 * @param value
 *          raw value to put on LED
 * @param buf
 *          buffer for BCD of the `value`
 *          `buf` must be able to four uint
 *
 */
void get_bcd(uint value, uint *buf)
{
    int i;
    uint v;

    v = value;
    for (i = 3; i >= 0; --i) {
        buf[i] = (v % 10);
        v /= 10;
    }

    return;
}

/**
 * @brief Set the given value to LED
 *
 *
 * @param value
 *          the value to put on LED
 *          (value % 10000) will be used since the LED use BCD
 * @param color
 *          LED color.
 *          Must be either `RED` or `GREEN
 *
 */
void set_led(uint value, LED_COLOR color)
{
    int i;
    uint amask, cmask, mask;
    const uint *amasks;
    uint value_bcd[4];

    get_bcd(value, value_bcd);
    amasks = (color == RED) ? RED_MASK : GRN_MASK;
    for (i = 3; i >= 0; --i) {
        /* Generate mask from amask (anode mask) and cmask (cathode mask) */
        amask = amasks[i];
        cmask = LED_MASK[value_bcd[i]];
        mask = amask | cmask;

        /* set mask, sleep 100ms, clear cathodes */
        gpio_set_mask(mask);
        sleep_ms(1);
        gpio_clr_mask(mask);
    }

    return;
}