/*
 * BlockchainAddress.h
 *
 *  Created on: 2018/12/30
 *      Author: iizuka
 */

#ifndef BC_BASE_BLOCKCHAINADDRESS_H_
#define BC_BASE_BLOCKCHAINADDRESS_H_

namespace codablecash {

class BlockchainAddress {
public:
	BlockchainAddress();
	virtual ~BlockchainAddress();

	static BlockchainAddress* createAddress() noexcept;

private:
	char shardhash;
	char* pubkey32;
};

} /* namespace codablecash */

#endif /* BC_BASE_BLOCKCHAINADDRESS_H_ */
