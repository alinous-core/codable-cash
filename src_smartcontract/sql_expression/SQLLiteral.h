/*
 * SQLLiteral.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_SQLLITERAL_H_
#define SQL_EXPRESSION_SQLLITERAL_H_

#include "sql/AbstractSQLExpression.h"
#include <cstdint>

namespace alinous {
class UnicodeString;

class SQLLiteral : public AbstractSQLExpression {
public:
	static const constexpr uint8_t TYPE_STRING{1};
	static const constexpr uint8_t TYPE_NUMBER{2};

	SQLLiteral();
	virtual ~SQLLiteral();

	void setValue(UnicodeString* value, uint8_t type) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
private:
	UnicodeString* value;
	uint8_t type;
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_SQLLITERAL_H_ */
