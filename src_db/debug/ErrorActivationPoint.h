/*
 * ErrorActivationPoint.h
 *
 *  Created on: 2018/04/27
 *      Author: iizuka
 */

#ifndef DEBUG_ERRORACTIVATIONPOINT_H_
#define DEBUG_ERRORACTIVATIONPOINT_H_

namespace alinous {

class UnicodeString;
class ErrorOccurrence;

class ErrorActivationPoint {
public:
	ErrorActivationPoint(const wchar_t* name, ErrorOccurrence* error);
	virtual ~ErrorActivationPoint();

protected:
	UnicodeString* name;
	ErrorOccurrence* error;
};

} /* namespace alinous */

#endif /* DEBUG_ERRORACTIVATIONPOINT_H_ */
