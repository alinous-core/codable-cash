/*
 * ErrorPointManager.cpp
 *
 *  Created on: 2018/04/27
 *      Author: iizuka
 */

#include "debug/ErrorPointManager.h"
#include "debug/ErrorOccurrence.h"

#include "base/UnicodeString.h"
#include "base/StackRelease.h"

namespace alinous {

ErrorPointManager* ErrorPointManager::inst;

ErrorPointManager::ErrorPointManager() : current(nullptr) {

}

ErrorPointManager::~ErrorPointManager() {
	clear();
}

void ErrorPointManager::clear() {
	Iterator<UnicodeString>* it = this->occurences.keySet()->iterator();
	StackRelease<Iterator<UnicodeString>> r_it(it);
	while(it->hasNext()){
		const UnicodeString* key = it->next();
		ErrorOccurrence* occurrence = this->occurences.get(key);

		delete occurrence;
	}
}


ErrorPointManager* ErrorPointManager::getInstance() noexcept {
	if(inst == nullptr){
		inst = new ErrorPointManager();
	}
	return inst;
}

void ErrorPointManager::closeInstance() noexcept {
	if(inst != nullptr){
		delete inst;
		inst = nullptr;
	}
}

void ErrorPointManager::activatePoint(const wchar_t* pointName,
		const wchar_t* occurrenceName, int errorCount) noexcept
{
	ErrorOccurrence* occurrence = new ErrorOccurrence(occurrenceName, errorCount);
	activatePoint(pointName, occurrence);
}

void ErrorPointManager::activatePoint(const wchar_t* pointName,
		ErrorOccurrence* occurrence) noexcept
{
	UnicodeString key(pointName);
	this->occurences.put(key, occurrence);
}



void ErrorPointManager::reachPoint(const wchar_t* pointName) noexcept {
	UnicodeString key(pointName);
	ErrorOccurrence* occurrence = this->occurences.get(key);

	if(occurrence != nullptr){
		this->current = occurrence;
	}
}


bool ErrorPointManager::checkError(const wchar_t* occurrenceName) noexcept {
	UnicodeString name(occurrenceName);
	if(this->current == nullptr){
		return this->current->hit(occurrenceName);
	}
	return false;
}



} /* namespace alinous */
