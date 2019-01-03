/*
 * TransactionInputs.cpp
 *
 *  Created on: 2019/01/03
 *      Author: iizuka
 */

#include "bc_base/TransactionInputs.h"
#include "bc_base/TransactionInput.h"

namespace codablecash {

TransactionInputs::TransactionInputs() {
	this->inputs = new ArrayList<TransactionInput>();
}

TransactionInputs::~TransactionInputs() {
	delete this->inputs;
}

} /* namespace codablecash */
