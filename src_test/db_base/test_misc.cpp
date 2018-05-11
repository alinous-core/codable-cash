/*
 * test_misc.cpp
 *
 *  Created on: 2018/04/15
 *      Author: iizuka
 */


#include "base/UnicodeString.h"

#include "base/Iterator.h"
#include "base/Integer.h"

#include "test_utils/t_macros.h"

using namespace alinous;

TEST_GROUP(DbBaseMiscTestGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}
};


TEST(DbBaseMiscTestGroup, test01){

}
/*
TEST(DbBaseMiscTestGroup, iteratorVirtual){
	Iterator<Integer>* it = new Iterator<Integer>();
	it->hasNext();
	it->next();
	it->remove();

	delete it;
}

TEST(DbBaseMiscTestGroup, iteratorVirtual02){
	Iterator<UnicodeString>* it = new Iterator<UnicodeString>();
	it->hasNext();
	it->next();
	it->remove();

	delete it;
}
*/
