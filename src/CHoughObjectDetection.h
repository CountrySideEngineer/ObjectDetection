/*
 * CHoughObjectDetection.h
 *
 *  Created on: 2018/06/10
 *      Author: orca2
 */

#ifndef CHOUGHOBJECTDETECTION_H_
#define CHOUGHOBJECTDETECTION_H_

#include "CDetectObject.h"

class CHoughObjectDetection: public CDetectObject {
public:
	enum DETECT_OBJECT_HOUGH_CONFIG {
		DETECT_OBJECT_HOUGH_CONFIG_RHO,
		DETECT_OBJECT_HOUGH_CONFIG_THETA,
		DETECT_OBJECT_HOUGH_CONFIG_THRESH,
		DETECT_OBJECT_HOUGH_CONFIG_SRN,
		DETECT_OBJECT_HOUGH_CONFIG_STN,
	};


	CHoughObjectDetection(int FilterSize = 5, int Thresh = 127, int MaxValue = 255);
	virtual ~CHoughObjectDetection();

	virtual Mat* Find(const Mat* SrcImage, const Mat* DstImage);

	virtual void SetConfig(DETECT_OBJECT_HOUGH_CONFIG config, int Value);
	virtual void SetConfig(DETECT_OBJECT_HOUGH_CONFIG config, double Value);

protected:
	double mRho;
	double mTheta;
	int mVoteThresh;
	double mSrn;
	double mStn;
};

#endif /* CHOUGHOBJECTDETECTION_H_ */
