#include "nodos.h"

#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#define MAX_VARIABLES 100
#define MAX_VAR_NAME  50

extern variableStorage *variables;

typedef struct {
	NodeType type;			  /*Declared data type */
	char name[MAX_VAR_NAME];  /* Variable name */
	char defined;			  /* Variable was defined or not */
} variableInfo;

typedef struct {
	variableInfo list[MAX_VARIABLES];
	int amount;
} variableStorage;

VariableNode *
findVariable(const char *name);

#endif