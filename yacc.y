%{
/* What parser will call when 
 * there is a syntactical error */
void yyerror (char *s);	

#include <stdio.h>
#include <stdlib.h>

/* For the single operation ++ / -- */
#define ADD 1
#define SUBTRACT 0

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

%token IF, ELIF, ELSE, DO, WHILE, PRINT
%token ASSIGN_SUM, ASSIGN_MULTI, ASSIGN_DIV, ASSIGN_SUBTRACT
%token SUM, SUM_ONE, MULTI, DIV, SUBTRACT, SUBTRACT_ONE, MODULE, ASSIGN
%token PRODUCT_OF, SUM_OF, SUMMATION, PRODUCT, FACTORIAL, SLOPE
%token EQUAL_OP, NOT_EQUAL_OP, GT_OP, GTE_OP, LT_OP, LTE_OP, AND_OP, OR_OP, NOT_OP
%token COMA, SEMI_COLON, OPEN_BRACES, CLOSE_BRACES, OPEN_PARENTHESES, CLOSE_PARENTHESES
%token INTEGER, DOUBLE, FUNCTION, COORDINATES, VARIABLE, STRING
%token NEW_LINE, ASSIGN_FUNC

/* ---------------------------------------------

/* Token will be saved in the member
 * <foo> in the union */
%token <foo> token

/* Assigning types to the left hand non terminals
 * that are going to appear in my grammar */
%type <foo> bar bar2

%%
instructions:
	  block
	| instructions block
	;

block:
	  braces
	| if_block
	| loop_block
	| math_block
	| slope_block
	| function_block
	| print_block
	| return_block
	| expression
	| new_line
	;

braces:
	  OPEN_BRACES CLOSE_BRACES
	| OPEN_BRACES instructions CLOSE_BRACES
	;

if_block:
	  IF OPEN_PARENTHESES expression CLOSE_PARATHESES braces
	| IF OPEN_PARENTHESES expression CLOSE_PARATHESES braces elif_block
	| IF OPEN_PARENTHESES expression CLOSE_PARATHESES braces ELSE braces
	;

elif_block:
	  ELIF OPEN_PARENTHESES expression CLOSE_PARATHESES braces
	| ELIF OPEN_PARENTHESES expression CLOSE_PARATHESES braces ELSE braces
	;

while_expression:
	WHILE OPEN_PARENTHESES expression CLOSE_PARENTESIS SEMI_COLON
	;

loop_block:
	DO braces while_expression
	;

math_block:
	  SUMMATION OPEN_PARENTHESES math_condition CLOSE_PARATHESES SEMI_COLON
	| SUMMATION OPEN_PARENTHESES math_condition CLOSE_PARATHESES braces SEMI_COLON
	| PRODUCT OPEN_PARENTHESES math_condition CLOSE_PARATHESES SEMI_COLON
	| PRODUCT OPEN_PARENTHESES math_condition CLOSE_PARATHESES braces SEMI_COLON

math_condition:
	INTEGER SEMI_COLON expression SEMI_COLON INTEGER
	;

slope_block:
	SLOPE OPEN_PARENTHESES COORDINATES COMA COORDINATES CLOSE_PARATHESES SEMI_COLON
	;

function_block:
	FUNTION STRING OPEN_PARENTHESES TYPE variable CLOSE_PARATHESES function_definition
	;

function_definition:
	//UNKNOWN FOR NOW

print_block:
	PRINT OPEN_PARENTHESES expression CLOSE_PARATHESES SEMI_COLON
	;

return_block:
	RETURN expression SEMI_COLON
	;

constant:
	  INTEGER
	| DOUBLE

variable:
	VARIABLE
	;

base_expression:
	  constant
	| variable
    | STRING
    | OPEN_PARENTHESES expression CLOSE_PARATHESES
    ;

operation:
	  simple_expression
	| count_operation
	| relational_operation
	| logic_operation
	;

count_op:
	  MULTI
	| DIV
	| MODULE
	| SUM
	| SUBTRACT
	;

count_operation:
	operation count_op operation
	;

relational_op:
	  GT_OP
	| GTE_OP
	| LT_OP
	| LTE_OP
	| EQUAL_OP
	| NOT_EQUAL_OP
	;

relational_operation:
	operation relational_op operation
	;

logic_op:
	  AND_OP
	| OR_OP
	;

logic_operation:
	  operation AND_OP operation
	| operation OR_OP operation
	;

assign_op:
	  ASSIGN
	| ASSIGN_SUM
	| ASSIGN_SUBTRACT
	| ASSIGN_DIV
	| ASSIGN_MULTI
	;

assign_operation:
	variable assign_op operation
	;

simple_expression:
	  base_expression
	| NOT_OP relational_operation
	| NOT_OP logic_operation
	;

expression:
	  operation
	| assign_operation
	;

%%
//ACA VA LAS FUNCIONES QUE USAMOS EN PRODUCCIONES Y DEFINIMOS EN LA PRIMERA PARTE

void yyerror (char *s) {
	fprintf(stderr, "%s\n", s);
}