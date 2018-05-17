/*
 * InputStreamReader.cpp
 *
 *  Created on: 2018/05/15
 *      Author: iizuka
 */

#include "base_io_stream/InputStreamReader.h"

#include "base_io_stream/InputStream.h"
#include "base_io/ByteBuffer.h"
#include "base_io/CharBuffer.h"
#include "base/UnicodeString.h"

#include "charsets/CharsetManager.h"

namespace alinous {

InputStreamReader::InputStreamReader(InputStream* in, UnicodeString* charsetName) {
	this->stream = in;
	this->charsetName = new UnicodeString(charsetName);
	init();
}

InputStreamReader::InputStreamReader(InputStream* in) {
	this->stream = in;
	this->charsetName = new UnicodeString(L"utf-8");
	init();
}

void InputStreamReader::init() noexcept {
	this->bytes = nullptr;
	this->chars = nullptr;
	this->buffer = nullptr;
	this->bufferLength = 0;

	this->remainBytes = ByteBuffer::allocate(4);
	this->remainBytes->position(0);

}

InputStreamReader::~InputStreamReader() {
	close();
	delete this->charsetName;

	if(this->buffer != nullptr){
		delete [] buffer;
	}
	if(this->bytes != nullptr){
		delete this->bytes;
	}
	if(this->chars != nullptr){
		delete this->chars;
	}
	if(this->remainBytes != nullptr){
		delete this->remainBytes;
	}
}

void InputStreamReader::close() {
	this->stream->close();
}

int InputStreamReader::read(wchar_t* b, int off, int len) {

	return __read(b, off, len);
}

int InputStreamReader::__read(wchar_t* b, int off, int len) {
	int estimatedLength = len * 2;

	if(this->buffer == nullptr || this->bufferLength != estimatedLength){
		initBuffer(estimatedLength);
	}

	int bred = this->stream->read(this->buffer, this->bufferLength);

	this->bytes->clear();
	this->chars->clear();

	this->remainBytes->position(0);
	while(this->remainBytes->hasRemaining())
	{
		char rb = this->remainBytes->get();
		this->bytes->put(rb);
	}
	this->bytes->put((uint8_t*)this->buffer, bred);

	CharsetManager* mgr = CharsetManager::getInstance();
	CharsetConverter* conv = mgr->getConverter(this->charsetName);
	CharsetDecoder* decoder = conv->newDecoder();


	int newLimit = this->bytes->position();
	this->bytes->limit(newLimit);
	this->bytes->position(0);

	decoder->decodeLoop(this->bytes, this->chars);

	this->remainBytes->clear();
	while(this->bytes->hasRemaining())
	{
		char rb = this->bytes->get();
		this->remainBytes->put(rb);
	}
	int remainPos = this->remainBytes->position();
	this->remainBytes->limit(remainPos);


	int decodedPos = this->chars->position();
	this->chars->position(0);
	this->chars->limit(decodedPos);

	int decodecLength = this->chars->remaining();
	int actualLength = decodecLength <= len ? decodecLength : len;

	int diff = decodecLength - actualLength;
	if(diff > 0){

	}

	return actualLength;
}

void InputStreamReader::initBuffer(int estimatedLength) noexcept {
	if(this->buffer != nullptr){
		delete [] this->buffer;
	}

	this->buffer = new char[estimatedLength]{};
	this->bufferLength = estimatedLength;

	if(this->bytes != nullptr){
		delete this->bytes;
	}
	if(this->chars != nullptr){
		delete this->chars;
	}

	this->bytes = ByteBuffer::allocate(estimatedLength);
	this->chars = CharBuffer::allocate(estimatedLength);
}

int InputStreamReader::read(wchar_t* b, int size) {
	return read(b, size);
}



} /* namespace alinous */
