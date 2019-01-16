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

namespace codablecash {
using namespace alinouslang;

class CodeElement {
public:
	static const constexpr short COMPILANT_UNIT{0};

	static const constexpr short CLASS_DECLARE{1};
	static const constexpr short CLASS_DECLARE_BLOCK{2};


	CodeElement(short kind);
	virtual ~CodeElement();

	void setPositions(int beginLine, int beginColumn, int endLine, int endColumn);
	void setPositions(Token* token, CodeElement* end);
	void setPosition(CodeElement* end);

protected:
	short kind;

	int beginLine;
	int beginColumn;
	int endLine;
	int endColumn;
};

} /* namespace codablecash */

#endif /* SC_CODEELEMENT_H_ */
