/*
 * NameSegments.h
 *
 *  Created on: 2020/05/02
 *      Author: iizuka
 */

#ifndef SC_ANALYZE_NAMESEGMENTS_H_
#define SC_ANALYZE_NAMESEGMENTS_H_

#include "base/ArrayList.h"

namespace alinous {

class UnicodeString;

class NameSegments {
public:
	NameSegments();
	virtual ~NameSegments();

	void addSegment(const UnicodeString* seg) noexcept;
	const UnicodeString* toString() noexcept;

	int length() const noexcept;
	void removeTop() noexcept;
private:
	ArrayList<UnicodeString>* list;

	UnicodeString* str;
};

} /* namespace alinous */

#endif /* SC_ANALYZE_NAMESEGMENTS_H_ */
