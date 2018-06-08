/*
 * CVideo.cpp
 *
 *  Created on: 2018/06/03
 *      Author: orca2
 */

#include "AVideo.h"

AVideo::AVideo() : mFileName(cv::String("")){ }
AVideo::AVideo(cv::String FileName)
	: mFileName(cv::String(FileName)) {}
AVideo::~AVideo() {}

