/*
 * LongRangeIterator.h
 *
 *  Created on: 2018/05/18
 *      Author: iizuka
 */

#ifndef FILESTORE_LONGRANGEITERATOR_H_
#define FILESTORE_LONGRANGEITERATOR_H_

#include <cstdint>

namespace alinous {

class LongRangeList;

class LongRangeIterator {
public:
	LongRangeIterator(const LongRangeIterator& base) = delete;
	explicit LongRangeIterator(LongRangeList* list) noexcept;
	virtual ~LongRangeIterator() noexcept;

	bool hasNext() noexcept;
	uint64_t next() noexcept;
private:
	LongRangeList* list;
	int listIndex;
	int current;
};

} /* namespace alinous */

#endif /* FILESTORE_LONGRANGEITERATOR_H_ */
