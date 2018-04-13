/*
 * File.h
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */

#ifndef BASE_IO_FILE_H_
#define BASE_IO_FILE_H_

namespace alinous {

class UnicodeString;

class File {
public:
	File(const UnicodeString* pathname) throw();
	virtual ~File() throw();

private:
	UnicodeString *pathSeparator;
	UnicodeString *path;
};

} /* namespace alinous */

#endif /* BASE_IO_FILE_H_ */
