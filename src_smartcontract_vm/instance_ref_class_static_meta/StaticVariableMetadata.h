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
class StaticClassMetadata;

class StaticVariableMetadata {
public:
	StaticVariableMetadata(int index, MemberVariableDeclare* val, StaticClassMetadata* parent);
	virtual ~StaticVariableMetadata();

	AnalyzedType getAnalyzedType() const noexcept;
	int getIndex() const noexcept;
	StaticClassMetadata* getParent() const noexcept;

private:
	int index;
	MemberVariableDeclare* val;
	StaticClassMetadata* parent;
};

} /* namespace alinous */

#endif /* INSTANCE_REF_CLASS_STATIC_META_STATICVARIABLEMETADATA_H_ */
