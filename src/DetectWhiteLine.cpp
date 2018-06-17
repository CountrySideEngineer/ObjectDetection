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
#include "CObjDetectConfigManager.h"
#include "CObjDetecStreamer.h"
using namespace std;

#define	DEFAULT_FILTER_SIZE		(3)
#define	DEFAULT_THRESH_VALUE	(180)

int main(int argc, char** argv) {

	cout << "Start Program!" << endl;

	if (argc < 3) {
		cerr << "Usage: DetectWhiteLine -i (source file) -o (output file)" << endl;
		cerr << "Option	-f (Filter size) : integer parameter" << endl;
		cerr << "\t\t-r (Thresh value) : integer parameter" << endl;

		return 0;
	}
	argv++;

	CObjDetectConfigManager ConfigManager;
	while ((NULL != argv) && (NULL != *argv)) {
		string Key(*argv);
		argv++;
		string Value(*argv);
		argv++;
		ConfigManager.SetOption(Key, Value);
	}
	ConfigManager.EnableConfig();
	CObjDetecStreamer* Streamer = ConfigManager.getStreamer();
	Streamer->Streaming(ConfigManager.getDetectObject());

	return 0;
}
