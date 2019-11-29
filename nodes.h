#ifndef NODES_H
#define NODES_H

typedef enum {  TYPE_NULL = 1,
                TYPE_CONSTANT,
                TYPE_STRING,
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
} NodeType;

typedef enum {  DATA_NUMBER,
                DATA_STRING,
                DATA_FUNCTION,
                DATA_COORDINATES
} DataType;

typedef struct {
  NodeType type;
  DataType data;
} Node;

typedef struct {
  NodeType type;
  DataType data;
  Node *node;
  struct ListNode *next;
} ListNode;

/* Node for calculations with two
 * elements and an operand between */
typedef struct {
  NodeType type;
  DataType data;
  Node *first;
  Node *second;
  char *op;
} OperationNode;

/* For the X++ and X-- operations */
typedef struct {
  NodeType type;
  DataType data;
  Node *node;
  char *op;
} SingleOperationNode; 

/* Node for the return expression */
typedef struct {
  NodeType type;
  DataType data;
  Node *expression;
} ReturnNode;

/* For numbers --> double and integer */
typedef struct {
  NodeType type;
  DataType data;
  char *constant;
} ConstantNode;

/* For manipulation of variables */
typedef struct {
  NodeType type;
  DataType data;
  int declared;
  char *name;
  Node *stored;
  char *variable;
} VariableNode;

/* Node to print */
typedef struct {
  NodeType type;
  DataType data;
  Node *expression;
} PrintNode;

/* To handle if / elif / else expressions */
typedef struct {
  NodeType type;
  DataType data;
  Node *ifNode;
  Node *ifBlock;
  Node *elifNode;
  Node *elifBlock;
  Node *elseNode;
} IfNode;

/* For the calculate while loop */
typedef struct {
  NodeType type;
  DataType data;
  Node *block;
  Node *condition;
} CalculateWhileNode;

/* Generic block node */
typedef struct {
  NodeType type;
  DataType data;
  ListNode *instructions;
} BlockNode;

/* For the string data type */
typedef struct {
  NodeType type;
  DataType data;
  char *string;
} StringNode;

/* For a single instruction */
typedef struct {
  NodeType type;
  DataType data;
  Node *instruction;
} InstructionNode;

/* For the NOT_OP expressions */
typedef struct {
  NodeType type;
  DataType data;
  Node *expression;
} NegationNode;

#endif