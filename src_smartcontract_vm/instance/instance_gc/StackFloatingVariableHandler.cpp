/*
 * StackFloatingVariableHandler.cpp
 *
 *  Created on: 2020/03/14
 *      Author: iizuka
 */

#include "instance/instance_gc/StackFloatingVariableHandler.h"
#include "instance/instance_gc/GcManager.h"

#include "instance/AbstractVmInstance.h"
#include "instance/IAbstractVmInstanceSubstance.h"

#include "instance/instance_ref/AbstractReference.h"

namespace alinous {

StackFloatingVariableHandler::StackFloatingVariableHandler(GcManager* gc) {
	this->gc = gc;
}

StackFloatingVariableHandler::~StackFloatingVariableHandler() {
	__release();
}

void StackFloatingVariableHandler::release() noexcept {
	__release();
	this->list.reset();
}

void StackFloatingVariableHandler::__release() noexcept {
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
