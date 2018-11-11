/*
 * LongRangeList.h
 *
 *  Created on: 2018/05/18
 *      Author: iizuka
 */

#ifndef FILESTORE_LONGRANGELIST_H_
#define FILESTORE_LONGRANGELIST_H_

#include "base/ArrayList.h"
#include <inttypes.h>

namespace alinous {

class ByteBuffer;

class LongRange;
class LongRangeIterator;
class LongRangeHitStatus;

class LongRangeList {
public:
	LongRangeList(const LongRangeList& base) = delete;
	LongRangeList();
	virtual ~LongRangeList();
public:
	void addRange(int64_t value) noexcept ;
	void addRange(int64_t min, int64_t max) noexcept ;
	void removeRange(int64_t min, int64_t max) noexcept;
	void removeRange(const LongRange* range) noexcept;

	bool isEmpty() const noexcept ;
	int size() const noexcept ;
	LongRange* get(int listIndex) const noexcept;
	LongRangeIterator* iterator() noexcept;

	int binarySize() noexcept;
	void toBinary(ByteBuffer* buff) noexcept;
	void fromBinary(ByteBuffer* buff) noexcept;

	void assertList() const;


private:
	bool needSplit(LongRangeHitStatus* minStatus, LongRangeHitStatus* maxStatus, const LongRange* range) noexcept;
	void removeInclusion(const LongRange* range) const noexcept;
	void insertRange(int pos, LongRange* range) noexcept;
	LongRangeHitStatus* hitStatus(uint64_t value, const LongRange* range, bool findHigher) const noexcept;
private:
	ArrayList<LongRange>* list;
};

} /* namespace alinous */

#endif /* FILESTORE_LONGRANGELIST_H_ */
