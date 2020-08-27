/*
 * AnalyzedScanPlan.cpp
 *
 *  Created on: 2020/08/27
 *      Author: iizuka
 */

#include "scan_planner_analyze/AnalyzedScanPlan.h"
#include "scan_planner_analyze/ScanTargetNameResolver.h"

namespace codablecash {

AnalyzedScanPlan::AnalyzedScanPlan() {
	this->scanTargetNameResolver = new ScanTargetNameResolver();

}

AnalyzedScanPlan::~AnalyzedScanPlan() {
	delete this->scanTargetNameResolver;
}

} /* namespace codablecash */
