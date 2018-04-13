/*
 * UnicodeString.cpp
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */

#include <base/UnicodeString.h>

namespace alinous {


UnicodeString::UnicodeString(const wchar_t* str) throw() {
	this->buff =  new RawArrayPrimitive<wchar_t>(32);
	this->__hashCode = 0;
	const wchar_t* ptr = str;
	while(*ptr != 0){
		wchar_t ch = *ptr;
		append(ch);
		ptr++;
	}
}

UnicodeString::UnicodeString(const wchar_t* str, int cap) throw() {
	this->buff =  new RawArrayPrimitive<wchar_t>(cap);
	this->__hashCode = 0;

	const wchar_t* ptr = str;
	while(*ptr != 0){
		wchar_t ch = *ptr;
		append(ch);
		ptr++;
	}
}

UnicodeString::UnicodeString(const UnicodeString* ptr) throw(){
	this->buff =  new RawArrayPrimitive<wchar_t>(32);
	this->__hashCode = 0;

	int length = ptr->length();
	for(int i = 0; i != length; ++i){
		wchar_t ch = ptr->charAt(i);
		append(ch);
	}
}

UnicodeString::~UnicodeString() {
	delete buff;
}


UnicodeString* UnicodeString::append(wchar_t ch)
{
	this->buff->addElement(ch);
	this->__hashCode = 0;

	return this;
}

char* UnicodeString::toCString(){
	// TODO: debug
	return nullptr;
}

wchar_t UnicodeString::get(int i) const throw() { return this->buff->get(i); };
wchar_t UnicodeString::charAt(int index) const throw()
{
	return this->buff->get(index);
};

int UnicodeString::length() const throw() {
	return this->buff->size();
}

int UnicodeString::isEmpty() const throw() {
	return this->buff->size() == 0;
}

bool UnicodeString::equals(UnicodeString* str) throw()
{
	int hash = str->hashCode();
	if(hash != this->hashCode()){
		return false;
	}

	return __equals(str);
}

bool UnicodeString::__equals(UnicodeString* str) const throw(){
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

int UnicodeString::hashCode()  throw() {
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

} /* namespace alinous */
