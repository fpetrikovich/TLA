#ifndef TRANSLATION_TOKENS_H
#define TRANSLATION_TOKENS_H

#define MAX_VARIABLES 100

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
                FUNCTION_DEF_TOKEN,
                FUNCTION_CALL_TOKEN,
                COORDINATES_TOKEN,
                VARIABLE_TOKEN,
                BLOCK_TOKEN,
                SIGMA_PI_TOKEN,
                SIGMA_PI_COND_TOKEN,
                SLOPE_TOKEN
} TokenType;

typedef enum {  DATA_NODATA = 1,
                DATA_FUNCTION,
                DATA_NEW,
                DATA_NULL,
                DATA_NUMBER,
                DATA_STRING,
                DATA_COORDINATES
} DataType;

typedef enum {  SUMMATION_TYPE,
                PRODUCTION_TYPE
} MathType;

/* Token structures that hold the token information */

/* Shared struct */
typedef struct basicInfo {
  TokenType   type;
  DataType    dataType;
} BasicInfo;

/* Basic token */
typedef struct Token {
  BasicInfo   basicInfo;
} Token;

/* List of tokens */
typedef struct TokenList {
  BasicInfo          basicInfo;
  Token              *current;
  struct TokenList   *next;
} TokenList;

/* Token for functions */
typedef struct FunctionDefinitionToken {
  BasicInfo     basicInfo;
  Token         *name;
  Token         *body;
  Token         *param;
} FunctionDefinitionToken;

typedef struct FunctionCallToken {
  BasicInfo   basicInfo;
  Token       *name;
  Token       *expression;
} FunctionCallToken;

/* Token for operations */
typedef struct OperationToken {
  BasicInfo   basicInfo; 
  Token     *first;   //What's left of the operator
  Token     *second;  //What's right of the operator
  char      *op;      //The operator symbol
} OperationToken;

/* Token for singular operations like X++ */
typedef struct SingleOperationToken {
  BasicInfo   basicInfo;
  Token     *operand; //What's being modified
  char      *op;      //The operator
} SingleOperationToken; 

/* Token for a return statement */
typedef struct ReturnToken {
  BasicInfo   basicInfo;
  Token     *expression;  //Expression to return
} ReturnToken;

/* Token for constant values */
/* For numbers --> double and integer */
typedef struct ConstantToken {
  BasicInfo   basicInfo;
  char      *constant;   //Constant value
} ConstantToken;

/* Token for handling variables */
typedef struct VariableToken {
  BasicInfo   basicInfo;
  int       declared; //Is it being declared or not?
  char      *name;    //Name of the variable
} VariableToken;

/* Token for printing */
typedef struct PrintToken {
  BasicInfo   basicInfo;
  Token     *expression;  //Expression to be printed
} PrintToken;

/* Token for if statement */
typedef struct IfToken {
  BasicInfo   basicInfo;
  Token     *ifCondition;   //Condition to be accepted
  Token     *ifBlock;       //Token with the information of what to do if it passes
  Token     *elifCondition; //Other condition to be accepted
  Token     *elifBlock;     //Token with the informatio of what to do if it passes
  Token     *elseBlock;     //Token with the information of what to do if it fails
} IfToken;

/* Token for a calculate while loop */
typedef struct CalculateWhileToken {
  BasicInfo   basicInfo;
  Token     *block;       //Block token with the statements to execute
  Token     *condition;   //Condition to continue looping
} CalculateWhileToken;

/* Token for a block of code */
typedef struct BlockToken {
  BasicInfo   basicInfo;
  TokenList   *statements;    //Statements
} BlockToken;

/* Token for a string */
typedef struct StringToken {
  BasicInfo   basicInfo;
  char      *string;        //String value
} StringToken;

/* For a single statement */
typedef struct StatementToken {
  BasicInfo   basicInfo;
  Token     *statement;     //Token that's being stated
} StatementToken;

/* For the NOT_OP expressions */
typedef struct NegationToken {
  BasicInfo   basicInfo;
  Token     *expression;        //Token of the expression being negated
} NegationToken;

typedef struct SigmaPiToken {
  BasicInfo   basicInfo;
  MathType    mathType;
  Token      *condition;
  Token      *acum;
} SigmaPiToken;

typedef struct SigmaPiConditionToken {
  BasicInfo  basicInfo;
  Token      *initNum;         //Token of the initial number
  Token      *expression;      //Token of the condition number
  Token      *finalNum;        //Token of the final number
} SigmaPiConditionToken;

typedef struct CoordinatesToken {
  BasicInfo   basicInfo;
  Token      *constant1;
  Token      *constant2;
} CoordinatesToken;

typedef struct SlopeToken {
  BasicInfo   basicInfo;
  Token       *coord1;
  Token       *coord2;
} SlopeToken;

#endif