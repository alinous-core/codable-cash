/*
 * test_type_resolver.cpp
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
#include "sc_analyze/AnalyzedClass.h"
#include "sc_analyze/TypeResolver.h"
#include "sc_analyze/AnalyzeContext.h"

#include "sc_declare_types/BoolType.h"

using namespace alinous;

TEST_GROUP(TestTypeResolveGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestTypeResolveGroup, resolveTypeBool){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/base/resources/aclass/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	AnalyzeContext* actx = util.sc->getAnalyzeContext();
	TypeResolver* resolver = actx->getTypeResolver();

	BoolType btype;
	AnalyzedType* atype = resolver->resolveType(nullptr, &btype); __STP(atype);
}


