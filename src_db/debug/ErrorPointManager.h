/*
 * ErrorPointManager.h
 *
 *  Created on: 2018/04/27
 *      Author: iizuka
 */

#ifndef DEBUG_ERRORPOINTMANAGER_H_
#define DEBUG_ERRORPOINTMANAGER_H_

// #include "base/HashMap.h"


namespace alinous {

class UnicodeString;
class ErrorOccurrence;

template<typename K, typename V> class HashMap;

class ErrorPointManager {
public:
	ErrorPointManager(const ErrorPointManager& base) = delete;
	ErrorPointManager();
	virtual ~ErrorPointManager();

	static ErrorPointManager* getInstance() noexcept;

	void activatePoint(const wchar_t* pointName, const wchar_t* occurrenceName, int errorCount) noexcept;
	void activatePoint(const wchar_t* pointName, ErrorOccurrence* occurrence) noexcept;
	void reachPoint(const wchar_t* pointName) noexcept;
	bool checkError(const wchar_t* occurrenceName) noexcept;

	void clear();
protected:
	HashMap<UnicodeString, ErrorOccurrence>* occurences;
	ErrorOccurrence* current;
};

} /* namespace alinous */

#endif /* DEBUG_ERRORPOINTMANAGER_H_ */
