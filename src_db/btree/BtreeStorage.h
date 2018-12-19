/*
 * BtreeStorage.h
 *
 *  Created on: 2018/12/18
 *      Author: iizuka
 */

#ifndef BTREE_BTREESTORAGE_H_
#define BTREE_BTREESTORAGE_H_

namespace alinous {

class UnicodeString;
class File;

class BtreeStorage {
public:
	BtreeStorage();
	virtual ~BtreeStorage();

private:
	UnicodeString* name;
	File* folder;
};

} /* namespace alinous */

#endif /* BTREE_BTREESTORAGE_H_ */
