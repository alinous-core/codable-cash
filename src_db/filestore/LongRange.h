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
	LongRange(int64_t min, int64_t max);
	virtual ~LongRange();

	int64_t width() noexcept ;
	bool hasNext(int64_t value) const noexcept ;
	int64_t getMin() const noexcept ;
	void setMin(int64_t min) noexcept ;
	int64_t getMax() const noexcept ;
	void setMax(int64_t max) noexcept ;
private:
private:
	int64_t min;
	int64_t max;
};

} /* namespace alinous */

#endif /* FILESTORE_LONGRANGE_H_ */
