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


ByteBuffer::~ByteBuffer() noexcept {
	delete this->data;
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

char ByteBuffer::get() noexcept {
	return data->get(this->pos++);
}

char ByteBuffer::get(const int index) const noexcept {
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

ByteBuffer* ByteBuffer::put(char b) noexcept {
	data->set(this->pos++, b);
	return this;
}

ByteBuffer* ByteBuffer::put(int index, uint8_t b) noexcept {
	data->set(index, b);
	return this;
}

ByteBuffer* ByteBuffer::put(const uint8_t* src, int length) noexcept(false) {
    return put(src, 0, length);
}

ByteBuffer* ByteBuffer::put(const uint8_t* src, int off, int len) noexcept(false) {
/*    int length = src->length;
    if ((off < 0) || (len < 0) || off + len > length) {
        throw new IndexOutOfBoundsException(ctx);
    }
*/
    if (len > remaining()) {
        throw new BufferOverflowException(__FILE__, __LINE__);
    }

    Mem::memcpy(data->getRoot() + this->pos, src + off, len);
    this->pos += len;

    return this;
}

ByteBuffer* ByteBuffer::put(ByteBuffer* src) noexcept {
	int maxLoop = src->lim;

	Mem::memcpy(&data->getRoot()[this->pos], src->data->getRoot(), maxLoop);
	this->pos += maxLoop;

	return this;
}

ByteBuffer* ByteBuffer::putChar(wchar_t value) noexcept {
	//data->set(this->pos++, value & 0xFF);
	//data->set(this->pos++, (value >> 1) & 0xFF);

	uint16_t sh = (uint16_t)value;
	char* bytes = (char*)&sh;

	data->set(this->pos++, bytes[0]);
	data->set(this->pos++, bytes[1]);

	return this;
}

ByteBuffer* ByteBuffer::putChar(int position, wchar_t value) noexcept {
	//data->set(this->pos++, value & 0xFF);
	//data->set(this->pos++, (value >> 1) & 0xFF);

	uint16_t sh = (uint16_t)value;
	char* bytes = (char*)&sh;

	data->set(position++, bytes[0]);
	data->set(position++, bytes[1]);

	return this;
}

ByteBuffer* ByteBuffer::putShort(short value) noexcept {
	char* bytes = (char*)&value;

	data->set(this->pos++, bytes[0]);
	data->set(this->pos++, bytes[1]);

	return this;
}

ByteBuffer* ByteBuffer::putShort(int position, short value) noexcept {
	char* bytes = (char*)&value;

	data->set(position++, bytes[0]);
	data->set(position++, bytes[1]);

	return this;
}

ByteBuffer* ByteBuffer::putInt(int32_t value) noexcept {
	int32_t* ptr = (int32_t*)(data->getRoot() + this->pos);
	*ptr = value;

	this->pos += 4;

/*
	char* bytes = (char*)&value;

	char* dest = data->getRoot();

	dest[this->pos++] = bytes[0];
	dest[this->pos++] = bytes[1];
	dest[this->pos++] = bytes[2];
	dest[this->pos++] = bytes[3];
*/
	return this;
}

ByteBuffer* ByteBuffer::putInt(int32_t position, int value) noexcept {
	char* bytes = (char*)&value;

	int pos = position;
	data->set(pos++, bytes[0]);
	data->set(pos++, bytes[1]);
	data->set(pos++, bytes[2]);
	data->set(pos++, bytes[3]);

	return this;
}

ByteBuffer* ByteBuffer::putLong(int64_t value) noexcept {
	char* bytes = (char*)&value;


	Mem::memcpy(&data->getRoot()[this->pos], bytes, sizeof(int64_t));

	this->pos += sizeof(int64_t);

	return this;
}

ByteBuffer* ByteBuffer::putLong(int position, int64_t value) noexcept {
	char* bytes = (char*)&value;


	Mem::memcpy(&data->getRoot()[position], bytes, sizeof(int64_t));

	this->pos += sizeof(int64_t);

	return this;
}

ByteBuffer* ByteBuffer::putFloat(float value) noexcept {
	char* bytes = (char*)&value;

	data->set(this->pos++, bytes[0]);
	data->set(this->pos++, bytes[1]);
	data->set(this->pos++, bytes[2]);
	data->set(this->pos++, bytes[3]);

	return this;
}

ByteBuffer* ByteBuffer::putFloat(int position, float value) noexcept {
	char* bytes = (char*)&value;

	data->set(position++, bytes[0]);
	data->set(position++, bytes[1]);
	data->set(position++, bytes[2]);
	data->set(position++, bytes[3]);

	return this;
}

ByteBuffer* ByteBuffer::putDouble(double value) noexcept {
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

ByteBuffer* ByteBuffer::putDouble(int position, double value) noexcept {
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

uint64_t ByteBuffer::getLong() noexcept {
	long long val = *((long long*)(this->data->getRoot() + this->pos));
	this->pos += sizeof(int64_t);

	return val;
}

uint64_t ByteBuffer::getLong(int position) noexcept {
	long long val = *((long long*)(this->data->getRoot() + position));

	return val;
}

double ByteBuffer::getDouble() noexcept {
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

double ByteBuffer::getDouble(int position) noexcept {
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

float ByteBuffer::getFloat() noexcept {
	uint8_t* ptr = this->data->getRoot() + this->pos;
	uint8_t dest[4]{};

	dest[0] = ptr[0];
	dest[1] = ptr[1];
	dest[2] = ptr[2];
	dest[3] = ptr[3];

	this->pos += sizeof(float);

	return *(reinterpret_cast<float*>((void*)dest));
}

float ByteBuffer::getFloat(int position) noexcept {
	uint8_t* ptr = this->data->getRoot() + position;
	uint8_t dest[4]{};

	dest[0] = ptr[0];
	dest[1] = ptr[1];
	dest[2] = ptr[2];
	dest[3] = ptr[3];

	this->pos += sizeof(float);

	return *(reinterpret_cast<float*>((void*)dest));
}

int32_t ByteBuffer::getInt() noexcept {
	int32_t val = *((int32_t*)(this->data->getRoot() + this->pos));
	this->pos += sizeof(int32_t);

	return val;
}

int32_t ByteBuffer::getInt(int position) noexcept {
	int32_t val = *((int32_t*)(this->data->getRoot() + position));

	return val;
}

wchar_t ByteBuffer::getChar() noexcept {
	wchar_t val = *((short*)(this->data->getRoot() + this->pos));

	this->pos += sizeof(int16_t);

	return (wchar_t)val;
}

wchar_t ByteBuffer::getChar(int position) noexcept {
	int16_t val = *((int16_t*)(this->data->getRoot() + position));

	return (wchar_t)val;
}

int16_t ByteBuffer::getShort() noexcept {
	int16_t val = *((int16_t*)(this->data->getRoot() + this->pos));
	this->pos += sizeof(int16_t);

	return val;
}

int16_t ByteBuffer::getShort(int position) noexcept {
	int16_t val = *((int16_t*)(this->data->getRoot() + position));

	return val;
}

const uint8_t* ByteBuffer::array() const noexcept {
	return data->getRoot();
}

} /* namespace alinous */
