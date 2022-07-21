LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := libwebsockets_static
LOCAL_MODULE_FILENAME := libwebsockets_static
LOCAL_SRC_FILES := ./lib/$(TARGET_ARCH_ABI)/libwebsockets.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_CPPFLAGS := -D__STDC_LIMIT_MACROS=1
LOCAL_EXPORT_CPPFLAGS := -D__STDC_LIMIT_MACROS=1
include $(PREBUILT_STATIC_LIBRARY)
