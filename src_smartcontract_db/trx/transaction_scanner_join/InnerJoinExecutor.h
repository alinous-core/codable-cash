/*
 * InnerJoinExecutor.h
 *
 *  Created on: 2020/08/23
 *      Author: iizuka
 */

#ifndef TRANSACTION_SCANNER_JOIN_INNERJOINEXECUTOR_H_
#define TRANSACTION_SCANNER_JOIN_INNERJOINEXECUTOR_H_

#include "trx/transaction_scanner_join/AbstractJoinExecutor.h"

namespace codablecash {

class InnerJoinExecutor : AbstractJoinExecutor {
public:
	InnerJoinExecutor(IJoinLeftSource* left, IJoinRightSource* right, ScanResultFieldMetadata* metadata, ScanJoinContext* context);
	virtual ~InnerJoinExecutor();
};

} /* namespace codablecash */

#endif /* TRANSACTION_SCANNER_JOIN_INNERJOINEXECUTOR_H_ */
