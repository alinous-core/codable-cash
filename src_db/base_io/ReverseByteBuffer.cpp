/*
 * ReverseByteBuffer.cpp
 *
 *  Created on: 2018/11/02
 *      Author: iizuka
 */

#include "base_io/ReverseByteBuffer.h"
#include "base/RawArrayPrimitive.h"

namespace alinous {


ReverseByteBuffer::ReverseByteBuffer(const int length) noexcept : ByteBuffer(length){
}
/*
ReverseByteBuffer::ReverseByteBuffer(const uint8_t* buffer, int length) : ByteBuffer(buffer, length) {
}
*/
ReverseByteBuffer::~ReverseByteBuffer() noexcept {
}


ByteBuffer* ReverseByteBuffer::putChar(wchar_t value) noexcept {
	//data->set(this->pos++, value & 0xFF);
	//data->set(this->pos++, (value >> 1) & 0xFF);

	uint16_t sh = (uint16_t)value;
	char* bytes = (char*)&sh;

	data->set(this->pos++, bytes[1]);
	data->set(this->pos++, bytes[0]);

	return this;
}

ByteBuffer* ReverseByteBuffer::putChar(int position, wchar_t value) noexcept {
	//data->set(this->pos++, value & 0xFF);
	//data->set(this->pos++, (value >> 1) & 0xFF);

	uint16_t sh = (uint16_t)value;
	char* bytes = (char*)&sh;

	data->set(position++, bytes[1]);
	data->set(position++, bytes[0]);

	return this;
}

ByteBuffer* ReverseByteBuffer::putShort(short value) noexcept {
	char* bytes = (char*)&value;

	data->set(this->pos++, bytes[1]);
	data->set(this->pos++, bytes[0]);

	return this;
}

ByteBuffer* ReverseByteBuffer::putShort(int position, short value) noexcept {
	char* bytes = (char*)&value;

	this->pos = position;
	data->set(this->pos++, bytes[1]);
	data->set(this->pos++, bytes[0]);

	return this;
}

ByteBuffer* ReverseByteBuffer::putInt(int32_t value) noexcept {
	char* bytes = (char*)&value;

	data->set(this->pos++, bytes[3]);
	data->set(this->pos++, bytes[2]);
	data->set(this->pos++, bytes[1]);
	data->set(this->pos++, bytes[0]);

	return this;
}

ByteBuffer* ReverseByteBuffer::putInt(int32_t position, int value) noexcept {
	char* bytes = (char*)&value;

	this->pos = position;
	data->set(this->pos++, bytes[3]);
	data->set(this->pos++, bytes[2]);
	data->set(this->pos++, bytes[1]);
	data->set(this->pos++, bytes[0]);

	return this;
}

ByteBuffer* ReverseByteBuffer::putLong(int64_t value) noexcept {
	char* bytes = (char*)&value;

	data->set(this->pos++, bytes[7]);
	data->set(this->pos++, bytes[6]);
	data->set(this->pos++, bytes[5]);
	data->set(this->pos++, bytes[4]);
	data->set(this->pos++, bytes[3]);
	data->set(this->pos++, bytes[2]);
	data->set(this->pos++, bytes[1]);
	data->set(this->pos++, bytes[0]);

	return this;
}

ByteBuffer* ReverseByteBuffer::putLong(int position, int64_t value) noexcept {
	char* bytes = (char*)&value;

	this->pos = position;
	data->set(this->pos++, bytes[7]);
	data->set(this->pos++, bytes[6]);
	data->set(this->pos++, bytes[5]);
	data->set(this->pos++, bytes[4]);
	data->set(this->pos++, bytes[3]);
	data->set(this->pos++, bytes[2]);
	data->set(this->pos++, bytes[1]);
	data->set(this->pos++, bytes[0]);

	return this;
}

ByteBuffer* ReverseByteBuffer::putFloat(float value) noexcept {
	char* bytes = (char*)&value;

	data->set(this->pos++, bytes[3]);
	data->set(this->pos++, bytes[2]);
	data->set(this->pos++, bytes[1]);
	data->set(this->pos++, bytes[0]);

	return this;
}

ByteBuffer* ReverseByteBuffer::putFloat(int position, float value) noexcept {
	char* bytes = (char*)&value;

	this->pos = position;
	data->set(this->pos++, bytes[3]);
	data->set(this->pos++, bytes[2]);
	data->set(this->pos++, bytes[1]);
	data->set(this->pos++, bytes[0]);

	return this;
}

ByteBuffer* ReverseByteBuffer::putDouble(double value) noexcept {
	char* bytes = (char*)&value;

	data->set(this->pos++, bytes[7]);
	data->set(this->pos++, bytes[6]);
	data->set(this->pos++, bytes[5]);
	data->set(this->pos++, bytes[4]);
	data->set(this->pos++, bytes[3]);
	data->set(this->pos++, bytes[2]);
	data->set(this->pos++, bytes[1]);
	data->set(this->pos++, bytes[0]);

	return this;
}

ByteBuffer* ReverseByteBuffer::putDouble(int position, double value) noexcept {
	char* bytes = (char*)&value;

	this->pos = position;
	data->set(this->pos++, bytes[7]);
	data->set(this->pos++, bytes[6]);
	data->set(this->pos++, bytes[5]);
	data->set(this->pos++, bytes[4]);
	data->set(this->pos++, bytes[3]);
	data->set(this->pos++, bytes[2]);
	data->set(this->pos++, bytes[1]);
	data->set(this->pos++, bytes[0]);

	return this;
}

int64_t ReverseByteBuffer::getLong() noexcept {
	uint8_t* ptr = this->data->getRoot() + this->pos;
	uint8_t dest[8]{};

	dest[0] = ptr[7];
	dest[1] = ptr[6];
	dest[2] = ptr[5];
	dest[3] = ptr[4];
	dest[4] = ptr[3];
	dest[5] = ptr[2];
	dest[6] = ptr[1];
	dest[7] = ptr[0];

	this->pos += sizeof(uint64_t);

	return *(reinterpret_cast<uint64_t*>((void*)dest));
}

int64_t ReverseByteBuffer::getLong(int position) noexcept {
	uint8_t* ptr = this->data->getRoot() + position;
	uint8_t dest[8]{};

	dest[0] = ptr[7];
	dest[1] = ptr[6];
	dest[2] = ptr[5];
	dest[3] = ptr[4];
	dest[4] = ptr[3];
	dest[5] = ptr[2];
	dest[6] = ptr[1];
	dest[7] = ptr[0];

	this->pos = position + sizeof(uint64_t);

	return *(reinterpret_cast<uint64_t*>((void*)dest));
}

double ReverseByteBuffer::getDouble() noexcept {
	uint8_t* ptr = this->data->getRoot() + this->pos;
	uint8_t dest[8]{};

	dest[0] = ptr[7];
	dest[1] = ptr[6];
	dest[2] = ptr[5];
	dest[3] = ptr[4];
	dest[4] = ptr[3];
	dest[5] = ptr[2];
	dest[6] = ptr[1];
	dest[7] = ptr[0];

	this->pos += sizeof(double);

	return *(reinterpret_cast<double*>((void*)dest));
}

double ReverseByteBuffer::getDouble(int position) noexcept {
	uint8_t* ptr = this->data->getRoot() + position;
	uint8_t dest[8]{};

	dest[0] = ptr[7];
	dest[1] = ptr[6];
	dest[2] = ptr[5];
	dest[3] = ptr[4];
	dest[4] = ptr[3];
	dest[5] = ptr[2];
	dest[6] = ptr[1];
	dest[7] = ptr[0];

	this->pos = position + sizeof(double);

	return *(reinterpret_cast<double*>((void*)dest));
}

float ReverseByteBuffer::getFloat() noexcept {
	uint8_t* ptr = this->data->getRoot() + this->pos;
	uint8_t dest[4]{};

	dest[0] = ptr[3];
	dest[1] = ptr[2];
	dest[2] = ptr[1];
	dest[3] = ptr[0];

	this->pos += sizeof(float);

	return *(reinterpret_cast<float*>((void*)dest));
}

float ReverseByteBuffer::getFloat(int position) noexcept {
	uint8_t* ptr = this->data->getRoot() + position;
	uint8_t dest[4]{};

	dest[0] = ptr[3];
	dest[1] = ptr[2];
	dest[2] = ptr[1];
	dest[3] = ptr[0];

	this->pos = position + sizeof(float);

	return *(reinterpret_cast<float*>((void*)dest));
}

int32_t ReverseByteBuffer::getInt() noexcept {
	char out[4]{};
	char* bytes = (char*)(this->data->getRoot() + this->pos);

	out[0] = bytes[3];
	out[1] = bytes[2];
	out[2] = bytes[1];
	out[3] = bytes[0];

	wchar_t val = *((int32_t*)out);
	this->pos += sizeof(int32_t);

	return val;
}

int32_t ReverseByteBuffer::getInt(int position) noexcept {
	char out[4]{};
	char* bytes = (char*)(this->data->getRoot() + position);

	out[0] = bytes[3];
	out[1] = bytes[2];
	out[2] = bytes[1];
	out[3] = bytes[0];

	wchar_t val = *((int32_t*)out);
	this->pos = position + sizeof(int16_t);

	return val;
}

wchar_t ReverseByteBuffer::getChar() noexcept {
	char out[2]{};
	char* bytes = (char*)(this->data->getRoot() + this->pos);

	out[0] = bytes[1];
	out[1] = bytes[0];

	wchar_t val = *((short*)out);
	this->pos += sizeof(int16_t);

	return val;
}

wchar_t ReverseByteBuffer::getChar(int position) noexcept {
	char out[2]{};
	char* bytes = (char*)(this->data->getRoot() + position);

	out[0] = bytes[1];
	out[1] = bytes[0];

	wchar_t val = *((short*)out);
	this->pos = position + sizeof(int16_t);

	return val;
}

int16_t ReverseByteBuffer::getShort() noexcept {
	char out[2]{};
	char* bytes = (char*)(this->data->getRoot() + this->pos);

	out[0] = bytes[1];
	out[1] = bytes[0];

	short val = *((short*)out);
	this->pos += sizeof(int16_t);

	return val;
}

int16_t ReverseByteBuffer::getShort(int position) noexcept {
	char out[2]{};
	char* bytes = (char*)(this->data->getRoot() + position);

	out[0] = bytes[1];
	out[1] = bytes[0];

	short val = *((short*)out);
	this->pos = position + sizeof(int16_t);

	return val;
}

} /* namespace alinous */
