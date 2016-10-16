%{
	#include<string.h>
	#include<stdio.h>
	#include "y.tab.h"
%}
%%
[ \t\n] ;
main {return MAIN;}
int|float|char|long|double {strcpy(yylval.string,yytext); return DATATYPE;}
[a-zA-Z_][a-zA-Z0-9]* {strcpy(yylval.string,yytext); return IDENTIFIER;}
[0-9]+ |
[0-9]+\.[0-9]+ {yylval.dval=atof(yytext); return NUMBER;} //IMP ATOF(YYTEXT)

. {return yytext[0];}
%%
int yywrap(){
	return 1;
}
