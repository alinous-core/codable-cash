/*
 * test_local_oid.cpp
 *
 *  Created on: 2020/09/25
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"

#include "vm/VirtualMachine.h"

#include "schema_table/record/table_record_local/LocalOidFactory.h"
#include "schema_table/record/table_record_local/LocalCdbOid.h"
#include "schema_table/record/table_record_value/VmInstanceValueConverter.h"

#include "base_io/ByteBuffer.h"

#include "engine/CdbException.h"

#include "schema_table/record/table_record_key/CdbOidKey.h"


TEST_GROUP(TestLocalOidGroup) {
	TEST_SETUP() {
	}
	TEST_TEARDOWN() {
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
	CdbOid oid2(oid->getOidValue());

	CHECK(!oid->equals(&oid2));

	LocalCdbOid::ValueCompare comp;
	int diff = comp(oid, &oid2);

	CHECK(diff > 0);
}

static bool checkBinary(ByteBuffer* buff);

bool checkBinary(ByteBuffer* buff){
	int lastSize = buff->capacity();

	buff->position(0);
	CdbOid* element = CdbOid::fromBinary(buff); __STP(element);

	int size = element->binarySize();
	if(lastSize != size){
		return false;
	}

	ByteBuffer* buff2 = ByteBuffer::allocateWithEndian(size, true); __STP(buff2);
	element->toBinary(buff2);

	if(buff2->position() != size){
		return false;
	}

	return Mem::memcmp(buff->array(), buff2->array(), size) == 0;
}

TEST(TestLocalOidGroup, binary01){
	LocalOidFactory factory;

	LocalCdbOid* oid = factory.createLocalOid(); __STP(oid);

	int size = oid->binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);

	oid->toBinary(buff);

	bool result = checkBinary(buff);
	CHECK(result)
}

TEST(TestLocalOidGroup, binary02){
	CdbOid* oid = new CdbOid(1); __STP(oid);

	int size = oid->binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);

	oid->toBinary(buff);

	bool result = checkBinary(buff);
	CHECK(result)
}

TEST(TestLocalOidGroup, binary03){
	LocalOidFactory factory;

	LocalCdbOid* oid = factory.createLocalOid(); __STP(oid);

	int size = oid->binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);

	oid->toBinary(buff);

	buff->position(0);
	CdbOid* element = CdbOid::fromBinary(buff); __STP(element);

	CHECK(element->getTypeCode() == LocalCdbOid::CDB_LOCAL_OID);
	CHECK(element->isLocal());
}

TEST(TestLocalOidGroup, binary04_err){
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(10, true); __STP(buff);
	buff->put((uint8_t)0);

	CdbException* ex = nullptr;
	try{
		CdbOid* element = CdbOid::fromBinary(buff); __STP(element);
	}catch(CdbException* e){
		ex = e;
	}

	CHECK(ex != nullptr);
	delete ex;
}

TEST(TestLocalOidGroup, toKey01){
	LocalOidFactory factory;

	LocalCdbOid* oid = factory.createLocalOid(); __STP(oid);

	CdbOidKey* key = dynamic_cast<CdbOidKey*>(oid->toKey()); __STP(key);

	const CdbOid* o = key->getOid();
	CHECK(o->isLocal());
}
