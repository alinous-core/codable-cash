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

class AbstractJoinExecutor : public IJoinLeftSource {
public:
	AbstractJoinExecutor(IJoinLeftSource* left, IJoinRightSource* right, ScanResultMetadata* metadata, ScanJoinContext* context);
	virtual ~AbstractJoinExecutor();

	const ScanResultMetadata* getMedadata() const noexcept {
		return metadata;
	}

protected:
	IJoinLeftSource* left;
	IJoinRightSource* right;

	ScanResultMetadata* metadata;
	ScanJoinContext* context;
};

} /* namespace codablecash */

#endif /* TRANSACTION_SCANNER_JOIN_ABSTRACTJOINEXECUTOR_H_ */
