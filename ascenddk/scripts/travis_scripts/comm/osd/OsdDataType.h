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

#ifndef INC_OSD_DATA_TYPE_H_
#define INC_OSD_DATA_TYPE_H_

#include <memory>
#include <string>
#include <cstdint>

// The memory size of the BGR image is 3 times that of width*height.
#define BGR_BUFFER_MULTIPLE 3

// The memory size of the YUV image is 1.5 times that of width*height.
#define YUV420SP_SIZE_MOLECULE    3
#define YUV420SP_SIZE_DENOMINATOR 2

namespace Ascend {
namespace Osd {
// Minimum width of image
const int MIN_WIDTH = 16;

// Maximum width of image
const int MAX_WIDTH = 4096;

// Minimum height of image
const int MIN_HEIGHT = 16;

// Maximum height of image
const int MAX_HEIGHT = 4096;

// Line connection mode: 4-connected line
const int CONNECT_LINE_4 = 4;

// Line connection mode: 8-connected line
const int CONNECT_LINE_8 = 8;

// Default depth of image in dvpp
const int DVPP_DEFAULT_BITWIDTH = 8;

// The minimum  deviation from the origin in horizontal direction.
const int DVPP_HORZ_MIN_DEVIATION = 0;

// The minimum deviation from the origin in the vertical direction.
const int DVPP_VERT_MIN_DEVIATION = 0;

// Image vertical magnification
const int DVPP_VERT_MAGNIFICATION = 1;

// Image horizontal magnification
const int DVPP_HORZ_MAGNIFICATION = 1;

// The number of pixels that text deviating from rectangle.
const int LABEL_PIXEL_MAGNIFICATION = 10;

// Call dvpp interface success
const int DVPP_INVOKE_SUCCESS = 0;

// Minimum radius of circle
const int MIN_RADIUS = 0;

// The result code returned by osd
enum ResultCode {
    DRAW_SUCCESS,
    DRAW_FAIL,
};

// Image format supported by dvpp
enum DvppImageFormat {
    YUV420_SEMI_PLANNAR = 0,
    YUV422_SEMI_PLANNAR,
    YUV444_SEMI_PLANNAR,
    YUV422_PACKED,
    YUV444_PACKED,
    RGB888_PACKED,
    XRGB8888_PACKED,
    YUV400_SEMI_PLANNAR,
    INVALID_IMAGE_TYPE,
};

// Image arrangement method supported by dvpp
enum DvppImageRankType {
    NV12 = 0,
    NV21,
    YUYV,
    YVYU,
    UYVY,
    YUV,
    RGB,
    BGR,
    RGBA,
    BGRA,
    ARGB,
    ABGR,
    INVALID_IMAGE_RANK_TYPE,
};

// Channel for input image
enum DvppChannelType {
    RDMA = 0,
    CVDR,
};

// Font type supported by OSD
enum FontType {
    FONT_SIMPLEX,
    FONT_PLAIN,
    FONT_DUPLEX,
    FONT_COMPLEX,
    FONT_TRIPLEX,
    FONT_COMPLEX_SMALL,
    FONT_SCRIPT_SIMPLEX,
    FONT_SCRIPT_COMPLEX,
    FONT_INVALID,
};

// Image format supported by osd
enum OsdImageFormat {
    YUV420SPNV12, // NV12
    IMAGE_INVALID,
};

// Color of drawing
struct Color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

// Coordinate points of drawing graphics
struct Coordinate {
    int32_t x;
    int32_t y;
};

// Rectangle point
struct RectanglePosition {
    Coordinate lt; // leftTop
    Coordinate rb; // rightBottom
};

// Image attribute
struct ImageAttribute {
    OsdImageFormat imageFormat;
    uint32_t width;
    uint32_t height;
    uint32_t size = 0;
    std::shared_ptr<uint8_t> data;
};

// Rectangle attribute
struct RectangleAttribute {
    RectanglePosition position;
    Color color = { 255, 255, 0 }; // default color: yellow
    int thickness = 1;
    int lineType = CONNECT_LINE_8;
};

// Circle attribute
struct CircleAttribute {
    Coordinate center;
    int radius;
    Color color = { 255, 255, 0 }; // default color: yellow
    int thickness = 1;
    int lineType = CONNECT_LINE_8;
};

// Text attribute
struct TextAttribute {
    std::string text;
    Coordinate position;
    FontType fontType = FONT_COMPLEX;
    Color color = { 255, 190, 0 }; // default color: deep yellow
    double fontScale = 0.5;
    int thickness = 1;
    int lineType = CONNECT_LINE_8;
};

// Rectangle and label attribute
struct RectangleLabelAttribute {
    RectangleAttribute rectAttr;
    TextAttribute textAttr;
};
}
}
#endif // !INC_OSD_DATA_TYPE_H_
