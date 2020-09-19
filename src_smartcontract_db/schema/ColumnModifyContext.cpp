/*
 * ColumnModifyContext.cpp
 *
 *  Created on: 2020/09/19
 *      Author: iizuka
 */

#include "schema/ColumnModifyContext.h"

namespace codablecash {

ColumnModifyContext::ColumnModifyContext() {
	this->uniqueChange = UniqueChage::UNIQUE_NONE;
	this->typeChanged = false;
	this->notNullChange = NotNullChage::NOTNULL_NONE;

	this->cdbType = 0;
}

ColumnModifyContext::~ColumnModifyContext() {

}

} /* namespace codablecash */
