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
	static constexpr uint8_t REF_BYTE{2};
	static constexpr uint8_t REF_CHAR{3};
	static constexpr uint8_t REF_SHORT{4};
	static constexpr uint8_t REF_INT{5};
	static constexpr uint8_t REF_LONG{6};


	AbstractReference();
	virtual ~AbstractReference();
};

} /* namespace alinous */

#endif /* INSTANCE_REF_ABSTRACTREFERENCE_H_ */
