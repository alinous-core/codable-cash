

set(__src
	AbstractExtObject.cpp
	ExtClassObject.cpp
	ExtPrimitiveObject.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_vm ext_binary)

