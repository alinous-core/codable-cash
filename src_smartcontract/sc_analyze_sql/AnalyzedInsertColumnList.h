/*
 * AnalyzedInsertColumnList.h
 *
 *  Created on: 2020/06/15
 *      Author: iizuka
 */

#ifndef SC_ANALYZE_SQL_ANALYZEDINSERTCOLUMNLIST_H_
#define SC_ANALYZE_SQL_ANALYZEDINSERTCOLUMNLIST_H_

#include "base/ArrayList.h"

namespace alinous {

class AnalyzedInsertColumn;
class UnicodeString;

class AnalyzedInsertColumnList {
public:
	AnalyzedInsertColumnList();
	virtual ~AnalyzedInsertColumnList();

private:
	ArrayList<AnalyzedInsertColumn> list;
};

} /* namespace alinous */

#endif /* SC_ANALYZE_SQL_ANALYZEDINSERTCOLUMNLIST_H_ */
