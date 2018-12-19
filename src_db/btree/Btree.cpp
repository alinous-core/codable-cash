/*
 * Btree.cpp
 *
 *  Created on: 2018/12/18
 *      Author: iizuka
 */

#include "btree/Btree.h"
#include "btree/BtreeStorage.h"

#include "base/UnicodeString.h"
#include "base_io/File.h"

namespace alinous {

Btree::Btree(File* folder, UnicodeString* name) {
	this->folder = new File(*folder);
	this->name = new UnicodeString(name);
	this->store = nullptr;

}

Btree::~Btree() {
	if(this->store != nullptr){
		delete this->store, this->store = nullptr;
	}
	delete this->name, this->name = nullptr;
	delete this->folder, this->folder = nullptr;
}

} /* namespace alinous */
