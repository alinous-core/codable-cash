/*
 * VmMemoryManager.h
 *
 *  Created on: 2019/01/16
 *      Author: iizuka
 */

#ifndef MEMORY_VMMEMORYMANAGER_H_
#define MEMORY_VMMEMORYMANAGER_H_
#include <cstdint>
#include <cstddef>

namespace alinous {

class LongRangeList;

class VmMemoryManager {
public:
	explicit VmMemoryManager(uint64_t capacity);
	virtual ~VmMemoryManager();

	char* malloc(uint32_t cap);
	void free(char* ptr);
	uint32_t getSize(char* ptr) const noexcept;

private:
	uint64_t capacity;
	uint64_t capacityUsed;
	LongRangeList* used;
	LongRangeList* available;
	char* mem;
};

} /* namespace alinous */

#endif /* MEMORY_VMMEMORYMANAGER_H_ */
