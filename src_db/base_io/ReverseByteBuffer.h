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
	ReverseByteBuffer(const uint8_t* buffer, int length);

	virtual ~ReverseByteBuffer() noexcept;

	static ByteBuffer* wrap(const uint8_t* buffer, int length);

	virtual ByteBuffer* putChar(wchar_t value) noexcept(false);
	virtual ByteBuffer* putChar(int position, wchar_t value) noexcept(false);
	virtual ByteBuffer* putShort(short value) noexcept(false);
	virtual ByteBuffer* putShort(int position, short value) noexcept(false);
	virtual ByteBuffer* putInt(int32_t value) noexcept(false);
	virtual ByteBuffer* putInt(int32_t position, int value) noexcept(false);
	virtual ByteBuffer* putLong(int position, int64_t value) noexcept(false);
	virtual ByteBuffer* putLong(int64_t value) noexcept(false);
	virtual ByteBuffer* putFloat(float value) noexcept(false);
	virtual ByteBuffer* putFloat(int position, float value) noexcept(false);
	virtual ByteBuffer* putDouble(double value) noexcept(false);
	virtual ByteBuffer* putDouble(int position, double value) noexcept(false);
	virtual int64_t getLong() noexcept(false);
	virtual int64_t getLong(int position) noexcept(false);
	virtual double getDouble() noexcept(false);
	virtual double getDouble(int position) noexcept(false);
	virtual float getFloat() noexcept(false);
	virtual float getFloat(int position) noexcept(false);
	virtual int32_t getInt() noexcept(false);
	virtual int32_t getInt(int position) noexcept(false);
	virtual wchar_t getChar() noexcept(false);
	virtual wchar_t getChar(int position) noexcept(false);
	virtual int16_t getShort() noexcept(false);
	virtual int16_t getShort(int position) noexcept(false);

	virtual ByteBuffer* clone() const noexcept(false);
};

} /* namespace alinous */

#endif /* BASE_IO_REVERSEBYTEBUFFER_H_ */
