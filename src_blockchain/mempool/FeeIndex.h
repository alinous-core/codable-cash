/*
 * FeeIndex.h
 *
 *  Created on: 2019/01/05
 *      Author: iizuka
 */

#ifndef MEMPOOL_FEEINDEX_H_
#define MEMPOOL_FEEINDEX_H_

namespace alinous {
class File;
class DiskCacheManager;
class Btree;
}

namespace codablecash {
using namespace alinous;

class FeeIndex {
public:
	static const constexpr wchar_t* FILE_NAME{L"idx_fee"};

	FeeIndex(const File* baseDir, DiskCacheManager* cacheManager);
	virtual ~FeeIndex();

	bool exists() const noexcept;
	void create() noexcept(false);

	void open() noexcept(false);
	void close() noexcept;

private:
	File* baseDir;
	DiskCacheManager* cacheManager;
	Btree* btree;
};

} /* namespace codablecash */

#endif /* MEMPOOL_FEEINDEX_H_ */
