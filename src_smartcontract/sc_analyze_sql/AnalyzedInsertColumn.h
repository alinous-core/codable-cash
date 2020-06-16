/*
 * AnalyzedColumn.h
 *
 *  Created on: 2020/06/15
 *      Author: iizuka
 */

#ifndef SC_ANALYZE_SQL_ANALYZEDINSERTCOLUMN_H_
#define SC_ANALYZE_SQL_ANALYZEDINSERTCOLUMN_H_

namespace codablecash {
class CdbTableColumn;
}
using namespace codablecash;

namespace alinous {

class AnalyzedInsertColumn {
public:
	explicit AnalyzedInsertColumn(const CdbTableColumn* column);
	virtual ~AnalyzedInsertColumn();

private:
	CdbTableColumn* column;
};

} /* namespace alinous */

#endif /* SC_ANALYZE_SQL_ANALYZEDINSERTCOLUMN_H_ */
