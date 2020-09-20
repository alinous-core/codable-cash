/*
 * ColumnModifyContext.h
 *
 *  Created on: 2020/09/19
 *      Author: iizuka
 */

#ifndef SCHEMA_COLUMNMODIFYCONTEXT_H_
#define SCHEMA_COLUMNMODIFYCONTEXT_H_
#include <cstdint>

namespace alinous {
class UnicodeString;
}
using namespace alinous;

namespace codablecash {

class CdbTableColumn;
class CdbTableIndex;

class ColumnModifyContext {
public:
	typedef enum __UniqueChage{
		UNIQUE_NONE, TO_UNIQUE, TO_NOT_UNIQUE
	} UniqueChage;

	typedef enum __NotNullChage{
		NOTNULL_NONE, TO_NOT_NULL, RELEASE_NOT_NULL
	} NotNullChage;

	ColumnModifyContext();
	virtual ~ColumnModifyContext();

	UniqueChage getUniqueChange() const noexcept {
		return uniqueChange;
	}

	void setUniqueChange(UniqueChage uniqueChange) noexcept {
		this->uniqueChange = uniqueChange;
	}
	void setNotNullChange(NotNullChage notNullChange) noexcept {
		this->notNullChange = notNullChange;
	}

	uint8_t getCdbType() const noexcept {
		return cdbType;
	}

	void setCdbType(uint8_t cdbType) noexcept {
		this->cdbType = cdbType;
	}

	int64_t getLength() const noexcept {
		return length;
	}

	void setLength(int64_t length) noexcept {
		this->length = length;
	}

	bool isTypeChanged() const noexcept {
		return typeChanged;
	}

	void setTypeChanged(bool typeChanged) noexcept {
		this->typeChanged = typeChanged;
	}

	void setDefaultValue(const UnicodeString* defalutValueStr) noexcept;
	const UnicodeString* getDefalutValueStr() const noexcept {
		return defalutValueStr;
	}

	CdbTableColumn* getColumn() const noexcept {
		return column;
	}
	void setColumn(CdbTableColumn* column) noexcept {
		this->column = column;
	}

	CdbTableIndex* getNewIndex() const noexcept {
		return newIndex;
	}
	void setNewIndex(CdbTableIndex* newIndex) noexcept {
		this->newIndex = newIndex;
	}

private:
	UniqueChage uniqueChange;
	NotNullChage notNullChange;

	bool typeChanged;
	uint8_t cdbType;
	int64_t length;
	UnicodeString* defalutValueStr;

	CdbTableColumn* column;
	CdbTableIndex* newIndex;
};

} /* namespace codablecash */

#endif /* SCHEMA_COLUMNMODIFYCONTEXT_H_ */
