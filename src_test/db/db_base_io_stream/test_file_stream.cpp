/*
 * test_file_stream.cpp
 *
 *  Created on: 2018/04/19
 *      Author: iizuka
 */


#include "test_utils/t_macros.h"

#include "base_io_stream/FileOutputStream.h"
#include "base_io_stream/FileInputStream.h"
#include "base_io_stream/exceptions.h"

using namespace alinous;


TEST_GROUP(FileStreamTestGroup) {
	TEST_SETUP() {
		env->setup();
	}
	TEST_TEARDOWN() {
		env->teardown();
	}

};

TEST(FileStreamTestGroup, construct){
	File projectFolder = this->env->testCaseDir();

	FileOutputStream stream(&projectFolder);
	FileInputStream inStream(&projectFolder);

	UnicodeString strfile01(L"test.txt");
	File* outFile = projectFolder.get(&strfile01);
	StackRelease<File> r_outFile(outFile);

	UnicodeString* strFile = outFile->getAbsolutePath();
	StackRelease<UnicodeString> r_strFile(strFile);

	FileOutputStream stream02(strFile);
	FileOutputStream stream03(strFile, true);

	FileInputStream inStream02(strFile);
}

TEST(FileStreamTestGroup, writeOpen){
	File projectFolder = this->env->testCaseDir();

	UnicodeString strfile01(L"test.txt");
	File* outFile = projectFolder.get(&strfile01);
	StackRelease<File> r_outFile(outFile);

	FileOutputStream stream(outFile);

	stream.open(false);
	stream.close();

	CHECK(outFile->exists())

	stream.open(true);
	stream.close();
}


TEST(FileStreamTestGroup, writeAppendOpen){
	File projectFolder = this->env->testCaseDir();

	UnicodeString strfile01(L"test.txt");
	File* outFile = projectFolder.get(&strfile01);
	StackRelease<File> r_outFile(outFile);

	FileOutputStream stream(outFile, true);

	stream.open(false);
	stream.close();

	CHECK(outFile->exists())
}

TEST(FileStreamTestGroup, writeAndRead){
	File projectFolder = this->env->testCaseDir();

	UnicodeString strfile01(L"test.txt");
	File* outFile = projectFolder.get(&strfile01);
	StackRelease<File> r_outFile(outFile);

	{
		FileOutputStream stream(outFile, true);

		stream.open(false);

		const char* cpath = strfile01.toCString();
		stream.write(cpath, strfile01.length());

		delete [] cpath;

		stream.flush();
	}

	// read
	FileInputStream inStream02(outFile);
	inStream02.open();

	char buff[256]{};
	int red = inStream02.read(buff, 256);
	buff[red] = 0;

	UnicodeString content(buff);
	CHECK(content.equals(&strfile01))
}

TEST(FileStreamTestGroup, writeOpenError){
	File projectFolder = this->env->testCaseDir();

	UnicodeString strfile01(L"dummy/test.txt");
	File* outFile = projectFolder.get(&strfile01);
	StackRelease<File> r_outFile(outFile);

	FileOutputStream stream(outFile, true);

	Exception* exp = nullptr;
	try{
		stream.open(false);
	}catch(Exception* e){
		exp = e;
	}

	CHECK(dynamic_cast<FileOpenException*>(exp) != nullptr)

	delete exp;
}

TEST(FileStreamTestGroup, readOpenError){
	File projectFolder = this->env->testCaseDir();

	UnicodeString strfile01(L"dummy/test.txt");
	File* readFile = projectFolder.get(&strfile01);
	StackRelease<File> r_outFile(readFile);

	InputStream* stream = new FileInputStream(readFile);
	StackRelease<InputStream> r_stream(stream);

	Exception* exp = nullptr;
	try{
		stream->open();
	}catch(Exception* e){
		exp = e;
	}

	CHECK(dynamic_cast<FileOpenException*>(exp) != nullptr)

	CHECK(!stream->available())
	CHECK(!stream->markSupported())
	stream->mark(0);
	stream->reset();

	delete exp;
}
