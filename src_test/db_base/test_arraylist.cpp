/*
 * test_arraylist.cpp
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */


#include <stdio.h>
#include "test_utils/t_macros.h"

#include "base/ArrayList.h"
#include "base/Integer.h"

using namespace alinous;

class dummyInt {
public:
	dummyInt() : value(0){
	}
	dummyInt(int i) : value(i){
	}

	int value;
};

TEST_GROUP(ArrayListTestGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}

};


TEST(ArrayListTestGroup, test01){
	ArrayList<dummyInt> ar;

	CHECK(ar.size() == 0);
}

TEST(ArrayListTestGroup, test02){
	ArrayList<dummyInt> ar;

	ar.addElement(new dummyInt(1));

	CHECK(ar.size() == 1);

	int size = ar.size();
	for(int i = 0; i != size; ++i){
		dummyInt* ptr = ar.get(i);
		delete ptr;
	}
}

TEST(ArrayListTestGroup, test03){
	ArrayList<dummyInt> ar;

	int maxLoop = 100;
	for(int i = 0; i != maxLoop; ++i){
		ar.addElement(new dummyInt(i));
	}

	int size = ar.size();
	CHECK(ar.size() == maxLoop);

	for(int i = 0; i != size; ++i){
		dummyInt* ptr = ar.get(i);
		CHECK(ptr->value == i);

		delete ptr;
	}
}

TEST(ArrayListTestGroup, test05){
	ArrayList<dummyInt> ar(1);

	CHECK(ar.size() == 0);
}

TEST(ArrayListTestGroup, test06){
	ArrayList<dummyInt> ar(8);

	CHECK(ar.size() == 0);
}

TEST(ArrayListTestGroup, test07){
	ArrayList<dummyInt> ar(8);

	int maxLoop = 100;
	for(int i = 0; i != maxLoop; ++i){
		ar.addElement(new dummyInt(i));
	}

	int size = ar.size();
	CHECK(ar.size() == maxLoop);

	for(int i = 0; i != size; ++i){
		dummyInt* ptr = ar.get(i);
		CHECK(ptr->value == i);

		delete ptr;
	}
}

TEST(ArrayListTestGroup, test08){
	ArrayList<dummyInt> ar(8);

	int maxLoop = 100;
	for(int i = 0; i != maxLoop; ++i){
		ar.addElement(new dummyInt(i));
	}

	int pos = ar.indexOfPtr(nullptr);
	CHECK(pos < 0);

	int size = ar.size();
	CHECK(ar.size() == maxLoop);

	for(int i = 0; i != size; ++i){
		dummyInt* ptr = ar.remove(0);
		CHECK(ptr->value == i);

		delete ptr;
	}
}

void releaseInternalObjects(ArrayList<Integer, Integer::ValueCompare>* ptr){
	int maxLoop = ptr->size();
	for(int i = 0; i != maxLoop; ++i){
		Integer* pInt = ptr->get(i);
		delete pInt;
	}
}

void isSorted(ArrayList<Integer, Integer::ValueCompare>* ptr){
	Integer* last = nullptr;

	int maxLoop = ptr->size();
	for(int i = 0; i != maxLoop; ++i){
		Integer* pInt = ptr->get(i);

		if(last){
			if(!(last->compareTo(pInt) <= 0)){
				throw -1;
			}
		}

		//printf("%d\n", pInt->value);


		last = pInt;
	}
}

TEST(ArrayListTestGroup, sort01){
	ArrayList<Integer, Integer::ValueCompare> ar(8);

	int maxLoop = 10;
	for(int i = 0; i != 10; ++i){
		Integer* pInt = new Integer(maxLoop - i);
		ar.addElement(pInt);
	}

	ar.sort();

	isSorted(&ar);
	releaseInternalObjects(&ar);
}

TEST(ArrayListTestGroup, sortInsert){
	ArrayList<Integer, Integer::ValueCompare> ar(8);

	int maxLoop = 10;
	for(int i = 0; i != 10; ++i){
		Integer* pInt = new Integer(maxLoop - i);
		ar.addElement(pInt);
	}

	ar.addElementWithSorted(new Integer(11));
	ar.addElementWithSorted(new Integer(0));
	ar.addElementWithSorted(new Integer(5));
	ar.addElementWithSorted(new Integer(-1));
	ar.addElementWithSorted(new Integer(-1));
	ar.addElementWithSorted(new Integer(100));
	ar.addElementWithSorted(new Integer(100));

	ar.addElementWithSorted(new Integer(100));

	ar.addElementWithSorted(new Integer(200));

	CHECK(ar.size() == (maxLoop + 9));

	isSorted(&ar);
	releaseInternalObjects(&ar);
}


TEST(ArrayListTestGroup, removeObjFalse){
	ArrayList<dummyInt> ar;

	ar.addElement(new dummyInt(1));

	dummyInt val(2);
	bool result = ar.removeByObj(&val);
	CHECK(result == false)

	int size = ar.size();
	for(int i = 0; i != size; ++i){
		dummyInt* ptr = ar.get(i);
		delete ptr;
	}
}
