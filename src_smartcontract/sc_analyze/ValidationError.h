/*
 * ValidationError.h
 *
 *  Created on: 2019/06/01
 *      Author: iizuka
 */

#ifndef SC_ANALYZE_VALIDATIONERROR_H_
#define SC_ANALYZE_VALIDATIONERROR_H_

namespace alinous {
class CodeElement;
class UnicodeString;

class ValidationError {
public:
	static constexpr int ERROR = 10;
	static constexpr int WARNING = 1;

	ValidationError(int type, CodeElement* element, const UnicodeString* msg);
	virtual ~ValidationError();

private:
	int type;
	CodeElement* element;
	UnicodeString* message;
};

} /* namespace alinous */

#endif /* SC_ANALYZE_VALIDATIONERROR_H_ */
