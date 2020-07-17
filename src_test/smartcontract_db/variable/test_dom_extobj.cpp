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
#include "ext_binary/ExtDomArrayObject.h"

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

TEST(TestDomExtObjGroup, case01withCopy){
	UnicodeString name(L"dom");
	ExtDomObject obj(&name);

	UnicodeString namestr(L"str");
	UnicodeString value(L"hello");
	ExtStringClass* strObj = new ExtStringClass(&namestr, &value);

	obj.put(&namestr, strObj);

	ExtDomObject* obj2 = dynamic_cast<ExtDomObject*>(obj.copy()); __STP(obj2);


	AbstractExtObject* prop = obj2->get(&namestr);
	ExtStringClass* propstr = dynamic_cast<ExtStringClass*>(prop);

	const UnicodeString* str = propstr->getValue();
	CHECK(str->equals(&value));
}

TEST(TestDomExtObjGroup, case02){
	UnicodeString name(L"domar");
	ExtDomArrayObject obj(&name);

	UnicodeString namestr(L"str");
	UnicodeString value(L"hello");
	ExtStringClass* strObj = new ExtStringClass(&namestr, &value);

	obj.add(strObj);

	CHECK(obj.size() == 1)

	AbstractExtObject* prop = obj.get(0);
	ExtStringClass* propstr = dynamic_cast<ExtStringClass*>(prop);

	const UnicodeString* str = propstr->getValue();
	CHECK(str->equals(&value));
}

TEST(TestDomExtObjGroup, case03){
	UnicodeString name(L"domar");
	ExtDomArrayObject obj(&name);

	UnicodeString namestr(L"str");
	UnicodeString value(L"hello");
	ExtStringClass* strObj = new ExtStringClass(&namestr, &value);

	obj.add(strObj);

	CHECK(obj.size() == 1)

	ExtDomArrayObject* obj2 = dynamic_cast<ExtDomArrayObject*>(obj.copy()); __STP(obj2);

	AbstractExtObject* prop = obj2->get(0);
	ExtStringClass* propstr = dynamic_cast<ExtStringClass*>(prop);

	const UnicodeString* str = propstr->getValue();
	CHECK(str->equals(&value));
}


