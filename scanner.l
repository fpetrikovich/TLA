%{
#include "y.tab.h"
#include "tokenFunctions.h"
#include "translationTokens.h"
#include "codeTranslator.h"
%}

digit		[0-9]
decimal		-?{digit}+\.{digit}+
variable 	[a-zA-Z][a-zA-Z0-9]*
coordinates \(-?[0-9]+,-?[0-9]+\)
new_line 	\n

%%
"if"					return IF;
"elif"					return ELIF;
"else"					return ELSE;
"calculate"				return DO;
"while"					return WHILE;
"print"					return PRINT;
"+="					return ASSIGN_SUM;
"*="					return ASSIGN_MULTI;
"\\=?"					return ASSIGN_DIV;
"-="					return ASSIGN_SUBTRACT;
"+"     				return SUM;;
"++" 					return SUM_ONE;
"*"						return MULTI;
"/"						return DIV;
"-"						return SUBTRACT;
"--"					return SUBTRACT_ONE;
"%%"					return MODULE;
"=" 			  	 	return ASSIGN;
"product of"			return PRODUCT_OF;
"sum of"				return SUM_OF;
"summation"				return SUMMATION;
"product"				return PRODUCT;
"slope"					return SLOPE;
"!!"					return FACTORIAL;
"!"						return NOT_OP;
"<-"					return ASSIGN_FUNC;
"=="					return EQUAL_OP;
"!="					return NOT_EQUAL_OP;
">"						return GT_OP;
">="					return GTE_OP;
"<"						return LT_OP;
"<="					return LTE_OP;
"&&"					return AND_OP;
"||"					return OR_OP;
":"						return COMA;
";"						return SEMI_COLON;
"{"						return OPEN_BRACES;
"}"						return CLOSE_BRACES;
"("						return OPEN_PARENTHESES;
")"						return CLOSE_PARENTHESES;
"start"					return START;
"end"					return END;
"number"				return NUMBER;
"coordinates"			return COORDINATES;
"string"				return STRING;	
"function"				return FUNCTION; //NO SE SI VA ESTA?

{decimal} 				{ strcpy(yylval.string, yytext); return NUMBER; }
{coordinates} 			{ strcpy(yylval.string, yytext); return STRING; }
{variable} 				{ strcpy(yylval.string, yytext); return VARIABLE; }
{new_line} 				{ yylineno++; return NEW_LINE; }
.
	
%%
int yywrap(void) {
	return 1;
}