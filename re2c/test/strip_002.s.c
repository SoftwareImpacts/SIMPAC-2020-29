/* Generated by re2c */
#line 1 "strip_002.s.re"
/* re2c lesson 002_strip_comments, strip_002.s, (c) M. Boerger 2006 - 2007 */

#line 31 "strip_002.s.re"


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define YYMAXFILL 2

#define	BSIZE	128

#if BSIZE < YYMAXFILL
# error BSIZE must be greater YYMAXFILL
#endif

#define	YYCTYPE		unsigned char
#define	YYCURSOR	s.cur
#define	YYLIMIT		s.lim
#define YYMARKER	s.mrk
#define	YYFILL(n)	{ if ((res = fill(&s, n)) >= 0) break; }

typedef struct Scanner
{
	FILE			*fp;
	unsigned char	*cur, *tok, *lim, *eof, *mrk;
	unsigned char 	buffer[BSIZE];
} Scanner;

int fill(Scanner *s, int len)
{
	if (!len)
	{
		s->cur = s->tok = s->lim = s->mrk = s->buffer;
		s->eof = 0;
	}
	if (!s->eof)
	{
		int got, cnt = s->tok - s->buffer;

		if (cnt > 0)
		{
			memcpy(s->buffer, s->tok, s->lim - s->tok);
			s->tok -= cnt;
			s->cur -= cnt;
			s->lim -= cnt;
			s->mrk -= cnt;
		}
		cnt = BSIZE - cnt;
		if ((got = fread(s->lim, 1, cnt, s->fp)) != cnt)
		{
			s->eof = &s->lim[got];
		}
		s->lim += got;
	}
	else if (s->cur + len > s->eof)
	{
		return 0; /* not enough input data */
	}
	return -1;
}

void echo(Scanner *s)
{
	fwrite(s->tok, 1, s->cur - s->tok, stdout);
}

int scan(FILE *fp)
{
	int  res = 0;
    Scanner s;

	if (!fp)
	{
		return 1; /* no file was opened */
	}

    s.fp = fp;
	
	fill(&s, 0);

	for(;;)
	{
		s.tok = s.cur;

#line 90 "strip_002.s.c"
		{
			YYCTYPE yych;
			if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
			yych = *YYCURSOR;
			if (yych == '/') goto yy4;
			++YYCURSOR;
yy3:
#line 121 "strip_002.s.re"
			{ fputc(*s.tok, stdout); continue; }
#line 100 "strip_002.s.c"
yy4:
			yych = *++YYCURSOR;
			if (yych == '*') goto yy5;
			if (yych == '/') goto yy7;
			goto yy3;
yy5:
			++YYCURSOR;
#line 120 "strip_002.s.re"
			{ goto comment; }
#line 110 "strip_002.s.c"
yy7:
			++YYCURSOR;
#line 119 "strip_002.s.re"
			{ goto cppcomment; }
#line 115 "strip_002.s.c"
		}
#line 122 "strip_002.s.re"

comment:
		s.tok = s.cur;

#line 122 "strip_002.s.c"
		{
			YYCTYPE yych;
			if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
			yych = *YYCURSOR;
			if (yych == '*') goto yy13;
			++YYCURSOR;
yy12:
#line 127 "strip_002.s.re"
			{ goto comment; }
#line 132 "strip_002.s.c"
yy13:
			yych = *++YYCURSOR;
			if (yych != '/') goto yy12;
			++YYCURSOR;
#line 126 "strip_002.s.re"
			{ goto commentws; }
#line 139 "strip_002.s.c"
		}
#line 128 "strip_002.s.re"

commentws:
		s.tok = s.cur;

#line 146 "strip_002.s.c"
		{
			YYCTYPE yych;
			if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
			yych = *YYCURSOR;
			if (yych <= '\f') {
				if (yych <= 0x08) goto yy18;
				if (yych <= '\t') goto yy20;
				if (yych <= '\n') goto yy22;
			} else {
				if (yych <= '\r') goto yy24;
				if (yych == ' ') goto yy20;
			}
yy18:
			++YYCURSOR;
#line 134 "strip_002.s.re"
			{ echo(&s); continue; }
#line 163 "strip_002.s.c"
yy20:
			++YYCURSOR;
yy21:
#line 133 "strip_002.s.re"
			{ goto commentws; }
#line 169 "strip_002.s.c"
yy22:
			++YYCURSOR;
#line 132 "strip_002.s.re"
			{ echo(&s); continue; }
#line 174 "strip_002.s.c"
yy24:
			++YYCURSOR;
			if ((yych = *YYCURSOR) == '\n') goto yy22;
			goto yy21;
		}
#line 135 "strip_002.s.re"

cppcomment:
		s.tok = s.cur;

#line 185 "strip_002.s.c"
		{
			YYCTYPE yych;
			if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
			yych = *YYCURSOR;
			if (yych == '\n') goto yy29;
			if (yych == '\r') goto yy31;
			++YYCURSOR;
yy28:
#line 140 "strip_002.s.re"
			{ goto cppcomment; }
#line 196 "strip_002.s.c"
yy29:
			++YYCURSOR;
#line 139 "strip_002.s.re"
			{ echo(&s); continue; }
#line 201 "strip_002.s.c"
yy31:
			++YYCURSOR;
			if ((yych = *YYCURSOR) == '\n') goto yy29;
			goto yy28;
		}
#line 141 "strip_002.s.re"

	}

	if (fp != stdin)
	{
		fclose(fp); /* close only if not stdin */
	}
	return res; /* return result */
}

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		return scan(!strcmp(argv[1], "-") ? stdin : fopen(argv[1], "r"));
	}
	else
	{
		fprintf(stderr, "%s <expr>\n", argv[0]);
		return 1;
	}
}
