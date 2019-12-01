#ifndef TOKEN_FUNCTIONS_H
#define TOKEN_FUNCTIONS_H

#include "translationTokens.h"

#define FALSE 0
#define TRUE !FALSE

/* Creation function for a statement token */
StatementToken *
createStatementToken		(Token *statement);

/* Adds a single statement to a list of statements */
TokenList *
addStatement				(const TokenList *list,
							 const Token *statement);

/* Creation function for a list of statement tokens */
TokenList *
createStatementList			(const Token *statement);

/* Creation function for a block token */
BlockToken *
createBlockToken			(const TokenList *statements);

/* Creation function for a if token */
IfToken *
createIfToken				(const Token *ifCondition,
							 const Token *ifBlock, 
							 const Token *elifCondition, 
							 const Token *elifBlock, 
							 const Token *elseBlock);

/* Creation function for a while token */
CalculateWhileToken *
createCalculateWhileToken	(const Token *condition,
							 const Token *block);

/* Creation function for an operation token */
OperationToken *
createOperationToken		(const Token *first,
							 const Token *second,
							 const char *oper);

/* Creation function for a single operation token */
SingleOperationToken *
createSingleOperationToken 	(const Token *operand, 
							 const char *oper);

/* Creation function for a string token */
StringToken *
createStringToken 			(const char *string);

/* Creation function for a constant token */
ConstantToken *
createConstantToken 		(const char *constant);

/* Creation function for a variable token */
VariableToken *
createVariableToken 		(const char *var, const Token *tokenT);

/* Creation function for a return token */
ReturnToken *
createReturnToken 			(const Token *expression);

/* Creation function for an empty token */
Token *
createEmptyToken 			(void);

/* Creation function for a negation token */
NegationToken *
createNegationToken 		(Token *expression);

/* Creation function for a print token */
PrintToken *
createPrintToken 			(Token *expression);

/* Free's a token */
void
freeToken					(Token *token);

#endif