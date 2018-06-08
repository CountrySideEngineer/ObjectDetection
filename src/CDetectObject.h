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
	CDetectObject() {}
	virtual ~CDetectObject() {}

	virtual Mat* Find(const Mat* SrcImage, const Mat* DstImage);
};

#endif /* CDETECTOBJECT_H_ */
