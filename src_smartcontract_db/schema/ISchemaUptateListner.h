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

class ISchemaUptateListner {
public:
	ISchemaUptateListner();
	virtual ~ISchemaUptateListner();

	virtual void schemaLoaded(SchemaManager* sc) = 0;
};

} /* namespace codablecash */

#endif /* SCHEMA_ISCHEMAUPTATELISTNER_H_ */
