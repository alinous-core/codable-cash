/*
 * CodeElement.cpp
 *
 *  Created on: 2019/01/15
 *      Author: iizuka
 */

#include "debug/debugMacros.h"

#include "sc/CodeElement.h"
#include "alinous_lang/Token.h"
#include "sc/CompilationUnit.h"

#include "sc_declare/ClassDeclare.h"
#include "sc_declare/ClassDeclareBlock.h"
#include "sc_declare/PackageDeclare.h"
#include "sc_declare/PackageNameDeclare.h"
#include "sc_declare/MethodDeclare.h"
#include "sc_declare/ArgumentsListDeclare.h"
#include "sc_declare/ArgumentDeclare.h"
#include "sc_declare/MemberVariableDeclare.h"
#include "sc_declare/AccessControlDeclare.h"
#include "sc_declare/ImportsDeclare.h"
#include "sc_declare/ImportDeclare.h"
#include "sc_declare/ClassExtends.h"
#include "sc_declare/ClassImplements.h"
#include "sc_declare/ClassName.h"

#include "sc_declare_types/BoolType.h"
#include "sc_declare_types/ByteType.h"
#include "sc_declare_types/CharType.h"
#include "sc_declare_types/ShortType.h"
#include "sc_declare_types/IntType.h"
#include "sc_declare_types/LongType.h"
#include "sc_declare_types/StringType.h"
#include "sc_declare_types/VoidType.h"
#include "sc_declare_types/ObjectType.h"
#include "sc_declare_types/DomType.h"

#include "sc_statement/StatementBlock.h"
#include "sc_statement/VariableDeclareStatement.h"
#include "sc_statement/SubstitutionStatement.h"
#include "sc_statement/ExpressionStatement.h"
#include "sc_statement/BlankStatement.h"

#include "sc_statement_ctrl/BreakStatement.h"
#include "sc_statement_ctrl/ContinueStatement.h"
#include "sc_statement_ctrl/DoWhileStatement.h"
#include "sc_statement_ctrl/ForStatement.h"
#include "sc_statement_ctrl/IfStatement.h"
#include "sc_statement_ctrl/ReturnStatement.h"
#include "sc_statement_ctrl/WhileStatement.h"

#include "sc_statement_exception/TryStatement.h"
#include "sc_statement_exception/CatchStatement.h"
#include "sc_statement_exception/ThrowStatement.h"
#include "sc_statement_exception/FinallyStatement.h"

#include "sc_expression/AllocationExpression.h"
#include "sc_expression/ArrayReferenceExpression.h"
#include "sc_expression/MemberReferenceExpression.h"
#include "sc_expression/CastExpression.h"
#include "sc_expression/ConstructorArray.h"
#include "sc_expression/ConstructorCall.h"
#include "sc_expression/ParenthesisExpression.h"
#include "sc_expression/VariableIdentifier.h"
#include "sc_expression/FunctionCallExpression.h"

#include "sc_expression_literal/BooleanLiteral.h"
#include "sc_expression_literal/LiteralExpression.h"
#include "sc_expression_literal/NullLiteral.h"
#include "sc_expression_literal/NumberLiteral.h"

#include "sc_expression_bit/AndExpression.h"
#include "sc_expression_bit/BitReverseExpression.h"
#include "sc_expression_bit/OrExpression.h"
#include "sc_expression_bit/ExclusiveOrExpression.h"
#include "sc_expression_bit/ShiftExpression.h"

#include "sc_expression_arithmetic/AddExpression.h"
#include "sc_expression_arithmetic/MultiplicativeExpression.h"
#include "sc_expression_arithmetic/NegateExpression.h"
#include "sc_expression_arithmetic/PostIncrementExpression.h"
#include "sc_expression_arithmetic/PreIncrementExpression.h"

#include "sc_expression_logical/ConditionalAndExpression.h"
#include "sc_expression_logical/ConditionalOrExpression.h"
#include "sc_expression_logical/EqualityExpression.h"
#include "sc_expression_logical/RelationalExpression.h"
#include "sc_expression_logical/NotExpression.h"

#include "sc_expression_json/JsonInitializerExpression.h"
#include "sc_expression_json/JsonArrayExpression.h"
#include "sc_expression_json/JsonKeyValuePairExpression.h"

#include "sql_ddl/CreateTableStatement.h"
#include "sql_ddl/DropTableStatement.h"
#include "sql_ddl/DdlColumnDescriptor.h"
#include "sql_ddl/ColumnTypeDescriptor.h"
#include "sql_ddl/AlterTableStatement.h"

#include "sql_ddl_alter/AlterAddColumnCommand.h"
#include "sql_ddl_alter/AlterAddIndexCommand.h"
#include "sql_ddl_alter/AlterDropColumnCommand.h"
#include "sql_ddl_alter/AlterDropIndexCommand.h"

#include "sql_ddl_alter_modify/AlterAddPrimaryKeyCommand.h"
#include "sql_ddl_alter_modify/AlterDropPrimaryKeyCommand.h"
#include "sql_ddl_alter_modify/AlterModifyCommand.h"
#include "sql_ddl_alter_modify/AlterRenameColumnCommand.h"
#include "sql_ddl_alter_modify/AlterRenameTableCommand.h"

#include "sql_dml/BeginStatement.h"
#include "sql_dml/CommitStatement.h"
#include "sql_dml/DeleteStatement.h"
#include "sql_dml/InsertStatement.h"
#include "sql_dml/RollbackStatement.h"
#include "sql_dml/SelectStatement.h"
#include "sql_dml/UpdateStatement.h"

#include "sql_expression/SQLAdditiveExpression.h"
#include "sql_expression/SQLAndExpression.h"
#include "sql_expression/SQLBooleanLiteral.h"
#include "sql_expression/SQLBetweenExpression.h"
#include "sql_expression/SQLColumnIdentifier.h"
#include "sql_expression/SQLEqualityExpression.h"
#include "sql_expression/SQLExpressionList.h"
#include "sql_expression/SQLFunctionCall.h"
#include "sql_expression/SQLInExpression.h"
#include "sql_expression/SQLIsNullExpression.h"
#include "sql_expression/SQLLikeExpression.h"
#include "sql_expression/SQLLiteral.h"
#include "sql_expression/SqlMultiplicativeExpression.h"
#include "sql_expression/SQLNotExpression.h"
#include "sql_expression/SQLOrExpression.h"
#include "sql_expression/SQLParenthesisExpression.h"
#include "sql_expression/SQLRelationalExpression.h"
#include "sql_expression/SQLPlaceHolder.h"
#include "sql_expression/SQLWildCard.h"

#include "sql_join_parts/TableIdentifier.h"
#include "sql_join_parts/SQLJoin.h"
#include "sql_join_parts/SQLJoinPart.h"
#include "sql_join_parts/TableList.h"
#include "sql_join_parts/ParenthesisJoinPart.h"

#include "sql_dml_parts/SQLColumnsList.h"
#include "sql_dml_parts/SQLFrom.h"
#include "sql_dml_parts/SQLGroupBy.h"
#include "sql_dml_parts/SQLHaving.h"
#include "sql_dml_parts/SQLLimitOffset.h"
#include "sql_dml_parts/SQLOrderBy.h"
#include "sql_dml_parts/SQLSelectTarget.h"
#include "sql_dml_parts/SQLSelectTargetList.h"
#include "sql_dml_parts/SQLSet.h"
#include "sql_dml_parts/SQLSetPair.h"
#include "sql_dml_parts/SQLWhere.h"

#include "base/UnicodeString.h"

#include "sc/exceptions.h"


namespace alinous {

CodeElement::CodeElement(short kind) {
	this->kind = kind;
	this->beginLine = 0;
	this->beginColumn = 0;
	this->endLine = 0;
	this->endColumn = 0;

	this->parent = nullptr;
}

CodeElement::~CodeElement() {
}


void CodeElement::setPositions(int beginLine, int beginColumn, int endLine, int endColumn) {
	this->beginLine = beginLine;
	this->beginColumn = beginColumn;
	this->endLine = endLine;
	this->endColumn = endColumn;
}


void CodeElement::setPositions(Token* token, Token* end) {
	this->beginLine = token->beginLine;
	this->beginColumn = token->beginColumn;
	this->endLine = end->endLine;
	this->endColumn = end->endColumn;
}


void CodeElement::setPositions(Token* token, CodeElement* end) {
	this->beginLine = token->beginLine;
	this->beginColumn = token->beginColumn;
	this->endLine = end->endLine;
	this->endColumn = end->endColumn;
}

void CodeElement::setPosition(CodeElement* element) {
	if(this->beginLine == 0 && this->beginColumn == 0){
		this->beginLine = element->beginLine;
		this->beginColumn = element->beginColumn;
		return;
	}

	this->endLine = element->endLine;
	this->endColumn = element->endColumn;
}

void CodeElement::setPosition(Token* token) {
	if(this->beginLine == 0 && this->beginColumn == 0){
		this->beginLine = token->beginLine;
		this->beginColumn = token->beginColumn;
		return;
	}

	this->endLine = token->endLine;
	this->endColumn = token->endColumn;
}

CodeElement* CodeElement::createFromBinary(ByteBuffer* in) {
	short type = in->getShort();
	CodeElement* element = nullptr;

	switch(type){
	case COMPILANT_UNIT:
		element = new CompilationUnit();
		break;

	case CLASS_DECLARE:
		element = new ClassDeclare();
		break;
	case CLASS_DECLARE_BLOCK:
		element = new ClassDeclareBlock();
		break;
	case PACKAGE_DECLARE:
		element = new PackageDeclare();
		break;
	case PACKAGE_NAME_DECLARE:
		element = new PackageNameDeclare();
		break;
	case METHOD_DECLARE:
		element = new MethodDeclare();
		break;
	case ARGUMENTS_LIST_DECLARE:
		element = new ArgumentsListDeclare();
		break;
	case ARGUMENT_DECLARE:
		element = new ArgumentDeclare();
		break;
	case MEMBER_VARIABLE_DECLARE:
		element = new MemberVariableDeclare();
		break;
	case ACCESS_CONTROL_DECLARE:
		element = new AccessControlDeclare();
		break;
	case IMPORTS_DECLARE:
		element = new ImportsDeclare();
		break;
	case IMPORT_DECLARE:
		element = new ImportDeclare();
		break;
	case CLASS_EXTENDS:
		element = new ClassExtends();
		break;
	case CLASS_IMPLEMENTS:
		element = new ClassImplements();
		break;
	case CLASS_NAME:
		element = new ClassName();
		break;

	case TYPE_BOOL:
		element = new BoolType();
		break;
	case TYPE_BYTE:
		element = new ByteType();
		break;
	case TYPE_CHAR:
		element = new CharType();
		break;
	case TYPE_SHORT:
		element = new ShortType();
		break;
	case TYPE_INT:
		element = new IntType();
		break;
	case TYPE_LONG:
		element = new LongType();
		break;
	case TYPE_STRING:
		element = new StringType();
		break;
	case TYPE_VOID:
		element = new VoidType();
		break;
	case TYPE_OBJECT:
		element = new ObjectType();
		break;
	case TYPE_DOM:
		element = new DomType();
		break;

	case STMT_BLOCK:
		element = new StatementBlock();
		break;
	case STMT_VARIABLE_DECLARE:
		element = new VariableDeclareStatement();
		break;
	case STMT_SUBSTITUTION:
		element = new SubstitutionStatement();
		break;
	case STMT_EXPRESSION:
		element = new ExpressionStatement();
		break;
	case STMT_BLANK:
		element = new BlankStatement();
		break;

	case STMT_BREAK:
		element = new BreakStatement();
		break;
	case STMT_CONTINUE:
		element = new ContinueStatement();
		break;
	case STMT_DO_WHILE:
		element = new DoWhileStatement();
		break;
	case STMT_FOR:
		element = new ForStatement();
		break;
	case STMT_IF:
		element = new IfStatement();
		break;
	case STMT_RETURN:
		element = new ReturnStatement();
		break;
	case STMT_WHILE:
		element = new WhileStatement();
		break;

	case STMT_TRY:
		element = new TryStatement();
		break;
	case STMT_TRY_CATCH:
		element = new CatchStatement();
		break;
	case STMT_THROW:
		element = new ThrowStatement();
		break;
	case STMT_FINALLY:
		element = new FinallyStatement();
		break;

	case EXP_ALLOCATION:
		element = new AllocationExpression();
		break;
	case EXP_ARRAY_REF:
		element = new ArrayReferenceExpression();
		break;
	case EXP_MEMBER_REF:
		element = new MemberReferenceExpression();
		break;
	case EXP_CAST:
		element = new CastExpression();
		break;
	case EXP_LITERAL:
		element = new LiteralExpression();
		break;
	case EXP_NUMBER_LITERAL:
		element = new NumberLiteral();
		break;
	case EXP_BOOLEAN_LITERAL:
		element = new BooleanLiteral();
		break;
	case EXP_NULL_LITERAL:
		element = new NullLiteral();
		break;
	case EXP_PARENTHESIS:
		element = new ParenthesisExpression();
		break;
	case EXP_VARIABLE_ID:
		element = new VariableIdentifier();
		break;

	case EXP_FUNCTIONCALL:
		element = new FunctionCallExpression();
		break;
	case EXP_CONSTRUCTORCALL:
		element = new ConstructorCall();
		break;
	case EXP_CONSTRUCTORARRAY:
		element = new ConstructorArray();
		break;

	case EXP_AND:
		element = new AndExpression();
		break;
	case EXP_BIT_REV:
		element = new BitReverseExpression();
		break;
	case EXP_OR:
		element = new OrExpression();
		break;
	case EXP_EX_OR:
		element = new ExclusiveOrExpression();
		break;
	case EXP_SHIFT:
		element = new ShiftExpression();
		break;

	case EXP_ADD:
		element = new AddExpression();
		break;
	case EXP_MUL:
		element = new MultiplicativeExpression();
		break;
	case EXP_NEGATE:
		element = new NegateExpression();
		break;
	case EXP_POST_INC:
		element = new PostIncrementExpression();
		break;
	case EXP_PRE_INC:
		element = new PreIncrementExpression();
		break;

	case EXP_CND_AND:
		element = new ConditionalAndExpression();
		break;
	case EXP_CND_OR:
		element = new ConditionalOrExpression();
		break;
	case EXP_CND_EQ:
		element = new EqualityExpression();
		break;
	case EXP_CND_RELATIONAL:
		element = new RelationalExpression();
		break;
	case EXP_CND_NOT:
		element = new NotExpression();
		break;

	case EXP_JSON_INITIALIZER:
		element = new JsonInitializerExpression();
		break;
	case EXP_JSON_VALUE_PAIR:
		element = new JsonKeyValuePairExpression();
		break;
	case EXP_JSON_ARRAY:
		element = new JsonArrayExpression();
		break;

	case DDL_CREATE_TABLE:
		element = new CreateTableStatement();
		break;
	case DDL_DROP_TABLE:
		element = new DropTableStatement();
		break;
	case DDL_COLMUN_DESC:
		element = new DdlColumnDescriptor();
		break;
	case DDL_TYPE_DESC:
		element = new ColumnTypeDescriptor();
		break;
	case DDL_ALTER_TABLE:
		element = new AlterTableStatement();
		break;

	case DDL_ALTER_ADD_INDEX:
		element = new AlterAddIndexCommand();
		break;
	case DDL_ALTER_ADD_COLUMN:
		element = new AlterAddColumnCommand();
		break;
	case DDL_ALTER_DROP_INDEX:
		element = new AlterDropIndexCommand();
		break;
	case DDL_ALTER_DROP_COLUMN:
		element = new AlterDropColumnCommand();
		break;

	case DML_STMT_BEGIN:
		element = new BeginStatement();
		break;
	case DML_STMT_COMMIT:
		element = new CommitStatement();
		break;
	case DML_STMT_DELETE:
		element = new DeleteStatement();
		break;
	case DML_STMT_INSERT:
		element = new InsertStatement();
		break;
	case DML_STMT_ROLLBACK:
		element = new RollbackStatement();
		break;
	case DML_STMT_SELECT:
		element = new SelectStatement();
		break;
	case DML_STMT_UPDATE:
		element = new UpdateStatement();
		break;

	case SQL_EXP_ADDITIVE:
		element = new SQLAdditiveExpression();
		break;
	case SQL_EXP_AND:
		element = new SQLAndExpression();
		break;
	case SQL_EXP_BOOL_LITERAL:
		element = new SQLBooleanLiteral();
		break;
	case SQL_EXP_BETWEEN:
		element = new SQLBetweenExpression();
		break;
	case SQL_EXP_COLUMN_ID:
		element = new SQLColumnIdentifier();
		break;
	case SQL_EXP_EQUALITY:
		element = new SQLEqualityExpression();
		break;
	case SQL_EXP_EXP_LIST:
		element = new SQLExpressionList();
		break;
	case SQL_EXP_FUNCTION_CALL:
		element = new SQLFunctionCall();
		break;
	case SQL_EXP_IN:
		element = new SQLInExpression();
		break;
	case SQL_EXP_IS_NULL:
		element = new SQLIsNullExpression();
		break;
	case SQL_EXP_LIKE:
		element = new SQLLikeExpression();
		break;
	case SQL_EXP_LITERAL:
		element = new SQLLiteral();
		break;
	case SQL_EXP_MULTIPLICATIVE:
		element = new SqlMultiplicativeExpression();
		break;
	case SQL_EXP_NOT:
		element = new SQLNotExpression();
		break;
	case SQL_EXP_OR:
		element = new SQLOrExpression();
		break;
	case SQL_EXP_PARENTHESIS:
		element = new SQLParenthesisExpression();
		break;
	case SQL_EXP_RELATIONAL:
		element = new SQLRelationalExpression();
		break;
	case SQL_EXP_TABLE_ID:
		element = new TableIdentifier();
		break;
	case SQL_EXP_PLACE_HOLDER:
		element = new SQLPlaceHolder();
		break;
	case SQL_EXP_JOIN:
		element = new SQLJoin();
		break;
	case SQL_EXP_JOIN_PART:
		element = new SQLJoinPart();
		break;
	case SQL_EXP_TABLE_LIST:
		element = new TableList();
		break;
	case SQL_EXP_PARENTHESIS_JOIN_PART:
		element = new ParenthesisJoinPart();
		break;
	case SQL_EXP_WILDCARD:
		element = new SQLWildCard();
		break;

	case SQL_PART_COLUMN_LIST:
		element = new SQLColumnsList();
		break;
	case SQL_PART_FROM:
		element = new SQLFrom();
		break;
	case SQL_PART_GROUP_BY:
		element = new SQLGroupBy();
		break;
	case SQL_PART_HAVING:
		element = new SQLHaving();
		break;
	case SQL_PART_LIMIT_OFFSET:
		element = new SQLLimitOffset();
		break;
	case SQL_PART_ORDER_BY:
		element = new SQLOrderBy();
		break;
	case SQL_PART_SELECT_TARGET:
		element = new SQLSelectTarget();
		break;
	case SQL_PART_SELECT_TARGET_LIST:
		element = new SQLSelectTargetList();
		break;
	case SQL_PART_SET:
		element = new SQLSet();
		break;
	case SQL_PART_SET_PAIR:
		element = new SQLSetPair();
		break;
	case SQL_PART_WHERE:
		element = new SQLWhere();
		break;

	default:
		throw new MulformattedScBinaryException(__FILE__, __LINE__);
	}

	assert(element->kind == type);

	element->fromBinary(in);

	return element;
}


int CodeElement::stringSize(UnicodeString* str) const noexcept {
	return sizeof(uint32_t) + str->length() * sizeof(uint16_t);
}

void CodeElement::putString(ByteBuffer* out, UnicodeString* str) const noexcept {
	uint32_t maxLoop = str->length();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		wchar_t ch = str->get(i);
		out->putChar(ch);
	}
}

UnicodeString* CodeElement::getString(ByteBuffer* in) const noexcept {
	UnicodeString* ret = new UnicodeString(L"");
	uint32_t maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		wchar_t ch = in->getChar();
		ret->append(ch);
	}

	return ret;
}

void CodeElement::checkNotNull(void* ptr) {
	if(ptr == nullptr){
		throw new MulformattedScBinaryException(L"NullPointer exception", __FILE__, __LINE__);
	}
}

void CodeElement::checkKind(CodeElement* element, short kind) {
	if(element->kind != kind){
		delete element;
		throw new MulformattedScBinaryException(__FILE__, __LINE__);
	}
}

void CodeElement::checkIsType(CodeElement* element) {
	if(!(element->kind >= TYPE_BOOL && element->kind < STMT_BLOCK)){
		delete element;
		throw new MulformattedScBinaryException(__FILE__, __LINE__);
	}
}

void CodeElement::checkIsStatement(CodeElement* element) {
	if(!((element->kind >= STMT_BLOCK && element->kind < EXP_ALLOCATION) ||
			(element->kind >= DDL_CREATE_TABLE && element->kind < SQL_EXP_ADDITIVE))){
		delete element;
		throw new MulformattedScBinaryException(__FILE__, __LINE__);
	}
}

void CodeElement::checkIsExp(CodeElement* element) {
	if(!(element->kind >= EXP_ALLOCATION && element->kind < DDL_CREATE_TABLE)){
		delete element;
		throw new MulformattedScBinaryException(__FILE__, __LINE__);
	}
}

void CodeElement::checkIsJsonExp(CodeElement* element) {
	if(!(element->kind >= EXP_JSON_INITIALIZER && element->kind < DDL_CREATE_TABLE)){
		delete element;
		throw new MulformattedScBinaryException(__FILE__, __LINE__);
	}
}


void CodeElement::checkIsSQLExp(CodeElement* element) {
	if(!(element->kind >= SQL_EXP_ADDITIVE && element->kind < SQL_PART_COLUMN_LIST)){
		delete element;
		throw new MulformattedScBinaryException(__FILE__, __LINE__);
	}
}

void CodeElement::checkIsJoinPart(CodeElement* element) {
	if(!(element->kind == SQL_EXP_PARENTHESIS_JOIN_PART || element->kind == SQL_EXP_JOIN || element->kind == SQL_EXP_JOIN_PART ||
			element->kind == SQL_EXP_TABLE_ID || element->kind == SQL_EXP_TABLE_LIST)){
		delete element;
		throw new MulformattedScBinaryException(__FILE__, __LINE__);
	}
}

void CodeElement::checkIsImport(CodeElement* element) {
	if(!(element->kind == IMPORT_DECLARE)){
		delete element;
		throw new MulformattedScBinaryException(__FILE__, __LINE__);
	}
}


void CodeElement::setParent(CodeElement* parent) noexcept {
	this->parent = parent;
}

CodeElement* CodeElement::getParent() const noexcept {
	return this->parent;
}

CompilationUnit* CodeElement::getCompilationUnit() const {
	CodeElement* element = this->parent;
	while(element != nullptr && element->kind != CodeElement::COMPILANT_UNIT){
		element = element->getParent();
	}

	if(element == nullptr){
		throw new MulformattedScBinaryException(__FILE__, __LINE__);
	}

	return dynamic_cast<CompilationUnit*>(element);
}

short CodeElement::getKind() const noexcept {
	return this->kind;
}

ClassDeclare* CodeElement::getClassDeclare() const {
	CodeElement* element = this->parent;
	while(element != nullptr && element->kind != CodeElement::CLASS_DECLARE){
		element = element->getParent();
	}

	if(element == nullptr){
		throw new MulformattedScBinaryException(__FILE__, __LINE__);
	}

	return dynamic_cast<ClassDeclare*>(element);
}



const UnicodeString* CodeElement::getPackageName() const noexcept {
	CompilationUnit* unit = getCompilationUnit();

	return unit->getPackageName();
}

bool CodeElement::isExecutable() {
	return false;
}

} /* namespace alinous */
