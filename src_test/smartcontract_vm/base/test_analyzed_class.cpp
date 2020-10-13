/*
 * test_analyzed_class.cpp
 *
 *  Created on: 2020/03/03
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
#include "engine/sc_analyze/AnalyzedClass.h"

using namespace alinous;

TEST_GROUP(TestAnalyzedClassGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestAnalyzedClassGroup, copyconstructor01){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/base/resources/aclass/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	AnalyzeContext* actx = util.sc->getAnalyzeContext();

	UnicodeString clazz(L"test.fw.SmartContract");
	AnalyzedType* atype = util.findClassDeclare(&clazz); __STP(atype);
	AnalyzedClass* aclass = atype->getAnalyzedClass();

	AnalyzedClass newCls(*aclass);
	AnalyzedType atype2(&newCls);

	CHECK(atype2.equals(atype))
}

TEST(TestAnalyzedClassGroup, copyconstructor02){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/base/resources/aclass/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	AnalyzeContext* actx = util.sc->getAnalyzeContext();

	UnicodeString clazz(L"test.fw.SmartContract");
	AnalyzedType* atype = util.findClassDeclare(&clazz); __STP(atype);
	AnalyzedClass* aclass = atype->getAnalyzedClass();

	AnalyzedClass newCls(*aclass);
	AnalyzedType atype2(&newCls);

	CHECK(atype2.equals(atype))

	UnicodeString ifFqn(L"test.fw.TestInterface");
	AnalyzedType* ifAtype = util.findClassDeclare(&ifFqn); __STP(ifAtype);
	AnalyzedClass* ifclass = ifAtype->getAnalyzedClass();

	result = atype2.getAnalyzedClass()->hasBaseClass(ifclass);
	CHECK(result)
}


TEST(TestAnalyzedClassGroup, findmethod01){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/base/resources/aclass/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	AnalyzeContext* actx = util.sc->getAnalyzeContext();

	UnicodeString clazz(L"test.fw.SmartContract");
	AnalyzedType* atype = util.findClassDeclare(&clazz); __STP(atype);
	AnalyzedClass* aclass = atype->getAnalyzedClass();

	AnalyzedClass newCls(*aclass);
	AnalyzedType atype2(&newCls);

	CHECK(atype2.equals(atype))

	UnicodeString ifFqn(L"test.fw.TestInterface");
	AnalyzedType* ifAtype = util.findClassDeclare(&ifFqn); __STP(ifAtype);
	AnalyzedClass* ifclass = ifAtype->getAnalyzedClass();

	ArrayList<AnalyzedType> argumentTypeList;
	argumentTypeList.setDeleteOnExit();
	argumentTypeList.addElement(new AnalyzedType(AnalyzedType::TYPE_BYTE));

	UnicodeString methodName(L"test01");
	MethodDeclare* dec = ifclass->findMethod(&methodName, &argumentTypeList);
	CHECK(dec == nullptr)
}

TEST(TestAnalyzedClassGroup, findmethod02){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/base/resources/aclass/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	AnalyzeContext* actx = util.sc->getAnalyzeContext();

	UnicodeString clazz(L"test.fw.SmartContract");
	AnalyzedType* atype = util.findClassDeclare(&clazz); __STP(atype);
	AnalyzedClass* aclass = atype->getAnalyzedClass();

	AnalyzedClass newCls(*aclass);
	AnalyzedType atype2(&newCls);

	CHECK(atype2.equals(atype))

	ArrayList<AnalyzedType> argumentTypeList;
	argumentTypeList.setDeleteOnExit();
	argumentTypeList.addElement(new AnalyzedType(AnalyzedType::TYPE_BYTE));

	UnicodeString methodName(L"vfunc01");
	MethodDeclare* dec = aclass->findMethod(&methodName, &argumentTypeList);
	CHECK(dec == nullptr)
}
