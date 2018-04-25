/*
 * RawBitSet.cpp
 *
 *  Created on: 2018/04/14
 *      Author: iizuka
 */

#include "debug/debugMacros.h"

#include "base/RawBitSet.h"
#include "osenv/memory.h"

namespace alinous {

constexpr const uint64_t RawBitSet::TWO_N_ARRAY[64];

void RawBitSet::BitsetArray::growLength(uint32_t len) noexcept {
	uint64_t* tmp = new uint64_t[len]{};

	Mem::memcpy(tmp, buff, length * sizeof(uint64_t));
	this->length = len;
	delete [] buff;
	buff = tmp;
}

RawBitSet::RawBitSet(uint32_t nbits) noexcept : bits( (nbits >> OFFSET) + ((nbits & RIGHT_BITS) > 0) ? 1 : 0 )
		, _needClear(false), actualArrayLength(0), isLengthActual(true) {
}

RawBitSet::~RawBitSet() {
}

void RawBitSet::set(uint32_t pos) noexcept
{
#ifdef __DEBUG__
	assert(pos >= (uint32_t)0);
#endif
	int len = (pos >> OFFSET) + 1;
	if(len > bits.length)
	{
		bits.growLength(len);
	}
	bits.set(bits[len - 1] | (TWO_N_ARRAY[pos & RIGHT_BITS]), len - 1);
	if(len > (int)actualArrayLength)
	{
		actualArrayLength = len;
		isLengthActual = true;
	}
	needClear();
}

void RawBitSet::clear(uint32_t pos) noexcept
{
#ifdef __DEBUG__
	assert(pos >= (uint32_t)0);
#endif
	if(!_needClear)
	{
		return ;
	}
	uint32_t arrayPos = pos >> OFFSET;
	if(arrayPos < actualArrayLength)
	{
		bits.set(bits[arrayPos] & (~(TWO_N_ARRAY[pos & RIGHT_BITS])),arrayPos);
		if(bits[actualArrayLength - 1] == (uint64_t)0)
		{
			isLengthActual = false;
		}
	}
}

void RawBitSet::needClear() noexcept
{
	this->_needClear = true;
}

int RawBitSet::nextSetBit(const uint32_t pos) const noexcept
{
	if(pos >= actualArrayLength << OFFSET)
	{
		return -1;
	}
	uint32_t idx = pos >> OFFSET;
	if(bits[idx] != (uint64_t)0L)
	{
		for(uint32_t j = pos & RIGHT_BITS; j < ELM_SIZE; j ++ )
		{
			if(((bits[idx] & (TWO_N_ARRAY[j])) != (uint64_t)0))
			{
				return (idx << OFFSET) + j;
			}
		}
	}
	idx ++ ;
	while(idx < actualArrayLength && bits[idx] == (uint64_t)0L)
	{
		idx ++ ;
	}
	if(idx == actualArrayLength)
	{
		return -1;
	}

	int ret = -1;
	for(uint32_t j = 0; j < ELM_SIZE; j ++ )
	{
		if(((bits[idx] & (TWO_N_ARRAY[j])) != 0))
		{
			ret = (idx << OFFSET) + j;
			break;
		}
	}
	return ret;
}

void RawBitSet::clear() noexcept
{
	if(_needClear)
	{

		for(uint32_t i = 0; i < (uint32_t)bits.length; i ++ )
		{
			bits.set(0L, i);
		}
		actualArrayLength = 0;
		isLengthActual = true;
		_needClear = false;
	}
}


} /* namespace alinous */
