/*
 * test_dom_array_base.cpp
 *
 *  Created on: 2020/07/11
 *      Author: iizuka
 */


#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"

#include "instance_dom/DomVariableInstance.h"

#include "instance_ref/VmRootReference.h"
#include "instance_ref/AbstractReference.h"

#include "instance_gc/GcManager.h"

#include "sc_analyze/AnalyzedType.h"

#include "instance_string/VmStringInstance.h"

#include "instance_dom/DomRuntimeReference.h"
#include "instance_dom/DomArrayVariable.h"

using namespace alinous;

TEST_GROUP(TestDomArrayBaseGroup) {
	TEST_SETUP(){
	}
	TEST_TEARDOWN(){
	}
};

TEST(TestDomArrayBaseGroup, case01){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);
	GcManager* gc = vm->getGc();

	{
		DomArrayVariable* val = new(vm) DomArrayVariable(vm); __STP(val);
		AnalyzedType at = val->getRuntimeType();

		CHECK(at.getType() == AnalyzedType::TYPE_DOM_ARRAY);

		const VMemList<AbstractReference>* list = val->getInstReferences();
		CHECK(list->size() == 0);
	}
}

