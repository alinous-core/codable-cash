/*
 * ColumnIndexMatcher.h
 *
 *  Created on: 2020/08/16
 *      Author: iizuka
 */

#ifndef TABLE_COLUMNINDEXMATCHER_H_
#define TABLE_COLUMNINDEXMATCHER_H_

#include "base/ArrayList.h"

using namespace alinous;

namespace codablecash {

class CdbTableIndex;
class CdbOid;

class ColumnIndexMatcher {
public:
	explicit ColumnIndexMatcher(CdbTableIndex* idx);
	virtual ~ColumnIndexMatcher();

	void doMatch(const ArrayList<const CdbOid>* oidlist) noexcept;

	CdbTableIndex* getIdx() const noexcept {
		return idx;
	}

	int getLength() const noexcept {
		return length;
	}

private:
	CdbTableIndex* idx;
	int length;
};

} /* namespace codablecash */

#endif /* TABLE_COLUMNINDEXMATCHER_H_ */
