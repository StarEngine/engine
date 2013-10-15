LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LS_CPP=$(subst $(1)/,,$(wildcard $(1)/*.cpp))
LS_CPP+= $(subst $(1)/,,$(wildcard $(1)/**/*.cpp))
LS_CPP+= $(subst $(1)/,,$(wildcard $(1)/**/**/*.cpp))
LS_CPP+= $(subst $(1)/,,$(wildcard $(1)/**/**/**/*.cpp))
LOCAL_MODULE    := stargame
LOCAL_CPPFLAGS  := -std=gnu++11 -D STAR2D=1 -D LOGGER_MIN_LEVEL=1
LOCAL_SRC_FILES := $(call LS_CPP,$(LOCAL_PATH))
LOCAL_LDLIBS    := -landroid -llog -lEGL -lGLESv1_CM -lGLESv2 -lOpenSLES
APP_PLATFORM := android-14
APP_OPTIM := debug

LOCAL_STATIC_LIBRARIES := android_native_app_glue png starengine

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)
$(call import-module,libpng)

$(call import-add-path,$(CURDIR))
$(call import-module,StarEngine/jni)