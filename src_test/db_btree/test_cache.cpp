/*
 * test_cache.cpp
 *
 *  Created on: 2018/12/23
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "btree/NodeCache.h"
#include "btreekey/ULongKey.h"

#include "btree/TreeNode.h"

using namespace alinous;

TEST_GROUP(TestNodeCashGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}
};

TEST(TestNodeCashGroup, constract){
	NodeCache cache(10, 10);
}

TEST(TestNodeCashGroup, add01){
	NodeCache cache(10, 10);

	TreeNode node(false, 4, new ULongKey(1));
	node.setFpos(256);


}


