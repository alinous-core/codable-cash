/*
 * BlockFileStore.h
 *
 *  Created on: 2018/10/06
 *      Author: iizuka
 */

#ifndef FILESTORE_BLOCK_BLOCKFILESTORE_H_
#define FILESTORE_BLOCK_BLOCKFILESTORE_H_

#include "filestore/FileStore.h"

namespace alinous {
	class BlockFileHeader;
	class BlockFileBody;
	class BlockHandle;
}

namespace alinous {



class BlockFileStore : public FileStore {
public:
	BlockFileStore(const FileStore& base) = delete;
	BlockFileStore(UnicodeString* dir, UnicodeString* name, DiskCacheManager* cacheManager) noexcept;
	virtual ~BlockFileStore() noexcept;


	void createStore(bool del, uint64_t defaultSize) noexcept(false);
	void createStore(bool del, uint64_t defaultSize, uint64_t blockSize) noexcept(false);

	void open(bool sync) noexcept(false);
	bool isOpened() const noexcept;
	void close() noexcept;

	BlockHandle* alloc(uint64_t size);
	BlockHandle* get(uint64_t fpos);
	void sync(bool fsync);

	BlockFileBody* getBody() const {
		return body;
	}
	BlockFileHeader* getHeader() const {
		return header;
	}

private:
	void internalClear() noexcept;
	void internalAllocBody(BlockHandle* handle, const uint64_t size);

private:
	BlockFileHeader* header;
	BlockFileBody* body;
};

} /* namespace alinous */

#endif /* FILESTORE_BLOCK_BLOCKFILESTORE_H_ */
