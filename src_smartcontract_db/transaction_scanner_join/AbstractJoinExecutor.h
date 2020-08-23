/*
 * AbstractJoinExecutor.h
 *
 *  Created on: 2020/08/23
 *      Author: iizuka
 */

#ifndef TRANSACTION_SCANNER_JOIN_ABSTRACTJOINEXECUTOR_H_
#define TRANSACTION_SCANNER_JOIN_ABSTRACTJOINEXECUTOR_H_

namespace codablecash {

class IJoinLeftSource;
class IJoinRightSource;

class AbstractJoinExecutor {
public:
	AbstractJoinExecutor(IJoinLeftSource* left, IJoinRightSource* right);
	virtual ~AbstractJoinExecutor();

protected:
	IJoinLeftSource* left;
	IJoinRightSource* right;
};

} /* namespace codablecash */

#endif /* TRANSACTION_SCANNER_JOIN_ABSTRACTJOINEXECUTOR_H_ */
