/*
 * AbstractJoinPart.cpp
 *
 *  Created on: 2019/02/28
 *      Author: iizuka
 */

#include "sql/AbstractJoinPart.h"

namespace alinous {

AbstractJoinPart::AbstractJoinPart(int kind) : AbstractSQLExpression(kind){
}

AbstractJoinPart::~AbstractJoinPart() {
}

} /* namespace alinous */
