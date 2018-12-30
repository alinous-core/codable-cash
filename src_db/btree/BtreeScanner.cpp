/*
 * BtreeScanner.cpp
 *
 *  Created on: 2018/12/29
 *      Author: iizuka
 */

#include "btree/BtreeScanner.h"
#include "btree/NodeCursor.h"

namespace alinous {

BtreeScanner::BtreeScanner(NodeCursor* cursor) {
	this->cursor = cursor;

}

BtreeScanner::~BtreeScanner() {
	delete this->cursor;
}

void BtreeScanner::begin() {
	this->cursor->gotoFirst();
}

bool BtreeScanner::hasNext() {
}

NodeHandle* BtreeScanner::next() {
}

} /* namespace alinous */


