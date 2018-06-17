/*
 * CObjDetecStreamer.h
 *
 *  Created on: 2018/06/17
 *      Author: orca2
 */

#ifndef COBJDETECSTREAMER_H_
#define COBJDETECSTREAMER_H_
#include <iostream>
#include "CDetectObject.h"
using namespace std;

class CObjDetecStreamer {
public:
	CObjDetecStreamer(string InputFileName, string OutputFileName);
	virtual ~CObjDetecStreamer();

	virtual int Streaming(CDetectObject* DetectObject = NULL);

protected:
	string mInputFileName;
	string mOutputFileName;
};

#endif /* COBJDETECSTREAMER_H_ */
