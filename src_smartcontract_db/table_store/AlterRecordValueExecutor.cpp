/*
 * AlterRecordValueExecutor.cpp
 *
 *  Created on: 2020/10/09
 *      Author: iizuka
 */

#include "table_store/AlterRecordValueExecutor.h"

namespace codablecash {

AlterRecordValueExecutor::AlterRecordValueExecutor(const CdbTableColumn* column) {
	this->column = column;
}

AlterRecordValueExecutor::~AlterRecordValueExecutor() {
	this->column = nullptr;
}

void AlterRecordValueExecutor::addColumn(TableStore* store) {
	// TODO AlterRecordValueExecutor::addNewColumn
}

void AlterRecordValueExecutor::removeColumn(TableStore* store) {
	// TODO AlterRecordValueExecutor::removeColumn
}

} /* namespace codablecash */
