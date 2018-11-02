/*
 * BlockFileBody.cpp
 *
 *  Created on: 2018/10/26
 *      Author: iizuka
 */

#include "filestore_block/BlockFileBody.h"

namespace alinous {

BlockFileBody::BlockFileBody(RandomAccessFile* file) noexcept : file(file){

}

BlockFileBody::~BlockFileBody() {
}

} /* namespace alinous */
