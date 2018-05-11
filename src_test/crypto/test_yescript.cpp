/*
 * test_yescript.cpp
 *
 *  Created on: 2018/04/11
 *      Author: iizuka
 */

#include <iostream>
#include <gmp.h>

#include "yescrypt/yescrypt.h"
#include "test_utils/t_macros.h"

using namespace alinous;

#define YESCRYPT_N 2048
#define YESCRYPT_R 8
#define YESCRYPT_P 1
#define YESCRYPT_T 0
#define YESCRYPT_FLAGS (YESCRYPT_RW | YESCRYPT_PWXFORM)

TEST_GROUP(Yescript) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}
};

int yescrypt_test(const uint8_t *passwd, size_t passwdlen,
                            const uint8_t *salt, size_t saltlen,
                            uint8_t *buf, size_t buflen)
{
    static __thread int initialized = 0;
    static __thread yescrypt_shared_t shared;
    static __thread yescrypt_local_t local;
    int retval;
    if (!initialized) {
        /* "shared" could in fact be shared, but it's simpler to keep it private
         * along with "local".  It's dummy and tiny anyway. */
        if (yescrypt_init_shared(&shared, NULL, 0,
                                 0, 0, 0, YESCRYPT_SHARED_DEFAULTS, 0, NULL, 0))
            return -1;
        if (yescrypt_init_local(&local)) {
            yescrypt_free_shared((yescrypt_shared_t*)&shared);
            return -1;
        }
        initialized = 1;
    }
    retval = yescrypt_kdf(&shared, &local, passwd, passwdlen, salt, saltlen,
                          YESCRYPT_N, YESCRYPT_R, YESCRYPT_P, YESCRYPT_T,
							(yescrypt_flags_t)YESCRYPT_FLAGS, buf, buflen);
#if 0
    if (yescrypt_free_local(&local)) {
        yescrypt_free_shared(&shared);
        return -1;
    }
    if (yescrypt_free_shared(&shared))
        return -1;
    initialized = 0;
#endif
    if (retval < 0) {
        yescrypt_free_local(&local);
        yescrypt_free_shared(&shared);
    }
    return retval;
}

TEST(Yescript, test01){
	const char* passwd = "password";
	uint8_t buf[256];

	yescrypt_test((const uint8_t *)passwd, 8,
			(const uint8_t *)passwd, 8,
                            buf, 256);
}

TEST(Yescript, test02){
	const char* passwd = "passwordpasswordpasswordpasswordpasswordpasswordpasswordpassword";
	uint8_t buf[256];

	yescrypt_test((const uint8_t *)passwd, 8*8,
			(const uint8_t *)passwd, 8,
                            buf, 256);
}




