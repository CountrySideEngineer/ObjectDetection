/*
 * CVideoWriter.h
 *
 *  Created on: 2018/06/03
 *      Author: orca2
 */

#ifndef CVIDEOWRITER_H_
#define CVIDEOWRITER_H_
#include "AVideo.h"

class CVideoWriter : public AVideo{
public:
	CVideoWriter();
	CVideoWriter(cv::String FileName);
	CVideoWriter(cv::String FileName,
			int Width, int Height, int Fps);
	virtual ~CVideoWriter();

	virtual void Write(cv::Mat& Image);

	virtual bool isOpened() const { return this->mWriter.isOpened(); }

	virtual void About();

	virtual int getImageWidth() const
		{ return this->mWidth; }
	virtual int getImageHeight() const
		{ return this->mHeight; }
	virtual int getImageFps() const
		{ return this->mFps; }
	//virtual int getFourCc() const
	//	{ return this->mFourCc; }

	virtual void setImageWidth(int Width) { this->mWidth = Width; }
	virtual void setImageHeight(int Height) { this->mHeight = Height; }
	//virtual void setFourCc(int FourCc) { this->mFourCc = FourCc; } FourCC is fixed by "XVID".
	virtual void setFps(int Fps) { this->mFps = Fps; }

protected:
	virtual bool Init();
	virtual bool Check();

protected:
	int mWidth;
	int mHeight;
	int mFps;

	cv::VideoWriter mWriter;

};

#endif /* CVIDEOWRITER_H_ */
