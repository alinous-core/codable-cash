/*
 * BlockFileBody.cpp
 *
 *  Created on: 2018/10/26
 *      Author: iizuka
 */

#include "filestore_block/BlockFileBody.h"

#include "debug/debugMacros.h"

namespace alinous {

BlockFileBody::BlockFileBody(RandomAccessFile* file) noexcept : file(file){

}

BlockFileBody::~BlockFileBody() {
}

void BlockFileBody::createStore(bool del) {

}

} /* namespace alinous */
