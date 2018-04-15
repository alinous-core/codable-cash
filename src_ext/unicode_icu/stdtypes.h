/*
 * Copyright (c) Tomohiro Iizuka. All rights reserved.
 * Licensed under the MIT license.
 */


#ifndef UNICODE_ICU_STDTYPES_H_
#define UNICODE_ICU_STDTYPES_H_

#include <stdint.h>

#ifndef NULL
#define NULL __null
#endif

namespace icu {

typedef int8_t UBool;
constexpr static const UBool FALSE{0};

}

#endif /* UNICODE_ICU_STDTYPES_H_ */
