/*
 * =======================================================================
 * Copyright (C), 2018, Huawei Tech. Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * =======================================================================
 */

#ifndef DVPPPROCESS_H_
#define DVPPPROCESS_H_

#include "securec.h"
#include "dvpp/idvppapi.h"
#include "dvpp/dvpp_config.h"
#include "toolchain/slog.h"

namespace Ascend {
namespace Utils {
#define ASC_LOG_ERROR(fmt, ...) \
dlog_error(ASCENDDK, "[%s:%d] " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)

// The memory size of the BGR image is 3 times that of width*height.
#define DVPP_BGR_BUFFER_MULTIPLE 3

// The memory size of the YUV image is 1.5 times that of width*height.
#define DVPP_YUV420SP_SIZE_MOLECULE    3
#define DVPP_YUV420SP_SIZE_DENOMINATOR 2


#define VPC_WIDTH_ALGIN 128

#define VPC_HEIGHT_ALGIN 16

#define VPC_ADDRESS_ALGIN 128

#define JPEGE_WIDTH_ALGIN 16


#define DVPP_RETURN_ERROR -1

#define DVPP_RETURN_OK 0
const unsigned int JPEGE_ADDRESS_ALGIN = 128;

// Bgr image need memory align
const int IMAGE_NEED_ALIGN = 0;

// Bgr image don't need memory align
const int IMAGE_NOT_NEED_ALIGN = 1;

struct ErrorDescription {
    int code;
    std::string codeInfo;
};

enum DvppEncodeType {
    H265_MAIN = 0, // H265-main level
    H264_BASE = 1, // H264-baseline level
    H264_MAIN = 2, // H264-main level
    H264_HIGH = 3, // H264-high level
};

enum YuvType {
    YUV420SP, // YUV420 semi-planner
    YVU420SP, // YVU420 semi-planner
};

enum CaptureObjFlag {
    JPEG, // convert to jpg
    H264, // convert to h264
    YUV, // convert to yuv
};

enum DvppErrorCode {
    DVPP_OPERATION_OK = 0,
    DVPP_ERROR_INVALIDPATAMETER = -1,
    DVPP_ERROR_MALLOCFAIL = -2,
    DVPP_ERROR_CREATEDVPPFAIL = -3,
    DVPP_ERROR_DVPPCTLFAIL = -4,
    DVPP_ERROR_NOOUTPUTINFO = -5,
    DVPP_ERROR_MEMCPYFAIL = -6,
};

#define CHECK_MEMCPY_RESULT(ret, buffer) \
if (ret != EOK) { \
    ASC_LOG_ERROR("Failed to copy memory,Ret=%d.", ret); \
    unsigned char *pBuf = buffer; \
    if (pBuf != nullptr){ \
        delete[] pBuf; \
    } \
    return DVPP_ERROR_MEMCPYFAIL; \
}

#define CHECK_VPC_MEMCPY_S_RESULT(errRet, inBuffer, piDvppApi) \
if (errRet != EOK) { \
    ASC_LOG_ERROR("Failed to copy memory,Ret=%d.", errRet); \
    if (inBuffer != nullptr) \
    { \
        free(inBuffer); \
    } \
    IDVPPAPI *dvppApi = piDvppApi; \
    if (piDvppApi != nullptr) \
    { \
        DestroyDvppApi(dvppApi); \
    } \
    return DVPP_ERROR_MEMCPYFAIL; \
}

struct ResolutionRatio {
    int width = 0;
    int height = 0;
};

struct DvppToJpgPara {
    // used to indicate the input format.
    eEncodeFormat format = JPGENC_FORMAT_NV12;

    // used to indicate the output quality while output is jpg.
    int level = 100;

    // image resolution.
    ResolutionRatio resolution;
};

struct DvppToH264Para {
    // coding protocol. 0:H265-main level 1:H264-baseline level
    //                  2:H264-main level 3:H264-high level
    int codingType = 3;

    // YUV storage method.0:YUV420 semi-planner 1:YVU420 semi-planner
    int yuvStoreType = 0;

    // resolution
    ResolutionRatio resolution;
};

struct DvppToYuvPara {
    int imageType = 0; // Dvpp image format
    int rank = 0;  // Image arrangement format
    int bitwidth = 0; // Image bit depth
    int cvdrOrRdma = 0; // Image path.default is cvdr
    ResolutionRatio resolution; // Image resolution
    int hmax = 0; // The maximum deviation from the origin in horizontal direction
    int hmin = 0; // The minimum deviation from the origin in horizontal direction
    int vmax = 0; // The maximum deviation from the origin in vertical direction
    int vmin = 0; // The minimum deviation from the origin in vertical direction
    double hinc = 0; // Horizontal magnification
    double vinc = 0; // Vertical magnification
};

struct DvppOutput {
    // output buffer
    unsigned char *pbuf;

    // size of output buffer
    unsigned int size;
};

struct DvppPara {
    DvppToJpgPara jpgPara;
    DvppToH264Para h264Para;
    DvppToYuvPara yuvPara;
};

/*
 *
 */
class DvppProcess {
 public:
    /**
     * @brief class constructor
     * @param [in] DvppToJpgPara para: instance jpg object.
     */
    DvppProcess(const DvppToJpgPara &para);

    /**
     * @brief class constructor
     * @param [in] DvppToJpgPara para: instance h264 object
     */
    DvppProcess(const DvppToH264Para &para);

    /**
     * @brief class constructor
     * @param [in] DvppToYuvPara para: instance yuv object
     */
    DvppProcess(const DvppToYuvPara &para);

    //class destructor
    virtual ~DvppProcess();

    /**
     * @brief Dvpp change from yuv to jpg or h264(if you use jpg object,
     *        then dvpp output jpeg data.if you use h264 object,then dvpp
     *        output h264 data.)
     * @param [in] char *pInputBuf: yuv data buffer
     *             (dvpp need char *,so pInputBuf do not use const)
     * @param [in] int inputSize  : size of yuv data buffer
     * @param [out]DvppOutput *pOutData :dvpp output buffer and size
     * @return  enum DvppErrorCode
     */
    int DvppOperationProc(char *pInputBuf, int inputSize, DvppOutput *pOutData);

    /**
     * @brief get a error message according to error code.
     * @param [in] int code: error code.
     */
    void PrintErrorInfo(int code) const;

    /**
     * @brief get conversion mode.
     * @param [in] enum CaptureObjFlag: conversion mode.
     */
    int GetMode() const;

 private:
    /**
     * @brief Dvpp change from yuv to jpg
     * @param [in] char *pInputBuf: yuv data buffer*/
    
