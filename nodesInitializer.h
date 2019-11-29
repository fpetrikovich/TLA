#ifndef NODES_INITIALIZER_H
#define NODES_INITIALIZER_H

#include "nodes.h"

#define FALSE 0
#define TRUE !FALSE

StringNode *
string(const char *string);

ConstantNode *
constant(const char *constant);

VariableNode *
variable(const char *var);

OperationNode *
operation(const Node *first, const Node *second, const char *oper);

SingleOperationNode *
singleOperation(const Node *node, const char *oper);

IfNode *
ifNode(const Node *ifN, const Node *ifBlock, const Node *elifN, const Node *elifBlock, const Node *elseN);

CalculateWhileNode *
whileNode(const Node *condition, const Node *block);

ListNode *
instructionsList(const Node *node);

ListNode *
addInstruction(const ListNode *list, const Node *node);

ReturnNode *
returnNode(const Node *expression);

BlockNode *
block(const ListNode *instructions);

Node *
empty();

InstructionNode *
instruction(Node *instruction);

NegationNode *
negation(Node *expression);

PrintNode *
print(Node *expression);

#endif