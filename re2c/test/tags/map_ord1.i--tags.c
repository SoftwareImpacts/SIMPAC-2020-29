/* Generated by re2c */
// incorrect automaton if mapping of TDFA states ignores version order

{
	YYCTYPE yych;
	if ((YYLIMIT - YYCURSOR) < 3) YYFILL(3);
	yych = *YYCURSOR;
	switch (yych) {
	case 'a':
		yyt2 = NULL;
		yyt1 = YYCURSOR;
		goto yy3;
	default:
		yyt1 = NULL;
		goto yy2;
	}
yy2:
	t = yyt1;
	{}
yy3:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'a':	goto yy4;
	default:	goto yy2;
	}
yy4:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'a':	goto yy5;
	default:
		yyt1 = yyt2;
		goto yy2;
	}
yy5:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
	case 'a':	goto yy5;
	default:	goto yy2;
	}
}

tags/map_ord1.i--tags.re:4: warning: rule matches empty string [-Wmatch-empty-string]
tags/map_ord1.i--tags.re:4: warning: tag 't' has 2nd degree of nondeterminism [-Wnondeterministic-tags]