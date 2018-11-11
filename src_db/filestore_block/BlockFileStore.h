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
}

namespace alinous {



class BlockFileStore : public FileStore {
public:
	BlockFileStore(const FileStore& base) = delete;
	BlockFileStore(UnicodeString* dir, UnicodeString* name, DiskCacheManager* cacheManager) noexcept;
	virtual ~BlockFileStore() noexcept;

	void createStore(bool del, uint64_t defaultSize) noexcept(false);
	bool isOpened() const noexcept;
	void close() noexcept;


private:
	void internalClear() noexcept;
private:
	BlockFileHeader* header;
	BlockFileBody* body;
};

} /* namespace alinous */

#endif /* FILESTORE_BLOCK_BLOCKFILESTORE_H_ */
