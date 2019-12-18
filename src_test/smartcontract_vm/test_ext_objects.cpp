/*
 * test_ext_objects.cpp
 *
 *  Created on: 2019/12/18
 *      Author: iizuka
 */


#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

#include "ext_binary/ExtClassObject.h"
#include "ext_binary/ExtPrimitiveObject.h"


using namespace alinous;


TEST_GROUP(TestExtObjects) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}

};

TEST(TestExtObjects, constructObj){
	ExtClassObject obj;
}

TEST(TestExtObjects, constructPrimitive){
	ExtPrimitiveObject obj;

}

