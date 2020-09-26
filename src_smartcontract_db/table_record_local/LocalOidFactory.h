/*
 * LocalOidFactory.h
 *
 *  Created on: 2020/09/25
 *      Author: iizuka
 */

#ifndef TABLE_RECORD_LOCAL_LOCALOIDFACTORY_H_
#define TABLE_RECORD_LOCAL_LOCALOIDFACTORY_H_

#include <cstdint>

namespace codablecash {

class LocalCdbOid;

class LocalOidFactory {
public:
	LocalOidFactory();
	virtual ~LocalOidFactory();

	LocalCdbOid* createLocalOid() noexcept;

private:
	uint64_t serial;
};

} /* namespace codablecash */

#endif /* TABLE_RECORD_LOCAL_LOCALOIDFACTORY_H_ */
