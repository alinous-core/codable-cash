/*
 * RawCompare.h
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */

#ifndef BASE_RAWCOMPARE_H_
#define BASE_RAWCOMPARE_H_


namespace alinous {
struct RawCompare {
public:
	int operator() (const void* const a, const void* const b) const noexcept{
		long long diff = (long long)a - (long long)b;
		if(diff == 0){
			return 0;
		}
		return diff > 0 ? 1 : -1;
	}
};

}


#endif /* BASE_RAWCOMPARE_H_ */
