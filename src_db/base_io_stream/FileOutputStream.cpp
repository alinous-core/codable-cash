/*
 * FilterOutputStream.cpp
 *
 *  Created on: 2018/04/21
 *      Author: iizuka
 */

#include "debug/debugMacros.h"

#include "base_io_stream/FileOutputStream.h"
#include "base_io_stream/exceptions.h"
#include "base_io/File.h"

#include "base/UnicodeString.h"

#include "base/StackRelease.h"

namespace alinous {


FileOutputStream::FileOutputStream(const File *file) noexcept : OutputStream(), fd(), append(false) {
	this->file = new File(*file);

}
FileOutputStream::FileOutputStream(const File* file, bool append) noexcept : OutputStream(), fd(), append(append) {
	this->file = new File(*file);
}
FileOutputStream::FileOutputStream(const UnicodeString* fileName) noexcept : OutputStream(), fd(), append(false) {
	this->file = new File(fileName);
}
FileOutputStream::FileOutputStream(const UnicodeString* fileName, bool append) noexcept : OutputStream(), fd(), append(append) {
	this->file = new File(fileName);
}

FileOutputStream::~FileOutputStream() {
	if(this->fd.isOpened()){
		close();
	}
	if(this->file){
		delete this->file;
	}
}

/**
 * throws FileOpenException
 */
void FileOutputStream::open(bool sync) {
	this->fd = Os::openFile2Write(this->file, this->append, sync);

	if(!this->fd.isOpened()){
		UnicodeString* path = this->file->getAbsolutePath();
		StackRelease<UnicodeString> r_path(path);

		throw new FileOpenException(path, __FILE__, __LINE__);
	}
}

void FileOutputStream::close() {
	Os::closeFileDescriptor(&this->fd);
}


void FileOutputStream::flush() {
	Os::syncFile(&this->fd);
}

void FileOutputStream::write(const char* buffer, int off, int len) {
	const char* buff2write = buffer + off;
	Os::write2File(&this->fd, buff2write, len);
}

void FileOutputStream::write(int b) {
	char buff[]{};
	buff[0] = b;
	Os::write2File(&this->fd, buff, 1);
}


} /* namespace alinous */
