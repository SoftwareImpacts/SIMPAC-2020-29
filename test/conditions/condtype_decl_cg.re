// re2c $INPUT -o $OUTPUT -cg
/*!types:re2c*/

int main ()
{
	YYCONDTYPE cond;
	char * YYCURSOR;
#define YYGETCONDITION() cond
/*!re2c
	re2c:yyfill:enable = 0;
	re2c:define:YYCTYPE = "unsigned char";
	<a> "a" {}
	<b> "b" {}
*/
	return 0;
}
