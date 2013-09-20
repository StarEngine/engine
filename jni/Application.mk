LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

NDK_TOOLCHAIN_VERSION=4.8
APP_STL:=stlport_static
APP_CFLAGS += -Wno-error=format-security