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
	static constexpr int CODE_WRONG_IMPORT_FORMAT = 2;
	static constexpr int CODE_WRONG_CLASS_NAME = 3;
	static constexpr int CODE_WRONG_TYPE_NAME = 4;

	static constexpr int CODE_VIRTUAL_FUNC_WITH_DIFFERENT_RETURN = 10;

	static constexpr int CODE_WRONG_FUNC_CALL_NAME = 20;
	static constexpr int CODE_WRONG_FUNC_CALL_AMBIGOUS = 21;

	static constexpr int CODE_CLASS_MEMBER_ALREADY_EXISTS = 30;
	static constexpr int CODE_CLASS_MEMBER_DOES_NOT_EXISTS = 31;

	static constexpr int CODE_ALLOCATION_TYPE_DOES_NOT_EXISTS = 40;

	//static constexpr int CODE_WRONG_TYPE_NAME = 4;


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
