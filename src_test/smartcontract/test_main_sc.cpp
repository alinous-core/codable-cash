/*
 * test_main_sc.cpp
 *
 *  Created on: 2018/12/31
 *      Author: iizuka
 */


#include "test_utils/t_macros.h"

#include "sc/SmartContract.h"

using namespace alinous;
using namespace codablecash;



TEST_GROUP(TestSmartContractGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}

};

TEST(TestSmartContractGroup, construct){
	SmartContract* sc = new SmartContract();
	delete sc;
}


