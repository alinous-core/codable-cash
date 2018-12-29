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

} /* namespace alinous */
