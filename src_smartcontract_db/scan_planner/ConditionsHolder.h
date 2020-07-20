/*
 * ConditionsHolder.h
 *
 *  Created on: 2020/07/19
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_CONDITIONSHOLDER_H_
#define SCAN_PLANNER_CONDITIONSHOLDER_H_

namespace alinous {
class AbstractSQLExpression;
}
using namespace alinous;

namespace codablecash {

class RootScanCondition;

class ConditionsHolder {
public:
	ConditionsHolder();
	virtual ~ConditionsHolder();

	void processExpression(AbstractSQLExpression* sqlExpression);
private:
	RootScanCondition* root;
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_CONDITIONSHOLDER_H_ */
