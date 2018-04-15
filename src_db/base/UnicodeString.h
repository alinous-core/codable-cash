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
	UnicodeString(const UnicodeString& inst) noexcept;
	virtual ~UnicodeString();

private:
	UnicodeString* __append(wchar_t ch) noexcept;
	void __closeString() noexcept;
public:
	UnicodeString* append(wchar_t ch) noexcept;
	UnicodeString* append(UnicodeString* str) noexcept;
	UnicodeString* append(int value) noexcept;

	UnicodeString* replace(wchar_t last, wchar_t next) const noexcept;

	char* toCString();
	const wchar_t* towString() const noexcept;

	UnicodeString* toLowerCase() const noexcept;
	UnicodeString* toUpperCase() const noexcept;

	bool startsWith(UnicodeString* str) const noexcept;
	bool startsWith(UnicodeString* str, int start) const noexcept;
	bool endsWith(UnicodeString* str) const noexcept;
	int getNextMatch(int pos, UnicodeString* str, wchar_t* next) const noexcept;


	UnicodeString* substring(int begin) const noexcept;
	UnicodeString* substring(int begin, int end) const noexcept;
	int indexOf(UnicodeString* str) const noexcept;
	int indexOf(UnicodeString* str, int lastIndex) const noexcept;
	int indexOf(wchar_t ch) const noexcept;
	int indexOf(wchar_t ch, int lastIndex) const noexcept;
	int lastIndexOf(wchar_t ch) const noexcept;
	int lastIndexOf(wchar_t ch, int lastIndex) const noexcept;
	int lastIndexOf(UnicodeString* str) const noexcept;
	int lastIndexOf(UnicodeString* str, int lastIndex) const noexcept;

	UnicodeString* insert(int position, wchar_t ch) noexcept;
	UnicodeString* insert(int dstOffset, UnicodeString* str) noexcept;
	UnicodeString* insert(int dstOffset, const wchar_t* str, int offset, int count) noexcept;

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

public:
	class ValueCompare {
	public:
		int operator () (const UnicodeString* const a, const UnicodeString* const b) const;
	};
};

} /* namespace alinous */

#endif /* BASE_UNICODESTRING_H_ */
