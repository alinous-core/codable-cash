/*
 * PrimitiveReference.h
 *
 *  Created on: 2019/05/25
 *      Author: iizuka
 */

#ifndef INSTANCE_REF_PRIMITIVEREFERENCE_H_
#define INSTANCE_REF_PRIMITIVEREFERENCE_H_

#include "instance_ref/AbstractReference.h"

namespace alinous {

class PrimitiveReference : public AbstractReference {
public:
	explicit PrimitiveReference(uint8_t type);
	virtual ~PrimitiveReference();

private:
};

} /* namespace alinous */

#endif /* INSTANCE_REF_PRIMITIVEREFERENCE_H_ */
