/*
 * AbstractAddress.h
 *
 *  Created on: 2019/01/03
 *      Author: iizuka
 */

#ifndef BC_BASE_ABSTRACTADDRESS_H_
#define BC_BASE_ABSTRACTADDRESS_H_

#include "filestore_block/IBlockObject.h"

namespace codablecash {
using namespace alinous;

class AbstractAddress : public IBlockObject {
public:
	static const constexpr char NORMAL_ADDRESS{0x01};
	static const constexpr char MULTISIG_ADDRESS{0x01};

	explicit AbstractAddress(int type);
	virtual ~AbstractAddress();

	int getType() const noexcept;

	virtual AbstractAddress* clone() const noexcept = 0;
	virtual bool equals(const AbstractAddress* other) const noexcept = 0;
private:
	int type;
};

} /* namespace codablecash */

#endif /* BC_BASE_ABSTRACTADDRESS_H_ */
