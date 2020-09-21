/*
 * RecordValueConverter.cpp
 *
 *  Created on: 2020/09/21
 *      Author: iizuka
 */

#include "table_store/RecordValueConverter.h"

namespace codablecash {

RecordValueConverter::RecordValueConverter(CdbTableColumn* column) {
	this->column = column;

}

RecordValueConverter::~RecordValueConverter() {
	this->column = nullptr;

}

} /* namespace codablecash */
