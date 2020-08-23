/*
 * IJoinLeftSource.h
 *
 *  Created on: 2020/08/23
 *      Author: iizuka
 */

#ifndef TRANSACTION_SCANNER_JOIN_IJOINLEFTSOURCE_H_
#define TRANSACTION_SCANNER_JOIN_IJOINLEFTSOURCE_H_

namespace codablecash {

class CdbRecord;

class IJoinLeftSource {
public:
	IJoinLeftSource();
	virtual ~IJoinLeftSource();

	virtual void start() = 0;
	virtual bool hasNext() = 0;
	virtual const CdbRecord* next() = 0;

	virtual void shutdown() = 0;
};

} /* namespace codablecash */

#endif /* TRANSACTION_SCANNER_JOIN_IJOINLEFTSOURCE_H_ */
