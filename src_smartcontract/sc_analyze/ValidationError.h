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
	static constexpr int CODE_NO_RETURN_METHOD_VALUE = 5;

	static constexpr int CODE_VIRTUAL_FUNC_WITH_DIFFERENT_RETURN = 10;

	static constexpr int CODE_WRONG_FUNC_CALL_NAME = 20;
	static constexpr int CODE_WRONG_FUNC_CALL_AMBIGOUS = 21;

	static constexpr int CODE_CLASS_MEMBER_ALREADY_EXISTS = 30;
	static constexpr int CODE_CLASS_MEMBER_DOES_NOT_EXISTS = 31;
	static constexpr int CODE_CLASS_MEMBER_AND_STACK_VARIABLE_DO_NOT_EXISTS = 32;
	static constexpr int CODE_CLASS_MEMBER_VOID = 33;
	static constexpr int CODE_CLASS_DOES_NOT_IMPLEMENET_METHOD = 34;

	static constexpr int CODE_ALLOCATION_TYPE_DOES_NOT_EXISTS = 40;

	static constexpr int CODE_ARRAY_INDEX_MUST_BE_NUMERIC = 50;

	static constexpr int CODE_TYPE_INCOMPATIBLE = 60;

	static constexpr int CODE_ARITHMETIC_NON_INTEGER = 70;

	static constexpr int CODE_LOGICAL_EXP_NON_BOOL = 71;

	//static constexpr int CODE_WRONG_TYPE_NAME = 4;


	ValidationError(int type, int errorCode, CodeElement* element, const UnicodeString* msg, std::initializer_list<const UnicodeString*> params);
	virtual ~ValidationError();

	int getErrorCode() const noexcept;
private:
	int type;
	int errorCode;
	CodeElement* element;
	UnicodeString* message;
	ArrayList<UnicodeString> msgParams;
};

} /* namespace alinous */

#endif /* SC_ANALYZE_VALIDATIONERROR_H_ */
