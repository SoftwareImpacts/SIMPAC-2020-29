/* Generated by re2c 0.16 on Mon Jun 25 20:07:34 2018 */
#line 1 "test.re"
typedef enum num_t { ERR, BIN, OCT, DEC, HEX } num_t;
static num_t lex(const char *YYCURSOR)
{
    const char *YYMARKER;
    
#line 9 "test.c"
{
	char yych;
	yych = *YYCURSOR;
	switch (yych) {
	case '0':	goto yy4;
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy5;
	default:	goto yy2;
	}
yy2:
	++YYCURSOR;
yy3:
#line 15 "test.re"
	{ return ERR; }
#line 31 "test.c"
yy4:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 0x00:	goto yy6;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':	goto yy8;
	case 'B':
	case 'b':	goto yy11;
	case 'X':
	case 'x':	goto yy12;
	default:	goto yy3;
	}
yy5:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 0x00:	goto yy13;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy15;
	default:	goto yy3;
	}
yy6:
	++YYCURSOR;
#line 17 "test.re"
	{ return OCT; }
#line 70 "test.c"
yy8:
	++YYCURSOR;
	yych = *YYCURSOR;
	switch (yych) {
	case 0x00:	goto yy6;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':	goto yy8;
	default:	goto yy10;
	}
yy10:
	YYCURSOR = YYMARKER;
	goto yy3;
yy11:
	yych = *++YYCURSOR;
	if (yych <= 0x00) goto yy10;
	goto yy18;
yy12:
	yych = *++YYCURSOR;
	if (yych <= 0x00) goto yy10;
	goto yy20;
yy13:
	++YYCURSOR;
#line 18 "test.re"
	{ return DEC; }
#line 101 "test.c"
yy15:
	++YYCURSOR;
	yych = *YYCURSOR;
	switch (yych) {
	case 0x00:	goto yy13;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy15;
	default:	goto yy10;
	}
yy17:
	++YYCURSOR;
	yych = *YYCURSOR;
yy18:
	switch (yych) {
	case 0x00:	goto yy21;
	case '0':
	case '1':	goto yy17;
	default:	goto yy10;
	}
yy19:
	++YYCURSOR;
	yych = *YYCURSOR;
yy20:
	switch (yych) {
	case 0x00:	goto yy23;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':	goto yy19;
	default:	goto yy10;
	}
yy21:
	++YYCURSOR;
#line 16 "test.re"
	{ return BIN; }
#line 163 "test.c"
yy23:
	++YYCURSOR;
#line 19 "test.re"
	{ return HEX; }
#line 168 "test.c"
}
#line 20 "test.re"

}
