/*
 * VTableMethodEntry.h
 *
 *  Created on: 2019/11/30
 *      Author: iizuka
 */

#ifndef SC_ANALYZE_FUNCTIONS_VTABLEMETHODENTRY_H_
#define SC_ANALYZE_FUNCTIONS_VTABLEMETHODENTRY_H_

namespace alinous {

class MethodDeclare;
class UnicodeString;

class VTableMethodEntry {
public:
	static constexpr int METHOD_NORMAL{1};
	static constexpr int METHOD_VIRTUAL{2};
	static constexpr int METHOD_VIRTUAL_SUPER{3};

	VTableMethodEntry(MethodDeclare* method, int type);
	virtual ~VTableMethodEntry();

	const UnicodeString* getName() const noexcept;
	MethodDeclare* getMethod() const noexcept;

	bool isVirtual() const noexcept;
	bool isStatic() const noexcept;
private:
	MethodDeclare* method;
	int type;
};

} /* namespace alinous */

#endif /* SC_ANALYZE_FUNCTIONS_VTABLEMETHODENTRY_H_ */
