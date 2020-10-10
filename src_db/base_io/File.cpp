/*
 * File.cpp
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */

#include "debug/debugMacros.h"

#include "base_io/File.h"
#include "base/UnicodeString.h"
#include "base/StackRelease.h"

#include "osenv/funcs.h"



namespace alinous {

const UnicodeString File::pathSeparator(PATH_SEPARATOR);
const UnicodeString File::DOT(L".");
const UnicodeString File::DDOT(L"..");

File::File(const File& obj) noexcept {
	this->path = new UnicodeString(obj.path);
}

File::File(const UnicodeString* pathname) noexcept {
	this->path = new UnicodeString(pathname);
}

File::~File() noexcept {
	delete this->path;
}

UnicodeString* File::getAbsolutePath() const {
	if(isAbsolute()){
		return new UnicodeString(this->path);
	}

	UnicodeString* retPath = __getAbsolutePath();
	if(retPath != nullptr){
		return retPath;
	}


	File* tmpFile = new File(&DOT);
	StackRelease<File> r_tmpFile(tmpFile);

	UnicodeString* homeDir = tmpFile->__getAbsolutePath();

	ArrayList<UnicodeString>* parts = this->path->split(&pathSeparator, false);
	ArrayList<UnicodeString>* realParts = homeDir->split(&pathSeparator, false);
	delete homeDir;

	ArrayList<UnicodeString> removeList;
	removeList.addAll(parts);
	removeList.addAll(realParts);

	int const maxLoop = parts->size();
	for(int i = 0; i != maxLoop; ++i){
		UnicodeString* cseg = parts->get(i);

		if(cseg->equals(&DOT)){
			continue;
		}
		else if(cseg->equals(&DDOT)){
			int top = realParts->size() - 1;
			realParts->remove(top);
		}
		else{
			realParts->addElement(cseg);
		}
	}

	retPath = new UnicodeString(L"", 512);
	int const finalLoop = realParts->size();
	for(int i = 0; i != finalLoop; ++i){
		UnicodeString* seg = realParts->get(i);

		retPath->append(&pathSeparator);
		retPath->append(seg);
	}

	removeList.deleteElements();
	delete parts;
	delete realParts;

	return retPath;

}

UnicodeString* File::__getAbsolutePath() const noexcept {
	const char* src = path->toCString();
	char* realp = Os::realpath(src, nullptr);

	delete [] src;

	if(realp == nullptr){
		return nullptr;
	}

	UnicodeString* ret = new UnicodeString(realp);

	Os::realpath_free(realp);

	return ret;
}

bool File::isAbsolute() const noexcept {
	return this->path->startsWith(&pathSeparator) && this->path->indexOf(&DDOT) < 0;
}

bool File::mkdirs() const noexcept {
	UnicodeString* src = getAbsolutePath();
	StackRelease<UnicodeString> r_src(src);

	ArrayList<UnicodeString>* parts = src->split(&pathSeparator, false);

	UnicodeString *path = new UnicodeString(L"", 512);
	StackRelease<UnicodeString> r_path(path);

	int const maxLoop = parts->size();
	for(int i = 0; i != maxLoop; ++i){
		UnicodeString* seg = parts->get(i);

		path->append(&pathSeparator);
		path->append(seg);

		File file(path);

		bool ex = file.exists();
		if(!ex){
			Os::mkdirs(path ,true, true, true
					,true, true, true
					,true, true, true);
		}
	}

	parts->deleteElements();
	delete parts;

	return true;
}

bool File::deleteFile() const noexcept
{
	return Os::deleteFile(path);
}

bool File::deleteDir() const noexcept {
	return deleteInnerDir(this);
}



bool File::deleteInnerDir(const File* dir) noexcept {
	ArrayList<UnicodeString>* _list = dir->list();
	StackRelease<ArrayList<UnicodeString>> r_list(_list);

	int maxLoop = _list->size();
	for(int i = 0; i != maxLoop; ++i){
		UnicodeString* seg = _list->get(i);
		File* innerFile = dir->get(seg);

		if(innerFile->isDirectory()){
			deleteInnerDir(innerFile);
		}else{
			innerFile->deleteFile();
		}

		delete innerFile;
	}

	_list->deleteElements();

	return Os::deleteFile(dir->path) == 0;
}

bool File::exists() const noexcept
{
	return Os::file_exists(this->path);
}

bool File::isDirectory() const noexcept
{
	return Os::isDirectory(this->path);
}
bool File::isFile() const noexcept
{
	return Os::isFile(this->path);
}


File* File::getDirectory() const noexcept {
	File* ret = nullptr;

	UnicodeString* src = getAbsolutePath();
	StackRelease<UnicodeString> r_src(src);

	ArrayList<UnicodeString>* parts = src->split(&pathSeparator, false);
	StackRelease<ArrayList<UnicodeString>> r_parts(parts);

	UnicodeString tmppath(L"", 512);
	UnicodeString tmppathout(L"", 512);


	int const maxLoop = parts->size();
	for(int i = 0; i != maxLoop; ++i){
		UnicodeString* seg = parts->get(i);

		tmppath.append(&pathSeparator);
		tmppath.append(seg);

		if(!Os::isDirectory(&tmppath)){
			break;
		}

		tmppathout.append(&pathSeparator);
		tmppathout.append(seg);
	}

	parts->deleteElements();

	ret = new File(&tmppathout);
	return ret;
}

File* File::get(const wchar_t* seg) const noexcept {
	UnicodeString segstr(seg);
	return get(&segstr);
}

File* File::get(const UnicodeString* seg) const noexcept {
	File* ret = nullptr;

	UnicodeString nextPath(this->path);
	if(!nextPath.endsWith(&pathSeparator)){
		nextPath.append(&pathSeparator);
	}

	nextPath.append(seg);
	ret = new File(&nextPath);

	return ret;
}

ArrayList<UnicodeString>* File::list() const noexcept
{
	return Os::listFiles(this->path);
}

int File::length() const noexcept {
	return Os::fileLength(this);
}

bool File::move(const File* destFile) const noexcept {
	UnicodeString* src = getAbsolutePath(); __STP(src);
	UnicodeString* dst = destFile->getAbsolutePath(); __STP(dst);

	return Os::rename(src, dst);
}


} /* namespace alinous */
