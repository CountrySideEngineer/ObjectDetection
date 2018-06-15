/*
 * CRoiObjectDetection.cpp
 *
 *  Created on: 2018/06/15
 *      Author: orca2
 */
#include <iostream>
#include <vector>
#include "CRoiObjectDetection.h"
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
CRoiObjectDetection::CRoiObjectDetection(int FilterSize, int Thresh, int MaxValue)
	: CDilateErodeObjectDetection(FilterSize, Thresh, MaxValue) {}

CRoiObjectDetection::~CRoiObjectDetection()
{
	destroyWindow(String("Lower right side"));
	destroyWindow(String("Lower left side"));
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
Mat* CRoiObjectDetection::Find(const Mat* SrcImage, const Mat* DstImage) {

	Mat* BinImageRet = NULL;

	SrcImage->copyTo(*DstImage);
	Mat DstImageCopy;
	DstImage->copyTo(DstImageCopy);

	//Lower right side.
	Rect RoiLowRight(320, 240, 320, 240);
	Mat DstImageRoiLowRight = DstImageCopy(RoiLowRight);
	BinImageRet = this->Find((Mat*)(&DstImageRoiLowRight));
	if (NULL == BinImageRet) {
		return NULL;
	}

	//Lower left side.
	Rect RoiLowLeft(0, 240, 320, 240);
	Mat DstImageRoiLowLeft = DstImageCopy(RoiLowLeft);
	BinImageRet = this->Find((Mat*)(&DstImageRoiLowLeft));
	if (NULL == BinImageRet) {
		return NULL;
	}

	imshow(String("Lower right side"), DstImageRoiLowRight);
	imshow(String("Lower left side"), DstImageRoiLowLeft);

	try {
		DstImageCopy.copyTo(*DstImage);
	} catch (cv::Exception &ex) {
		cerr << ex.msg << endl;
	}
	return (Mat*)DstImage;
}

Mat* FindContouers(Mat* TargetImage) {
	return NULL;
}
