/*
 * SQLJoinPart.h
 *
 *  Created on: 2019/02/25
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_SQLJOINPART_H_
#define SQL_EXPRESSION_SQLJOINPART_H_

#include <cstdint>
#include "sql/AbstractJoinPart.h"

namespace alinous {

class SQLJoinPart : public AbstractJoinPart {
public:
	static const constexpr uint8_t LEFT_OUTER_JOIN{1};
	static const constexpr uint8_t RIGHT_OUTER_JOIN{2};
	static const constexpr uint8_t INNER_JOIN{3};
	static const constexpr uint8_t CROSS_JOIN{3};

	SQLJoinPart();
	virtual ~SQLJoinPart();

	void setJoinType(uint8_t joinType) noexcept;
private:
	uint8_t joinType;
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_SQLJOINPART_H_ */
