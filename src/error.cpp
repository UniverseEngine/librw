#include <stdio.h>
#include <stdarg.h>

#include "rwbase.h"
#include "rwerror.h"

namespace rw {

static Error error;

void
setError(Error *e)
{
	error = *e;
}

Error*
getError(Error *e)
{
	*e = error;
	error.plugin = 0;
	error.code = 0;
	return e;
}

#define ECODE(c, s) s

const char *errstrs[] = {
	"No error",
#include "base.err"
};

#undef ECODE

char*
dbgsprint(uint32 code, ...)
{
	va_list ap;
	static char strbuf[512];

	if(code & 0x80000000)
		code &= ~0x80000000;
	va_start(ap, code);

#ifdef _MSC_VER
	vsprintf_s(strbuf, errstrs[code], ap);
#else
	vsprintf(strbuf, errstrs[code], ap);
#endif
	
	va_end(ap);
	return strbuf;
}

}
