/*
 * ColumnIdentifierColumn.cpp
 *
 *  Created on: 2020/07/21
 *      Author: iizuka
 */

#include "scan_condition_params/ColumnIdentifierScanParam.h"

namespace codablecash {

ColumnIdentifierScanParam::ColumnIdentifierScanParam(SQLColumnIdentifier* sqlColId) : sqlColId(sqlColId){
	this->cdbColumn = nullptr;
}

ColumnIdentifierScanParam::~ColumnIdentifierScanParam() {

}

} /* namespace codablecash */
