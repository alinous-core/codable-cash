/*
 * VmInstanceKey.h
 *
 *  Created on: 2019/07/06
 *      Author: iizuka
 */

#ifndef INSTANCE_GC_VMINSTANCEKEY_H_
#define INSTANCE_GC_VMINSTANCEKEY_H_

namespace alinous {

class AbstractVmInstance;
class IAbstractVmInstanceSubstance;

class VmInstanceKey {
public:
	VmInstanceKey(const VmInstanceKey& inst);
	explicit VmInstanceKey(const IAbstractVmInstanceSubstance* instance);
	virtual ~VmInstanceKey();

	int hashCode() const noexcept;

	class ValueCompare {
	public:
		int operator() (const VmInstanceKey* const _this, const  VmInstanceKey* const object) const noexcept;
	};

private:
	const IAbstractVmInstanceSubstance* instance;
};

} /* namespace alinous */

#endif /* INSTANCE_GC_VMINSTANCEKEY_H_ */
