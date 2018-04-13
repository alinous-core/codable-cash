/*
 * UnicodeString.h
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */

#ifndef BASE_UNICODESTRING_H_
#define BASE_UNICODESTRING_H_

#include "RawArrayPrimitive.h"

namespace alinous {

class UnicodeString {
public:
	UnicodeString(const wchar_t* str);
	UnicodeString(const wchar_t* str, int cap);
	virtual ~UnicodeString();

	UnicodeString* append(wchar_t ch);

	int length() const throw();
	wchar_t get(int i) const throw();
	wchar_t charAt(int index) const throw();
	int isEmpty() const throw();
	bool equals(UnicodeString* str) throw();

	bool __equals(UnicodeString* str) const throw();

	int hashCode() throw();
protected:
	RawArrayPrimitive<wchar_t>* buff;
	int __hashCode;
};

} /* namespace alinous */

#endif /* BASE_UNICODESTRING_H_ */
