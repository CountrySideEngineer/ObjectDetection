/*
 * CVideo.h
 *
 *  Created on: 2018/06/03
 *      Author: orca2
 */

#ifndef AVIDEO_H_
#define AVIDEO_H_
#include <iostream>
#include "opencv/cv.hpp"

class AVideo {
public:
	AVideo();
	AVideo(cv::String FileName);
	virtual ~AVideo();

	virtual void About() = 0;

	const cv::String&	getFileName() const { return this->mFileName; }
	const cv::Mat& getImage() const { return this->mImage; }

protected:
	cv::String mFileName;
	cv::Mat mImage;
};

#endif /* AVIDEO_H_ */
