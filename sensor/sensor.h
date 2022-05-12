#ifndef SENSOR_H_INCLUDED
#define SENSOR_H_INCLUDED

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"

/*
 *
 * Definitions
 *
 */

/*
 * MH-Z19C Pin <--> Pico GPIO Mapping
 */
#define UART_ID   (uart1)
#define MHZ19C_HD (1)
#define MHZ19C_TX (4)  // UART1 TX
#define MHZ19C_RX (5)  // UART1 RX


/*
 *
 * Prototypes
 *
 */

/**
 * @brief Initialize UART pins connected to MHZ19C
 *
 * @details initialize MHZ19C_TX and MHZ19C_RX according to
 *              https://akizukidenshi.com/download/ds/winsen/MH-Z19C_20210518.pdf
 *
 * @param None
 * @return None
 *
 */
void init_sensor();

/**
 * @brief Return checksum for the given cmd
 * @detail https://akizukidenshi.com/download/ds/winsen/MH-Z19C_20210518.pdf
 *
 * @param cmd
 *          The packet to send/receive
 *
 * @return checksum
 *
 */
uint8_t get_checksum(uint8_t *cmd);

/**
 * @brief Enable/Disable Self-Caliblation for Zero Point
 *
 *
 * @param enable
 *          True for ON, False for OFF
 *
 * @return no return value
 *
 */
void set_self_calibration(bool enable);

/**
 * @brief Read CO2 concentration
 *
 *
 * @param none
 *
 * @return positive if chcksum is valid, -1 for invalid response
 *
 */
int read_concentration();

#endif
