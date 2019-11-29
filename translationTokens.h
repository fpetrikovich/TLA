#ifndef TRANSLATION_TOKENS_H
#define TRANSLATION_TOKENS_H

/* Definition of token types for the translation to C program*/
typedef enum {  NULL_TOKEN = 1,
                OPERATION_TOKEN,
                IF_TOKEN,
                WHILE_TOKEN,
                RETURN_TOKEN,
                STATEMENT_TOKEN,
                STATEMENTS_TOKEN,
                NEGATION_TOKEN,
                PRINT_TOKEN,
                CONDITION_TOKEN,
                STRING_TOKEN,
                CONSTANT_TOKEN,
                VARIABLE_TOKEN,
                BLOCK_TOKEN
} TokenType;


/* Token structures that hold the token information */

/* Basic token */
typedef struct Token {
  TokenType type;
} Token;

/* List of tokens */
typedef struct TokenList {
  TokenType type;
  Token *current;
  struct TokenList *next;
} TokenList;

/* Token for operations */
typedef struct OperationToken {
  TokenType type;     //OPERATION_TOKEN
  Token *first;       //What's left of the operator
  Token *second;      //What's right of the operator
  char *oper;         //The operator symbol
} OperationToken;

/* Token for a return statement */
typedef struct ReturnToken {
  TokenType type;     //RETURN_TOKEN
  Token *expression;  //Expression to return
} ReturnToken;

/* Token for constant values */
typedef struct ConstantToken {
  TokenType type;     //CONSTANT_TOKEN
  char *value;        //Constant value
} ConstantToken;

/* Token for variables */
typedef struct VariableToken {
  TokenType type;     //VARIABLE_TOKEN
  int declared;
  char *name;
  Token *stored;
  char *variable;
} VariableToken;

/* Token for conditions */
typedef struct ConditionToken {
  TokenType type;     //CONDITION_TOKEN
  Token *first;
  Token *second;
  Token *third;
} ConditionToken;

/* Token for printing */
typedef struct PrintToken {
  TokenType type;     //PRINT_TOKEN
  Token *expression;  //Expression to be printed
} PrintToken;

/* Token for if statement */
typedef struct IfToken {
  TokenType type;     //IF_TOKEN
  Token *condition;   //Condition to be accepted
  Token *then;        //Token with the information of what to do if it passes
  Token *otherwise;   //Token with the information of what to do if it fails
} IfToken;

/* Token for a while loop */
typedef struct WhileToken {
  TokenType type;     //WHILE_TOKEN
  Token *condition;   //Condition to continue looping
  Token *block;       //Block token with the statements to execute
} WhileToken;

/* Token for a block of code */
typedef struct BlockToken {
  TokenType type;           //BLOCK_TOKEN
  ListToken *statements;    //Statements
} BlockToken;

typedef struct StringToken {
  TokenType type;           //STRING_TOKEN
  char *string;             //String value
} StringToken;

typedef struct StatementToken {
  TokenType type;           //STATEMENT_TOKEN
  Token *statement;         //Token that's being stated
} StatementToken;

typedef struct NegationToken {
  TokenType type;           //NEGATION_TOKEN
  Token *expression;        //Token of the expression being negated
} NegationToken;

#endif