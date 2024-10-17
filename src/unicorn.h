/*
 * unicorn
 * version 0.002
 * 2024-06-11
 */


#ifndef UC_H_UNICORN
#define UC_H_UNICORN


#include <stddef.h>
#include <limits.h>

#if __STDC_VERSION__ >= 199901L
#include <stdint.h>
#endif


#if !defined(WCHAR_MAX)
#if defined(__WCHAR_MAX)
#define WCHAR_MAX __WCHAR_MAX
#elif defined(__WCHAR_MAX__)
#define WCHAR_MAX __WCHAR_MAX__
#else
#error "UNICORN: could not detect the size of a wide character."
#endif
#endif

#if WCHAR_MAX < 0xFFFF
#error "UNICORN: a wide character must have a maximum value of at least 0xFFFF."
#elif WCHAR_MAX < 0x10FFFF
#define UC_UTF16 1 /* UTF-16 */
#else
#define UC_UTF16 0 /* UTF-32 */
#endif


typedef signed long int UC_wint_t;

#define UC_WINT_MAX LONG_MAX
#define UC_WINT_MIN LONG_MIN

#define UC_WEOF (-1)

#define UC_MB_LEN_MAX 4
#define UC_MB_CUR_MAX UC_MB_LEN_MAX


size_t UC_wcslen(const wchar_t* s);
size_t UC_wcsnlen(const wchar_t* s, size_t n);

wchar_t* UC_wcscpy(wchar_t* dest, const wchar_t* src);
wchar_t* UC_wcsncpy(wchar_t* dest, const wchar_t* src, size_t n);
wchar_t* UC_wcpcpy(wchar_t* dest, const wchar_t* src);
wchar_t* UC_wcpncpy(wchar_t* dest, const wchar_t* src, size_t n);

wchar_t* UC_wcscat(wchar_t* dest, const wchar_t* src);
wchar_t* UC_wcsncat(wchar_t* dest, const wchar_t* src, size_t n);

int UC_wcscmp(const wchar_t* s1, const wchar_t* s2);
int UC_wcsncmp(const wchar_t* s1, const wchar_t* s2, size_t n);

wchar_t* UC_wcschr(const wchar_t* s, wchar_t c);
wchar_t* UC_wcsrchr(const wchar_t* s, wchar_t c);

wchar_t* UC_wcsstr(const wchar_t* s, const wchar_t* kernel);

size_t UC_wcsspn(const wchar_t* s, const wchar_t* accept);
size_t UC_wcscspn(const wchar_t* s, const wchar_t* reject);

wchar_t* UC_wcspbrk(const wchar_t* s, const wchar_t* accept);

wchar_t* UC_wcstok(wchar_t* s, const wchar_t* delim, wchar_t** pnext);

wchar_t* UC_wmemset(wchar_t* s, wchar_t c, size_t n);

wchar_t* UC_wmemcpy(wchar_t* dest, const wchar_t* src, size_t n);
wchar_t* UC_wmemmove(wchar_t* dest, const wchar_t* src, size_t n);

int UC_wmemcmp(const wchar_t* s1, const wchar_t* s2, size_t n);

wchar_t* UC_wmemchr(const wchar_t* s, wchar_t c, size_t n);

size_t UC_wcstombs(char* dest, const wchar_t* src, size_t n);
size_t UC_mbstowcs(wchar_t* dest, const char* src, size_t n);

int UC_wctomb(char* s, wchar_t c);
int UC_wcstomb(char* s, const wchar_t* pc);
int UC_mbtowc(wchar_t* pc, const char* s, size_t n);

/* in UTF-8, these two functions are completely useless and extremely trivial.
   but whatever, I've still implemented them anyway.                          */
int UC_wctob(UC_wint_t c);
UC_wint_t UC_btowc(int c);

int UC_mblen(const char* s, size_t n);


#endif /* UC_H_UNICORN */
