/*
 * Base58.cpp
 *
 *  Created on: 2018/12/31
 *      Author: iizuka
 */

#include "bc_base/Base58.h"

#include "base/UnicodeString.h"
#include "base_io/ByteBuffer.h"
#include "base/StackRelease.h"

namespace codablecash {

UnicodeString* Base58::encode(const char* input, int inputLength) noexcept {
    if (inputLength == 0) {
        return new UnicodeString(L"");
    }

    // Count leading zeros.
    int zeros = 0;
    while (zeros < inputLength && input[zeros] == 0) {
        ++zeros;
    }

    char* input2 = new char[inputLength]{};
    StackArrayRelease<char> __st_input2(input2);
    for(int i = 0; i != inputLength; ++i){
    	input2[i] = input[i];
    }


    int encodedLength = inputLength * 2;
    char* encoded = new char[encodedLength]{}; // upper bound
    StackArrayRelease<char> __st_encoded(encoded);

    int outputStart = encodedLength;
    for (int inputStart = zeros; inputStart < inputLength; ) {
    	encoded[--outputStart] = ALPHABET[divmod(input2, inputLength, inputStart, 256, 58)];
    	if (input2[inputStart] == 0) {
    		++inputStart; // optimization - skip leading zeros
    	}
    }

    while (outputStart < encodedLength && encoded[outputStart] == ENCODED_ZERO) {
        ++outputStart;
    }

	while (--zeros >= 0) {
		encoded[--outputStart] = ENCODED_ZERO;
	}

    UnicodeString* str = new UnicodeString(L"");
    int maxLoop = encodedLength - outputStart;
    for(int i = 0; i != maxLoop; ++i){
    	wchar_t ch = encoded[outputStart + i];
    	str->append(ch);
    }

	return str;
}

ByteBuffer* Base58::decode(UnicodeString* input) noexcept {
	int* INDEXES = initIndex();

	if(input->length() == 0) {
		return nullptr;
	}

	int input58Length = input->length();
	char* input58 = new char[input->length()];
	StackArrayRelease<char> __st_input58(input58);
	for (int i = 0; i < input->length(); ++i) {
		 wchar_t c = input->charAt(i);
		 int digit = c < 128 ? INDEXES[c] : -1;
		 if (digit < 0) {
			return nullptr;
		 }
		 input58[i] = (char) digit;
	}

	int zeros = 0;
	while (zeros < input58Length && input58[zeros] == 0) {
		++zeros;
    }

	int decodedLength = input->length();
	char* decoded = new char[decodedLength];
	StackArrayRelease<char> __st_decoded(decoded);
	int outputStart = decodedLength;
	for (int inputStart = zeros; inputStart < input58Length; ) {
		decoded[--outputStart] = divmod(input58, input58Length, inputStart, 58, 256);
		if (input58[inputStart] == 0) {
			++inputStart;
		}
	}

	while (outputStart < decodedLength && decoded[outputStart] == 0) {
		++outputStart;
	}

	ByteBuffer* result = ByteBuffer::allocate(decodedLength - (outputStart - zeros));

	result->put((const uint8_t*)decoded, outputStart - zeros, decodedLength - (outputStart - zeros));

	return result;
}

char Base58::divmod(char* number, int numberLength, int firstDigit, int base, int divisor) {
	int remainder = 0;
	for (int i = firstDigit; i < numberLength; i++) {
		int digit = (int) (number[i] & 0xFF);
		int temp = remainder * base + digit;
		number[i] = (char) (temp / divisor);
		remainder = temp % divisor;
	}
	return (char) remainder;
}

int* Base58::initIndex() {
	static int indexes[128]{-1};
	static bool initdone = false;

	if(!initdone){
		initdone = true;
		for (int i = 0; i < 58; i++) {
			indexes[ALPHABET[i]] = i;
		}
	}

	return indexes;
}

} /* namespace codablecash */

