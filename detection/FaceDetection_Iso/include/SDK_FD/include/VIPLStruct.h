#ifndef VIPL_STRUCT_H
#define VIPL_STRUCT_H

#ifdef VIPL_EXPORTS
#define VIPL_API __declspec(dllexport)
#else
#define VIPL_API __declspec(dllimport)
#endif

#include <cstdlib>

/** Definition for fixed-width integer types.
 *  It is assumed that the code be compiled with MSVC.
 */
#if _MSC_VER > 1500
#include <cstdint>
#else
typedef signed char int8_t;
typedef short int16_t;
typedef int int32_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
#endif

/** @struct VIPLImageData VIPLStruct.h
 ** @brief Storing data of an image.
 *  Note that the pixel values are expected to be stored in a row-major style,
 *  and it is assumed no padding is used, i.e. pixel values are continuously
 *  stored one after the other.
 *  For RGB (multi-channel) images, data are expected to be stored by pixel and
 *  channels are stored in the order of BGR, i.e. B-G-R-B-G-R- ... -B-G-R. This
 *  is consistent with `cv::Mat` in OpenCV.
 */
typedef struct VIPLImageData {
	VIPLImageData()
	{
		data = NULL;
		width = 0;
		height = 0;
		channels = 0;
	}

	VIPLImageData(int32_t _width, int32_t _height, int32_t _channels = 1)
	{
		data = NULL;
		width = _width;
		height = _height;
		channels = _channels;
	}

	uint8_t* data;
	int32_t width;
	int32_t height;
	int32_t channels;
} VIPLImageData;

/** @struct VIPLFaceInfo VIPLStruct.h
 *  @brief Information of detected faces.
 *  The four parameters of the bounding boxes are stored. The score of a face
 *  indicates how likely it is truely a face (Larger values are preferred).
 *  @see VIPLFaceDetector
 */
typedef struct {
	/* rectangle bounding box */

	int32_t x;
	int32_t y;
	int32_t width;
	int32_t height;

	/* view of face (Euler angle) */

	double roll;  /**< rotation around x aixs */
	double pitch; /**< rotation around y axis */
	double yaw;   /**< rotation around z axis */

	double score;
} VIPLFaceInfo;

/**
 * @struct VIPLPoint VIPLStruct.h
 * @brief 2D point.
 */
typedef struct {
    double x;
    double y;
} VIPLPoint;

#endif
