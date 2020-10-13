/*
 * MemberVariableTable.cpp
 *
 *  Created on: 2020/01/04
 *      Author: iizuka
 */

#include "engine/sc_analyze_variables/MemberVariableTable.h"
#include "engine/sc_analyze_variables/MemberVariableEntry.h"

#include "base/UnicodeString.h"

namespace alinous {

MemberVariableTable::MemberVariableTable() {

}

MemberVariableTable::~MemberVariableTable() {
	this->list.deleteElements();

}

void MemberVariableTable::addEntry(const UnicodeString* name, MemberVariableDeclare* dec) noexcept {
	MemberVariableEntry* entry = new MemberVariableEntry(name, dec);

	this->list.addElement(entry);
	this->map.put(name, entry);
}

bool MemberVariableTable::hasEntry(const UnicodeString* name) const noexcept {
	MemberVariableEntry* entry = this->map.get(name);
	return entry != nullptr;
}

ArrayList<MemberVariableEntry>* MemberVariableTable::getVariableList() noexcept {
	return &this->list;
}


} /* namespace alinous */
