/*
 * test_exec_fw.cpp
 *
 *  Created on: 2019/06/20
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

using namespace alinous;


TEST_GROUP(TestExecFwGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}

};

TEST(TestExecFwGroup, exec){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_vm/resources/typeres/main.alns"));
	_ST(File, sourceFile2, projectFolder->get(L"src_test/smartcontract_vm/resources/typeres/utils.alns"));
	_ST(File, sourceFile3, projectFolder->get(L"src_test/smartcontract_vm/resources/typeres/impl.alns"));

	SmartContract* sc = new SmartContract();
	sc->addCompilationUnit(sourceFile);
	sc->addCompilationUnit(sourceFile2);
	sc->addCompilationUnit(sourceFile3);

	VirtualMachine* vm = new VirtualMachine(1024); __STP(vm);
	vm->loadSmartContract(sc);

	vm->analyze();
	bool haserror = vm->hasError();
	CHECK(!haserror);


}
