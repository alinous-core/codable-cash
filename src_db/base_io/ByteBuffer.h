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
	ByteBuffer(const int length) noexcept;
public:
	static ByteBuffer* allocate(const int capacity) noexcept;
	virtual ~ByteBuffer() noexcept;

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
	ByteBuffer* putChar(wchar_t value) noexcept;
	ByteBuffer* putChar(int position, wchar_t value) noexcept;
	ByteBuffer* putShort(short value) noexcept;
	ByteBuffer* putShort(int position, short value) noexcept;
	ByteBuffer* putInt(int32_t value) noexcept;
	ByteBuffer* putInt(int32_t position, int value) noexcept;
	ByteBuffer* putLong(int position, int64_t value) noexcept;
	ByteBuffer* putLong(int64_t value) noexcept;
	ByteBuffer* putFloat(float value) noexcept;
	ByteBuffer* putFloat(int position, float value) noexcept;
	ByteBuffer* putDouble(double value) noexcept;
	ByteBuffer* putDouble(int position, double value) noexcept;
	uint64_t getLong() noexcept;
	uint64_t getLong(int position) noexcept;
	double getDouble() noexcept;
	double getDouble(int position) noexcept;
	float getFloat() noexcept;
	float getFloat(int position) noexcept;
	int32_t getInt() noexcept;
	int32_t getInt(int position) noexcept;
	wchar_t getChar() noexcept;
	wchar_t getChar(int position) noexcept;
	int16_t getShort() noexcept;
	int16_t getShort(int position) noexcept;


private:
    int pos;
    int lim;
    int cap;
    RawArrayPrimitive<uint8_t>* data;
};

} /* namespace alinous */

#endif /* BASE_IO_BYTEBUFFER_H_ */
