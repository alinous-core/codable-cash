/*
 * AbstractBtreeKey.cpp
 *
 *  Created on: 2018/12/23
 *      Author: iizuka
 */

#include "btree/AbstractBtreeKey.h"

namespace alinous {

AbstractBtreeKey::AbstractBtreeKey() : IBlockObject() {
}

AbstractBtreeKey::~AbstractBtreeKey() {
}

IBlockObject* AbstractBtreeKey::copyData() const noexcept {
	return clone();
}

} /* namespace alinous */
