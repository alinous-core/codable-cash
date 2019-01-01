/*
 * NetworkShardStatus.h
 *
 *  Created on: 2018/12/31
 *      Author: iizuka
 */

#ifndef BC_NETWORK_NETWORKSHARDSSTATUS_H_
#define BC_NETWORK_NETWORKSHARDSSTATUS_H_

namespace codablecash {

class NetworkShardsStatus {
public:

	explicit NetworkShardsStatus(int numShard);
	virtual ~NetworkShardsStatus();

private:
	int numShard;
};

} /* namespace codablecash */

#endif /* BC_NETWORK_NETWORKSHARDSSTATUS_H_ */
