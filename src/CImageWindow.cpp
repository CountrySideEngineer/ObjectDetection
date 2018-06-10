/*
 * CImageWindow.cpp
 *
 *  Created on: 2018/06/08
 *      Author: orca2
 */

#include <assert.h>
#include "CImageWindow.h"
#include "iostream"
using namespace std;

/**
 * Constructors.
 */
CImageWindow::CImageWindow(const char* WindowName) : mWindowName(string(WindowName)) {}
CImageWindow::CImageWindow(const string WindowName) : mWindowName(WindowName) {}

/**
 * Destructor.
 */
CImageWindow::~CImageWindow() {
	try {
		if (!this->mWindowName.empty()) {
			cv::destroyWindow(this->mWindowName.c_str());
		}
	}
	catch (exception &e) {
		cout << "Window has not been opened." << endl;
	}
}

/**
 * Open image to show window.
 *
 * @param[in]	Image	Reference to "Mat" object cotains an iamge data to show.
 */
void CImageWindow::Show(const cv::Mat& Image) {
	assert(!this->mWindowName.empty());
	assert((0 != Image.size().height) && (0 != Image.size().width));

	cv::imshow(cv::String(this->mWindowName), Image);
}

/**
 * Close image window.
 */
void CImageWindow::Close() {
	assert(!this->mWindowName.empty());

	cv::destroyWindow(this->mWindowName);
}

/**
 * Close ALL windows of image, shown by calling imshow() method of OpenCv.
 * This is static method of CImageWindow class.
 */
void CImageWindow::CloseAll() {
	cv::destroyAllWindows();
}
