

set(__src
	AbstractExtObject.cpp
	ExtArrayObject.cpp
	ExtClassObject.cpp
	ExtDomArrayObject.cpp
	ExtDomObject.cpp
	ExtExceptionObject.cpp
	ExtNullPtrObject.cpp
	ExtPrimitiveObject.cpp
	ExtStringClass.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_vm ext_binary)

