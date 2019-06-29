/*
 * AnalyzeStackManager.h
 *
 *  Created on: 2019/06/12
 *      Author: iizuka
 */

#ifndef SC_ANALYZE_ANALYZESTACKMANAGER_H_
#define SC_ANALYZE_ANALYZESTACKMANAGER_H_

#include "base/ArrayList.h"

namespace alinous {

class AnalyzeStack;

class AnalyzeStackManager {
public:
	AnalyzeStackManager();
	virtual ~AnalyzeStackManager();

	void addFunctionStack() noexcept;
	void popFunctionStack() noexcept;
	void addBlockStack() noexcept;
	void popBlockStack() noexcept;

	//void addVariableDeclare() noexcept;
private:
	ArrayList<AnalyzeStack>* stack;
};

} /* namespace alinous */

#endif /* SC_ANALYZE_ANALYZESTACKMANAGER_H_ */
