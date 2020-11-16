/*
 * IndexRangeCandidate.h
 *
 *  Created on: 2020/11/16
 *      Author: iizuka
 */

#ifndef SCAN_SELECT_SCAN_PLANNER_SCANNER_INDEX_INDEXRANGECANDIDATE_H_
#define SCAN_SELECT_SCAN_PLANNER_SCANNER_INDEX_INDEXRANGECANDIDATE_H_

#include "scan_select/scan_planner/scanner/index/IndexCandidate.h"

namespace codablecash {

class IndexRangeCandidate : public IndexCandidate {
public:
	IndexRangeCandidate();
	virtual ~IndexRangeCandidate();

};

} /* namespace codablecash */

#endif /* SCAN_SELECT_SCAN_PLANNER_SCANNER_INDEX_INDEXRANGECANDIDATE_H_ */
