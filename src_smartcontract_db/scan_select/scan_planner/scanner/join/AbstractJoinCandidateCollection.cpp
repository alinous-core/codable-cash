/*
 * AbstractJoinCandidateCollection.cpp
 *
 *  Created on: 2020/09/03
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/join/AbstractJoinCandidateCollection.h"

namespace codablecash {

AbstractJoinCandidateCollection::AbstractJoinCandidateCollection(int joinType)
					: AbstractJoinCandidate(joinType) {

}

AbstractJoinCandidateCollection::~AbstractJoinCandidateCollection() {

}

} /* namespace codablecash */
