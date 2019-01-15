/*
 * ClassDeclare.h
 *
 *  Created on: 2019/01/15
 *      Author: iizuka
 */

#ifndef SC_DECLARE_CLASSDECLARE_H_
#define SC_DECLARE_CLASSDECLARE_H_

#include "sc/CodeElement.h"

namespace codablecash {

class ClassDeclareBlock;

class ClassDeclare : public CodeElement {
public:
	ClassDeclare();
	virtual ~ClassDeclare();

	void setBlock(ClassDeclareBlock* block);

private:
	ClassDeclareBlock* block;
};

} /* namespace codablecash */

#endif /* SC_DECLARE_CLASSDECLARE_H_ */
