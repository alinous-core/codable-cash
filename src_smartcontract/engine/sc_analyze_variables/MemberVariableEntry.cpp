/*
 * MemberVariableEntry.cpp
 *
 *  Created on: 2020/01/04
 *      Author: iizuka
 */

#include "engine/sc_analyze_variables/MemberVariableEntry.h"

#include "base/UnicodeString.h"
namespace alinous {

MemberVariableEntry::MemberVariableEntry(const UnicodeString* name, MemberVariableDeclare* dec) {
	this->name = new UnicodeString(name);
	this->dec = dec;
}

MemberVariableEntry::~MemberVariableEntry() {
	delete this->name;
	this->dec = nullptr;
}

const UnicodeString* MemberVariableEntry::getName() const noexcept {
	return this->name;
}

MemberVariableDeclare* MemberVariableEntry::getMemberVariableDeclare() const noexcept {
	return this->dec;
}

} /* namespace alinous */
