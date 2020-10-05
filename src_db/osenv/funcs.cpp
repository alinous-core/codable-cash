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
#include <time.h>


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

void Os::usleep(uint32_t microsec) noexcept {
	::usleep(microsec);
}

uint64_t Os::getMicroSec() noexcept {
	struct timespec startTime;
	clock_gettime(CLOCK_REALTIME, &startTime);

	uint64_t microsec = startTime.tv_sec * 1000000 + (startTime.tv_nsec / 1000);
	return microsec;
}

uint64_t Os::getTimestampLong() noexcept {
	time_t t = time(NULL);
	return (uint64_t)t;
}


int Os::threadKeyCreate(THREAD_KEY* key) {
	return ::pthread_key_create(key, nullptr);
}

int Os::threadKeyDelete(THREAD_KEY key) {
	return ::pthread_key_delete(key);
}

int Os::threadSetSpecific(THREAD_KEY key, const void* value) noexcept {
	return ::pthread_setspecific(key, value);
}

void* Os::threadGetSpecific(THREAD_KEY key) noexcept {
	return ::pthread_getspecific(key);
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

int64_t Os::fileLength(const File* const file) noexcept {
	struct stat  st;

	UnicodeString *path = file->getAbsolutePath();

	const char* src = path->toCString();
	int ret = stat(src, &st);

	delete path;
	delete [] src;

	if(ret != 0){
		return -1;
	}

	return st.st_size;
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

	int fd = ::open(cpath, mode, 0644);

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

FileDescriptor Os::openFile2ReadWrite(const File *file, bool sync) noexcept {
	CAUSE_ERROR_BY_RETURN(L"Os::openFile2ReadWrite", FileDescriptor(-1))

	UnicodeString* path = file->getAbsolutePath();
	StackRelease<UnicodeString> r_path(path);

	const char* cpath = path->toCString();

	int mode = O_CREAT | O_RDWR; // | O_BINARY;
	if(sync){
		mode |= O_SYNC;
	}

	int fd = ::open(cpath, mode, 0644);

	delete [] cpath;

	FileDescriptor desc;
	desc.fd = fd;

	return desc;
}

int Os::write2File(const FileDescriptor* fd, const char* buff, int length) noexcept {
	CAUSE_ERROR_BY_RETURN(L"Os::write2File", -1)

	int ret = 0;
	if(length > 0){
		ret = ::write(fd->fd, buff, length);
	}
	return ret;
}

int Os::readFile(const FileDescriptor* fd, char* buffer, int size) noexcept {
	CAUSE_ERROR_BY_RETURN(L"Os::readFile", -1)

	return ::read(fd->fd, buffer, size);
}

int Os::syncFile(const FileDescriptor* fd) noexcept {
	CAUSE_ERROR_BY_RETURN(L"Os::syncFile", -1)

	return ::syncfs(fd->fd);
}

void Os::closeFileDescriptor(FileDescriptor* fd) noexcept {
	//printf("FD: %d", fd->fd);::fflush(stdout);

	::close(fd->fd);
	fd->fd = 0;
}

int Os::seekFile(const FileDescriptor* fd, int64_t offset, SeekOrigin origin) noexcept {
	CAUSE_ERROR_BY_RETURN(L"Os::seekFile", -1)
	return ::lseek(fd->fd, offset, origin);
}


uint64_t Os::getSystemPageSize() noexcept {
	return ::sysconf(_SC_PAGE_SIZE);
}

bool Os::rename(const UnicodeString* src, const UnicodeString* dest) noexcept {
	const char* oldfile = src->toCString();
	const char* newfile = dest->toCString();

	int ret = ::rename(oldfile, newfile);

	delete [] oldfile;
	delete [] newfile;

	return ret == 0;
}

}
