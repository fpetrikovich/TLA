#include "codeTranslator.h"
#include <string.h>

variableStorage *variables = NULL;
static variableDefinida variables[MAX_VARIABLES];

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

/* Translator for string */
char *
stringTranslator(Token *token) {
  char *value = ((StringToken *)token)->string;

  const size_t bufferLenght = strlen(value) + 1;
  char *buffer = malloc(bufferLenght);
  if(buffer == NULL) {
  	return NULL;
  }
  snprintf(buffer, bufferLenght, "%s", value);

  return buffer;
}

/* Tramslator for constant */
char *
constantTranslator(Token *token) {
  char *value = ((ConstantToken *)token)->value;
  char *buffer = malloc(strlen(value) + 1);
  if(buffer == NULL) {
  	return NULL;
  }
  strcpy(buffer, value);
  return buffer;
}

/* Translator for variable token */
char *
variableTranslator(Token *token) {
  char *name = ((VariableToken *)token)->name;
  char *newVariable = calloc(strlen(name) + strlen("_") + 1, sizeof(char));
  if(newVariable == NULL) {
  	return NULL;
  }
  strcpy(newVariable, name);
  strcat(newVariable, "_");

  return newVariable;
}

/* Translator for if token */
char *
ifTranslator(Token *token) {
  IfToken *castedToken = (IfToken *)token;

  //Translate parts of the if to C
  char *ifCondition = process(castedToken->ifCondition);
  if(ifCondition == NULL) {
  	return NULL;
  }
  char *ifBlock = process(castedToken->ifBlock);
  if(ifBlock == NULL) {
  	free(ifCondition);
  	return NULL;
  }

  //Now the following three parts are optional, so they could be missing
  if(castedToken->elifCondition != NULL && castedToken->elifBlock != NULL) {
  	char *elifCondition = process(castedToken->elifCondition);
  	if(elifCondition == NULL) {
  		free(ifCondition);
  		free(ifBlock);
  		return NULL;
  	}

  	char *elifBlock = process(castedToken->elifBlock);
  	if (elifBlock == NULL) {
  		free(ifCondition);
  		free(ifBlock);
  		free(elifCondition);
  		return NULL;
  	}
  } else if ((castedToken->elifCondition == NULL && castedToken->elifBlock != NULL) || (castedToken->elifCondition != NULL && castedToken->elifBlock == NULL)) {
  	//If one is present without the other then it's invalid
  	free(ifCondition);
  	free(ifBlock);
  	return NULL;
  }

  if(castedToken->elseBlock != NULL) {
  	char *elseBlock = process(castedToken->elseBlock);
  	if (elseBlock == NULL) {
  		free(ifCondition);
  		free(ifBlock);
  		if(castedToken->elifCondition != NULL && castedToken->elifBlock != NULL) {
  			free(elifCondition);
  			free(elifBlock);
  		}
  		return NULL;
  	}
  }

  //We calculate the buffer lenght, there are three different cases
  //The base lenght is:
 	size_t bufferLenght = strlen(ifCondition) + strlen(ifBlock) + strlen("if %s {%s}") + 2;	//+2 cuz i consider a \n as well
 	//If there is an elif we should add it:
 	if(castedToken->elifCondition != NULL && castedToken->elifBlock != NULL) {
 		bufferLenght += strlen(elifCondition) + strlen(elifBlock) + strlen(" else if %s {%s}");
 	}
 	//If there is an else block we should add it:
 	if(castedToken->elseBlock != NULL) {
 		bufferLenght += strlen(elseBlock) + strlen(" else {%s}");
 	}

 	//Now we allocate the space
  char *buffer = malloc(bufferLenght);
  if (buffer == NULL) {
  	free(ifCondition);
  	free(ifBlock);
  	if(castedToken->elifCondition != NULL && castedToken->elifBlock != NULL) {
  		free(elifCondition);
  		free(elifBlock);
  	}
  	if(castedToken->elseBlock != NULL) {
  		free(elseBlock);
  	}
  	return NULL;
  }

  //Now we add to buffer according to the different cases
  if(castedToken->elifCondition != NULL && castedToken->elifBlock != NULL && castedToken->elseBlock != NULL) {
  	//Everything is present
  	snprintf(buffer, bufferLenght, "if %s {%s} else if %s {%s} else {%s}\n", ifCondition, ifBlock, elifCondition, elifBlock, elseBlock);

  	//Free what's uneeded
  	free(ifCondition);
  	free(ifBlock);
  	free(elifCondition);
  	free(elifBlock);
  	free(elseBlock);
  } else if(castedToken->elifCondition != NULL && castedToken->elifBlock != NULL) {
  	//Just else missing
  	snprintf(buffer, bufferLenght, "if %s {%s} else if %s {%s}\n", ifCondition, ifBlock, elifCondition, elifBlock);

  	//Free what's uneeded
  	free(ifCondition);
  	free(ifBlock);
  	free(elifCondition);
  	free(elifBlock);
  } else {
  	//Just if and else
  	snprintf(buffer, bufferLenght, "if %s {%s} else {%s}\n", ifCondition, ifBlock, elseBlock);

  	//Free what's uneeded
  	free(ifCondition);
  	free(ifBlock);
  	free(elseBlock);
  }

  return buffer;
}

//TODO: Revise this whole variable thing, is it needed
/* Translator for operation token */
char *
operationTranslator(Token *token) {
  //We only call this function if we know the type, so we can safely cast it
  OperationToken *castedToken = (OperationToken *)token;

  //We process the stuff to the left of the operator
  char *first = process(castedToken->first);
  if(first == NULL) {
  	return NULL;
  }
  //We process the stuff to the right of the operator
  char *second = process(castedToken->second);
  if(second == NULL) {
  	free(first);
  	return NULL;
  }
  char *op = castedToken->op;
  char *buffer;

  if (castedToken->first->type == VARIABLE_TOKEN && strcmp(castedToken->op, "=") == 0 || strcmp(castedToken->op, "+=") == 0 || strcmp(castedToken->op, "-=") == 0 || strcmp(castedToken->op, "/=") == 0 || strcmp(castedToken->op, "*=") == 0) {
    //We find the variable its refering to, if it doesn't exist we just create it
    variableInfo *variable = findVariable(((VariableToken *)castedToken->first)->name);

    VariableToken *castedFirstToken 	= (VariableToken *)castedToken->first;
    VariableToken *castedSecondToken 	= (VariableToken *)castedToken->second;

    if ((castedToken->second->type == STRING_TOKEN || (castedToken->second->type == VARIABLE_TOKEN && castedSecondToken->stored != NULL && castedSecondToken->stored->type == STRING_TOKEN))) {
      const size_t bufferLenght = strlen(first) + strlen(op) + strlen(second) + strlen("char* ") + 4;
      
      buffer = malloc(bufferLenght);
      if(buffer == NULL) {
      	free(first);
      	free(second);
      	return NULL;
      }
      
      if (variable->definida == 0) {
        snprintf(buffer, bufferLenght, "char* ");
      }

      variable->type = STRING_TOKEN;
    } else {
      const size_t bufferLenght = strlen(first) + strlen(op) + strlen(second) + strlen("int ") + 4;
      
      buffer = malloc(bufferLenght);
      if(buffer == NULL) {
      	free(first);
      	free(second);
      	return NULL;
      }

      if (variable->definida == 0) {
        snprintf(buffer, bufferLenght, "int ");
      }
      
      variable->type = CONSTANT_TOKEN;
    }

    //We add to buffer
    strcat(buffer, first);
    strcat(buffer, " ");
    strcat(buffer, op);
    strcat(buffer, " ");
    strcat(buffer, second);
    strcat(buffer, ";");

    //We free what's uneeded
    free(first);
    free(second);
    return buffer;
  } else {
    const size_t bufferLenght = strlen(first) + strlen(op) + strlen(second) + strlen("()") + 1;
    
    buffer = malloc(bufferLenght);
    if(buffer == NULL) {
    	free(first);
    	free(second);
    	return NULL;
    }

    snprintf(buffer, bufferLenght, "(%s%s%s)", first, op, second);

    free(first);
    free(second);

    return buffer;
  }
}

/* Translator for block token */
char *
blockTranslator(Token *token) {
  return process(token->statements);
}

/* Translator for empty token */
char *
emptyTranslator(Token *token) {

  const size_t bufferLenght = strlen("\n") + 1;
  char *buffer = malloc(bufferLenght);
  if(buffer == NULL) {
  	return NULL;
  }
  strcpy(buffer, "\n");

  return buffer;
}

/* Translator for negation */
char *
negationTranslator(Token *token) {
  NegationToken *castedToken = (NegationToken *)token;
  char *expression = process(castedToken->expression);
  if(expression == NULL) {
  	return NULL;
  }

  const size_t bufferLenght = strlen(expression) + strlen("(!)") + 1;
  char *buffer = calloc(bufferLenght, sizeof(char));
  if(buffer == NULL) {
  	free(expression);
  	return NULL;
  }
  snprintf(buffer, bufferLenght, "(!%s)", expression);

  free(expression);
  return buffer;
}

/* Translator for return expression */
char *
returnTranslator(Token *token) {
  ReturnToken *castedToken = (ReturnToken *)token;

  char *expression = process(castedToken->expression);
  if(expression == NULL) {
  	return NULL;
  }

  const size_t bufferLenght = strlen(expression) + strlen("return ;\n") + 1;
  char *buffer = malloc(bufferLenght);
  if(buffer == NULL) {
  	free(expression);
  	return NULL;
  }
  snprintf(buffer, bufferLenght, "return %s;\n", expression);

  free(expression);
  return buffer;
}

/* Translator for a print token */
char *
printTranslator(Token *token) {
  PrintToken *castedToken = (PrintToken *)token;
  char *expression = process(castedToken->expression);
  if(expression == NULL) {
  	return NULL;
  }
  char *printfParameter;

  char *p = malloc(strlen(expression) * sizeof(char));
  if(p == NULL) {
  	free(expression);
  	return NULL;
  }
  strcpy(p, expression);

  variableInfo *variable = findVariable(p);

  if (variable->type == STRING_TOKEN)
    printfParameter = "%s";
  else
    printfParameter = "%d";

  const size_t bufferLenght = strlen(expression) + strlen("printf('XX', );\n") + 1;
  char *buffer = calloc(bufferLenght, sizeof(char));
  if(buffer == NULL) {
  	free(p);
  	free(expression);
  	return NULL;
  }

  snprintf(buffer, bufferLenght, "printf(\"%s\", %s);\n", printfParameter, expression);

  free(p);
  free(expression);

  return buffer;
}

/* Translation for while token */
char *
calculateWhileTranslator(Token *token) {
	//We only call this function if we know the type, so we can safely cast it
  CalculateWhileToken *castedToken = (CalculateWhileToken *)token;

  //We translate to C
  char *condition = process(castedToken->condition);
  if(condition == NULL) {
  	return NULL;
  }
  char *block = process(castedToken->block);
  if(block == NULL) {
  	free(condition);
  	return NULL;
  }

  //Calculate lenght of buffer
  const size_t bufferLenght = strlen(condition) + strlen(block) + strlen("while %s {%s}") + 1;
  char *buffer = malloc(bufferLenght);
  if(buffer == NULL) {
  	free(condition);
  	free(block);
  	return NULL;
  }

  //We copy to buffer
  snprintf(buffer, bufferLenght, "while %s {%s}", condition, block);

  //We free uneeded strings
  free(condition);
  free(block);

  return buffer;
}

/* Translator for statement token */
char *
statementTranslator(Token *token) {
	//We only call this function if we know the type, so we can safely cast it
  StatementToken *castedToken = (StatementToken *)token;

  //We translate the statemet to C code
  char *statement = process(castedToken->statement);

  if(statement == NULL) {
  	return NULL;
  }

  //Aside from the lenght of the statement we need space for the new line and the NULL
  const size_t bufferLenght = strlen(statement) + strlen("\n") + 1;
  //We create an initial buffer to save our translated code to
  char *buffer 							= malloc(bufferLenght);
  if(buffer == NULL) {
  	//TODO: See how to best manage this errors
  	return NULL;
  }
  //We copy to buffer
  snprintf(buffer, bufferLenght, "%s\n", statement);

  //We no longer need the statement string so we free it
  free(statement);

  return buffer;
}

/* Translator for a statement list */
char *
statementListTranslator(Token *token) {
	//We only call this function if we know the type, so we can safely cast it
  TokenList *list = (TokenList *)token;

  //We create an initial buffer to save our translated code to
  char *buffer = malloc(1);
  if(buffer == NULL) {
  	//TODO: See how to best manage this errors
  	return NULL;
  }
  buffer[0] = '\0';

  //TODO: This should never happen but we check just in case
  if (list == NULL)
    return buffer;

  do {
    Token *currentToken = (Token *)list->current;
    //If we reach the end on the first run we finish the loop
    if (currentToken == NULL)
      break;

    //We translate this current Token to C code
    char *newCode = process(currentToken);
    if(newCode == NULL) {
    	//TODO: See how to best manange this errors
    	free(buffer);
    	return NULL;
    }
    //We allocate the extra memory for this new code
    char *newBuffer = realloc(buffer, strlen(newCode) + strlen(buffer) + 1);
    if (newBuffer == NULL) {
    	//TODO: See how to best manange this errors
    	free(buffer);
    	return NULL;
    }
    buffer = newBuffer;

    //Since realloc leaves the original data intact, we use strcat
    strcat(buffer, newCode);

    //Now that we no longer need the newCode we free it
    free(newCode);

  } while ((list = list->next) != NULL);

  //Once we processed all the elements of the list we return the code
  return buffer;
}

/* Token processing function
		its return value should be free'd by whoever requested it once they are done with it */
static char *
process(Token *token) {
  //Verify the input is not null
	char *returnValue = NULL;
  if (token == NULL) {
    return returnValue;
  }

  //Translate it according to the type
  switch(token->type) {
  	case NULL_TOKEN:
  		returnValue = emptyTranslator(token);
  		break;
  	case OPERATION_TOKEN:
  		returnValue = operationTranslator(token);
  		break;
  	case SINGLE_OPERATION_TOKEN:
  		//TODO
  		break;
  	case IF_TOKEN:
  		returnValue = ifTranslator(token);
  		break;
  	case WHILE_TOKEN:
  		returnValue = calculateWhileTranslator(token);
  		break;
  	case RETURN_TOKEN:
  		returnValue = returnTranslator(token);
  		break;
  	case STATEMENT_TOKEN:
  		returnValue = statementTranslator(token);
  		break;
  	case STATEMENTS_TOKEN:
  		returnValue = statementListTranslator(token);
  		break;
  	case NEGATION_TOKEN:
  		returnValue = negationTranslator(token);
  		break;
  	case PRINT_TOKEN:
  		returnValue = printTranslator(token);
  		break;
  	case STRING_TOKEN:
  		returnValue = stringTranslator(token);
  		break;
  	case CONSTANT_TOKEN:
  		returnValue = constantTranslator(token);
  		break;
  	case INTEGER_TOKEN:
  	case DOUBLE_TOKEN:
  	case FUNCTION_TOKEN:
  	case COORDINATES_TOKEN:
  		//TODO
  		break;
  	case VARIABLE_TOKEN:
  		returnValue = variableTranslator(token);
  		break;
  	case BLOCK_TOKEN:
  		returnValue = blockTranslator(token);
  		break;
  	default:
  }
  //Return the translation of the token
  return returnValue;
}

/* Main function to translate our code to C code 
		its return value should be free'd by whoever requested it once they are done with it */
char *
translateToC(Token *token) {

	//Load C program in string form
	char *code = process(token);

	//Return it to be printed to file
	return code;
}