/*
 * StackFloatingVariableHandler.cpp
 *
 *  Created on: 2020/03/14
 *      Author: iizuka
 */

#include "instance_gc/StackFloatingVariableHandler.h"
#include "instance_gc/GcManager.h"

#include "instance/AbstractVmInstance.h"

#include "instance_ref/AbstractReference.h"

namespace alinous {

StackFloatingVariableHandler::StackFloatingVariableHandler(GcManager* gc) {
	this->gc = gc;
}

StackFloatingVariableHandler::~StackFloatingVariableHandler() {
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractVmInstance* inst = this->list.get(i);
		if(inst->isReference()){
			AbstractReference* ref = dynamic_cast<AbstractReference*>(inst);
			inst = ref->getInstance();
		}

		this->gc->handleFloatingObject(inst);
	}
}

} /* namespace alinous */
