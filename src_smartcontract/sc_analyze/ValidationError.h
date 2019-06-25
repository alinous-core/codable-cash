/*
 * ValidationError.h
 *
 *  Created on: 2019/06/01
 *      Author: iizuka
 */

#ifndef SC_ANALYZE_VALIDATIONERROR_H_
#define SC_ANALYZE_VALIDATIONERROR_H_
#include <initializer_list>

#include "base/ArrayList.h"

namespace alinous {
class CodeElement;
class UnicodeString;

class ValidationError {
public:
	static constexpr int ERROR = 10;
	static constexpr int WARNING = 1;

	static constexpr int CODE_CLASS_ALREADY_EXISTS = 1;
	static constexpr int CODE_WRONG_IMPORT_FORMAT = 1;


	ValidationError(int type, int errorCode, CodeElement* element, const UnicodeString* msg, std::initializer_list<const UnicodeString*> params);
	virtual ~ValidationError();

private:
	int type;
	int errorCode;
	CodeElement* element;
	UnicodeString* message;
	ArrayList<UnicodeString> msgParams;
};

} /* namespace alinous */

#endif /* SC_ANALYZE_VALIDATIONERROR_H_ */
