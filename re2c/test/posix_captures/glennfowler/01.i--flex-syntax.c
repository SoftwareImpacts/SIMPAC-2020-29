/* Generated by re2c */

{
	YYCTYPE yych;
	if ((YYLIMIT - YYCURSOR) < 3) YYFILL(3);
	yych = *YYCURSOR;
	switch (yych) {
	case 'a':
		yyt1 = yyt3 = yyt4 = YYCURSOR;
		goto yy3;
	default:
		yyt2 = yyt4 = NULL;
		yyt1 = yyt3 = YYCURSOR;
		goto yy2;
	}
yy2:
	yynmatch = 4;
	yypmatch[2] = yyt1;
	yypmatch[4] = yyt3;
	yypmatch[6] = yyt4;
	yypmatch[7] = yyt2;
	yypmatch[0] = yyt1;
	yypmatch[1] = YYCURSOR;
	yypmatch[3] = yyt3;
	yypmatch[5] = YYCURSOR;
	{}
yy3:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'a':
		yyt3 = yyt4 = YYCURSOR;
		goto yy4;
	case 'b':	goto yy6;
	default:
		yyt2 = yyt4 = NULL;
		yyt3 = YYCURSOR;
		goto yy2;
	}
yy4:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'b':	goto yy6;
	default:	goto yy5;
	}
yy5:
	YYCURSOR = YYMARKER;
	yyt2 = yyt4 = NULL;
	yyt3 = YYCURSOR;
	goto yy2;
yy6:
	++YYCURSOR;
	yyt2 = YYCURSOR;
	goto yy2;
}

posix_captures/glennfowler/01.i--flex-syntax.re:5: warning: rule matches empty string [-Wmatch-empty-string]
posix_captures/glennfowler/01.i--flex-syntax.re:6: warning: rule matches empty string [-Wmatch-empty-string]
posix_captures/glennfowler/01.i--flex-syntax.re:6: warning: unreachable rule (shadowed by rule at line 5) [-Wunreachable-rules]