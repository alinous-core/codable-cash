/*
 * IndexResolver.h
 *
 *  Created on: 2020/11/26
 *      Author: iizuka
 */

#ifndef SCAN_SELECT_SCAN_PLANNER_SCANNER_INDEX_INDEXRESOLVER_H_
#define SCAN_SELECT_SCAN_PLANNER_SCANNER_INDEX_INDEXRESOLVER_H_

namespace codablecash {

class CodableDatabase;

class IndexResolver {
public:
	explicit IndexResolver(CodableDatabase* db);
	virtual ~IndexResolver();

private:
	CodableDatabase* db;
};

} /* namespace codablecash */

#endif /* SCAN_SELECT_SCAN_PLANNER_SCANNER_INDEX_INDEXRESOLVER_H_ */
