/*
 * AnalyzedScanPlan.cpp
 *
 *  Created on: 2020/08/27
 *      Author: iizuka
 */

#include "scan_planner_analyze/AnalyzedScanPlan.h"
#include "scan_planner_analyze/ScanTargetNameResolver.h"
#include "scan_planner_analyze/ScanColumnNameResolver.h"

#include "scan_planner_scanner/AbstractScannerFactory.h"

namespace codablecash {

AnalyzedScanPlan::AnalyzedScanPlan() {
	this->scanTargetNameResolver = new ScanTargetNameResolver();
	this->scanColumnNameResolver = new ScanColumnNameResolver();
	this->scanFactory = nullptr;
}

AnalyzedScanPlan::~AnalyzedScanPlan() {
	delete this->scanTargetNameResolver;
	delete this->scanColumnNameResolver;
	delete this->scanFactory;
}

} /* namespace codablecash */
