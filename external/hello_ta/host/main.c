/*
 * Hello World TA - Host Application
 *
 * This runs in Normal World and calls the Hello TA in Secure World
*/

/*
    Normal World 的測試程式，使用 TEE Client API 流程：
    1. TEEC_InitializeContext() — 初始化 TEE context（連接 /dev/tee0）
    2. TEEC_OpenSession() — 以 UUID 開啟與 TA 的 session（觸發 tee-supplicant 載入 TA）
    3. TEEC_InvokeCommand(SAY_HELLO) — 呼叫 TA 的 SAY_HELLO 命令
    4. TEEC_InvokeCommand(INC_VALUE) — 傳入 42，預期回傳 43
    5. TEEC_CloseSession() + TEEC_FinalizeContext() — 清理資源
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tee_client_api.h>

/* UUID for Hello World TA */
static const TEEC_UUID hello_ta_uuid = {
    0x8aaaf200, 0x2450, 0x11e4,
    { 0xab, 0xe2, 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b }
};

/* Command IDs - must match TA */
#define HELLO_TA_CMD_SAY_HELLO  0
#define HELLO_TA_CMD_INC_VALUE  1

int main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)))
{
    TEEC_Result res;
    TEEC_Context ctx;
    TEEC_Session sess;
    TEEC_Operation op;
    uint32_t err_origin;

    printf("=== Hello TA Test Application ===\n\n");

    /* Initialize TEE context */
    printf("[1] Initializing TEE context...\n");
    res = TEEC_InitializeContext(NULL, &ctx);
    if (res != TEEC_SUCCESS) {
        fprintf(stderr, "TEEC_InitializeContext failed: 0x%x\n", res);
        return 1;
    }
    printf("    Success!\n\n");

    /* Open session with the TA */
    printf("[2] Opening session with Hello TA...\n");
    res = TEEC_OpenSession(&ctx, &sess, &hello_ta_uuid,
                           TEEC_LOGIN_PUBLIC, NULL, NULL, &err_origin);
    if (res != TEEC_SUCCESS) {
        fprintf(stderr, "TEEC_OpenSession failed: 0x%x origin 0x%x\n",
                res, err_origin);
        TEEC_FinalizeContext(&ctx);
        return 1;
    }
    printf("    Success!\n\n");

    /* Test 1: Say Hello */
    printf("[3] Calling HELLO_TA_CMD_SAY_HELLO...\n");
    memset(&op, 0, sizeof(op));
    op.paramTypes = TEEC_PARAM_TYPES(TEEC_NONE, TEEC_NONE,
                                     TEEC_NONE, TEEC_NONE);

    res = TEEC_InvokeCommand(&sess, HELLO_TA_CMD_SAY_HELLO, &op, &err_origin);
    if (res != TEEC_SUCCESS) {
        fprintf(stderr, "TEEC_InvokeCommand(SAY_HELLO) failed: 0x%x origin 0x%x\n",
                res, err_origin);
    } else {
        printf("    Success! (Check kernel log for TA message)\n\n");
    }

    /* Test 2: Increment Value */
    printf("[4] Calling HELLO_TA_CMD_INC_VALUE with value=42...\n");
    memset(&op, 0, sizeof(op));
    op.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INOUT, TEEC_NONE,
                                     TEEC_NONE, TEEC_NONE);
    op.params[0].value.a = 42;

    res = TEEC_InvokeCommand(&sess, HELLO_TA_CMD_INC_VALUE, &op, &err_origin);
    if (res != TEEC_SUCCESS) {
        fprintf(stderr, "TEEC_InvokeCommand(INC_VALUE) failed: 0x%x origin 0x%x\n",
                res, err_origin);
    } else {
        printf("    Success! TA returned value: %u (expected 43)\n\n",
               op.params[0].value.a);
    }

    /* Close session */
    printf("[5] Closing session...\n");
    TEEC_CloseSession(&sess);
    printf("    Done!\n\n");

    /* Finalize context */
    printf("[6] Finalizing TEE context...\n");
    TEEC_FinalizeContext(&ctx);
    printf("    Done!\n\n");

    printf("=== Test Complete ===\n");
    return 0;
}