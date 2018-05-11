/*
 * OutputStreamWriter.cpp
 *
 *  Created on: 2018/05/10
 *      Author: iizuka
 */

#include "base_io_stream/OutputStreamWriter.h"
#include "base_io_stream/OutputStream.h"
#include "base/UnicodeString.h"

#include "base/StackRelease.h"
namespace alinous {

OutputStreamWriter::OutputStreamWriter(OutputStream* out, UnicodeString* charsetName) {
	this->out = out;
	this->charsetName = new UnicodeString(charsetName);
}

OutputStreamWriter::OutputStreamWriter(OutputStream* out) {
	this->out = out;
	this->charsetName = new UnicodeString(L"utf-8");
}

OutputStreamWriter::~OutputStreamWriter() {
	close();
	delete charsetName;
}

void OutputStreamWriter::close() {
	flush();
	this->out->close();
}

void OutputStreamWriter::flush() {
	this->out->flush();
}

void OutputStreamWriter::write(const wchar_t* cbuf) {
	Writer::write(cbuf);
}

void OutputStreamWriter::write(const wchar_t* cbuf, int size) {
	Writer::write(cbuf, size);
}

void OutputStreamWriter::write(const wchar_t* cbuf, int off, int len) {
	UnicodeString* outStr = new UnicodeString(cbuf);
	StackRelease<UnicodeString> r_outStr(outStr);

	write(outStr, off, len);
}

void OutputStreamWriter::write(const UnicodeString* str, int off, int len) {
	UnicodeString* outStr = str->substring(off, len);
	StackRelease<UnicodeString> r_outStr(outStr);

	const char* c_str = outStr->toCString();
	int length = Mem::strlen(c_str);
	this->out->write(c_str, length);

	delete [] c_str;
}

void OutputStreamWriter::write(const UnicodeString* str) {
	Writer::write(str);
}

} /* namespace alinous */
