/*
 * exceptions.h
 *
 *  Created on: 2018/12/25
 *      Author: iizuka
 */

#ifndef BTREE_EXCEPTIONS_H_
#define BTREE_EXCEPTIONS_H_

#include "base/Exception.h"

namespace alinous {

class NodeStructureException: public Exception {
public:
	NodeStructureException(const char* srcfile, int srcline) noexcept;
	NodeStructureException(Exception* cause, const char* srcfile, int srcline)
			noexcept;
	NodeStructureException(const wchar_t* message, const char* srcfile,
			int srcline) noexcept;
	NodeStructureException(const wchar_t* message, Exception* cause,
			const char* srcfile, int srcline) noexcept;
	virtual ~NodeStructureException();
	static const wchar_t* defaultMessage;
};

} /* namespace alinous */


#endif /* BTREE_EXCEPTIONS_H_ */

