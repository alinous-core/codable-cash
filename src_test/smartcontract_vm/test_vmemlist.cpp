/*
 * test_vmemlist.cpp
 *
 *  Created on: 2019/06/06
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "instance_parts/VmMalloc.h"
#include "instance_parts/VMemList.h"

#include "instance_ref/PrimitiveReference.h"

using namespace alinous;

TEST_GROUP(TestVmMemList) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestVmMemList, construct){
	VirtualMachine vm(1024);

	PrimitiveReference* ref = PrimitiveReference::createIntReference(&vm, 1);
	VMemList<PrimitiveReference> list(&vm);

	CHECK(ref->getIntValue() == 1)

	delete ref;
}
/*
TEST(TestVmMemList, test02){
	VirtualMachine vm(1024);

	PrimitiveReference* ref = PrimitiveReference::createIntReference(&vm, 1);
	CHECK(ref->getIntValue() == 1)

	VMemList<PrimitiveReference> list(&vm);
	list.addElement(ref);
}
*/
/*
TEST(TestVmMemList, test02){
	ArrayList<dummyInt> ar;

	ar.addElement(new dummyInt(1));

	CHECK(ar.size() == 1);

	int size = ar.size();
	for(int i = 0; i != size; ++i){
		dummyInt* ptr = ar.get(i);
		delete ptr;
	}
}*/

