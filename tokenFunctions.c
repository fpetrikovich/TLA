#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tokenFunctions.h"
#include "translationTokens.h"


/* Internal function for verifying the pointer returned by malloc/calloc */
static int
isValid(void *ptr) {
    if (ptr == NULL) {
        fprintf(stderr, "Error allocating heap space\n");
        return 0;
    }
    return 1;
}


VariableToken *
createOrFindVariable(const char *name) {
  int i;
  for (i = 0; variables[i] != NULL && i < MAX_VARIABLES; i++) {
    if (strcmp(variables[i]->name, name) == 0) {
      return variables[i];
    } 
  }
  variables[i] = createVariableToken(name);
  return variables[i];
}

Token *
castVariable(Token *variable, DataType dataType) {
  if(variable->basicInfo.dataType != DATA_NEW){
    /* Already casted before --> redeclaration = error */
    variable->basicInfo.dataType = DATA_NULL;
    return variable;
  }
  variable->basicInfo.dataType = dataType;
  return variable;
}

/* Creates a basic token */
Token *
createToken(TokenType type, DataType dataType) {
    Token *token = malloc(sizeof *token);
    if(!isValid(token)) return NULL;

    token->basicInfo.type     = type;
    token->basicInfo.dataType = dataType;
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

  token->basicInfo.type       = STATEMENT_TOKEN;
  token->statement            = statement;
  token->basicInfo.dataType   = statement->basicInfo.dataType;
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
    freeToken((Token *)list);
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

  list->basicInfo.type      = STATEMENTS_TOKEN;
  list->basicInfo.dataType  = statement->basicInfo.dataType;
  list->current             = (Token *)statement;   //First statement on the list
  list->next                = NULL;
  return list;
}

/* Free statement list */
void
freeStatementList(Token *token) {
  if(token != NULL) {
    TokenList *castedToken = (TokenList *)token;
    freeToken(castedToken->current);
    freeToken((Token *)castedToken->next);
    free(token);
  }
}

/* Creates a block token */
BlockToken *
createBlockToken(const TokenList *statements) {
  //First we allocate memory
  BlockToken *token = malloc(sizeof *token);
  if(!isValid(token)) return NULL;
  
  token->basicInfo.type       = BLOCK_TOKEN;
  token->basicInfo.dataType   = statements->basicInfo.dataType;
  token->statements = (TokenList *)statements;
  return token;
}

/* Free a block token */
void
freeBlockToken(Token *token) {
  if(token != NULL) {
    BlockToken *castedToken = (BlockToken *)token;
    freeToken((Token *)castedToken->statements);
    free(token);
  }
}

SigmaPiToken *
createSigmaPiToken(MathType type, Token *acumVariable, Token *condition) {
  SigmaPiToken *token = malloc(sizeof *token);
  if (!isValid(token)) return NULL;
  
  token->basicInfo.type     = SIGMA_PI_TOKEN;
  token->basicInfo.dataType = condition->basicInfo.dataType;
  token->mathType           = type;  
  token->condition          = condition;
  token->acum               = acumVariable;
  return token;
}

void
freeSigmaPiToken(Token * token){
  if(token != NULL) {
    SigmaPiToken *castedToken = (SigmaPiToken *)token;
    freeToken(castedToken->condition);
    free(token);
  }
}

SigmaPiConditionToken *
createSigmaPiCondtionToken (const Token *initNum, const Token *expr, const Token *finalNum) {
  SigmaPiConditionToken *token = malloc(sizeof *token);

  token->basicInfo.type     = SIGMA_PI_COND_TOKEN;
  token->basicInfo.dataType = DATA_NUMBER;
  token->initNum            = (Token *)initNum;
  token->expression         = (Token *)expr;
  token->finalNum           = (Token *)finalNum;
  
 return token;
}

int
checkLimits(OperationToken *num1, OperationToken *num2) {
  if (strcmp(num1->op, "=") != 0 || strcmp(num2->op, "=") != 0) {
    return DATA_NULL;
  }
  /* Same variable was specified and numbers were assigned */
  if (num1->first->basicInfo.type == VARIABLE_TOKEN && num2->first->basicInfo.type == VARIABLE_TOKEN) {
    VariableToken *var1 = (VariableToken *)num1->first;
    VariableToken *var2 = (VariableToken *)num2->first;

    if( strcmp(var1->name, var2->name) == 0 
    && num1->second->basicInfo.dataType == DATA_NUMBER 
    && num2->second->basicInfo.dataType == DATA_NUMBER) {
      return DATA_NUMBER;
    }
  }
}

SigmaPiConditionToken *
createSigmaPiConditionToken (const Token *initNum, const Token *expr, const Token *finalNum) {
  SigmaPiConditionToken *token = malloc(sizeof *token);
  if(!isValid(token)) return NULL;

  if (initNum->basicInfo.type != OPERATION_TOKEN || finalNum->basicInfo.type != OPERATION_TOKEN) {
    token->basicInfo.dataType = DATA_NULL;
    return token;
  }

  OperationToken *beginNum = (OperationToken *)initNum;
  OperationToken *endNum   = (OperationToken *)finalNum;

  token->basicInfo.dataType = checkLimits(beginNum, endNum);
  token->basicInfo.type     = SIGMA_PI_COND_TOKEN;
  token->initNum            = (Token *)initNum;
  token->expression         = (Token *)expr;
  token->finalNum           = (Token *)finalNum;
  
 return token;
}

void
freeSigmaPiConditionToken(Token * token){
  if(token != NULL) {
    SigmaPiConditionToken *castedToken = (SigmaPiConditionToken *)token;
    freeToken(castedToken->initNum);
    freeToken(castedToken->expression);
    freeToken(castedToken->finalNum);
    free(token);
  }
}

SlopeToken *
createSlopeToken(Token * coord1, Token * coord2){
  SlopeToken *token = malloc(sizeof * token);
  if(!isValid(token)) return NULL;
  if(coord1->basicInfo.type != COORDINATES_TOKEN || coord2->basicInfo.type != COORDINATES_TOKEN){
    token->basicInfo.dataType = DATA_NULL;
  }
  token->basicInfo.type = CONSTANT_TOKEN;
  token->coord1         = coord1;
  token->coord2         = coord2;
  return token;
}

void
freeSlopeToken(Token * token){
  if(token != NULL) {
    SlopeToken *castedToken = (SlopeToken *)token;
    freeToken(castedToken->coord1);
    freeToken(castedToken->coord2);
    free(token);
  }
}

/* Creates an if token */
IfToken *
createIfToken(const Token *ifCondition, const Token *ifBlock, const Token *elifCondition, const Token *elifBlock, const Token *elseBlock) {
  //First we allocate memory
  IfToken *token = malloc(sizeof *token);
  if(!isValid(token)) return NULL;
  
  token->basicInfo.type           = IF_TOKEN;
  token->basicInfo.dataType       = DATA_NODATA;
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
  CalculateWhileToken *token = malloc(sizeof *token);
  if(!isValid(token)) return NULL;
  
  token->basicInfo.type       = WHILE_TOKEN;
  token->basicInfo.dataType   = DATA_NODATA;
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
createOperationToken(const Token *first,const char *oper,const Token *second) {
  //First we allocate memory
  OperationToken *token = malloc(sizeof *token);
  if(!isValid(token)) return NULL;
  
  token->basicInfo.type     = OPERATION_TOKEN;
  token->first    = (Token *)first;
  token->second   = (Token *)second;

  //We have two possible data types, we make sure they match
  if(first->basicInfo.dataType != second->basicInfo.dataType) {
      // Set the dataType as invalid
      token->basicInfo.dataType = DATA_NULL;
  } else {
    //If they match, the only operation permited to string is assignment
    if(first->basicInfo.dataType == DATA_STRING && strcmp(oper, "=") != 0) {
      token->basicInfo.dataType = DATA_NULL;
    } else {
      token->basicInfo.dataType = first->basicInfo.dataType;
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

    token->basicInfo.type     = SINGLE_OPERATION_TOKEN;
    if(operand->basicInfo.dataType != DATA_NUMBER) {
      token->basicInfo.dataType = DATA_NULL;
    } else {
      token->basicInfo.dataType = operand->basicInfo.dataType;
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
  
  token->basicInfo.type     = STRING_TOKEN;
  token->basicInfo.dataType = DATA_STRING;
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
  
  token->basicInfo.type     = CONSTANT_TOKEN;
  token->basicInfo.dataType = DATA_NUMBER;
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
  
  token->basicInfo.type     = VARIABLE_TOKEN;
  token->basicInfo.dataType = DATA_NEW;
  token->declared = 0;
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
freeVariableToken(VariableToken *token) {
  if(token != NULL) {
    //TODO: Fix this!!!!
    free(token->name);
    free(token);
  }
}

/* Creates a return token */
ReturnToken *
createReturnToken(const Token *expression) {
  ReturnToken *token = malloc(sizeof *token);
  if(!isValid(token)) return NULL;
  
  token->basicInfo.type       = RETURN_TOKEN;
  token->basicInfo.dataType   = expression->basicInfo.dataType;
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
  
  token->basicInfo.type     = NULL_TOKEN;
  token->basicInfo.dataType = DATA_NODATA;
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
  
  token->basicInfo.type       = NEGATION_TOKEN;
  if(expression->basicInfo.dataType == DATA_NUMBER) {
    token->basicInfo.dataType = expression->basicInfo.dataType;
  } else {
    token->basicInfo.dataType = DATA_NULL;
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
  
  token->basicInfo.type       = PRINT_TOKEN;
  if(expression->basicInfo.dataType == DATA_STRING || expression->basicInfo.dataType == DATA_NUMBER) {
    token->basicInfo.dataType = expression->basicInfo.dataType;
  } else {
    token->basicInfo.dataType = DATA_NULL;
  }
  token->expression = expression;
  return token;
}


/* Free a print token */
void
freePrintToken(Token *token) {
  if(token != NULL) {
    PrintToken *castedToken = (PrintToken *)token;
    freeToken(castedToken->expression);
    free(token);
  }
}

void
freeToken(Token *token) {
  if(token != NULL) {
    switch(token->basicInfo.type) {
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
        freeStatementList(token);
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
      case FUNCTION_TOKEN:
      case COORDINATES_TOKEN:
        //TODO
        break;
      case VARIABLE_TOKEN:
        //Will be done in the main;
        break;
      case BLOCK_TOKEN:
        freeBlockToken(token);
        break;
      case SIGMA_PI_TOKEN:
        freeSigmaPiToken(token);
        break;
      case SIGMA_PI_COND_TOKEN:
        freeSigmaPiConditionToken(token);
        break;
      case SLOPE_TOKEN:
        freeSlopeToken(token);
        break;
      default:
        printf("Something went wrong, this token has no valid type\n");
    }
  }
}

// VARIABLES FREE
void
freeVariables(void) {
  for (int i = 0; variables[i] != NULL && i < MAX_VARIABLES; i++) {
    freeVariableToken(variables[i]);
  }
  free(variables);
}