/*
 * test_dom_extobj.cpp
 *
 *  Created on: 2020/07/04
 *      Author: iizuka
 */
#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"

#include "ext_binary/ExtDomObject.h"
#include "ext_binary/ExtStringClass.h"

using namespace alinous;

TEST_GROUP(TestDomExtObjGroup) {
	TEST_SETUP(){
	}
	TEST_TEARDOWN(){
	}
};

TEST(TestDomExtObjGroup, case01){
	UnicodeString name(L"dom");
	ExtDomObject obj(&name);

	UnicodeString namestr(L"str");
	UnicodeString value(L"hello");
	ExtStringClass* strObj = new ExtStringClass(&namestr, &value);

	obj.put(&namestr, strObj);

	AbstractExtObject* prop = obj.get(&namestr);
	ExtStringClass* propstr = dynamic_cast<ExtStringClass*>(prop);

	const UnicodeString* str = propstr->getValue();
	CHECK(str->equals(&value));
}
