/*
 * ByteBuffer.h
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */

#ifndef BASE_IO_BYTEBUFFER_H_
#define BASE_IO_BYTEBUFFER_H_

#include <stdint.h>

namespace alinous {

template <typename T> class RawArrayPrimitive;

class ByteBuffer {
protected:
	friend class UnicodeString;
	ByteBuffer(const ByteBuffer& base) = delete;
	explicit ByteBuffer(const int length) noexcept;
	ByteBuffer(const uint8_t* buffer, int length);
public:
	static ByteBuffer* allocate(const int capacity) noexcept;
	static ByteBuffer* wrap(const uint8_t* buffer, int length);

	virtual ~ByteBuffer() noexcept;

	ByteBuffer* clear() noexcept;
	inline bool hasRemaining() noexcept {
    	return (pos < lim);
    }
	int remaining() const noexcept;
	int position() const noexcept;
	ByteBuffer* position(const int newPosition) noexcept;
	int limit() noexcept;
	ByteBuffer* limit(const int limit) noexcept;
	int capacity() noexcept;
	char get() noexcept;
	char get(const int index) const noexcept;
	ByteBuffer* get(uint8_t* dest, int length) noexcept(false);
	ByteBuffer* get(uint8_t* dest, int off, int len) noexcept(false);

	ByteBuffer* put(char b) noexcept;
	ByteBuffer* put(int index, uint8_t b) noexcept;
	ByteBuffer* put(const uint8_t* src, int length) noexcept(false);
	ByteBuffer* put(const uint8_t* src, int off, int len) noexcept(false);
	ByteBuffer* put(ByteBuffer* src) noexcept;
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

	const uint8_t* array() const noexcept;
protected:
    int pos;
    int lim;
    int cap;
    RawArrayPrimitive<uint8_t>* data;
};

} /* namespace alinous */

#endif /* BASE_IO_BYTEBUFFER_H_ */
