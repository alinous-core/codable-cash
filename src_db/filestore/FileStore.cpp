/*
 * FileStore.cpp
 *
 *  Created on: 2018/05/18
 *      Author: iizuka
 */

#include "filestore/FileStore.h"

#include "random_access_file/DiskCacheManager.h"
#include "random_access_file/RandomAccessFile.h"
#include "base/UnicodeString.h"
#include "base_io/File.h"

#include "base/StackRelease.h"


namespace alinous {

FileStore::FileStore(UnicodeString* dir, UnicodeString* name, DiskCacheManager* cacheManager) noexcept {
	this->cacheManager = cacheManager;
	this->headerFile = nullptr;
	this->file = nullptr;

	this->dir = new UnicodeString(dir);
	this->name = new UnicodeString(name);
}

FileStore::~FileStore() noexcept {
	if(this->headerFile != nullptr){
		delete this->headerFile;
	}
	if(this->file != nullptr){
		delete this->file;
	}
	delete this->dir;
	delete this->name;
}

void FileStore::open() {
	File baseDir(dir);
	if(!baseDir.exists()){
		baseDir.mkdirs();
	}

	_ST(UnicodeString, filename, new UnicodeString(this->name))
	filename->append(L".bin");
	_ST(File, storeFile, baseDir.get(filename))
	this->file = new RandomAccessFile(storeFile, this->cacheManager);

	_ST(UnicodeString, headerfilename, new UnicodeString(this->name))
	headerfilename->append(L".bin");
	_ST(File, storeHeaderFile, baseDir.get(headerfilename))
	this->file = new RandomAccessFile(storeHeaderFile, this->cacheManager);
}

bool FileStore::isOpened() const noexcept {
	return this->file != nullptr;
}

void FileStore::close() noexcept {

}

} /* namespace alinous */
