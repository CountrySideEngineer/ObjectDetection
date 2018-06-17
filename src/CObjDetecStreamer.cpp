/*
 * CObjDetecStreamer.cpp
 *
 *  Created on: 2018/06/17
 *      Author: orca2
 */
#include "opencv/cv.h"
#include "opencv/cv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include "CObjDetecStreamer.h"
#include "CVideoReader.h"
#include "CVideoWriter.h"
#include "CImageWindow.h"

CObjDetecStreamer::CObjDetecStreamer(string InputFileName, string OutputFileName)
	: mInputFileName(InputFileName)
	, mOutputFileName(OutputFileName)
{}
CObjDetecStreamer::~CObjDetecStreamer() {}

/**
 * Show object detected image.
 * The base image is read from file.
 *
 * @param	DetectObject	Pointer to CDetectObject instance,
 * @return	Result of streaming, returns 0 if the stream finished
 * 			without error, otherwise returns minus value.
 * 			*If error, its information is written into standard
 * 			 terminal.
 */
int CObjDetecStreamer::Streaming(CDetectObject* DetectObject)
{
	if (this->mInputFileName.empty()||
		this->mOutputFileName.empty())
	{
		cerr << "Both input and output file name must be set." << endl;

		return -1;
	}

	CVideoReader Reader(this->mInputFileName);
	if (!Reader.isOpened()) {
		cerr << "Input file can not be opened." << endl;

		return -2;
	}
	CVideoWriter Writer(this->mOutputFileName,
			Reader.getImageWidth(),
			Reader.getImageHeight(),
			Reader.getImageFps());

	Reader.About();
	Writer.About();

	cv::Mat CapturedImage;
	cv::Mat DetectedImage(Reader.getImageHeight(),
			Reader.getImageWidth(),
			(int)CV_8UC3);
	CImageWindow InImgWindow(string("Captured image"));
	CImageWindow OutImgWindows(string("Detected image"));
	for (int index = 0; index < Reader.getImageFrameNum(); index++) {

		CapturedImage = Reader.Read();
		if (NULL != DetectObject) {
			DetectObject->Find((const Mat*)(&CapturedImage), (const Mat*)(&DetectedImage));
		} else {
			CapturedImage.copyTo(DetectedImage);
		}

		InImgWindow.Show(CapturedImage);
		OutImgWindows.Show(DetectedImage);

		Writer.Write(DetectedImage);

		cv::waitKey(1000 / Reader.getImageFps());
	}

	return 0;
}
