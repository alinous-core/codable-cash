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
#include "btree/NodeCacheRef.h"

using namespace alinous;

TEST_GROUP(TestNodeCashGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}
};

TEST(TestNodeCashGroup, constract){
	NodeCache cache(10, 10);
}

TEST(TestNodeCashGroup, copyConst){
	CachedFpos f1(10);
	CachedFpos f2(20);

	f2 = f1;

	CHECK(f2.fpos == f1.fpos)
}

TEST(TestNodeCashGroup, add01){
	NodeCache cache(10, 10);
	uint64_t fpos = 256;

	TreeNode* node = new TreeNode(false, 4, new ULongKey(1));
	node->setFpos(fpos);

	cache.add(node);

	NodeCacheRef* ref = cache.get(fpos);
	CHECK(ref->getNode()->getFpos() == fpos)
}

TEST(TestNodeCashGroup, add02){
	NodeCache cache(1, 1);
	uint64_t fpos = 256;
	uint64_t fpos2 = 512;

	TreeNode* node1 = new TreeNode(false, 4, new ULongKey(1));
	node1->setFpos(fpos);
	cache.add(node1);

	TreeNode* node2 = new TreeNode(false, 4, new ULongKey(2));
	node2->setFpos(fpos2);
	cache.add(node2);
}





