# Android.mk for Hello TA Host Application

LOCAL_PATH := $(call my-dir)

################################################################################
# Host Application — 用 Android 構建系統編譯
################################################################################
include $(CLEAR_VARS)

LOCAL_MODULE := hello_ta_test
LOCAL_MODULE_TAGS := optional
LOCAL_VENDOR_MODULE := true		# 安裝到 /vendor/bin/

LOCAL_SRC_FILES := host/main.c

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../optee_client/public

LOCAL_SHARED_LIBRARIES := libteec	# 連結 OP-TEE Client API 的 libteec.so

include $(BUILD_EXECUTABLE)

################################################################################
# TA Binary — 預編譯檔案，直接複製
################################################################################
include $(CLEAR_VARS)

LOCAL_MODULE := 8aaaf200-2450-11e4-abe2-0002a5d5c51b.ta
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := ETC
LOCAL_VENDOR_MODULE := true		
LOCAL_MODULE_PATH := $(TARGET_OUT_VENDOR)/lib/optee_armtz	# 安裝到 /vendor/lib/optee_armtz/
LOCAL_SRC_FILES := ta/out/8aaaf200-2450-11e4-abe2-0002a5d5c51b.ta

include $(BUILD_PREBUILT)