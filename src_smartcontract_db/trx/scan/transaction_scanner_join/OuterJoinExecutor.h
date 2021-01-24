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

class JoinCandidateCursor;

class OuterJoinExecutor : public AbstractJoinExecutor {
public:
	OuterJoinExecutor(IJoinLeftSource* left, IJoinRightSource* right, ScanResultMetadata* metadata, ScanJoinContext* context, AbstractScanCondition* filterCondition);
	virtual ~OuterJoinExecutor();

	virtual void start();
	virtual bool hasNext();
	virtual const CdbRecord* next();

	virtual void shutdown();

private:
	bool hasNextLeftRecord();
	void onChangeLeft();

private:
	CdbRecord* leftRecord;
	JoinCandidateCursor* joinCandidateCursor;
};

} /* namespace codablecash */

#endif /* TRANSACTION_SCANNER_JOIN_OUTERJOINEXECUTOR_H_ */
