/*
 * AbstractScanConditionElement.h
 *
 *  Created on: 2020/07/21
 *      Author: iizuka
 */

#ifndef SCAN_CONDITION_ABSTRACTSCANCONDITIONELEMENT_H_
#define SCAN_CONDITION_ABSTRACTSCANCONDITIONELEMENT_H_

namespace alinous {
class UnicodeString;
}
using namespace alinous;

namespace codablecash {

class AbstractScanConditionElement {
public:
	AbstractScanConditionElement();
	virtual ~AbstractScanConditionElement();

	virtual const UnicodeString* toStringCode() noexcept = 0;
};

} /* namespace codablecash */

#endif /* SCAN_CONDITION_ABSTRACTSCANCONDITIONELEMENT_H_ */
