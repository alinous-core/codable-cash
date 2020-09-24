/*
 * SwapCacheFactory.h
 *
 *  Created on: 2020/09/24
 *      Author: iizuka
 */

#ifndef TRANSACTION_CACHE_SWAPCACHEFACTORY_H_
#define TRANSACTION_CACHE_SWAPCACHEFACTORY_H_

namespace alinous {
class File;
}
using namespace alinous;

namespace codablecash {

class SwapCacheFactory {
public:
	explicit SwapCacheFactory(const File* tmpdir);
	virtual ~SwapCacheFactory();

	void resetDir();
private:
	File* baseDir;
};

} /* namespace codablecash */

#endif /* TRANSACTION_CACHE_SWAPCACHEFACTORY_H_ */
