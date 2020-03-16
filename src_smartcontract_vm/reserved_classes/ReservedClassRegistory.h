/*
 * ReservedClassRegistory.h
 *
 *  Created on: 2020/03/16
 *      Author: iizuka
 */

#ifndef RESERVED_CLASSES_RESERVEDCLASSREGISTORY_H_
#define RESERVED_CLASSES_RESERVEDCLASSREGISTORY_H_

namespace alinous {

class ReservedClassRegistory {
private:
	ReservedClassRegistory();

public:
	static ReservedClassRegistory* getInstance();

	virtual ~ReservedClassRegistory();
};

} /* namespace alinous */

#endif /* RESERVED_CLASSES_RESERVEDCLASSREGISTORY_H_ */
