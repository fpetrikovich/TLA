#include <stdlib.h>
#include <string.h>
#include "tokenFunctions.h"

/* Creates a statement token */
StatementToken *createStatementToken(Token *statement) {
  //First we allocate memory
  StatementToken *token = malloc(sizeof(StatementToken));
  if (token == NULL) {
    //TODO: See how to handle NULL returns on yacc
    return NULL;
  }
  token->type       = STATEMENT_TOKEN;
  token->statement  = statement;
  return token;
}

/* Adds a statement to the list of statement */
TokenList *addStatement(const TokenList *list, const Token *statement) {
  //We start from the first token of the list and search the first token with next equal to NULL
  TokenList *currentToken = (TokenList *)list;
  while (currentToken->next != NULL)
    currentToken = currentToken->next;

  //Once we find the current token who's next is null, we add our new statement to that next
  currentToken->next = createStatementList(statement);

  //TODO: See how to handle failure in memory allocation
  if(currentToken->next == NULL) {
    //TODO: Free the previous elements of the list
    return NULL;
  }

  return (TokenList *)list;
}

/* Creates a list of statement tokens */
TokenList *createStatementList(const Token *statement) {
  //First we allocate memory
  TokenList *list = malloc(sizeof(TokenList));
  if (list == NULL) {
    //TODO: See how to handle NULL returns on yacc
    return NULL;
  }
  list->type    = STATEMENTS_TOKEN;
  list->current = (Token *)statement;   //First statement on the list
  list->next    = NULL;
  return list;
}

/* Creates a block token */
BlockToken *createBlockToken(const TokenList *statements) {
  //First we allocate memory
  BlockToken *token = malloc(sizeof(BlockToken));
  if (token == NULL) {
    //TODO: Handle frees
    return NULL;
  }
  token->type       = BLOCK_TOKEN;
  token->statements = (TokenList *)statements;
  return token;
}

/* Creates an if token */
IfToken *createIfToken(const Token *condition, const Token *then, const Token *otherwise) {
  //First we allocate memory
  IfToken *token = malloc(sizeof(IfToken));
  if (token == NULL) {
    //TODO: Handle frees
    return NULL;
  }
  token->type       = IF_TOKEN;
  token->condition  = (Token *)condition;
  token->then       = (Token *)then;
  token->otherwise  = (Token *)otherwise;
  return token;
}

/* Creates a while token */
WhileToken *createWhileToken(const Token *condition, const Token *block) {
  //First we allocate memory
  WhileToken *token = malloc(sizeof(WhileToken));
  if (token == NULL) {
    //TODO: Handle frees
    return NULL;
  }
  token->type       = WHILE_TOKEN;
  token->condition  = (Token *)condition;
  token->block      = (Token *)block;
  return token;
}

/* Creates an operation token */
OperationToken *createOperationToken(const Token *first, const Token *second, const char *oper) {
  //First we allocate memory
  OperationToken *token = malloc(sizeof(OperationToken));
  if (token == NULL) {
    //TODO: Handle frees
    return NULL;
  }
  token->type     = OPERATION_TOKEN;
  token->first    = (Token *)first;
  token->second   = (Token *)second;
  token->oper     = calloc(strlen(oper) + 1, sizeof(char));
  if(token->oper == NULL) {
    free(token);
    return NULL;
  }
  strcpy(token->oper, oper);
  return token;
}

/* Creates a string token */
StringToken *createStringToken(const char *string) {
  //First we allocate memory
  StringToken *token = malloc(sizeof(StringToken));
  if (token == NULL) {
    //TODO: Handle frees
    return NULL;
  }
  token->type   = STRING_TOKEN;
  token->string = calloc(strlen(string) + 1, sizeof(char));
  if(token->string == NULL) {
    free(token);
    return NULL;
  }
  strcpy(token->string, string);
  return token;
}

/* Creates a constant token */
ConstantToken *createConstantToken(const char *constant) {
  //First we allocate memory
  ConstantToken *token = malloc(sizeof(ConstantToken));
  if (token == NULL) {
    //TODO: Handle frees
    return NULL;
  }
  token->type     = CONSTANT_TOKEN;
  token->constant = calloc(strlen(constant) + 1, sizeof(char));
  if(token->constant == NULL) {
    free(token);
    return NULL;
  }
  strcpy(token->constant, constant);
  return token;
}

/* Creates a toker for a variable */
VariableToken *createVariableToken(const char *var) {
  VariableToken *token = malloc(sizeof(VariableToken));
  if (token == NULL) {
    //TODO: Handle frees
    return NULL;
  }
  token->type     = VARIABLE_TOKEN;
  token->stored   = NULL;
  token->declared = FALSE;
  token->name = calloc(strlen(var) + 1, sizeof(char));
  if(token->name == NULL) {
    free(token);
    return NULL;
  }
  strcpy(token->name, var);
  return token;
}

/* Creates a condition token */
ConditionToken *createConditionToken(const Token *first, const Token *second, const Token *third) {
  ConditionToken *token = malloc(sizeof(ConditionToken));
  if (token == NULL) {
    //TODO: Handle frees
    return NULL;
  }
  token->type   = CONDITION_TOKEN;
  token->first  = (Token *)first;
  token->second = (Token *)second;
  token->third  = (Token *)third;
  return token;
}

/* Creates a return token */
ReturnToken *createReturnToken(const Token *expression) {
  ReturnToken *token = malloc(sizeof(ReturnToken));
  if (token == NULL) {
    //TODO: Handle frees
    return NULL;
  }
  token->type       = RETURN_TOKEN;
  token->expression = (Token *)expression;
  return token;
}

/* Creates an empty token */
Token *createEmptyToken() {
  Token *token = malloc(sizeof(Token));
  if (token == NULL) {
    //TODO: Handle frees
    return NULL;
  }
  token->type = NULL_TOKEN;
  return token;
}

/* Creates a negation token */
NegationToken *createNegationToken(Token *expression) {
  NegationToken *token = malloc(sizeof(NegationToken));
  if (token == NULL) {
    //TODO: Handle frees
    return NULL;
  }
  token->type       = NEGATION_TOKEN;
  token->expression = expression;
  return token;
}

/* Creates a print token */
PrintToken *createPrintToken(Token *expression) {
  PrintToken *token = malloc(sizeof(PrintToken));
  if (token == NULL) {
    //TODO: Handle frees
    return NULL;
  }
  token->type       = PRINT_TOKEN;
  token->expression = expression;
  return token;
}