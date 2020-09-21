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

class RecordValueConverter {
public:
	explicit RecordValueConverter(CdbTableColumn* column);
	virtual ~RecordValueConverter();

private:
	CdbTableColumn* column;
};

} /* namespace codablecash */

#endif /* TABLE_STORE_RECORDVALUECONVERTER_H_ */
