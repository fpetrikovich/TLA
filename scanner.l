%{
#include "y.tab.h"
%}

digit		[0-9]
number		-?{digit}+
string_reg 	\"[^\"]*\"
variable 	[a-zA-Z][a-zA-Z0-9]*
coordinates \(-?[0-9]+,-?[0-9]+\)
new_line 	\n

%%
"start"					return START;
"end"					return END;
"if"					return IF;
"elif"					return ELIF;
"else"					return ELSE;
"calculate"				return DO;
"while"					return WHILE;
"print"					return PRINT;
"number"				return NUMBER_TYPE;
"string"				return STRING_TYPE;	
"function"				return FUNCTION_TYPE; 
"return"				return RETURN;
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
[ \t\r]+				;		//Ignore white space


{number} 				{ strcpy(yylval.string, yytext); return NUMBER_LITERAL; }
{variable} 				{ strcpy(yylval.string, yytext); return VAR;    }
{string_reg}			{ strcpy(yylval.string, yytext); return STRING_LITERAL; }
{new_line} 				{ yylineno++; }		//Do we even use new line? should we just ignore it?
.						;
	
%%
int yywrap(void) {
	return 1;
}