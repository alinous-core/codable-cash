/*
 * AbstractJoinCandidateCollection.h
 *
 *  Created on: 2020/09/03
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_CTX_JOIN_ABSTRACTJOINCANDIDATECOLLECTION_H_
#define SCAN_PLANNER_SCANNER_CTX_JOIN_ABSTRACTJOINCANDIDATECOLLECTION_H_

#include "scan_select/scan_planner/scanner/join/AbstractJoinCandidate.h"

namespace codablecash {

class JoinCandidate;
class AbstractCdbKey;
class CdbRecord;

class AbstractJoinCandidateCollection : public AbstractJoinCandidate {
public:
	explicit AbstractJoinCandidateCollection(int joinType);
	virtual ~AbstractJoinCandidateCollection();

	virtual int size() const noexcept = 0;
	virtual const JoinCandidate* get(int i) const noexcept = 0;
	virtual AbstractCdbKey* makeKeyFromRecord(const CdbRecord* leftRecord) const noexcept = 0;
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_CTX_JOIN_ABSTRACTJOINCANDIDATECOLLECTION_H_ */
