/*
 * ParenthesisJoinPart.cpp
 *
 *  Created on: 2019/02/28
 *      Author: iizuka
 */

#include "sql_join_parts/ParenthesisJoinPart.h"

namespace alinous {

ParenthesisJoinPart::ParenthesisJoinPart() : AbstractJoinPart(CodeElement::SQL_EXP_PARENTHESIS_JOIN_PART) {

}

ParenthesisJoinPart::~ParenthesisJoinPart() {
}

} /* namespace alinous */
