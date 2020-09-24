/*
 * ISchemaUptateListner.h
 *
 *  Created on: 2020/05/14
 *      Author: iizuka
 */

#ifndef SCHEMA_ISCHEMAUPTATELISTNER_H_
#define SCHEMA_ISCHEMAUPTATELISTNER_H_

namespace codablecash {

class SchemaManager;
class CdbTable;
class ColumnModifyContext;

class ISchemaUptateListner {
public:
	ISchemaUptateListner();
	virtual ~ISchemaUptateListner();

	virtual void schemaLoaded(SchemaManager* sc) = 0;
	virtual void onCreateTable(SchemaManager* mgr, const CdbTable* table) = 0;
	virtual void onAlterModify(SchemaManager* mgr, const CdbTable* table, const ColumnModifyContext* ctx) = 0;
};

} /* namespace codablecash */

#endif /* SCHEMA_ISCHEMAUPTATELISTNER_H_ */
