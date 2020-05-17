/*
 * CdbStorageManager.cpp
 *
 *  Created on: 2020/05/16
 *      Author: iizuka
 */

#include "table_store/CdbStorageManager.h"

#include "schema/SchemaManager.h"


namespace codablecash {

CdbStorageManager::CdbStorageManager() {
	this->schema = nullptr;
}

CdbStorageManager::~CdbStorageManager() {
	this->schema = nullptr;
}

void CdbStorageManager::schemaLoaded(SchemaManager* sc) {
	this->schema = sc;
}

void codablecash::CdbStorageManager::onCreateTable(SchemaManager* mgr, CdbTable* table) {


	// FIXME create storage
}


} /* namespace codablecash */
