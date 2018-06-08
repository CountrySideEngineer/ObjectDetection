/*
 * CVideoWriter.cpp
 *
 *  Created on: 2018/06/03
 *      Author: orca2
 */
#include <iostream>
#include "CVideoWriter.h"
using namespace std;

/**
 * Constructors.
 */
CVideoWriter::CVideoWriter()
	: AVideo(cv::String("")) , mWidth(-1), mHeight(-1), mFps(-1) {}
CVideoWriter::CVideoWriter(cv::String FileName)
	: AVideo(FileName), mWidth(-1), mHeight(-1), mFps(-1) {}
CVideoWriter::CVideoWriter(cv::String FileName, int Width, int Height, int Fps)
	: AVideo(FileName), mWidth(Width), mHeight(Height), mFps(Fps) {}
/**
 * Destructors.
 */
CVideoWriter::~CVideoWriter() {
	if (this->mWriter.isOpened()) {
		this->mWriter.release();
	}
}

/**
 * Initialize the output video file.
 *
 * @return	Result of initializing.
 * 			This method returns true if the initialize finishes successfully,
 * 			otherwise returns false.
 */
bool CVideoWriter::Init() {
	/*
	 *	Check whether the output file has been opened first,
	 *	because this "initialize" function is called by many functions (maybe...).
	 *	So, the every time this function is called, the check sequence is run.
	 *	If the "isOpened()" is checked in front of opening the video, (in short,
	 *	after checking all parameters),it costs.
	 *	So to save resources, the CHECK is set at the start of sequence.
	 */
	if (this->mWriter.isOpened()) {
		/*
		 * The comment below is kind advice, but so loud.
		 * So, set it not to be show.
		 */
		//cout << "The output file - " << this->mFileName << " - has already been opened." << endl;

		return true;
	}

	//Check whether member parameters are correct or not.
	if (!this->Check()) {
		return false;
	}

	int fourcc = cv::VideoWriter::fourcc('X','V','I', 'D');
	bool OpenResult = false;
	OpenResult = this->mWriter.open(this->mFileName, fourcc,
			this->mFps,
			cv::Size(this->mWidth, this->mHeight));
	if ((OpenResult) && (this->mWriter.isOpened())) {
		//cout << "Output file " << this->mFileName << " can be opened." << endl;

		return true;
	} else {
		//cout << "Output file " << this->mFileName << " can not be opened." << endl;

		return false;
	}
}

/**
 *	Check whether member parameter of this class object is correct or not.
 *
 *	@return	This method returns true if all the parameters are correct, otherwise
 *			returns false.
 */
bool CVideoWriter::Check() {
	//Check output file name.
	if (this->mFileName.empty()) {
		cerr << "Output filename has not been set." << endl;

		return false;
	}

	//Check output image file configuration.
	if ((-1 == this->mWidth) ||
		(-1 == this->mHeight) ||
		(-1 == this->mFps))
	{
		cerr << "Output image has not been configured." << endl;
		cerr << "Size of image(width and height) and frame rate (fps:frame per second)" << endl;
		cerr << "must been set before write image into output file." << endl;

		return false;
	}
	return true;
}


/**
 * Write image frame into output image file.
 *
 * @param[in]	Image data to write in to output file.
 */
void CVideoWriter::Write(cv::Mat& Image) {
	if (!this->Init()) {
		cerr << "Initialize failed." << endl;

		//@ToDo Change code to throw exception.
		return;
	}

	if ((this->mHeight != Image.size().height) || (this->mWidth != Image.size().width)) {
		cerr << "Size of output image is not same that of input image, \"Image\"" << endl;

		//@ToDo Change code to throw exception.
		return;
	}

	this->mWriter << Image;
}

/**
 * Show information of output video information.
 */
void CVideoWriter::About() {
	cout << "About video data information to write." << endl;

	cout << "File Path:" << this->mFileName << endl;
	cout << "Size of image:" << endl;
	cout << "\theight = " << this->mHeight << endl;
	cout << "\twidth = " << this->mWidth << endl;
	cout << "FPS = " << this->mFps << endl;
}
