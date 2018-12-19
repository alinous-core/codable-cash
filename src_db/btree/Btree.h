/*
 * Btree.h
 *
 *  Created on: 2018/12/18
 *      Author: iizuka
 */

#ifndef BTREE_BTREE_H_
#define BTREE_BTREE_H_

namespace alinous {

class File;
class UnicodeString;

class BtreeStorage;

class Btree {
public:
	Btree(File* folder, UnicodeString* name);
	virtual ~Btree();


private:
	BtreeStorage* store;
};

} /* namespace alinous */

#endif /* BTREE_BTREE_H_ */
