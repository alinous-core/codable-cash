/*
 * AnalyzedColumn.cpp
 *
 *  Created on: 2020/06/15
 *      Author: iizuka
 */

#include "sc_analyze_sql/AnalyzedInsertColumn.h"

#include "table/CdbTableColumn.h"


namespace alinous {

AnalyzedInsertColumn::AnalyzedInsertColumn(const CdbTableColumn* column) {
	this->column = new CdbTableColumn(*column);
}

AnalyzedInsertColumn::~AnalyzedInsertColumn() {
	delete this->column;
}

} /* namespace alinous */
