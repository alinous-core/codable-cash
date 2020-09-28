/*
 * FeeTransactionsListValue.cpp
 *
 *  Created on: 2019/01/13
 *      Author: iizuka
 */

#include "mempool_idx/FeeTransactionsListValue.h"
#include "base_io/ByteBuffer.h"

namespace codablecash {

FeeTransactionsListValue::FeeTransactionsListValue(const FeeTransactionsListValue& inst) : list(8), IBlockObject() {
	int maxLoop = inst.list.size();
	for(int i = 0; i != maxLoop; ++i){
		uint64_t v = inst.list.get(i);

		this->list.addElement(v);
	}
}

FeeTransactionsListValue::FeeTransactionsListValue() : list(8), IBlockObject() {
}

FeeTransactionsListValue::FeeTransactionsListValue(uint64_t value) : list(8), IBlockObject() {
	this->list.addElement(value);
}

FeeTransactionsListValue::~FeeTransactionsListValue() {
}

int FeeTransactionsListValue::binarySize() const {
	int total = sizeof(uint32_t);
	total += sizeof(uint64_t) * this->list.size();

	return total;
}

void FeeTransactionsListValue::toBinary(ByteBuffer* out) const {
	int maxLoop = this->list.size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		uint64_t fpos = this->list.get(i);
		out->putLong(fpos);
	}
}

FeeTransactionsListValue* FeeTransactionsListValue::fromBinary(ByteBuffer* in) {
	FeeTransactionsListValue* value = new FeeTransactionsListValue();

	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		uint64_t fpos = in->getLong();
		value->list.addElement(fpos);
	}

	return value;
}

void FeeTransactionsListValue::join(const FeeTransactionsListValue* value) noexcept {
	const RawArrayPrimitive<uint64_t>* newList = &value->list;

	int maxLoop = newList->size();
	for(int i = 0; i != maxLoop; ++i){
		uint64_t v = newList->get(i);
		if(contains(v)){
			continue;
		}
		this->list.addElement(v);
	}
}

bool FeeTransactionsListValue::contains(uint64_t value) const noexcept {
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		uint64_t v = this->list.get(i);
		if(v == value){
			return true;
		}
	}

	return false;
}

void FeeTransactionsListValue::remove(uint64_t value) noexcept {
	int index = indexof(value);

	this->list.remove(index);
}

int FeeTransactionsListValue::indexof(uint64_t value) const noexcept {
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		uint64_t v = this->list.get(i);
		if(v == value){
			return i;
		}
	}

	return -1;
}

bool FeeTransactionsListValue::isEmpty() const noexcept {
	return this->list.size() == 0;
}

IBlockObject* FeeTransactionsListValue::copyData() const noexcept {
	return new FeeTransactionsListValue(*this);
}

} /* namespace codablecash */
