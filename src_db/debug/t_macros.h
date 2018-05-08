/*
 * macros.h
 *
 *  Created on: 2018/05/08
 *      Author: iizuka
 */

#ifndef DEBUG_T_MACROS_H_
#define DEBUG_T_MACROS_H_

#include "debug/TestExecutor.h"
#include "debug/TestGroup.h"
#include "debug/TestCase.h"

#define _STR_L(str) L##str
#define STR_L(str) _STR_L(#str)


#define TEST_GROUP(grp) \
class grp : public TestGroup { \
public: \
	grp(const wchar_t* groupName) : TestGroup(groupName){ \
	}\
	virtual ~grp(){ \
	} \
} grp##_inst(STR_L(grp));




#endif /* DEBUG_T_MACROS_H_ */
