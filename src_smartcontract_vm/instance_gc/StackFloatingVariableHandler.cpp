/*
 * StackFloatingVariableHandler.cpp
 *
 *  Created on: 2020/03/14
 *      Author: iizuka
 */

#include "instance_gc/StackFloatingVariableHandler.h"
#include "instance_gc/GcManager.h"

#include "instance/AbstractVmInstance.h"
#include "instance/IAbstractVmInstanceSubstance.h"

#include "instance_ref/AbstractReference.h"

namespace alinous {

StackFloatingVariableHandler::StackFloatingVariableHandler(GcManager* gc) {
	this->gc = gc;
}

StackFloatingVariableHandler::~StackFloatingVariableHandler() {
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		IAbstractVmInstanceSubstance* inst = this->list.get(i);

		this->gc->handleFloatingObject(inst);
	}
}

AbstractVmInstance* StackFloatingVariableHandler::registerInstance(AbstractVmInstance* inst) noexcept {
	if(inst == nullptr || inst->isNull()){
		return nullptr;
	}

	this->list.addElement(inst->getInstance());

	return inst;
}

} /* namespace alinous */
