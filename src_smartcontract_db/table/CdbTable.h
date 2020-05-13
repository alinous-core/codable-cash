/*
 * CdbTable.h
 *
 *  Created on: 2020/05/13
 *      Author: iizuka
 */

#ifndef TABLE_CDBTABLE_H_
#define TABLE_CDBTABLE_H_

#include <cstdint>

#include "base/ArrayList.h"
#include "base/HashMap.h"

using namespace alinous;

namespace codablecash {

class CdbTableColumn;
class CdbOid;

class CdbTable {
public:
	explicit CdbTable(uint64_t oid);
	virtual ~CdbTable();

	void addColumn(CdbTableColumn* col) noexcept;
private:
	CdbOid* oid;
	ArrayList<CdbTableColumn>* columns;
	HashMap<CdbOid, CdbTableColumn>* columnMap;

};

} /* namespace codablecash */

#endif /* TABLE_CDBTABLE_H_ */
