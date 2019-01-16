/*
 * test_file.cpp
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "charsets/CharsetManager.h"

#include "base_io/File.h"
#include "base/UnicodeString.h"
#include "osenv/funcs.h"

using namespace alinous;


TEST_GROUP(FileTestGroup) {
	TEST_SETUP() {
		env->setup();
	}
	TEST_TEARDOWN() {
		env->teardown();
	}

};

TEST(FileTestGroup, fileLengthError){
	UnicodeString path(L"dfgdfhjghkjghhgkj/gfdgsdfgdfsg");
	File* file = new File(&path);

	int64_t ret = Os::fileLength(file);
	CHECK(ret < 0)

	delete file;
}

TEST(FileTestGroup, test01){
	UnicodeString path(L"/test/path/index.html");
	File* file = new File(&path);

	UnicodeString* ret = file->getAbsolutePath();

	File file2 = *file;

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
}

TEST(FileTestGroup, test04){
	UnicodeString path(L"../dfgdfhjghkjghhgkj/gfdgsdfgdfsg");
	File* file = new File(&path);

	UnicodeString* ret = file->getAbsolutePath();
	delete ret;

	delete file;
}

TEST(FileTestGroup, test05){
	UnicodeString path(L"./dfgdfhjghkjghhgkj/gfdgsdfgdfsg");
	File* file = new File(&path);

	UnicodeString* ret = file->getAbsolutePath();
	delete ret;

	delete file;
}

TEST(FileTestGroup, mkdir01){
	File __dir =  this->env->testCaseDir();

	UnicodeString path(L"target/data_out/");
	UnicodeString path2(L"target/data_out/ext/01");

	File* file = __dir.get(&path);

	file->deleteDir();
	file->mkdirs();

	CHECK(file->exists());

	File* file2 = __dir.get(&path2);
	file2->mkdirs();


	File* file3 = file2->get(L"test.bin");
	FileDescriptor fd = Os::openFile2Write(file3, false, true);
	Os::closeFileDescriptor(&fd);

	file->deleteDir();
	CHECK(!file->exists());

	delete file;
	delete file2;
	delete file3;
}

TEST(FileTestGroup, isFile){
	UnicodeString path(prog);
	File* file = new File(&path);

	bool f = file->isFile();
	CHECK(f);

	f = file->isDirectory();
	CHECK(!f);

	delete file;
}


TEST(FileTestGroup, isFileNotExists){
	UnicodeString path(L"dfgdfhjghkjghhgkj/gfdgsdfgdfsg");
	File* file = new File(&path);

	bool f = file->isFile();
	CHECK(!f);

	f = file->isDirectory();
	CHECK(!f);

	delete file;
}

TEST(FileTestGroup, getDirectory){
	UnicodeString path(prog);
	File file(&path);

	File* dir = file.getDirectory();
	bool f = dir->isFile();
	CHECK(!f);

	f = dir->isDirectory();
	CHECK(f);

	delete dir;
}

TEST(FileTestGroup, list){
	UnicodeString path(prog);
	File file(&path);

	ArrayList<UnicodeString>* files = file.list();

	files->deleteElements();
	delete files;
}

TEST(FileTestGroup, list2){
	UnicodeString path(prog);
	File file(&path);

	File* baseDir = file.getDirectory();

	ArrayList<UnicodeString>* files = baseDir->list();

	int maxLoop = files->size();
	for(int i = 0; i != maxLoop; ++i){
		UnicodeString *p = files->get(i);

		const wchar_t *wstr = p->towString();

		CHECK(Mem::wcscmp(wstr, L".") != 0);
		CHECK(Mem::wcscmp(wstr, L"..") != 0);
	}

	files->deleteElements();
	delete files;

	delete baseDir;
}

TEST(FileTestGroup, projectTestDir){
	File __dir =  this->env->testCaseDir();


}


