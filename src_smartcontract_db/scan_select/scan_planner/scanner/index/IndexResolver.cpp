/*
 * IndexResolver.cpp
 *
 *  Created on: 2020/11/26
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/index/IndexResolver.h"

namespace codablecash {

IndexResolver::IndexResolver(CodableDatabase* db) {
	this->db = db;
}

IndexResolver::~IndexResolver() {
	this->db = nullptr;
}

} /* namespace codablecash */
