/*
 * AbstractVariableInstraction.h
 *
 *  Created on: 2019/10/31
 *      Author: iizuka
 */

#ifndef VARIABLE_ACCESS_ABSTRACTVARIABLEINSTRACTION_H_
#define VARIABLE_ACCESS_ABSTRACTVARIABLEINSTRACTION_H_
#include <cstdint>

namespace alinous {

class AnalyzeContext;
class AnalyzedType;
class AbstractVmInstance;
class VirtualMachine;
class CodeElement;

class AbstractVariableInstraction {
public:
	static const constexpr uint8_t INSTRUCTION_ARRAY_REF{1};
	static const constexpr uint8_t INSTRUCTION_EXPRESSION{2};
	static const constexpr uint8_t INSTRUCTION_MEMBER_FUNCTION{3};
	static const constexpr uint8_t INSTRUCTION_MEMBER_VARIABLE{4};
	static const constexpr uint8_t INSTRUCTION_STACK_VARIABLE{5};
	static const constexpr uint8_t INSTRUCTION_THIS_POINTER{6};
	static const constexpr uint8_t INSTRUCTION_CLASS_TYPE{7};


	explicit AbstractVariableInstraction(uint8_t type);
	virtual ~AbstractVariableInstraction();

	virtual void analyze(AnalyzeContext* actx, AbstractVariableInstraction* lastIinst, CodeElement* element) = 0;
	virtual AnalyzedType getAnalyzedType() const noexcept = 0;
	virtual bool hasErrorOnAnalyze() const noexcept;

	virtual CodeElement* getCodeElement() const noexcept = 0;

	virtual AbstractVmInstance* interpret(VirtualMachine* vm, AbstractVmInstance* lastInst) = 0;

	uint8_t getType() const noexcept;
protected:
	uint8_t type;
	bool hasError;
};

} /* namespace alinous */

#endif /* VARIABLE_ACCESS_ABSTRACTVARIABLEINSTRACTION_H_ */
