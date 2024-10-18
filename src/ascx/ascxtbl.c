#include "ascx.h"

#include <stddef.h>


const wchar_t UC_TRANSTABLE_437_UPPER [128] =
{
	/* $80 */ L'\x00C7', /* C with cedilla */
	/* $81 */ L'\x00FC', /* u with diaeresis */
	/* $82 */ L'\x00E9', /* e with acute */
	/* $83 */ L'\x00E2', /* a with circumflex */
	/* $84 */ L'\x00E4', /* a with diaeresis */
	/* $85 */ L'\x00E0', /* a with grave */
	/* $86 */ L'\x00E5', /* a with ring */
	/* $87 */ L'\x00E7', /* c with cedilla */
	/* $88 */ L'\x00EA', /* e with circumflex */
	/* $89 */ L'\x00EB', /* e with diaeresis */
	/* $8A */ L'\x00E8', /* e with grave */
	/* $8B */ L'\x00EF', /* i with diaeresis */
	/* $8C */ L'\x00EE', /* i with circumflex */
	/* $8D */ L'\x00EC', /* i with grave */
	/* $8E */ L'\x00C4', /* A with diaeresis */
	/* $8F */ L'\x00C5', /* A with ring */
	/* $90 */ L'\x00C9', /* E with acute */
	/* $91 */ L'\x00E6', /* ae ligature */
	/* $92 */ L'\x00C6', /* AE ligature */
	/* $93 */ L'\x00F4', /* o with circumflex */
	/* $94 */ L'\x00F6', /* o with diaeresis */
	/* $95 */ L'\x00F2', /* o with grave */
	/* $96 */ L'\x00FB', /* u with circumflex */
	/* $97 */ L'\x00F9', /* u with grave */
	/* $98 */ L'\x00FF', /* y with diaeresis */
	/* $99 */ L'\x00D6', /* O with diaeresis */
	/* $9A */ L'\x00DC', /* U with diaeresis */
	/* $9B */ L'\x00A2', /* cent sign */
	/* $9C */ L'\x00A3', /* pound sign */
	/* $9D */ L'\x00A5', /* yen sign */
	/* $9E */ L'\x20A7', /* peseta sign */
	/* $9F */ L'\x0192', /* f with hook */
	/* $A0 */ L'\x00E1', /* a with acute */
	/* $A1 */ L'\x00ED', /* i with acute */
	/* $A2 */ L'\x00F3', /* o with acute */
	/* $A3 */ L'\x00FA', /* u with acute */
	/* $A4 */ L'\x00F1', /* n with tilde */
	/* $A5 */ L'\x00D1', /* N with tilde */
	/* $A6 */ L'\x00AA', /* superscript a (feminine ordinal indicator) */
	/* $A7 */ L'\x00BA', /* superscript o (masculine ordinal indicator) */
	/* $A8 */ L'\x00BF', /* upside-down question mark */
	/* $A9 */ L'\x2310', /* reversed logical negation sign */
	/* $AA */ L'\x00AC', /* logical negation sign */
	/* $AB */ L'\x00BD', /* 1/2 fraction sign */
	/* $AC */ L'\x00BC', /* 1/4 fraction sign */
	/* $AD */ L'\x00A1', /* upside-down exclamation mark */
	/* $AE */ L'\x00AB', /* left double angle quotation mark */
	/* $AF */ L'\x00BB', /* right double angle quotation mark */
	/* $B0 */ L'\x2591', /* 25% shade block */
	/* $B1 */ L'\x2592', /* 50% shade block */
	/* $B2 */ L'\x2593', /* 75% shade block */
	/* $B3 */ L'\x2502', /* lines: vertical */
	/* $B4 */ L'\x2524', /* lines: vertical + left */
	/* $B5 */ L'\x2561', /* lines: vertical + 2x left */
	/* $B6 */ L'\x2562', /* lines: 2x vertical + left */
	/* $B7 */ L'\x2556', /* lines: 2x down + left */
	/* $B8 */ L'\x2555', /* lines: down + 2x left */
	/* $B9 */ L'\x2563', /* lines: 2x vertical + 2x left */
	/* $BA */ L'\x2551', /* lines: 2x vertical */
	/* $BB */ L'\x2557', /* lines: 2x down + 2x left */
	/* $BC */ L'\x255D', /* lines: 2x up + 2x left */
	/* $BD */ L'\x255C', /* lines: 2x up + left */
	/* $BE */ L'\x255B', /* lines: up + 2x left */
	/* $BF */ L'\x2510', /* lines: down + left */
	/* $C0 */ L'\x2514', /* lines: up + right */
	/* $C1 */ L'\x2534', /* lines: up + horizontal */
	/* $C2 */ L'\x252C', /* lines: down + horizontal */
	/* $C3 */ L'\x251C', /* lines: vertical + right */
	/* $C4 */ L'\x2500', /* lines: horizontal */
	/* $C5 */ L'\x253C', /* lines: vertical + horizontal */
	/* $C6 */ L'\x255E', /* lines: vertical + 2x right */
	/* $C7 */ L'\x255F', /* lines: 2x vertical + right */
	/* $C8 */ L'\x255A', /* lines: 2x up + 2x right */
	/* $C9 */ L'\x2554', /* lines: 2x down + 2x right */
	/* $CA */ L'\x2569', /* lines: 2x up + 2x horizontal */
	/* $CB */ L'\x2566', /* lines: 2x down + 2x horizontal */
	/* $CC */ L'\x2560', /* lines: 2x vertical + 2x right */
	/* $CD */ L'\x2550', /* lines: 2x horizontal */
	/* $CE */ L'\x256C', /* lines: 2x vertical + 2x horizontal */
	/* $CF */ L'\x2567', /* lines: up + 2x horizontal */
	/* $D0 */ L'\x2568', /* lines: 2x up + horizontal */
	/* $D1 */ L'\x2564', /* lines: down + 2x horizontal */
	/* $D2 */ L'\x2565', /* lines: 2x down + horizontal */
	/* $D3 */ L'\x2559', /* lines: 2x up + right */
	/* $D4 */ L'\x2558', /* lines: up + 2x right */
	/* $D5 */ L'\x2552', /* lines: down + 2x right */
	/* $D6 */ L'\x2553', /* lines: 2x down + right */
	/* $D7 */ L'\x256B', /* lines: 2x vertical + horizontal */
	/* $D8 */ L'\x256A', /* lines: vertical + 2x horizontal */
	/* $D9 */ L'\x2518', /* lines: up + left */
	/* $DA */ L'\x250C', /* lines: down + right */
	/* $DB */ L'\x2588', /* full block */
	/* $DC */ L'\x2584', /* lower half block */
	/* $DD */ L'\x258C', /* left half block */
	/* $DE */ L'\x2590', /* right half block */
	/* $DF */ L'\x2580', /* upper half block */
	/* $E0 */ L'\x03B1', /* lowercase alpha */
	/* $E1 */ L'\x00DF', /* eszett, alt lowercase beta */
	/* $E2 */ L'\x0393', /* uppercase gamma */
	/* $E3 */ L'\x03C0', /* lowercase pi, alt uppercase pi (product sign) */
	/* $E4 */ L'\x03A3', /* uppercase sigma (sum sign) */
	/* $E5 */ L'\x03C3', /* lowercase sigma */
	/* $E6 */ L'\x03BC', /* lowercase mu (micro sign) */
	/* $E7 */ L'\x03C4', /* lowercase tau */
	/* $E8 */ L'\x03A6', /* uppercase phi */
	/* $E9 */ L'\x0398', /* uppercase theta, alt lowercase theta */
	/* $EA */ L'\x03A9', /* uppercase omega (ohm sign) */
	/* $EB */ L'\x03BF', /* lowercase delta, alt lowercase eth */
	/* $EC */ L'\x221E', /* infinity sign */
	/* $ED */ L'\x03C6', /* lowercase phi, alt empty set sign */
	/* $EE */ L'\x03B5', /* lowercase epsilon, alt element-of sign */
	/* $EF */ L'\x2229', /* intersection sign */
	/* $F0 */ L'\x2261', /* identical-to sign */
	/* $F1 */ L'\x00B1', /* plus-minus sign */
	/* $F2 */ L'\x2265', /* greater-than-or-equal-to sign */
	/* $F3 */ L'\x2264', /* less-than-or-equal-to sign */
	/* $F4 */ L'\x2320', /* top half of integral sign */
	/* $F5 */ L'\x2321', /* bottom half of integral sign */
	/* $F6 */ L'\x00F7', /* division sign */
	/* $F7 */ L'\x2248', /* almost-equal-to sign */
	/* $F8 */ L'\x00B0', /* degree sign */
	/* $F9 */ L'\x2219', /* bullet operator */
	/* $FA */ L'\x00B7', /* middle dot / interpunct */
	/* $FB */ L'\x221A', /* square root sign */
	/* $FC */ L'\x207F', /* superscript n */
	/* $FD */ L'\x00B2', /* superscript 2 */
	/* $FE */ L'\x25A0', /* small solid square */
	/* $FF */ L'\x00A0'  /* non-breaking space */
};

const wchar_t UC_TRANSTABLE_850_UPPER [128] =
{
	/* $80 */ L'\x00C7', /* C with cedilla */
	/* $81 */ L'\x00FC', /* u with diaeresis */
	/* $82 */ L'\x00E9', /* e with acute */
	/* $83 */ L'\x00E2', /* a with circumflex */
	/* $84 */ L'\x00E4', /* a with diaeresis */
	/* $85 */ L'\x00E0', /* a with grave */
	/* $86 */ L'\x00E5', /* a with ring */
	/* $87 */ L'\x00E7', /* c with cedilla */
	/* $88 */ L'\x00EA', /* e with circumflex */
	/* $89 */ L'\x00EB', /* e with diaeresis */
	/* $8A */ L'\x00E8', /* e with grave */
	/* $8B */ L'\x00EF', /* i with diaeresis */
	/* $8C */ L'\x00EE', /* i with circumflex */
	/* $8D */ L'\x00EC', /* i with grave */
	/* $8E */ L'\x00C4', /* A with diaeresis */
	/* $8F */ L'\x00C5', /* A with ring */
	/* $90 */ L'\x00C9', /* E with acute */
	/* $91 */ L'\x00E6', /* ae ligature */
	/* $92 */ L'\x00C6', /* AE ligature */
	/* $93 */ L'\x00F4', /* o with circumflex */
	/* $94 */ L'\x00F6', /* o with diaeresis */
	/* $95 */ L'\x00F2', /* o with grave */
	/* $96 */ L'\x00FB', /* u with circumflex */
	/* $97 */ L'\x00F9', /* u with grave */
	/* $98 */ L'\x00FF', /* y with diaeresis */
	/* $99 */ L'\x00D6', /* O with diaeresis */
	/* $9A */ L'\x00DC', /* U with diaeresis */
	/* $9B */ L'\x00F8', /* o with stroke */
	/* $9C */ L'\x00A3', /* pound sign */
	/* $9D */ L'\x00D8', /* O with stroke */
	/* $9E */ L'\x00D7', /* multiplication sign */
	/* $9F */ L'\x0192', /* f with hook */
	/* $A0 */ L'\x00E1', /* a with acute */
	/* $A1 */ L'\x00ED', /* i with acute */
	/* $A2 */ L'\x00F3', /* o with acute */
	/* $A3 */ L'\x00FA', /* u with acute */
	/* $A4 */ L'\x00F1', /* n with tilde */
	/* $A5 */ L'\x00D1', /* N with tilde */
	/* $A6 */ L'\x00AA', /* superscript a (feminine ordinal indicator) */
	/* $A7 */ L'\x00BA', /* superscript o (masculine ordinal indicator) */
	/* $A8 */ L'\x00BF', /* upside-down question mark */
	/* $A9 */ L'\x00AE', /* registered sign */
	/* $AA */ L'\x00AC', /* logical negation sign */
	/* $AB */ L'\x00BD', /* 1/2 fraction sign */
	/* $AC */ L'\x00BC', /* 1/4 fraction sign */
	/* $AD */ L'\x00A1', /* upside-down exclamation mark */
	/* $AE */ L'\x00AB', /* left double angle quotation mark */
	/* $AF */ L'\x00BB', /* right double angle quotation mark */
	/* $B0 */ L'\x2591', /* 25% shade block */
	/* $B1 */ L'\x2592', /* 50% shade block */
	/* $B2 */ L'\x2593', /* 75% shade block */
	/* $B3 */ L'\x2502', /* lines: vertical */
	/* $B4 */ L'\x2524', /* lines: vertical + left */
	/* $B5 */ L'\x00C1', /* A with acute */
	/* $B6 */ L'\x00C2', /* A with circumflex */
	/* $B7 */ L'\x00C0', /* A with grave */
	/* $B8 */ L'\x00A9', /* copyright sign */
	/* $B9 */ L'\x2563', /* lines: 2x vertical + 2x left */
	/* $BA */ L'\x2551', /* lines: 2x vertical */
	/* $BB */ L'\x2557', /* lines: 2x down + 2x left */
	/* $BC */ L'\x255D', /* lines: 2x up + 2x left */
	/* $BD */ L'\x00A2', /* cent sign */
	/* $BE */ L'\x00A5', /* yen sign */
	/* $BF */ L'\x2510', /* lines: down + left */
	/* $C0 */ L'\x2514', /* lines: up + right */
	/* $C1 */ L'\x2534', /* lines: up + horizontal */
	/* $C2 */ L'\x252C', /* lines: down + horizontal */
	/* $C3 */ L'\x251C', /* lines: vertical + right */
	/* $C4 */ L'\x2500', /* lines: horizontal */
	/* $C5 */ L'\x253C', /* lines: vertical + horizontal */
	/* $C6 */ L'\x00E3', /* a with tilde */
	/* $C7 */ L'\x00C3', /* A with tilde */
	/* $C8 */ L'\x255A', /* lines: 2x up + 2x right */
	/* $C9 */ L'\x2554', /* lines: 2x down + 2x right */
	/* $CA */ L'\x2569', /* lines: 2x up + 2x horizontal */
	/* $CB */ L'\x2566', /* lines: 2x down + 2x horizontal */
	/* $CC */ L'\x2560', /* lines: 2x vertical + 2x right */
	/* $CD */ L'\x2550', /* lines: 2x horizontal */
	/* $CE */ L'\x256C', /* lines: 2x vertical + 2x horizontal */
	/* $CF */ L'\x00A4', /* currency sign */
	/* $D0 */ L'\x00F0', /* lowercase eth */
	/* $D1 */ L'\x00D0', /* uppercase eth */
	/* $D2 */ L'\x00CA', /* E with circumflex */
	/* $D3 */ L'\x00CB', /* E with diaeresis */
	/* $D4 */ L'\x00C8', /* E with grave */
	/* $D5 */ L'\x0131', /* dotless i */
	/* $D6 */ L'\x00CD', /* I with acute */
	/* $D7 */ L'\x00CE', /* I with circumflex */
	/* $D8 */ L'\x00CF', /* I with diaeresis */
	/* $D9 */ L'\x2518', /* lines: up + left */
	/* $DA */ L'\x250C', /* lines: down + right */
	/* $DB */ L'\x2588', /* full block */
	/* $DC */ L'\x2584', /* lower half block */
	/* $DD */ L'\x00A6', /* broken bar */
	/* $DE */ L'\x00CC', /* I with acute */
	/* $DF */ L'\x2580', /* upper half block */
	/* $E0 */ L'\x00D3', /* O with acute */
	/* $E1 */ L'\x00DF', /* eszett, alt lowercase beta */
	/* $E2 */ L'\x00D4', /* O with circumflex */
	/* $E3 */ L'\x00D2', /* O with grave */
	/* $E4 */ L'\x00F5', /* o with tilde */
	/* $E5 */ L'\x00D5', /* O with tilde */
	/* $E6 */ L'\x03BC', /* lowercase mu (micro sign) */
	/* $E7 */ L'\x00FE', /* lowercase thorn */
	/* $E8 */ L'\x00DE', /* uppercase thorn */
	/* $E9 */ L'\x00DA', /* U with acute */
	/* $EA */ L'\x00DB', /* U with circumflex */
	/* $EB */ L'\x00D9', /* U with grave */
	/* $EC */ L'\x00FD', /* y with acute */
	/* $ED */ L'\x00DD', /* Y with acute */
	/* $EE */ L'\x00AF', /* freestanding macron */
	/* $EF */ L'\x00B4', /* freestanding acute */
	/* $F0 */ L'\x00AD', /* soft hyphen */
	/* $F1 */ L'\x00B1', /* plus-minus sign */
	/* $F2 */ L'\x2017', /* freestanding double underline */
	/* $F3 */ L'\x00BE', /* 3/4 fraction sign */
	/* $F4 */ L'\x00B6', /* pilcrow sign */
	/* $F5 */ L'\x00A7', /* section sign */
	/* $F6 */ L'\x00F7', /* division sign */
	/* $F7 */ L'\x00B8', /* freestanding cedilla */
	/* $F8 */ L'\x00B0', /* degree sign */
	/* $F9 */ L'\x00A8', /* freetanding diaeresis */
	/* $FA */ L'\x00B7', /* middle dot / interpunct */
	/* $FB */ L'\x00B9', /* superscript 1 */
	/* $FC */ L'\x00B3', /* superscript 3 */
	/* $FD */ L'\x00B2', /* superscript 2 */
	/* $FE */ L'\x25A0', /* small solid square */
	/* $FF */ L'\x00A0'  /* non-breaking space */
};

const wchar_t UC_TRANSTABLE_IBM_C0_REP [33] =
{
	/* $00 */ L'\x0000', /* null */
	/* $01 */ L'\x263A', /* smiley face with background colour */
	/* $02 */ L'\x263B', /* smiley face with foreground colour */
	/* $03 */ L'\x2665', /* heart suit */
	/* $04 */ L'\x2666', /* diamond suit */
	/* $05 */ L'\x2663', /* club suit */
	/* $06 */ L'\x2660', /* spade suit */
	/* $07 */ L'\x2022', /* bullet */
	/* $08 */ L'\x25D8', /* bullet with inverted colours */
	/* $09 */ L'\x25CB', /* hollow circle */
	/* $0A */ L'\x25D9', /* hollow circle with inverted colours */
	/* $0B */ L'\x2642', /* male symbol */
	/* $0C */ L'\x2640', /* female symbol */
	/* $0D */ L'\x266A', /* eighth note, alt sixteenth note */
	/* $0E */ L'\x266B', /* two connected eighth notes, alt- whatever */
	/* $0F */ L'\x263C', /* sun symbol */
	/* $10 */ L'\x25BA', /* right pointing triangle (should be 25B6?) */
	/* $11 */ L'\x25C4', /* left pointing triangle (should be 25C0?) */
	/* $12 */ L'\x2195', /* up-down pointing arrow */
	/* $13 */ L'\x203C', /* double exclamation mark */
	/* $14 */ L'\x00B6', /* pilcrow sign */
	/* $15 */ L'\x00A7', /* section sign */
	/* $16 */ L'\x25AC', /* solid rectangle */
	/* $17 */ L'\x21A8', /* up-down pointing arrow with base */
	/* $18 */ L'\x2191', /* up pointing arrow */
	/* $19 */ L'\x2193', /* down pointing arrow */
	/* $1A */ L'\x2192', /* right pointing arrow */
	/* $1B */ L'\x2190', /* left pointing arrow  */
	/* $1C */ L'\x221F', /* right angle */
	/* $1D */ L'\x2194', /* left-right pointing arrow */
	/* $1E */ L'\x25B2', /* up pointing triangle */
	/* $1F */ L'\x25BC', /* down pointing triangle */

	/* $7F */ L'\x2302'  /* house symbol */
};

const wchar_t UC_TRANSTABLE_1252_UPPER [32] =
{
	/* $80 */ L'\x20AC', /* euro sign */
	/* $81 */ L'\xFFFD',
	/* $82 */ L'\x201A', /* single low-9 quotation mark */
	/* $83 */ L'\x0192', /* f with hook */
	/* $84 */ L'\x201E', /* double low-9 quotation mark */
	/* $85 */ L'\x2026', /* ellipsis */
	/* $86 */ L'\x2020', /* dagger */
	/* $87 */ L'\x2021', /* double dagger */
	/* $88 */ L'\x02C6', /* freestanding small circumflex */
	/* $89 */ L'\x2030', /* per mille sign */
	/* $8A */ L'\x0160', /* S with caron */
	/* $8B */ L'\x2039', /* left single angle quotation mark */
	/* $8C */ L'\x0152', /* OE ligature */
	/* $8D */ L'\xFFFD',
	/* $8E */ L'\x017D', /* Z with caron */
	/* $8F */ L'\xFFFD',
	/* $90 */ L'\xFFFD',
	/* $91 */ L'\x2018', /* left single quotation mark */
	/* $92 */ L'\x2019', /* right single quotation mark */
	/* $93 */ L'\x201C', /* left double quotation mark */
	/* $94 */ L'\x201D', /* right double quotation mark */
	/* $95 */ L'\x2022', /* bullet */
	/* $96 */ L'\x2013', /* en dash */
	/* $97 */ L'\x2014', /* em dash */
	/* $98 */ L'\x02DC', /* freestanding small tilde */
	/* $99 */ L'\x2122', /* trademark sign */
	/* $9A */ L'\x0161', /* s with caron */
	/* $9B */ L'\x203A', /* right single angle quotation mark */
	/* $9C */ L'\x0153', /* oe ligature */
	/* $9D */ L'\xFFFD',
	/* $9E */ L'\x017E', /* z with caron */
	/* $9F */ L'\x0178'  /* Y with diaeresis */
};

const wchar_t UC_EURO = L'\x20AC'; /* euro sign */
