/*
 * TestGroupSetup.h
 *
 *  Created on: 2018/05/08
 *      Author: iizuka
 */

#ifndef DEBUG_TESTGROUPACTIONS_H_
#define DEBUG_TESTGROUPACTIONS_H_

namespace alinous {

class TestGroupActions {
public:
	virtual ~TestGroupActions(){}
	virtual void setup();
	virtual void teardown();
};

} /* namespace alinous */

#endif /* DEBUG_TESTGROUPACTIONS_H_ */
