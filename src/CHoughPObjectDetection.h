/*
 * CHoughPObjectDetection.h
 *
 *  Created on: 2018/06/10
 *      Author: orca2
 */

#ifndef CHOUGHPOBJECTDETECTION_H_
#define CHOUGHPOBJECTDETECTION_H_

#include "CHoughObjectDetection.h"

class CHoughPObjectDetection: public CHoughObjectDetection {
public:
	CHoughPObjectDetection(int FilterSize = 5, int Thresh = 127, int MaxValue = 255);
	virtual ~CHoughPObjectDetection();

	virtual Mat* Find(const Mat* SrcImage, const Mat* DstImage);

protected:
};

#endif /* CHOUGHPOBJECTDETECTION_H_ */
