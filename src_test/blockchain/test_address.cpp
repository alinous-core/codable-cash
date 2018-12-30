/*
 * test_address.cpp
 *
 *  Created on: 2018/12/30
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "bc_base/BlockchainAddress.h"

using namespace alinous;
using namespace codablecash;

TEST_GROUP(TestBlockchainAddressGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}

};

TEST(TestBlockchainAddressGroup, constract){
	BlockchainAddress* address = new BlockchainAddress();
	delete address;
}



