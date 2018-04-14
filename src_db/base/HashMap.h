/*
 * HashMap.h
 *
 *  Created on: 2018/04/14
 *      Author: iizuka
 */

#ifndef BASE_HASHMAP_H_
#define BASE_HASHMAP_H_

#include "HashMapRawArray.h"
#include "HashMapKeySet.h"

namespace alinous {





template <typename T, typename V>
class HashMap {
public:
	HashMap() noexcept : hashMapKeySet(){

	}
	virtual ~HashMap() noexcept {

	}

protected:
	HashMapKeySet<T, V>* hashMapKeySet;
};


}


#endif /* BASE_HASHMAP_H_ */
