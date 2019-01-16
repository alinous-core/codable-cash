/*
 * alinouslang.h
 *
 *  Created on: 2019/01/15
 *      Author: iizuka
 */

#ifndef SC_ALINOUSLANG_H_
#define SC_ALINOUSLANG_H_


#include "sc/CompilationUnit.h"

#include "sc_declare/ClassDeclare.h"
#include "sc_declare/ClassDeclareBlock.h"

namespace alinouslang {
using namespace alinous;
}

#define _P(tokenBegin, tokenEnd) tokenBegin->beginLine, tokenBegin->beginColumn, tokenEnd->endLine, tokenEnd->endColumn
#define _PO()

#endif /* SC_ALINOUSLANG_H_ */
