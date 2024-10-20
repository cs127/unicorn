/*
 * unicorn
 * version 0.003
 * 2024-10-17
 */


#include "unicorn.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>


typedef enum {UC_false, UC_true} UC_bool;


#define UC_SIZE_PLACEHOLDER ((size_t)(-1))

#define UC_MAX_CODEPOINT 0x10FFFF

#define UC_MAX_1BYTE 0x007F
#define UC_MAX_2BYTE 0x07FF
#define UC_MAX_3BYTE 0xFFFF
#define UC_MAX_4BYTE UC_MAX_CODEPOINT

#define UC_SURMASK 0x03FF
#define UC_HIGHSUR 0xD800
#define UC_LOWSUR  0xDC00

#define UC_IS_IN_RANGE(c) ((c) >= 0 && (c) <= UC_MAX_CODEPOINT)

#define UC_SUR_OFFSET 0x10000
#define UC_IS_BMP(c) ((c) <= 0xFFFF)

#define UC_IS_HIGHSUR(c) ((c) >= 0xD800 && (c) < 0xDC00)
#define UC_IS_LOWSUR(c)  ((c) >= 0xDC00 && (c) < 0xE000)

#define UC_IS_SUR(c) (UC_IS_HIGHSUR(c) || UC_IS_LOWSUR(c))

#define UC_IS_OVERLONG(c, l)        \
((l) > 1 && (c) <= UC_MAX_1BYTE) || \
((l) > 2 && (c) <= UC_MAX_2BYTE) || \
((l) > 3 && (c) <= UC_MAX_3BYTE)

#define UC_TOP1 0x80
#define UC_TOP2 0xC0
#define UC_TOP3 0xE0
#define UC_TOP4 0xF0
#define UC_TOP5 0xF8

#define UC_BOTTOM3 0x07
#define UC_BOTTOM4 0x0F
#define UC_BOTTOM5 0x1F
#define UC_BOTTOM6 0x3F

#define UC_IS_1BYTE(b) (!((b) & UC_TOP1))
#define UC_IS_2BYTE(b) (((b) & UC_TOP3) == UC_TOP2)
#define UC_IS_3BYTE(b) (((b) & UC_TOP4) == UC_TOP3)
#define UC_IS_4BYTE(b) (((b) & UC_TOP5) == UC_TOP4)

#define UC_IS_CONT(b)  (((b) & UC_TOP2) == UC_TOP1)


size_t UC_wcslen(const wchar_t* s)
{
	size_t i = 0;

	while (s[i]) i++;

	return i;
}

size_t UC_wcsnlen(const wchar_t* s, size_t n)
{
	size_t i = 0;

	while (s[i] && i < n) i++;

	return i;
}

wchar_t* UC_wcscpy(wchar_t* dest, const wchar_t* src)
{
	size_t i;

	for (i = 0; src[i]; i++) dest[i] = src[i];

	/* wcscpy/wcpcpy must null-terminate the destination. */
	dest[i] = L'\0';

	return dest;
}

wchar_t* UC_wcsncpy(wchar_t* dest, const wchar_t* src, size_t n)
{
	size_t i;
	UC_bool end = UC_false;

	for (i = 0; i < n; i++)
	{
		if (!end)
		{
			/* we're not past the end of the source yet, so
			   the corresponding character is copied normally.

			   note that we might be exactly at the end,
			   but in that case, the source character is a null,
			   so it won't make a difference.                    */
			dest[i] = src[i];

			/* check if we are at the end.
			   if so, the remaining destination characters will
			   be filled with nulls.                            */
			if (!dest[i]) end = UC_true;
		}
		else
		{
			/* we are past the end of the source.
			   fill the destination with a null.  */
			dest[i] = L'\0';
		}
	}

	/* don't do anything else here.
	   if n is small enough that causes the source to end prematurely
	   (without null-termination), the destination must be left as is
	   after the copying (i.e. not null-terminated).                  */

	return dest;
}

wchar_t* UC_wcpcpy(wchar_t* dest, const wchar_t* src)
{
	/* almost identical to wcscpy. only the return value is different. */

	size_t i;

	for (i = 0; src[i]; i++) dest[i] = src[i];

	/* wcscpy/wcpcpy must null-terminate the destination. */
	dest[i] = L'\0';

	return &dest[i];
}

wchar_t* UC_wcpncpy(wchar_t* dest, const wchar_t* src, size_t n)
{
	/* almost identical to wcsncpy. only the return value is different. */

	size_t i,
	       endpos = n;
	UC_bool end = UC_false;

	for (i = 0; i < n; i++)
	{
		if (!end)
		{
			/* we're not past the end of the source yet, so
			   the corresponding character is copied normally.

			   note that we might be exactly at the end,
			   but in that case, the source character is a null,
			   so it won't make a difference.                    */
			dest[i] = src[i];

			/* check if we are at the end.
			   if so, the remaining destination characters will
			   be filled with nulls.                            */
			if (!dest[i])
			{
				end = UC_true;
				endpos = i + 1;
			}
		}
		else
		{
			/* we are past the end of the source.
			   fill the destination with a null.  */
			dest[i] = L'\0';
		}
	}

	/* don't do anything else here.
	   if n is small enough that causes the source to end prematurely
	   (without null-termination), the destination must be left as is
	   after the copying (i.e. not null-terminated).                  */

	return &dest[endpos];
}

wchar_t* UC_wcscat(wchar_t* dest, const wchar_t* src)
{
	size_t i,
	       tail = 0;

	while (dest[tail]) tail++;

	for (i = 0; src[i]; i++) dest[tail + i] = src[i];
	dest[tail + i] = L'\0';

	return dest;
}

wchar_t* UC_wcsncat(wchar_t* dest, const wchar_t* src, size_t n)
{
	size_t i,
	       tail = 0;

	while (dest[tail]) tail++;

	for (i = 0; src[i] && i < n; i++) dest[tail + i] = src[i];
	dest[tail + i] = L'\0';

	return dest;
}

int UC_wcscmp(const wchar_t* s1, const wchar_t* s2)
{
	size_t i;

	for (i = 0; s1[i] || s2[i]; i++)
	{
		if (s1[i] != s2[i]) return (int)(s1[i]) - (int)(s2[i]);
	}

	return 0;
}

int UC_wcsncmp(const wchar_t* s1, const wchar_t* s2, size_t n)
{
	size_t i;

	for (i = 0; i < n && (s1[i] || s2[i]); i++)
	{
		if (s1[i] != s2[i]) return (int)(s1[i]) - (int)(s2[i]);
	}

	return 0;
}

wchar_t* UC_wcschr(const wchar_t* s, wchar_t c)
{
	size_t i;

	for (i = 0; s[i]; i++)
	{
		if (s[i] == c) return &((wchar_t*)s)[i];
	}

	return NULL;
}

wchar_t* UC_wcsrchr(const wchar_t* s, wchar_t c)
{
	size_t i,
	       last = UC_SIZE_PLACEHOLDER;

	for (i = 0; s[i]; i++)
	{
		if (s[i] == c) last = i;
	}

	return (last != UC_SIZE_PLACEHOLDER) ? &((wchar_t*)s)[last] : NULL;
}

wchar_t* UC_wcsstr(const wchar_t* s, const wchar_t* kernel)
{
	/* could probably use some optimization. */

	size_t i,
	       klen;

	if (!*kernel) return (wchar_t*)s;

	klen = UC_wcslen(kernel);

	for (i = 0; s[i] && s[i + klen - 1]; i++)
	{
		if (!UC_wcsncmp(&s[i], kernel, klen)) return &((wchar_t*)s)[i];
	}

	return NULL;
}

size_t UC_wcsspn(const wchar_t* s, const wchar_t* accept)
{
	size_t i;

	for (i = 0; s[i]; i++)
	{
		if (!UC_wcschr(accept, s[i])) return i;
	}

	return i;
}

size_t UC_wcscspn(const wchar_t* s, const wchar_t* reject)
{
	size_t i;

	for (i = 0; s[i]; i++)
	{
		if (UC_wcschr(reject, s[i])) return i;
	}

	return i;
}

wchar_t* UC_wcspbrk(const wchar_t* s, const wchar_t* accept)
{
	size_t i;

	for (i = 0; s[i]; i++)
	{
		if (UC_wcschr(accept, s[i])) return &((wchar_t*)s)[i];
	}

	return NULL;
}

wchar_t* UC_wcstok(wchar_t* s, const wchar_t* delim, wchar_t** pnext)
{
	/* this code is somewhat based on glibc's strtok_r implementation. */

	size_t tlen;

	if (!s) s = *pnext;

	/* skip leading delimiters. */
	s = &s[UC_wcsspn(s, delim)];

	/* check if the token is empty.
	   (i.e. the end of the string has been reached. there is no token.) */
	if (!*s)
	{
		*pnext = s;
		return NULL;
	}

	/* find the end of the token. */
	tlen = UC_wcscspn(s, delim);

	/* check if the end of the token is the end of the string. */
	if (!s[tlen])
	{
		*pnext = &s[tlen];
		return s;
	}

	/* null-terminate the token. */
	s[tlen] = L'\0';

	/* mark the start of the next token. */
	*pnext = &s[tlen + 1];

	return s;
}

wchar_t* UC_wmemset(wchar_t* s, wchar_t c, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++) s[i] = c;

	return s;
}

wchar_t* UC_wmemcpy(wchar_t* dest, const wchar_t* src, size_t n)
{
	return memcpy(dest, src, n * sizeof(wchar_t));
}

wchar_t* UC_wmemmove(wchar_t* dest, const wchar_t* src, size_t n)
{
	return memmove(dest, src, n * sizeof(wchar_t));
}

int UC_wmemcmp(const wchar_t* s1, const wchar_t* s2, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
	{
		if (s1[i] != s2[i]) return (int)(s1[i]) - (int)(s2[i]);
	}

	return 0;
}

wchar_t* UC_wmemchr(const wchar_t* s, wchar_t c, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
	{
		if (s[i] == c) return &((wchar_t*)s)[i];
	}

	return NULL;
}

size_t UC_wcstombs(char* dest, const wchar_t* src, size_t n)
{
	size_t isrc = 0,
	       idest,
	       trail = 0;
	unsigned long int csrc;

	for (idest = 0; idest < n || !dest; idest++)
	{
		if (!trail)
		{
			/* start of a character. */

			if (!UC_IS_IN_RANGE(src[isrc]))
			{
				/* codepoint out of valid range. */
				return -1;
			}
#if UC_UTF16 /* UTF-16 */
			if (!UC_IS_SUR(src[isrc]))
			{
				/* regular character. */
				csrc = src[isrc++];
			}
			else if
			(
				UC_IS_HIGHSUR(src[isrc]) &&
				UC_IS_LOWSUR(src[isrc + 1])
			)
			{
				/* surrogate pair. */
				csrc = 0;
				csrc |= (src[isrc++] & UC_SURMASK) << 10;
				csrc |= (src[isrc++] & UC_SURMASK) << 0;
				csrc += UC_SUR_OFFSET;
			}
			else
			{
				/* invalid surrogate sequence. */
				return -1;
			}
#else        /* UTF-32 */
			if (!UC_IS_SUR(src[isrc]))
			{
				csrc = src[isrc++];
			}
			else
			{
				/* UTF-16 surrogate (invalid in UTF-32). */
				return -1;
			}
#endif
			if (!csrc)
			{
				/* null character (end of string). */
				if (dest) dest[idest] = '\0';
				return idest;
			}
			else if (csrc <= UC_MAX_1BYTE)
			{
				/* 1-byte (ASCII) character. */
				trail = 0;
				if (dest) dest[idest] = csrc;
			}
			else if (csrc <= UC_MAX_2BYTE)
			{
				/* first byte of a 2-byte character. */
				trail = 1;
				if (dest && idest + trail >= n) return idest;
				if (dest) dest[idest] = (csrc >> 6) | UC_TOP2;
			}
			else if (csrc <= UC_MAX_3BYTE)
			{
				/* first byte of a 3-byte character. */
				trail = 2;
				if (dest && idest + trail >= n) return idest;
				if (dest) dest[idest] = (csrc >> 12) | UC_TOP3;
			}
			else
			{
				/* first byte of a 4-byte (non-BMP) character.
				   in UTF-16, this case will only occur with
				   surrogate pairs.                           */
				trail = 3;
				if (dest && idest + trail >= n) return idest;
				if (dest) dest[idest] = (csrc >> 18) | UC_TOP4;
			}
		}
		else
		{
			/* continuation of a 2/3/4-byte character. */
			trail--;
			if (dest) dest[idest] =
			((csrc >> (6 * trail)) & UC_BOTTOM6) | UC_TOP1;
		}
	}

	return idest;
}

size_t UC_mbstowcs(wchar_t* dest, const char* src, size_t n)
{
	size_t isrc = 0,
	       idest,
	       trail,
	       clen;
	UC_bool lowsur = UC_false; /* will always remain false in UTF-32. */
	unsigned long int csrc;

	for (idest = 0; idest < n || !dest; idest++)
	{
		if (!lowsur)
		{
			/* regular character or high surrogate.
			   surrogates are only valid in UTF-16. */

			/* read the first byte of the character. */

			if (UC_IS_1BYTE(src[isrc]))
			{
				/* 1-byte (ASCII) character. */
				trail = 0;
				csrc = src[isrc++];
			}
			else if (UC_IS_2BYTE(src[isrc]))
			{
				/* first byte of a 2-byte character. */
				trail = 1;
				csrc = (src[isrc++] & UC_BOTTOM5) << 6;
			}
			else if (UC_IS_3BYTE(src[isrc]))
			{
				/* first byte of a 3-byte character.
				   this might be a UTF-16 surrogate,
				   which is invalid in UTF-8.        */
				trail = 2;
				csrc = (src[isrc++] & UC_BOTTOM4) << 12;
			}
			else if (UC_IS_4BYTE(src[isrc]))
			{
				/* first byte of a 4-byte (non-BMP) character.
				   this will require checking later:
				   if the codepoint is 0x10FFFF or lower,
				   it requires a surrogate pair in UTF-16.
				   otherwise, it is invalid entirely.         */
				trail = 3;
				csrc = (src[isrc++] & UC_BOTTOM3) << 18;
			}
			else
			{
				/* unexpected byte, which is either:
				   * continuation byte
				     (cannot be at the start of a character),
				   or
				   * first byte of a 5/6/7/8-byte character
				     (nonstandard).                           */
				return -1;
			}

			clen = 1 + trail;

			/* read the remaining bytes. */

			while (trail)
			{
				if (!UC_IS_CONT(src[isrc]))
				{
					/* unexpected byte
					   (expected a continuation byte). */
					return -1;
				}

				csrc |=
				(src[isrc++] & UC_BOTTOM6) << (6 * (--trail));
			}

			if (UC_IS_OVERLONG(csrc, clen))
			{
				/* overlong character
				   (encoded in more bytes than necessary). */
				return -1;
			}

			if (UC_IS_SUR(csrc))
			{
				/* UTF-16 surrogate (invalid in UTF-8). */
				return -1;
			}
			else if (!UC_IS_IN_RANGE(csrc))
			{
				/* codepoint out of valid range. */
				return -1;
			}

			if (!csrc)
			{
				/* null character (end of string). */
				if (dest) dest[idest] = L'\0';
				return idest;
			}
#if UC_UTF16 /* UTF-16 */
			if (UC_IS_BMP(csrc))
			{
				/* BMP character.
				   can be written normally. */
				if (dest) dest[idest] = csrc;
			}
			else
			{
				/* non-BMP character.
				   requires a surrogate pair. */

				/* write the high surrogate now. */
				if (dest) dest[idest] =
				((csrc - UC_SUR_OFFSET) >> 10) | UC_HIGHSUR;

				/* write the low surrogate on the next turn. */
				lowsur = UC_true;
			}
#else        /* UTF-32 */
			if (dest) dest[idest] = csrc;
#endif
		}
		else
		{
			/* this block of code can only be accessed in UTF-16. */

			/* low surrogate. */
			if (dest) dest[idest] =
			((csrc - UC_SUR_OFFSET) & UC_SURMASK) | UC_LOWSUR;

			/* reset the behaviour for the next turn. */
			lowsur = UC_false;
		}
	}

	return idest;
}

static int UC_wctomb_(char* mb, unsigned long int c)
{
	size_t i = 0,
	       trail;

	if (c <= UC_MAX_1BYTE)
	{
		/* 1-byte (ASCII) character. */
		trail = 0;
		mb[i++] = c;
	}
	else if (c <= UC_MAX_2BYTE)
	{
		/* first byte of a 2-byte character. */
		trail = 1;
		mb[i++] = (c >> 6) | UC_TOP2;
	}
	else if (c <= UC_MAX_3BYTE)
	{
		/* first byte of a 3-byte character. */
		trail = 2;
		mb[i++] = (c >> 12) | UC_TOP3;
	}
	else
	{
		/* first byte of a 4-byte (non-BMP) character.
		   this block of code is only accessible in UTF-32,
		   since a non-BMP character cannot be represented
		   by a single wchar_t in UTF-16.                   */
		trail = 3;
		mb[i++] = (c >> 18) | UC_TOP4;
	}

	while (trail)
	{
		mb[i++] = ((c >> (6 * (--trail))) & UC_BOTTOM6) | UC_TOP1;
	}

	return i;
}

int UC_wctomb(char* mb, wchar_t c)
{
	if (!mb)
	{
		/* shift state reset has been requested.
		   no further action is needed other than returning 0,
		   because UTF-8 is stateless.                         */
		return 0;
	}

	if (!UC_IS_IN_RANGE(c))
	{
		/* codepoint out of valid range. */
		return -1;
	}
	if (UC_IS_SUR(c))
	{
		/* UTF-16 surrogate
		   (meaningless as a single character, even in UTF-16). */
		return -1;
	}

	return UC_wctomb_(mb, c);
}

int UC_wcstomb(char* mb, const wchar_t* pc)
{
	unsigned long int c;

	if (!mb)
	{
		/* shift state reset has been requested.
		   no further action is needed other than returning 0,
		   because UTF-8 is stateless.                         */
		return 0;
	}

	if (!UC_IS_IN_RANGE(*pc))
	{
		/* codepoint out of valid range. */
		return -1;
	}
#if UC_UTF16 /* UTF-16 */
	if (!UC_IS_SUR(*pc))
	{
		/* regular character. */
		c = *pc;
	}
	else if (UC_IS_HIGHSUR(pc[0]) && UC_IS_LOWSUR(pc[1]))
	{
		/* surrogate pair. */
		c = 0;
		c |= (pc[0] & UC_SURMASK) << 10;
		c |= (pc[1] & UC_SURMASK) << 0;
		c += UC_SUR_OFFSET;
	}
	else
	{
		/* invalid surrogate sequence. */
		return -1;
	}
#else        /* UTF-32 */
	if (!UC_IS_SUR(*pc))
	{
		c = *pc;
	}
	else
	{
		/* UTF-16 surrogate (invalid in UTF-32). */
		return -1;
	}
#endif

	return UC_wctomb_(mb, c);
}

static int UC_mbtowcx_(wchar_t* pc, const char* mb, size_t n, UC_bool towcs)
{
	size_t i,
	       trail,
	       clen;
	unsigned long int c;

	if (!mb)
	{
		/* shift state reset has been requested.
		   no further action is needed other than returning 0,
		   because UTF-8 is stateless.                         */
		return 0;
	}

	trail = UC_SIZE_PLACEHOLDER;

	for (i = 0; i < n || !trail; i++)
	{
		if (trail == UC_SIZE_PLACEHOLDER)
		{
			/* read the first byte of the character. */

			if (!mb[i])
			{
				/* null character. */
				return 0;
			}
			else if (UC_IS_1BYTE(mb[i]))
			{
				/* 1-byte (ASCII) character. */
				trail = 0;
				c = mb[i];
			}
			else if (UC_IS_2BYTE(mb[i]))
			{
				/* first byte of a 2-byte character. */
				trail = 1;
				c = (mb[i] & UC_BOTTOM5) << 6;
			}
			else if (UC_IS_3BYTE(mb[i]))
			{
				/* first byte of a 3-byte character.
				   this might be a UTF-16 surrogate,
				   which is invalid in UTF-8.        */
				trail = 2;
				c = (mb[i] & UC_BOTTOM4) << 12;
			}
			else if (UC_IS_4BYTE(mb[i]))
			{
				/* first byte of a 4-byte (non-BMP) character.
				   this will require checking later:
				   if the codepoint is 0x10FFFF or lower,
				   it requires a surrogate pair in UTF-16.
				   otherwise, it is invalid entirely.         */
#if UC_UTF16 /* UTF-16 */
				/* reject if called from mbtowc, since the
				   destination requires two characters for a
				   surrogate pair.                            */
				if (!towcs) return -1;
#endif
				trail = 3;
				c = (mb[i] & UC_BOTTOM3) << 18;
			}
			else
			{
				/* unexpected byte, which is either:
				   * continuation byte
				     (cannot be at the start of a character),
				   or
				   * first byte of a 5/6/7/8-byte character
				     (nonstandard).                           */
				return -1;
			}

			clen = 1 + trail;
		}
		else if (!trail)
		{
			/* the character has been fully parsed. */

			if (UC_IS_OVERLONG(c, clen))
			{
				/* overlong character
				   (encoded in more bytes than necessary). */
				return -1;
			}

			if (UC_IS_SUR(c))
			{
				/* UTF-16 surrogate (invalid in UTF-8). */
				return -1;
			}
			else if (!UC_IS_IN_RANGE(c))
			{
				/* codepoint out of valid range. */
				return -1;
			}
#if UC_UTF16 /* UTF-16 */
			if (UC_IS_BMP(c))
			{
				/* BMP character.
				   can be written normally. */
				if (pc) *pc = c;
			}
			else
			{
				/* non-BMP character.
				   requires a surrogate pair. */
				if (pc)
				{
					pc[0] =
					((c - UC_SUR_OFFSET) >> 10) |
					UC_HIGHSUR;

					pc[1] =
					((c - UC_SUR_OFFSET) & UC_SURMASK) |
					UC_LOWSUR;
				}
			}
#else        /* UTF-32 */
			if (pc) *pc = c;
#endif
			break;
		}
		else
		{
			/* parsing the continuation of a character. */

			if (!UC_IS_CONT(mb[i]))
			{
				/* unexpected byte
				   (expected a continuation byte). */
				return -1;
			}

			c |= (mb[i] & UC_BOTTOM6) << (6 * (--trail));
		}
	}

	return !trail ? i : -1;
}

int UC_mbtowc(wchar_t* pc, const char* mb, size_t n)
{
	return UC_mbtowcx_(pc, mb, n, UC_false);
}

int UC_mbtowcs(wchar_t* pc, const char* mb, size_t n)
{
	return UC_mbtowcx_(pc, mb, n, UC_true);
}

int UC_wctob(UC_wint_t c)
{
	return c >= 0x00 & c <= 0x7F ? c : EOF;
}

UC_wint_t UC_btowc(int a)
{
	return a >= 0x00 & a <= 0x7F ? a : UC_WEOF;
}

int UC_mblen(const char* mb, size_t n)
{
	size_t i,
	       trail = UC_SIZE_PLACEHOLDER,
	       clen;
	unsigned long int c;

	for (i = 0; i < n || !trail; i++)
	{
		if (trail == UC_SIZE_PLACEHOLDER)
		{
			/* read the first byte of the character. */

			if (!mb[i])
			{
				/* null character. */
				return 0;
			}
			else if (UC_IS_1BYTE(mb[i]))
			{
				/* 1-byte (ASCII) character. */
				trail = 0;
				c = mb[i];
			}
			else if (UC_IS_2BYTE(mb[i]))
			{
				/* first byte of a 2-byte character. */
				trail = 1;
				c = (mb[i] & UC_BOTTOM5) << 6;
			}
			else if (UC_IS_3BYTE(mb[i]))
			{
				/* first byte of a 3-byte character.
				   this might be a UTF-16 surrogate,
				   which is invalid in UTF-8.        */
				trail = 2;
				c = (mb[i] & UC_BOTTOM4) << 12;
			}
			else if (UC_IS_4BYTE(mb[i]))
			{
				/* first byte of a 4-byte (non-BMP) character.
				   this will require checking later:
				   if the codepoint is 0x10FFFF or lower,
				   it requires a surrogate pair in UTF-16.
				   otherwise, it is invalid entirely.         */
				trail = 3;
				c = (mb[i] & UC_BOTTOM3) << 18;
			}
			else
			{
				/* unexpected byte, which is either:
				   * continuation byte
				     (cannot be at the start of a character),
				   or
				   * first byte of a 5/6/7/8-byte character
				     (nonstandard).                           */
				return -1;
			}

			clen = 1 + trail;
		}
		else if (!trail)
		{
			/* the character has been fully parsed. */

			if (UC_IS_OVERLONG(c, clen))
			{
				/* overlong character 
				   (encoded in more bytes than necessary). */
				return -1;
			}

			if (UC_IS_SUR(c))
			{
				/* UTF-16 surrogate (invalid in UTF-8). */
				return -1;
			}
			else if (!UC_IS_IN_RANGE(c))
			{
				/* codepoint out of valid range. */
				return -1;
			}

			break;
		}
		else
		{
			/* parsing the continuation of a character. */

			if (!UC_IS_CONT(mb[i]))
			{
				/* unexpected byte
				   (expected a continuation byte). */
				return -1;
			}

			c |= (mb[i] & UC_BOTTOM6) << (6 * (--trail));
		}
	}

	return !trail ? i : -1;
}
