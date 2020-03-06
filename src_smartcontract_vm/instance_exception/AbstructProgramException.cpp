/*
 * AbstructProgramException.cpp
 *
 *  Created on: 2020/03/06
 *      Author: iizuka
 */

#include "instance_exception/AbstructProgramException.h"

namespace alinous {

AbstructProgramException::AbstructProgramException(const char* srcfile, int srcline) noexcept : Exception(srcfile, srcline) {

}
AbstructProgramException::AbstructProgramException(Exception* cause, const char* srcfile, int srcline) noexcept : Exception(cause, srcfile, srcline) {

}
AbstructProgramException::AbstructProgramException(const wchar_t* message, const char* srcfile, int srcline) noexcept : Exception(message, srcfile, srcline) {

}
AbstructProgramException::AbstructProgramException(const wchar_t* message, Exception* cause, const char* srcfile, int srcline) noexcept : Exception(message, cause, srcfile, srcline) {

}
AbstructProgramException::~AbstructProgramException() {
}
} /* namespace alinous */
