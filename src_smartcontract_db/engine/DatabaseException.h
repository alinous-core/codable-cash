/*
 * DatabaseException.h
 *
 *  Created on: 2020/05/12
 *      Author: iizuka
 */

#ifndef ENGINE_DATABASEEXCEPTION_H_
#define ENGINE_DATABASEEXCEPTION_H_

namespace codablecash {

class DatabaseException {
public:
	DatabaseException();
	virtual ~DatabaseException();
};

} /* namespace codablecash */

#endif /* ENGINE_DATABASEEXCEPTION_H_ */
