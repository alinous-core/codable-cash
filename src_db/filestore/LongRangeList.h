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

class LongRangeList {
public:
	LongRangeList();
	virtual ~LongRangeList();
public:
	void addRange(int64_t value) noexcept ;
	void removeRange(int64_t value) noexcept ;
	LongRange* get(int listIndex) const noexcept ;
	bool isEmpty() const noexcept ;
	int size() const noexcept ;
	LongRangeIterator* iterator() const noexcept ;
private:
	void spiltByRemove(LongRange* range, int64_t value, int pos) noexcept ;
	void insertRange(int pos, LongRange* newRange) noexcept ;
	void insertOrExtend(int pos, int64_t value) noexcept ;
	void insertRange(int pos, int64_t value) noexcept ;
	int indexOfInsert(int64_t value) const noexcept ;
private:
	ArrayList<LongRange>* list;
};

} /* namespace alinous */

#endif /* FILESTORE_LONGRANGELIST_H_ */
