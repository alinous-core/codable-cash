/*
 * File.h
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */

#ifndef BASE_IO_FILE_H_
#define BASE_IO_FILE_H_

#include "base/ArrayList.h"

namespace alinous {

class UnicodeString;


class File {
public:
	static const UnicodeString pathSeparator;
	static const UnicodeString DOT;
	static const UnicodeString DDOT;

	File(const File& obj) noexcept;
	File &operator=(const File &o) = delete;

	explicit File(const UnicodeString* pathname) noexcept;
	virtual ~File() noexcept;

	UnicodeString* getAbsolutePath() const;
	bool isAbsolute() const noexcept;
	bool exists() const noexcept;
private:
	UnicodeString* __getAbsolutePath() const noexcept;

public:
	bool mkdirs() const noexcept;
	bool deleteFile() const noexcept;
	bool deleteDir() const noexcept;
	bool isDirectory() const noexcept;
	bool isFile() const noexcept;
	int length() const noexcept;

	File* getDirectory() const noexcept;
	File* get(const UnicodeString* seg) const noexcept;
	File* get(const wchar_t* seg) const noexcept;
	ArrayList<UnicodeString>* list() const noexcept;

	bool move(const File* destFile) const noexcept;

private:
	static bool deleteInnerDir(const File* dir) noexcept;
private:
	UnicodeString *path;
};

} /* namespace alinous */

#endif /* BASE_IO_FILE_H_ */
