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

class LongRange;
class LongRangeIterator;
class LongRangeHitStatus;

class LongRangeList {
public:
	LongRangeList();
	virtual ~LongRangeList();
public:
	void addRange(int64_t value) noexcept ;
	void addRange(int64_t min, int64_t max) noexcept ;

	bool isEmpty() const noexcept ;
	int size() const noexcept ;
	LongRange* get(int listIndex) const noexcept;
	LongRangeIterator* iterator() noexcept;

/*
	void removeRange(int64_t value) noexcept ;
	 ;
*/
private:
	LongRangeHitStatus* hitStatus(uint64_t value, const LongRange* range, bool findHigher) const noexcept;
private:
	ArrayList<LongRange>* list;
};

} /* namespace alinous */

#endif /* FILESTORE_LONGRANGELIST_H_ */
