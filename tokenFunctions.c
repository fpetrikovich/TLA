#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tokenFunctions.h"

/* Creates a basic token */
Token *
createToken(TokenType type, DataType data) {
    Token *token = malloc(sizeof *token);
    if(!isValid(token)) return NULL;

    token->type = type;
    token->data = data;
    return token;
}

/* Creates a statement token */
StatementToken *
createStatementToken(Token *statement) {
  //First we allocate memory
  StatementToken *token = malloc(sizeof *token);
  if(!isValid(token)) return NULL;

  token->type       = STATEMENT_TOKEN;
  token->data       = NULL;
  token->statement  = statement;
  return token;
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
  
  list->type    = STATEMENTS_TOKEN;
  list->data    = NULL;
  list->current = (Token *)statement;   //First statement on the list
  list->next    = NULL;
  return list;
}

/* Creates a block token */
BlockToken *
createBlockToken(const TokenList *statements) {
  //First we allocate memory
  BlockToken *token = malloc(sizeof *token);
  if(!isValid(token)) return NULL;
  
  token->type       = BLOCK_TOKEN;
  token->data       = NULL;
  token->statements = (TokenList *)statements;
  return token;
}

/* Creates an if token */
IfToken *
createIfToken(const Token *ifCondition, const Token *ifBlock, const Token *elifCondition, const Token *elifBlock, const Token *elseBlock) {
  //First we allocate memory
  IfToken *token = malloc(sizeof *token);
  if(!isValid(token)) return NULL;
  
  token->type           = IF_TOKEN;
  token->data           = NULL;
  token->ifCondition    = (Token *)ifCondition;
  token->ifBlock        = (Token *)ifBlock;
  token->elifCondition  = (Token *)elifCondition;
  token->elifBlock      = (Token *)elifBlock;
  token->elseBlock      = (Token *)elseBlock;
  return token;
}

/* Creates a while token */
CalculateWhileToken *
createCalculateWhileToken(const Token *condition, const Token *block) {
  //First we allocate memory
  WhileToken *token = malloc(sizeof *token);
  if(!isValid(token)) return NULL;
  
  token->type       = WHILE_TOKEN;
  token->data       = NULL;
  token->condition  = (Token *)condition;
  token->block      = (Token *)block;
  return token;
}

/* Creates an operation token */
OperationToken *
createOperationToken(const Token *first, const Token *second, const char *oper) {
  //First we allocate memory
  OperationToken *token = malloc(sizeof *token);
  if(!isValid(token)) return NULL;
  
  token->type     = OPERATION_TOKEN;
  token->data     = first->data;
  token->first    = (Token *)first;
  token->second   = (Token *)second;
  token->op       = calloc(strlen(oper) + 1, sizeof(char));
  
  if(!isValid(token->op)) {
    free(token);
    return NULL;
  }
  
  strcpy(token->op, oper);
  return token;
}

/* Creates a single operation token */
SingleOperationToken *
createSingleOperationToken(const Token *operand, const char *oper) {
    //First we allocate memory
    SingleOperationToken *token = malloc(sizeof *token);
    if(!isValid(token)) return NULL;

    token->type     = SINGLE_OPERATION_TOKEN;
    token->data     = DATA_NUMBER;
    token->operand  = (Token *)operand;
    token->op       = calloc(3, sizeof(char)); /* 2 for the operation and 1 for the 0 */
    
    if(!isValid(token->op)) {
      free(token);
      return NULL;
    }

    strcpy(token->op, oper);
    return token;
}

/* Creates a string token */
StringToken *
createStringToken(const char *string) {
  //First we allocate memory
  StringToken *token = malloc(sizeof *token);
  if(!isValid(token)) return NULL;
  
  token->type   = STRING_TOKEN;
  token->data   = DATA_STRING;
  token->string = calloc(strlen(string) + 1, sizeof(char));
  
  if(!isValid(token->string)) {
    free(token);
    return NULL;
  }
  
  strcpy(token->string, string);
  return token;
}

/* Creates a constant token */
ConstantToken *
createConstantToken(const char *constant) {
  //First we allocate memory
  ConstantToken *token = malloc(sizeof *token);
  if(!isValid(token)) return NULL;
  
  token->type     = CONSTANT_TOKEN;
  token->data     = DATA_NUMBER;
  token->constant = calloc(strlen(constant) + 1, sizeof(char));
  
  if(!isValid(token->constant)) {
    free(token);
    return NULL;
  }
  
  strcpy(token->constant, constant);
  return token;
}

/* Creates a token for a variable */
VariableToken *
createVariableToken(const char *var, const Token *tokenT) {
  VariableToken *token = malloc(sizeof *token);
  if(!isValid(token)) return NULL;
  
  token->type     = VARIABLE_TOKEN;
  token->data     = tokenT->data;
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

/* Creates a return token */
ReturnToken *
createReturnToken(const Token *expression) {
  ReturnToken *token = malloc(sizeof *token);
  if(!isValid(token)) return NULL;
  
  token->type       = RETURN_TOKEN;
  token->data       = NULL;
  token->expression = (Token *)expression;
  return token;
}

/* Creates an empty token */
Token *
createEmptyToken() {
  Token *token = malloc(sizeof *token);
  if(!isValid(token)) return NULL;
  
  token->type = NULL_TOKEN;
  token->data = NULL;
  return token;
}

/* Creates a negation token */
NegationToken *
createNegationToken(Token *expression) {
  NegationToken *token = malloc(sizeof *token);
  if(!isValid(token)) return NULL;
  
  token->type       = NEGATION_TOKEN;
  token->data       = DATA_NUMBER;      //Negation works with numbers not strings
  token->expression = expression;
  return token;
}

/* Creates a print token */
PrintToken *
createPrintToken(Token *expression) {
  PrintToken *token = malloc(sizeof *token);
  if(!isValid(token)) return NULL;
  
  token->type       = PRINT_TOKEN;
  token->data       = NULL;
  token->expression = expression;
  return token;
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