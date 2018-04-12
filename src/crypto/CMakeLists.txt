

set(__cryptosrc
	crypto/Schnorr.cpp
	crypto/SchnorrKeyPair.cpp
	crypto/SchnorrSignature.cpp
)
	
set(cryptosrc ${__cryptosrc} PARENT_SCOPE)


set(gnodir ${CMAKE_BINARY_DIR}/src/CMakeFiles/codablelib.dir/crypto/)

add_custom_target(report_crypto
    COMMAND mkdir -p coverage/crypto
    COMMAND ${CMAKE_MAKE_PROGRAM} test
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

add_custom_command(TARGET report_crypto
    COMMAND echo "=================== GCOV crypto ===================="
	COMMAND gcov -b  ${__cryptosrc} -o ${gnodir}
	COMMAND lcov -c -d ${gnodir} -o test.info
	COMMAND genhtml -o output test.info
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/coverage/crypto
)
add_dependencies(report report_crypto)

