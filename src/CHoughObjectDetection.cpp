/*
 * CHoughObjectDetection.cpp
 *
 *  Created on: 2018/06/10
 *      Author: orca2
 */

#include <iostream>
#include <math.h>
#include "CHoughObjectDetection.h"
#include "opencv/cv.h"
#include "opencv/cv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
using namespace std;

CHoughObjectDetection::CHoughObjectDetection(
		int FilterSize, int Thresh, int MaxValue)
	: CDetectObject(FilterSize, Thresh, MaxValue)
{
	this->mRho = 1;
	this->mTheta = CV_PI / 180;	//unit: radian
	this->mVoteThresh = 60;
	this->mSrn = 0;
	this->mStn = 0;
}

CHoughObjectDetection::~CHoughObjectDetection() {}

/**
 * Detect and mark white line detected by Hough transform.
 *
 * @param[in]	Source image to scan.
 * @param[out]	Destination image to draw traffic signs.
 *
 * @return	An image traffic signs are detected and marked.
 */
Mat* CHoughObjectDetection::Find(const Mat* SrcImage, const Mat* DstImage) {

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

	vector<cv::Vec2f> Lines;
	cv::HoughLines(mBin, Lines,
			(double)this->mRho,
			(double)this->mTheta,
			this->mVoteThresh);

	SrcImage->copyTo(*DstImage);
	for (int index = 0; index < (int)Lines.size(); index++) {
		float rho = Lines[index][0];
		float theta = Lines[index][0];
		double a = cos(theta);
		double b = sin(theta);
		double x0 = a * rho;
		double y0 = b * rho;
		Point Point1(cvRound(x0 + 1000 * (-b)),
				cvRound(y0 + 1000 * a));
		Point Point2(cvRound(x0 - 1000 * (-b)),
				cvRound(y0 - 1000 * a));
		cv::line(*DstImage, Point1, Point2, cv::Scalar(0, 0, 255), 3, 8);

	}

	return (Mat*)DstImage;
}



/**
 * Setup parameters used while object detection.
 *
 * @param[in]	Config	Key of field to set value.
 * @param[in]	Value	Value to set the field identified by argument Config.
 */
void CHoughObjectDetection::SetConfig(DETECT_OBJECT_HOUGH_CONFIG Config, int Value) {
	switch (Config) {
	case DETECT_OBJECT_HOUGH_CONFIG_RHO:
		this->mRho = Value;
		break;

	case DETECT_OBJECT_HOUGH_CONFIG_THETA:
		this->mTheta = Value;
		break;

	case DETECT_OBJECT_HOUGH_CONFIG_THRESH:
		this->mVoteThresh = Value;
		break;

	default:
		cerr << "Invalid argument.";
		throw invalid_argument("Invalid configuration field");
		break;
	}
}

/**
 * Setup parameters used while object detection.
 *
 * @param[in]	Config	Key of field to set value.
 * @param[in]	Value	Value to set the field identified by argument Config.
 */
void CHoughObjectDetection::SetConfig(DETECT_OBJECT_HOUGH_CONFIG Config, double Value) {
	switch (Config) {
	case DETECT_OBJECT_HOUGH_CONFIG_SRN:
		this->mSrn = Value;
		break;

	case DETECT_OBJECT_HOUGH_CONFIG_STN:
		this->mStn = Value;
		break;

	default:
		cerr << "Invalid argument.";
		throw invalid_argument("Invalid configuration field");
		break;
	}
}
