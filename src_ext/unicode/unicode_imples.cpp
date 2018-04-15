/*
 * Copyright (c) Tomohiro Iizuka. All rights reserved.
 * Licensed under the MIT license.
 */


#include "stdtypes.h"
#include "ubidi_props.h"
#include "uchar.h"

namespace icu {


UCharDirection
ubidi_getClass(const UBiDiProps *bdp, uint32_t c) throw() {
    uint16_t props=UTRIE2_GET16(&bdp->trie, c);
    return (UCharDirection)UBIDI_GET_CLASS(props);
}
UBool
ubidi_isMirrored(const UBiDiProps *bdp, uint32_t c) throw() {
    uint16_t props=UTRIE2_GET16(&bdp->trie, c);
    return (UBool)UBIDI_GET_FLAG(props, UBIDI_IS_MIRRORED_SHIFT);
}
uint32_t
getMirror(const UBiDiProps *bdp, uint32_t c, uint16_t props) throw() {
    int32_t delta=UBIDI_GET_MIRROR_DELTA(props);
    if(delta!=UBIDI_ESC_MIRROR_DELTA) {
        return c+delta;
    } else {
        /* look for mirror code point in the mirrors[] table */
        const uint32_t *mirrors;
        uint32_t m;
        int32_t i, length;
        uint32_t c2;

        mirrors=bdp->mirrors;
        length=bdp->indexes[UBIDI_IX_MIRROR_LENGTH];

        /* linear search */
        for(i=0; i<length; ++i) {
            m=mirrors[i];
            c2=UBIDI_GET_MIRROR_CODE_POINT(m);
            if(c==c2) {
                /* found c, return its mirror code point using the index in m */
                return UBIDI_GET_MIRROR_CODE_POINT(mirrors[UBIDI_GET_MIRROR_INDEX(m)]);
            } else if(c<c2) {
                break;
            }
        }

        /* c not found, return it itself */
        return c;
    }
    return 0;
}

uint32_t
ubidi_getMirror(const UBiDiProps *bdp, uint32_t c) throw() {
    uint16_t props=UTRIE2_GET16(&bdp->trie, c);
    return getMirror(bdp, c, props);
}

/////////////// uchar.h
uint32_t
u_getUnicodeProperties(uint32_t c, int32_t column) throw() {
    if(column>=propsVectorsColumns) {
        return 0;
    } else {
        uint16_t vecIndex=UTRIE2_GET16(&propsVectorsTrie, c);
        return propsVectors[vecIndex+column];
    }
}

uint8_t u_charType(uint32_t c) throw() {
	uint32_t props;
    GET_PROPS(c, props);
    return (uint8_t)GET_CATEGORY(props);
}

/* Checks if ch is a lower case letter.*/
UBool
u_islower(uint32_t c) throw() {
    uint32_t props;
    GET_PROPS(c, props);
    return (UBool)(GET_CATEGORY(props)==U_LOWERCASE_LETTER);
}

/* Checks if ch is an upper case letter.*/
UBool
u_isupper(uint32_t c) throw() {
    uint32_t props;
    GET_PROPS(c, props);
    return (UBool)(GET_CATEGORY(props)==U_UPPERCASE_LETTER);
}

/* Checks if ch is a title case letter; usually upper case letters.*/
UBool
u_istitle(uint32_t c) throw() {
    uint32_t props;
    GET_PROPS(c, props);
    return (UBool)(GET_CATEGORY(props)==U_TITLECASE_LETTER);
}

/* Checks if ch is a decimal digit. */
UBool
u_isdigit(uint32_t c) throw() {
    uint32_t props;
    GET_PROPS(c, props);
    return (UBool)(GET_CATEGORY(props)==U_DECIMAL_DIGIT_NUMBER);
}

UBool
u_isxdigit(uint32_t c) throw() {
    uint32_t props;

    /* check ASCII and Fullwidth ASCII a-fA-F */
    if(
        (c<=0x66 && c>=0x41 && (c<=0x46 || c>=0x61)) ||
        (c>=0xff21 && c<=0xff46 && (c<=0xff26 || c>=0xff41))
    ) {
        return 1;
    }

    GET_PROPS(c, props);
    return (UBool)(GET_CATEGORY(props)==U_DECIMAL_DIGIT_NUMBER);
}

/* Checks if the Unicode character is a letter.*/
UBool
u_isalpha(uint32_t c) throw() {
    uint32_t props;
    GET_PROPS(c, props);
    return (UBool)((CAT_MASK(props)&U_GC_L_MASK)!=0);
}

UBool
u_isUAlphabetic(uint32_t c) throw() {
    return (u_getUnicodeProperties(c, 1) & U_MASK(UPROPS_ALPHABETIC))!=0;
}

/* Checks if c is a letter or a decimal digit */
UBool
u_isalnum(uint32_t c) throw() {
    uint32_t props;
    GET_PROPS(c, props);
    return (UBool)((CAT_MASK(props)&(U_GC_L_MASK|U_GC_ND_MASK))!=0);
}

/**
 * Checks if c is alphabetic, or a decimal digit; implements UCHAR_POSIX_ALNUM.
 * @internal
 */
UBool
u_isalnumPOSIX(uint32_t c) throw() {
    return (UBool)(u_isUAlphabetic(c) || u_isdigit(c));
}

/* Checks if ch is a unicode character with assigned character type.*/
UBool
u_isdefined(uint32_t c) throw() {
    uint32_t props;
    GET_PROPS(c, props);
    return (UBool)(GET_CATEGORY(props)!=0);
}

/* Checks if the Unicode character is a base form character that can take a diacritic.*/
UBool
u_isbase(uint32_t c) throw() {
    uint32_t props;
    GET_PROPS(c, props);
    return (UBool)((CAT_MASK(props)&(U_GC_L_MASK|U_GC_N_MASK|U_GC_MC_MASK|U_GC_ME_MASK))!=0);
}

/* Checks if the Unicode character is a control character.*/
UBool
u_iscntrl(uint32_t c) throw() {
    uint32_t props;
    GET_PROPS(c, props);
    return (UBool)((CAT_MASK(props)&(U_GC_CC_MASK|U_GC_CF_MASK|U_GC_ZL_MASK|U_GC_ZP_MASK))!=0);
}

UBool
u_isISOControl(uint32_t c) throw() {
    return (uint32_t)c<=0x9f && (c<=0x1f || c>=0x7f);
}

/* Checks if the Unicode character is a space character.*/
UBool
u_isspace(uint32_t c) throw() {
    uint32_t props;
    GET_PROPS(c, props);
    return (UBool)((CAT_MASK(props)&U_GC_Z_MASK)!=0 || IS_THAT_CONTROL_SPACE(c));
}

UBool
u_isJavaSpaceChar(uint32_t c) throw() {
    uint32_t props;
    GET_PROPS(c, props);
    return (UBool)((CAT_MASK(props)&U_GC_Z_MASK)!=0);
}

/* Checks if the Unicode character is a whitespace character.*/
UBool
u_isWhitespace(uint32_t c) throw() {
    uint32_t props;
    GET_PROPS(c, props);
    return (UBool)(
                ((CAT_MASK(props)&U_GC_Z_MASK)!=0 &&
                    c!=NBSP && c!=FIGURESP && c!=NNBSP) || /* exclude no-break spaces */
                IS_THAT_ASCII_CONTROL_SPACE(c)
           );
}

UBool
u_isblank(uint32_t c) throw() {
    if((uint32_t)c<=0x9f) {
        return c==9 || c==0x20; /* TAB or SPACE */
    } else {
        /* Zs */
        uint32_t props;
        GET_PROPS(c, props);
        return (UBool)(GET_CATEGORY(props)==U_SPACE_SEPARATOR);
    }
}

UBool
u_isUWhiteSpace(uint32_t c) throw() {
    return (u_getUnicodeProperties(c, 1)&U_MASK(UPROPS_WHITE_SPACE))!=0;
}

/* Checks if the Unicode character is printable.*/
UBool
u_isprint(uint32_t c) throw() {
    uint32_t props;
    GET_PROPS(c, props);
    /* comparing ==0 returns FALSE for the categories mentioned */
    return (UBool)((CAT_MASK(props)&U_GC_C_MASK)==0);
}

/**
 * Checks if c is in
 * [^\p{space}\p{gc=Control}\p{gc=Surrogate}\p{gc=Unassigned}]
 * with space=\p{Whitespace} and Control=Cc.
 * Implements UCHAR_POSIX_GRAPH.
 * @internal
 */
UBool
u_isgraphPOSIX(uint32_t c) throw() {
    uint32_t props;
    GET_PROPS(c, props);
    /* \p{space}\p{gc=Control} == \p{gc=Z}\p{Control} */
    /* comparing ==0 returns FALSE for the categories mentioned */
    return (UBool)((CAT_MASK(props)&
                    (U_GC_CC_MASK|U_GC_CS_MASK|U_GC_CN_MASK|U_GC_Z_MASK))
                   ==0);
}

/**
 * Checks if c is in \p{graph}\p{blank} - \p{cntrl}.
 * Implements UCHAR_POSIX_PRINT.
 * @internal
 */
UBool
u_isprintPOSIX(uint32_t c) throw() {
    uint32_t props;
    GET_PROPS(c, props);
    /*
     * The only cntrl character in graph+blank is TAB (in blank).
     * Here we implement (blank-TAB)=Zs instead of calling u_isblank().
     */
    return (UBool)((GET_CATEGORY(props)==U_SPACE_SEPARATOR) || u_isgraphPOSIX(c));
}

UBool
u_isgraph(uint32_t c) throw() {
    uint32_t props;
    GET_PROPS(c, props);
    /* comparing ==0 returns FALSE for the categories mentioned */
    return (UBool)((CAT_MASK(props)&
                    (U_GC_CC_MASK|U_GC_CF_MASK|U_GC_CS_MASK|U_GC_CN_MASK|U_GC_Z_MASK))
                   ==0);
}

UBool
u_ispunct(uint32_t c) throw() {
    uint32_t props;
    GET_PROPS(c, props);
    return (UBool)((CAT_MASK(props)&U_GC_P_MASK)!=0);
}

/* Checks if the Unicode character can start a Unicode identifier.*/
UBool
u_isIDStart(uint32_t c) throw() {
    /* same as u_isalpha() */
    uint32_t props;
    GET_PROPS(c, props);
    return (UBool)((CAT_MASK(props)&(U_GC_L_MASK|U_GC_NL_MASK))!=0);
}

/*Checks if the Unicode character can be ignorable in a Java or Unicode identifier.*/
UBool
u_isIDIgnorable(uint32_t c) throw() {
    if(c<=0x9f) {
        return u_isISOControl(c) && !IS_THAT_ASCII_CONTROL_SPACE(c);
    } else {
        uint32_t props;
        GET_PROPS(c, props);
        return (UBool)(GET_CATEGORY(props)==U_FORMAT_CHAR);
    }
}

/* Checks if the Unicode character can be a Unicode identifier part other than starting the
 identifier.*/
UBool
u_isIDPart(uint32_t c) throw() {
    uint32_t props;
    GET_PROPS(c, props);
    return (UBool)(
           (CAT_MASK(props)&
            (U_GC_ND_MASK|U_GC_NL_MASK|
             U_GC_L_MASK|
             U_GC_PC_MASK|U_GC_MC_MASK|U_GC_MN_MASK)
           )!=0 ||
           u_isIDIgnorable(c));
}

/*Checks if the Unicode character can start a Java identifier.*/
UBool
u_isJavaIDStart(uint32_t c) throw() {
    uint32_t props;
    GET_PROPS(c, props);
    return (UBool)((CAT_MASK(props)&(U_GC_L_MASK|U_GC_SC_MASK|U_GC_PC_MASK))!=0);
}

/*Checks if the Unicode character can be a Java identifier part other than starting the
 * identifier.
 */
UBool
u_isJavaIDPart(uint32_t c) throw() {
    uint32_t props;
    GET_PROPS(c, props);
    return (UBool)(
           (CAT_MASK(props)&
            (U_GC_ND_MASK|U_GC_NL_MASK|
             U_GC_L_MASK|
             U_GC_SC_MASK|U_GC_PC_MASK|
             U_GC_MC_MASK|U_GC_MN_MASK)
           )!=0 ||
           u_isIDIgnorable(c));
}

int32_t
u_charDigitValue(uint32_t c) throw() {
    uint32_t props;
    int32_t value;
    GET_PROPS(c, props);
    value=(int32_t)GET_NUMERIC_TYPE_VALUE(props)-UPROPS_NTV_DECIMAL_START;
    if(value<=9) {
        return value;
    } else {
        return -1;
    }
}

double
u_getNumericValue(uint32_t c) throw() {
    uint32_t props;
    int32_t ntv;
    GET_PROPS(c, props);
    ntv=(int32_t)GET_NUMERIC_TYPE_VALUE(props);

    if(ntv==UPROPS_NTV_NONE) {
        return U_NO_NUMERIC_VALUE;
    } else if(ntv<UPROPS_NTV_DIGIT_START) {
        /* decimal digit */
        return ntv-UPROPS_NTV_DECIMAL_START;
    } else if(ntv<UPROPS_NTV_NUMERIC_START) {
        /* other digit */
        return ntv-UPROPS_NTV_DIGIT_START;
    } else if(ntv<UPROPS_NTV_FRACTION_START) {
        /* small integer */
        return ntv-UPROPS_NTV_NUMERIC_START;
    } else if(ntv<UPROPS_NTV_LARGE_START) {
        /* fraction */
        int32_t numerator=(ntv>>4)-12;
        int32_t denominator=(ntv&0xf)+1;
        return (double)numerator/denominator;
    } else if(ntv<UPROPS_NTV_BASE60_START) {
        /* large, single-significant-digit integer */
        double numValue;
        int32_t mant=(ntv>>5)-14;
        int32_t exp=(ntv&0x1f)+2;
        numValue=mant;

        /* multiply by 10^exp without math.h */
        while(exp>=4) {
            numValue*=10000.;
            exp-=4;
        }
        switch(exp) {
        case 3:
            numValue*=1000.;
            break;
        case 2:
            numValue*=100.;
            break;
        case 1:
            numValue*=10.;
            break;
        case 0:
        default:
            break;
        }

        return numValue;
    } else if(ntv<UPROPS_NTV_RESERVED_START) {
        /* sexagesimal (base 60) integer */
        int32_t numValue=(ntv>>2)-0xbf;
        int32_t exp=(ntv&3)+1;

        switch(exp) {
        case 4:
            numValue*=60*60*60*60;
            break;
        case 3:
            numValue*=60*60*60;
            break;
        case 2:
            numValue*=60*60;
            break;
        case 1:
            numValue*=60;
            break;
        case 0:
        default:
            break;
        }

        return numValue;
    } else {
        /* reserved */
        return U_NO_NUMERIC_VALUE;
    }
}

int8_t
u_digit(uint32_t ch, int8_t radix) throw() {
    int8_t value;
    if((uint8_t)(radix-2)<=(36-2)) {
        value=(int8_t)u_charDigitValue(ch);
        if(value<0) {
            /* ch is not a decimal digit, try latin letters */
            if(ch>=0x61 && ch<=0x7A) {
                value=(int8_t)(ch-0x57);  /* ch - 'a' + 10 */
            } else if(ch>=0x41 && ch<=0x5A) {
                value=(int8_t)(ch-0x37);  /* ch - 'A' + 10 */
            } else if(ch>=0xFF41 && ch<=0xFF5A) {
                value=(int8_t)(ch-0xFF37);  /* fullwidth ASCII a-z */
            } else if(ch>=0xFF21 && ch<=0xFF3A) {
                value=(int8_t)(ch-0xFF17);  /* fullwidth ASCII A-Z */
            }
        }
    } else {
        value=-1;   /* invalid radix */
    }
    return (int8_t)((value<radix) ? value : -1);
}

uint32_t
u_forDigit(int32_t digit, int8_t radix) throw() {
    if((uint8_t)(radix-2)>(36-2) || (uint32_t)digit>=(uint32_t)radix) {
        return 0;
    } else if(digit<10) {
        return (uint32_t)(0x30+digit);
    } else {
        return (uint32_t)((0x61-10)+digit);
    }
}

UCharDirection
u_charDirection(uint32_t c) throw() {
    return ubidi_getClass(&ubidi_props_singleton, c);
}

UBool
u_isMirrored(uint32_t c) throw() {
    return ubidi_isMirrored(&ubidi_props_singleton, c);
}

uint32_t
u_charMirror(uint32_t c) throw() {
    return ubidi_getMirror(&ubidi_props_singleton, c);
}


/* simple case mappings ----------------------------------------------------- */

uint32_t
ucase_tolower(const UCaseProps *csp, uint32_t c) throw() {
    uint16_t props=UTRIE2_GET16(&csp->trie, c);
    if(!PROPS_HAS_EXCEPTION(props)) {
        if(UCASE_GET_TYPE(props)>=UCASE_UPPER) {
            c+=UCASE_GET_DELTA(props);
        }
    } else {
        const uint16_t *pe=GET_EXCEPTIONS(csp, props);
        uint16_t excWord=*pe++;
        if(HAS_SLOT(excWord, UCASE_EXC_LOWER)) {
            GET_SLOT_VALUE(excWord, UCASE_EXC_LOWER, pe, c);
        }
    }
    return c;
}

uint32_t
ucase_toupper(const UCaseProps *csp, uint32_t c) throw() {
    uint16_t props=UTRIE2_GET16(&csp->trie, c);
    if(!PROPS_HAS_EXCEPTION(props)) {
        if(UCASE_GET_TYPE(props)==UCASE_LOWER) {
            c+=UCASE_GET_DELTA(props);
        }
    } else {
        const uint16_t *pe=GET_EXCEPTIONS(csp, props);
        uint16_t excWord=*pe++;
        if(HAS_SLOT(excWord, UCASE_EXC_UPPER)) {
            GET_SLOT_VALUE(excWord, UCASE_EXC_UPPER, pe, c);
        }
    }
    return c;
}

uint32_t
ucase_totitle(const UCaseProps *csp, uint32_t c) throw() {
    uint16_t props=UTRIE2_GET16(&csp->trie, c);
    if(!PROPS_HAS_EXCEPTION(props)) {
        if(UCASE_GET_TYPE(props)==UCASE_LOWER) {
            c+=UCASE_GET_DELTA(props);
        }
    } else {
        const uint16_t *pe=GET_EXCEPTIONS(csp, props);
        uint16_t excWord=*pe++;
        int32_t idx;
        if(HAS_SLOT(excWord, UCASE_EXC_TITLE)) {
            idx=UCASE_EXC_TITLE;
        } else if(HAS_SLOT(excWord, UCASE_EXC_UPPER)) {
            idx=UCASE_EXC_UPPER;
        } else {
            return c;
        }
        GET_SLOT_VALUE(excWord, idx, pe, c);
    }
    return c;
}

uint32_t
ucase_fold(const UCaseProps *csp, uint32_t c, uint32_t options) throw() {
    uint16_t props=UTRIE2_GET16(&csp->trie, c);
    if(!PROPS_HAS_EXCEPTION(props)) {
        if(UCASE_GET_TYPE(props)>=UCASE_UPPER) {
            c+=UCASE_GET_DELTA(props);
        }
    } else {
        const uint16_t *pe=GET_EXCEPTIONS(csp, props);
        uint16_t excWord=*pe++;
        int32_t idx;
        if(excWord&UCASE_EXC_CONDITIONAL_FOLD) {
            /* special case folding mappings, hardcoded */
            if((options&_FOLD_CASE_OPTIONS_MASK)==U_FOLD_CASE_DEFAULT) {
                /* default mappings */
                if(c==0x49) {
                    /* 0049; C; 0069; # LATIN CAPITAL LETTER I */
                    return 0x69;
                } else if(c==0x130) {
                    /* no simple case folding for U+0130 */
                    return c;
                }
            } else {
                /* Turkic mappings */
                if(c==0x49) {
                    /* 0049; T; 0131; # LATIN CAPITAL LETTER I */
                    return 0x131;
                } else if(c==0x130) {
                    /* 0130; T; 0069; # LATIN CAPITAL LETTER I WITH DOT ABOVE */
                    return 0x69;
                }
            }
        }
        if(HAS_SLOT(excWord, UCASE_EXC_FOLD)) {
            idx=UCASE_EXC_FOLD;
        } else if(HAS_SLOT(excWord, UCASE_EXC_LOWER)) {
            idx=UCASE_EXC_LOWER;
        } else {
            return c;
        }
        GET_SLOT_VALUE(excWord, idx, pe, c);
    }
    return c;
}


/* case mapping properties API ---------------------------------------------- */

/* Transforms the Unicode character to its lower case equivalent.*/
uint32_t
u_tolower(uint32_t c) throw() {
    return ucase_tolower(GET_CASE_PROPS(), c);
}

/* Transforms the Unicode character to its upper case equivalent.*/
uint32_t
u_toupper(uint32_t c) throw() {
    return ucase_toupper(GET_CASE_PROPS(), c);
}

/* Transforms the Unicode character to its title case equivalent.*/
uint32_t
u_totitle(uint32_t c) throw() {
    return ucase_totitle(GET_CASE_PROPS(), c);
}

/* return the simple case folding mapping for c */
uint32_t
u_foldCase(uint32_t c, uint32_t options) throw() {
    return ucase_fold(GET_CASE_PROPS(), c, options);
}

}

