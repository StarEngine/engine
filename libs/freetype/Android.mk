LOCAL_PATH:= $(call my-dir)
 
include $(CLEAR_VARS)
 
LOCAL_MODULE := freetype
LOCAL_SRC_FILES := jni/libfreetype.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/jni/include $(LOCAL_PATH)/jni/include/freetype
 
include $(PREBUILT_STATIC_LIBRARY)