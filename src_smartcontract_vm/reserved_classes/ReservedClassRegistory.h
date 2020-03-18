/*
 * ReservedClassRegistory.h
 *
 *  Created on: 2020/03/16
 *      Author: iizuka
 */

#ifndef RESERVED_CLASSES_RESERVEDCLASSREGISTORY_H_
#define RESERVED_CLASSES_RESERVEDCLASSREGISTORY_H_

#include "base/ArrayList.h"


namespace alinous {
class AnalyzedClass;

class ReservedClassRegistory {
private:
	ReservedClassRegistory();

public:
	static ReservedClassRegistory* getInstance();

	virtual ~ReservedClassRegistory();

	const ArrayList<AnalyzedClass>* getReservedClassesList() const noexcept;

private:
	ArrayList<AnalyzedClass> list;
};

} /* namespace alinous */

#endif /* RESERVED_CLASSES_RESERVEDCLASSREGISTORY_H_ */