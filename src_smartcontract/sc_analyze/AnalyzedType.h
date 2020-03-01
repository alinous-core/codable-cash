/*
 * AnalyzedType.h
 *
 *  Created on: 2019/06/11
 *      Author: iizuka
 */

#ifndef SC_ANALYZE_ANALYZEDTYPE_H_
#define SC_ANALYZE_ANALYZEDTYPE_H_
#include <cstdint>

namespace alinous {

class AnalyzedClass;
class UnicodeString;

class AnalyzedType {
public:
	static const constexpr short TYPE_NULL{0};

	static const constexpr short TYPE_BOOL{20};
	static const constexpr short TYPE_BYTE{21};
	static const constexpr short TYPE_CHAR{22};
	static const constexpr short TYPE_SHORT{23};
	static const constexpr short TYPE_INT{24};
	static const constexpr short TYPE_LONG{25};
	static const constexpr short TYPE_STRING{26};
	static const constexpr short TYPE_VOID{27};
	static const constexpr short TYPE_OBJECT{28};

	static const UnicodeString SIG_BOOL;
	static const UnicodeString SIG_BYTE;
	static const UnicodeString SIG_CHAR;
	static const UnicodeString SIG_SHORT;
	static const UnicodeString SIG_INT;
	static const UnicodeString SIG_LONG;
	static const UnicodeString SIG_STRING;

	AnalyzedType(const AnalyzedType& obj); // copy constructor

	explicit AnalyzedType(uint8_t type);
	explicit AnalyzedType(AnalyzedClass* clazz);
	AnalyzedType();

	virtual ~AnalyzedType();

	AnalyzedClass* getAnalyzedClass() const noexcept;
	uint8_t getType() const noexcept;
	const UnicodeString* stringName() noexcept;
	const UnicodeString* getSignatureName() noexcept;

	bool isVoid() const noexcept;

	void setDim(int dim) noexcept;
	int getDim() const noexcept;
	bool isArray() const noexcept;

	bool equals(AnalyzedType* other) const noexcept;
private:
	void makeStringName() noexcept;
	void makeObjectString() noexcept;

private:
	uint8_t type;
	AnalyzedClass* aclazz; // reference
	int dim;

	UnicodeString* str;
};

} /* namespace alinous */

#endif /* SC_ANALYZE_ANALYZEDTYPE_H_ */
