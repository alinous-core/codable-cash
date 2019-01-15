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
	CodeElement();
	virtual ~CodeElement();

	void setPositions(int beginLine, int beginColumn, int endLine, int endColumn);
	void setPositions(Token* token, CodeElement* end);
	void setPosition(CodeElement* end);


protected:
	int beginLine;
	int beginColumn;
	int endLine;
	int endColumn;
};

} /* namespace codablecash */

#endif /* SC_CODEELEMENT_H_ */
