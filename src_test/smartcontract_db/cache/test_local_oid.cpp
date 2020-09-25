/*
 * test_local_oid.cpp
 *
 *  Created on: 2020/09/25
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"

#include "vm/VirtualMachine.h"

#include "table_record_local/LocalOidFactory.h"
#include "table_record_local/LocalCdbOid.h"

TEST_GROUP(TestLocalOidGroup) {
	TEST_SETUP() {
		env->setup();
	}
	TEST_TEARDOWN() {
		env->teardown();
	}
};

TEST(TestLocalOidGroup, case01){
	LocalOidFactory factory;

	LocalCdbOid* oid = factory.createLocalOid(); __STP(oid);

	CHECK(oid->getTypeCode() == LocalCdbOid::CDB_LOCAL_OID);
	CHECK(oid->isLocal());
}

TEST(TestLocalOidGroup, case02){
	LocalOidFactory factory;

	LocalCdbOid* oid = factory.createLocalOid(); __STP(oid);
	LocalCdbOid* oid2 = new LocalCdbOid(*oid); __STP(oid2);

	CHECK(oid->equals(oid2));
}

TEST(TestLocalOidGroup, case03){
	LocalOidFactory factory;

	LocalCdbOid* oid = factory.createLocalOid(); __STP(oid);
	CdbOid oid2(oid->getOid());

	CHECK(!oid->equals(&oid2));

	LocalCdbOid::ValueCompare comp;
	int diff = comp(oid, &oid2);

	CHECK(diff > 0);
}
