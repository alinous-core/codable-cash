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

#include "exceptions.h"

namespace alinous {

FileStore::FileStore(UnicodeString* dir, UnicodeString* name, DiskCacheManager* cacheManager) noexcept {
	this->cacheManager = cacheManager;
	this->headerFile = nullptr;
	this->file = nullptr;

	this->dir = new UnicodeString(dir);
	this->name = new UnicodeString(name);
}

FileStore::~FileStore() noexcept {
	close();
	delete this->dir;
	delete this->name;
}

void FileStore::createStore(bool del, uint64_t defaultSize) noexcept(false) {
	File baseDir(dir);
	if(!baseDir.exists()){
		baseDir.mkdirs();
	}

	if(del){
		deleteLastFiles(baseDir);
	}

	openFile(baseDir, true);
	this->file->setLength(defaultSize);

	openHeaderFile(baseDir, true);

	close();
}

void FileStore::deleteLastFiles(File& baseDir) const noexcept{
	_ST(UnicodeString, filename, new UnicodeString(this->name))
	filename->append(L".bin");
	_ST(File, storeFile, baseDir.get(filename))
	if(storeFile->exists()){
		storeFile->deleteFile();
	}

	_ST(UnicodeString, headerfilename, new UnicodeString(this->name))
	headerfilename->append(L"-header.bin");
	_ST(File, storeHeaderFile, baseDir.get(headerfilename))
	if(storeHeaderFile->exists()){
		storeHeaderFile->deleteFile();
	}
}


void FileStore::open(bool sync) noexcept(false) {
	File baseDir(dir);

	openFile(baseDir, sync);
	openHeaderFile(baseDir, sync);
}

void FileStore::openFile(File& baseDir, bool sync) {
	_ST(UnicodeString, filename, new UnicodeString(this->name))
	filename->append(L".bin");
	_ST(File, storeFile, baseDir.get(filename))
	this->file = new RandomAccessFile(storeFile, this->cacheManager);

	try{
		this->file->open(sync);
	}catch(Exception* e){
		throw new FileStorageException(L"Failed in Opening file.", e, __FILE__, __LINE__);
	}
}

void FileStore::openHeaderFile(File& baseDir, bool sync) {
	_ST(UnicodeString, headerfilename, new UnicodeString(this->name))
	headerfilename->append(L"-header.bin");
	_ST(File, storeHeaderFile, baseDir.get(headerfilename))
	this->headerFile = new RandomAccessFile(storeHeaderFile, this->cacheManager);

	try{
		this->headerFile->open(sync);
	}catch(Exception* e){
		throw new FileStorageException(L"Failed in Opening header file.", e, __FILE__, __LINE__);
	}
}

bool FileStore::isOpened() const noexcept {
	return this->file != nullptr;
}

void FileStore::close() noexcept {
	if(this->headerFile != nullptr){
		this->headerFile->close();
		delete this->headerFile;
		this->headerFile = nullptr;
	}
	if(this->file != nullptr){
		this->file->close();
		delete this->file;
		this->file = nullptr;
	}
}


} /* namespace alinous */
