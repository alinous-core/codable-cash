/*
 * ReservedClassRegistory.cpp
 *
 *  Created on: 2020/03/16
 *      Author: iizuka
 */

#include "reserved_classes/ReservedClassRegistory.h"

namespace alinous {

ReservedClassRegistory::ReservedClassRegistory() {

}

ReservedClassRegistory* ReservedClassRegistory::getInstance() {
	static ReservedClassRegistory inst;

	return &inst;
}

ReservedClassRegistory::~ReservedClassRegistory() {

}

} /* namespace alinous */
