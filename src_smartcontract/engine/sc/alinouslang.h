/*
 * alinouslang.h
 *
 *  Created on: 2019/01/15
 *      Author: iizuka
 */

#ifndef SC_ALINOUSLANG_H_
#define SC_ALINOUSLANG_H_

#include "base/UnicodeString.h"

#include "engine/sc/CompilationUnit.h"

#include "lang/sc_declare/AccessControlDeclare.h"
#include "lang/sc_declare/ArgumentsListDeclare.h"
#include "lang/sc_declare/ArgumentDeclare.h"
#include "lang/sc_declare/ClassDeclare.h"
#include "lang/sc_declare/ClassDeclareBlock.h"
#include "lang/sc_declare/MemberVariableDeclare.h"
#include "lang/sc_declare/MethodDeclare.h"
#include "lang/sc_declare/PackageDeclare.h"
#include "lang/sc_declare/PackageNameDeclare.h"
#include "lang/sc_declare/ImportsDeclare.h"
#include "lang/sc_declare/ImportDeclare.h"
#include "lang/sc_declare/ClassExtends.h"
#include "lang/sc_declare/ClassImplements.h"
#include "lang/sc_declare/ClassName.h"

#include "lang/sc_declare_types/BoolType.h"
#include "lang/sc_declare_types/ByteType.h"
#include "lang/sc_declare_types/CharType.h"
#include "lang/sc_declare_types/ShortType.h"
#include "lang/sc_declare_types/IntType.h"
#include "lang/sc_declare_types/LongType.h"
#include "lang/sc_declare_types/StringType.h"
#include "lang/sc_declare_types/VoidType.h"
#include "lang/sc_declare_types/ObjectType.h"
#include "lang/sc_declare_types/DomType.h"

#include "lang/sc_statement/ExpressionStatement.h"
#include "lang/sc_statement/StatementBlock.h"
#include "lang/sc_statement/BlankStatement.h"
#include "lang/sc_statement/SubstitutionStatement.h"
#include "lang/sc_statement/VariableDeclareStatement.h"

#include "lang/sc_statement_ctrl/BreakStatement.h"
#include "lang/sc_statement_ctrl/ContinueStatement.h"
#include "lang/sc_statement_ctrl/DoWhileStatement.h"
#include "lang/sc_statement_ctrl/ForStatement.h"
#include "lang/sc_statement_ctrl/IfStatement.h"
#include "lang/sc_statement_ctrl/ReturnStatement.h"
#include "lang/sc_statement_ctrl/WhileStatement.h"

#include "lang/sc_statement_exception/TryStatement.h"
#include "lang/sc_statement_exception/CatchStatement.h"
#include "lang/sc_statement_exception/FinallyStatement.h"
#include "lang/sc_statement_exception/ThrowStatement.h"

#include "lang/sc_expression/AllocationExpression.h"
#include "lang/sc_expression/ArrayReferenceExpression.h"
#include "lang/sc_expression/CastExpression.h"
#include "lang/sc_expression/ConstructorArray.h"
#include "lang/sc_expression/ConstructorCall.h"
#include "lang/sc_expression/FunctionCallExpression.h"
#include "lang/sc_expression/MemberReferenceExpression.h"
#include "lang/sc_expression/ParenthesisExpression.h"
#include "lang/sc_expression/VariableIdentifier.h"

#include "lang/sc_expression_literal/BooleanLiteral.h"
#include "lang/sc_expression_literal/LiteralExpression.h"
#include "lang/sc_expression_literal/NullLiteral.h"
#include "lang/sc_expression_literal/NumberLiteral.h"

#include "lang/sc_expression_arithmetic/AddExpression.h"
#include "lang/sc_expression_arithmetic/MultiplicativeExpression.h"
#include "lang/sc_expression_arithmetic/NegateExpression.h"
#include "lang/sc_expression_arithmetic/PostIncrementExpression.h"
#include "lang/sc_expression_arithmetic/PreIncrementExpression.h"

#include "lang/sc_expression_bit/AndExpression.h"
#include "lang/sc_expression_bit/BitReverseExpression.h"
#include "lang/sc_expression_bit/ExclusiveOrExpression.h"
#include "lang/sc_expression_bit/OrExpression.h"
#include "lang/sc_expression_bit/ShiftExpression.h"

#include "lang/sc_expression_logical/ConditionalAndExpression.h"
#include "lang/sc_expression_logical/ConditionalOrExpression.h"
#include "lang/sc_expression_logical/EqualityExpression.h"
#include "lang/sc_expression_logical/NotExpression.h"
#include "lang/sc_expression_logical/RelationalExpression.h"

#include "lang/sc_expression_json/JsonInitializerExpression.h"
#include "lang/sc_expression_json/JsonArrayExpression.h"
#include "lang/sc_expression_json/JsonKeyValuePairExpression.h"

#include "lang_sql/sql_ddl/CreateTableStatement.h"
#include "lang_sql/sql_ddl/DropTableStatement.h"
#include "lang_sql/sql_ddl/ColumnTypeDescriptor.h"
#include "lang_sql/sql_ddl/DdlColumnDescriptor.h"
#include "lang_sql/sql_ddl/AlterTableStatement.h"

#include "lang_sql/sql_ddl_alter/AlterAddColumnCommand.h"
#include "lang_sql/sql_ddl_alter/AlterAddIndexCommand.h"
#include "lang_sql/sql_ddl_alter/AlterDropColumnCommand.h"
#include "lang_sql/sql_ddl_alter/AlterDropIndexCommand.h"

#include "lang_sql/sql_ddl_alter_modify/AlterAddPrimaryKeyCommand.h"
#include "lang_sql/sql_ddl_alter_modify/AlterDropPrimaryKeyCommand.h"
#include "lang_sql/sql_ddl_alter_modify/AlterModifyCommand.h"
#include "lang_sql/sql_ddl_alter_modify/AlterRenameColumnCommand.h"
#include "lang_sql/sql_ddl_alter_modify/AlterRenameTableCommand.h"

#include "lang_sql/sql_dml/BeginStatement.h"
#include "lang_sql/sql_dml/CommitStatement.h"
#include "lang_sql/sql_dml/DeleteStatement.h"
#include "lang_sql/sql_dml/InsertStatement.h"
#include "lang_sql/sql_dml/RollbackStatement.h"
#include "lang_sql/sql_dml/SelectStatement.h"
#include "lang_sql/sql_dml/UpdateStatement.h"

#include "lang_sql/sql_dml_parts/SQLColumnsList.h"
#include "lang_sql/sql_dml_parts/SQLFrom.h"
#include "lang_sql/sql_dml_parts/SQLGroupBy.h"
#include "lang_sql/sql_dml_parts/SQLHaving.h"
#include "lang_sql/sql_dml_parts/SQLLimitOffset.h"
#include "lang_sql/sql_dml_parts/SQLOrderBy.h"
#include "lang_sql/sql_dml_parts/SQLSelectTarget.h"
#include "lang_sql/sql_dml_parts/SQLSelectTargetList.h"
#include "lang_sql/sql_dml_parts/SQLSet.h"
#include "lang_sql/sql_dml_parts/SQLSetPair.h"
#include "lang_sql/sql_dml_parts/SQLWhere.h"

#include "lang_sql/sql_expression/SQLAdditiveExpression.h"
#include "lang_sql/sql_expression/SQLAndExpression.h"
#include "lang_sql/sql_expression/SQLBetweenExpression.h"
#include "lang_sql/sql_expression/SQLBooleanLiteral.h"
#include "lang_sql/sql_expression/SQLFunctionCall.h"
#include "lang_sql/sql_expression/SQLLiteral.h"
#include "lang_sql/sql_expression/SQLLikeExpression.h"
#include "lang_sql/sql_expression/SQLIsNullExpression.h"
#include "lang_sql/sql_expression/SQLInExpression.h"
#include "lang_sql/sql_expression/SQLExpressionList.h"
#include "lang_sql/sql_expression/SQLEqualityExpression.h"
#include "lang_sql/sql_expression/SQLColumnIdentifier.h"
#include "lang_sql/sql_expression/SqlMultiplicativeExpression.h"
#include "lang_sql/sql_expression/SQLNotExpression.h"
#include "lang_sql/sql_expression/SQLOrExpression.h"
#include "lang_sql/sql_expression/SQLParenthesisExpression.h"
#include "lang_sql/sql_expression/SQLRelationalExpression.h"
#include "lang_sql/sql_expression/SQLPlaceHolder.h"
#include "lang_sql/sql_expression/SQLWildCard.h"
#include "lang_sql/sql_expression/SQLNullLiteral.h"

#include "lang_sql/sql_join_parts/ParenthesisJoinPart.h"
#include "lang_sql/sql_join_parts/SQLJoin.h"
#include "lang_sql/sql_join_parts/SQLJoinPart.h"
#include "lang_sql/sql_join_parts/TableIdentifier.h"
#include "lang_sql/sql_join_parts/TableList.h"


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
