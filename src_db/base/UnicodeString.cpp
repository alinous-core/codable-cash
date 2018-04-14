/*
 * UnicodeString.cpp
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */

#include <base/UnicodeString.h>

#include <wchar.h>
#include <wctype.h>

namespace alinous {


UnicodeString::UnicodeString(const wchar_t* str) noexcept {
	this->buff =  new RawArrayPrimitive<wchar_t>(32);
	this->__hashCode = 0;
	const wchar_t* ptr = str;
	while(*ptr != 0){
		wchar_t ch = *ptr;
		append(ch);
		ptr++;
	}
}

UnicodeString::UnicodeString(const wchar_t* str, int cap) noexcept {
	this->buff =  new RawArrayPrimitive<wchar_t>(cap);
	this->__hashCode = 0;

	const wchar_t* ptr = str;
	while(*ptr != 0){
		wchar_t ch = *ptr;
		append(ch);
		ptr++;
	}
}

UnicodeString::UnicodeString(const UnicodeString* ptr) noexcept{
	this->buff =  new RawArrayPrimitive<wchar_t>(ptr->length() + 1);
	this->__hashCode = 0;

	int length = ptr->length();
	for(int i = 0; i != length; ++i){
		wchar_t ch = ptr->charAt(i);
		append(ch);
	}
}

UnicodeString::UnicodeString(const UnicodeString& inst) noexcept {
	this->buff =  new RawArrayPrimitive<wchar_t>(inst.length() + 1);
	this->__hashCode = 0;

	int length = inst.length();
	for(int i = 0; i != length; ++i){
		wchar_t ch = inst.charAt(i);
		append(ch);
	}
}

UnicodeString::~UnicodeString() {
	delete buff;
}


UnicodeString* UnicodeString::append(wchar_t ch) noexcept
{
	this->buff->addElement(ch);
	this->__hashCode = 0;

	return this;
}

UnicodeString* UnicodeString::append(UnicodeString* str) noexcept {
	int len = str->length();

	for(int i = 0; i != len; ++i){
		wchar_t ch = str->charAt(i);
		append(ch);
	}

	return this;
}

char* UnicodeString::toCString(){
	// TODO: debug
	return nullptr;
}

const wchar_t* UnicodeString::towString() const noexcept
{
	if(this->buff->currentSize == this->buff->numArray){
		this->buff->addElement(0);
		this->buff->remove(this->buff->numArray - 1);
	}else{
		//wchar_t lastCh = this->buff->get(this->buff->numArray);
		//if(lastCh != 0x0){
		//	this->buff->addElement(0);
		//	this->buff->remove(this->buff->numArray - 1);
		//}
		this->buff->addElement(0);
		this->buff->remove(this->buff->numArray - 1);
	}
	this->buff->root[this->buff->numArray] = L'\0';

	return this->buff->root;
}

UnicodeString* UnicodeString::toLowerCase() const noexcept
{
	UnicodeString* newStr = new UnicodeString(L"");

	const int size = this->buff->size();
	for(int i = 0; i != size; ++i){
		wchar_t newCh = towlower(this->buff->get(i));

		newStr->append(newCh);
	}

	return newStr;
}
UnicodeString* UnicodeString::toUpperCase() const noexcept
{
	UnicodeString* newStr = new UnicodeString(L"");

	const int size = this->buff->size();
	for(int i = 0; i < size; i++){
		wchar_t newCh = towupper(this->buff->get(i));

		newStr->append(newCh);
	}

	return newStr;
}

bool UnicodeString::startsWith(UnicodeString* str) const noexcept
{
	return startsWith(str, 0);
}
bool UnicodeString::startsWith(UnicodeString* str, int start) const noexcept {
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

bool UnicodeString::endsWith(UnicodeString* str) const noexcept {
	const int length = str->length();
	int pos = this->length() - 1;
	int posTarget = length - 1;

	for(int i = 0; i != length; ++i){
		if(this->charAt(pos--) != str->charAt(posTarget--)){
			return false;
		}
	}

	return true;
}

int UnicodeString::getNextMatch(int pos, UnicodeString* str, wchar_t* next) const noexcept {
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
		newStr->append(str[i]);
	}

	return newStr;
}
int UnicodeString::indexOf(UnicodeString* str) const noexcept {
	return indexOf(str, 0);
}
int UnicodeString::indexOf(UnicodeString* str, int lastIndex) const noexcept {
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
int UnicodeString::lastIndexOf(UnicodeString* str) const noexcept {
	return lastIndexOf(str, length());
}
int UnicodeString::lastIndexOf(UnicodeString* str, int lastIndex) const noexcept {
	if(lastIndex > this->length()){
		lastIndex = this->length();
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

		index = indexOf(ch, index);
	}

	return -1;
}

UnicodeString* UnicodeString::insert(int position, wchar_t ch) noexcept {
	buff->addElement(ch ,position);
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

UnicodeString* UnicodeString::insert(int dstOffset, wchar_t* str, int offset, int count) noexcept {
	int position = dstOffset;
	for(int i = 0; i != count; ++i){
		insert(position++, str[i]);
	}
	return this;
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

bool UnicodeString::equals(UnicodeString* str) noexcept
{
	int hash = str->hashCode();
	if(hash != this->hashCode()){
		return false;
	}

	return __equals(str);
}

bool UnicodeString::__equals(UnicodeString* str) const noexcept{
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

int UnicodeString::hashCode()  noexcept {
    if (this->__hashCode == 0) {
    	const int count = length();
        if (count == 0) {
            return 0;
        }
        int hash = 0;
        for (int i = 0; i < count; i++) {
            hash = charAt(i) + ((hash << 5) - hash);
        }
        this->__hashCode = hash;
    }
    return this->__hashCode;
}

int UnicodeString::ValueCompare::operator () (const UnicodeString* const a, const UnicodeString* const b) const {
	const wchar_t* astr = a->towString();
	const wchar_t* bstr = b->towString();

	int res = wcscmp(astr, bstr);

	return res;
}

} /* namespace alinous */
