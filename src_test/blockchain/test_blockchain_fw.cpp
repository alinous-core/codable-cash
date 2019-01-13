/*
 * test_blockchain_fw.cpp
 *
 *  Created on: 2019/01/01
 *      Author: iizuka
 */


#include "test_utils/t_macros.h"

#include "bc/Blockchains.h"
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

	Blockchains chains(&config);

	chains.init();

}





