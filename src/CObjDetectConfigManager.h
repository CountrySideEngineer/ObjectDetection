/*
 * CObjDetectConfigManager.h
 *
 *  Created on: 2018/06/17
 *      Author: orca2
 */

#ifndef COBJDETECTCONFIGMANAGER_H_
#define COBJDETECTCONFIGMANAGER_H_
#include "AConfigManager.h"
#include "CDetectObject.h"
#include "CObjDetecStreamer.h"
#include "CVideoObjDetectStreamer.h"

class CObjDetectConfigManager : public AConfigManager {
public:
	enum STREAM_TYPE {
		STREAM_TYPE_FILE = 0,
		STREAM_TYPE_CAMERA,
	};

	CObjDetectConfigManager();
	virtual ~CObjDetectConfigManager();

	virtual CObjDetecStreamer* getStreamer() const { return this->mStreamer; }
	virtual CDetectObject* getDetectObject() const { return this->mDetectObject; }
	virtual string getInputFileName() const { return this->mInputFileName; }
	virtual string getOutputFileName() const { return this->mOutputFileName; }

	virtual void SetOption(string Key, string Value);
	virtual bool EnableConfig();

protected:

protected:
	enum OBJECT_DETECT_TYPE {
		OBJECT_DETECT_TYPE_NORMAL = 0,
		OBJECT_DETECT_TYPE_HOUGH,
		OBJECT_DETECT_TYPE_HOUGHP,
		OBJECT_DETECT_TYPE_DILATE_ERODE,
		OBJECT_DETECT_TYPE_ROI,
		OBJECT_DETECT_TYPE_SPLIT,
	};

	int mFilterSize;
	int mThreshValue;
	string mInputFileName;
	string mOutputFileName;
	CDetectObject* mDetectObject;
	CObjDetecStreamer* mStreamer;
	OBJECT_DETECT_TYPE mObjDetType;
	STREAM_TYPE mStreamType;

};

#endif /* COBJDETECTCONFIGMANAGER_H_ */
