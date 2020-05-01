/*
 * StaticVariableMetadata.h
 *
 *  Created on: 2020/04/30
 *      Author: iizuka
 */

#ifndef INSTANCE_REF_CLASS_STATIC_META_STATICVARIABLEMETADATA_H_
#define INSTANCE_REF_CLASS_STATIC_META_STATICVARIABLEMETADATA_H_

namespace alinous {

class MemberVariableDeclare;
class AnalyzedType;

class StaticVariableMetadata {
public:
	StaticVariableMetadata(int index, MemberVariableDeclare* val);
	virtual ~StaticVariableMetadata();

	AnalyzedType getAnalyzedType() const noexcept;
private:
	int index;
	MemberVariableDeclare* val;
};

} /* namespace alinous */

#endif /* INSTANCE_REF_CLASS_STATIC_META_STATICVARIABLEMETADATA_H_ */
