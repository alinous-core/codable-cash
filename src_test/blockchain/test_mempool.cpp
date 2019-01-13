/*
 * test_mempool.cpp
 *
 *  Created on: 2019/01/05
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"
#include "mempool/MemPool.h"

#include "base_io/ByteBuffer.h"
#include "base/StackRelease.h"

using namespace alinous;
using namespace codablecash;

TEST_GROUP(TestMempoolGroup) {
	TEST_SETUP(){
		env->setup();
	}
	TEST_TEARDOWN(){
		env->teardown();
	}
};

TEST(TestMempoolGroup, constract){
	File projectFolder = this->env->testCaseDir();
	_ST(File, baseDir, projectFolder.get(L"store"))

	MemPool memPool(baseDir);
}

TEST(TestMempoolGroup, init){
	File projectFolder = this->env->testCaseDir();
	_ST(File, baseDir, projectFolder.get(L"store"))

	{
		MemPool memPool(baseDir);
		memPool.init();
		memPool.close();
	}

	{
		MemPool memPool(baseDir);
		memPool.init();
		memPool.close();
	}
}
