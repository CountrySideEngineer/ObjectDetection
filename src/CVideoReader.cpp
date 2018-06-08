/*
 * CVideoReader.cpp
 *
 *  Created on: 2018/06/03
 *      Author: orca2
 */

#include "CVideoReader.h"
#include "exception"
using namespace std;

/**
 * Constructors with no argument.
 */
CVideoReader::CVideoReader() : AVideo() {}

/**
 * Constructor with argument of Video file name.
 *
 * @param[in]	FileName	Name of input video file.
 */
CVideoReader::CVideoReader(cv::String FileName) : AVideo(FileName) {
	this->Init();
}

/**
 * Destructor of this class.
 * If any videp file has been opened, close (release) it.
 */
CVideoReader::~CVideoReader() {
	if (this->mCapture.isOpened()) {
		this->mCapture.release();
	}
}

/**
 * Initialize parameter of video.
 */
void CVideoReader::Init() {
	if ((NULL != this->mFileName.c_str()) &&
		(0 != this->mFileName.length()) &&
		(!this->mCapture.isOpened()))
	{
		this->mCapture.open(this->mFileName);
	}
}

/**
 * Read video frame data from the file.
 *
 * @return	Read video frame data.
 */
cv::Mat& CVideoReader::Read() {
	try {
		this->mCapture >> this->mImage;
		return this->mImage;
	} catch (exception& ex) {
		cerr << ex.what() << endl;

		throw;
	}
}

/**
 * Show information of output video information.
 */
void CVideoReader::About() {
	cout << "About video data information to read." << endl;
	cout << "File Path:" << this->mFileName  << endl;
	cout << "Size of image:" << endl;
	cout << "\theight = " << this->getImageHeight() << endl;
	cout << "\twidth = " << this->getImageWidth() << endl;
	cout << "FPS = " << this->getImageFps() << endl;
	cout << "Frame num = " << this->getImageFrameNum() << endl;
}

