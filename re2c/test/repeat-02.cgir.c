/* Generated by re2c */
// multiple scanners


enum YYCONDTYPE {
	yycr1,
	yycr2,
};



void scan(unsigned char* in)
{

{
	unsigned char yych;
	static void *yyctable[2] = {
		&&yyc_r1,
		&&yyc_r2,
	};
	goto *yyctable[YYGETCONDITION()];
/* *********************************** */
yyc_r1:
	if (limit1 <= cursor1) fill1(1);
	yych = *cursor1;
	if (yych <= '2') {
		if (yych <= '0') goto yy3;
		if (yych <= '1') goto yy4;
		goto yy6;
	} else {
		if (yych <= '`') goto yy3;
		if (yych <= 'a') goto yy8;
		if (yych <= 'b') goto yy10;
	}
yy3:
yy4:
	++cursor1;
	{ return "1"; }
yy6:
	++cursor1;
	{ return "2"; }
yy8:
	++cursor1;
	{ return "a"; }
yy10:
	++cursor1;
	{ return "b"; }
/* *********************************** */
yyc_r2:
	if (limit1 <= cursor1) fill1(1);
	yych = *cursor1;
	if (yych <= '2') {
		if (yych <= '0') goto yy14;
		if (yych <= '1') goto yy15;
		goto yy17;
	} else {
		if (yych == 'b') goto yy19;
	}
yy14:
yy15:
	++cursor1;
	{ return "1"; }
yy17:
	++cursor1;
	{ return "2"; }
yy19:
	++cursor1;
	{ return "b"; }
}

}

void scan(unsigned short* in)
{

{
	unsigned short yych;
	static void *yyctable[2] = {
		&&yyc_r1,
		&&yyc_r2,
	};
	goto *yyctable[YYGETCONDITION()];
/* *********************************** */
yyc_r1:
	if (limit2 <= cursor2) fill2(1);
	yych = *cursor2;
	if (yych <= '2') {
		if (yych <= '0') goto yy3;
		if (yych <= '1') goto yy4;
		goto yy6;
	} else {
		if (yych <= '`') goto yy3;
		if (yych <= 'a') goto yy8;
		if (yych <= 'b') goto yy10;
	}
yy3:
yy4:
	++cursor2;
	{ return "1"; }
yy6:
	++cursor2;
	{ return "2"; }
yy8:
	++cursor2;
	{ return "a"; }
yy10:
	++cursor2;
	{ return "b"; }
/* *********************************** */
yyc_r2:
	if (limit2 <= cursor2) fill2(1);
	yych = *cursor2;
	if (yych <= '2') {
		if (yych <= '0') goto yy14;
		if (yych <= '1') goto yy15;
		goto yy17;
	} else {
		if (yych == 'b') goto yy19;
	}
yy14:
yy15:
	++cursor2;
	{ return "1"; }
yy17:
	++cursor2;
	{ return "2"; }
yy19:
	++cursor2;
	{ return "b"; }
}

}

void scan(unsigned int* in)
{

{
	unsigned int yych;
	static void *yyctable[2] = {
		&&yyc_r1,
		&&yyc_r2,
	};
	goto *yyctable[YYGETCONDITION()];
/* *********************************** */
yyc_r1:
	if (limit3 <= cursor3) fill3(1);
	yych = *cursor3;
	if (yych <= '2') {
		if (yych <= '0') goto yy3;
		if (yych <= '1') goto yy4;
		goto yy6;
	} else {
		if (yych <= '`') goto yy3;
		if (yych <= 'a') goto yy8;
		if (yych <= 'b') goto yy10;
	}
yy3:
yy4:
	++cursor3;
	{ return "1"; }
yy6:
	++cursor3;
	{ return "2"; }
yy8:
	++cursor3;
	{ return "a"; }
yy10:
	++cursor3;
	{ return "b"; }
/* *********************************** */
yyc_r2:
	if (limit3 <= cursor3) fill3(1);
	yych = *cursor3;
	if (yych <= '2') {
		if (yych <= '0') goto yy14;
		if (yych <= '1') goto yy15;
		goto yy17;
	} else {
		if (yych == 'b') goto yy19;
	}
yy14:
yy15:
	++cursor3;
	{ return "1"; }
yy17:
	++cursor3;
	{ return "2"; }
yy19:
	++cursor3;
	{ return "b"; }
}

}

re2c: warning: line 13: control flow in condition 'r1' is undefined for strings that match '[\x0-\x30\x33-\x60\x63-\xFF]', use default rule '*' [-Wundefined-control-flow]
re2c: warning: line 13: control flow in condition 'r2' is undefined for strings that match '[\x0-\x30\x33-\x61\x63-\xFF]', use default rule '*' [-Wundefined-control-flow]
re2c: warning: line 13: control flow in condition 'r1' is undefined for strings that match '[\x0-\x30\x33-\x60\x63-\xFF]', use default rule '*' [-Wundefined-control-flow]
re2c: warning: line 13: control flow in condition 'r2' is undefined for strings that match '[\x0-\x30\x33-\x61\x63-\xFF]', use default rule '*' [-Wundefined-control-flow]
re2c: warning: line 13: control flow in condition 'r1' is undefined for strings that match '[\x0-\x30\x33-\x60\x63-\xFF]', use default rule '*' [-Wundefined-control-flow]
re2c: warning: line 13: control flow in condition 'r2' is undefined for strings that match '[\x0-\x30\x33-\x61\x63-\xFF]', use default rule '*' [-Wundefined-control-flow]
