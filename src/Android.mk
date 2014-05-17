LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LS_CPP=$(subst $(1)/,,$(wildcard $(1)/*.cpp))
LS_CPP+= $(subst $(1)/,,$(wildcard $(1)/**/*.cpp))
LS_CPP+= $(subst $(1)/,,$(wildcard $(1)/**/**/*.cpp))
LS_CPP+= $(subst $(1)/,,$(wildcard $(1)/**/**/**/*.cpp))

LOCAL_MODULE    := starengine
LOCAL_CFLAGS 	:= -D FT_FREETYPE_H="freetype/freetype.h"
LOCAL_CPPFLAGS  := -std=gnu++11 -D STAR2D=1 -D LOGGER_MIN_LEVEL=1 -Ilibs\freetype\jni\include -Ilibs\libpng
LOCAL_SRC_FILES := $(call LS_CPP,$(LOCAL_PATH))

LOCAL_STATIC_LIBRARIES := android_native_app_glue freetype libpng

include $(BUILD_STATIC_LIBRARY)

$(call import-module,android/native_app_glue)

$(call import-add-path,libs)

$(call import-module,freetype)
$(call import-module,libpng)