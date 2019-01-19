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
	static const constexpr short ARGUMENT_DECLARE{6};
	static const constexpr short MEMBER_VARIABLE_DECLARE{7};
	static const constexpr short TYPE_DECLARE{8};
	static const constexpr short ACCESS_CONTROL_DECLARE{9};


	static const constexpr short TYPE_CHAR{20};
	static const constexpr short TYPE_SHORT{21};
	static const constexpr short TYPE_INT{22};
	static const constexpr short TYPE_LONG{23};
	static const constexpr short TYPE_STRING{24};
	static const constexpr short TYPE_VOID{25};


	explicit CodeElement(short kind);
	virtual ~CodeElement();

	void setPositions(int beginLine, int beginColumn, int endLine, int endColumn);
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
