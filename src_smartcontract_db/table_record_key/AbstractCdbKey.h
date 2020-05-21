/*
 * AbstractCdbKey.h
 *
 *  Created on: 2020/05/21
 *      Author: iizuka
 */

#ifndef TABLE_RECORD_KEY_ABSTRACTCDBKEY_H_
#define TABLE_RECORD_KEY_ABSTRACTCDBKEY_H_

#include "btree/AbstractBtreeKey.h"

namespace alinous {
}
using namespace alinous;

namespace codablecash {

class AbstractCdbKey : public AbstractBtreeKey {
public:
	AbstractCdbKey();
	virtual ~AbstractCdbKey();
};

} /* namespace codablecash */

#endif /* TABLE_RECORD_KEY_ABSTRACTCDBKEY_H_ */
