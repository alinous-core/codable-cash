/*
 * Integer.cpp
 *
 *  Created on: 2018/04/15
 *      Author: iizuka
 */

#include <base/Integer.h>

#include "base/exceptions.h"
#include "base/UnicodeString.h"
#include "base/Character.h"

namespace alinous {

constexpr const int Integer::MAX_VALUE;
constexpr const int Integer::MIN_VALUE;
constexpr const int Integer::SIZE;
constexpr const int Integer::MIN_RADIX;
constexpr const int Integer::MAX_RADIX;

Integer::Integer(int value) : value(value) {
}

Integer::~Integer() {
}

int Integer::parseInt(UnicodeString* string)
{
	return parseInt(string, 10);
}
int Integer::parseInt(UnicodeString* string, int radix)
{
	if(string == nullptr || radix < Integer::MIN_RADIX || radix > Integer::MAX_RADIX)
	{
		throw new NumberFormatException(__FILE__, __LINE__);
	}
	int length = string->length();int i = 0;
	if(length == 0)
	{
		throw new NumberFormatException(string, __FILE__, __LINE__);
	}
	bool negative = string->charAt(i) == L'-';
	if(negative && ++i == length)
	{
		throw new NumberFormatException(string, __FILE__, __LINE__);
	}
	return parse(string, i, radix, negative);
}

int Integer::parse(UnicodeString* string, int offset, int radix, bool negative)
{
	int max = Integer::MIN_VALUE / radix;
	int result = 0;int length = string->length();
	while(offset < length)
	{
		int digit = Character::digit(string->charAt(offset++), radix);
		if(digit == -1)
		{
			throw new NumberFormatException(string, __FILE__, __LINE__);
		}
		if(max > result)
		{
			throw new NumberFormatException(string, __FILE__, __LINE__);
		}
		result = result * radix - digit;
	}
	if(!negative)
	{
		result = -result;
		if(result < 0)
		{
			throw new NumberFormatException(string, __FILE__, __LINE__);
		}
	}
	return result;
}

int Integer::hashCode() const noexcept
{
	return value;
}

int Integer::compareTo(const Integer* object) const noexcept {
	return value > object->value ? 1 : (value < object->value ? -1 : 0);
}

int Integer::ValueCompare::operator() (const Integer* const _this, const  Integer* const object) const throw()
{
	return _this->compareTo(object);
}

} /* namespace alinous */
