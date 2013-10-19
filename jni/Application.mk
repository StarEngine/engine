LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

override APP_MIN_PLATFORM_LEVEL=99
NDK_TOOLCHAIN_VERSION=4.8
APP_STL:=gnustl_static
APP_CFLAGS += -Wno-error=format-security
APP_GNUSTL_FORCE_CPP_FEATURES := exceptions rtti