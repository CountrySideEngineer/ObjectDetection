/*
 * CVideoObjDetectStreamer.cpp
 *
 *  Created on: 2018/06/17
 *      Author: orca2
 */

#include "CVideoObjDetectStreamer.h"
#include "CVideoReader.h"
#include "opencv/cv.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "CVideoWriter.h"
#include "CImageWindow.h"

CVideoObjDetectStreamer::CVideoObjDetectStreamer(
		string InputFileName, string OutputFileName)
	: CObjDetecStreamer(InputFileName, OutputFileName)
{}

CVideoObjDetectStreamer::~CVideoObjDetectStreamer() {}

/**
 * Show object detected image.
 * The base image is read from video, USB camera.
 *
 * @param	DetectObject	Pointer to CDetectObject instance,
 * @return	Result of streaming, returns 0 if the stream finished
 * 			without error, otherwise returns minus value.
 * 			*If error, its information is written into standard
 * 			 terminal.
 */
int CVideoObjDetectStreamer::Streaming(CDetectObject* DetectObject)
{
	VideoCapture Cap;
	Cap.open(0);
	if (!Cap.isOpened()) {
		cerr << "Camera can not open." << endl;

		return -2;
	}
	double Fps = Cap.get(cv::CAP_PROP_FPS);
	int ResizeHeight = 320;
	int ResizeWidth = 480;

//	CVideoWriter Writer(this->mOutputFileName,
//			ResizeWidth, ResizeHeight, Fps);

//	Writer.About();

	cv::Size ResizedImageSize(ResizeWidth, ResizeHeight);
	cv::Mat CapturedImage;
	cv::Mat ResizedImage;
	cv::Mat DetectedImage(ResizeHeight, ResizeWidth, (int)CV_8UC3);
	CImageWindow InImgWindow(string("Captured image"));
	CImageWindow OutImgWindows(string("Detected image"));
	do {
		Cap >> CapturedImage;
		cv::resize(CapturedImage, ResizedImage, ResizedImageSize);
		if (NULL != DetectObject) {
			DetectObject->Find((const Mat*)(&ResizedImage), (const Mat*)(&DetectedImage));
		} else {
			ResizedImage.copyTo(DetectedImage);
		}
		OutImgWindows.Show(DetectedImage);

		cv::waitKey(1000 / Fps);
	} while (cv::waitKey(1) < 0);

	return 0;
}
