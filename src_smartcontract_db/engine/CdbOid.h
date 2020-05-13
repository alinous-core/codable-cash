/*
 * CdbOid.h
 *
 *  Created on: 2020/05/13
 *      Author: iizuka
 */

#ifndef ENGINE_CDBOID_H_
#define ENGINE_CDBOID_H_

#include <cstdint>

namespace codablecash {

class CdbOid {
public:
	explicit CdbOid(uint64_t oid);
	virtual ~CdbOid();

private:
	uint64_t oid;
};

} /* namespace codablecash */

#endif /* ENGINE_CDBOID_H_ */
