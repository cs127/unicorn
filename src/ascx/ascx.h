#ifndef UC_H_ASCX
#define UC_H_ASCX


#include <limits.h>
#include <stddef.h>


#ifndef UC_WINT_IMPL
#define UC_WINT_IMPL

typedef signed long int UC_wint_t;

#define UC_WINT_MAX LONG_MAX
#define UC_WINT_MIN LONG_MIN

#define UC_WEOF (-1)

#endif /* UC_WINT_IMPL */


typedef enum UC_trans
{
	UC_TRANS_437_C0,     /* w/ C0 control characters. */
	UC_TRANS_437_C0_REP, /* w/ dingbats instead of C0 control characters. */

	UC_TRANS_850_C0,     /* w/ C0 control characters. */
	UC_TRANS_850_C0_REP, /* w/ dingbats instead of C0 control characters. */

	UC_TRANS_858_C0,     /* w/ C0 control characters. */
	UC_TRANS_858_C0_REP, /* w/ dingbats instead of C0 control characters. */

	UC_TRANS_1252,

	UC_TRANS_8859_1,     /* w/ C0 and C1 control characters. */


	UC_TRANS_COUNT
}
UC_trans_t;


extern const wchar_t UC_TRANSTABLE_437_UPPER [128];
extern const wchar_t UC_TRANSTABLE_850_UPPER [128];
extern const wchar_t UC_TRANSTABLE_IBM_C0_REP [33];
extern const wchar_t UC_TRANSTABLE_1252_UPPER [32];
extern const wchar_t UC_EURO;


UC_wint_t UC_ascxtowc(int c, UC_trans_t t);

size_t
UC_ascxstowcs(wchar_t* dest, const unsigned char* src, size_t n, UC_trans_t t);


#endif /* UC_H_ASCX */
