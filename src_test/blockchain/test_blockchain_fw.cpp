/*
 * test_blockchain_fw.cpp
 *
 *  Created on: 2019/01/01
 *      Author: iizuka
 */


#include <bc/CodablecashBlockchains.h>
#include "test_utils/t_macros.h"

#include "bc/BlockchainsConfig.h"

using namespace alinous;
using namespace codablecash;

TEST_GROUP(TestBlockchainFrameworkGroup) {
	TEST_SETUP(){
		env->setup();
	}
	TEST_TEARDOWN(){
		env->teardown();
	}
};

TEST(TestBlockchainFrameworkGroup, constract){
	File projectFolder = this->env->testCaseDir();
	_ST(File, baseDir, projectFolder.get(L"store"))
	_ST(UnicodeString, baseDirStr, baseDir->getAbsolutePath())


	BlockchainsConfig config;
	config.baseFolder = new File(*baseDir);

	CodablecashBlockchains chains(&config);

	chains.init();

}





