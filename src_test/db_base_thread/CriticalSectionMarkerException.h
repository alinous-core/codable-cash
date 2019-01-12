/*
 * CriticalSectionMarkerException.h
 *
 *  Created on: 2019/01/12
 *      Author: iizuka
 */

#ifndef DB_BASE_THREAD_CRITICALSECTIONMARKEREXCEPTION_H_
#define DB_BASE_THREAD_CRITICALSECTIONMARKEREXCEPTION_H_

#include "base/Exception.h"

namespace alinous {

class CriticalSectionMarkerException: public Exception {
public:
	CriticalSectionMarkerException(const char* srcfile, int srcline);
	virtual ~CriticalSectionMarkerException();
};

} /* namespace alinous */

#endif /* DB_BASE_THREAD_CRITICALSECTIONMARKEREXCEPTION_H_ */
