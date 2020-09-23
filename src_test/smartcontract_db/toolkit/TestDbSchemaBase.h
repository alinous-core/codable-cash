/*
 * TestDbSchemaBase.h
 *
 *  Created on: 2020/08/24
 *      Author: iizuka
 */

#ifndef SMARTCONTRACT_DB_TOOLKIT_TESTDBSCHEMABASE_H_
#define SMARTCONTRACT_DB_TOOLKIT_TESTDBSCHEMABASE_H_
#include <cstdint>


namespace alinous {
class TestEnv;
class File;
class VirtualMachine;
}
using namespace alinous;


namespace codablecash {

class CodableDatabase;
class CdbTableColumn;

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

	CdbTableColumn* getColumn(const wchar_t* schema, const wchar_t* table, const wchar_t* column);
	CdbTableColumn* getColumn(const wchar_t* table, const wchar_t* column);
protected:
	void createDb();

protected:
	VirtualMachine* vm;
	TestEnv* env;

	File* dbDir;
};

} /* namespace codablecash */

#endif /* SMARTCONTRACT_DB_TOOLKIT_TESTDBSCHEMABASE_H_ */
