/*
 * FilterOutputStream.cpp
 *
 *  Created on: 2018/04/21
 *      Author: iizuka
 */

#include "debug/debugMacros.h"

#include "base_io_stream/FileOutputStream.h"
#include "base_io/File.h"

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

	}
	if(this->file){
		delete this->file;
	}
}

void FileOutputStream::open(bool sync) {
	this->fd = Os::openFile2Write(this->file, this->append, sync);
}

void FileOutputStream::write(const RawArrayPrimitive<char>* buffer, int off, int len) {

}

void FileOutputStream::write(int b) {

}

} /* namespace alinous */
