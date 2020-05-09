/*
 * CodableDatabase.cpp
 *
 *  Created on: 2020/05/09
 *      Author: iizuka
 */

#include "engine/CodableDatabase.h"

#include "transaction/CdbTransactionManager.h"


namespace codablecash {

CodableDatabase::CodableDatabase() {
	this->trxManager = new CdbTransactionManager();
}

CodableDatabase::~CodableDatabase() {
	delete this->trxManager;

}

} /* namespace alinous */
