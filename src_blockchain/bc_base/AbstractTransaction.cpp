/*
 * AbstractTransaction.cpp
 *
 *  Created on: 2019/01/03
 *      Author: iizuka
 */

#include "bc_base/AbstractTransaction.h"

namespace codablecash {

AbstractTransaction::AbstractTransaction(int type) {
	this->type = type;
}

AbstractTransaction::AbstractTransaction(const AbstractTransaction& inst) {
	this->type = inst.type;
}

AbstractTransaction::~AbstractTransaction() {
}

} /* namespace codablecash */
