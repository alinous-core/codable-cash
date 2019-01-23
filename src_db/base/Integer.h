/*
 * Integer.h
 *
 *  Created on: 2018/04/15
 *      Author: iizuka
 */

#ifndef BASE_INTEGER_H_
#define BASE_INTEGER_H_

namespace alinous {

class UnicodeString;

class Integer {
public:
	constexpr static const int MAX_VALUE{((int)0x7FFFFFFF)};
	constexpr static const int MIN_VALUE{((int)0x80000000)};
	constexpr static const int SIZE{32};
	constexpr static const int MIN_RADIX{2};
	constexpr static const int MAX_RADIX{36};

	Integer(const Integer& base) = default;
	explicit Integer(int value);
	virtual ~Integer();

	//static int numberOfLeadingZeros(int i);
	//static int bitCount(int i);

	static int parseInt(UnicodeString* string);
	static int parseInt(UnicodeString* string, int radix);

	static UnicodeString* toString(int i, int radix);
protected:
	static int parse(UnicodeString* string, int offset, int radix, bool negative);

public:
	int hashCode() const noexcept;
	bool equals(const Integer* o) const noexcept { return compareTo(o) == 0;};
	int compareTo(const Integer* object) const noexcept;

	int value;

public:

	class ValueCompare {
	public:
		int operator() (const Integer* const _this, const  Integer* const object) const noexcept;
	};
};

} /* namespace alinous */

#endif /* BASE_INTEGER_H_ */
