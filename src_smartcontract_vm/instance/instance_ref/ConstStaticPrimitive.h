/*
 * ConstStaticPrimitive.h
 *
 *  Created on: 2020/03/24
 *      Author: iizuka
 */

#ifndef INSTANCE_REF_CONSTSTATICPRIMITIVE_H_
#define INSTANCE_REF_CONSTSTATICPRIMITIVE_H_

#include "instance/instance_ref/PrimitiveReference.h"

namespace alinous {

class ConstStaticPrimitive : public PrimitiveReference {
public:
	ConstStaticPrimitive(PrimitiveReference* primitiveObj);
	virtual ~ConstStaticPrimitive();

	virtual bool isStaticConst() const noexcept;
};

} /* namespace alinous */

#endif /* INSTANCE_REF_CONSTSTATICPRIMITIVE_H_ */
