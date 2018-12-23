/*
 * InfinityKey.cpp
 *
 *  Created on: 2018/12/23
 *      Author: iizuka
 */

#include "btree/InfinityKey.h"

namespace alinous {

InfinityKey::InfinityKey() : AbstractBtreeKey() {
}

InfinityKey::~InfinityKey() {
}

bool InfinityKey::isInfinity() {
	return true;
}

} /* namespace alinous */
