/*
 * funcs.cpp
 *
 *  Created on: 2018/04/18
 *      Author: iizuka
 */

#include "debug/debugMacros.h"

#include "funcs.h"

#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>



#include "base/UnicodeString.h"
#include "base/StackRelease.h"
#include "base_io/File.h"


namespace alinous {


/**************************************************************************
 * Thread functions
 */
THREAD_ID Os::getCurrentThreadId() noexcept {
	return ::pthread_self();
}

THREAD_ID Os::createThread(SysThreadRoutine threadFunc, void* params) noexcept {
	THREAD_ID id;
	::pthread_create( &id, nullptr, threadFunc, params);
	return id;
}

void Os::setThreadName(THREAD_ID id, const char* name) noexcept {
	::pthread_setname_np(id, name);
}
UnicodeString* Os::getThreadName(THREAD_ID id) noexcept {
	char thread_name[256]{};
	int ret = ::pthread_getname_np(id, thread_name, sizeof(thread_name));

	UnicodeString* name = nullptr;
	if(ret == 0){
		name = new UnicodeString(thread_name);
	}

	return name;
}

void Os::joinThread(THREAD_ID id) noexcept {
	::pthread_join(id, nullptr);
}

/**************************************************************************
 * File functions
 */
bool FileDescriptor::isOpened() const noexcept {
	return this->fd > 0;
}


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
		return array;
	}

	struct dirent* dent;
    do{
        dent = ::readdir(dp);
        if (dent != 0){
        	// std::cout << dent->d_name << std::endl;

        	if(Mem::strcmp(dent->d_name, ".") == 0 || Mem::strcmp(dent->d_name, "..") == 0){
        		continue;
        	}
        	UnicodeString *newPath = new UnicodeString(dent->d_name);
        	array->addElement(newPath);
        }
    }while(dent != 0);

    closedir(dp);

	return array;
}

FileDescriptor Os::openFile2Write(const File *file, bool append, bool sync) noexcept {
	UnicodeString* path = file->getAbsolutePath();
	StackRelease<UnicodeString> r_path(path);

	const char* cpath = path->toCString();

	int mode = O_CREAT | O_WRONLY;
	if(append){
		mode |= O_APPEND;
	}else{
		mode |= O_TRUNC;
	}
	if(sync){
		mode |= O_SYNC;
	}

	int fd = ::open(cpath, mode);

	delete [] cpath;

	FileDescriptor desc;
	desc.fd = fd;

	return desc;
}

FileDescriptor Os::openFile2Read(const File *file) noexcept {
	UnicodeString* path = file->getAbsolutePath();
		StackRelease<UnicodeString> r_path(path);

		const char* cpath = path->toCString();

		int mode = O_RDONLY;

		int fd = ::open(cpath, mode);

		delete [] cpath;

		FileDescriptor desc;
		desc.fd = fd;

		return desc;
}

int Os::write2File(const FileDescriptor* fd, const char* buff, int length) noexcept {
	return ::write(fd->fd, buff, length);
}

int Os::readFile(const FileDescriptor* fd, char* buffer, int size) noexcept {
	return ::read(fd->fd, buffer, size);
}

int Os::syncFile(const FileDescriptor* fd) noexcept {
	::syncfs(fd->fd);
}

void Os::closeFileDescriptor(FileDescriptor* fd) noexcept {
	::close(fd->fd);
	fd->fd = 0;
}

}


