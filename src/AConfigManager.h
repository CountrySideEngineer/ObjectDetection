/*
 * AConfigManager.h
 *
 *  Created on: 2018/06/17
 *      Author: orca2
 */

#ifndef ACONFIGMANAGER_H_
#define ACONFIGMANAGER_H_
#include <iostream>
#include <string>
using namespace std;

class AConfigManager {
public:
	AConfigManager();
	virtual ~AConfigManager();

	virtual void SetOption(string Key, string Value) = 0;
};

#endif /* ACONFIGMANAGER_H_ */
