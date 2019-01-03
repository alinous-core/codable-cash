/*
 * ByteBuffer.cpp
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */

#include "debug/debugMacros.h"

#include "base_io/ByteBuffer.h"
#include "base_io/exceptions.h"

#include "base/RawArrayPrimitive.h"
#include "base_io/ReverseByteBuffer.h"


namespace alinous {

ByteBuffer::ByteBuffer(const int length) noexcept {
	this->data = new RawArrayPrimitive<uint8_t>(length);
	this->lim = length;
	this->cap = length;
	this->pos = 0;
}

ByteBuffer::ByteBuffer(const uint8_t* buffer, int length) {
	this->data = new RawArrayPrimitive<uint8_t>(length);
	this->lim = length;
	this->cap = length;
	this->pos = 0;

	put(buffer, length);
	this->pos = 0;
}

ByteBuffer* ByteBuffer::allocate(const int capacity) noexcept {
	ByteBuffer* buff = new ByteBuffer(capacity);
	return buff;
}

ByteBuffer* ByteBuffer::wrap(const uint8_t* buffer, int length) {
	ByteBuffer* buff = new ByteBuffer(buffer, length);
	return buff;
}

ByteBuffer* ByteBuffer::allocateWithEndian(const int capacity,
		bool bigEndian) noexcept {
	int32_t num = 0xABCDEF01;
	char* p = (char*)(&num);

	bool isBig = (*p == 0xAB);
	if(isBig == bigEndian){
		return ByteBuffer::allocate(capacity);
	}

	return new ReverseByteBuffer(capacity);
}

ByteBuffer* ByteBuffer::wrapWithEndian(const uint8_t* buffer, int length, bool bigEndian) noexcept(false){
	int32_t num = 0xABCDEF01;
	char* p = (char*)(&num);

	bool isBig = (*p == 0xAB);
	if(isBig == bigEndian){
		return ByteBuffer::wrap(buffer, length);
	}

	return ReverseByteBuffer::wrap(buffer, length);
}


ByteBuffer::~ByteBuffer() noexcept {
	delete this->data;
}


ByteBuffer* ByteBuffer::clear() noexcept {
	this->lim = this->cap;
	this->pos = 0;
	return this;
}


int ByteBuffer::remaining() const noexcept
{
	 return this->lim - this->pos;
}

int ByteBuffer::position() const noexcept
{
	return this->pos;
}
ByteBuffer* ByteBuffer::position(const int newPosition) noexcept
{
	this->pos = newPosition;
	return this;
}
int ByteBuffer::limit() noexcept
{
	return this->lim;
}
ByteBuffer* ByteBuffer::limit(const int limit) noexcept
{
	this->lim = limit;
	return this;
}

int ByteBuffer::capacity() noexcept {
	return this->cap;
}

char ByteBuffer::get() noexcept(false) {
	if(remaining() < (int)sizeof(char)){
		throw new BufferOverflowException(L"put(char b)", __FILE__, __LINE__);
	}

	return data->get(this->pos++);
}

char ByteBuffer::get(const int index) const noexcept(false) {
	if(index + (int)sizeof(char) > lim){
		throw new BufferOverflowException(L"put(int index, uint8_t b)", __FILE__, __LINE__);
	}

	return data->get(index);
}

ByteBuffer* ByteBuffer::get(uint8_t* dest, int length) noexcept(false) {
	return get(dest, 0, length);
}


ByteBuffer* ByteBuffer::get(uint8_t* dest, int off, int len) noexcept(false) {
	if (__builtin_expect(len > remaining(), 0)) {
		throw new BufferUnderflowException(__FILE__, __LINE__);
	}

	Mem::memcpy(dest + off, data->getRoot() + this->pos, len);
	this->pos += len;
/*
	for (int i = off; i < off + len; i++) {
		dest->set(get(ctx), i, ctx);
	}
*/
	return this;
}

ByteBuffer* ByteBuffer::put(char b) noexcept(false) {
	if(remaining() < (int)sizeof(char)){
		throw new BufferOverflowException(L"put(char b)", __FILE__, __LINE__);
	}

	data->set(this->pos++, b);
	return this;
}

ByteBuffer* ByteBuffer::put(int index, uint8_t b) noexcept(false) {
	if(index + (int)sizeof(char) > lim){
		throw new BufferOverflowException(L"put(int index, uint8_t b)", __FILE__, __LINE__);
	}

	data->set(index, b);
	return this;
}

ByteBuffer* ByteBuffer::put(const uint8_t* src, int length) noexcept(false) {
    return put(src, 0, length);
}

ByteBuffer* ByteBuffer::put(const uint8_t* src, int off, int len) noexcept(false) {
    if (len > remaining()) {
        throw new BufferOverflowException(__FILE__, __LINE__);
    }

    Mem::memcpy(data->getRoot() + this->pos, src + off, len);
    this->pos += len;

    return this;
}

ByteBuffer* ByteBuffer::put(ByteBuffer* src) noexcept(false) {
	int maxLoop = src->lim;

	if(remaining() < maxLoop){
		throw new BufferOverflowException(L"put(ByteBuffer* src)", __FILE__, __LINE__);
	}

	Mem::memcpy(&data->getRoot()[this->pos], src->data->getRoot(), maxLoop);
	this->pos += maxLoop;

	return this;
}

ByteBuffer* ByteBuffer::putChar(wchar_t value) noexcept(false) {
	if(remaining() < (int)sizeof(short)){
		throw new BufferOverflowException(L"put(wchar_t value)", __FILE__, __LINE__);
	}

	uint16_t sh = (uint16_t)value;
	char* bytes = (char*)&sh;

	data->set(this->pos++, bytes[0]);
	data->set(this->pos++, bytes[1]);

	return this;
}

ByteBuffer* ByteBuffer::putChar(int position, wchar_t value) noexcept(false) {
	if(this->lim - position < (int)sizeof(short)){
		throw new BufferOverflowException(L"putChar(int position, wchar_t value)", __FILE__, __LINE__);
	}

	uint16_t sh = (uint16_t)value;
	char* bytes = (char*)&sh;

	data->set(position++, bytes[0]);
	data->set(position++, bytes[1]);

	return this;
}

ByteBuffer* ByteBuffer::putShort(short value) noexcept(false) {
	if(remaining() < (int)sizeof(short)){
		throw new BufferOverflowException(L"putShort(short value)", __FILE__, __LINE__);
	}

	char* bytes = (char*)&value;

	data->set(this->pos++, bytes[0]);
	data->set(this->pos++, bytes[1]);

	return this;
}

ByteBuffer* ByteBuffer::putShort(int position, short value) noexcept(false) {
	if(this->lim - position < (int)sizeof(short)){
		throw new BufferOverflowException(L"putShort(int position, short value)", __FILE__, __LINE__);
	}

	char* bytes = (char*)&value;

	data->set(position++, bytes[0]);
	data->set(position++, bytes[1]);

	return this;
}

ByteBuffer* ByteBuffer::putInt(int32_t value) noexcept(false) {
	if(remaining() < (int)sizeof(int32_t)){
		throw new BufferOverflowException(L"putInt(int32_t value)", __FILE__, __LINE__);
	}

	int32_t* ptr = (int32_t*)(data->getRoot() + this->pos);
	*ptr = value;

	this->pos += 4;

	return this;
}

ByteBuffer* ByteBuffer::putInt(int32_t position, int value) noexcept(false) {
	if(this->lim - position < (int)sizeof(int32_t)){
		throw new BufferOverflowException(L"putInt(int32_t position, int value)", __FILE__, __LINE__);
	}

	char* bytes = (char*)&value;

	int pos = position;
	data->set(pos++, bytes[0]);
	data->set(pos++, bytes[1]);
	data->set(pos++, bytes[2]);
	data->set(pos++, bytes[3]);

	return this;
}

ByteBuffer* ByteBuffer::putLong(int64_t value) noexcept(false) {
	if(remaining() < (int)sizeof(int64_t)){
		throw new BufferOverflowException(L"putLong(int64_t value)", __FILE__, __LINE__);
	}

	char* bytes = (char*)&value;


	Mem::memcpy(&data->getRoot()[this->pos], bytes, sizeof(int64_t));

	this->pos += sizeof(int64_t);

	return this;
}

ByteBuffer* ByteBuffer::putLong(int position, int64_t value) noexcept(false) {
	if(this->lim - position < (int)sizeof(int64_t)){
		throw new BufferOverflowException(L"putLong(int position, int64_t value)", __FILE__, __LINE__);
	}

	char* bytes = (char*)&value;


	Mem::memcpy(&data->getRoot()[position], bytes, sizeof(int64_t));

	this->pos += sizeof(int64_t);

	return this;
}

ByteBuffer* ByteBuffer::putFloat(float value) noexcept(false) {
	if(remaining() < (int)sizeof(float)){
		throw new BufferOverflowException(L"putFloat(float value)", __FILE__, __LINE__);
	}

	char* bytes = (char*)&value;

	data->set(this->pos++, bytes[0]);
	data->set(this->pos++, bytes[1]);
	data->set(this->pos++, bytes[2]);
	data->set(this->pos++, bytes[3]);

	return this;
}

ByteBuffer* ByteBuffer::putFloat(int position, float value) noexcept(false) {
	if(this->lim - position < (int)sizeof(float)){
		throw new BufferOverflowException(L"putFloat(int position, float value)", __FILE__, __LINE__);
	}

	char* bytes = (char*)&value;

	data->set(position++, bytes[0]);
	data->set(position++, bytes[1]);
	data->set(position++, bytes[2]);
	data->set(position++, bytes[3]);

	return this;
}

ByteBuffer* ByteBuffer::putDouble(double value) noexcept(false) {
	if(remaining() < (int)sizeof(double)){
		throw new BufferOverflowException(L"putDouble(double value)", __FILE__, __LINE__);
	}

	char* bytes = (char*)&value;

	data->set(this->pos++, bytes[0]);
	data->set(this->pos++, bytes[1]);
	data->set(this->pos++, bytes[2]);
	data->set(this->pos++, bytes[3]);
	data->set(this->pos++, bytes[4]);
	data->set(this->pos++, bytes[5]);
	data->set(this->pos++, bytes[6]);
	data->set(this->pos++, bytes[7]);

	return this;
}

ByteBuffer* ByteBuffer::putDouble(int position, double value) noexcept(false) {
	if(this->lim - position < (int)sizeof(double)){
		throw new BufferOverflowException(L"putDouble(int position, double value)", __FILE__, __LINE__);
	}

	char* bytes = (char*)&value;

	data->set(position++, bytes[0]);
	data->set(position++, bytes[1]);
	data->set(position++, bytes[2]);
	data->set(position++, bytes[3]);
	data->set(position++, bytes[4]);
	data->set(position++, bytes[5]);
	data->set(position++, bytes[6]);
	data->set(position++, bytes[7]);

	return this;
}

int64_t ByteBuffer::getLong() noexcept(false) {
	if(remaining() < (int)sizeof(int64_t)){
		throw new BufferOverflowException(__FILE__, __LINE__);
	}

	long long val = *((long long*)(this->data->getRoot() + this->pos));
	this->pos += sizeof(int64_t);

	return val;
}

int64_t ByteBuffer::getLong(int position) noexcept(false) {
	if(this->lim - position < (int)sizeof(int64_t)){
		throw new BufferOverflowException(__FILE__, __LINE__);
	}

	long long val = *((long long*)(this->data->getRoot() + position));

	return val;
}

double ByteBuffer::getDouble() noexcept(false) {
	if(remaining() < (int)sizeof(double)){
		throw new BufferOverflowException(__FILE__, __LINE__);
	}

	uint8_t* ptr = this->data->getRoot() + this->pos;
	uint8_t dest[8]{};

	dest[0] = ptr[0];
	dest[1] = ptr[1];
	dest[2] = ptr[2];
	dest[3] = ptr[3];
	dest[4] = ptr[4];
	dest[5] = ptr[5];
	dest[6] = ptr[6];
	dest[7] = ptr[7];

	this->pos += sizeof(double);

	return *(reinterpret_cast<double*>((void*)dest));
}

double ByteBuffer::getDouble(int position) noexcept(false) {
	if(this->lim - position < (int)sizeof(double)){
		throw new BufferOverflowException(__FILE__, __LINE__);
	}

	uint8_t* ptr = this->data->getRoot() + position;
	uint8_t dest[8]{};

	dest[0] = ptr[0];
	dest[1] = ptr[1];
	dest[2] = ptr[2];
	dest[3] = ptr[3];
	dest[4] = ptr[4];
	dest[5] = ptr[5];
	dest[6] = ptr[6];
	dest[7] = ptr[7];

	this->pos += sizeof(double);

	return *(reinterpret_cast<double*>((void*)dest));
}

float ByteBuffer::getFloat() noexcept(false) {
	if(remaining() < (int)sizeof(float)){
		throw new BufferOverflowException(__FILE__, __LINE__);
	}

	uint8_t* ptr = this->data->getRoot() + this->pos;
	uint8_t dest[4]{};

	dest[0] = ptr[0];
	dest[1] = ptr[1];
	dest[2] = ptr[2];
	dest[3] = ptr[3];

	this->pos += sizeof(float);

	return *(reinterpret_cast<float*>((void*)dest));
}

float ByteBuffer::getFloat(int position) noexcept(false) {
	if(this->lim - position < (int)sizeof(float)){
		throw new BufferOverflowException(__FILE__, __LINE__);
	}

	uint8_t* ptr = this->data->getRoot() + position;
	uint8_t dest[4]{};

	dest[0] = ptr[0];
	dest[1] = ptr[1];
	dest[2] = ptr[2];
	dest[3] = ptr[3];

	this->pos = position + sizeof(float);

	return *(reinterpret_cast<float*>((void*)dest));
}

int32_t ByteBuffer::getInt() noexcept(false) {
	if(remaining() < (int)sizeof(int32_t)){
		throw new BufferOverflowException(L"", __FILE__, __LINE__);
	}

	int32_t val = *((int32_t*)(this->data->getRoot() + this->pos));
	this->pos += sizeof(int32_t);

	return val;
}

int32_t ByteBuffer::getInt(int position) noexcept(false) {
	if(this->lim - position < (int)sizeof(int32_t)){
		throw new BufferOverflowException(__FILE__, __LINE__);
	}

	int32_t val = *((int32_t*)(this->data->getRoot() + position));
	this->pos = position + sizeof(int16_t);

	return val;
}

wchar_t ByteBuffer::getChar() noexcept(false) {
	if(remaining() < (int)sizeof(int16_t)){
		throw new BufferOverflowException(L"", __FILE__, __LINE__);
	}

	wchar_t val = *((short*)(this->data->getRoot() + this->pos));

	this->pos += sizeof(int16_t);

	return (wchar_t)val;
}

wchar_t ByteBuffer::getChar(int position) noexcept(false) {
	if(this->lim - position < (int)sizeof(int16_t)){
		throw new BufferOverflowException(__FILE__, __LINE__);
	}

	int16_t val = *((int16_t*)(this->data->getRoot() + position));
	this->pos = position + sizeof(int16_t);

	return (wchar_t)val;
}

int16_t ByteBuffer::getShort() noexcept(false) {
	if(remaining() < (int)sizeof(int16_t)){
		throw new BufferOverflowException(L"", __FILE__, __LINE__);
	}

	int16_t val = *((int16_t*)(this->data->getRoot() + this->pos));
	this->pos += sizeof(int16_t);

	return val;
}

int16_t ByteBuffer::getShort(int position) noexcept(false) {
	if(this->lim - position < (int)sizeof(int16_t)){
		throw new BufferOverflowException(__FILE__, __LINE__);
	}

	int16_t val = *((int16_t*)(this->data->getRoot() + position));
	this->pos = position + sizeof(int16_t);

	return val;
}

const uint8_t* ByteBuffer::array() const noexcept {
	return data->getRoot();
}

ByteBuffer* ByteBuffer::clone() const {
	return new ByteBuffer(array(), this->cap);
}

} /* namespace alinous */


