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
	static ByteBuffer* allocateWithEndian(const int capacity, bool bigEndian) noexcept;
	static ByteBuffer* wrapWithEndian(const uint8_t* buffer, int length, bool bigEndian) noexcept;

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
	char get() noexcept(false);
	char get(const int index) const noexcept(false);
	ByteBuffer* get(uint8_t* dest, int length) noexcept(false);
	ByteBuffer* get(uint8_t* dest, int off, int len) noexcept(false);

	ByteBuffer* put(const char b) noexcept(false);
	ByteBuffer* put(int index, const uint8_t b) noexcept(false);
	ByteBuffer* put(const uint8_t* src, int length) noexcept(false);
	ByteBuffer* put(const uint8_t* src, int off, int len) noexcept(false);
	ByteBuffer* put(ByteBuffer* src) noexcept(false);
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

	const uint8_t* array() const noexcept;
protected:
    int pos;
    int lim;
    int cap;
    RawArrayPrimitive<uint8_t>* data;
};

} /* namespace alinous */

#endif /* BASE_IO_BYTEBUFFER_H_ */
