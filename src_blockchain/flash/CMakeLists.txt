

set(__src
	AbstractFlashBlock.cpp
	FlashBlockchain.cpp
	PoWGeneratedBlock.cpp
	TicketGeneratedBlock.cpp
)
handle_sub(codablecashlib "${__src}" blockchain flash)

