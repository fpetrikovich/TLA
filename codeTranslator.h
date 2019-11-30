#include "translationTokens.h"

#ifndef CODE_TRANSLATOR_H
#define CODE_TRANSLATOR_H

#define MAX_VAR_NAME  50

extern VariableToken **variables;

VariableToken *
createOrFindVariable(const char *name);

VariableToken *
castVariable(VariableToken *variable, Token *token);

char *
stringTranslator(Token *token);

char *
constantTranslator(Token *token);

char *
variableTranslator(Token *token);

char *
ifTranslator(Token *token);

char *
operationTranslator(Token *token);

char *
blockTranslator(Token *token);

char *
emptyTranslator(Token *token);

char *
negationTranslator(Token *token);

char *
returnTranslator(Token *token);

char *
printTranslator(Token *token);

char *
calculateWhileTranslator(Token *token);

char *
statementTranslator(Token *token);

char *
statementListTranslator(Token *token);

static char *
process(Token *token);

char *
translateToC(Token *token);

#endif