/*
 * AbstractTransaction.h
 *
 *  Created on: 2019/01/03
 *      Author: iizuka
 */

#ifndef BC_BASE_ABSTRACTTRANSACTION_H_
#define BC_BASE_ABSTRACTTRANSACTION_H_

namespace codablecash {

class AbstractTransaction {
public:
	static const constexpr int TYPE_SEND_BALANCE = 1;

	explicit AbstractTransaction(int type);
	virtual ~AbstractTransaction();

protected:
	int type;
};

} /* namespace codablecash */

#endif /* BC_BASE_ABSTRACTTRANSACTION_H_ */
