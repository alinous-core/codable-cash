/*
 * test_analyzed_class.cpp
 *
 *  Created on: 2020/03/03
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

#include "sc_analyze/AnalyzedType.h"

#include "base/UnicodeString.h"

#include "../VmTestUtils.h"
#include "sc_analyze/AnalyzeContext.h"

using namespace alinous;

TEST_GROUP(TestAnalyzedClassGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestAnalyzedClassGroup, copyconstructor){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/base/resources/case01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	AnalyzeContext* actx = util.sc->getAnalyzeContext();
	CHECK(actx->getCurrentElement() == nullptr)

	TypeResolver* resolver = actx->getTypeResolver();
	//resolver->findClassType(nullptr, );
}

