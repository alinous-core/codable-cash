/*
 * NetworkShard.h
 *
 *  Created on: 2019/01/01
 *      Author: iizuka
 */

#ifndef BC_NETWORK_NETWORKSHARD_H_
#define BC_NETWORK_NETWORKSHARD_H_

namespace codablecash {

class NetworkShard {
private:
	NetworkShard();
public:
	NetworkShard(const NetworkShard& inst) = default;
	NetworkShard(int start, int length);
	virtual ~NetworkShard();

	int size() const noexcept;

	char getRandomHash() const noexcept;
	NetworkShard* clone() const noexcept;

private:
	int begin;
	int end;
};

} /* namespace codablecash */

#endif /* BC_NETWORK_NETWORKSHARD_H_ */
