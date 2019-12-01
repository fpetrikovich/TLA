#ifndef CODE_TRANSLATOR_H
#define CODE_TRANSLATOR_H

#include "tokenFunctions.h"

/* For storing functions */
typedef struct translatedFunctions {
	char 						*translation;
	struct translatedFunctions 	*next;
} TranslatedFunctions;

/* Frees functions */
void
freeFunctions();

/* Generates a single string for the functions */
char *
getFunctions();

int
addFunctionToArray(char *translation);

char *
functionDefTranslator(Token *token);

char *
functionCallTranslator(Token *token);

/* For the rest */
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

char *
SlopeTranslator(Token *token);

static char *
process(Token *token);

char *
translateToC(Token *token);

#endif