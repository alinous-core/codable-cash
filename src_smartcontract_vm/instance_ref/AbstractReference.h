/*
 * AbstractReference.h
 *
 *  Created on: 2019/05/24
 *      Author: iizuka
 */

#ifndef INSTANCE_REF_ABSTRACTREFERENCE_H_
#define INSTANCE_REF_ABSTRACTREFERENCE_H_
#include <cstdint>

namespace alinous {

class AbstractReference {
public:
	static constexpr uint8_t REF_OBJ{1};


	AbstractReference();
	virtual ~AbstractReference();
};

} /* namespace alinous */

#endif /* INSTANCE_REF_ABSTRACTREFERENCE_H_ */
