/*
 * BlockState.h
 *
 *  Created on: 2020/04/05
 *      Author: iizuka
 */

#ifndef VM_CTRL_BLOCKSTATE_H_
#define VM_CTRL_BLOCKSTATE_H_

namespace alinous {

class BlockState {
public:
	static const constexpr int BLOCK_NORMAL{0};
	static const constexpr int BLOCK_METHOD{1};
	static const constexpr int BLOCK_CTRL_LOOP{2};

	static const constexpr int BLOCK_FOR{3};
	static const constexpr int BLOCK_WHILE{4};
	static const constexpr int BLOCK_DO_WHILE{5};

	explicit BlockState(int type);
	virtual ~BlockState();

	int getType() const noexcept;

private:
	int type;
};

} /* namespace alinous */

#endif /* VM_CTRL_BLOCKSTATE_H_ */
