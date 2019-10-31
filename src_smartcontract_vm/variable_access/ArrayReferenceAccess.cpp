/*
 * ArrayReferenceAccess.cpp
 *
 *  Created on: 2019/10/31
 *      Author: iizuka
 */

#include "variable_access/ArrayReferenceAccess.h"

namespace alinous {

ArrayReferenceAccess::ArrayReferenceAccess(ArrayReferenceExpression* arrayRefExp) {
	this->arrayRefExp = arrayRefExp;
}

ArrayReferenceAccess::~ArrayReferenceAccess() {
}

} /* namespace alinous */
