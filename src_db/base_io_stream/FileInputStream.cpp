/*
 * FileInputStream.cpp
 *
 *  Created on: 2018/04/25
 *      Author: iizuka
 */

#include "base_io_stream/FileInputStream.h"
#include "base_io_stream/exceptions.h"

#include "base/UnicodeString.h"
#include "base_io/File.h"

#include "base/StackRelease.h"

namespace alinous {

FileInputStream::FileInputStream(const File* file) noexcept {
	this->file = new File(*file);
}

FileInputStream::FileInputStream(const UnicodeString* fileName) noexcept {
	this->file = new File(fileName);
}

FileInputStream::~FileInputStream() {
	if(this->fd.isOpened()){
		close();
	}
	if(this->file){
		delete this->file;
	}
}

void FileInputStream::open() {
	this->fd = Os::openFile2Read(this->file);

	if(!this->fd.isOpened()){
		UnicodeString* path = this->file->getAbsolutePath();
		StackRelease<UnicodeString> r_path(path);

		throw new FileOpenException(path->towString(), __FILE__, __LINE__);
	}
}

void FileInputStream::close() {
	if(this->fd.isOpened()){
		Os::closeFileDescriptor(&this->fd);
	}
}

int FileInputStream::read(char* b, int size) {
	return InputStream::read(b, size);
}

int FileInputStream::read(char* b, int off, int len) {
	int ret = Os::readFile(&this->fd, b + off, len);
	//if(ret < 0){
	//	throw new FileIOException(__FILE__, __LINE__);
	//}
	return ret;
}

int FileInputStream::available() {
	return this->fd.isOpened();
}

} /* namespace alinous */


