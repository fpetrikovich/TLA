%{
/* What parser will call when 
 * there is a syntactical error */
void yyerror (char *s);	

#include <stdio.h>
#include <stdlib.h>

// ACA VAN LAS DECLARACIONES DE LAS FUNCIONES
%}

/* Specify the different types 
 * my lexical analyzer can return */
%union {
	int foo;
}

/* Which of the productions that follow 
 * in the middle section is going to be
 * my starting rule */
%start

/* ----------------- TOKENS ---------------------
 * Token that I'm expecting from the lexical 
 * analyzer (will save as defines in tab.h) */

%token IF, ELSE, DO, WHILE, PRINT
%token ASSIGN_SUM, ASSIGN_MULTI, ASSIGN_DIV, ASSIGN_SUBTRACT,
%token SUM, SUM_ONE, MULTI, DIV, SUBTRACT, SUBTRACT_ONE, MODULE, ASSIGN,
%token PRODUCT_OF, SUM_OF, SUMMATION, PRODUCT, FACTORIAL, SLOPE,
%token EQUAL_OP, NOT_EQUAL_OP, GT_OP, GTE_OP, LT_OP, LTE_OP, AND_OP, OR_OP,
%token COMA, SEMI_COLON, OPEN_BRACES, CLOSE_BRACES, OPEN_PARENTHESES, CLOSE_PARENTHESES,
%token INTEGER, DOUBLE, FUNCTION, COORDINATES, VARIABLE, STRING,
%token NEW_LINE,

/* ---------------------------------------------

/* Token will be saved in the member
 * <foo> in the union */
%token <foo> token

/* Assigning types to the left hand non terminals
 * that are going to appear in my grammar */
%type <foo> bar bar2

%%
//ACA VAN LAS PRODUCCIONES

%%
//ACA VA LAS FUNCIONES QUE USAMOS EN PRODUCCIONES Y DEFINIMOS EN LA PRIMERA PARTE

void yyerror (char *s) {
	fprintf(stderr, "%s\n", s);
}