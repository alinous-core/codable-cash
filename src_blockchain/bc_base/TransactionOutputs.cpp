/*
 * TransactionOutputs.cpp
 *
 *  Created on: 2019/01/03
 *      Author: iizuka
 */

#include "bc_base/TransactionOutputs.h"
#include "bc_base/TransactionOutput.h"

namespace codablecash {

TransactionOutputs::TransactionOutputs() {
	this->outputs = new ArrayList<TransactionOutput>;

}

TransactionOutputs::~TransactionOutputs() {
	delete this->outputs;
}

} /* namespace codablecash */
