//============================================================================
// Name        : DetectWhiteLine.cpp
// Author      : CountrySideEngineer
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "CVideoReader.h"
#include "CVideoWriter.h"
#include "opencv/cv.h"
#include "opencv/cv.hpp"
#include "opencv2/highgui.hpp"
#include "CDetectObject.h"
#include "CDilateErodeObjectDetection.h"
#include "CHoughObjectDetection.h"
#include "CHoughPObjectDetection.h"
#include "CRoiObjectDetection.h"
#include "CImageWindow.h"
using namespace std;

#define	DEFAULT_FILTER_SIZE		(3)
#define	DEFAULT_THRESH_VALUE	(180)

int main(int argc, char** argv) {

	cout << "Start Program!" << endl;

	int FilterSize = DEFAULT_FILTER_SIZE;
	int ThreshValue = DEFAULT_THRESH_VALUE;

	if (argc < 3) {
		cerr << "Usage: DetectWhiteLine -i (source file) -o (output file)" << endl;
		cerr << "Option	-f (Filter size) : integer parameter" << endl;
		cerr << "\t\t-r (Thresh value) : integer parameter" << endl;

		return 0;
	}
	argv++;
	cv::String InputFile;
	cv::String OutputFile;
	while ((NULL != argv) && (NULL != *argv)) {
		if ("-i" == string(*argv)) {
			argv++;
			InputFile = cv::String(*argv);
		} else if ("-o" == string(*argv)) {
			argv++;
			OutputFile = cv::String(*argv);
		} else if ("-f" == string(*argv)) {
			argv++;
			sscanf(*argv, "%d", &FilterSize);
		} else if ("-t" == string(*argv)) {
			argv++;
			sscanf(*argv, "%d", &ThreshValue);
		}
		argv++;
	}

	//CDetectObject DetectObject(5, 180, 255);
	//CDetectObject *DetectObject = new CHoughPObjectDetection(FilterSize, ThreshValue, 255);
	//((CHoughPObjectDetection*)DetectObject)->SetConfig(CHoughObjectDetection::DETECT_OBJECT_HOUGH_CONFIG_THRESH, 300);
	//CDetectObject *DetectObject = new CDilateErodeObjectDetection(FilterSize, ThreshValue, 255);
	CDetectObject *DetectObject = new CRoiObjectDetection(FilterSize, ThreshValue, 255);
	CVideoReader VideoReader(InputFile);
	CVideoWriter VideoWriter(OutputFile,
			VideoReader.getImageWidth(),
			VideoReader.getImageHeight(),
			VideoReader.getImageFps());

	VideoReader.About();
	VideoWriter.About();

	if (!(VideoReader.isOpened())) {
		cerr << "Input file can not be opened." << endl;

		return 0;
	}

	cv::Mat CaptureImgae;
	cv::Mat DetectedImage(VideoReader.getImageHeight(),
			VideoReader.getImageWidth(),
			(int)CV_8UC3);
	CImageWindow CapImageWindow(string("Image window"));
	CImageWindow DetectedImageWindow(string("Detected image window"));
	for (int index = 0; index < VideoReader.getImageFrameNum(); index++) {

		CaptureImgae = VideoReader.Read();
		DetectObject->Find((const Mat*)(&CaptureImgae), (const Mat*)(&DetectedImage));

		CapImageWindow.Show(CaptureImgae);
		DetectedImageWindow.Show(DetectedImage);

		VideoWriter.Write(DetectedImage);

		cv::waitKey(1000 / VideoReader.getImageFps());
	}

	delete DetectObject;

	cout << "End Program!" << endl;

	return 0;
}
