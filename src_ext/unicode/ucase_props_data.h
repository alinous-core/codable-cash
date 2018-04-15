/*
 * Copyright (c) Tomohiro Iizuka. All rights reserved.
 * Licensed under the MIT license.
 */


#include "stdtypes.h"
#include "ubidi_props.h"
#include "uchar_props_data.h"

#ifndef __UCASE_PROPS_DATA_H__
#define __UCASE_PROPS_DATA_H__

namespace icu {

/* indexes into indexes[] */
enum {
    UCASE_IX_INDEX_TOP,
    UCASE_IX_LENGTH,
    UCASE_IX_TRIE_SIZE,
    UCASE_IX_EXC_LENGTH,
    UCASE_IX_UNFOLD_LENGTH,

    UCASE_IX_MAX_FULL_LENGTH=15,
    UCASE_IX_TOP=16
};

extern const int32_t ucase_props_indexes[UCASE_IX_TOP];

extern const uint16_t ucase_props_trieIndex[10500];

extern const uint16_t ucase_props_exceptions[1322];

extern const uint16_t ucase_props_unfold[370];
struct UCaseProps {
    UDataMemory *mem;
    const int32_t *indexes;
    const uint16_t *exceptions;
    const uint16_t *unfold;

    UTrie2 trie;
    uint8_t formatVersion[4];
};

constexpr static const UCaseProps ucase_props_singleton={
  NULL,
  ucase_props_indexes,
  ucase_props_exceptions,
  ucase_props_unfold,
  {
    ucase_props_trieIndex,
    ucase_props_trieIndex+3104,
    NULL,
    3104,
    7396,
    0x188,
    0xc9c,
    0x0,
    0x0,
    0xe0800,
    0x2900,
    NULL, 0, FALSE, FALSE, 0, NULL
  },
  { 3,0,0,0 }
};

}

#endif
