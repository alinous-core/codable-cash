/*
 * AbstructProgramException.cpp
 *
 *  Created on: 2020/03/06
 *      Author: iizuka
 */

#include "instance_exception/AbstractProgramException.h"

namespace alinous {

AbstractProgramException::AbstractProgramException(const char* srcfile, int srcline) noexcept : Exception(srcfile, srcline) {

}
AbstractProgramException::AbstractProgramException(Exception* cause, const char* srcfile, int srcline) noexcept : Exception(cause, srcfile, srcline) {

}
AbstractProgramException::AbstractProgramException(const wchar_t* message, const char* srcfile, int srcline) noexcept : Exception(message, srcfile, srcline) {

}
AbstractProgramException::AbstractProgramException(const wchar_t* message, Exception* cause, const char* srcfile, int srcline) noexcept : Exception(message, cause, srcfile, srcline) {

}
AbstractProgramException::~AbstractProgramException() {
}
} /* namespace alinous */
