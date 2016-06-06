LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

# 遍历目录及子目录的函数
define walk
    $(wildcard $(1)) $(foreach e, $(wildcard $(1)/*), $(call walk, $(e)))
endef
  
# 遍历Classes目录
ALLFILES = $(call walk, $(LOCAL_PATH)/../../../../framework/cpp/sdk/pogo)
ALLFILES += $(call walk, $(LOCAL_PATH)/../../Classes)

FILE_LIST := hellocpp/main.cpp \
		   ../../../../framework/cpp/common/filesystem/linux/linux_support.cpp \
		   ../../../../framework/cpp/common/filesystem/basefilesystem.cpp \
		   ../../../../framework/cpp/common/filesystem/filesystem_stdio.cpp \
		   ../../../../framework/cpp/common/filesystem/packfile.cpp \
		   ../../../../framework/cpp/common/tier0/dbg.cpp \
		   ../../../../framework/cpp/common/tier0/linux/platform_linux.cpp \
		   ../../../../framework/cpp/common/tier0/memstd.cpp \
		   ../../../../framework/cpp/common/vstdlib/commandline.cpp \
		   ../../../../framework/cpp/common/vstdlib/keyvaluessystem.cpp \
		   ../../../../framework/cpp/common/vstdlib/random.cpp \
		   ../../../../framework/cpp/common/vstdlib/strtools.cpp \
		   ../../../../framework/cpp/sdk/valve/util/interface.cpp \
		   ../../../../framework/cpp/sdk/valve/util/mempool.cpp \
		   ../../../../framework/cpp/sdk/valve/util/utlbuffer.cpp \
		   ../../../../framework/cpp/sdk/valve/util/utlsymbol.cpp	   

# 从所有文件中提取出所有.cpp文件
FILE_LIST += $(filter %.cpp, $(ALLFILES))
  
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
					$(LOCAL_PATH)/../../../../framework/cpp/sdk/public \
					$(LOCAL_PATH)/../../../../framework/cpp/sdk/valve/public \
					$(LOCAL_PATH)/../../../../framework/cpp/sdk/pogo \
					$(LOCAL_PATH)/../../../../framework/cpp/sdk/boost/include \

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
