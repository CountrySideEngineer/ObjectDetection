/*
 * CVideoObjDetectStreamer.cpp
 *
 *  Created on: 2018/06/17
 *      Author: orca2
 */
#include <iostream>
#include <time.h>
#include <sys/time.h>
#include "CVideoObjDetectStreamer.h"
#include "CVideoReader.h"
#include "opencv/cv.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "CVideoWriter.h"
#include "CImageWindow.h"

#ifdef _DEBUG
#define DETECT_DEBUG_IMAGE_ON	(1)
#define CALC_DETECT_TIME		(1)
#else
#define DETECT_DEBUG_IMAGE_ON	(0)
#define CALC_DETECT_TIME		(1)
#endif

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

	int CameraConfig_Height = 480;
	int CameraConfig_Width = 320;
	Cap.set(CAP_PROP_FRAME_HEIGHT, CameraConfig_Height);
	Cap.set(CAP_PROP_FRAME_WIDTH, CameraConfig_Width);

	double Fps = Cap.get(cv::CAP_PROP_FPS);
	int CapFrameHeigth = Cap.get(CAP_PROP_FRAME_HEIGHT);
	int CapFrameWidth = Cap.get(CAP_PROP_FRAME_WIDTH);

	//About
	cout << "About camera data information to read." << endl;
	cout << "Size of image:" << endl;
	cout << "\theight = " << CapFrameHeigth << endl;
	cout << "\twidth = " << CapFrameWidth << endl;
	cout << "FPS = " << Fps << endl;

	cv::Mat CapturedImage;
	cv::Mat DetectedImage(CapFrameHeigth, CapFrameWidth, (int)CV_8UC3);
	CImageWindow OutImgWindows(string("Detected image"));
	do {
		Cap >> CapturedImage;
		if (NULL != DetectObject) {
			DetectObject->Find((const Mat*)(&CapturedImage), (const Mat*)(&DetectedImage));
		} else {
			CapturedImage.copyTo(DetectedImage);
		}
#if CALC_DETECT_TIME == 1
		timeval StartTime;
		gettimeofday(&StartTime, NULL);
#endif	//CALC_DETECT_TIME == 1

		OutImgWindows.Show(DetectedImage);

#if CALC_DETECT_TIME == 1
		timeval EndTime;
		gettimeofday(&EndTime, NULL);

		long PassedTime = ((EndTime.tv_sec * 1000) + (EndTime.tv_usec / 1000)) -
				((StartTime.tv_sec * 1000) + (StartTime.tv_usec / 1000));
		cout << "Video Stream - Passed time = " << PassedTime << " millisecond" << endl;
#endif	//CALC_DETECT_TIME == 1

		cv::waitKey(1000 / Fps);
	} while (cv::waitKey(1) < 0);

	return 0;
}
