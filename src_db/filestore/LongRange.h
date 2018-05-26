/*
 * LongRange.h
 *
 *  Created on: 2018/05/18
 *      Author: iizuka
 */

#ifndef FILESTORE_LONGRANGE_H_
#define FILESTORE_LONGRANGE_H_

#include <inttypes.h>

namespace alinous {

class LongRange {
public:
	LongRange(const LongRange& base) = delete;
	explicit LongRange(const LongRange* base) noexcept;
	LongRange(uint64_t min, uint64_t max) noexcept;
	virtual ~LongRange();

	int compare(uint64_t value) const noexcept;
	int includeType(uint64_t value) const noexcept;

	uint64_t width() noexcept ;
	bool hasNext(uint64_t value) const noexcept ;
	uint64_t getMin() const noexcept ;
	void setMin(uint64_t min) noexcept ;
	uint64_t getMax() const noexcept ;
	void setMax(uint64_t max) noexcept ;

private:
	uint64_t min;
	uint64_t max;
};

} /* namespace alinous */

#endif /* FILESTORE_LONGRANGE_H_ */
