/*
 * CdbStorageManager.h
 *
 *  Created on: 2020/05/16
 *      Author: iizuka
 */

#ifndef TABLE_STORE_CDBSTORAGEMANAGER_H_
#define TABLE_STORE_CDBSTORAGEMANAGER_H_

#include "schema/ISchemaUptateListner.h"

namespace codablecash {

class SchemaManager;

class CdbStorageManager : public ISchemaUptateListner {
public:
	CdbStorageManager();
	virtual ~CdbStorageManager();

	virtual void schemaLoaded(SchemaManager* sc);

private:
	SchemaManager* schema;
};

} /* namespace codablecash */

#endif /* TABLE_STORE_CDBSTORAGEMANAGER_H_ */
