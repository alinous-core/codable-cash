/*
 * VMemRawBitSet.cpp
 *
 *  Created on: 2020/06/22
 *      Author: iizuka
 */

#include "instance/instance_parts/VMemRawBitSet.h"

#include "vm/VirtualMachine.h"

#include "instance/instance_parts/VmMalloc.h"

#include "osenv/memory.h"

#include "vm/memory/VmMemoryManager.h"

namespace alinous {

constexpr const uint64_t VMemRawBitSet::TWO_N_ARRAY[64];

VMemRawBitSet::VMemRawBitSet(VirtualMachine* vm, uint32_t nbits) noexcept {
	this->bits = new(vm) VMemBitsetArray(vm, ((nbits >> OFFSET) + ((nbits & RIGHT_BITS) > 0)) ? 1 : 0 );
	this->_needClear = false;
	this->actualArrayLength = 0;
	this->isLengthActual = true;

}

VMemRawBitSet::~VMemRawBitSet() {
	delete this->bits;
}

void VMemRawBitSet::set(uint32_t pos) {
#ifdef __DEBUG__
	assert(pos >= (uint32_t)0);
#endif
	int len = (pos >> OFFSET) + 1;
	if(len > bits->length)
	{
		bits->growLength(len);
	}
	bits->set((*bits)[len - 1] | (TWO_N_ARRAY[pos & RIGHT_BITS]), len - 1);
	if(len > (int)actualArrayLength)
	{
		actualArrayLength = len;
		isLengthActual = true;
	}
	needClear();
}

void VMemRawBitSet::clear(uint32_t pos) {
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
		bits->set((*bits)[arrayPos] & (~(TWO_N_ARRAY[pos & RIGHT_BITS])),arrayPos);
		if((*bits)[actualArrayLength - 1] == (uint64_t)0)
		{
			isLengthActual = false;
		}
	}
}

void VMemRawBitSet::needClear() {
	this->_needClear = true;
}

int VMemRawBitSet::nextSetBit(const uint32_t pos) const {
	if(pos >= actualArrayLength << OFFSET)
	{
		return -1;
	}
	uint32_t idx = pos >> OFFSET;
	if((*bits)[idx] != (uint64_t)0L)
	{
		for(uint32_t j = pos & RIGHT_BITS; j < ELM_SIZE; j ++ )
		{
			if((((*bits)[idx] & (TWO_N_ARRAY[j])) != (uint64_t)0))
			{
				return (idx << OFFSET) + j;
			}
		}
	}
	idx ++ ;
	while(idx < actualArrayLength && (*bits)[idx] == (uint64_t)0L)
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
		if((((*bits)[idx] & (TWO_N_ARRAY[j])) != 0))
		{
			ret = (idx << OFFSET) + j;
			break;
		}
	}
	return ret;
}

void VMemRawBitSet::clear() {
	if(_needClear)
	{

		for(uint32_t i = 0; i < (uint32_t)bits->length; i ++ )
		{
			bits->set(0L, i);
		}
		actualArrayLength = 0;
		isLengthActual = true;
		_needClear = false;
	}
}

VMemRawBitSet::VMemBitsetArray::VMemBitsetArray(VirtualMachine* vm, int numBits) {
	this->alloc = vm->getAlloc();

	this->length = numBits;
	//this->buff = new uint64_t[numBits]{};
	this->buff = (uint64_t*)alloc->mallocPtrArray(sizeof(uint64_t) * numBits);
	Mem::memset(this->buff, 0, sizeof(uint64_t) * numBits);
}

VMemRawBitSet::VMemBitsetArray::~VMemBitsetArray() {
	this->alloc->releaseArray(this->buff);
}

void* VMemRawBitSet::VMemBitsetArray::operator new(size_t size,	VirtualMachine* vm) {
	VmMemoryManager* mem = vm->getMemory();
	uint64_t mallocSize = size + sizeof(VirtualMachine*);

	void* p = mem->malloc(mallocSize);
	VirtualMachine** vmp = (VirtualMachine**)p;
	*vmp = vm;

	return ((char*)p) + sizeof(VirtualMachine*);
}

void VMemRawBitSet::VMemBitsetArray::operator delete(void* p, size_t size) {
	void* ptr = ((char*)p) - sizeof(VirtualMachine*);

	VirtualMachine** vm = (VirtualMachine**)ptr;
	VmMemoryManager* mem = (*vm)->getMemory();

	mem->free((char*)ptr);
}

void VMemRawBitSet::VMemBitsetArray::growLength(uint32_t len) {
	// uint64_t* tmp = new uint64_t[len]{};
	uint64_t* tmp = (uint64_t*)this->alloc->mallocPtrArray(sizeof(uint64_t) * len);

	Mem::memcpy(tmp, buff, length * sizeof(uint64_t));
	this->length = len;

	// delete [] buff;
	this->alloc->releaseArray(this->buff);

	buff = tmp;
}

} /* namespace alinous */
