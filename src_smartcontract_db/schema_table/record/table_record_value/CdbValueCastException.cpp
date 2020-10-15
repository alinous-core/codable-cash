/*
 * CdbValueCastException.cpp
 *
 *  Created on: 2020/09/22
 *      Author: iizuka
 */

#include "schema_table/record/table_record_value/CdbValueCastException.h"

namespace codablecash {

CdbValueCastException::CdbValueCastException(const char* srcfile, int srcline) noexcept
				: CdbException(srcfile, srcline) {
}

CdbValueCastException::CdbValueCastException(Exception* cause, const char* srcfile, int srcline) noexcept
				: CdbException(cause, srcfile, srcline) {
}

CdbValueCastException::CdbValueCastException(const wchar_t* message, const char* srcfile, int srcline) noexcept
				: CdbException(message, srcfile, srcline) {
}

CdbValueCastException::CdbValueCastException(const wchar_t* message, Exception* cause, const char* srcfile, int srcline) noexcept
				: CdbException(message, cause, srcfile, srcline) {
}

CdbValueCastException::~CdbValueCastException() {

}

} /* namespace codablecash */
