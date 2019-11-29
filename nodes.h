#ifndef NODES_H
#define NODES_H

typedef enum {  TYPE_NULL = 1,
                TYPE_CONSTANT,
                TYPE_OPERATION,
                TYPE_CONDITIONAL,
                TYPE_STRING,
                TYPE_BLOCK,
                TYPE_IF,
                TYPE_WHILE,
                TYPE_RETURN,
                TYPE_INSTRUCTION,
                TYPE_NEGATION,
                TYPE_VARIABLE,
                TYPE_INSTRUCTIONS,
                TYPE_PRINT
} NodeType;

typedef struct Node
{
  NodeType type;
} Node;

typedef struct ListNode
{
  NodeType type;
  Node *node;
  struct ListNode *next;
} ListNode;

typedef struct OperationNode
{
  NodeType type;
  Node *first;
  Node *second;
  char *oper;
} OperationNode;

typedef struct ReturnNode
{
  NodeType type;
  Node *expression;
} ReturnNode;

typedef struct ConstantNode
{
  NodeType type;
  char *constant;
} ConstantNode;

typedef struct VariableNode
{
  NodeType type;
  int declared;
  char *name;
  Node *stored;
  char *variable;
} VariableNode;

typedef struct ConditionalNode
{
  NodeType type;
  Node *first;
  Node *second;
  Node *third;
} ConditionalNode;

typedef struct PrintNode
{
  NodeType type;
  Node *expression;
} PrintNode;

typedef struct IfNode
{
  NodeType type;
  Node *condition;
  Node *then;
  Node *otherwise;
} IfNode;

typedef struct WhileNode
{
  NodeType type;
  Node *condition;
  Node *block;
} WhileNode;

typedef struct BlockNode
{
  NodeType type;
  ListNode *instructions;
} BlockNode;

typedef struct StringNode
{
  NodeType type;
  char *string;
} StringNode;

typedef struct InstructionNode
{
  NodeType type;
  Node *instruction;
} InstructionNode;

typedef struct NegationNode
{
  NodeType type;
  Node *expression;
} NegationNode;

#endif