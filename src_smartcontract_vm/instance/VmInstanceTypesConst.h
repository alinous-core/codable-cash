/*
 * VmInstanceTypesConst.h
 *
 *  Created on: 2020/01/08
 *      Author: iizuka
 */

#ifndef INSTANCE_VMINSTANCETYPESCONST_H_
#define INSTANCE_VMINSTANCETYPESCONST_H_
#include <cstdint>

namespace alinous {

class VmInstanceTypesConst {
public:
	static constexpr uint8_t INST_NULL {0};
	static constexpr uint8_t STACK {1};
	static constexpr uint8_t INST_OBJ {2};
	static constexpr uint8_t INST_STRING{3};
	static constexpr uint8_t INST_ARRAY{4};
	static constexpr uint8_t INST_DOM{5};
	static constexpr uint8_t INST_DOM_ARRAY{6};

	static constexpr uint8_t INST_EXCEPTION{10};
	static constexpr uint8_t INST_BIG_INT{11};

	static constexpr uint8_t REF_ROOT{100};
	static constexpr uint8_t REF_OBJ{101};
	static constexpr uint8_t REF_BYTE{102};
	static constexpr uint8_t REF_CHAR{103};
	static constexpr uint8_t REF_SHORT{104};
	static constexpr uint8_t REF_INT{105};
	static constexpr uint8_t REF_BOOL{106};
	static constexpr uint8_t REF_LONG{107};

	static constexpr uint8_t REF_ARRAY{150};
	static constexpr uint8_t REF_DOM{151};
	static constexpr uint8_t REF_DOM_RUNTIME{152};

	static constexpr uint8_t REF_CLASS_TYPE{200};
};

} /* namespace alinous */

#endif /* INSTANCE_VMINSTANCETYPESCONST_H_ */
