/*
 * CDetectObject.cpp
 *
 *  Created on: 2018/05/20
 *      Author: orca2
 */
#include <iostream>
#include <vector>
#include "CDetectObject.h"
#include "opencv/cv.hpp"
#include "opencv2/highgui.hpp"
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
CDetectObject::CDetectObject(int FilterSize, int Thresh, int MaxValue)
	: mFilterSize((double)FilterSize)
	, mThresh((double)Thresh)
	, mMaxValue((double)MaxValue)
{}

/**
 * Detect and mark traffic object.
 *
 * @param[in]	Source image to scan.
 * @param[out]	Destination image to draw traffic signs.
 *
 * @return	An image traffic signs are detected and marked.
 */
Mat* CDetectObject::Find(const Mat* SrcImage, const Mat* DstImage) {

	/*
	 * To accentuate the edge of border, convert the input image into
	 * 2 value scale, black and white.
	 */
	Size Filter(this->mFilterSize, this->mFilterSize);
	cvtColor(*SrcImage, mGray, COLOR_BGR2GRAY);
	blur(mGray, mFiltered, Filter);
	threshold(mFiltered, mBin, this->mThresh, this->mMaxValue, THRESH_BINARY);

	vector< vector<Point> > Contours;
	findContours(mBin, Contours, CV_RETR_LIST, CHAIN_APPROX_SIMPLE);

	SrcImage->copyTo(*DstImage);
	for (unsigned int index = 0; index < Contours.size(); index++) {
		drawContours((Mat&)*DstImage, Contours, index, Scalar(0, 0, 255), 1);
	}

	return (Mat*)DstImage;
}

/**
 * Setup parameters used while object detection.
 *
 * @param[in]	Config	Key of field to set value.
 * @param[in]	Value	Value to set the field identified by argument Config.
 */
void CDetectObject::SetConfig(DETECT_OBJECT_CONFIG Config, int Value) {
	switch (Config) {
	case DETECT_OBJECT_CONFIG_FIL_SIZE:
		this->mFilterSize = Value;
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
void CDetectObject::SetConfig(DETECT_OBJECT_CONFIG Config, double Value) {
	switch (Config) {
	case DETECT_OBJECT_CONFIG_THRESH_THRESH:
		this->mThresh = Value;
		break;

	case DETECT_OBJECT_CONFIG_THRESH_MAXVAL:
		this->mMaxValue = Value;
		break;

	default:
		cerr << "Invalid argument.";
		throw invalid_argument("Invalid configuration field");
		break;
	}
}
