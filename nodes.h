#ifndef NODES_H
#define NODES_H

typedef enum {  TYPE_NULL = 1,
                TYPE_CONSTANT,
                TYPE_OPERATION,
                TYPE_SINGLE_OPERATION,
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
                TYPE_PRINT,
                /* For declarations */
                TYPE_INTEGER,
                TYPE_DOUBLE,
                TYPE_STRING,
                TYPE_FUNCTION,
                TYPE_COORDINATES
} NodeType;

typedef struct {
  NodeType type;
} Node;

typedef struct {
  NodeType type;
  Node *node;
  struct ListNode *next;
} ListNode;

/* Node for calculations with two
 * elements and an operand between */
typedef struct {
  NodeType type;
  Node *first;
  Node *second;
  char *op;
} OperationNode;

/* For the X++ and X-- operations */
typedef struct {
  NodeType type;
  Node *node;
  char *op;
} SingleOperationNode; 

/* Node for the return expression */
typedef struct {
  NodeType type;
  Node *expression;
} ReturnNode;

/* For numbers --> double and integer */
typedef struct {
  NodeType type;
  char *constant;
} ConstantNode;

/* For manipulation of variables */
typedef struct {
  NodeType type;
  int declared;
  char *name;
  Node *stored;
  char *variable;
} VariableNode;

/* Node to print */
typedef struct {
  NodeType type;
  Node *expression;
} PrintNode;

/* To handle if / elif / else expressions */
typedef struct {
  NodeType type;
  Node *ifNode;
  Node *ifBlock;
  Node *elifNode;
  Node *elifBlock;
  Node *elseNode;
} IfNode;

/* For the calculate while loop */
typedef struct {
  NodeType type;
  Node *block;
  Node *condition;
} CalculateWhileNode;

/* Generic block node */
typedef struct {
  NodeType type;
  ListNode *instructions;
} BlockNode;

/* For the string data type */
typedef struct {
  NodeType type;
  char *string;
} StringNode;

/* For a single instruction */
typedef struct {
  NodeType type;
  Node *instruction;
} InstructionNode;

/* For the NOT_OP expressions */
typedef struct {
  NodeType type;
  Node *expression;
} NegationNode;

#endif