/*
 * CRoiObjectDetection.h
 *
 *  Created on: 2018/06/15
 *      Author: orca2
 */

#ifndef CROIOBJECTDETECTION_H_
#define CROIOBJECTDETECTION_H_

#include "CDetectObject.h"
#include "CDilateErodeObjectDetection.h"

class CRoiObjectDetection: public CDilateErodeObjectDetection {
public:
	CRoiObjectDetection(int FilterSize = 5, int Thresh = 127, int MaxValue = 255);
	virtual ~CRoiObjectDetection();

	virtual Mat* Find(const Mat* SrcImage, const Mat* DstImage);
	virtual Mat* Find(Mat* TargetImage);
};

#endif /* CROIOBJECTDETECTION_H_ */
