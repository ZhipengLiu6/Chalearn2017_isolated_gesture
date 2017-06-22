#ifndef VIPL_FACE_DETECTOR_H
#define VIPL_FACE_DETECTOR_H

#include "VIPLStruct.h"

/** @enum VIPLFaceView
 *  Flags indicating view of faces.
 */
enum VIPLFaceView {
	Frontal = 0x1L,
	Profile = 0x2L
};

/** @class VIPLFaceDetector VIPLFaceDetector.h
 *  @brief The face detector.
 */
class VIPLFaceDetector
{
public:
	/** A constructor with an optional argument specifying path of the model file.
     *  If called with no argument, the model file is assumed to be stored in the
	 *  the working directory as "VIPLFaceDetector4.0.dat".
	 *  
	 *  @note
	 *  If the detector fails to load the model file, then it will terminate the
	 *  program after outputing an error message to the standard error stream.
	 *
	 *  @param modelPath Path of the model file, either absolute or relative to
	 *                   the working directory)
	 */
	VIPL_API VIPLFaceDetector(const char* modelPath = nullptr);

	/** A Destructor which should never be called explicitly.
	 *  Release all dynamically allocated resources.
	 */
	VIPL_API ~VIPLFaceDetector();

	/** Detect faces on the given grayscale image.
	 *  If a multi-channel image is passed in, the detector will return immediately
	 *  without performing detection.
	 *  
	 *  @note
	 *  If OpenMP is enabled, this method could run with at most 4 threads.
	 *
	 *  @note
	 *  It is not supported to detect faces on multiple images simultaneously. In
	 *  order to achieve this, one can create multiple instances of `FaceDetector`
	 *  class - one for each image, and use different instances with different images.
	 *
	 *  @param image A grayscale image.
	 *  @return The number of face detected. -1 if somehow no detection is performed.
     *  @see VIPLImageData
	 */
	VIPL_API int32_t Detect(const VIPLImageData & image);

	/** Get faces detected on the last given image.
	 *  
	 *  @note
	 *  The returned pointer should never be deleted outside!
	 *
	 *  @param[out] faceNum Number of faces detected (i.e. returned)
	 *  @return A pointer to an array of `VIPLFaceInfo`.
     *  @see VIPLFaceInfo
	 */
	VIPL_API const VIPLFaceInfo* const GetDetections(int32_t* faceNum = nullptr) const;

	/** Get faces detected on the last given image, whose scores are no less than
	 *  the specified value.
	 *  Scores given by the detector to detections indicates how likely a detection
	 *  is truly a face (larger values preferred). By specifying the `minScore`, one
	 *  only get detections whose scores are no less than the `minScore`. In such
	 *  cases, the assigned value of the `faceNum` argument may be different from the
	 *  one return by `Detect()`.
	 *
	 *  The `faceNum` pointer is not expected to be `nullptr`, or no detections will
	 *  be returned.
     *  
	 *  @note
	 *  The returned pointer should never be deleted outside!
	 *
	 *  @param      minScore Minimum score to take a detection truly as a face.
	 *  @param[out] faceNum Number of faces detected (i.e. returned)
	 *  @return A pointer to an array of `VIPLFaceInfo`.
     *  @see VIPLFaceInfo
	 */
	VIPL_API const VIPLFaceInfo* const GetDetections(int32_t* faceNum, float minScore) const;

	/** Return only one detection on the last given image.
	 *  The returned detection should be the "best" one in most cases. Here the "best"
	 *  actually means a trade-off between the score, position, and size. If no face
	 *  is detected, then an "empty" face will returned, i.e. face with size of zero.
	 *
	 *  @note
	 *  Currently positions are not considered.
	 *  
	 *  @return VIPLFaceInfo The detected face, or an "empty" one.
	 *  @see VIPLFaceInfo
	 */
	VIPL_API VIPLFaceInfo GetOneDetection() const;

	/** Set the minimum size of faces to detect.
	 *  Size of a face is measured by the width/height of the detected bounding box,
	 *  which is a square. The size should be no less than 20 (default), and a smaller
	 *  value will be ignored.
	 *
	 *  @param size The minimum size of wanted faces.
	 */
	VIPL_API void SetMinFaceSize(int32_t size);

	/** Set the maximum size of faces to detect.
	 *  The maximum face size actually used is computed as the minimum among: user
	 *  specified size, image width, image height.
	 *  
	 *  @param size The maximum size of wanted faces.
	 *  @see SetMinFaceSize()
	 */
	VIPL_API void SetMaxFaceSize(int32_t size);

	/** Set the view flag of faces to detect.
	 *  The detector will detect faces in a certain view only if the cooresponding flag
	 *  is set ON, i.e. the bit is set to 1. The argument value can be the bitwise OR of
	 *  multiple `VIPLFaceView` flags.
	 *
	 *  @note
	 *  When the detector is set to detect frontal faces only, it runs faster with the
	 *  same input image.
	 *  
	 *  @param view Flag indicating the face view of interest.
	 *  @return Current view flag.
	 *  @see VIPLFaceView
	 */
	VIPL_API void SetView(int32_t view = VIPLFaceView::Frontal | VIPLFaceView::Profile);

	/** Adjusting the performance of the detector.
	 *  This is a trade-off between false alarm rate and recall rate, as well as speed.
	 *  Higher recall rate is achieved at the cost of either increased false alarm rate
	 *  or slower speed, or both.
	 *
	 *  Larger values (higher levels) means higher recall rate. There are only 5 valid
	 *  levels, i.e 1, 2, ..., 5. Values less than 1 or greater than 5 will be taken as
	 *  1 and 5 respectively. The default level is 2.
	 *
	 *  @note
	 *  It is recommend to use level 2 and 4. Level 3 will result in slow speed.
	 *
	 *  @param level A value in {1, 2, ..., 5} indicating the performance of the detector.
	 */
	VIPL_API void SetPerformanceLevel(int32_t level);

	/** Adjusting the speed of the detector.
	 *  This is a trade-off between speed and consumption of computational resources, as
	 *  well as performance. Faster speed will result in either increased consumption of
	 *  computational resources or decreased performance, or both.
	 *  
	 *  Larger values (higher levels) means faster speed. There are only 4 valid levels,
	 *  i.e. 1, 2, 3 and 4. Values less than 1 or greater than 4 will be taken as 1 and 4
	 *  respectively. The default level is 3.
	 *
	 *  @note
	 *  Faster speed requires that OpenMP be enabled.
	 *  
	 *  @param level A value of 1, 2, 3 or 4 indicating the speed of detector.
	 */
	VIPL_API void SetSpeedLevel(int32_t level);

private:
	class Impl;
	Impl* mImpl;
};

#endif