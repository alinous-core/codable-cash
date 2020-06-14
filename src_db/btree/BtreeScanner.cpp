/*
 * BtreeScanner.cpp
 *
 *  Created on: 2018/12/29
 *      Author: iizuka
 */

#include "btree/BtreeScanner.h"
#include "btree/NodeCursor.h"
#include "btree/AbstractBtreeKey.h"
#include "filestore_block/IBlockObject.h"

namespace alinous {

BtreeScanner::BtreeScanner(NodeCursor* cursor) {
	this->cursor = cursor;
	this->nextObj = nullptr;
	this->initialized = false;
	this->key = nullptr;
}

BtreeScanner::~BtreeScanner() {
	delete this->cursor;
	if(this->nextObj != nullptr){
		delete this->nextObj;
	}
	if(this->key != nullptr){
		delete this->key;
	}
}

void BtreeScanner::begin() {
}

void BtreeScanner::begin(const AbstractBtreeKey* key) {
	this->key = key != nullptr ? key->clone() : nullptr;
}

bool BtreeScanner::hasNext() {
	if(this->nextObj != nullptr){
		delete this->nextObj, this->nextObj = nullptr;
	}

	if(!this->initialized){
		if(this->key == nullptr){
			this->nextObj = this->cursor->gotoFirst();
			this->initialized = true;
		}
		else{
			this->nextObj = this->cursor->gotoKey(this->key);
			this->initialized = true;
		}
	}
	else{
		this->nextObj = this->cursor->getNext();
	}

	return this->nextObj != nullptr;
}

const IBlockObject* BtreeScanner::next() {
	return this->nextObj;
}

} /* namespace alinous */


