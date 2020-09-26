/*
 * LocalOidFactory.cpp
 *
 *  Created on: 2020/09/25
 *      Author: iizuka
 */

#include "table_record_local/LocalOidFactory.h"

#include "table_record_local/LocalCdbOid.h"

namespace codablecash {

LocalOidFactory::LocalOidFactory() {
	this->serial = 1;
}

LocalOidFactory::~LocalOidFactory() {

}

LocalCdbOid* LocalOidFactory::createLocalOid() noexcept {
	return new LocalCdbOid(this->serial++);
}

} /* namespace codablecash */
