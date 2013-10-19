LOCAL_PATH:= $(call my-dir)
 
include $(CLEAR_VARS)
 
LOCAL_MODULE := freetype
LOCAL_SRC_FILES := lib/libfreetype.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include $(LOCAL_PATH)/include/freetype
 
include $(PREBUILT_STATIC_LIBRARY)