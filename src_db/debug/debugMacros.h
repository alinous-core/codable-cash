/*
 * debugMacros.h
 *
 *  Created on: 2018/04/25
 *      Author: iizuka
 */

#ifndef DEBUG_DEBUGMACROS_H_
#define DEBUG_DEBUGMACROS_H_


#include <assert.h>

#ifdef __TEST_CPP_UNIT__
#include "debug/ErrorPointManager.h"

#define ERROR_POINT(pointName) ErrorPointManager::getInstance()->reachPoint(pointName);
#define CAUSE_ERROR_BY_RETURN(occurrenceName, retvalue) do{\
			if(ErrorPointManager::getInstance()->checkError(occurrenceName)){\
				return retvalue;\
			}\
		}while(0);
#define CAUSE_ERROR_BY_THROW(occurrenceName, throwEx) do{\
			if(ErrorPointManager::getInstance()->checkError(occurrenceName)){\
				throw throwEx;\
			}\
		}while(0);

#else

#define ERROR_POINT(pointName)
#define OCCUR_ERROR(occurrenceName, retvalue)
#define CAUSE_ERROR_BY_THROW(occurrenceName, throwEx)

#endif /* __TEST_CPP_UNIT__ */

#endif /* DEBUG_DEBUGMACROS_H_ */
