/*
 * TableIndexDetectorStackMarker.h
 *
 *  Created on: 2020/09/07
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_CTX_INDEX_TABLEINDEXDETECTORSTACKMARKER_H_
#define SCAN_PLANNER_SCANNER_CTX_INDEX_TABLEINDEXDETECTORSTACKMARKER_H_

namespace codablecash {

class TableIndexDetectorStack;

class TableIndexDetectorStackMarker {
public:
	explicit TableIndexDetectorStackMarker(TableIndexDetectorStack* stack);
	virtual ~TableIndexDetectorStackMarker();

private:
	TableIndexDetectorStack* stack;
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_CTX_INDEX_TABLEINDEXDETECTORSTACKMARKER_H_ */
