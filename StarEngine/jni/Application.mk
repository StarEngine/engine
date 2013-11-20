LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

NDK_TOOLCHAIN_VERSION=4.8
APP_STL:=gnustl_static
APP_CFLAGS += -Wno-error=format-security
APP_GNUSTL_FORCE_CPP_FEATURES := exceptions rtti