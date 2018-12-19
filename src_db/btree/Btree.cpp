/*
 * Btree.cpp
 *
 *  Created on: 2018/12/18
 *      Author: iizuka
 */

#include "btree/Btree.h"
#include "btree/BtreeStorage.h"

namespace alinous {

Btree::Btree(File* folder, UnicodeString* name) {

	this->store = nullptr;

}

Btree::~Btree() {
	if(this->store != nullptr){
		delete this->store, this->store = nullptr;
	}
}

} /* namespace alinous */
