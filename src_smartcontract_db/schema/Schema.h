/*
 * Schema.h
 *
 *  Created on: 2020/05/11
 *      Author: iizuka
 */

#ifndef SCHEMA_SCHEMA_H_
#define SCHEMA_SCHEMA_H_
#include <cstdint>

#include "base/ArrayList.h"

namespace alinous {
class UnicodeString;
class File;

}  // namespace alinous
using namespace alinous;

namespace codablecash {

class SchemaBinary;
class ISchemaUptateListner;

class Schema {
public:
	static const UnicodeString PUBLIC;
	static const UnicodeString SCHEMA_FILE;

	Schema();
	virtual ~Schema();

	void addSchemaUpdateListner(ISchemaUptateListner* listner) noexcept;

	static void createSchema(const UnicodeString* name, File* baseDir);
	void loadSchema(const File* baseDir);

	void save();

	uint64_t newTransactionId();
	uint64_t newSchemaObjectId() noexcept;

private:
	void fireSchemaLoaded() noexcept;

private:
	SchemaBinary* binary;
	File* schemaBin;

	ArrayList<ISchemaUptateListner> listners;
};

} /* namespace alinous */

#endif /* SCHEMA_SCHEMA_H_ */
