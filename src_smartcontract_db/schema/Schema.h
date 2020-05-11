/*
 * Schema.h
 *
 *  Created on: 2020/05/11
 *      Author: iizuka
 */

#ifndef SCHEMA_SCHEMA_H_
#define SCHEMA_SCHEMA_H_

namespace alinous {
class UnicodeString;
class File;
}  // namespace alinous
using namespace alinous;

namespace codablecash {

class Schema {
public:
	static const UnicodeString PUBLIC;

	Schema();
	virtual ~Schema();

	static void createSchema(const UnicodeString* name, File* baseDir);
};

} /* namespace alinous */

#endif /* SCHEMA_SCHEMA_H_ */
