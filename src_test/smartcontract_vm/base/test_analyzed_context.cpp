/*
 * test_analyzed_context.cpp
 *
 *  Created on: 2020/03/04
 *      Author: iizuka
 */
#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "engine/sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

#include "engine/sc_analyze/AnalyzedType.h"

#include "base/UnicodeString.h"

#include "../VmTestUtils.h"
#include "engine/sc_analyze/AnalyzeContext.h"

#include "lang/sc_declare_types/ObjectType.h"
#include "engine/sc/CompilationUnit.h"

#include "base/Exception.h"


using namespace alinous;

TEST_GROUP(TestAnalyzedContextGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestAnalyzedContextGroup, resolveTypeBool){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/base/resources/aclass/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	AnalyzeContext* actx = util.sc->getAnalyzeContext();
	CompilationUnit* unit = util.sc->getCompilationUnit(0);

	Exception* ex = nullptr;
	try {
		ObjectType otype;
		otype.setParent(unit);
		actx->getAnalyzedClass(&otype);
	}
	catch(Exception* e){
		ex = e;
	}

	CHECK(ex != nullptr);
	delete ex;
}
