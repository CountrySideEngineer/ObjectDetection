/*	//cv::String InputFile;
	//cv::String OutputFile;
 *
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

#ifdef _DEBUG
#define DETECT_DEBUG_IMAGE_ON	(1)
#else
#define DETECT_DEBUG_IMAGE_ON	(0)
#endif

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
 * Destructor.
 */
CDetectObject::~CDetectObject() {
#if DETECT_DEBUG_IMAGE_ON == 1
	try {
		destroyWindow("Gray");
		destroyWindow("Filtered");
		destroyWindow("Bin");
	}
	catch (exception &ex) {
		cout << "Window has not been opened." << endl;
		cout << ex.what() << endl;
	}
#endif	//DETECT_DEBUG_IMAGE_ON == 1
}

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
	Mat BinImage;
	Mat* ConvertedImage;

	ConvertedImage = this->Convert2Bin(SrcImage, (Mat*)(&BinImage));
	if (ConvertedImage != (Mat*)(&BinImage)) {
		cerr << "Image output err" << endl;

		return NULL;
	}

	vector< vector<Point> > Contours;
	findContours(mBin, Contours, CV_RETR_LIST, CHAIN_APPROX_SIMPLE);

	SrcImage->copyTo(*DstImage);
	for (unsigned int index = 0; index < Contours.size(); index++) {
		drawContours((Mat&)*DstImage, Contours, index, Scalar(0, 0, 255), 1);
	}

	return (Mat*)DstImage;
}

/**
 * Basic, common sequence to convert input image into bin-level image.
 * The sequence run in this method is that convert color image into gray
 * scale, filtering by Blur filter, and convert into bin-level image.
 *
 * @parma[in]	SrcImage	input image.
 * @param[out]	DstImage	Pointer to output image.
 */
Mat* CDetectObject::Convert2Bin(const Mat* SrcImage, Mat* DstImage) {
	assert(NULL != SrcImage);
	assert(NULL != DstImage);

	Size Filter(this->mFilterSize, this->mFilterSize);
	cvtColor(*SrcImage, this->mGray, COLOR_BGR2GRAY);
	blur(this->mGray, this->mFiltered, Filter);
	threshold(this->mFiltered, this->mBin, this->mThresh, this->mMaxValue, THRESH_BINARY);

	this->mBin.copyTo(*DstImage);

#if DETECT_DEBUG_IMAGE_ON == 1
	cv::imshow(cv::String("Gray"), this->mGray);
	cv::imshow(cv::String("Filtered"), this->mFiltered);
	cv::imshow(cv::String("Bin"), this->mBin);
#endif	//DETECT_DEBUG_IMAGE_ON == 1

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
