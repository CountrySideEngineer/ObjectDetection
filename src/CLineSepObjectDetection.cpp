/*
 * CLineSepObjectDetection.cpp
 *
 *  Created on: 2018/06/23
 *      Author: orca2
 */
#include <iostream>
#include "CLineSepObjectDetection.h"
using namespace std;

/**
 * Constructor with default argument.
 *
 * @param[in]	FilterSize	Size of filter used in object detection.
 * @param[in]	Thresh		Threshold value used to change image into binary format.
 * @param[in]	MaxValue	Max value used to change image into binary format.
 */
CLineSepObjectDetection::CLineSepObjectDetection(int FilterSize, int Thresh, int MaxValue)
: CDilateErodeObjectDetection(FilterSize, Thresh, MaxValue) {}

/**
 *	Destructor.
 */
CLineSepObjectDetection::~CLineSepObjectDetection() { }

/**
 * Draw contours into argument TargetImage.
 *
 * @param[in,out]	TargetImage	Pointer to image input and detected image will
 * 								be drawn.
 * @return	Returns pointer to image
 */
Mat* CLineSepObjectDetection::Find(Mat* TargetImage) {
	Mat BinImage;
	Mat* BinImageRet = NULL;

	BinImageRet = this->Convert2Bin(TargetImage, (Mat*)&BinImage);
	if (BinImageRet != (&BinImage)) {
		cerr << "Image output err!" << endl;

		return NULL;
	}

	vector< vector<Point> > Contours;
	findContours(BinImage, Contours, CV_RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	for (unsigned int index = 0; index < Contours.size(); index++) {
		drawContours((Mat&)(*TargetImage), Contours, index, Scalar(0, 0, 255), 5);
	}

	return TargetImage;
}

/**
 *	Find object, especially white line, and draw their contours with red line.
 *
 *	@param[in]	SrcImage	Source image.
 *	@param[out]	DstImage	Image object detected.
 *	@return Pointer to image the object detected.
 */
Mat* CLineSepObjectDetection::Find(const Mat* SrcImage, const Mat* DstImage)
{
	SrcImage->copyTo(*DstImage);

#define IMAGE_SPLIT_NUM		(20)
#define IMAGE_DETECT_AREA_NUM	(IMAGE_SPLIT_NUM / 2)

	int SplitIndex = SrcImage->rows >> 1;		//Divide by 2
	int SectionHeight = SrcImage->rows / IMAGE_SPLIT_NUM;
	int SectionWidth = SrcImage->cols >> 1;		//Divide by 2
	for (int index = 0; index < IMAGE_DETECT_AREA_NUM; index++) {
		Rect LeftRoi(0, SplitIndex, SectionWidth, SectionHeight);
		Mat DstImageLeftRoi = (Mat)(*DstImage)(LeftRoi);
		Mat RotateImage;
		flip(DstImageLeftRoi, RotateImage, 1);
		this->Find((Mat*)(&RotateImage));
		flip(RotateImage, DstImageLeftRoi, 1);

		Rect RightRoi(SectionWidth, SplitIndex, SectionWidth, SectionHeight);
		Mat DstImageRightRoi = (Mat)(*DstImage)(RightRoi);
		this->Find((Mat*)(&DstImageRightRoi));

		SplitIndex += SectionHeight;
	}

	return (Mat*)DstImage;
}
