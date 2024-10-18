#include "ascx.h"

#include <stddef.h>
#include <string.h>


#define UC_tablecopy(dest, src, n) memcpy(dest, src, (n) * sizeof(wchar_t))


UC_wint_t UC_ascxtowc(int c, UC_trans_t t)
{
	unsigned char bc;
	wchar_t wc;
	size_t r;

	bc = c;
	r = UC_ascxstowcs(&wc, &bc, 1, t);

	return r != (size_t)(-1) ? wc : UC_WEOF;
}

size_t
UC_ascxstowcs(wchar_t* dest, const unsigned char* src, size_t n, UC_trans_t t)
{
	size_t i;
	wchar_t table [256];

	if (!dest)
	{
		/* no destination specified.
		   simply return the length of the extended-ASCII string. */
		return strlen(src);
	}

	if (t >= UC_TRANS_COUNT)
	{
		/* invalid transformation type. */
		return -1;
	}

	/* set up the transformation table: */

	/* 1. start with an identity transform. */

	for (i = 0; i < 256; i++) table[i] = i;

	/* 2. fill the C0 control codepoints with IBM dingbats if necessary. */

	switch (t)
	{
	case UC_TRANS_437_C0_REP:
	case UC_TRANS_850_C0_REP:
	case UC_TRANS_858_C0_REP:
		UC_tablecopy(&table[0x00], &UC_TRANSTABLE_IBM_C0_REP[0], 32);
		UC_tablecopy(&table[0x7F], &UC_TRANSTABLE_IBM_C0_REP[32], 1);
		break;
	}

	/* 3. fill the upper half of the codepage
	      (ignoring the small differences).   */

	switch (t)
	{
	case UC_TRANS_437_C0:
	case UC_TRANS_437_C0_REP:
		UC_tablecopy(&table[0x80], &UC_TRANSTABLE_437_UPPER[0], 128);
		break;

	case UC_TRANS_850_C0:
	case UC_TRANS_850_C0_REP:
	case UC_TRANS_858_C0:
	case UC_TRANS_858_C0_REP:
		UC_tablecopy(&table[0x80], &UC_TRANSTABLE_850_UPPER[0], 128);
		break;

	case UC_TRANS_1252:
		UC_tablecopy(&table[0x80], &UC_TRANSTABLE_1252_UPPER[0], 32);
		break;
	}

	/* 4. add the small differences (e.g. euro sign) */

	switch (t)
	{
	case UC_TRANS_858_C0:
	case UC_TRANS_858_C0_REP:
		UC_tablecopy(&table[0xD5], &UC_EURO, 1);
		break;
	}

	/* and we're done.
	   ISO-8859-1 is a simple identity transform,
	   so it skips steps 2-4.                     */

	/* do the conversion. */

	for (i = 0; i < n; i++)
	{
		if (src[i])
		{
			/* regular character. */
			dest[i] = table[src[i]];
		}
		else
		{
			/* null character (end of string). */
			dest[i] = L'\0';
			return i;
		}
	}

	return i;
}
