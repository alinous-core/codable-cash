

set(__src
	AbstractFlashBlock.cpp
	AbstractFlashBlockHeader.cpp
	FlashBlockchain.cpp
	MinerSignature.cpp
	PoWGeneratedBlock.cpp
	PoWGeneratedBlockHeader.cpp
	TicketGeneratedBlock.cpp
	TicketGeneratedBlockHeader.cpp
)
handle_sub(codablecashlib "${__src}" blockchain flash)

