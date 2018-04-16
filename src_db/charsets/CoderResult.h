/*
 * CoderResult.h
 *
 *  Created on: 2018/04/16
 *      Author: iizuka
 */

#ifndef CHARSETS_CODERRESULT_H_
#define CHARSETS_CODERRESULT_H_

#include "base/exceptions.h"

namespace alinous {

class CoderResult {
public:
	CoderResult(int type, int length) noexcept;
	virtual ~CoderResult();

	static const CoderResult UNDERFLOW;
	static const CoderResult OVERFLOW;

	static const int CR_UNDERFLOW  = 0;
	static const int CR_OVERFLOW   = 1;
	static const int CR_ERROR_MIN  = 2;
	static const int CR_MALFORMED  = 2;
	static const int CR_UNMAPPABLE = 3;

    // indicating underflow error type
    static const int TYPE_UNDERFLOW = 1;
    // indicating overflow error type
    static const int TYPE_OVERFLOW = 2;
    // indicating malformed-input error type
    static const int TYPE_MALFORMED_INPUT = 3;
    // indicating unmappable character error type
    static const int TYPE_UNMAPPABLE_CHAR = 4;

	static CoderResult malformedForLength(int length){
		CoderResult result(CR_MALFORMED, length);
		return result;
	}

    bool isUnderflow(){
        return this->type == TYPE_UNDERFLOW;
    }
    bool isOverflow(){
        return this->type == TYPE_OVERFLOW;
    }
    bool isUnmappable(){
        return this->type == TYPE_UNMAPPABLE_CHAR;
    }
	static CoderResult unmappableForLength(int length){
		if (length > 0) {
			CoderResult r(TYPE_UNMAPPABLE_CHAR, length);
			return r;
		}
		// niochar.08=The length must be positive: {0}.
		throw new IllegalArgumentException();
	}

private:
	int type;
	int length;
};

} /* namespace alinous */

#endif /* CHARSETS_CODERRESULT_H_ */
