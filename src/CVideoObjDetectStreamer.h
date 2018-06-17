/*
 * CVideoObjDetectStreamer.h
 *
 *  Created on: 2018/06/17
 *      Author: orca2
 */

#ifndef CVIDEOOBJDETECTSTREAMER_H_
#define CVIDEOOBJDETECTSTREAMER_H_

#include "CObjDetecStreamer.h"

class CVideoObjDetectStreamer: public CObjDetecStreamer {
public:
	CVideoObjDetectStreamer(string InputFileName, string OutputFileName);
	virtual ~CVideoObjDetectStreamer();

	virtual int Streaming(CDetectObject* DetectObject = NULL);
};

#endif /* CVIDEOOBJDETECTSTREAMER_H_ */
