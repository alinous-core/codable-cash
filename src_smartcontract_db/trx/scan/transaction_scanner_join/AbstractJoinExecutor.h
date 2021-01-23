/*
 * AbstractJoinExecutor.h
 *
 *  Created on: 2020/08/23
 *      Author: iizuka
 */

#ifndef TRANSACTION_SCANNER_JOIN_ABSTRACTJOINEXECUTOR_H_
#define TRANSACTION_SCANNER_JOIN_ABSTRACTJOINEXECUTOR_H_

#include "trx/scan/transaction_scanner_join/IJoinLeftSource.h"

namespace codablecash {

class IJoinLeftSource;
class IJoinRightSource;
class ScanResultMetadata;
class ScanJoinContext;
class AbstractScanCondition;

class AbstractJoinExecutor : public IJoinLeftSource {
public:
	AbstractJoinExecutor(IJoinLeftSource* left, IJoinRightSource* right, ScanResultMetadata* metadata, ScanJoinContext* context, AbstractScanCondition* filterCondition);
	virtual ~AbstractJoinExecutor();

	const ScanResultMetadata* getMedadata() const noexcept {
		return metadata;
	}

	void start();
	void shutdown();

protected:
	IJoinLeftSource* left;
	IJoinRightSource* right;

	ScanResultMetadata* metadata;
	ScanJoinContext* context;
	AbstractScanCondition* filterCondition;
};

} /* namespace codablecash */

#endif /* TRANSACTION_SCANNER_JOIN_ABSTRACTJOINEXECUTOR_H_ */
