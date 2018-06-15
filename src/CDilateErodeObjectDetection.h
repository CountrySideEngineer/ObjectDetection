/*
 * CDilateObjectDetection.h
 *
 *  Created on: 2018/06/14
 *      Author: orca2
 */

#ifndef CDILATEERODEOBJECTDETECTION_H_
#define CDILATEERODEOBJECTDETECTION_H_

#include "CDetectObject.h"
#include "opencv/cv.hpp"
using namespace cv;

class CDilateErodeObjectDetection: public CDetectObject {
public:
	CDilateErodeObjectDetection(int FilterSize = 5, int Thresh = 127, int MaxValue = 255);
	virtual ~CDilateErodeObjectDetection();

protected:
	virtual Mat* Convert2Bin(const Mat* SrcImage, Mat* DstImage);
};

#endif /* CDILATEERODEOBJECTDETECTION_H_ */
