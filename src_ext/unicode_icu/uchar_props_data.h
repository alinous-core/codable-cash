/*
 * Copyright (c) Tomohiro Iizuka. All rights reserved.
 * Licensed under the MIT license.
 */


#include "stdtypes.h"

#ifndef __UCHAR_PROPS_DATA_H__
#define __UCHAR_PROPS_DATA_H__

namespace icu {


#define UNEWTRIE2_MAX_DATA_LENGTH (0x110000+0x40+0x40+0x400)

/* indexes[] entries */
enum {
    UPROPS_PROPS32_INDEX,
    UPROPS_EXCEPTIONS_INDEX,
    UPROPS_EXCEPTIONS_TOP_INDEX,

    UPROPS_ADDITIONAL_TRIE_INDEX,
    UPROPS_ADDITIONAL_VECTORS_INDEX,
    UPROPS_ADDITIONAL_VECTORS_COLUMNS_INDEX,

    UPROPS_SCRIPT_EXTENSIONS_INDEX,

    UPROPS_RESERVED_INDEX_7,
    UPROPS_RESERVED_INDEX_8,

    /* size of the data file (number of 32-bit units after the header) */
    UPROPS_DATA_TOP_INDEX,

    /* maximum values for code values in vector word 0 */
    UPROPS_MAX_VALUES_INDEX=10,
    /* maximum values for code values in vector word 2 */
    UPROPS_MAX_VALUES_2_INDEX,

    UPROPS_INDEX_COUNT=16
};

enum {
    /** Shift size for getting the index-1 table offset. */
    UTRIE2_SHIFT_1=6+5,

    /** Shift size for getting the index-2 table offset. */
    UTRIE2_SHIFT_2=5,

    /**
     * Difference between the two shift sizes,
     * for getting an index-1 offset from an index-2 offset. 6=11-5
     */
    UTRIE2_SHIFT_1_2=UTRIE2_SHIFT_1-UTRIE2_SHIFT_2,

    /**
     * Number of index-1 entries for the BMP. 32=0x20
     * This part of the index-1 table is omitted from the serialized form.
     */
    UTRIE2_OMITTED_BMP_INDEX_1_LENGTH=0x10000>>UTRIE2_SHIFT_1,

    /** Number of code points per index-1 table entry. 2048=0x800 */
    UTRIE2_CP_PER_INDEX_1_ENTRY=1<<UTRIE2_SHIFT_1,

    /** Number of entries in an index-2 block. 64=0x40 */
    UTRIE2_INDEX_2_BLOCK_LENGTH=1<<UTRIE2_SHIFT_1_2,

    /** Mask for getting the lower bits for the in-index-2-block offset. */
    UTRIE2_INDEX_2_MASK=UTRIE2_INDEX_2_BLOCK_LENGTH-1,

    /** Number of entries in a data block. 32=0x20 */
    UTRIE2_DATA_BLOCK_LENGTH=1<<UTRIE2_SHIFT_2,

    /** Mask for getting the lower bits for the in-data-block offset. */
    UTRIE2_DATA_MASK=UTRIE2_DATA_BLOCK_LENGTH-1,

    /**
     * Shift size for shifting left the index array values.
     * Increases possible data size with 16-bit index values at the cost
     * of compactability.
     * This requires data blocks to be aligned by UTRIE2_DATA_GRANULARITY.
     */
    UTRIE2_INDEX_SHIFT=2,

    /** The alignment size of a data block. Also the granularity for compaction. */
    UTRIE2_DATA_GRANULARITY=1<<UTRIE2_INDEX_SHIFT,

    /* Fixed layout of the first part of the index array. ------------------- */

    /**
     * The BMP part of the index-2 table is fixed and linear and starts at offset 0.
     * Length=2048=0x800=0x10000>>UTRIE2_SHIFT_2.
     */
    UTRIE2_INDEX_2_OFFSET=0,

    /**
     * The part of the index-2 table for U+D800..U+DBFF stores values for
     * lead surrogate code _units_ not code _points_.
     * Values for lead surrogate code _points_ are indexed with this portion of the table.
     * Length=32=0x20=0x400>>UTRIE2_SHIFT_2. (There are 1024=0x400 lead surrogates.)
     */
    UTRIE2_LSCP_INDEX_2_OFFSET=0x10000>>UTRIE2_SHIFT_2,
    UTRIE2_LSCP_INDEX_2_LENGTH=0x400>>UTRIE2_SHIFT_2,

    /** Count the lengths of both BMP pieces. 2080=0x820 */
    UTRIE2_INDEX_2_BMP_LENGTH=UTRIE2_LSCP_INDEX_2_OFFSET+UTRIE2_LSCP_INDEX_2_LENGTH,

    /**
     * The 2-byte UTF-8 version of the index-2 table follows at offset 2080=0x820.
     * Length 32=0x20 for lead bytes C0..DF, regardless of UTRIE2_SHIFT_2.
     */
    UTRIE2_UTF8_2B_INDEX_2_OFFSET=UTRIE2_INDEX_2_BMP_LENGTH,
    UTRIE2_UTF8_2B_INDEX_2_LENGTH=0x800>>6,  /* U+0800 is the first code point after 2-byte UTF-8 */

    /**
     * The index-1 table, only used for supplementary code points, at offset 2112=0x840.
     * Variable length, for code points up to highStart, where the last single-value range starts.
     * Maximum length 512=0x200=0x100000>>UTRIE2_SHIFT_1.
     * (For 0x100000 supplementary code points U+10000..U+10ffff.)
     *
     * The part of the index-2 table for supplementary code points starts
     * after this index-1 table.
     *
     * Both the index-1 table and the following part of the index-2 table
     * are omitted completely if there is only BMP data.
     */
    UTRIE2_INDEX_1_OFFSET=UTRIE2_UTF8_2B_INDEX_2_OFFSET+UTRIE2_UTF8_2B_INDEX_2_LENGTH,
    UTRIE2_MAX_INDEX_1_LENGTH=0x100000>>UTRIE2_SHIFT_1,

    /*
     * Fixed layout of the first part of the data array. -----------------------
     * Starts with 4 blocks (128=0x80 entries) for ASCII.
     */

    /**
     * The illegal-UTF-8 data block follows the ASCII block, at offset 128=0x80.
     * Used with linear access for single bytes 0..0xbf for simple error handling.
     * Length 64=0x40, not UTRIE2_DATA_BLOCK_LENGTH.
     */
    UTRIE2_BAD_UTF8_DATA_OFFSET=0x80,

    /** The start of non-linear-ASCII data blocks, at offset 192=0xc0. */
    UTRIE2_DATA_START_OFFSET=0xc0
};

enum {
    /**
     * At build time, leave a gap in the index-2 table,
     * at least as long as the maximum lengths of the 2-byte UTF-8 index-2 table
     * and the supplementary index-1 table.
     * Round up to UTRIE2_INDEX_2_BLOCK_LENGTH for proper compacting.
     */
    UNEWTRIE2_INDEX_GAP_OFFSET=UTRIE2_INDEX_2_BMP_LENGTH,
    UNEWTRIE2_INDEX_GAP_LENGTH=
        ((UTRIE2_UTF8_2B_INDEX_2_LENGTH+UTRIE2_MAX_INDEX_1_LENGTH)+UTRIE2_INDEX_2_MASK)&
        ~UTRIE2_INDEX_2_MASK,

    /**
     * Maximum length of the build-time index-2 array.
     * Maximum number of Unicode code points (0x110000) shifted right by UTRIE2_SHIFT_2,
     * plus the part of the index-2 table for lead surrogate code points,
     * plus the build-time index gap,
     * plus the null index-2 block.
     */
    UNEWTRIE2_MAX_INDEX_2_LENGTH=
        (0x110000>>UTRIE2_SHIFT_2)+
        UTRIE2_LSCP_INDEX_2_LENGTH+
        UNEWTRIE2_INDEX_GAP_LENGTH+
        UTRIE2_INDEX_2_BLOCK_LENGTH,

    UNEWTRIE2_INDEX_1_LENGTH=0x110000>>UTRIE2_SHIFT_1
};

/* constants for the storage form of numeric types and values */
enum {
    /** No numeric value. */
    UPROPS_NTV_NONE=0,
    /** Decimal digits: nv=0..9 */
    UPROPS_NTV_DECIMAL_START=1,
    /** Other digits: nv=0..9 */
    UPROPS_NTV_DIGIT_START=11,
    /** Small integers: nv=0..154 */
    UPROPS_NTV_NUMERIC_START=21,
    /** Fractions: ((ntv>>4)-12) / ((ntv&0xf)+1) = -1..17 / 1..16 */
    UPROPS_NTV_FRACTION_START=0xb0,
    /**
     * Large integers:
     * ((ntv>>5)-14) * 10^((ntv&0x1f)+2) = (1..9)*(10^2..10^33)
     * (only one significant decimal digit)
     */
    UPROPS_NTV_LARGE_START=0x1e0,
    /**
     * Sexagesimal numbers:
     * ((ntv>>2)-0xbf) * 60^((ntv&3)+1) = (1..9)*(60^1..60^4)
     */
    UPROPS_NTV_BASE60_START=0x300,
    /** No numeric value (yet). */
    UPROPS_NTV_RESERVED_START=UPROPS_NTV_BASE60_START+36,  /* 0x300+9*4=0x324 */

    UPROPS_NTV_MAX_SMALL_INT=UPROPS_NTV_FRACTION_START-UPROPS_NTV_NUMERIC_START-1
};


struct UNewTrie2 {
    int32_t index1[UNEWTRIE2_INDEX_1_LENGTH];
    int32_t index2[UNEWTRIE2_MAX_INDEX_2_LENGTH];
    uint32_t *data;

    uint32_t initialValue, errorValue;
    int32_t index2Length, dataCapacity, dataLength;
    int32_t firstFreeBlock;
    int32_t index2NullOffset, dataNullOffset;
    uint32_t highStart;
    UBool isCompacted;

    /**
     * Multi-purpose per-data-block table.
     *
     * Before compacting:
     *
     * Per-data-block reference counters/free-block list.
     *  0: unused
     * >0: reference counter (number of index-2 entries pointing here)
     * <0: next free data block in free-block list
     *
     * While compacting:
     *
     * Map of adjusted indexes, used in compactData() and compactIndex2().
     * Maps from original indexes to new ones.
     */
    int32_t map[UNEWTRIE2_MAX_DATA_LENGTH>>UTRIE2_SHIFT_2];
};

struct UTrie2 {
    /* protected: used by macros and functions for reading values */
    const uint16_t *index;
    const uint16_t *data16;     /* for fast UTF-8 ASCII access, if 16b data */
    const uint32_t *data32;     /* NULL if 16b data is used via index */

    int32_t indexLength, dataLength;
    uint16_t index2NullOffset;  /* 0xffff if there is no dedicated index-2 null block */
    uint16_t dataNullOffset;
    uint32_t initialValue;
    /** Value returned for out-of-range code points and illegal UTF-8. */
    uint32_t errorValue;

    /* Start of the last range which ends at U+10ffff, and its value. */
    uint32_t highStart;
    int32_t highValueIndex;

    /* private: used by builder and unserialization functions */
    void *memory;           /* serialized bytes; NULL if not frozen yet */
    int32_t length;         /* number of serialized bytes at memory; 0 if not frozen yet */
    UBool isMemoryOwned;    /* TRUE if the trie owns the memory */
    UBool padding1;
    int16_t padding2;
    UNewTrie2 *newTrie;     /* builder object; NULL when frozen */
};
typedef struct UTrie2 UTrie2;



extern const uint16_t propsTrie_index[19268];

static const UTrie2 propsTrie={
    propsTrie_index,
    propsTrie_index+4108,
    NULL,
    4108,
    15160,
    0xa40,
    0x108c,
    0x0,
    0x0,
    0x110000,
    0x4b40,
    NULL, 0, FALSE, FALSE, 0, NULL
};

extern const uint16_t propsVectorsTrie_index[26188];

static const UTrie2 propsVectorsTrie={
    propsVectorsTrie_index,
    propsVectorsTrie_index+4364,
    NULL,
    4364,
    21824,
    0xa40,
    0x118c,
    0x0,
    0x0,
    0x110000,
    0x6648,
    NULL, 0, FALSE, FALSE, 0, NULL
};

extern const uint32_t propsVectors[5520];

constexpr static const int32_t countPropsVectors=5520;
constexpr static const int32_t propsVectorsColumns=3;
extern const uint16_t scriptExtensions[114];

extern const int32_t indexes[UPROPS_INDEX_COUNT];

}

#endif // __UCHAR_PROPS_DATA_H__

