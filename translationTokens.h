#ifndef TRANSLATION_TOKENS_H
#define TRANSLATION_TOKENS_H

/* Definition of token types for the translation to C program*/
typedef enum {  NULL_TOKEN = 1,
                OPERATION_TOKEN,
                SINGLE_OPERATION_TOKEN,
                IF_TOKEN,
                WHILE_TOKEN,
                RETURN_TOKEN,
                STATEMENT_TOKEN,
                STATEMENTS_TOKEN,
                NEGATION_TOKEN,
                PRINT_TOKEN,
                STRING_TOKEN,
                CONSTANT_TOKEN,
                INTEGER_TOKEN,
                DOUBLE_TOKEN,
                FUNCTION_TOKEN,
                COORDINATES_TOKEN,
                VARIABLE_TOKEN,
                BLOCK_TOKEN
} TokenType;

typedef enum {  DATA_NUMBER,
                DATA_STRING,
                DATA_COORDINATES
} DataType;

/* Token structures that hold the token information */

/* Basic token */
typedef struct {
  TokenType   type;
  DataType    dataType;
} Token;

/* List of tokens */
typedef struct {
  TokenType   type;
  DataType    dataType;
  Token       *current;
  TokenList   *next;
} TokenList;

/* Token for operations */
typedef struct {
  TokenType type;     //OPERATION_TOKEN
  DataType  dataType; 
  Token     *first;   //What's left of the operator
  Token     *second;  //What's right of the operator
  char      *op;      //The operator symbol
} OperationToken;

/* Token for singular operations like X++ */
typedef struct {
  TokenType type;     //SINGLE_OPERATION_TOKEN
  DataType  dataType;
  Token     *operand; //What's being modified
  char      *op;      //The operator
} SingleOperationToken; 

/* Token for a return statement */
typedef struct {
  TokenType type;        //RETURN_TOKEN
  DataType  dataType;
  Token     *expression;  //Expression to return
} ReturnToken;

/* Token for constant values */
/* For numbers --> double and integer */
typedef struct {
  TokenType type;     //CONSTANT_TOKEN
  DataType  dataType;
  char      *value;   //Constant value
} ConstantToken;

/* Token for handling variables */
typedef struct {
  TokenType type;     //VARIABLE_TOKEN
  DataType  dataType;
  int       declared; //Is it being declared or not?
  char      *name;    //Name of the variable
  Token     *stored;
  char      *variable;
} VariableToken;

/* Token for printing */
typedef struct {
  TokenType type;         //PRINT_TOKEN
  DataType  dataType;
  Token     *expression;  //Expression to be printed
} PrintToken;

/* Token for if statement */
typedef struct {
  TokenType type;           //IF_TOKEN
  Token     *ifCondition;   //Condition to be accepted
  Token     *ifBlock;       //Token with the information of what to do if it passes
  Token     *elifCondition; //Other condition to be accepted
  Token     *elifBlock;     //Token with the informatio of what to do if it passes
  Token     *elseBlock;     //Token with the information of what to do if it fails
} IfToken;

/* Token for a calculate while loop */
typedef struct {
  TokenType type;         //WHILE_TOKEN
  Token     *block;       //Block token with the statements to execute
  Token     *condition;   //Condition to continue looping
} CalculateWhileToken;

/* Token for a block of code */
typedef struct {
  TokenType   type;           //BLOCK_TOKEN
  DataType    dataType;
  TokenList   *statements;    //Statements
} BlockToken;

/* Token for a string */
typedef struct {
  TokenType type;           //STRING_TOKEN
  DataType  dataType;
  char      *string;        //String value
} StringToken;

/* For a single statement */
typedef struct {
  TokenType type;           //STATEMENT_TOKEN
  DataType  dataType;
  Token     *statement;     //Token that's being stated
} StatementToken;

/* For the NOT_OP expressions */
typedef struct {
  TokenType type;              //NEGATION_TOKEN
  DataType  dataType;
  Token     *expression;        //Token of the expression being negated
} NegationToken;

#endif