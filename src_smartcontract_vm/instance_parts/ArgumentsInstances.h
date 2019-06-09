/*
 * ArgumentsInstances.h
 *
 *  Created on: 2019/06/08
 *      Author: iizuka
 */

#ifndef INSTANCE_PARTS_ARGUMENTSINSTANCES_H_
#define INSTANCE_PARTS_ARGUMENTSINSTANCES_H_

#include "base/ArrayList.h"

namespace alinous {

class AbstractReference;

class ArgumentsInstances {
public:
	ArgumentsInstances();
	virtual ~ArgumentsInstances();

private:
	ArrayList<AbstractReference> list;

};

} /* namespace alinous */

#endif /* INSTANCE_PARTS_ARGUMENTSINSTANCES_H_ */
