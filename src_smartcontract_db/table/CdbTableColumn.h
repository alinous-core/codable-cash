/*
 * CdbTableColumn.h
 *
 *  Created on: 2020/05/13
 *      Author: iizuka
 */

#ifndef TABLE_CDBTABLECOLUMN_H_
#define TABLE_CDBTABLECOLUMN_H_
#include <cstdint>

#include "engine/CdbBinaryObject.h"

namespace codablecash {

class CdbOid;

class CdbTableColumn : public CdbBinaryObject {
public:
	explicit CdbTableColumn(uint64_t oid);
	virtual ~CdbTableColumn();

	const CdbOid* getOid() const noexcept;
private:
	CdbOid* oid;
};

} /* namespace codablecash */

#endif /* TABLE_CDBTABLECOLUMN_H_ */
