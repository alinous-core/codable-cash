/*
 * CdbStorageManager.cpp
 *
 *  Created on: 2020/05/16
 *      Author: iizuka
 */

#include "table_store/CdbStorageManager.h"

#include "schema/Schema.h"


namespace codablecash {

CdbStorageManager::CdbStorageManager() {
	this->schema = nullptr;
}

CdbStorageManager::~CdbStorageManager() {
	this->schema = nullptr;
}

void CdbStorageManager::schemaLoaded(Schema* sc) {
	this->schema = sc;

}

} /* namespace codablecash */
