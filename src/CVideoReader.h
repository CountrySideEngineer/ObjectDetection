/*
 * CVideoReader.h
 *
 *  Created on: 2018/06/03
 *      Author: orca2
 */

#ifndef CVIDEOREADER_H_
#define CVIDEOREADER_H_
#include "opencv2/videoio.hpp"
#include "AVideo.h"

class CVideoReader : public AVideo {
public:
	CVideoReader();
	CVideoReader(cv::String FileName);
	virtual ~CVideoReader();

	virtual cv::Mat& Read();

	virtual bool isOpened() const { return this->mCapture.isOpened(); }

	virtual void About();

	virtual int getImageWidth() const
		{ return this->mCapture.get(cv::CAP_PROP_FRAME_WIDTH); }
	virtual int getImageHeight() const
		{ return this->mCapture.get(cv::CAP_PROP_FRAME_HEIGHT); }
	virtual int getImageFps() const
		{ return this->mCapture.get(cv::CAP_PROP_FPS); }
	virtual int getImageFrameNum() const
		{ return this->mCapture.get(cv::CAP_PROP_FRAME_COUNT); }

protected:
	virtual void Init();

protected:
	cv::VideoCapture mCapture;
};

#endif /* CVIDEOREADER_H_ */
