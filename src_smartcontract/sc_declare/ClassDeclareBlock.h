/*
 * ClassDeclareBlock.h
 *
 *  Created on: 2019/01/15
 *      Author: iizuka
 */

#ifndef SC_DECLARE_CLASSDECLAREBLOCK_H_
#define SC_DECLARE_CLASSDECLAREBLOCK_H_

#include "sc/CodeElement.h"

namespace codablecash {

class ClassDeclareBlock : public CodeElement{
public:
	ClassDeclareBlock();
	virtual ~ClassDeclareBlock();
};

} /* namespace codablecash */

#endif /* SC_DECLARE_CLASSDECLAREBLOCK_H_ */
