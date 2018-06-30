/*
 * CLineSepObjectDetection.h
 *
 *  Created on: 2018/06/23
 *      Author: orca2
 */

#ifndef CLINESEPOBJECTDETECTION_H_
#define CLINESEPOBJECTDETECTION_H_

#include "CDilateErodeObjectDetection.h"

class CLineSepObjectDetection: public CDilateErodeObjectDetection {
public:
	CLineSepObjectDetection(int FilterSize = 5, int Thresh = 127, int MaxValue = 255);
	virtual ~CLineSepObjectDetection();

	virtual Mat* Find(const Mat* SrcImage, const Mat* DstImage);
	virtual Mat* Find(Mat* TargetImage);
};

#endif /* CLINESEPOBJECTDETECTION_H_ */
