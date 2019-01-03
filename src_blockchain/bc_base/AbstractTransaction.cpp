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

AbstractTransaction::~AbstractTransaction() {
}

} /* namespace codablecash */
