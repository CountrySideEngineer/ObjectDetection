/*
 * CObjDetectConfigManager.cpp
 *
 *  Created on: 2018/06/17
 *      Author: orca2
 */

#include "CObjDetectConfigManager.h"
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include "CHoughObjectDetection.h"
#include "CHoughPObjectDetection.h"
#include "CDilateErodeObjectDetection.h"
#include "CRoiObjectDetection.h"
#include "CObjDetecStreamer.h"
#include "CVideoObjDetectStreamer.h"
#include "CLineSepObjectDetection.h"
#define	DEFAULT_FILTER_SIZE		(3)
#define	DEFAULT_THRESH_VALUE	(180)

/**
 * Constructor
 */
CObjDetectConfigManager::CObjDetectConfigManager()
	: mFilterSize(DEFAULT_FILTER_SIZE)
	, mThreshValue(DEFAULT_THRESH_VALUE)
	, mDetectObject(new CDetectObject(DEFAULT_FILTER_SIZE, DEFAULT_THRESH_VALUE, 255))
	, mStreamer(NULL)
	, mObjDetType(OBJECT_DETECT_TYPE_NORMAL)
	, mStreamType(STREAM_TYPE_FILE)
{
}

/**
 * Destructor
 */
CObjDetectConfigManager::~CObjDetectConfigManager()
{
	if (NULL != this->mDetectObject) {
		delete this->mDetectObject;
	}
	if (NULL != this->mStreamer) {
		delete this->mStreamer;
	}
}

void CObjDetectConfigManager::SetOption(string Key, string Value)
{
	if (string("-i") == Key) {
		this->mInputFileName = Value;
	} else if (string("-o") == Key) {
		this->mOutputFileName = Value;
	} else if (string("-t") == Key) {
		sscanf((const char*)(Value.c_str()), "%d", &(this->mThreshValue));
	} else if (string("-f") == Key) {
		sscanf((const char*)(Value.c_str()), "%d", &(this->mFilterSize));
	} else if (string("-d") == Key) {
		std::transform(Value.begin(), Value.end(), Value.begin(), ::tolower);
		if (string("normal") == Value) {
			this->mObjDetType = OBJECT_DETECT_TYPE_NORMAL;
		} else if (string("hough") == Value) {
			this->mObjDetType = OBJECT_DETECT_TYPE_HOUGH;
		} else if (string("houghp") == Value) {
			this->mObjDetType = OBJECT_DETECT_TYPE_HOUGHP;
		} else if (string("dilate") == Value) {
			this->mObjDetType = OBJECT_DETECT_TYPE_DILATE_ERODE;
		} else if (string("roi") == Value) {
			this->mObjDetType = OBJECT_DETECT_TYPE_ROI;
		} else if (string("spl") == Value) {
			this->mObjDetType = OBJECT_DETECT_TYPE_SPLIT;
		}
	} else if (string("-in") == Key) {
		if (string("camera") == Value) {
			this->mStreamType = STREAM_TYPE_CAMERA;
		} else if (string("file") == Value) {
			this->mStreamType = STREAM_TYPE_FILE;
		}
	}
}

bool CObjDetectConfigManager::EnableConfig()
{
	CDetectObject* DetectObject = NULL;

#define DETECT_OBJECT_CASE_SET(DetectObject, ObjType, ObjClass)		\
	case ObjType:													\
	{																\
		DetectObject =												\
			new ObjClass(this->mFilterSize,							\
					this->mThreshValue,								\
					255);											\
		break;														\
	}

#define SET_DETECT_OBJECT(ObjType, ObjClass)						\
		DETECT_OBJECT_CASE_SET(DetectObject, ObjType, ObjClass)

	switch (this->mObjDetType) {
		SET_DETECT_OBJECT(OBJECT_DETECT_TYPE_NORMAL, CDetectObject);
		SET_DETECT_OBJECT(OBJECT_DETECT_TYPE_HOUGH, CHoughObjectDetection);
		SET_DETECT_OBJECT(OBJECT_DETECT_TYPE_HOUGHP, CHoughPObjectDetection);
		SET_DETECT_OBJECT(OBJECT_DETECT_TYPE_DILATE_ERODE, CDilateErodeObjectDetection);
		SET_DETECT_OBJECT(OBJECT_DETECT_TYPE_ROI, CRoiObjectDetection);
		SET_DETECT_OBJECT(OBJECT_DETECT_TYPE_SPLIT, CLineSepObjectDetection);
	}

	if (NULL != DetectObject) {
		if (NULL != this->mDetectObject) {
			delete this->mDetectObject;
		}
		this->mDetectObject = DetectObject;
	}
	/*
	 * In the case the detection type configuration is invalid,
	 * the member variable DetectObject has been set default value, CDetectObject().
	 * So, the variable must not be NULL.
	 * (Checking value, whether the variable is NULL or not, is not needed.
	 */

	if ((this->mInputFileName.empty()) ||
		(this->mOutputFileName.empty()))
	{
		return (bool)-1;
	}

	if (STREAM_TYPE_FILE == this->mStreamType) {
		this->mStreamer =
				new CObjDetecStreamer(
						this->mInputFileName, this->mOutputFileName);
	} else {
		this->mStreamer =
				new CVideoObjDetectStreamer(
						this->mInputFileName, this->mOutputFileName);
	}

	return (bool)0;
}

