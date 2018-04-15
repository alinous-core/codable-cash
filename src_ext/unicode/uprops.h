/*
 * Copyright (c) Tomohiro Iizuka. All rights reserved.
 * Licensed under the MIT license.
 */


#include "utrie2.h"

#ifndef UNICODE_UPROPS_H_
#define UNICODE_UPROPS_H_

namespace icu {

/* definitions for the main properties words */
enum {
    /* general category shift==0                                0 (5 bits) */
    /* reserved                                                 5 (1 bit) */
    UPROPS_NUMERIC_TYPE_VALUE_SHIFT=6                       /*  6 (10 bits) */
};


#define GET_NUMERIC_TYPE_VALUE(props) ((props)>>UPROPS_NUMERIC_TYPE_VALUE_SHIFT)


#define UPROPS_NTV_GET_TYPE(ntv) \
    ((ntv==UPROPS_NTV_NONE) ? U_NT_NONE : \
    (ntv<UPROPS_NTV_DIGIT_START) ?  U_NT_DECIMAL : \
    (ntv<UPROPS_NTV_NUMERIC_START) ? U_NT_DIGIT : \
    U_NT_NUMERIC)

/* number of properties vector words */
#define UPROPS_VECTOR_WORDS     3

/*
 * Properties in vector word 0
 * Bits
 * 31..24   DerivedAge version major/minor one nibble each
 * 23..22   3..1: Bits 7..0 = Script_Extensions index
 *             3: Script value from Script_Extensions
 *             2: Script=Inherited
 *             1: Script=Common
 *             0: Script=bits 7..0
 * 21..20   reserved
 * 19..17   East Asian Width
 * 16.. 8   UBlockCode
 *  7.. 0   UScriptCode, or index to Script_Extensions
 */

/* derived age: one nibble each for major and minor version numbers */
#define UPROPS_AGE_MASK         0xff000000
#define UPROPS_AGE_SHIFT        24

/* Script_Extensions: mask includes Script */
#define UPROPS_SCRIPT_X_MASK    0x00c000ff
#define UPROPS_SCRIPT_X_SHIFT   22

#define UPROPS_EA_MASK          0x000e0000
#define UPROPS_EA_SHIFT         17

#define UPROPS_BLOCK_MASK       0x0001ff00
#define UPROPS_BLOCK_SHIFT      8

#define UPROPS_SCRIPT_MASK      0x000000ff

/* UPROPS_SCRIPT_X_WITH_COMMON must be the lowest value that involves Script_Extensions. */
#define UPROPS_SCRIPT_X_WITH_COMMON     0x400000
#define UPROPS_SCRIPT_X_WITH_INHERITED  0x800000
#define UPROPS_SCRIPT_X_WITH_OTHER      0xc00000

/*
 * Properties in vector word 1
 * Each bit encodes one binary property.
 * The following constants represent the bit number, use 1<<UPROPS_XYZ.
 * UPROPS_BINARY_1_TOP<=32!
 *
 * Keep this list of property enums in sync with
 * propListNames[] in icu/source/tools/genprops/props2.c!
 *
 * ICU 2.6/uprops format version 3.2 stores full properties instead of "Other_".
 */
enum {
    UPROPS_WHITE_SPACE,
    UPROPS_DASH,
    UPROPS_HYPHEN,
    UPROPS_QUOTATION_MARK,
    UPROPS_TERMINAL_PUNCTUATION,
    UPROPS_MATH,
    UPROPS_HEX_DIGIT,
    UPROPS_ASCII_HEX_DIGIT,
    UPROPS_ALPHABETIC,
    UPROPS_IDEOGRAPHIC,
    UPROPS_DIACRITIC,
    UPROPS_EXTENDER,
    UPROPS_NONCHARACTER_CODE_POINT,
    UPROPS_GRAPHEME_EXTEND,
    UPROPS_GRAPHEME_LINK,
    UPROPS_IDS_BINARY_OPERATOR,
    UPROPS_IDS_TRINARY_OPERATOR,
    UPROPS_RADICAL,
    UPROPS_UNIFIED_IDEOGRAPH,
    UPROPS_DEFAULT_IGNORABLE_CODE_POINT,
    UPROPS_DEPRECATED,
    UPROPS_LOGICAL_ORDER_EXCEPTION,
    UPROPS_XID_START,
    UPROPS_XID_CONTINUE,
    UPROPS_ID_START,                            /* ICU 2.6, uprops format version 3.2 */
    UPROPS_ID_CONTINUE,
    UPROPS_GRAPHEME_BASE,
    UPROPS_S_TERM,                              /* new in ICU 3.0 and Unicode 4.0.1 */
    UPROPS_VARIATION_SELECTOR,
    UPROPS_PATTERN_SYNTAX,                      /* new in ICU 3.4 and Unicode 4.1 */
    UPROPS_PATTERN_WHITE_SPACE,
    UPROPS_RESERVED,                            /* reserved & unused */
    UPROPS_BINARY_1_TOP                         /* ==32 - full! */
};

/*
 * Properties in vector word 2
 * Bits
 * 31..26   reserved
 * 25..20   Line Break
 * 19..15   Sentence Break
 * 14..10   Word Break
 *  9.. 5   Grapheme Cluster Break
 *  4.. 0   Decomposition Type
 */
#define UPROPS_LB_MASK          0x03f00000
#define UPROPS_LB_SHIFT         20

#define UPROPS_SB_MASK          0x000f8000
#define UPROPS_SB_SHIFT         15

#define UPROPS_WB_MASK          0x00007c00
#define UPROPS_WB_SHIFT         10

#define UPROPS_GCB_MASK         0x000003e0
#define UPROPS_GCB_SHIFT        5

#define UPROPS_DT_MASK          0x0000001f


/** Turn a bit index into a bit flag. @internal */
#define FLAG(n) ((uint32_t)1<<(n))

/** Flags for general categories in the order of UCharCategory. @internal */
#define _Cn     FLAG(U_GENERAL_OTHER_TYPES)
constexpr static const uint32_t _Lu = FLAG(U_UPPERCASE_LETTER);
constexpr static const uint32_t  _Ll =  FLAG(U_LOWERCASE_LETTER);
constexpr static const uint32_t  _Lt =  FLAG(U_TITLECASE_LETTER);
constexpr static const uint32_t  _Lm =  FLAG(U_MODIFIER_LETTER);
/* constexpr static const uint32_t  _Lo =  FLAG(U_OTHER_LETTER) -- conflicts with MS Visual Studio 9.0 xiosbase */
constexpr static const uint32_t  _Mn =  FLAG(U_NON_SPACING_MARK);
constexpr static const uint32_t  _Me =  FLAG(U_ENCLOSING_MARK);
constexpr static const uint32_t  _Mc =  FLAG(U_COMBINING_SPACING_MARK);
constexpr static const uint32_t  _Nd =  FLAG(U_DECIMAL_DIGIT_NUMBER);
constexpr static const uint32_t  _Nl =  FLAG(U_LETTER_NUMBER);
constexpr static const uint32_t  _No =  FLAG(U_OTHER_NUMBER);
constexpr static const uint32_t  _Zs =  FLAG(U_SPACE_SEPARATOR);
constexpr static const uint32_t  _Zl =  FLAG(U_LINE_SEPARATOR);
constexpr static const uint32_t  _Zp =  FLAG(U_PARAGRAPH_SEPARATOR);
constexpr static const uint32_t  _Cc =  FLAG(U_CONTROL_CHAR);
constexpr static const uint32_t  _Cf =  FLAG(U_FORMAT_CHAR);
constexpr static const uint32_t  _Co =  FLAG(U_PRIVATE_USE_CHAR);
constexpr static const uint32_t  _Cs =  FLAG(U_SURROGATE);
constexpr static const uint32_t  _Pd =  FLAG(U_DASH_PUNCTUATION);
constexpr static const uint32_t  _Ps =  FLAG(U_START_PUNCTUATION);
/* constexpr static const uint32_t  _Pe =  FLAG(U_END_PUNCTUATION) -- conflicts with MS Visual Studio 9.0 xlocnum */
/* constexpr static const uint32_t  _Pc =  FLAG(U_CONNECTOR_PUNCTUATION) -- conflicts with MS Visual Studio 9.0 streambuf */
constexpr static const uint32_t  _Po =  FLAG(U_OTHER_PUNCTUATION);
constexpr static const uint32_t  _Sm =  FLAG(U_MATH_SYMBOL);
constexpr static const uint32_t  _Sc =  FLAG(U_CURRENCY_SYMBOL);
constexpr static const uint32_t  _Sk =  FLAG(U_MODIFIER_SYMBOL);
constexpr static const uint32_t  _So =  FLAG(U_OTHER_SYMBOL);
constexpr static const uint32_t  _Pi =  FLAG(U_INITIAL_PUNCTUATION);
/* #define _Pf     FLAG(U_FINAL_PUNCTUATION) -- conflicts with MS Visual Studio 9.0 streambuf */

/** Some code points. @internal */
enum {
    TAB     =0x0009,
    LF      =0x000a,
    FF      =0x000c,
    CR      =0x000d,
    U_A     =0x0041,
    U_F     =0x0046,
    U_Z     =0x005a,
    U_a     =0x0061,
    U_f     =0x0066,
    U_z     =0x007a,
    DEL     =0x007f,
    NL      =0x0085,
    NBSP    =0x00a0,
    CGJ     =0x034f,
    FIGURESP=0x2007,
    HAIRSP  =0x200a,
    ZWNJ    =0x200c,
    ZWJ     =0x200d,
    RLM     =0x200f,
    NNBSP   =0x202f,
    WJ      =0x2060,
    INHSWAP =0x206a,
    NOMDIG  =0x206f,
    U_FW_A  =0xff21,
    U_FW_F  =0xff26,
    U_FW_Z  =0xff3a,
    U_FW_a  =0xff41,
    U_FW_f  =0xff46,
    U_FW_z  =0xff5a,
    ZWNBSP  =0xfeff
};


/**
 * Constants for which data and implementation files provide which properties.
 * Used by UnicodeSet for service-specific property enumeration.
 * @internal
 */
enum UPropertySource {
    /** No source, not a supported property. */
    UPROPS_SRC_NONE,
    /** From uchar.c/uprops.icu main trie */
    UPROPS_SRC_CHAR,
    /** From uchar.c/uprops.icu properties vectors trie */
    UPROPS_SRC_PROPSVEC,
    /** From unames.c/unames.icu */
    UPROPS_SRC_NAMES,
    /** From ucase.c/ucase.icu */
    UPROPS_SRC_CASE,
    /** From ubidi_props.c/ubidi.icu */
    UPROPS_SRC_BIDI,
    /** From uchar.c/uprops.icu main trie as well as properties vectors trie */
    UPROPS_SRC_CHAR_AND_PROPSVEC,
    /** From ucase.c/ucase.icu as well as unorm.cpp/unorm.icu */
    UPROPS_SRC_CASE_AND_NORM,
    /** From normalizer2impl.cpp/nfc.nrm */
    UPROPS_SRC_NFC,
    /** From normalizer2impl.cpp/nfkc.nrm */
    UPROPS_SRC_NFKC,
    /** From normalizer2impl.cpp/nfkc_cf.nrm */
    UPROPS_SRC_NFKC_CF,
    /** From normalizer2impl.cpp/nfc.nrm canonical iterator data */
    UPROPS_SRC_NFC_CANON_ITER,
    /** One more than the highest UPropertySource (UPROPS_SRC_) constant. */
    UPROPS_SRC_COUNT
};
typedef enum UPropertySource UPropertySource;

}

#endif /* UNICODE_UPROPS_H_ */
