/*
 * LocalOidFactory.cpp
 *
 *  Created on: 2020/09/25
 *      Author: iizuka
 */

#include "schema_table/record/table_record_local/LocalOidFactory.h"
#include "schema_table/record/table_record_local/LocalCdbOid.h"

#include "schema_table/record/table_record_value/VmInstanceValueConverter.h"

#include "base_thread/SysMutex.h"
#include "base_thread/StackUnlocker.h"

namespace codablecash {

LocalOidFactory::LocalOidFactory() {
	this->serial = 1;
}

LocalOidFactory::~LocalOidFactory() {

}

LocalCdbOid* LocalOidFactory::createLocalOid() noexcept {
	SysMutex mutex;
	StackUnlocker unlocker(&mutex);

	return new LocalCdbOid(this->serial++);
}

} /* namespace codablecash */
