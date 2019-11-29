#include <stdlib.h>
#include <string.h>
#include "nodesInitializer.h"

StringNode *string(const char *string)
{
  StringNode *node = malloc(sizeof(StringNode));
  node->type = TYPE_STRING;
  node->string = calloc(strlen(string) + 1, sizeof(char));
  strcpy(node->string, string);
  return node;
}

ConstantNode *constant(const char *constant)
{
  ConstantNode *node = malloc(sizeof(ConstantNode));
  node->type = TYPE_CONSTANT;
  node->constant = calloc(strlen(constant) + 1, sizeof(char));
  strcpy(node->constant, constant);
  return node;
}

VariableNode *variable(const char *var)
{
  VariableNode *node = malloc(sizeof(VariableNode));
  node->type = TYPE_VARIABLE;
  node->stored = NULL;
  node->declared = FALSE;
  node->name = calloc(strlen(var) + 1, sizeof(char));
  strcpy(node->name, var);
  return node;
}

OperationNode *operation(const Node *first, const Node *second, const char *oper)
{
  OperationNode *node = malloc(sizeof(OperationNode));
  node->type = TYPE_OPERATION;
  node->first = (Node *)first;
  node->second = (Node *)second;
  node->oper = calloc(strlen(oper) + 1, sizeof(char));
  strcpy(node->oper, oper);
  return node;
}

ConditionalNode *conditional(const Node *first, const Node *second, const Node *third)
{
  ConditionalNode *node = malloc(sizeof(ConditionalNode));
  node->type = TYPE_CONDITIONAL;
  node->first = (Node *)first;
  node->second = (Node *)second;
  node->third = (Node *)third;
  return node;
}

IfNode *ifNode(const Node *condition, const Node *then, const Node *otherwise)
{
  IfNode *node = malloc(sizeof(IfNode));
  node->type = TYPE_IF;
  node->condition = (Node *)condition;
  node->then = (Node *)then;
  node->otherwise = (Node *)otherwise;
  return node;
}

WhileNode *while(const Node *condition, const Node *block)
{
  WhileNode *node = malloc(sizeof(WhileNode));
  node->type = TYPE_WHILE;
  node->condition = (Node *)condition;
  node->block = (Node *)block;
  return node;
}

ListNode *instructionsList(const Node *node)
{
  ListNode *list = malloc(sizeof(ListNode));
  list->type = TYPE_INSTRUCTIONS;
  list->node = (Node *)node;
  list->next = NULL;
  return list;
}

ListNode *addInstruction(const ListNode *list, const Node *node)
{
  ListNode *currentNode = (ListNode *)list;
  while (currentNode->next != NULL)
    currentNode = currentNode->next;
  currentNode->next = instructionsList(node);

  return (ListNode *)list;
}

ReturnNode *returnNode(const Node *expression)
{
  ReturnNode *node = malloc(sizeof(ReturnNode));
  node->type = TYPE_RETURN;
  node->expression = (Node *)expression;
  return node;
}

BlockNode *block(const ListNode *instructions)
{
  BlockNode *node = malloc(sizeof(BlockNode));
  node->type = TYPE_BLOCK;
  node->instructions = (ListNode *)instructions;
  return node;
}

Node *empty()
{
  Node *node = malloc(sizeof(Node));
  node->type = TYPE_NULL;
  return node;
}

InstructionNode *instruction(Node *instruction)
{
  InstructionNode *node = malloc(sizeof(InstructionNode));
  node->type = TYPE_INSTRUCTION;
  node->instruction = instruction;
  return node;
}

NegationNode *negation(Node *expression)
{
  NegationNode *node = malloc(sizeof(NegationNode));
  node->type = TYPE_NEGATION;
  node->expression = expression;
  return node;
}

PrintNode *print(Node *expression)
{
  PrintNode *node = malloc(sizeof(PrintNode));
  node->type = TYPE_PRINT;
  node->expression = expression;
  return node;
}