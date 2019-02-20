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

#include "sc_statement/ExpressionStatement.h"
#include "sc_statement/StatementBlock.h"
#include "sc_statement/BlankStatement.h"
#include "sc_statement/SubstitutionStatement.h"
#include "sc_statement/VariableDeclareStatement.h"

#include "sc_statement_ctrl/BreakStatement.h"
#include "sc_statement_ctrl/ContinueStatement.h"
#include "sc_statement_ctrl/DoWhileStatement.h"
#include "sc_statement_ctrl/ForStatement.h"
#include "sc_statement_ctrl/IfStatement.h"
#include "sc_statement_ctrl/ReturnStatement.h"
#include "sc_statement_ctrl/WhileStatement.h"


#include "sc_expression/AllocationExpression.h"
#include "sc_expression/ArrayReferenceExpression.h"
#include "sc_expression/BooleanLiteral.h"
#include "sc_expression/CastExpression.h"
#include "sc_expression/FunctionCallExpression.h"
#include "sc_expression/LiteralExpression.h"
#include "sc_expression/MemberReferenceExpression.h"
#include "sc_expression/NullLiteral.h"
#include "sc_expression/NumberLiteral.h"
#include "sc_expression/ParenthesisExpression.h"
#include "sc_expression/VariableIdentifier.h"

#include "sc_expression_arithmetic/AddExpression.h"
#include "sc_expression_arithmetic/MultiplicativeExpression.h"
#include "sc_expression_arithmetic/NegateExpression.h"
#include "sc_expression_arithmetic/PostIncrementExpression.h"
#include "sc_expression_arithmetic/PreIncrementExpression.h"

#include "sc_expression_bit/AndExpression.h"
#include "sc_expression_bit/BitReverseExpression.h"
#include "sc_expression_bit/ExclusiveOrExpression.h"
#include "sc_expression_bit/OrExpression.h"
#include "sc_expression_bit/ShiftExpression.h"

#include "sc_expression_logical/ConditionalAndExpression.h"
#include "sc_expression_logical/ConditionalOrExpression.h"
#include "sc_expression_logical/EqualityExpression.h"
#include "sc_expression_logical/NotExpression.h"
#include "sc_expression_logical/RelationalExpression.h"

#include "sql_ddl/CreateTableStatement.h"
#include "sql_ddl/DropTableStatement.h"

#include "sql_dml/BeginStatement.h"
#include "sql_dml/CommitStatement.h"
#include "sql_dml/DeleteStatement.h"
#include "sql_dml/InsertStatement.h"
#include "sql_dml/RollbackStatement.h"
#include "sql_dml/SelectStatement.h"
#include "sql_dml/UpdateStatement.h"

#include "sql_dml_parts/SQLColumnsList.h"
#include "sql_dml_parts/SQLFrom.h"
#include "sql_dml_parts/SQLFrom.h"
#include "sql_dml_parts/SQLGroupBy.h"
#include "sql_dml_parts/SQLLimitOffset.h"

#include "sql_expression/SQLAdditiveExpression.h"
#include "sql_expression/SQLAndExpression.h"
#include "sql_expression/SQLBetweenExpression.h"
#include "sql_expression/SQLBooleanLiteral.h"
#include "sql_expression/SQLFunctionCall.h"
#include "sql_expression/SQLLiteral.h"
#include "sql_expression/SQLLikeExpression.h"
#include "sql_expression/SQLIsNullExpression.h"
#include "sql_expression/SQLInExpression.h"
#include "sql_expression/SQLExpressionList.h"
#include "sql_expression/SQLEqualityExpression.h"
#include "sql_expression/SQLColumnIdentifier.h"
#include "sql_expression/SqlMultiplicativeExpression.h"
#include "sql_expression/SQLNotExpression.h"
#include "sql_expression/SQLOrExpression.h"
#include "sql_expression/SQLParenthesisExpression.h"
#include "sql_expression/SQLRelationalExpression.h"
#include "sql_expression/TableIdentifier.h"
#include "sql_expression/SQLPlaceHolder.h"

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
