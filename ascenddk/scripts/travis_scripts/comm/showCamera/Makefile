TOPDIR      := $(patsubst %,%,$(CURDIR))
DDK_HOME := /root/tools/che/ddk/ddk
CC := aarch64-linux-gnu-g++
CPP := aarch64-linux-gnu-g++
#CC := g++
#CPP := g++

LOCAL_MODULE_NAME := showCamera
CC_FLAGS := -std=c++11

local_src_files := \
        $(TOPDIR)/showCamera.cpp \

local_inc_dirs := \
        $(TOPDIR) \
        $(DDK_HOME)/include/inc/dvpp \
        $(DDK_HOME)/include/inc \
        $(DDK_HOME)/include/third_party/protobuf/include \
        $(DDK_HOME)/include/third_party/cereal/include \
        $(DDK_HOME)/include/third_party/opencv/include \
        $(DDK_HOME)/include/libc_sec/include \

local_shared_libs_dirs := \
        $(DDK_HOME)/lib/aarch64-linux-gcc5.4 \

local_shared_libs := \
        hiai_server \
        hiai_common \
        matrixdaemon \
        fmk_common \
        drvdevdrv \
        drvhdc \
        drvhdc_host \
        drvtcp  \
        mmpa \
        crypto \
        c_sec \
        runtime \
        teec \
        npu_drv \
        pthread \
        cce \
        cce_aicpudev \
        cce_aicore \
        protobuf \
        rt  \
        profilerclient \
        slog \
        dl \
        opencv_world \
        OMX_Core \
        OMX_Core_VENC \
        Dvpp_api \
        Dvpp_vpc \
        OMX_common   \
        OMX_hisi_vdec_core   \
        OMX_hisi_video_decoder  \
        OMX_hisi_video_encoder \
        Dvpp_png_decoder \
        Dvpp_jpeg_decoder \
        Dvpp_jpeg_encoder \
        media_mini \

Q := @

FULL_SRC_FILES        := $(local_src_files)
FULL_INC_DIRS         := $(foreach inc_dir, $(local_inc_dirs), -I$(inc_dir))
SHARED_LIBRARIES      := $(foreach shared_lib, $(local_shared_libs), -l$(shared_lib))
SHARED_LIBRARIES_DIRS := $(foreach shared_lib_dir, $(local_shared_libs_dirs), -L$(shared_lib_dir) -Wl,-rpath-link,$(shared_lib_dir))

LOCAL_OBJ_PATH        := $(TOPDIR)/out
LOCAL_LIBRARY         := $(LOCAL_OBJ_PATH)/$(LOCAL_MODULE_NAME)
FULL_C_SRCS           := $(filter %.c,$(FULL_SRC_FILES))
FULL_C_OBJS           := $(patsubst $(TOPDIR)/%.c,$(LOCAL_OBJ_PATH)/%.o, $(FULL_C_SRCS))
FULL_CPP_SRCS         := $(filter %.cpp,$(FULL_SRC_FILES))
FULL_CPP_OBJS         := $(patsubst $(TOPDIR)/%.cpp,$(LOCAL_OBJ_PATH)/%.o, $(FULL_CPP_SRCS))

all: do_pre_build do_build

do_pre_build:
        $(Q)echo - do [$@]
        $(Q)rm -rf $(LOCAL_OBJ_PATH)
        $(Q)mkdir -p $(LOCAL_OBJ_PATH)

do_build: $(LOCAL_LIBRARY) | do_pre_build
        $(Q)echo - do [$@]

$(LOCAL_LIBRARY): $(FULL_C_OBJS) $(FULL_CPP_OBJS) | do_pre_build
        $(Q)echo [LD] $@
        $(CPP) $(CC_FLAGS) -o $(LOCAL_LIBRARY) $(FULL_C_OBJS) $(FULL_CPP_OBJS) -Wl,--whole-archive  -Wl,--no-whole-archive -Wl,--start-group  -Wl,--end-group $(SHARED_LIBRARIES_DIRS) $(SHARED_LIBRARIES)

$(FULL_C_OBJS): $(LOCAL_OBJ_PATH)/%.o : $(TOPDIR)/%.c  | do_pre_build
        $(Q)echo [CC] $@
        $(Q)mkdir -p $(dir $@)
        $(CPP) $(CC_FLAGS)  $(FULL_INC_DIRS) -c $< -o $@

$(FULL_CPP_OBJS): $(LOCAL_OBJ_PATH)/%.o : $(TOPDIR)/%.cpp  | do_pre_build
        $(Q)echo [CC] $@
        $(Q)mkdir -p $(dir $@)
        $(CPP) $(CC_FLAGS) $(FULL_INC_DIRS) -c $< -o $@
