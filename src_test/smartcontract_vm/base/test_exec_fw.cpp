/*
 * test_exec_fw.cpp
 *
 *  Created on: 2019/06/20
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "engine/sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

using namespace alinous;


TEST_GROUP(TestExecFwGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}

};

TEST(TestExecFwGroup, exec){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_vm/base/resources/typeres/main.alns"));
	_ST(File, sourceFile2, projectFolder->get(L"src_test/smartcontract_vm/base/resources/typeres/utils.alns"));
	_ST(File, sourceFile3, projectFolder->get(L"src_test/smartcontract_vm/base/resources/typeres/impl.alns"));
	_ST(File, sourceFile4, projectFolder->get(L"src_test/smartcontract_vm/base/resources/typeres/ObjectA.alns"));

	SmartContract* sc = new SmartContract();
	sc->addCompilationUnit(sourceFile, projectFolder);
	sc->addCompilationUnit(sourceFile2, projectFolder);
	sc->addCompilationUnit(sourceFile3, projectFolder);
	sc->addCompilationUnit(sourceFile4, projectFolder);

	VirtualMachine* vm = new VirtualMachine(1024); __STP(vm);
	vm->loadSmartContract(sc);

	vm->analyze();
	bool haserror = vm->hasError();
	CHECK(!haserror);


}
