/*
 * TestDbSchemaBase.h
 *
 *  Created on: 2020/08/24
 *      Author: iizuka
 */

#ifndef SMARTCONTRACT_DB_TOOLKIT_TESTDBSCHEMABASE_H_
#define SMARTCONTRACT_DB_TOOLKIT_TESTDBSCHEMABASE_H_
#include <cstdint>

#include "base/ArrayList.h"

namespace alinous {
class TestEnv;
class File;
class VirtualMachine;
class ExtExceptionObject;
}
using namespace alinous;


namespace codablecash {

class CodableDatabase;
class CdbTableColumn;
class CdbTableIndex;
class CdbTable;
class IndexStore;
class CdbRecord;

class TestDbSchemaBase {
public:
	explicit TestDbSchemaBase(TestEnv* env);
	virtual ~TestDbSchemaBase();

	virtual void init();
	virtual void init(uint64_t memCapacity);

	CodableDatabase* getDatabase() const noexcept;
	VirtualMachine* getVm() const noexcept {
		return this->vm;
	}

	const ExtExceptionObject* checkUncaughtException();

	CdbTable* getTable(const wchar_t* schema, const wchar_t* table);

	CdbTableColumn* getColumn(const wchar_t* schema, const wchar_t* table, const wchar_t* column);
	CdbTableColumn* getColumn(const wchar_t* table, const wchar_t* column);

	CdbTableIndex* getIndex(const wchar_t* schema, const wchar_t* table, const wchar_t* column);
	CdbTableIndex* getIndex(const wchar_t* table, const wchar_t* column);

	IndexStore* getIndexStore(const wchar_t* schema, const wchar_t* table, const wchar_t* column);
	IndexStore* getIndexStore(const wchar_t* table, const wchar_t* column);

	ArrayList<CdbRecord>* scanRecords(const wchar_t* table);
	ArrayList<CdbRecord>* scanRecords(const wchar_t* schema, const wchar_t* table);

protected:
	void initSmartcontract();
	void setMain(const wchar_t* pkg, const wchar_t* clazz, const wchar_t* method) noexcept;
	void createDb();

protected:
	VirtualMachine* vm;
	TestEnv* env;

	uint64_t loidSerial;

	File* dbDir;

	File* folder; // smart contract base

	ExtExceptionObject* exobj;
};

} /* namespace codablecash */

#endif /* SMARTCONTRACT_DB_TOOLKIT_TESTDBSCHEMABASE_H_ */
