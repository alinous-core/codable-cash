/*
 * test_exception_inst.cpp
 *
 *  Created on: 2020/07/04
 *      Author: iizuka
 */
#include "test_utils/t_macros.h"
#include "vm/VirtualMachine.h"

#include "instance/instance_exception_class/VmExceptionInstance.h"
#include "instance/instance_exception_class/ExceptionClassDeclare.h"

#include "engine/sc_analyze/AnalyzedClass.h"

#include "base/UnicodeString.h"

TEST_GROUP(TestExceptionInsttGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};


TEST(TestExceptionInsttGroup, meg01){
	VirtualMachine* vm = new VirtualMachine(1024*100); __STP(vm);

	{
		ExceptionClassDeclare* dec = new ExceptionClassDeclare(); __STP(dec);

		AnalyzedClass* clazz = new AnalyzedClass(dec); __STP(clazz);
		VmExceptionInstance* inst = new(vm) VmExceptionInstance(clazz, vm); __STP(inst);

		UnicodeString message(L"Hello");
		inst->setMessage(&message);

		const UnicodeString* str = inst->getMessage();
		CHECK(str->equals(&message))

		str = inst->toString();
		CHECK(str != nullptr)
	}
}
