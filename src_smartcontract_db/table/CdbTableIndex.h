/*
 * CdbTableIndex.h
 *
 *  Created on: 2020/05/13
 *      Author: iizuka
 */

#ifndef TABLE_CDBTABLEINDEX_H_
#define TABLE_CDBTABLEINDEX_H_
#include <cstdint>

#include "base/ArrayList.h"
#include "base/HashMap.h"

using namespace alinous;

namespace codablecash {

class CdbOid;
class CdbTableColumn;

class CdbTableIndex {
public:
	explicit CdbTableIndex(uint64_t oid);
	virtual ~CdbTableIndex();

	void addColumn(CdbTableColumn* col) noexcept;

	void setPrimaryKey(bool bl);
	bool isPrimaryKey() const noexcept;
private:
	CdbOid* oid;
	bool primary;

	ArrayList<CdbTableColumn>* columns;
	HashMap<CdbOid, CdbTableColumn>* columnMap;
};

} /* namespace codablecash */

#endif /* TABLE_CDBTABLEINDEX_H_ */
