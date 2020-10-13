/*
 * LongIntegerKey.h
 *
 *  Created on: 2019/11/14
 *      Author: iizuka
 */

#ifndef INSTANCE_REF_STATIC_LONGINTEGERKEY_H_
#define INSTANCE_REF_STATIC_LONGINTEGERKEY_H_
#include <cstdint>

namespace alinous {

class PrimitiveReference;

class LongIntegerKey {
public:
	LongIntegerKey(int64_t value);
	virtual ~LongIntegerKey();

	int hashCode() const noexcept;
	int compareTo(const LongIntegerKey* object) const noexcept;
	class ValueCompare {
	public:
		int operator() (const LongIntegerKey* const _this, const  LongIntegerKey* const object) const noexcept;
	};
private:
	int64_t value;
};

} /* namespace alinous */

#endif /* INSTANCE_REF_STATIC_LONGINTEGERKEY_H_ */
