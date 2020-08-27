/*
 * AnalyzedScanPlan.h
 *
 *  Created on: 2020/08/27
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_ANALYZE_ANALYZEDSCANPLAN_H_
#define SCAN_PLANNER_ANALYZE_ANALYZEDSCANPLAN_H_

namespace codablecash {

class ScanTargetNameResolver;

class AnalyzedScanPlan {
public:
	AnalyzedScanPlan();
	virtual ~AnalyzedScanPlan();

private:
	ScanTargetNameResolver* scanTargetNameResolver;
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_ANALYZE_ANALYZEDSCANPLAN_H_ */
