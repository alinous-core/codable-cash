/*
 * test_btree_misc.cpp
 *
 *  Created on: 2020/09/27
 *      Author: iizuka
 */


#include "test_utils/t_macros.h"

#include "base/StackRelease.h"
#include "base/RawArrayPrimitive.h"

#include "btree/BtreeHeaderBlock.h"
#include "btree/BtreeConfig.h"
#include "btree/AbstractBtreeKey.h"
#include "btree/DataNode.h"
#include "btree/TreeNode.h"

#include "btreekey/NullKey.h"

#include <cstdint>


using namespace alinous;

TEST_GROUP(TestBTreeMiscGroup) {
	TEST_SETUP(){
	}
	TEST_TEARDOWN(){
	}
};

TEST(TestBTreeMiscGroup, case01){
	BtreeConfig config;

	BtreeConfig* config2 = dynamic_cast<BtreeConfig*>(config.copyData()); __STP(config2);

	CHECK(config.blockSize = config2->blockSize);
	CHECK(config.nodeNumber = config2->blockSize);
}

TEST(TestBTreeMiscGroup, case02){
	BtreeHeaderBlock block;

	BtreeHeaderBlock* block2 = dynamic_cast<BtreeHeaderBlock*>(block.copyData()); __STP(block2);

	CHECK(block.getRootFpos() == block2->getRootFpos());
}

TEST(TestBTreeMiscGroup, case03){
	AbstractBtreeKey* key = new NullKey(); __STP(key);

	AbstractBtreeKey* key2 = dynamic_cast<AbstractBtreeKey*>(key->copyData()); __STP(key2);

	CHECK(key->compareTo(key2) == 0);
}

TEST(TestBTreeMiscGroup, case04){
	AbstractBtreeKey* key = new NullKey();
	DataNode node(key);
	node.setDataFpos(10L);
	node.setFpos(1L);

	DataNode* node2 = dynamic_cast<DataNode*>(node.copyData()); __STP(node2);

	CHECK(node.getFpos() == node2->getFpos());
	CHECK(node.getDataFpos() == node2->getDataFpos());
}

TEST(TestBTreeMiscGroup, case05){
	AbstractBtreeKey* key = new NullKey();
	TreeNode node(true, 4, key, true);
	node.setFpos(1L);

	TreeNode* node2 = dynamic_cast<TreeNode*>(node.copyData()); __STP(node2);

	CHECK(node.getFpos() == node2->getFpos());

	RawArrayPrimitive<uint64_t>* list = node2->getInnerNodeFpos();
	CHECK(list->size() == 4);
}
