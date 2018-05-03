/*
 * ErrorOccurrence.h
 *
 *  Created on: 2018/04/27
 *      Author: iizuka
 */

#ifndef DEBUG_ERROROCCURRENCE_H_
#define DEBUG_ERROROCCURRENCE_H_

namespace alinous {

class UnicodeString;

class ErrorOccurrence {
public:
	ErrorOccurrence(const ErrorOccurrence& base) = delete;
	ErrorOccurrence(const wchar_t* name, int errorCount);
	virtual ~ErrorOccurrence();

	bool hit(const wchar_t* name) noexcept;
protected:
	UnicodeString* name;
	int errorCount;
	int count;
};

} /* namespace alinous */

#endif /* DEBUG_ERROROCCURRENCE_H_ */
