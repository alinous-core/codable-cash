/*
 * TestDbSchemaAlterText01.cpp
 *
 *  Created on: 2020/10/02
 *      Author: iizuka
 */

#include "TestDbSchemaAlterText01.h"

#include "table/CdbTable.h"

#include "base/StackRelease.h"
#include "base/UnicodeString.h"

#include "table_record_value/AbstractCdbValue.h"

#include "base/StackRelease.h"

#include "engine/CodableDatabase.h"

#include "transaction/CdbTransaction.h"

#include "transaction_log/CreateTableLog.h"
#include "transaction_log/InsertLog.h"

#include "table_record/CdbRecord.h"
#include "table_record/CdbTableIdentifier.h"

#include "table_record_value/CdbIntValue.h"
#include "table_record_value/CdbStringValue.h"

#include "table_record_local/LocalCdbOid.h"

namespace codablecash {

TestDbSchemaAlterText01::TestDbSchemaAlterText01(TestEnv* env) : TestDbSchemaBase(env) {


}

TestDbSchemaAlterText01::~TestDbSchemaAlterText01() {

}

void TestDbSchemaAlterText01::init(uint64_t memCapacity) {
}

void TestDbSchemaAlterText01::createTable() {
}

void TestDbSchemaAlterText01::insert01() {
}

void TestDbSchemaAlterText01::insertRecord(CdbTransaction* trx, int id,	const wchar_t* name, int email_id) {
}

} /* namespace alinous */
