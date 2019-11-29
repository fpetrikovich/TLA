#include "codeGenerator.h"
#include <string.h>

variableStorage *variables = NULL;

variableInfo *
findVariable(const char *name) {
	for (int i = 0; i < variables->amount; i++) {
		if (strcmp(variables->list[i].name, name)) {
			return &(variables->list[i]);
		}
	}
	printf("\"%s\" is not declared.\n", name);
	exit(EXIT_FAILURE);
}