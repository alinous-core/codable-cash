/*
 * alinouslang.h
 *
 *  Created on: 2019/01/15
 *      Author: iizuka
 */

#ifndef SC_ALINOUSLANG_H_
#define SC_ALINOUSLANG_H_

#include "base/UnicodeString.h"

#include "sc/CompilationUnit.h"

#include "sc_declare/AccessControlDeclare.h"
#include "sc_declare/ArgumentsListDeclare.h"
#include "sc_declare/ArgumentDeclare.h"
#include "sc_declare/ClassDeclare.h"
#include "sc_declare/ClassDeclareBlock.h"
#include "sc_declare/MemberVariableDeclare.h"
#include "sc_declare/MethodDeclare.h"
#include "sc_declare/PackageDeclare.h"
#include "sc_declare/PackageNameDeclare.h"

#include "sc_declare_types/CharType.h"
#include "sc_declare_types/ShortType.h"
#include "sc_declare_types/IntType.h"
#include "sc_declare_types/LongType.h"
#include "sc_declare_types/StringType.h"
#include "sc_declare_types/VoidType.h"

#include "sc_statement/StatementBlock.h"

#include "sc_expression/NullLiteral.h"


namespace alinouslang {
using namespace alinous;
}

#define _P(tokenBegin, tokenEnd) tokenBegin->beginLine, tokenBegin->beginColumn, tokenEnd->endLine, tokenEnd->endColumn
#define _PO()

#define _STR(t) new UnicodeString(t->image.c_str())
#define __ONERROR(obj) \
	if(hasError){\
		delete obj, obj=nullptr;\
	}

#endif /* SC_ALINOUSLANG_H_ */
