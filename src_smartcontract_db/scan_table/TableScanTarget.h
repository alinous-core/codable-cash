/*
 * TableScanTarget.h
 *
 *  Created on: 2020/08/07
 *      Author: iizuka
 */

#ifndef SCAN_TABLE_TABLESCANTARGET_H_
#define SCAN_TABLE_TABLESCANTARGET_H_

#include "scan_table/AbstractScanTableTarget.h"

namespace alinous {
class VirtualMachine;
}
using namespace alinous;

namespace codablecash {

class TableScanTarget : public AbstractScanTableTarget {
public:
	TableScanTarget();
	virtual ~TableScanTarget();

	void setSchema(const UnicodeString* schema) noexcept;
	void setTableName(const UnicodeString* tableName) noexcept;
	void setAlias(const UnicodeString* alias) noexcept;

	virtual const UnicodeString* toString() noexcept;

	virtual IJoinLeftSource* getLeftSource(VirtualMachine* vm);
	virtual IJoinLeftSource* getRightSource(VirtualMachine* vm);


private:
	UnicodeString* schema;
	UnicodeString* tableName;
	UnicodeString* alias;

	UnicodeString* str;
};

} /* namespace codablecash */

#endif /* SCAN_TABLE_TABLESCANTARGET_H_ */
