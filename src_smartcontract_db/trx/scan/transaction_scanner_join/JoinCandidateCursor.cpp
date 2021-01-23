/*
 * JoinCandidateCursor.cpp
 *
 *  Created on: 2021/01/23
 *      Author: iizuka
 */

#include "trx/scan/transaction_scanner_join/JoinCandidateCursor.h"

#include "scan_select/scan_planner/scanner/join/AbstractJoinCandidateCollection.h"
#include "scan_select/scan_planner/scanner/join/AbstractJoinCandidate.h"
#include "scan_select/scan_planner/scanner/join/JoinOrCandidate.h"

namespace codablecash {

JoinCandidateCursor::JoinCandidateCursor(AbstractJoinCandidate* joinCandidat) {
	this->joinCandidate = joinCandidat;
	this->pos = 0;
}

JoinCandidateCursor::~JoinCandidateCursor() {
	this->joinCandidate = nullptr;
}

void JoinCandidateCursor::init() noexcept {
	AbstractJoinCandidate::CandidateType candidateType = this->joinCandidate->getCandidateType();

	if(candidateType == AbstractJoinCandidate::CandidateType::OR){
		JoinOrCandidate* orCandidate = dynamic_cast<JoinOrCandidate*>(this->joinCandidate);

		int maxLoop = orCandidate->size();
		for(int i = 0; i != maxLoop; ++i){
			const AbstractJoinCandidateCollection* col = orCandidate->get(i);
			this->list.addElement(col);
		}
	}
	else {
		const AbstractJoinCandidateCollection* col = dynamic_cast<const AbstractJoinCandidateCollection*>(this->joinCandidate);
		this->list.addElement(col);
	}
}

bool JoinCandidateCursor::finished() const noexcept {
	return this->pos < this->list.size();
}

void JoinCandidateCursor::inc() noexcept {
	this->pos++;
}


} /* namespace codablecash */
