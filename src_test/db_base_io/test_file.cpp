/*
 * test_file.cpp
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */

#include "CppUTest/CommandLineTestRunner.h"
#include "charsets/CharsetManager.h"

#include "base_io/File.h"
#include "base/UnicodeString.h"


using namespace alinous;


TEST_GROUP(FileTestGroup) {
	TEST_SETUP() {
		CharsetManager::getInstance();
	}
	TEST_TEARDOWN() {
		CharsetManager::closeInstance();
	}

};


TEST(FileTestGroup, test01){
	UnicodeString path(L"/test/path/index.html");
	File* file = new File(&path);

	UnicodeString* ret = file->getAbsolutePath();
	delete ret;

	delete file;
}

TEST(FileTestGroup, test02){
	UnicodeString path(L".");
	File* file = new File(&path);

	UnicodeString* ret = file->getAbsolutePath();
	delete ret;

	delete file;
}

TEST(FileTestGroup, test03){
	UnicodeString path(L"dfgdfhjghkjghhgkj/gfdgsdfgdfsg");
	File* file = new File(&path);

	UnicodeString* ret = file->getAbsolutePath();
	delete ret;

	delete file;

	CharsetManager::closeInstance();
}

TEST(FileTestGroup, test04){
	UnicodeString path(L"../dfgdfhjghkjghhgkj/gfdgsdfgdfsg");
	File* file = new File(&path);

	UnicodeString* ret = file->getAbsolutePath();
	delete ret;

	delete file;

	CharsetManager::closeInstance();
}

TEST(FileTestGroup, test05){
	UnicodeString path(L"./dfgdfhjghkjghhgkj/gfdgsdfgdfsg");
	File* file = new File(&path);

	UnicodeString* ret = file->getAbsolutePath();
	delete ret;

	delete file;
}

TEST(FileTestGroup, mkdir01){
	UnicodeString path(L"./test_data");
	File* file = new File(&path);

	file->mkdirs();

	delete file;
}


