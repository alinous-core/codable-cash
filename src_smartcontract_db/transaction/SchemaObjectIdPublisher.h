/*
 * SchemaObjectIdPublisher.h
 *
 *  Created on: 2020/05/14
 *      Author: iizuka
 */

#ifndef TRANSACTION_SCHEMAOBJECTIDPUBLISHER_H_
#define TRANSACTION_SCHEMAOBJECTIDPUBLISHER_H_
#include <cstdint>

namespace codablecash {
class Schema;

class SchemaObjectIdPublisher {
public:
	explicit SchemaObjectIdPublisher(Schema* schema);
	virtual ~SchemaObjectIdPublisher();

	uint64_t newOid();
private:
	Schema* schema;
};

} /* namespace codablecash */

#endif /* TRANSACTION_SCHEMAOBJECTIDPUBLISHER_H_ */
