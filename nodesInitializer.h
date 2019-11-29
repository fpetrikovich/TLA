#ifndef NODES_INITIALIZER_H
#define NODES_INITIALIZER_H

#include "nodes.h"

#define FALSE 0
#define TRUE !FALSE

StringNode *string(const char *string);
ConstantNode *constant(const char *constant);
VariableNode *variable(const char *var);
OperationNode *operation(const Node *first, const Node *second, const char *oper);
ConditionalNode *conditional(const Node *first, const Node *second, const Node *third);
IfNode *ifNode(const Node *condition, const Node *then, const Node *otherwise);
WhileNode *whileNode(const Node *condition, const Node *block);
ListNode *instructionsList(const Node *node);
ListNode *addInstruction(const ListNode *list, const Node *node);
ReturnNode *returnNode(const Node *expression);
BlockNode *block(const ListNode *instructions);
Node *empty();
InstructionNode *instruction(Node *instruction);
NegationNode *negation(Node *expression);
PrintNode *print(Node *expression);

#endif