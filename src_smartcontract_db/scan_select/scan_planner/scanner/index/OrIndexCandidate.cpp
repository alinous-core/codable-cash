/*
 * OrIndexCandidate.cpp
 *
 *  Created on: 2020/09/07
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/index/OrIndexCandidate.h"

#include "scan_select/scan_planner/scanner/index/AbstractIndexCandidateCollection.h"

#include "base/StackRelease.h"

#include "scan_select/scan_planner/scanner/index/AbstractIndexCandidate.h"

#include "base/UnicodeString.h"
using namespace alinous;

namespace codablecash {

OrIndexCandidate::OrIndexCandidate(const OrIndexCandidate& inst) : AbstractIndexCandidate(inst.indexType) {
	int maxLoop = inst.list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractIndexCandidateCollection* col = inst.list.get(i);
		add(col);
	}
}

OrIndexCandidate::OrIndexCandidate() : AbstractIndexCandidate(AbstractIndexCandidate::IndexType::OR) {

}

OrIndexCandidate::~OrIndexCandidate() {
	this->list.deleteElements();
}

AbstractIndexCandidate::IndexType OrIndexCandidate::getCandidateType() const noexcept {
	return AbstractIndexCandidate::IndexType::OR;
}

AbstractIndexCandidate* OrIndexCandidate::multiply(const AbstractIndexCandidate* other) const noexcept {
	AbstractIndexCandidate::IndexType candidateType = other->getCandidateType();

	if(candidateType == AbstractIndexCandidate::IndexType::OR){
		const OrIndexCandidate* orCandidate = dynamic_cast<const OrIndexCandidate*>(other);
		return multiplyOr(orCandidate);
	}

	OrIndexCandidate* newCond = new OrIndexCandidate();
	AbstractIndexCandidateCollection* col = dynamic_cast<AbstractIndexCandidateCollection*>(other->copy());
	__STP(col);

	multiply(this, col, newCond);

	return newCond;
}

AbstractIndexCandidate* OrIndexCandidate::multiplyOr(const OrIndexCandidate* other) const noexcept {
	OrIndexCandidate* newCond = new OrIndexCandidate();

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractIndexCandidateCollection* col = this->list.get(i);

		multiply(other, col, newCond);
	}

	return newCond;
}

const UnicodeString* OrIndexCandidate::toCodeString() noexcept {
	if(this->str == nullptr){
		this->str = new UnicodeString(L"");

		int maxLoop = this->list.size();
		for(int i = 0; i != maxLoop; ++i){
			AbstractIndexCandidateCollection* col = this->list.get(i);

			if(i != 0){
				this->str->append(L" OR ");
			}

			const UnicodeString* colstr = col->toCodeString();
			this->str->append(colstr);
		}
	}

	return this->str;
}

void OrIndexCandidate::multiply(const OrIndexCandidate* other,
		const AbstractIndexCandidateCollection* col, OrIndexCandidate* newCond) const noexcept {
	int maxLoop = other->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractIndexCandidateCollection* c = other->list.get(i);

		AbstractIndexCandidate* newC = c->multiply(col);
		AbstractIndexCandidateCollection* newCollection = dynamic_cast<AbstractIndexCandidateCollection*>(newC);

		newCond->list.addElement(newCollection);
	}
}


AbstractIndexCandidate* OrIndexCandidate::copy() const noexcept {
	return new OrIndexCandidate(*this);
}

void OrIndexCandidate::add(const AbstractIndexCandidateCollection* candidate) noexcept {
	this->list.addElement(dynamic_cast<AbstractIndexCandidateCollection*>(candidate->copy()));
}

int OrIndexCandidate::size() const noexcept {
	return this->list.size();
}

AbstractIndexCandidateCollection* OrIndexCandidate::get(int i) const noexcept {
	return this->list.get(i);
}

} /* namespace codablecash */
