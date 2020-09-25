/*
 * LocalCdbOid.h
 *
 *  Created on: 2020/09/25
 *      Author: iizuka
 */

#ifndef TABLE_RECORD_LOCAL_LOCALCDBOID_H_
#define TABLE_RECORD_LOCAL_LOCALCDBOID_H_

#include "engine/CdbOid.h"

namespace codablecash {

class LocalCdbOid: public CdbOid {
public:
	LocalCdbOid(const LocalCdbOid& inst);
	LocalCdbOid(uint64_t oid);
	virtual ~LocalCdbOid();
};

} /* namespace codablecash */

#endif /* TABLE_RECORD_LOCAL_LOCALCDBOID_H_ */
