#ifndef LED_H_INCLUDED
#define LED_H_INCLUDED

#include "pico/stdlib.h"

/*
 *
 * Definitions
 *
 */

/*
 * LED color
 */
typedef enum { GREEN, RED } LED_COLOR;

/*
 * OSL40363-LRYG Pin <--> Pico GPIO Mapping
 */
#define LED_PIN_1 (15)
#define LED_PIN_2 (14)
#define LED_PIN_3 (13)
#define LED_PIN_4 (12)
#define LED_PIN_5 (11)
#define LED_PIN_6 (10)
#define LED_PIN_7 (9)
#define LED_PIN_8 (8)
#define LED_PIN_9 (26)
#define LED_PIN_10 (22)
#define LED_PIN_11 (21)
#define LED_PIN_12 (20)
#define LED_PIN_13 (19)
#define LED_PIN_14 (18)
#define LED_PIN_15 (17)
#define LED_PIN_16 (16)

/*
 * OSL40363-LRYG Pin Alias
 */
#define GRN_DIG1 (LED_PIN_1)
#define GRN_DIG2 (LED_PIN_4)
#define GRN_DIG3 (LED_PIN_7)
#define GRN_DIG4 (LED_PIN_8)
#define RED_DIG1 (LED_PIN_16)
#define RED_DIG2 (LED_PIN_14)
#define RED_DIG3 (LED_PIN_11)
#define RED_DIG4 (LED_PIN_9)
#define SEG_A (LED_PIN_13)
#define SEG_B (LED_PIN_10)
#define SEG_C (LED_PIN_6)
#define SEG_D (LED_PIN_3)
#define SEG_E (LED_PIN_2)
#define SEG_F (LED_PIN_12)
#define SEG_G (LED_PIN_15)
#define DIG_DP (LED_PIN_5)

/*
 * OSL40363-LRYG Mask on Pico GPIO
 */
#define MASK_GRN_DIG1 (0x1 << GRN_DIG1)
#define MASK_GRN_DIG2 (0x1 << GRN_DIG2)
#define MASK_GRN_DIG3 (0x1 << GRN_DIG3)
#define MASK_GRN_DIG4 (0x1 << GRN_DIG4)
#define MASK_RED_DIG1 (0x1 << RED_DIG1)
#define MASK_RED_DIG2 (0x1 << RED_DIG2)
#define MASK_RED_DIG3 (0x1 << RED_DIG3)
#define MASK_RED_DIG4 (0x1 << RED_DIG4)
#define MASK_SEG_A (0x1 << SEG_A)
#define MASK_SEG_B (0x1 << SEG_B)
#define MASK_SEG_C (0x1 << SEG_C)
#define MASK_SEG_D (0x1 << SEG_D)
#define MASK_SEG_E (0x1 << SEG_E)
#define MASK_SEG_F (0x1 << SEG_F)
#define MASK_SEG_G (0x1 << SEG_G)
#define MASK_SEG_DP (0x1 << SEG_DP)

/*
 * 7-seg LED mask
 * A, B, C, D, E, F, G, and DP assign:
 *
 *  +---<A>---+
 *  |         |
 * <F>       <B>
 *  |         |
 *  +---<G>---+
    |         |
 * <E>       <C>
 *  |         |
 *  +---<D>---+   <DP>
 *
 */
#define LED_MASK_0                                                             \
    (MASK_SEG_A | MASK_SEG_B | MASK_SEG_C | MASK_SEG_D | MASK_SEG_E |          \
     MASK_SEG_F)
#define LED_MASK_1 (MASK_SEG_B | MASK_SEG_C)
#define LED_MASK_2                                                             \
    (MASK_SEG_A | MASK_SEG_B | MASK_SEG_E | MASK_SEG_D | MASK_SEG_G)
#define LED_MASK_3                                                             \
    (MASK_SEG_A | MASK_SEG_B | MASK_SEG_C | MASK_SEG_D | MASK_SEG_G)
#define LED_MASK_4 (MASK_SEG_B | MASK_SEG_C | MASK_SEG_F | MASK_SEG_G)
#define LED_MASK_5                                                             \
    (MASK_SEG_A | MASK_SEG_C | MASK_SEG_D | MASK_SEG_F | MASK_SEG_G)
#define LED_MASK_6                                                             \
    (MASK_SEG_A | MASK_SEG_C | MASK_SEG_D | MASK_SEG_E | MASK_SEG_F |          \
     MASK_SEG_G)
#define LED_MASK_7 (MASK_SEG_A | MASK_SEG_B | MASK_SEG_C | MASK_SEG_F)
#define LED_MASK_8                                                             \
    (MASK_SEG_A | MASK_SEG_B | MASK_SEG_C | MASK_SEG_D | MASK_SEG_E |          \
     MASK_SEG_F | MASK_SEG_G)
#define LED_MASK_9                                                             \
    (MASK_SEG_A | MASK_SEG_B | MASK_SEG_C | MASK_SEG_D | MASK_SEG_F |          \
     MASK_SEG_G)
#define LED_MASK_A                                                             \
    (MASK_SEG_A | MASK_SEG_B | MASK_SEG_C | MASK_SEG_E | MASK_SEG_F |          \
     MASK_SEG_G)
#define LED_MASK_B                                                             \
    (MASK_SEG_C | MASK_SEG_D | MASK_SEG_E | MASK_SEG_F | MASK_SEG_G)
#define LED_MASK_C (MASK_SEG_A | MASK_SEG_D | MASK_SEG_E | MASK_SEG_F)
#define LED_MASK_D                                                             \
    (MASK_SEG_B | MASK_SEG_C | MASK_SEG_D | MASK_SEG_E | MASK_SEG_G)
#define LED_MASK_E                                                             \
    (MASK_SEG_A | MASK_SEG_D | MASK_SEG_E | MASK_SEG_F | MASK_SEG_G)
#define LED_MASK_F (MASK_SEG_A | MASK_SEG_E | MASK_SEG_F | MASK_SEG_G)

/*
 *
 * Prototypes
 *
 */

/**
 * @brief Initialize GPIO pins connected to OSL40363-LRYG
 *
 * @details call `gpio_init_mask()`, then call `gpio_set_dir_out_masked()`
 *          LED Pins are defined in `LED_PIN_MASK`
 *
 * @param None
 * @return None
 *
 */
void init_led();

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
void get_bcd(uint value, uint *buf);

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
void set_led(uint value, LED_COLOR color);

#endif