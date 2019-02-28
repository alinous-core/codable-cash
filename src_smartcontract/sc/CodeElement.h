/*
 * CodeElement.h
 *
 *  Created on: 2019/01/15
 *      Author: iizuka
 */

#ifndef SC_CODEELEMENT_H_
#define SC_CODEELEMENT_H_

namespace alinouslang {
class Token;
}

namespace alinous {
using namespace alinouslang;

class CodeElement {
public:
	static const constexpr short COMPILANT_UNIT{0};

	static const constexpr short CLASS_DECLARE{1};
	static const constexpr short CLASS_DECLARE_BLOCK{2};
	static const constexpr short PACKAGE_DECLARE{3};
	static const constexpr short PACKAGE_NAME_DECLARE{4};
	static const constexpr short METHOD_DECLARE{5};
	static const constexpr short ARGUMENTS_LIST_DECLARE{6};
	static const constexpr short ARGUMENT_DECLARE{7};
	static const constexpr short MEMBER_VARIABLE_DECLARE{8};
	static const constexpr short ACCESS_CONTROL_DECLARE{9};


	static const constexpr short TYPE_CHAR{20};
	static const constexpr short TYPE_SHORT{21};
	static const constexpr short TYPE_INT{22};
	static const constexpr short TYPE_LONG{23};
	static const constexpr short TYPE_STRING{24};
	static const constexpr short TYPE_VOID{25};

	static const constexpr short STMT_BLOCK{50};
	static const constexpr short STMT_VARIABLE_DECLARE{51};
	static const constexpr short STMT_SUBSTITUTION{52};
	static const constexpr short STMT_EXPRESSION{53};
	static const constexpr short STMT_BLANK{54};

	static const constexpr short STMT_BREAK{60};
	static const constexpr short STMT_CONTINUE{61};
	static const constexpr short STMT_DO_WHILE{62};
	static const constexpr short STMT_FOR{63};
	static const constexpr short STMT_IF{64};
	static const constexpr short STMT_RETURN{65};
	static const constexpr short STMT_WHILE{66};


	static const constexpr short EXP_ALLOCATION{80};
	static const constexpr short EXP_ARRAY_REF{81};
	static const constexpr short EXP_MEMBER_REF{82};
	static const constexpr short EXP_CAST{83};
	static const constexpr short EXP_LITERAL{84};
	static const constexpr short EXP_NUMBER_LITERAL{85};
	static const constexpr short EXP_BOOLEAN_LITERAL{86};
	static const constexpr short EXP_NULL_LITERAL{87};
	static const constexpr short EXP_PARENTHESIS{88};
	static const constexpr short EXP_VARIABLE_ID{89};

	static const constexpr short EXP_FUNCTIONCALL{100};

	static const constexpr short EXP_AND{110};
	static const constexpr short EXP_BIT_REV{111};
	static const constexpr short EXP_OR{112};
	static const constexpr short EXP_EX_OR{113};
	static const constexpr short EXP_SHIFT{114};

	static const constexpr short EXP_ADD{120};
	static const constexpr short EXP_MUL{121};
	static const constexpr short EXP_NEGATE{122};
	static const constexpr short EXP_POST_INC{123};
	static const constexpr short EXP_PRE_INC{124};

	static const constexpr short EXP_CND_AND{130};
	static const constexpr short EXP_CND_OR{131};
	static const constexpr short EXP_CND_EQ{132};
	static const constexpr short EXP_CND_RELATIONAL{133};
	static const constexpr short EXP_CND_NOT{134};

	static const constexpr short DDL_CREATE_TABLE{150};
	static const constexpr short DDL_DROP_TABLE{151};

	static const constexpr short DML_STMT_BEGIN{160};
	static const constexpr short DML_STMT_COMMIT{161};
	static const constexpr short DML_STMT_DELETE{162};
	static const constexpr short DML_STMT_INSERT{163};
	static const constexpr short DML_STMT_ROLLBACK{164};
	static const constexpr short DML_STMT_SELECT{165};
	static const constexpr short DML_STMT_UPDATE{166};

	static const constexpr short SQL_EXP_ADDITIVE{180};
	static const constexpr short SQL_EXP_AND{181};
	static const constexpr short SQL_EXP_BOOL_LITERAL{182};
	static const constexpr short SQL_EXP_BETWEEN{183};
	static const constexpr short SQL_EXP_COLUMN_ID{184};
	static const constexpr short SQL_EXP_EQUALITY{185};
	static const constexpr short SQL_EXP_EXP_LIST{186};
	static const constexpr short SQL_EXP_FUNCTION_CALL{187};
	static const constexpr short SQL_EXP_IN{188};
	static const constexpr short SQL_EXP_IS_NULL{189};
	static const constexpr short SQL_EXP_LIKE{190};
	static const constexpr short SQL_EXP_LITERAL{191};
	static const constexpr short SQL_EXP_MULTIPLICATIVE{192};
	static const constexpr short SQL_EXP_NOT{193};
	static const constexpr short SQL_EXP_OR{194};
	static const constexpr short SQL_EXP_PARENTHESIS{195};
	static const constexpr short SQL_EXP_RELATIONAL{196};
	static const constexpr short SQL_EXP_TABLE_ID{197};
	static const constexpr short SQL_EXP_PLACE_HOLDER{198};
	static const constexpr short SQL_EXP_JOIN{199};
	static const constexpr short SQL_EXP_JOIN_PART{200};
	static const constexpr short SQL_EXP_TABLE_LIST{201};
	static const constexpr short SQL_EXP_PARENTHESIS_JOIN_PART{202};

	static const constexpr short SQL_PART{220};

	explicit CodeElement(short kind);
	virtual ~CodeElement();

	void setPositions(int beginLine, int beginColumn, int endLine, int endColumn);
	void setPositions(Token* token, Token* end);
	void setPositions(Token* token, CodeElement* end);
	void setPosition(CodeElement* element);
	void setPosition(Token* token);

protected:
	short kind;

	int beginLine;
	int beginColumn;
	int endLine;
	int endColumn;
};

} /* namespace alinous */

#endif /* SC_CODEELEMENT_H_ */
