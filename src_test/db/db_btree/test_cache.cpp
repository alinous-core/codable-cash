/*
 * test_cache.cpp
 *
 *  Created on: 2018/12/23
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "btree_cache/NodeCache.h"
#include "btree_cache/NodeCacheRef.h"

#include "btreekey/ULongKey.h"

#include "btree/TreeNode.h"

#include "test_utils/TestBreak.h"
#include "base_thread/AbstractThreadRunner.h"

#include "osenv/funcs.h"

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

	TreeNode* node = new TreeNode(false, 4, new ULongKey(1), true);
	node->setFpos(fpos);

	cache.add(node);

	NodeCacheRef* ref = cache.get(fpos);
	CHECK(ref->getNode()->getFpos() == fpos)
}

TEST(TestNodeCashGroup, add02){
	NodeCache cache(1, 1);
	uint64_t fpos = 256;
	uint64_t fpos2 = 512;

	TreeNode* node1 = new TreeNode(false, 4, new ULongKey(1), true);
	node1->setFpos(fpos);
	cache.add(node1);

	TreeNode* node2 = new TreeNode(false, 4, new ULongKey(2), true);
	node2->setFpos(fpos2);
	cache.add(node2);

	NodeCacheRef* ref = cache.get(fpos);
	CHECK(ref == nullptr)

	ref = cache.get(fpos2);
	CHECK(ref != nullptr)
}

class TestCacheRuuer : public AbstractThreadRunner {
public:
	TestCacheRuuer(const UnicodeString* name, TestBreak* breakpoint, NodeCache* cache) : AbstractThreadRunner(name) {
		this->breakpoint = breakpoint;
		this->cache = cache;
	}
	virtual ~TestCacheRuuer(){}

	virtual void process() noexcept{
		uint64_t fpos2 = 512;
		TreeNode* node2 = new TreeNode(false, 4, new ULongKey(2), true);
		node2->setFpos(fpos2);

		breakpoint->breakpoint(1);
		cache->add(node2);
	}

private:
	TestBreak* breakpoint;
	NodeCache* cache;
};

TEST(TestNodeCashGroup, add03){
	NodeCache cache(1, 1);
	uint64_t fpos = 256;
	uint64_t fpos2 = 512;

	// thread test
	UnicodeString str01(L"test01");
	TestBreak break01;

	TestCacheRuuer* runner01 = new TestCacheRuuer(&str01, &break01, &cache);
	runner01->start();

	TreeNode* node1 = new TreeNode(false, 4, new ULongKey(1), true);
	node1->setFpos(fpos);
	cache.add(node1);

	// lock
	NodeCacheRef* ref = cache.get(fpos);
	CHECK(ref != nullptr)
	ref->inc();

	break01.resume(1);
	// before resume first one, wait for second thread is waiting
	Os::usleep(1000);

	// unlock
	ref->dec();

	runner01->join();
	delete runner01;
}



