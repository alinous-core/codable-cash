/*
 * AnalyzedColumn.cpp
 *
 *  Created on: 2020/06/15
 *      Author: iizuka
 */

#include "engine/sc_analyze_sql/AnalyzedInsertColumn.h"

#include "schema_table/table/CdbTableColumn.h"


namespace alinous {

AnalyzedInsertColumn::AnalyzedInsertColumn(const CdbTableColumn* column) {
	this->column = new CdbTableColumn(*column);
}

AnalyzedInsertColumn::~AnalyzedInsertColumn() {
	delete this->column;
}

int AnalyzedInsertColumn::getPosition() const noexcept {
	return this->column->getPosition();
}

uint8_t AnalyzedInsertColumn::getCdbColumnType() const noexcept {
	return this->column->getType();
}

} /* namespace alinous */
