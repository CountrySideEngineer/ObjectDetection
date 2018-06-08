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
using namespace std;

int main(int argc, char** argv) {

	cout << "Start Program!" << endl;

	if (argc < 3) {
		cerr << "Usage: DetectWhiteLine (source file) (output file)" << endl;

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
		}
		argv++;
	}

	CDetectObject DetectObject;
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
	for (int index = 0; index < VideoReader.getImageFrameNum(); index++) {

		CaptureImgae = VideoReader.Read();
		DetectObject.Find((const Mat*)(&CaptureImgae), (const Mat*)(&DetectedImage));

		cv::imshow(cv::String("image window"), CaptureImgae);
		cv::imshow(cv::String("detected image"), DetectedImage);

		VideoWriter.Write(DetectedImage);

		cv::waitKey(1000 / VideoReader.getImageFps());
	}

	cout << "End Program!" << endl;

	cv::destroyAllWindows();

	return 0;
}
