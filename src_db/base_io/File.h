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
	static const UnicodeString pathSeparator;

	File(const UnicodeString* pathname) noexcept;
	virtual ~File() noexcept;

	UnicodeString* getAbsolutePath() const;
	bool isAbsolute() const noexcept;
private:
	UnicodeString* __getAbsolutePath() const noexcept;

public:
	bool mkdirs() const noexcept;

private:
	UnicodeString *path;
};

} /* namespace alinous */

#endif /* BASE_IO_FILE_H_ */
