/*
 * test_reader.cpp
 *
 *  Created on: 2018/05/17
 *      Author: iizuka
 */




#include "test_utils/t_macros.h"

#include "base_io_stream/exceptions.h"
#include "base_io_stream/FileOutputStream.h"
#include "base_io_stream/OutputStreamWriter.h"

#include "base/StackRelease.h"

#include "base_io_stream/InputStream.h"
#include "base_io_stream/InputStreamReader.h"
#include "base_io_stream/FileInputStream.h"

using namespace alinous;


TEST_GROUP(ReaderTestGroup) {
	TEST_SETUP() {
		env->setup();
	}
	TEST_TEARDOWN() {
		env->teardown();
	}

};

static UnicodeString* makeTestFile(File projectFolder, const wchar_t* content){
	_ST(File, outFile, projectFolder.get(L"out.txt"))
	UnicodeString* path = outFile->getAbsolutePath();

	UnicodeString charset(L"utf-8");
	FileOutputStream outStream(path);
	outStream.open(false);

	OutputStreamWriter writer(&outStream, &charset);
	writer.write(content);
	writer.close();

	return path;
}

TEST(ReaderTestGroup, construct){
	const wchar_t* content = L"Hello world";
	UnicodeString strContent(content);
	_ST(UnicodeString, path, makeTestFile(this->env->testCaseDir(), content))

	UnicodeString charset(L"utf-8");
	FileInputStream stream(path);
	stream.open();
	InputStreamReader reader(&stream, &charset);

	UnicodeString result(L"");
	wchar_t* buff = new wchar_t[12]{};

	int red = reader.read(buff, 12);
	result.append(buff, red);

	bool bl = result.equals(&strContent);
	CHECK(bl)
	delete [] buff;
}

TEST(ReaderTestGroup, read01){
	const wchar_t* content = L"Hello world";
	UnicodeString strContent(content);
	_ST(UnicodeString, path, makeTestFile(this->env->testCaseDir(), content))

	FileInputStream stream(path);
	stream.open();
	InputStreamReader reader(&stream);

	UnicodeString result(L"");
	wchar_t* buff = new wchar_t[12]{};

	int red = reader.read(buff, 4);
	result.append(buff, red);

	red = reader.read(buff, 1);
	result.append(buff, red);

	red = reader.read(buff, 1);
	result.append(buff, red);

	red = reader.read(buff, 12);
	result.append(buff, red);

	bool bl = result.equals(&strContent);
	CHECK(bl)
	delete [] buff;
}

TEST(ReaderTestGroup, read02){
	const wchar_t* content = L"Hello world";
	UnicodeString strContent(content);
	_ST(UnicodeString, path, makeTestFile(this->env->testCaseDir(), content))

	FileInputStream stream(path);
	stream.open();
	InputStreamReader reader(&stream);

	UnicodeString result(L"");
	wchar_t* buff = new wchar_t[12]{};

	int red = reader.read(buff, 4);
	result.append(buff, red);

	red = reader.read(buff, 12);
	result.append(buff, red);

	bool bl = result.equals(&strContent);
	CHECK(bl)
	delete [] buff;
}

TEST(ReaderTestGroup, read03){
	const wchar_t* content = L"Hello world";
	UnicodeString strContent(content);
	_ST(UnicodeString, path, makeTestFile(this->env->testCaseDir(), content))

	FileInputStream stream(path);
	stream.open();
	InputStreamReader reader(&stream);

	UnicodeString result(L"");
	wchar_t* buff = new wchar_t[12]{};

	int red = reader.read(buff, 1);
	result.append(buff, red);

	red = reader.read(buff, 4);
	result.append(buff, red);

	red = reader.read(buff, 12);
	result.append(buff, red);

	bool bl = result.equals(&strContent);
	CHECK(bl)
	delete [] buff;
}

TEST(ReaderTestGroup, read04){
	const wchar_t* content = L"Hello world Hello world";
	UnicodeString strContent(content);
	_ST(UnicodeString, path, makeTestFile(this->env->testCaseDir(), content))

	FileInputStream stream(path);
	stream.open();
	InputStreamReader reader(&stream);

	UnicodeString result(L"");
	wchar_t* buff = new wchar_t[12]{};

	int red = reader.read(buff, 4);
	result.append(buff, red);

	red = reader.read(buff, 2);
	result.append(buff, red);

	red = reader.read(buff, 2);
	result.append(buff, red);

	red = reader.read(buff, 2);
	result.append(buff, red);

	red = reader.read(buff, 12);
	result.append(buff, red);

	red = reader.read(buff, 12);
	result.append(buff, red);

	bool bl = result.equals(&strContent);
	CHECK(bl)
	delete [] buff;
}


TEST(ReaderTestGroup, utfRemain){
	const wchar_t* content = L"Hello 木Hello world";
	UnicodeString strContent(content);
	_ST(UnicodeString, path, makeTestFile(this->env->testCaseDir(), content))

	UnicodeString charset(L"utf-8");
	FileInputStream stream(path);
	stream.open();
	InputStreamReader reader(&stream, &charset);

	UnicodeString result(L"");
	wchar_t* buff = new wchar_t[12]{};

	int red = reader.read(buff, 4);
	result.append(buff, red);

	red = reader.read(buff, 12);
	result.append(buff, red);

	red = reader.read(buff, 12);
	result.append(buff, red);


	bool bl = result.equals(&strContent);
	CHECK(bl)
	delete [] buff;
}


