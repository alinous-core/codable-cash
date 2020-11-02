/*
 * OuterJoinExecutor.h
 *
 *  Created on: 2020/08/23
 *      Author: iizuka
 */

#ifndef TRANSACTION_SCANNER_JOIN_OUTERJOINEXECUTOR_H_
#define TRANSACTION_SCANNER_JOIN_OUTERJOINEXECUTOR_H_

#include "trx/scan/transaction_scanner_join/AbstractJoinExecutor.h"

namespace codablecash {

class OuterJoinExecutor : public AbstractJoinExecutor {
public:
	OuterJoinExecutor(IJoinLeftSource* left, IJoinRightSource* right, ScanResultMetadata* metadata, ScanJoinContext* context);
	virtual ~OuterJoinExecutor();

	virtual void start();
	virtual bool hasNext();
	virtual const CdbRecord* next();

	virtual void shutdown();
};

} /* namespace codablecash */

#endif /* TRANSACTION_SCANNER_JOIN_OUTERJOINEXECUTOR_H_ */
