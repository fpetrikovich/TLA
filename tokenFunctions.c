#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tokenFunctions.h"

/* Creates a basic token */
Token *
createToken(TokenType type, DataType dataType) {
    Token *token = malloc(sizeof *token);
    if(!isValid(token)) return NULL;

    token->type     = type;
    token->dataType = dataType;
    return token;
}

/* Free basic token */
void
freeBasicToken(Token *token) {
  if(token != NULL) {
    free(token);
  }
}

/* Creates a statement token */
StatementToken *
createStatementToken(Token *statement) {
  //First we allocate memory
  StatementToken *token = malloc(sizeof *token);
  if(!isValid(token)) return NULL;

  token->type       = STATEMENT_TOKEN;
  token->statement  = statement;
  token->dataType   = statement->dataType;
  return token;
}

/* Free statement token */
void
freeStatementToken(Token *token) {
  if(token != NULL) {
    StatementToken *castedToken = (StatementToken *)token;
    freeToken(castedToken->statement);
    free(token);
  }
}

/* Adds a statement to the list of statement */
TokenList *
addStatement(const TokenList *list, const Token *statement) {
  //We start from the first token of the list and search the first token with next equal to NULL
  TokenList *currentToken = (TokenList *)list;
  while (currentToken->next != NULL)
    currentToken = currentToken->next;

  //Once we find the current token who's next is null, we add our new statement to that next
  currentToken->next = createStatementList(statement);
  if(!isValid(currentToken->next)) {
    //TODO: Free the previous elements of the list
    return NULL;
  }

  return (TokenList *)list;
}

/* Creates a list of statement tokens */
TokenList *
createStatementList(const Token *statement) {
  //First we allocate memory
  TokenList *list = malloc(sizeof *list);
  if(!isValid(list)) return NULL;

  list->type      = STATEMENTS_TOKEN;
  list->dataType  = statement->dataType;
  list->current   = (Token *)statement;   //First statement on the list
  list->next      = NULL;
  return list;
}

/* Free statement list */
void
freeStatementList(Token *token) {
  if(token != NULL) {
    TokenList *castedToken = (TokenList *)token;
    freeToken(castedToken->current);
    freeToken(castedToken->next);
    free(token);
  }
}

/* Creates a block token */
BlockToken *
createBlockToken(const TokenList *statements) {
  //First we allocate memory
  BlockToken *token = malloc(sizeof *token);
  if(!isValid(token)) return NULL;
  
  token->type       = BLOCK_TOKEN;
  token->dataType   = statements->dataType;
  token->statements = (TokenList *)statements;
  return token;
}

/* Free a block token */
void
freeBlockToken(Token *token) {
  if(token != NULL) {
    BlockToken *castedToken = (BlockToken *)token;
    freeToken(castedToken->statements);
    free(token);
  }
}

/* Creates a summation token with delimiters ( num1 and num2 could be variables, )*/
SummationToken *
createSummationToken(const Token *initNum,const Token * condition ,const Token *finalNum) {
  SummationToken *token = malloc(sizeof *token);
  if(!isValid(token)) return NULL;
  if(initNum->dataType != DATA_NUMBER || finalNum->dataType != DATA_NUMBER){
    token->dataType = NULL;
  }
  token->type           = SUMMATION_TOKEN;
  token->initNum        = (Token *)initNum;
  token->condition      = (Token *)condition;
  token->finalNum       = (Token *)finalNum;
  
  return token;
}

void
freeSummationToken(Token * token){
  if(token != NULL) {
    SummationToken *castedToken = (SummationToken *)token;
    freeToken(castedToken->condition);
    freeToken(castedToken->initNum);
    freeToken(castedToken->finalNum);
    free(token);
  }
}

ProductionToken *
createProductionToken(const Token *initNum,const Token * condition ,const Token *finalNum) {
  ProductionToken *token = malloc(sizeof * token);
  if(!isValid(token)) return NULL;
  if(initNum->type != CONSTANT_TOKEN || finalNum  ->type != CONSTANT_TOKEN){
    token->dataType = NULL;
  }
  token->type           = PRODUCTION_TOKEN;
  token->initNum        = (Token *)initNum;
  token->condition      = (Token *)condition;
  token->finalNum       = (Token *)finalNum;

  return token;
}

void
freeProductionToken(Token * token) {
  if(token != NULL) {
    ProductionToken *castedToken = (ProductionToken *)token;
    freeToken(castedToken->condition);
    freeToken(castedToken->initNum);
    freeToken(castedToken->finalNum);
    free(token);
  }
}


/* Creates an if token */
IfToken *
createIfToken(const Token *ifCondition, const Token *ifBlock, const Token *elifCondition, const Token *elifBlock, const Token *elseBlock) {
  //First we allocate memory
  IfToken *token = malloc(sizeof *token);
  if(!isValid(token)) return NULL;
  
  token->type           = IF_TOKEN;
  token->dataType       = DATA_NULL;
  token->ifCondition    = (Token *)ifCondition;
  token->ifBlock        = (Token *)ifBlock;
  token->elifCondition  = (Token *)elifCondition;
  token->elifBlock      = (Token *)elifBlock;
  token->elseBlock      = (Token *)elseBlock;
  return token;
}

/* Free if token */
void
freeIfToken(Token *token) {
  if(token != NULL) {
    IfToken *castedToken = (IfToken *)token;
    freeToken(castedToken->ifCondition);
    freeToken(castedToken->ifBlock);
    freeToken(castedToken->elifCondition);
    freeToken(castedToken->elifBlock);
    freeToken(castedToken->elseBlock);
    free(token);
  }
}

/* Creates a while token */
CalculateWhileToken *
createCalculateWhileToken(const Token *condition, const Token *block) {
  //First we allocate memory
  WhileToken *token = malloc(sizeof *token);
  if(!isValid(token)) return NULL;
  
  token->type       = WHILE_TOKEN;
  token->dataType   = DATA_NULL;
  token->condition  = (Token *)condition;
  token->block      = (Token *)block;
  return token;
}

/* Free while token */
void
freeCalculateWhileToken(Token *token) {
  if(token != NULL) {
    CalculateWhileToken *castedToken = (CalculateWhileToken *)token;
    freeToken(castedToken->condition);
    freeToken(castedToken->block);
    free(token);
  }
}

/* Creates an operation token */
OperationToken *
createOperationToken(const Token *first, const Token *second, const char *oper) {
  //First we allocate memory
  OperationToken *token = malloc(sizeof *token);
  if(!isValid(token)) return NULL;
  
  token->type     = OPERATION_TOKEN;
  token->first    = (Token *)first;
  token->second   = (Token *)second;

  //We have two possible data types, we make sure they match
  if(first->dataType != second->dataType) {
    //If it doesn't match it could be an assignment for a new variable
    if(first->dataType == DATA_NEW && strcmp(oper, "=") == 0) {
      token->dataType = second->dataType;
    } else {
      token->dataType = NULL;
    }
  } else {
    //If they match, the only operation permited to string is assignment
    if(first->dataType == DATA_STRING && strcmp(oper, "=") != 0) {
      token->dataType = NULL;
    } else {
      token->dataType = first->dataType;
    }
  }


  token->op       = calloc(strlen(oper) + 1, sizeof(char));
  
  if(!isValid(token->op)) {
    free(token);
    return NULL;
  }
  
  strcpy(token->op, oper);
  return token;
}

/* Free operation token */
void
freeOperationToken(Token *token) {
  if(token != NULL) {
    OperationToken *castedToken = (OperationToken *)token;
    freeToken(castedToken->first);
    freeToken(castedToken->second);
    free(castedToken->op);
    free(token);
  }
}

/* Creates a single operation token */
SingleOperationToken *
createSingleOperationToken(const Token *operand, const char *oper) {
    //First we allocate memory
    SingleOperationToken *token = malloc(sizeof *token);
    if(!isValid(token)) return NULL;

    token->type     = SINGLE_OPERATION_TOKEN;
    if(operand->dataType != DATA_NUMBER) {
      token->dataType = NULL
    } else {
      token->dataType = operand->dataType;
    }
    token->operand  = (Token *)operand;
    token->op       = calloc(3, sizeof(char)); /* 2 for the operation and 1 for the 0 */
    
    if(!isValid(token->op)) {
      free(token);
      return NULL;
    }

    strcpy(token->op, oper);
    return token;
}

/* Free single operation token */
void
freeSingleOperationToken(Token *token) {
  if(token != NULL) {
    SingleOperationToken *castedToken = (SingleOperationToken *)token;
    freeToken(castedToken->operand);
    free(castedToken->op);
    free(token);
  }
}

/* Creates a string token */
StringToken *
createStringToken(const char *string) {
  //First we allocate memory
  StringToken *token = malloc(sizeof *token);
  if(!isValid(token)) return NULL;
  
  token->type     = STRING_TOKEN;
  token->dataType = DATA_STRING;
  token->string   = calloc(strlen(string) + 1, sizeof(char));
  
  if(!isValid(token->string)) {
    free(token);
    return NULL;
  }
  
  strcpy(token->string, string);
  return token;
}

/* Free string token */
void
freeStringToken(Token *token) {
  if(token != NULL) {
    StringToken *castedToken = (StringToken *)token;
    free(castedToken->string);
    free(token);
  }
}

/* Creates a constant token */
ConstantToken *
createConstantToken(const char *constant) {
  //First we allocate memory
  ConstantToken *token = malloc(sizeof *token);
  if(!isValid(token)) return NULL;
  
  token->type     = CONSTANT_TOKEN;
  token->dataType = DATA_NUMBER;
  token->constant = calloc(strlen(constant) + 1, sizeof(char));
  
  if(!isValid(token->constant)) {
    free(token);
    return NULL;
  }
  
  strcpy(token->constant, constant);
  return token;
}

/* Free constant token */
void
freeConstantToken(Token *token) {
  if(token != NULL) {
    ConstantToken *castedToken = (ConstantToken *)token;
    free(castedToken->constant);
    free(token);
  }
}

/* Creates a token for a variable */
VariableToken *
createVariableToken(const char *var) {
  VariableToken *token = malloc(sizeof *token);
  if(!isValid(token)) return NULL;
  
  token->type     = VARIABLE_TOKEN;
  token->dataType = DATA_NEW;
  token->stored   = NULL;
  token->declared = FALSE;
  token->name     = calloc(strlen(var) + 1, sizeof(char));
  
  if(!isValid(token->name)) {
    free(token);
    return NULL;
  }
  
  strcpy(token->name, var);
  return token;
}

/* Free variable token */
void
freeVariableToken(Token *token) {
  if(token != NULL) {
    VariableToken *castedToken = (VariableToken *)token;
    free(castedToken->name);
    free(token);
  }
}

/* Creates a return token */
ReturnToken *
createReturnToken(const Token *expression) {
  ReturnToken *token = malloc(sizeof *token);
  if(!isValid(token)) return NULL;
  
  token->type       = RETURN_TOKEN;
  token->dataType   = expression->dataType;
  token->expression = (Token *)expression;
  return token;
}

/* Free return token */
void
freeReturnToken(Token *token) {
  if(token != NULL) {
    free(NULL);
  }
}

/* Creates an empty token */
Token *
createEmptyToken() {
  Token *token = malloc(sizeof *token);
  if(!isValid(token)) return NULL;
  
  token->type     = NULL_TOKEN;
  token->dataType = DATA_NULL;
  return token;
}

/* Free emtpy token */
void
freeEmptyToken(Token *token) {
  if(token != NULL) {
    free(token);
  }
}

/* Creates a negation token */
NegationToken *
createNegationToken(Token *expression) {
  NegationToken *token = malloc(sizeof *token);
  if(!isValid(token)) return NULL;
  
  token->type       = NEGATION_TOKEN;
  if(expression->dataType == DATA_NUMBER) {
    token->dataType = expression->dataType;
  } else {
    token->dataType = NULL;
  }
  token->expression = expression;
  return token;
}

/* Free a negation token */
void
freeNegationToken(Token *token) {
  if(token != NULL) {
    free(token);
  }
}

/* Creates a print token */
PrintToken *
createPrintToken(Token *expression) {
  PrintToken *token = malloc(sizeof *token);
  if(!isValid(token)) return NULL;
  
  token->type       = PRINT_TOKEN;
  if(expression->dataType == DATA_STRING) {
    token->dataType = expression->dataType;
  } else {
    token->dataType = NULL;
  }
  token->expression = expression;
  return token;
}


/* Free a print token */
void
freePrintToken(Token *token) {
  if(token != NULL) {
    free(token);
  }
}

/* Internal function for verifying the pointer returned by malloc/calloc */
static int
isValid(void *ptr) {
    if (ptr == NULL) {
        fprintf(stderr, "Error allocating heap space\n");
        return 0;
    }
    return 1;
}

void
freeToken(Token *token) {
  if(token != NULL) {
    switch(token->type) {
      case NULL_TOKEN:
        freeEmptyToken(token);
        break;
      case OPERATION_TOKEN:
        freeOperationToken(token);
        break;
      case SINGLE_OPERATION_TOKEN:
        freeSingleOperationToken(token);
        break;
      case IF_TOKEN:
        freeIfToken(token);
        break;
      case WHILE_TOKEN:
        freeCalculateWhileToken(token);
        break;
      case RETURN_TOKEN:
        freeReturnToken(token);
        break;
      case STATEMENT_TOKEN:
        freeStatementToken(token);
        break;
      case STATEMENTS_TOKEN:
        freeStatmentList(token);
        break;
      case NEGATION_TOKEN:
        freeNegationToken(token);
        break;
      case PRINT_TOKEN:
        freePrintToken(token);
        break;
      case STRING_TOKEN:
        freeStringToken(token);
        break;
      case CONSTANT_TOKEN:
        freeConstantToken(token);
        break;
      case INTEGER_TOKEN:
      case DOUBLE_TOKEN:
      case FUNCTION_TOKEN:
      case COORDINATES_TOKEN:
        //TODO
        break;
      case VARIABLE_TOKEN:
        freeVariableToken(token);
        break;
      case BLOCK_TOKEN:
        freeBlockToken(token);
        break;
      default:
    }
  }
}