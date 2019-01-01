

set(__src
	NetworkShard.cpp
	NetworkShardsStatus.cpp
)
handle_sub(codablecashlib "${__src}" blockchain bc_network)

