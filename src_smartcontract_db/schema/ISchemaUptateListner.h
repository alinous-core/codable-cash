/*
 * ISchemaUptateListner.h
 *
 *  Created on: 2020/05/14
 *      Author: iizuka
 */

#ifndef SCHEMA_ISCHEMAUPTATELISTNER_H_
#define SCHEMA_ISCHEMAUPTATELISTNER_H_

namespace codablecash {

class Schema;

class ISchemaUptateListner {
public:
	ISchemaUptateListner();
	virtual ~ISchemaUptateListner();

	virtual void schemaLoaded(Schema* sc) = 0;
};

} /* namespace codablecash */

#endif /* SCHEMA_ISCHEMAUPTATELISTNER_H_ */
