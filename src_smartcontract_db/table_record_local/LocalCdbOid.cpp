/*
 * LocalCdbOid.cpp
 *
 *  Created on: 2020/09/25
 *      Author: iizuka
 */

#include "table_record_local/LocalCdbOid.h"

namespace codablecash {

LocalCdbOid::LocalCdbOid(const LocalCdbOid& inst) : CdbOid(inst) {
}

LocalCdbOid::LocalCdbOid(uint64_t oid) : CdbOid(oid) {

}

LocalCdbOid::~LocalCdbOid() {

}

} /* namespace codablecash */
