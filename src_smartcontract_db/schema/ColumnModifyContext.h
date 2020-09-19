/*
 * ColumnModifyContext.h
 *
 *  Created on: 2020/09/19
 *      Author: iizuka
 */

#ifndef SCHEMA_COLUMNMODIFYCONTEXT_H_
#define SCHEMA_COLUMNMODIFYCONTEXT_H_

namespace codablecash {

class ColumnModifyContext {
public:
	typedef enum __UniqueChage{
		UNIQUE_NONE, TO_UNIQUE, TO_NOT_UNIQUE
	} UniqueChage;

	typedef enum __NotNullChage{
		NOTNULL_NONE, TO_NOT_NULL, RELEASE_NOT_NULL
	} NotNullChage;

	ColumnModifyContext();
	virtual ~ColumnModifyContext();


private:
	UniqueChage uniqueChange;
	bool typeChanged;
	NotNullChage notNullChange;
};

} /* namespace codablecash */

#endif /* SCHEMA_COLUMNMODIFYCONTEXT_H_ */
