/*
 * OuterJoinExecutor.h
 *
 *  Created on: 2020/08/23
 *      Author: iizuka
 */

#ifndef TRANSACTION_SCANNER_JOIN_OUTERJOINEXECUTOR_H_
#define TRANSACTION_SCANNER_JOIN_OUTERJOINEXECUTOR_H_

#include "trx/transaction_scanner_join/AbstractJoinExecutor.h"

namespace codablecash {

class OuterJoinExecutor : AbstractJoinExecutor {
public:
	OuterJoinExecutor(IJoinLeftSource* left, IJoinRightSource* right, ScanResultFieldMetadata* metadata, ScanJoinContext* context);
	virtual ~OuterJoinExecutor();
};

} /* namespace codablecash */

#endif /* TRANSACTION_SCANNER_JOIN_OUTERJOINEXECUTOR_H_ */
