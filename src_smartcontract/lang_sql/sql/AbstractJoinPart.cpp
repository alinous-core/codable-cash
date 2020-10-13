/*
 * AbstractJoinPart.cpp
 *
 *  Created on: 2019/02/28
 *      Author: iizuka
 */

#include "lang_sql/sql/AbstractJoinPart.h"

#include "engine/CdbException.h"

using namespace codablecash;

namespace alinous {

AbstractJoinPart::AbstractJoinPart(int kind) : AbstractSQLExpression(kind){
}

AbstractJoinPart::~AbstractJoinPart() {
}

void AbstractJoinPart::onSelectTarget(VirtualMachine* vm) {
	throw new CdbException(L"Can not use join condition in select target", __FILE__, __LINE__);
}


} /* namespace alinous */
