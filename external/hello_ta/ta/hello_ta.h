/*
 * Hello World TA - Header
 *
 * Simple TA to test OP-TEE environment
 */

#ifndef HELLO_TA_H
#define HELLO_TA_H

/* UUID for Hello World TA: 8aaaf200-2450-11e4-abe2-0002a5d5c51b */
#define HELLO_TA_UUID \
    { 0x8aaaf200, 0x2450, 0x11e4, \
        { 0xab, 0xe2, 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } }

/* Command IDs */
#define HELLO_TA_CMD_SAY_HELLO      0   // 印出訊息到 Secure World log
#define HELLO_TA_CMD_INC_VALUE      1   // 將傳入的數值 +1 後回傳

#endif /* HELLO_TA_H */
