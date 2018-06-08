/*
 * CImageWindow.h
 *
 *  Created on: 2018/06/08
 *      Author: orca2
 */

#ifndef CIMAGEWINDOW_H_
#define CIMAGEWINDOW_H_

#include <string>
#include "opencv/cv.hpp"
#include "opencv2/highgui.hpp"
using namespace std;

class CImageWindow {
public:
	CImageWindow(const char* WindowName);
	CImageWindow(const string WindowName);
	virtual ~CImageWindow();

	virtual string getWindowName() const { return this->mWindowName; }

	virtual void Show(const cv::Mat& Image);
	virtual void Close();

public:
	static void CloseAll();

protected:
	string mWindowName;
};

#endif /* CIMAGEWINDOW_H_ */
