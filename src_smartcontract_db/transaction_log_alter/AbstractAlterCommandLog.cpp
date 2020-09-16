/*
 * AbstractAlterCommandLog.cpp
 *
 *  Created on: 2020/09/16
 *      Author: iizuka
 */

#include "transaction_log_alter/AbstractAlterCommandLog.h"

namespace codablecash {

AbstractAlterCommandLog::AbstractAlterCommandLog(uint8_t type) : AbstractDdlLog(type) {

}

AbstractAlterCommandLog::~AbstractAlterCommandLog() {

}

} /* namespace codablecash */
