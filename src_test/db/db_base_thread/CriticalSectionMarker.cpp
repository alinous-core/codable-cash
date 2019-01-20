/*
 * CriticalSectionMarker.cpp
 *
 *  Created on: 2019/01/12
 *      Author: iizuka
 */

#include "db/db_base_thread/CriticalSectionMarker.h"
#include "base_thread/StackUnlocker.h"
#include "db/db_base_thread/CriticalSectionMarkerException.h"

namespace alinous {

CriticalSectionMarker::CriticalSectionMarker() {
	this->critical = false;
}

CriticalSectionMarker::~CriticalSectionMarker() {
}

void CriticalSectionMarker::enter() {
	{
		StackUnlocker __st_lock(&this->lock);

		if(this->critical == true){
			throw new CriticalSectionMarkerException(__FILE__, __LINE__);
		}

		this->critical = true;
	}
}

void CriticalSectionMarker::exit() {
	{
		StackUnlocker __st_lock(&this->lock);
		if(this->critical == false){
			throw new CriticalSectionMarkerException(__FILE__, __LINE__);
		}

		this->critical = false;
	}
}

void CriticalSectionMarker::checkCritical() {
	{
		StackUnlocker __st_lock(&this->lock);
		if(this->critical == true){
			throw new CriticalSectionMarkerException(__FILE__, __LINE__);
		}
	}
}

} /* namespace alinous */
