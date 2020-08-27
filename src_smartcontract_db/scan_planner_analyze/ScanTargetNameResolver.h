/*
 * ScanTargetNameResolver.h
 *
 *  Created on: 2020/08/27
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_ANALYZE_SCANTARGETNAMERESOLVER_H_
#define SCAN_PLANNER_ANALYZE_SCANTARGETNAMERESOLVER_H_

#include "base/HashMap.h"

namespace alinous {
class UnicodeString;
}
using namespace alinous;

namespace codablecash {

class AbstractScanTableTarget;

class ScanTargetNameResolver {
public:
	ScanTargetNameResolver();
	virtual ~ScanTargetNameResolver();

	void add(const UnicodeString* tableFqn, AbstractScanTableTarget* target);
	AbstractScanTableTarget* get(const UnicodeString* tableFqn) const noexcept;

private:
	HashMap<UnicodeString, AbstractScanTableTarget> map;
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_ANALYZE_SCANTARGETNAMERESOLVER_H_ */
