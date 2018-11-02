/*
 * ReverseByteBuffer.h
 *
 *  Created on: 2018/11/02
 *      Author: iizuka
 */

#ifndef BASE_IO_REVERSEBYTEBUFFER_H_
#define BASE_IO_REVERSEBYTEBUFFER_H_

#include "ByteBuffer.h"

namespace alinous {

class ReverseByteBuffer : public ByteBuffer {
public:
	ReverseByteBuffer(const ReverseByteBuffer& base) = delete;
	explicit ReverseByteBuffer(const int length) noexcept;
	//ReverseByteBuffer(const uint8_t* buffer, int length);

	virtual ~ReverseByteBuffer() noexcept;

	virtual ByteBuffer* putChar(wchar_t value) noexcept;
	virtual ByteBuffer* putChar(int position, wchar_t value) noexcept;
	virtual ByteBuffer* putShort(short value) noexcept;
	virtual ByteBuffer* putShort(int position, short value) noexcept;
	virtual ByteBuffer* putInt(int32_t value) noexcept;
	virtual ByteBuffer* putInt(int32_t position, int value) noexcept;
	virtual ByteBuffer* putLong(int position, int64_t value) noexcept;
	virtual ByteBuffer* putLong(int64_t value) noexcept;
	virtual ByteBuffer* putFloat(float value) noexcept;
	virtual ByteBuffer* putFloat(int position, float value) noexcept;
	virtual ByteBuffer* putDouble(double value) noexcept;
	virtual ByteBuffer* putDouble(int position, double value) noexcept;
	virtual uint64_t getLong() noexcept;
	virtual uint64_t getLong(int position) noexcept;
	virtual double getDouble() noexcept;
	virtual double getDouble(int position) noexcept;
	virtual float getFloat() noexcept;
	virtual float getFloat(int position) noexcept;
	virtual int32_t getInt() noexcept;
	virtual int32_t getInt(int position) noexcept;
	virtual wchar_t getChar() noexcept;
	virtual wchar_t getChar(int position) noexcept;
	virtual int16_t getShort() noexcept;
	virtual int16_t getShort(int position) noexcept;
};

} /* namespace alinous */

#endif /* BASE_IO_REVERSEBYTEBUFFER_H_ */
