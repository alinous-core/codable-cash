/*
 * ColumnIndexMatcher.h
 *
 *  Created on: 2020/08/16
 *      Author: iizuka
 */

#ifndef TABLE_COLUMNINDEXMATCHER_H_
#define TABLE_COLUMNINDEXMATCHER_H_

namespace codablecash {

class CdbTableIndex;

class ColumnIndexMatcher {
public:
	explicit ColumnIndexMatcher(CdbTableIndex* idx);
	virtual ~ColumnIndexMatcher();



	CdbTableIndex* getIdx() const {
		return idx;
	}

private:
	CdbTableIndex* idx;
};

} /* namespace codablecash */

#endif /* TABLE_COLUMNINDEXMATCHER_H_ */
