/*
 * BTreeKeyFactory.h
 *
 *  Created on: 2018/12/23
 *      Author: iizuka
 */

#ifndef BTREE_BTREEKEYFACTORY_H_
#define BTREE_BTREEKEYFACTORY_H_

#include <inttypes.h>

namespace alinous {

class BTreeKeyFactory {
public:
	static const constexpr uint32_t INFINITY_KEY{0x01};

	BTreeKeyFactory();
	virtual ~BTreeKeyFactory();


};

} /* namespace alinous */

#endif /* BTREE_BTREEKEYFACTORY_H_ */
