#include "sensor.h"

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
void init_sensor()
{
    //  Baud Rate: 9600
    //   Data bit: 8 bytes
    //   Stop bit: 1 byte
    // Parity Bit: null
    // Don't use CTS/RTS
    uart_init(UART_ID, 9600);
    gpio_set_function(MHZ19C_TX, GPIO_FUNC_UART);
    gpio_set_function(MHZ19C_RX, GPIO_FUNC_UART);
    uart_set_format(UART_ID, 8, 1, UART_PARITY_NONE);

    return;
}

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
uint8_t get_checksum(uint8_t *cmd)
{
    uint8_t checksum;
    checksum = 0;
    for (int i = 0; i < 8; ++i) {
        checksum += cmd[i];
    }


    return (0xFF- checksum);
}

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
void set_self_calibration(bool enable)
{
    uint8_t cmd[9] = { 0xFF, 0x01, 0x79, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

    // Build cmd
    cmd[3] = enable ? 0xA0 : 0x00;
    cmd[8] = get_checksum(cmd);

    // Send
    uart_write_blocking(UART_ID, cmd, sizeof(cmd));

    return;
}

/**
 * @brief Read CO2 concentration
 *
 *
 * @param none
 *
 * @return positive if chcksum is valid, -1 for invalid response
 *
 */
int read_concentration()
{
    const int8_t tx[9] = {  0xFF, 0x01, 0x86, 0x00,
                         0x00, 0x00, 0x00, 0x00, 0x79 };
    uint8_t rx[9];
    uint8_t checksum;
    int concentration;

    // Send/Recv Read CO2 command
    uart_write_blocking(UART_ID, tx, sizeof(tx));
    uart_read_blocking(UART_ID, rx, sizeof(rx));

#if 0
    for (int i = 0; i < 10; ++i) {
        uint8_t r, c;
        r = uart_is_readable_within_us(UART_ID, 100*1000);
        c = r ? uart_getc(UART_ID) : -1;
        printf("rx[%i] = %02X (readable: %d)\n", i, c, r);
    }
#endif


    // sanity check
    concentration = rx[2] * 256 + rx[3];
    checksum = get_checksum(rx);

    return (checksum == rx[8]) ? concentration : -1;
}

