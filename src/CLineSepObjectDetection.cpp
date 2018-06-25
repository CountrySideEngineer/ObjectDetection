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
	findContours(BinImage, Contours, CV_RETR_LIST, CHAIN_APPROX_SIMPLE);
	for (unsigned int index = 0; index < Contours.size(); index++) {
		drawContours((Mat&)(*TargetImage), Contours, index, Scalar(0, 0, 255), 5);
	}

	return TargetImage;
}


Mat* CLineSepObjectDetection::Find(const Mat* SrcImage, const Mat* DstImage)
{
	SrcImage->copyTo(*DstImage);

	int SplitIndex = SrcImage->rows / 2;
	int HeightSection = SrcImage->rows / 10;
	int WidthSection = SrcImage->cols;
	for (int index = 0; index < 5; index++) {
		Rect Roi(0, SplitIndex, WidthSection, HeightSection);
		Mat DstImageRoi = (Mat)(*DstImage)(Roi);
		this->Find((Mat*)(&DstImageRoi));
		SplitIndex += HeightSection;
	}

	return (Mat*)DstImage;
}
