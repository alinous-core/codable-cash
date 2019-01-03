/*
 * AbstractAddress.h
 *
 *  Created on: 2019/01/03
 *      Author: iizuka
 */

#ifndef BC_BASE_ABSTRACTADDRESS_H_
#define BC_BASE_ABSTRACTADDRESS_H_

namespace codablecash {

class AbstractAddress {
public:
	static const constexpr char NORMAL_ADDRESS{0x01};
	static const constexpr char MULTISIG_ADDRESS{0x01};

	explicit AbstractAddress(int type);
	virtual ~AbstractAddress();

	int getType() const noexcept;
private:
	int type;
};

} /* namespace codablecash */

#endif /* BC_BASE_ABSTRACTADDRESS_H_ */
