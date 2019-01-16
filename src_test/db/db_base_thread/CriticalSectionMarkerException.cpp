/*
 * CriticalSectionMarkerException.cpp
 *
 *  Created on: 2019/01/12
 *      Author: iizuka
 */

#include "db/db_base_thread/CriticalSectionMarkerException.h"

namespace alinous {

CriticalSectionMarkerException::CriticalSectionMarkerException(const char* srcfile, int srcline) :
	Exception(srcfile, srcline) {
}

CriticalSectionMarkerException::~CriticalSectionMarkerException() {
}

} /* namespace alinous */
