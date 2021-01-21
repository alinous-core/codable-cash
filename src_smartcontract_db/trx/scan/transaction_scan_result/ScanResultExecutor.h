/*
 * ScanResultExecutor.h
 *
 *  Created on: 2021/01/21
 *      Author: iizuka
 */

#ifndef TRX_SCAN_TRANSACTION_SCAN_RESULT_SCANRESULTEXECUTOR_H_
#define TRX_SCAN_TRANSACTION_SCAN_RESULT_SCANRESULTEXECUTOR_H_

namespace codablecash {

class IJoinLeftSource;

class ScanResultExecutor {
public:
	explicit ScanResultExecutor(IJoinLeftSource* source);
	virtual ~ScanResultExecutor();

private:
	IJoinLeftSource* source;
};

} /* namespace codablecash */

#endif /* TRX_SCAN_TRANSACTION_SCAN_RESULT_SCANRESULTEXECUTOR_H_ */
