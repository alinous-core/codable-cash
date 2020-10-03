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
class AbstractCdbValue;

class ColumnModifyContext {
public:
	typedef enum __UniqueChage{
		UNIQUE_NONE, TO_UNIQUE, TO_NOT_UNIQUE
	} UniqueChage;

	typedef enum __NotNullChage{
		NOTNULL_NONE, TO_NOT_NULL, RELEASE_NOT_NULL
	} NotNullChage;

	typedef enum __LengthChange{
		LENGTH_NO_CHANGE, LENGTH_CHANGE_SHORTER, LENGTH_CHANGE_LONGER
	} LengthChange;

	ColumnModifyContext();
	virtual ~ColumnModifyContext();

	void analyze();

	UniqueChage getUniqueChange() const noexcept {
		return uniqueChange;
	}
	void setUniqueChange(UniqueChage uniqueChange) noexcept {
		this->uniqueChange = uniqueChange;
	}

	void setNotNullChange(NotNullChage notNullChange) noexcept {
		this->notNullChange = notNullChange;
	}
	NotNullChage getNotNullChange() const {
		return notNullChange;
	}

	void setLengthChange(LengthChange lengthChange) noexcept {
		this->lengthChange = lengthChange;
	}

	LengthChange getLengthChange() const noexcept {
		return this->lengthChange;
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

	CdbTableIndex* getRemovalIndex() const noexcept {
		return removalIndex;
	}
	void setRemovalIndex(CdbTableIndex* removalIndex) noexcept {
		this->removalIndex = removalIndex;
	}

	const AbstractCdbValue* getDefaultValue() const noexcept {
		return this->defaultValue;
	}

	bool isDefaultChanged() const noexcept {
		return defaultChanged;
	}

	void setDefaultChanged(bool defaultChanged) noexcept {
		this->defaultChanged = defaultChanged;
	}

	bool isNotNull() const noexcept {
		return notNull;
	}

	void setNotNull(bool notNull) noexcept {
		this->notNull = notNull;
	}

	bool isUnique() const noexcept {
		return unique;
	}

	void setUnique(bool unique) noexcept {
		this->unique = unique;
	}



private:
	void analyzeDefaultValue();

private:
	UniqueChage uniqueChange;
	NotNullChage notNullChange;
	LengthChange lengthChange;

	bool notNull;
	bool unique;

	bool typeChanged;
	uint8_t cdbType;
	int64_t length;
	UnicodeString* defalutValueStr;

	CdbTableColumn* column;
	CdbTableIndex* newIndex;
	CdbTableIndex* removalIndex;

	bool defaultChanged;

	// analyzed value
	AbstractCdbValue* defaultValue;
};

} /* namespace codablecash */

#endif /* SCHEMA_COLUMNMODIFYCONTEXT_H_ */
