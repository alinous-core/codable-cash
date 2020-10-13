/*
 * IValueProvider.cpp
 *
 *  Created on: 2020/07/21
 *      Author: iizuka
 */

#include "scan_select/scan_condition/IValueProvider.h"

namespace codablecash {

IValueProvider::IValueProvider() {

}

IValueProvider::~IValueProvider() {

}

bool IValueProvider::isColumn() const noexcept {
	return false;
}


} /* namespace codablecash */
