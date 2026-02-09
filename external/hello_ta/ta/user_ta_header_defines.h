/*
 * Hello World TA - User TA Header Defines
 */

#ifndef USER_TA_HEADER_DEFINES_H
#define USER_TA_HEADER_DEFINES_H

#include "hello_ta.h"

#define TA_UUID             HELLO_TA_UUID
#define TA_FLAGS            TA_FLAG_EXEC_DDR    // TA 在 DDR 記憶體中執行
#define TA_STACK_SIZE       (2 * 1024)          // 2KB stack
#define TA_DATA_SIZE        (32 * 1024)         // 32KB data/heap

#define TA_CURRENT_TA_EXT_PROPERTIES \
    { "gp.ta.description", USER_TA_PROP_TYPE_STRING, "Hello World TA" }, \
    { "gp.ta.version", USER_TA_PROP_TYPE_U32, &(const uint32_t){ 0x0010 } }

#endif /* USER_TA_HEADER_DEFINES_H */