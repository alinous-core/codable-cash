/*
 * UnicodeString.cpp
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */


#include <regex>
#include <iostream>

#include "debug/debugMacros.h"

#include "base/UnicodeString.h"

#include "osenv/memory.h"

#include "base/StackRelease.h"
#include "base_io/CharBuffer.h"
#include "base_io/ByteBuffer.h"
#include "charsets/CharsetManager.h"

namespace alinous {

UnicodeString& UnicodeString::operator=(const UnicodeString &o) {
	if(&o != this){
		if(this->buff == nullptr){
			this->buff = new RawArrayPrimitive<wchar_t>(32);
		}
		this->buff->reset();

		int maxLoop = o.length();
		for(int i = 0; i != maxLoop; ++i){
			wchar_t ch = o.charAt(i);
			append(ch);
		}
	}

	return *this;
}

UnicodeString::UnicodeString() noexcept {
	this->buff = nullptr;
	this->__hashCode = 0;
}

UnicodeString::UnicodeString(const wchar_t* str) noexcept {
	this->buff = new RawArrayPrimitive<wchar_t>(32);
	this->__hashCode = 0;
	const wchar_t* ptr = str;
	while(*ptr != 0){
		wchar_t ch = *ptr;
		__append(ch);
		ptr++;
	}

	__closeString();
}

UnicodeString::UnicodeString(const wchar_t* str, int cap) noexcept {
	this->buff =  new RawArrayPrimitive<wchar_t>(cap);
	this->__hashCode = 0;

	const wchar_t* ptr = str;
	while(*ptr != 0){
		wchar_t ch = *ptr;
		__append(ch);
		ptr++;
	}

	__closeString();
}
/*
UnicodeString::UnicodeString(const wchar_t* str, int offset, int count) noexcept {
	this->buff =  new RawArrayPrimitive<wchar_t>(count);
	this->__hashCode = 0;

	for(int i = 0; i != count; ++i){
		wchar_t ch = str[offset + i];
		__append(ch);
	}

	__closeString();
}
*/
UnicodeString::UnicodeString(const char* str) noexcept {
	UnicodeString utf8str(CharsetManager::UTF_8());
	CharsetConverter* cnv =  CharsetManager::getInstance()->getConverter(&utf8str);

	int len = Mem::strlen(str) + 1;
	ByteBuffer *in = ByteBuffer::wrap((const uint8_t*)str, len);
	CharBuffer * out = CharBuffer::allocate(len * 2);
	StackRelease<ByteBuffer> _in(in);
	StackRelease<CharBuffer> _out(out);

	CharsetDecoder* dec = cnv->newDecoder();

	dec->decodeLoop(in, out);

	int pos = out->position();
	this->buff =  new RawArrayPrimitive<wchar_t>(pos + 1);
	this->__hashCode = 0;

	out->position(0);
	for(int i = 0; i != pos; ++i){
		wchar_t ch = out->get();
		if(ch == 0){
			break;
		}

		__append(ch);
	}
	__closeString();
}

UnicodeString::UnicodeString(const UnicodeString* ptr) noexcept{
	this->buff =  new RawArrayPrimitive<wchar_t>(ptr->length() + 1);
	this->__hashCode = 0;

	int length = ptr->length();
	for(int i = 0; i != length; ++i){
		wchar_t ch = ptr->charAt(i);
		__append(ch);
	}

	__closeString();
}

UnicodeString::UnicodeString(const UnicodeString& inst) noexcept {
	this->buff =  new RawArrayPrimitive<wchar_t>(inst.length() + 1);
	this->__hashCode = 0;

	int length = inst.length();
	for(int i = 0; i != length; ++i){
		wchar_t ch = inst.charAt(i);
		__append(ch);
	}

	__closeString();
}

UnicodeString::~UnicodeString() {
	delete buff;
}

UnicodeString* UnicodeString::__append(wchar_t ch) noexcept {
	this->buff->addElement(ch);

	return this;
}

void UnicodeString::__closeString() noexcept {
	this->buff->addElement(L'\0');
	this->buff->backLast();

	const int count = length();
    if (count == 0) {
    	this->__hashCode = 0;
        return;
    }
    int hash = 0;
    for (int i = 0; i < count; i++) {
        hash = charAt(i) + ((hash << 5) - hash);
    }
    this->__hashCode = hash;
}


UnicodeString& UnicodeString::append(const wchar_t ch) noexcept
{
	__append(ch);
	__closeString();

	return *this;
}

UnicodeString& UnicodeString::append(const wchar_t* str) noexcept
{
	int len = Mem::wstrlen(str);
	for(int i = 0; i != len; ++i){
		wchar_t ch = str[i];
		__append(ch);
	}

	__closeString();
	return *this;
}

UnicodeString& UnicodeString::append(const wchar_t* str, int len) noexcept {
	for(int i = 0; i != len; ++i){
		wchar_t ch = str[i];
		__append(ch);
	}

	__closeString();
	return *this;
}

UnicodeString& UnicodeString::append(const int16_t* str, int offset, int len) noexcept {
	for(int i = 0; i != len; ++i){
		wchar_t ch = str[offset + i];
		__append(ch);
	}

	__closeString();
	return *this;
}

UnicodeString& UnicodeString::append(const wchar_t* str, int offset, int len) noexcept {
	for(int i = 0; i != len; ++i){
		wchar_t ch = str[offset + i];
		__append(ch);
	}

	__closeString();
	return *this;
}

UnicodeString* UnicodeString::valueOf(const int16_t* str, int offset, int len) {
	UnicodeString* ret = new UnicodeString(L"");

	for(int i = 0; i != len; ++i){
		wchar_t ch = str[offset + i];
		ret->append(ch);
	}

	return ret;
}

UnicodeString& UnicodeString::append(const UnicodeString* str) noexcept {
	int len = str->length();

	for(int i = 0; i != len; ++i){
		wchar_t ch = str->charAt(i);
		__append(ch);
	}

	__closeString();

	return *this;
}

UnicodeString& UnicodeString::append(const int v) noexcept
{
	if(v == 0){
		append(L"0");
		return *this;
	}

	int value = v;
	if(value < 0){
		value = value * -1;
		__append(L'-');
	}

	wchar_t buf[64] = {};
	int offset = 0;
	while(value != 0){
		int d = value % 10;
		value /= 10;

		S_PRINTF(&buf[offset], sizeof(buff), L"%d", d);

		offset++;
	}

	for(int i = offset - 1; i >= 0; i--){
		__append(buf[i]);
	}

	__closeString();

	return *this;
}

UnicodeString* UnicodeString::replace(wchar_t last, wchar_t next) const noexcept {
	UnicodeString *retStr =  new UnicodeString(L"");

	const int maxLoop = this->buff->numArray;
	for(int i = 0; i != maxLoop; ++i){
		wchar_t ch = this->buff->get(i);
		if(ch == last){
			retStr->__append(next);
		}else{
			retStr->__append(ch);
		}
	}

	retStr->__closeString();

	return retStr;
}

const char* UnicodeString::toCString() const {
	UnicodeString utf8(L"utf-8");
	return toCString(&utf8);
}
const char* UnicodeString::toCString(const UnicodeString* charset) const {
	CharBuffer* in = CharBuffer::wrap(this);
	ByteBuffer* out = ByteBuffer::allocate(this->length() * 2 + 1);


	CharsetManager* mgr = CharsetManager::getInstance();
	CharsetConverter* cnv = mgr->getConverter(charset);

	CharsetEncoder* encoder = cnv->newEncoder();
	encoder->encodeLoop(in ,out);

	int size = out->position() + 1;
	char* retBuff = new char[size];

	Mem::memcpy(retBuff, out->data->getRoot(), size);
	retBuff[size - 1] = '\0';

	delete in;
	delete out;

	return retBuff;
}

const wchar_t* UnicodeString::towString() const noexcept
{
	return this->buff->root;
}

UnicodeString* UnicodeString::toLowerCase() const noexcept
{
	UnicodeString* newStr = new UnicodeString(L"");

	const int size = this->buff->size();
	for(int i = 0; i != size; ++i){
		wchar_t newCh = towlower(this->buff->get(i));

		newStr->__append(newCh);
	}

	newStr->__closeString();

	return newStr;
}
UnicodeString* UnicodeString::toUpperCase() const noexcept
{
	UnicodeString* newStr = new UnicodeString(L"");

	const int size = this->buff->size();
	for(int i = 0; i < size; i++){
		wchar_t newCh = Mem::toupper(this->buff->get(i));

		newStr->__append(newCh);
	}

	newStr->__closeString();

	return newStr;
}

bool UnicodeString::startsWith(const UnicodeString& str) const noexcept {
	return startsWith(&str);
}

bool UnicodeString::startsWith(const UnicodeString* str) const noexcept
{
	return startsWith(str, 0);
}
bool UnicodeString::startsWith(const UnicodeString* str, int start) const noexcept {
	const int length = this->length();

	int pos = 0;
	wchar_t match;
	for(int i = start; i < length; i++){
		wchar_t ch = this->charAt(i);
		pos = getNextMatch(pos, str, &match);
		if(pos < 0){
			return true;
		}

		if(match != ch){
			return false;
		}
	}

	pos = getNextMatch(pos, str, &match);
	if(pos < 0){
		return true;
	}

	return false;

}

bool UnicodeString::endsWith(const UnicodeString* str) const noexcept {
	const int length = str->length();
	int pos = this->length() - 1;
	int posTarget = length - 1;

	if(length > this->length()){
		return false;
	}

	for(int i = 0; i != length; ++i){
		if(this->charAt(pos--) != str->charAt(posTarget--)){
			return false;
		}
	}

	return true;
}

int UnicodeString::getNextMatch(int pos, const UnicodeString* str, wchar_t* next) const noexcept {
	if(str->length() <= pos){
		return -1;
	}

	*next = str->charAt(pos++);

	return pos;
}


UnicodeString* UnicodeString::substring(int begin) const noexcept
{
	return substring(begin, length());
}
UnicodeString* UnicodeString::substring(int begin, int end) const noexcept
{
	UnicodeString* newStr =  new UnicodeString(L"");

	const wchar_t *str = towString();

	const int max = end;
	for(int i = begin; i != max; i++){
		newStr->__append(str[i]);
	}
	newStr->__closeString();

	return newStr;
}
int UnicodeString::indexOf(const UnicodeString* str) const noexcept {
	return indexOf(str, 0);
}
int UnicodeString::indexOf(const UnicodeString* str, int lastIndex) const noexcept {
	wchar_t ch =str->charAt(0);
	int index = indexOf(ch, lastIndex);
	while(index >= 0){
		if(this->startsWith(str, index)){
			return index;
		}

		index++;
		if(this->length() <= index){
			return -1;
		}

		index = indexOf(ch, index);
	}

	return -1;
}
int UnicodeString::indexOf(wchar_t ch) const noexcept {
	return indexOf(ch, 0);
}
int UnicodeString::indexOf(wchar_t ch, int lastIndex) const noexcept {
	const int length = this->length();
	for(int i = lastIndex; i < length; i++){
		if(this->charAt(i) == ch){
			return i;
		}
	}

	return -1;
}
int UnicodeString::lastIndexOf(wchar_t ch) const noexcept {
	return lastIndexOf(ch, length() - 1);
}
int UnicodeString::lastIndexOf(wchar_t ch, int lastIndex) const noexcept {
	for (int i = lastIndex; i >= 0; i--) {
		if(this->charAt(i) == ch){
			return i;
		}
	}

	return -1;
}
int UnicodeString::lastIndexOf(const UnicodeString* str) const noexcept {
	return lastIndexOf(str, length());
}
int UnicodeString::lastIndexOf(const UnicodeString* str, int lastIndex) const noexcept {
	if(lastIndex > this->length()){
		lastIndex = this->length();
	}
	if(lastIndex < str->length()){
		return -1;
	}

	wchar_t ch = str->charAt(0);
	int index = lastIndexOf(ch, lastIndex);
	while(index >= 0){
		if(this->startsWith(str, index)){
			return index;
		}

		index--;
		if(index < 0){
			return -1;
		}

		index = lastIndexOf(ch, index);
	}

	return -1;
}

UnicodeString* UnicodeString::insert(int position, wchar_t ch) noexcept {
	buff->addElement(ch ,position);

	__closeString();

	return this;
}

UnicodeString* UnicodeString::insert(int dstOffset, UnicodeString* str) noexcept {
	const int count = str->length();
	int position = dstOffset;
	for(int i = 0; i != count; ++i){
		insert(position++, str->charAt(i));
	}

	return this;
}

UnicodeString* UnicodeString::insert(int dstOffset, const wchar_t* str, int offset, int count) noexcept {
	int position = dstOffset;
	for(int i = 0; i != count; ++i){
		insert(position++, str[i]);
	}
	return this;
}

ArrayList<UnicodeString>* UnicodeString::split(const UnicodeString* regex) const noexcept {
	return split(regex, true);
}

ArrayList<UnicodeString>* UnicodeString::split(const UnicodeString* regex, bool addBlankString) const noexcept {
	ArrayList<UnicodeString>* list = new ArrayList<UnicodeString>();


	const std::wstring str = towString();
	std::wregex wreg(regex->towString());

	std::wsregex_token_iterator it(str.begin(), str.end(), wreg, -1), end;
	for (; it != end; ++it) {
		const std::wstring res = *it;//(it->first, it->second);

		int len = res.length();
		if(!addBlankString && len == 0){
			continue;
		}
		const wchar_t *cwstr = res.c_str();

		UnicodeString* result = new UnicodeString(cwstr);
		list->addElement(result);
	}

	return list;
}


wchar_t UnicodeString::get(int i) const noexcept { return this->buff->get(i); };
wchar_t UnicodeString::charAt(int index) const noexcept
{
	return this->buff->get(index);
};

int UnicodeString::length() const noexcept {
	return this->buff->size();
}

int UnicodeString::isEmpty() const noexcept {
	return this->buff->size() == 0;
}

bool UnicodeString::equals(const UnicodeString& str) const noexcept {
	return equals(&str);
}

bool UnicodeString::equals(const UnicodeString* str) const noexcept
{
	int hash = str->hashCode();
	int _this_hash = this->hashCode();
	if(hash != _this_hash){
		return false;
	}

	return __equals(str);
}

bool UnicodeString::equals(const wchar_t* str) const noexcept {
	UnicodeString inst(str);

	return equals(inst);
}

bool UnicodeString::__equals(const UnicodeString* str) const noexcept{
	const int size = str->length();
	if(size != this->length()){
		return false;
	}
	for(int i = 0; i < size; i++){
		wchar_t src = str->get(i);
		wchar_t dest = this->get(i);

		if(src != dest){
			return false;
		}
	}

	return true;
}

int UnicodeString::hashCode() const noexcept {
    return this->__hashCode;
}

int UnicodeString::ValueCompare::operator () (const UnicodeString* const a, const UnicodeString* const b) const {
	const wchar_t* astr = a->towString();
	const wchar_t* bstr = b->towString();

	int res = Mem::wcscmp(astr, bstr);

	return res;
}

} /* namespace alinous */
