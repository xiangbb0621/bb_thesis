/*
	TA_CreateEntryPoint() — TA 載入時呼叫
	TA_DestroyEntryPoint() — TA 卸載時呼叫
	TA_OpenSessionEntryPoint() — 建立 session 時呼叫
	TA_CloseSessionEntryPoint() — 關閉 session 時呼叫
	TA_InvokeCommandEntryPoint() — 處理命令：
		SAY_HELLO：使用 IMSG() 在 Secure World 輸出 "Hello from Secure World!"
		INC_VALUE：接收 TEE_PARAM_TYPE_VALUE_INOUT 參數，將 params[0].value.a++ 後回傳
*/


/*
 * Hello World TA - Implementation
 *
 * Simple TA to test OP-TEE environment
 */

#include <tee_internal_api.h>
#include <tee_internal_api_extensions.h>
#include "hello_ta.h"

/*
 * Called when the TA is created (loaded)
 */
TEE_Result TA_CreateEntryPoint(void)
{
    DMSG("Hello TA: CreateEntryPoint");
    return TEE_SUCCESS;
}

/*
 * Called when the TA is destroyed (unloaded)
 */
void TA_DestroyEntryPoint(void)
{
    DMSG("Hello TA: DestroyEntryPoint");
}

/*
 * Called when a new session is opened
 */
TEE_Result TA_OpenSessionEntryPoint(uint32_t param_types,
                                    TEE_Param params[4],
                                    void **sess_ctx)
{
    uint32_t exp_param_types = TEE_PARAM_TYPES(TEE_PARAM_TYPE_NONE,
                                               TEE_PARAM_TYPE_NONE,
                                               TEE_PARAM_TYPE_NONE,
                                               TEE_PARAM_TYPE_NONE);

    (void)params;
    (void)sess_ctx;

    DMSG("Hello TA: OpenSessionEntryPoint");

    if (param_types != exp_param_types)
        return TEE_ERROR_BAD_PARAMETERS;

    return TEE_SUCCESS;
}

/*
 * Called when the session is closed
 */
void TA_CloseSessionEntryPoint(void *sess_ctx)
{
    (void)sess_ctx;
    DMSG("Hello TA: CloseSessionEntryPoint");
}

/*
 * Called when a command is invoked
 */
TEE_Result TA_InvokeCommandEntryPoint(void *sess_ctx,
                                      uint32_t cmd_id,
                                      uint32_t param_types,
                                      TEE_Param params[4])
{
    (void)sess_ctx;

    switch (cmd_id) {
    case HELLO_TA_CMD_SAY_HELLO:
        IMSG("Hello from Secure World!");
        return TEE_SUCCESS;

    case HELLO_TA_CMD_INC_VALUE:
        if (TEE_PARAM_TYPE_GET(param_types, 0) != TEE_PARAM_TYPE_VALUE_INOUT)
            return TEE_ERROR_BAD_PARAMETERS;

        IMSG("Received value: %u", params[0].value.a);
        params[0].value.a++;
        IMSG("Returning value: %u", params[0].value.a);
        return TEE_SUCCESS;

    default:
        return TEE_ERROR_BAD_PARAMETERS;
    }
}