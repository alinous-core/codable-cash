/*
 * test_character.cpp
 *
 *  Created on: 2018/04/15
 *      Author: iizuka
 */


#include "test_utils/t_macros.h"

#include "base/Character.h"

using namespace alinous;

TEST_GROUP(CharacterTestGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}

};

TEST(CharacterTestGroup, test01){
	Character * ch = new Character(L'A');
	delete ch;
}
