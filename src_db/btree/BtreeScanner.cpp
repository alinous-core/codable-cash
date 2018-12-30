/*
 * BtreeScanner.cpp
 *
 *  Created on: 2018/12/29
 *      Author: iizuka
 */

#include "btree/BtreeScanner.h"
#include "btree/NodeCursor.h"
#include "filestore_block/IBlockObject.h"

namespace alinous {

BtreeScanner::BtreeScanner(NodeCursor* cursor) {
	this->cursor = cursor;
	this->nextObj = nullptr;
	this->initialized = false;
}

BtreeScanner::~BtreeScanner() {
	delete this->cursor;
	if(this->nextObj != nullptr){
		delete this->nextObj;
	}
}

void BtreeScanner::begin() {
}

bool BtreeScanner::hasNext() {
	if(this->nextObj != nullptr){
		delete this->nextObj, this->nextObj = nullptr;
	}

	if(!this->initialized){
		this->nextObj = this->cursor->gotoFirst();
		this->initialized = true;
	}
	else{

	}

	return this->nextObj != nullptr;
}

IBlockObject* BtreeScanner::next() {
	return this->nextObj;
}

} /* namespace alinous */


