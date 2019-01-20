/*
 * Elementary.h
 *
 *  Created on: 2019/01/21
 *      Author: iizuka
 */

#ifndef NUMERIC_ELEMENTARY_H_
#define NUMERIC_ELEMENTARY_H_

#include <inttypes.h>

namespace alinous {

class Elementary {
public:
	static int inplaceAdd(int* a, int aSize, int addend);
};

} /* namespace alinous */

#endif /* NUMERIC_ELEMENTARY_H_ */
