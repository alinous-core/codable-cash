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

TEST(ReaderTestGroup, construct){
	File projectFolder = this->env->testCaseDir();

	_ST(File, outFile, projectFolder.get(L"out.txt"))
	_ST(UnicodeString, path, outFile->getAbsolutePath())

	UnicodeString charset(L"utf-8");
	FileOutputStream outStream(path);
	outStream.open(false);

	OutputStreamWriter writer(&outStream, &charset);
	writer.write(L"Hello world");
	writer.close();

	FileInputStream stream(path);
	stream.open();
	InputStreamReader reader(&stream, &charset);
}
