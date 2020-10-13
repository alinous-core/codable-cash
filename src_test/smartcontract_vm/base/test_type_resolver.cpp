/*
 * test_type_resolver.cpp
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
#include "engine/sc_analyze/AnalyzedClass.h"
#include "engine/sc_analyze/TypeResolver.h"
#include "engine/sc_analyze/AnalyzeContext.h"

#include "lang/sc_declare_types/BoolType.h"
#include "lang/sc_declare_types/ObjectType.h"

#include "lang/sc_declare/ClassDeclare.h"

#include "lang/sc_declare/PackageNameDeclare.h"

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

	CHECK(atype->getType() == AnalyzedType::TYPE_BOOL);
}

TEST(TestTypeResolveGroup, resolveTypeError){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/base/resources/aclass/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	AnalyzeContext* actx = util.sc->getAnalyzeContext();
	TypeResolver* resolver = actx->getTypeResolver();

	BoolType btype;
	btype.setType(-1);
	AnalyzedType* atype = resolver->resolveType(nullptr, &btype); __STP(atype);
	CHECK(atype == nullptr);
}

TEST(TestTypeResolveGroup, findBaseTypeBool){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/base/resources/aclass/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	AnalyzeContext* actx = util.sc->getAnalyzeContext();
	TypeResolver* resolver = actx->getTypeResolver();

	UnicodeString typestr(L"boolean");
	AnalyzedType* atype = resolver->findBaseType(&typestr); __STP(atype);

	CHECK(atype->getType() == AnalyzedType::TYPE_BOOL);
}

TEST(TestTypeResolveGroup, findBaseTypeByte){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/base/resources/aclass/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	AnalyzeContext* actx = util.sc->getAnalyzeContext();
	TypeResolver* resolver = actx->getTypeResolver();

	UnicodeString typestr(L"byte");
	AnalyzedType* atype = resolver->findBaseType(&typestr); __STP(atype);

	CHECK(atype->getType() == AnalyzedType::TYPE_BYTE);
}

TEST(TestTypeResolveGroup, findBaseTypeShort){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/base/resources/aclass/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	AnalyzeContext* actx = util.sc->getAnalyzeContext();
	TypeResolver* resolver = actx->getTypeResolver();

	UnicodeString typestr(L"short");
	AnalyzedType* atype = resolver->findBaseType(&typestr); __STP(atype);

	CHECK(atype->getType() == AnalyzedType::TYPE_SHORT);
}

TEST(TestTypeResolveGroup, findBaseTypeChar){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/base/resources/aclass/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	AnalyzeContext* actx = util.sc->getAnalyzeContext();
	TypeResolver* resolver = actx->getTypeResolver();

	UnicodeString typestr(L"char");
	AnalyzedType* atype = resolver->findBaseType(&typestr); __STP(atype);

	CHECK(atype->getType() == AnalyzedType::TYPE_CHAR);
}

TEST(TestTypeResolveGroup, findBaseTypeLong){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/base/resources/aclass/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	AnalyzeContext* actx = util.sc->getAnalyzeContext();
	TypeResolver* resolver = actx->getTypeResolver();

	UnicodeString typestr(L"long");
	AnalyzedType* atype = resolver->findBaseType(&typestr); __STP(atype);

	CHECK(atype->getType() == AnalyzedType::TYPE_LONG);
}

TEST(TestTypeResolveGroup, findBaseTypeString){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/base/resources/aclass/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	AnalyzeContext* actx = util.sc->getAnalyzeContext();
	TypeResolver* resolver = actx->getTypeResolver();

	UnicodeString typestr(L"String");
	AnalyzedType* atype = resolver->findBaseType(&typestr); __STP(atype);

	CHECK(atype->getType() == AnalyzedType::TYPE_STRING);
}

TEST(TestTypeResolveGroup, findClassTypeError01){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/base/resources/aclass/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	AnalyzeContext* actx = util.sc->getAnalyzeContext();
	TypeResolver* resolver = actx->getTypeResolver();

	UnicodeString packageName(L"test.fw.base");
	UnicodeString name(L"dummy");
	AnalyzedType* atype = resolver->testFindClassType(&packageName, &name); __STP(atype);

	CHECK(atype == nullptr);
}

TEST(TestTypeResolveGroup, findClassTypeError02){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/base/resources/aclass/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	AnalyzeContext* actx = util.sc->getAnalyzeContext();
	TypeResolver* resolver = actx->getTypeResolver();

	UnicodeString packageName(L"aaaaa");
	UnicodeString name(L"dummy");
	AnalyzedType* atype = resolver->testFindClassType(&packageName, &name); __STP(atype);

	CHECK(atype == nullptr);
}

TEST(TestTypeResolveGroup, resolveTypeInPackage){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/base/resources/aclass/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	AnalyzeContext* actx = util.sc->getAnalyzeContext();
	TypeResolver* resolver = actx->getTypeResolver();

	UnicodeString clazz(L"test.fw.SmartContract");
	AnalyzedType* aclazztype = util.findClassDeclare(&clazz); __STP(aclazztype);

	CHECK(aclazztype != nullptr);

	AnalyzedClass* aclazz = aclazztype->getAnalyzedClass();
	ClassDeclare* dec = aclazz->getClassDeclare();
	ObjectType otype;
	UnicodeString *clazzName = new UnicodeString(L"SmartContract");
	otype.setName(clazzName);

	PackageNameDeclare *pkg = new PackageNameDeclare();
	pkg->addSegment(new UnicodeString(L"test"));
	pkg->addSegment(new UnicodeString(L"fw"));
	otype.setPackageName(pkg);

	AnalyzedType* atype = resolver->testResolveType(dec, &otype); __STP(atype);

	CHECK(atype != nullptr);
}

