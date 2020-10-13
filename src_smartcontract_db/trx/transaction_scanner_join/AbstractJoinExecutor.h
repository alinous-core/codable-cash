/*
 * AbstractJoinExecutor.h
 *
 *  Created on: 2020/08/23
 *      Author: iizuka
 */

#ifndef TRANSACTION_SCANNER_JOIN_ABSTRACTJOINEXECUTOR_H_
#define TRANSACTION_SCANNER_JOIN_ABSTRACTJOINEXECUTOR_H_

#include "trx/transaction_scanner_join/IJoinLeftSource.h"

namespace codablecash {

class IJoinLeftSource;
class IJoinRightSource;
class ScanResultFieldMetadata;
class ScanJoinContext;

class AbstractJoinExecutor : public IJoinLeftSource {
public:
	AbstractJoinExecutor(IJoinLeftSource* left, IJoinRightSource* right, ScanResultFieldMetadata* metadata, ScanJoinContext* context);
	virtual ~AbstractJoinExecutor();

	const ScanResultFieldMetadata* getMedadata() const noexcept {
		return metadata;
	}

protected:
	IJoinLeftSource* left;
	IJoinRightSource* right;

	ScanResultFieldMetadata* metadata;
	ScanJoinContext* context;
};

} /* namespace codablecash */

#endif /* TRANSACTION_SCANNER_JOIN_ABSTRACTJOINEXECUTOR_H_ */
