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

#ifndef INC_OSD_API_H_
#define INC_OSD_API_H_

#include <vector>
#include "OsdDataType.h"
#include "toolchain/slog.h"

#define MODULE_ID_OSD ASCENDDK
#define ASC_OSD_LOG_ERROR(fmt, ...) \
dlog_error(MODULE_ID_OSD, "[%s:%d]" fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define ASC_OSD_LOG_INFO(fmt, ...) \
dlog_info(MODULE_ID_OSD, "[%s:%d]" fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)

namespace Ascend {
namespace Osd {

/**
 * @brief Draw one or more rectangles on the original image
 * @param [in] srcImgAttr: all required attributes of image
 * @param [in] rectAttrs: all required attributes of rectangles
 * @param [out] dstImg: image data after draw rectangles
 * @return DRAW_SUCCESS:draw rectangle success
 *         DRAW_FAIL:draw rectangle fail
 */
int DrawRectangle(const ImageAttribute &srcImgAttr,
                  const std::vector<RectangleAttribute> &rectAttrs,
                  std::shared_ptr<uint8_t> &dstImg);

/**
 * @brief Draw one or more rectangles and labels on the original image
 * @param [in] srcImgAttr: all required attributes of image
 * @param [in] rectLabelAttrs: all required attributes of rectangles and labels
 * @param [out] dstImg: image data after draw rectangles and labels
 * @return DRAW_SUCCESS:draw rectangle and label success
 *         DRAW_FAIL:draw rectangle and label fail
 */
int DrawRectangleAndLabel(
        const ImageAttribute &srcImgAttr,
        const std::vector<RectangleLabelAttribute> &rectLabelAttrs,
        std::shared_ptr<uint8_t> &dstImg);

/**
 * @brief Draw one or more circles on the original image
 * @param [in] srcImgAttr: all required attributes of image
 * @param [in] cirAttrs: all required attributes of circles
 * @param [out] dstImg: image data after draw circles
 * @return DRAW_SUCCESS:draw circle success
 *         DRAW_FAIL:draw circle fail
 */
int DrawCircle(const ImageAttribute &srcImgAttr,
               const std::vector<CircleAttribute> &cirAttrs,
               std::shared_ptr<uint8_t> &dstImg);

/**
 * @brief Draw one or more text on the original image
 * @param [in] srcImgAttr: all required attributes of image
 * @param [in] textAttrs: all required attributes of text
 * @param [out] dstImg: image data after draw text
 * @return DRAW_SUCCESS:draw text success
 *         DRAW_FAIL:draw text fail
 */
int PutText(const ImageAttribute &srcImgAttr,
            const std::vector<TextAttribute> &textAttrs,
            std::shared_ptr<uint8_t> &dstImg);
}
}

#endif // !INC_OSD_API_H_
