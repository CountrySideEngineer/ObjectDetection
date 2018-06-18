/*
 * CRoiObjectDetection.cpp
 *
 *  Created on: 2018/06/15
 *      Author: orca2
 */
#include <iostream>
#include <vector>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "CRoiObjectDetection.h"
#include "opencv/cv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
using namespace std;
using namespace cv;

#define DETECT_DEBUG_IMAGE_ON	(1)
#define CALC_DETECT_TIME		(1)
/**
 * Constructor with default argument.
 *
 * @param[in]	FilterSize	Size of filter used in object detection.
 * @param[in]	Thresh		Threshold value used to change image into binary format.
 * @param[in]	MaxValue	Max value used to change image into binary format.
 */
CRoiObjectDetection::CRoiObjectDetection(int FilterSize, int Thresh, int MaxValue)
	: CDilateErodeObjectDetection(FilterSize, Thresh, MaxValue) {}

CRoiObjectDetection::~CRoiObjectDetection()
{
#if DETECT_DEBUG_IMAGE_ON == 1
	destroyWindow(String("Lower right side"));
	destroyWindow(String("Lower left side"));
#endif
}

/**
 * Draw contours into argument TargetImage.
 *
 * @param[in,out]	TargetImage	Pointer to image input and detected image will
 * 								be drawn.
 * @return	Returns pointer to image
 */
Mat* CRoiObjectDetection::Find(Mat* TargetImage) {
	Mat BinImage;
	Mat* BinImageRet = NULL;

	BinImageRet = this->Convert2Bin(TargetImage, (Mat*)&BinImage);
	if (BinImageRet != (&BinImage)) {
		cerr << "Image output err!" << endl;

		return NULL;
	}

	vector< vector<Point> > Contours;
	findContours(BinImage, Contours, CV_RETR_LIST, CHAIN_APPROX_SIMPLE);
	for (unsigned int index = 0; index < Contours.size(); index++) {
		drawContours((Mat&)(*TargetImage), Contours, index, Scalar(0, 0, 255), 5);
	}

	return TargetImage;
}

/**
 * Detect and mark traffic object.
 * The area of handling image is limited.
 *
 * @paran[in]	SrcImage	Source image to scan.
 * @param[out]	DstImage	Image detected object will be drawn.
 * @return	Returns pointer to image the objected detected is drawn if the sequence
 * 			has finished successfully, otherwise returns NULL.
 */
Mat* CRoiObjectDetection::Find(const Mat* SrcImage, const Mat* DstImage)
{
#if CALC_DETECT_TIME == 1
	timeval StartTime;
	gettimeofday(&StartTime, NULL);
#endif	//CALC_DETECT_TIME == 1

	Mat* BinImageRet = NULL;

	SrcImage->copyTo(*DstImage);
	Mat DstImageCopy;
	DstImage->copyTo(DstImageCopy);

	//Lower right side.
	int Height = SrcImage->rows;
	int Width = SrcImage->cols;
	int HeightHalf = Height / 2;
	int WidthHalf = Width / 2;

	Rect RoiLowRight(WidthHalf, HeightHalf, WidthHalf, HeightHalf);
	Mat DstImageRoiLowRight = DstImageCopy(RoiLowRight);
	BinImageRet = this->Find((Mat*)(&DstImageRoiLowRight));
	if (NULL == BinImageRet) {
		return NULL;
	}

	//Lower left side.
	Rect RoiLowLeft(0, HeightHalf, WidthHalf, HeightHalf);
	Mat DstImageRoiLowLeft = DstImageCopy(RoiLowLeft);
	Mat RotateImage;
	cv::flip(DstImageRoiLowLeft, RotateImage, 1);
	BinImageRet = this->Find((Mat*)(&RotateImage));
	if (NULL == BinImageRet) {
		return NULL;
	}
	cv::flip(RotateImage, DstImageRoiLowLeft, 1);

#if DETECT_DEBUG_IMAGE_ON == 1
	imshow(String("Lower right side"), DstImageRoiLowRight);
	imshow(String("Lower left side"), RotateImage);
#endif

	try {
		DstImageCopy.copyTo(*DstImage);
	} catch (cv::Exception &ex) {
		cerr << ex.msg << endl;
	}

#if CALC_DETECT_TIME == 1
	timeval EndTime;
	gettimeofday(&EndTime, NULL);

	long PassedTime = ((EndTime.tv_sec * 1000) + (EndTime.tv_usec / 1000)) -
			((StartTime.tv_sec * 1000) + (StartTime.tv_usec / 1000));
	cout << "Passed time = " << PassedTime << " millisecond" << endl;
#endif	//CALC_DETECT_TIME == 1

	return (Mat*)DstImage;
}
