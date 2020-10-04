/*
 * UnicodeString.h
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */

#ifndef BASE_UNICODESTRING_H_
#define BASE_UNICODESTRING_H_

#include "RawArrayPrimitive.h"
#include "ArrayList.h"

#include <cstdint>

namespace alinous {


class UnicodeString {
protected:
	RawArrayPrimitive<wchar_t>* buff;
	int __hashCode;
public:
	UnicodeString &operator=(const UnicodeString &o);


	UnicodeString(const UnicodeString& inst) noexcept;
	UnicodeString() noexcept;

	explicit UnicodeString(const wchar_t* str) noexcept;
	explicit UnicodeString(const wchar_t* str, int cap) noexcept;
	//explicit UnicodeString(const wchar_t* str, int offset, int count) noexcept;
	explicit UnicodeString(const char* str) noexcept;
	explicit UnicodeString(const UnicodeString* ptr) noexcept;


	virtual ~UnicodeString();

private:
	UnicodeString* __append(wchar_t ch) noexcept;
	void __closeString() noexcept;
public:
	UnicodeString& append(const wchar_t ch) noexcept;
	UnicodeString& append(const UnicodeString* str) noexcept;
	UnicodeString& append(const int value) noexcept;
	UnicodeString& append(const wchar_t* str) noexcept;
	UnicodeString& append(const wchar_t* str, int len) noexcept;
	UnicodeString& append(const int16_t* str, int offset, int len) noexcept;
	UnicodeString& append(const wchar_t* str, int offset, int len) noexcept;

	static UnicodeString* valueOf(const int16_t* str, int offset, int len);

	UnicodeString* replace(wchar_t last, wchar_t next) const noexcept;

	const char* toCString() const;
	const char* toCString(const UnicodeString* charset) const;
	const wchar_t* towString() const noexcept;
	const wchar_t* c_str(){ return towString(); }

	UnicodeString* toLowerCase() const noexcept;
	UnicodeString* toUpperCase() const noexcept;

	bool startsWith(const UnicodeString& str) const noexcept;
	bool startsWith(const UnicodeString* str) const noexcept;
	bool startsWith(const UnicodeString* str, int start) const noexcept;
	bool endsWith(const UnicodeString* str) const noexcept;
	int getNextMatch(int pos, const UnicodeString* str, wchar_t* next) const noexcept;


	UnicodeString* substring(int begin) const noexcept;
	UnicodeString* substring(int begin, int end) const noexcept;
	int indexOf(const UnicodeString* str) const noexcept;
	int indexOf(const UnicodeString* str, int lastIndex) const noexcept;
	int indexOf(wchar_t ch) const noexcept;
	int indexOf(wchar_t ch, int lastIndex) const noexcept;
	int lastIndexOf(wchar_t ch) const noexcept;
	int lastIndexOf(wchar_t ch, int lastIndex) const noexcept;
	int lastIndexOf(const UnicodeString* str) const noexcept;
	int lastIndexOf(const UnicodeString* str, int lastIndex) const noexcept;

	UnicodeString* insert(int position, wchar_t ch) noexcept;
	UnicodeString* insert(int dstOffset, UnicodeString* str) noexcept;
	UnicodeString* insert(int dstOffset, const wchar_t* str, int offset, int count) noexcept;

	ArrayList<UnicodeString>* split(const UnicodeString* pattern) const noexcept;
	ArrayList<UnicodeString>* split(const UnicodeString* pattern, bool addBlankString) const noexcept;

	int length() const noexcept;
	wchar_t get(int i) const noexcept;
	wchar_t charAt(int index) const noexcept;
	int isEmpty() const noexcept;
	bool equals(const UnicodeString* str) const noexcept;
	bool equals(const UnicodeString& str) const noexcept;
	bool equals(const wchar_t* str) const noexcept;

	bool __equals(const UnicodeString* str) const noexcept;

	int hashCode() const noexcept;


public:
	class ValueCompare {
	public:
		int operator () (const UnicodeString* const a, const UnicodeString* const b) const;
	};
};

} /* namespace alinous */

#endif /* BASE_UNICODESTRING_H_ */
