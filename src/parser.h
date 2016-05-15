#ifndef PARSER_H_
#define PARSER_H_
#include "util.h"
#include "tokenizer.h"
#include "linked_list.h"

DEFSTRUCT(file_contents);
DEFSTRUCT(struct_declaration);
DEFSTRUCT(struct_member);
DEFSTRUCT(func_declaration);
DEFSTRUCT(statement);
DEFSTRUCT(parameter);
struct file_contents {
	linked_list *structs;
	linked_list *functions;
};
struct struct_declaration {
	slice name;
	linked_list *members;
	source_origin origin;
};
struct struct_member {
	slice type, name;
};
struct func_declaration {
	slice type, name;
	linked_list *parameters;
	statement *root;
};
typedef enum statement_type {OP_ADD, OP_SUB, OP_MULT, OP_DIV, OP_MOD, OP_EXP,
	OP_BIT_AND,	OP_BOOL_AND, OP_BIT_OR, OP_BOOL_OR, OP_BIT_XOR, OP_BOOL_XOR, OP_BIT_NOT, OP_BOOL_NOT,
	OP_GREATER, OP_LESS, OP_GREATER_EQUAL, OP_LESS_EQUAL, OP_EQUAL, OP_NOT_EQUAL,
	OP_SHIFT_LEFT, OP_SHIFT_RIGHT, OP_BIT_SHIFT_RIGHT,
	OP_ASSIGN, OP_INIT, OP_MEMBER, OP_GETREF, OP_DEREF, OP_INDEX,
	RETURN, BREAK, CONTINUE,
	FUNC_CALL,
	STACK_INIT, HEAP_INIT,
	IF, ELSE, ELSEIF, WHILE, FOR, FOREACH,
	BLOCK, TYPE, NAME,
	ROOT,
	STRING, CHAR, NUM,
	VALUE_TRUE, VALUE_FALSE} statement_type;
struct statement {
	slice data;
	statement_type type;
	linked_list *children;
};
file_contents analyze(parse_source tokens);
#endif
