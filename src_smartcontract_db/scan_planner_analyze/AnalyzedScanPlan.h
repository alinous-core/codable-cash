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
class ScanColumnNameResolver;
class AbstractScannerFactory;

class AnalyzedScanPlan {
public:
	AnalyzedScanPlan();
	virtual ~AnalyzedScanPlan();

	ScanTargetNameResolver* getScanTargetNameResolver() const noexcept {
		return scanTargetNameResolver;
	}

	ScanColumnNameResolver* getScanColumnNameResolver() const noexcept {
		return scanColumnNameResolver;
	}

	AbstractScannerFactory* getScanFactory() const noexcept {
		return scanFactory;
	}
	void setScanFactory(AbstractScannerFactory* scanFactory) noexcept;


private:
	ScanTargetNameResolver* scanTargetNameResolver;
	ScanColumnNameResolver* scanColumnNameResolver;

	AbstractScannerFactory* scanFactory;

};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_ANALYZE_ANALYZEDSCANPLAN_H_ */
