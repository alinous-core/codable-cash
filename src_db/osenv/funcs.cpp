/*
 * funcs.cpp
 *
 *  Created on: 2018/04/18
 *      Author: iizuka
 */


#include "funcs.h"

#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>

#include "base/UnicodeString.h"



namespace alinous {

/**************************************************************************
 * File functions
 */
char* Os::realpath(const char *path, char *resolved_path) noexcept {
	return ::realpath(path, resolved_path);
}
void Os::realpath_free(char* path) noexcept {
	::free(path);
}

bool Os::file_exists(UnicodeString* path) noexcept {
	struct stat  st;
	const char* src = path->toCString();

	int ret = stat(src, &st);

	delete [] src;

	return ret == 0;
}

int Os::mkdirs(UnicodeString *path,
			bool __S_IRUSR , bool __S_IWUSR, bool __S_IXUSR,
			bool __S_IRGRP , bool __S_IWGRP, bool __S_IXGRP,
			bool __S_IROTH , bool __S_IWOTH, bool __S_IXOTH) noexcept {
	const char* dirPath = path->toCString();
	unsigned int mode = 0;

	if(__S_IRUSR){
		mode |= S_IRUSR;
	}
	if(__S_IWUSR){
		mode |= S_IWUSR;
	}
	if(__S_IXUSR){
		mode |= S_IXUSR;
	}

	if(__S_IRGRP){
		mode |= S_IRGRP;
	}
	if(__S_IWGRP){
		mode |= S_IWGRP;
	}
	if(__S_IXGRP){
		mode |= S_IXGRP;
	}

	if(__S_IROTH){
		mode |= S_IROTH;
	}
	if(__S_IWOTH){
		mode |= S_IWOTH;
	}
	if(__S_IXOTH){
		mode |= S_IXOTH;
	}

	int ret = ::mkdir(dirPath, mode);

	delete [] dirPath;

	return ret;
}

int Os::deleteFile(const UnicodeString *path) noexcept {
	const char *from = path->toCString();
	int ret = ::remove(from);

	delete [] from;

	return ret;
}

bool Os::isDirectory(const UnicodeString* path) noexcept {
	struct stat  st;
	const char* src = path->toCString();

	int ret = stat(src, &st);
	delete [] src;

	if(ret != 0){
		return false;
	}
	return (st.st_mode & S_IFMT) == S_IFDIR;
}
bool Os::isFile(const UnicodeString* path) noexcept {
	struct stat  st;
	const char* src = path->toCString();

	int ret = ::stat(src, &st);
	delete [] src;

	if(ret != 0){
		return false;
	}
	return (st.st_mode & S_IFMT) != S_IFDIR;
}

ArrayList<UnicodeString>* Os::listFiles(const UnicodeString* path) noexcept {
	ArrayList<UnicodeString>* array = new ArrayList<UnicodeString>();
	const char *dirname = path->toCString();

	DIR* dp= ::opendir(dirname);
	delete [] dirname;

	if(dp == 0){
		return 0;
	}

	struct dirent* dent;
    do{
        dent = ::readdir(dp);
        if (dent!=0){
        	// std::cout << dent->d_name << std::endl;
        	UnicodeString *newPath = new UnicodeString(dent->d_name);
        	array->addElement(newPath);

        	//array->addElement(newPath);
        }
    }while(dent != 0);

    closedir(dp);

	return array;
}

}
