/*
 * RawBitSet.h
 *
 *  Created on: 2018/04/14
 *      Author: iizuka
 */

#ifndef BASE_RAWBITSET_H_
#define BASE_RAWBITSET_H_

#include <cstdint>

namespace alinous {

class RawBitSet {
public:
	constexpr static const uint32_t OFFSET{6};
	constexpr static const uint32_t ELM_SIZE{1 << OFFSET};
	constexpr static const uint32_t RIGHT_BITS{ELM_SIZE - 1};
	constexpr static const uint64_t TWO_N_ARRAY[64]
		{0x1L, 0x2L, 0x4L, 0x8L, 0x10L, 0x20L, 0x40L, 0x80L, 0x100L, 0x200L, 0x400L, 0x800L, 0x1000L, 0x2000L, 0x4000L, 0x8000L, 0x10000L, 0x20000L, 0x40000L, 0x80000L, 0x100000L, 0x200000L, 0x400000L, 0x800000L, 0x1000000L, 0x2000000L, 0x4000000L, 0x8000000L, 0x10000000L, 0x20000000L, 0x40000000L, 0x80000000L, 0x100000000L, 0x200000000L, 0x400000000L, 0x800000000L, 0x1000000000L, 0x2000000000L, 0x4000000000L, 0x8000000000L, 0x10000000000L, 0x20000000000L, 0x40000000000L, 0x80000000000L, 0x100000000000L, 0x200000000000L, 0x400000000000L, 0x800000000000L, 0x1000000000000L, 0x2000000000000L, 0x4000000000000L, 0x8000000000000L, 0x10000000000000L, 0x20000000000000L, 0x40000000000000L, 0x80000000000000L, 0x100000000000000L, 0x200000000000000L, 0x400000000000000L, 0x800000000000000L, 0x1000000000000000L, 0x2000000000000000L, 0x4000000000000000L, 0x8000000000000000L};

	class BitsetArray {
	public:
		int length;
		uint64_t* buff;
		BitsetArray(const BitsetArray& base) = delete;
		explicit BitsetArray(int numBits) noexcept {
			this->length = numBits;
			this->buff = new uint64_t[numBits]{};
		}
		~BitsetArray() noexcept {
			delete [] buff;
		}

		void set(uint64_t value, int index) throw() {
			this->buff[index] = value;
		}

		void growLength(uint32_t len) noexcept;

		uint64_t operator[](const int pos) const throw() {
			return buff[pos];
		}
		uint64_t operator[](const uint32_t pos) const throw() {
			return buff[pos];
		}
	};

	RawBitSet(const RawBitSet& base) = delete;
	explicit RawBitSet(uint32_t nbits) noexcept;
	virtual ~RawBitSet();

	bool get(uint32_t pos) noexcept ;
	void set(uint32_t pos) noexcept ;
	void clear(uint32_t pos) noexcept ;
	void needClear() noexcept ;
	int nextSetBit(const uint32_t pos) const noexcept ;
	void clear() noexcept ;

private:
	BitsetArray* bits;
	bool _needClear;
	uint32_t actualArrayLength;
	bool isLengthActual;
};

} /* namespace alinous */

#endif /* BASE_RAWBITSET_H_ */
