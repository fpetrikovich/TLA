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
%start instructions

%parse-param { ListNode ** code }

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
%token BEGIN, END

/* ---------------------------------------------

/* Token will be saved in the member
 * <foo> in the union */
%token <foo> token

/* Assigning types to the left hand non terminals
 * that are going to appear in my grammar */
%type <foo> bar bar2

%%
instructions:
	  BEGIN block END { *code = instructionList($2);   $$ = *code; }
	| BEGIN END		  { *code = instructionList(NULL); $$ = *code; }
	;

block:
	  braces 			{ $$ = bloque($1); }
	| if_block 			{ $$ = $1; }
	| loop_block		{ $$ = $1; }
	| math_block		{ $$ = $1; }
	| slope_block		{ $$ = $1; }
	| function_block	{ $$ = $1; }
	| print_block		{ $$ = $1; }
	| return_block		{ $$ = $1; }
	| expression 		{ $$ = instruction($1); }
	| new_line 			{ $$ = empty(); }
	;

braces:
	  OPEN_BRACES CLOSE_BRACES				{ $$ = instructionList(NULL); }
	| OPEN_BRACES instructions CLOSE_BRACES { $$ = $2; }
	;

if_block:
	  IF OPEN_PARENTHESES expression CLOSE_PARATHESES braces
	  	{ $$ = ifNode($3, $5, NULL, NULL, NULL); }
	| IF OPEN_PARENTHESES expression CLOSE_PARATHESES braces ELIF OPEN_PARENTHESES expression CLOSE_PARATHESES braces
	  	{ $$ = ifNode($3, $5, $8, $10, NULL); }
	| IF OPEN_PARENTHESES expression CLOSE_PARATHESES braces ELIF OPEN_PARENTHESES expression CLOSE_PARATHESES braces ELSE braces
	 	{ $$ = ifNode($3, $5, $8, $10, $12); }
	| IF OPEN_PARENTHESES expression CLOSE_PARATHESES braces ELSE braces
		{ $$ = ifNode($3, $5, NULL, NULL, $7); }
	;

loop_block:
	DO braces WHILE OPEN_PARENTHESES expression CLOSE_PARENTESIS SEMI_COLON 
		{ $$ = whileNode($5, $2); }
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
	PRINT OPEN_PARENTHESES expression CLOSE_PARATHESES SEMI_COLON { $$ = print($3); }
	;

return_block:
	RETURN expression SEMI_COLON { $$ = returnNode($2); }
	;

constant:
	  INTEGER { $$ = constant($1); }
	| DOUBLE  { $$ = constant($1); }
	;

variable:
	VARIABLE  { $$ = variable($1); }
	;

base_expression:
	  constant { $$ = $1; }
	| variable { $$ = $1; }
    | STRING   { $$ = string($1); }
    | OPEN_PARENTHESES expression CLOSE_PARATHESES { $$ = $2; }
    ;

simple_expression:
	  base_expression				{ $$ = $1; }
	| NOT_OP relational_operation 	{ $$ = negation($2); }
	| NOT_OP logic_operation 		{ $$ = negation($2); }
	;

expression:
	  simple_expression 	{ $$ = $1; }
	| count_operation		{ $$ = $1; }
	| relational_operation	{ $$ = $1; }
	| logic_operation		{ $$ = $1; }
	;

count_op:
	  MULTI 	{ strcpy($$, "*"); }
	| DIV 		{ strcpy($$, "/"); }
	| MODULE 	{ strcpy($$, "%"); }
	| SUM 		{ strcpy($$, "+"); }
	| SUBTRACT 	{ strcpy($$, "-"); }
	;

count_operation:
	expression count_op expression { $$ = operation($1, $2, $3); }
	;

relational_op:
	  GT_OP 		{ strcpy($$, ">"); }
	| GTE_OP		{ strcpy($$,">="); }
	| LT_OP 		{ strcpy($$, "<"); }
	| LTE_OP 		{ strcpy($$,"<="); }
	| EQUAL_OP 		{ strcpy($$,"=="); }
	| NOT_EQUAL_OP  { strcpy($$,"!="); }
	;

relational_operation:
	expression relational_op expression { $$ = operation($1, $2, $3); }
	;

logic_op:
	  AND_OP { strcpy($$, "&&"); }
	| OR_OP  { strcpy($$, "||"); }
	;

logic_operation:
	  expression AND_OP expression  { $$ = operation($1, $2, $3); }
	| expression OR_OP expression   { $$ = operation($1, $2, $3); }
	;

one_op:
	  SUM_ONE		{ strcpy($$, "++"); }
	| SUBTRACT_ONE	{ strcpy($$, "--"); }
	;

one_operation:
	variable one_op { $$ = single_operation($1, $2); }
	;

assign_op:
	  ASSIGN 			{ strcpy($$, "="); }
	| ASSIGN_SUM 		{ strcpy($$,"+="); }
	| ASSIGN_SUBTRACT	{ strcpy($$,"-="); }
	| ASSIGN_DIV		{ strcpy($$,"/="); }
	| ASSIGN_MULTI		{ strcpy($$,"*="); }
	;

assign_operation:
	variable assign_op operation { $$ = operation($1, $2, $3); }
	;

%%
//ACA VA LAS FUNCIONES QUE USAMOS EN PRODUCCIONES Y DEFINIMOS EN LA PRIMERA PARTE

void 
yyerror(ListNode ** code, char *s) {
	fprintf(stderr, "%s\n", s);
	printf("-------------\n%s in line %d\n-------------\n", s, yylineno);
	exit(EXIT_FAILURE);
}

int
main(void) {

}