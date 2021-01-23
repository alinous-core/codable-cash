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
class CodableDatabase;

class ScanResultExecutor {
public:
	explicit ScanResultExecutor(IJoinLeftSource* source, CodableDatabase* db);
	virtual ~ScanResultExecutor();

	void execScan();

private:
	void doExecScan();
private:
	IJoinLeftSource* source;
	CodableDatabase* db;
};

} /* namespace codablecash */

#endif /* TRX_SCAN_TRANSACTION_SCAN_RESULT_SCANRESULTEXECUTOR_H_ */
