/*
 * ParenthesisJoinPart.h
 *
 *  Created on: 2019/02/28
 *      Author: iizuka
 */

#ifndef SQL_JOIN_PARTS_PARENTHESISJOINPART_H_
#define SQL_JOIN_PARTS_PARENTHESISJOINPART_H_

#include "sql/AbstractJoinPart.h"

namespace alinous {

class ParenthesisJoinPart : public AbstractJoinPart {
public:
	ParenthesisJoinPart();
	virtual ~ParenthesisJoinPart();

	void setPart(AbstractJoinPart* part) noexcept;
private:
	AbstractJoinPart* part;
};

} /* namespace alinous */

#endif /* SQL_JOIN_PARTS_PARENTHESISJOINPART_H_ */
