/*
 * AbstractIndexCandidate.cpp
 *
 *  Created on: 2020/09/07
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/index/AbstractIndexCandidate.h"

namespace codablecash {

AbstractIndexCandidate::AbstractIndexCandidate(IndexType indexType) {
	this->indexType = indexType;
}

AbstractIndexCandidate::~AbstractIndexCandidate() {

}

} /* namespace codablecash */
