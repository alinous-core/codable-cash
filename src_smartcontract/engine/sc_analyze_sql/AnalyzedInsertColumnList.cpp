/*
 * AnalyzedInsertColumnList.cpp
 *
 *  Created on: 2020/06/15
 *      Author: iizuka
 */

#include "sc_analyze_sql/AnalyzedInsertColumnList.h"
#include "sc_analyze_sql/AnalyzedInsertColumn.h"

namespace alinous {

AnalyzedInsertColumnList::AnalyzedInsertColumnList() {

}

AnalyzedInsertColumnList::~AnalyzedInsertColumnList() {
	this->list.deleteElements();
}

void AnalyzedInsertColumnList::addAnalyzedInsertColumn(AnalyzedInsertColumn* col) noexcept {
	this->list.addElement(col);
}

int AnalyzedInsertColumnList::size() const noexcept {
	return this->list.size();
}

AnalyzedInsertColumn* AnalyzedInsertColumnList::get(int i) const noexcept {
	return this->list.get(i);
}


} /* namespace alinous */
