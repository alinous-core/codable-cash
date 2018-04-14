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
	UnicodeString(const wchar_t* str) noexcept;
	UnicodeString(const wchar_t* str, int cap) noexcept;
	UnicodeString(const UnicodeString* ptr) noexcept;

	virtual ~UnicodeString();

	UnicodeString* append(wchar_t ch) noexcept;
	UnicodeString* append(UnicodeString* str) noexcept;

	char* toCString();

	int length() const noexcept;
	wchar_t get(int i) const noexcept;
	wchar_t charAt(int index) const noexcept;
	int isEmpty() const noexcept;
	bool equals(UnicodeString* str) noexcept;

	bool __equals(UnicodeString* str) const noexcept;

	int hashCode() noexcept;
protected:
	RawArrayPrimitive<wchar_t>* buff;
	int __hashCode;
};

} /* namespace alinous */

#endif /* BASE_UNICODESTRING_H_ */
