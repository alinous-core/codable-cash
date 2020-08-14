/*
 * CdbOidValueListCursor.h
 *
 *  Created on: 2020/08/14
 *      Author: iizuka
 */

#ifndef TABLE_RECORD_VALUE_CDBOIDVALUELISTCURSOR_H_
#define TABLE_RECORD_VALUE_CDBOIDVALUELISTCURSOR_H_

namespace codablecash {

class CdbOidValueList;
class CdbOid;

class CdbOidValueListCursor {
public:
	CdbOidValueListCursor(const CdbOidValueList* list);
	virtual ~CdbOidValueListCursor();

	bool hasNext() noexcept;
	const CdbOid* next() noexcept;

private:
	const CdbOidValueList* list;
	int pos;
	int maxCount;

	CdbOid* obj;
};

} /* namespace codablecash */

#endif /* TABLE_RECORD_VALUE_CDBOIDVALUELISTCURSOR_H_ */
