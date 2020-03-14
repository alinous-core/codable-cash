/*
 * StackFloatingVariableHandler.h
 *
 *  Created on: 2020/03/14
 *      Author: iizuka
 */

#ifndef INSTANCE_GC_STACKFLOATINGVARIABLEHANDLER_H_
#define INSTANCE_GC_STACKFLOATINGVARIABLEHANDLER_H_

#include "base/ArrayList.h"

namespace alinous {

class GcManager;
class AbstractVmInstance;

class StackFloatingVariableHandler {
public:
	explicit StackFloatingVariableHandler(GcManager* gc);
	virtual ~StackFloatingVariableHandler();

private:
	GcManager* gc;
	ArrayList<AbstractVmInstance> list;
};

} /* namespace alinous */

#endif /* INSTANCE_GC_STACKFLOATINGVARIABLEHANDLER_H_ */
