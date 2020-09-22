/*
 * RecordValueConverter.h
 *
 *  Created on: 2020/09/21
 *      Author: iizuka
 */

#ifndef TABLE_STORE_RECORDVALUECONVERTER_H_
#define TABLE_STORE_RECORDVALUECONVERTER_H_

namespace codablecash {

class CdbTableColumn;
class AbstractCdbValue;
class CdbRecord;

class RecordValueConverter {
public:
	RecordValueConverter(CdbTableColumn* column, const AbstractCdbValue* defaultValue);
	virtual ~RecordValueConverter();

	CdbRecord* processUpdate(const CdbRecord* record);
private:
	CdbTableColumn* column;
	const AbstractCdbValue* defaultValue;
};

} /* namespace codablecash */

#endif /* TABLE_STORE_RECORDVALUECONVERTER_H_ */
