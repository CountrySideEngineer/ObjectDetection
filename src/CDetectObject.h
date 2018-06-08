/*
 * CDetectObject.h
 *
 *  Created on: 2018/05/20
 *      Author: orca2
 */

#ifndef CDETECTOBJECT_H_
#define CDETECTOBJECT_H_
#include "opencv/cv.hpp"
using namespace cv;

class CDetectObject {
public:
	enum DETECT_OBJECT_CONFIG {
		DETECT_OBJECT_CONFIG_FIL_SIZE,
		DETECT_OBJECT_CONFIG_THRESH_THRESH,
		DETECT_OBJECT_CONFIG_THRESH_MAXVAL,
		DETECT_OBJECT_CONFIG_MAX,
	};

	CDetectObject(int FilterSize = 5, int Thresh = 127, int MaxValue = 255);
	virtual ~CDetectObject() {}

	virtual Mat* Find(const Mat* SrcImage, const Mat* DstImage);

	virtual void SetConfig(DETECT_OBJECT_CONFIG config, int Value);
	virtual void SetConfig(DETECT_OBJECT_CONFIG config, double Value);

protected:
	int mFilterSize;
	double mThresh;
	double mMaxValue;

	Mat mGray;
	Mat mBin;
	Mat mFiltered;
};

#endif /* CDETECTOBJECT_H_ */
