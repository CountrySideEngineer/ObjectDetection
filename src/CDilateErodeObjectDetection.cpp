/*
 * CDilateObjectDetection.cpp
 *
 *  Created on: 2018/06/14
 *      Author: orca2
 */
#include "CDilateErodeObjectDetection.h"

#include <iostream>
#include <vector>
#include "opencv/cv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
using namespace std;
using namespace cv;

/**
 * Constructor with default argument.
 *
 * @param[in]	FilterSize	Size of filter used in object detection.
 * @param[in]	Thresh		Threshold value used to change image into binary format.
 * @param[in]	MaxValue	Max value used to change image into binary format.
 */
CDilateErodeObjectDetection::CDilateErodeObjectDetection(int FilterSize, int Thresh, int MaxValue)
	: CDetectObject(FilterSize, Thresh, MaxValue)
{}

/**
 * Destructor.
 */
CDilateErodeObjectDetection::~CDilateErodeObjectDetection() {}

/**
 * Basic, common sequence to convert input image into bin-level image.
 * Additional to that of base class, the output image is treated by "dilate" operation.
 *
 * @parma[in]	SrcImage	input image.
 * @param[out]	DstImage	Pointer to output image.
 */
Mat* CDilateErodeObjectDetection::Convert2Bin(const Mat* SrcImage, Mat* DstImage) {
	Mat BinImage;
	Mat DilateImage;

	Mat* BaseBinImage = CDetectObject::Convert2Bin(SrcImage, (Mat*)(&BinImage));
	if (BaseBinImage != (Mat*)(&BinImage)) {
		cerr << "Image output err" << endl;

		return NULL;
	}


	dilate(BinImage, DilateImage, Mat::eye(20, 20, CV_8UC1), Point(-1, -1), 5);
	erode(DilateImage, (Mat&)(*DstImage), Mat::eye(20, 20, CV_8UC1), Point(-1, -1), 5);

	return DstImage;
}
