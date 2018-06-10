/*
 * CHoughPObjectDetection.cpp
 *
 *  Created on: 2018/06/10
 *      Author: orca2
 */
#include <iostream>
#include "CHoughPObjectDetection.h"
#include "opencv/cv.h"
#include "opencv/cv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
using namespace std;

/**
 * Constructor with initial value of size of filter, and thresh and max value
 * used while transforming into bin image and Max.
 *
 * @param[in]	FilterSize
 * @param[in]	Thresh	Value ot thresh used in bin-level transform.
 * @param[in]	MaxValue	MaxValue for bin-level image.
 */
CHoughPObjectDetection::CHoughPObjectDetection(
		int FilterSize, int Thresh, int MaxValue)
	: CHoughObjectDetection(FilterSize, Thresh, MaxValue)
{}

/**
 * Destructor
 */
CHoughPObjectDetection::~CHoughPObjectDetection() {}

/**
 * Detect and mark white line detected by HoughP transform.
 *
 * @param[in]	Source image to scan.
 * @param[out]	Destination image to draw traffic signs.
 *
 * @return	An image traffic signs are detected and marked.
 */
Mat* CHoughPObjectDetection::Find(const Mat* SrcImage, const Mat* DstImage) {

	/*
	 * To accentuate the edge of border, convert the input image into
	 * 2 value scale, black and white.
	 */
	Mat BinImage;
	Mat* ConvertedImage;

	ConvertedImage = this->Convert2Bin(SrcImage, (Mat*)(&BinImage));
	if (ConvertedImage != (Mat*)(&BinImage)) {
		cerr << "Image output err" << endl;
	}

	vector<cv::Vec4i> Lines;
	cv::HoughLinesP(BinImage, Lines,
			(double)this->mRho,
			(double)this->mTheta,
			this->mVoteThresh);
//			80, 30);

	SrcImage->copyTo(*DstImage);

	for (int index = 0; index < (int)Lines.size(); index++) {
		line(*DstImage,
			Point(Lines[index][0], Lines[index][1]),
			Point(Lines[index][2], Lines[index][3]),
			cv::Scalar(0, 0, 255), 3, 8);
	}

	return NULL;
}
