/*
 * ScanJoinContextHolder.h
 *
 *  Created on: 2020/08/30
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_CTX_SCANJOINCONTEXTHOLDER_H_
#define SCAN_PLANNER_SCANNER_CTX_SCANJOINCONTEXTHOLDER_H_

#include "base/ArrayList.h"

using namespace alinous;

namespace codablecash {

class ScanJoinContext;

class ScanJoinContextHolder {
public:
	ScanJoinContextHolder();
	virtual ~ScanJoinContextHolder();

private:
	ArrayList<ScanJoinContext> list;


};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_CTX_SCANJOINCONTEXTHOLDER_H_ */
