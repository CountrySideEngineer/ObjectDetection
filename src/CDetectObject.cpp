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
 * Detect and mark traffic object.
 *
 * @param[in]	Source image to scan.
 * @param[out]	Destination image to draw traffic signs.
 *
 * @return	An image traffic signs are detected and marked.
 */
Mat* CDetectObject::Find(const Mat* SrcImage, const Mat* DstImage) {
	Mat Gray;
	Mat Bin;
	Mat Filtered;

	/*
	 * To accentuate the edge of border, convert the input image into
	 * 2 value scale, black and white.
	 */
	cvtColor(*SrcImage, Gray, COLOR_BGR2GRAY);
	blur(Gray, Filtered, Size(5, 5));
	threshold(Filtered, Bin, 210, 255, THRESH_BINARY);

	vector< vector<Point> > Contours;
	findContours(Bin, Contours, CV_RETR_LIST, CHAIN_APPROX_SIMPLE);

	SrcImage->copyTo(*DstImage);
	for (unsigned int index = 0; index < Contours.size(); index++) {
		drawContours((Mat&)*DstImage, Contours, index, Scalar(0, 0, 255), 1);
	}

	return (Mat*)DstImage;
}
