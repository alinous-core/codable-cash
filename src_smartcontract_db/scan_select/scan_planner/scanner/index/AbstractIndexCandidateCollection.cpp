/*
 * AbstractIndexCandidateCollection.cpp
 *
 *  Created on: 2020/09/07
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/index/AbstractIndexCandidateCollection.h"

namespace codablecash {

AbstractIndexCandidateCollection::AbstractIndexCandidateCollection(IndexType indexType) : AbstractIndexCandidate(indexType) {

}

AbstractIndexCandidateCollection::~AbstractIndexCandidateCollection() {

}

} /* namespace codablecash */
