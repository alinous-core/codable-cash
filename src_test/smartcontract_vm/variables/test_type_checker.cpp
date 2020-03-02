/*
 * test_type_checker.cpp
 *
 *  Created on: 2020/02/27
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

#include "../VmTestUtils.h"
#include "base/StackRelease.h"

#include "ext_binary/ExtClassObject.h"
#include "ext_binary/ExtPrimitiveObject.h"

#include "type_check/AnalyzedTypeChecker.h"

#include "sc_analyze/AnalyzedType.h"

#include "type_check/InternalTypeChecker.h"


using namespace alinous;

TEST_GROUP(TestTypeCheckGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestTypeCheckGroup, construct){
	AnalyzedTypeChecker checker;
}

TEST(TestTypeCheckGroup, intnl01){
	AnalyzedType left(AnalyzedType::TYPE_INT);
	AnalyzedType right(AnalyzedType::TYPE_INT);

	int ret = InternalTypeChecker::analyzeCompatibility(&left, &right);
	CHECK(InternalTypeChecker::OK == ret);
}

TEST(TestTypeCheckGroup, intnl02){
	AnalyzedType left(AnalyzedType::TYPE_INT);
	AnalyzedType right;

	int ret = InternalTypeChecker::analyzeCompatibility(&left, &right);
	CHECK(InternalTypeChecker::INCOMPATIBLE == ret);
}

TEST(TestTypeCheckGroup, intnl03){
	AnalyzedType left;
	AnalyzedType right;

	int ret = InternalTypeChecker::analyzeCompatibility(&left, &right);
	CHECK(InternalTypeChecker::NO_CHECK == ret);
}

TEST(TestTypeCheckGroup, intnl04){
	AnalyzedType left(AnalyzedType::TYPE_BOOL);
	AnalyzedType right(AnalyzedType::TYPE_BOOL);

	int ret = InternalTypeChecker::analyzeCompatibility(&left, &right);
	CHECK(InternalTypeChecker::OK == ret);
}

TEST(TestTypeCheckGroup, intnl05){
	AnalyzedType left(AnalyzedType::TYPE_BOOL);
	AnalyzedType right(AnalyzedType::TYPE_INT);

	int ret = InternalTypeChecker::analyzeCompatibility(&left, &right);
	CHECK(InternalTypeChecker::INCOMPATIBLE == ret);
}

TEST(TestTypeCheckGroup, intnl06){
	AnalyzedType left(AnalyzedType::TYPE_STRING);
	AnalyzedType right(AnalyzedType::TYPE_STRING);

	int ret = InternalTypeChecker::analyzeCompatibility(&left, &right);
	CHECK(InternalTypeChecker::OK == ret);
}


TEST(TestTypeCheckGroup, intnl07){
	AnalyzedType left(AnalyzedType::TYPE_STRING);
	AnalyzedType right(AnalyzedType::TYPE_INT);

	int ret = InternalTypeChecker::analyzeCompatibility(&left, &right);
	CHECK(InternalTypeChecker::INCOMPATIBLE == ret);
}

TEST(TestTypeCheckGroup, intnlDim){
	AnalyzedType left(AnalyzedType::TYPE_INT);
	AnalyzedType right(AnalyzedType::TYPE_INT);

	left.setDim(2);

	int ret = InternalTypeChecker::analyzeCompatibility(&left, &right);
	CHECK(InternalTypeChecker::INCOMPATIBLE == ret);
}
