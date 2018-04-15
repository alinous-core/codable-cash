/*
 * Copyright (c) Tomohiro Iizuka. All rights reserved.
 * Licensed under the MIT license.
 */




#include "stdtypes.h"
#include "ubidi_props.h"


#ifndef _UBIDI_PROPS_DATA_H_
#define _UBIDI_PROPS_DATA_H_

namespace icu {


extern const int32_t ubidi_props_indexes[UBIDI_IX_TOP]; //={0x10,0x5994,0x5628,0x1a,0x620,0x8b4,0x10ac0,0x10af0,0,0,0,0,0,0,0,0x5502b6};

extern const uint16_t ubidi_props_trieIndex[11020];

extern const uint32_t ubidi_props_mirrors[26];

extern const uint8_t ubidi_props_jgArray[660];;

extern const uint8_t ubidi_props_jgArray2[48];


extern const UBiDiProps ubidi_props_singleton;

}

#endif // _UBIDI_PROPS_DATA_H_
