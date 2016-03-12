#ifndef __GoLiteCompiler__TYPE__H__
#define __GoLiteCompiler__TYPE__H__

#include "mem_sys.h"
#include "treeNode.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define EXPR_TYPE 	10000
int id_generator = 0;
char err_msg[200];

typedef struct type{
	int type;
	char ** id;          //This is for struct system
	struct type ** list; //A list of types
	int list_size;
	int list_cap;

	int compare_id;
}type;

type * new_int_type();
type * new_float_type();
type * new_bool_type();
type * new_rune_type();
type * new_string_type();
type * new_basic_type(nodeAST * AST);
type * new_slice_type(nodeAST * AST);
type * new_array_type(nodeAST * AST);
type * new_struct_type(nodeAST * AST);

void free_type(type * garbage);

type * get_var_type(nodeAST * AST);
type * get_func_type(nodeAST * node);
type * get_typedef_type(nodeAST * node);
int compare_type(type * arg0, type * arg1);
int print_type(type * to_print, FILE * file);

/*
* -----------------------------------------------------------------------------------------------------------
* Constructors and Destructors
* -----------------------------------------------------------------------------------------------------------
*/

type * type_cpy(type * val){
	type * ret = alloc(1, sizeof(struct type));
	ret->type = val->type;
	ret->id = val->id;
	ret->list = val->list;
	ret->list_size = 0;
	ret->list_cap = 0;
	if(ret->type == STRUCT_TYPE || ret->type == PROG_FUNCTION || ret->type == EXPR_TYPE)
		ret->compare_id = val->compare_id;
	return ret;
}

type * new_int_type(){
	type * ret = alloc(1, sizeof(struct type));
	ret->type = VAR_INT;
	ret->id = NULL;
	ret->list_size = 0;
	ret->list_cap = 0;
	ret->list = NULL;
	return ret;
}

type * new_float_type(){
	type * ret = alloc(1, sizeof(struct type));
	ret->type = VAR_FLOAT64;
	ret->id = NULL;
	ret->list_size = 0;
	ret->list_cap = 0;
	ret->list = NULL;
	return ret;
}

type * new_bool_type(){
	type * ret = alloc(1, sizeof(struct type));
	ret->type = VAR_BOOL;
	ret->id = NULL;
	ret->list_size = 0;
	ret->list_cap = 0;
	ret->list = NULL;
	return ret;
}

type * new_rune_type(){
	type * ret = alloc(1, sizeof(struct type));
	ret->type = VAR_RUNE;
	ret->id = NULL;
	ret->list_size = 0;
	ret->list_cap = 0;
	ret->list = NULL;
	return ret;
}

type * new_string_type(){
	type * ret = alloc(1, sizeof(struct type));
	ret->type = VAR_STRING;
	ret->id = NULL;
	ret->list = NULL;
	ret->list_size = 0;
	ret->list_cap = 0;
	ret->list = NULL;
	return ret;
}

type * new_slice_type(nodeAST * AST){
	type * ret = alloc(1, sizeof(struct type));
	ret->type = SLICE_TYPE;
	ret->id = NULL;
	ret->list_size = 1;
	ret->list_cap = 1;
	ret->list = alloc(1, sizeof(struct type *));
	ret->list[0] = get_var_type(AST->nodeValue.arrayType.type);
	return ret;
}

type * new_array_type(nodeAST * AST){
	type * ret = alloc(1, sizeof(struct type));
	ret->type = ARRAY_TYPE;
	ret->id = NULL;
	ret->list_size = 1;
	ret->list_cap = 1;
	ret->list = alloc(1, sizeof(struct type *));
	ret->list[0] = get_var_type(AST->nodeValue.arrayType.type);
	return ret;
}

type * new_struct_type(nodeAST * AST){
	type * ret = alloc(1, sizeof(struct type));
	ret->type = STRUCT_TYPE;
	ret->id = (char **)alloc(8, sizeof(char *));
	ret->list = (type **)alloc(8, sizeof(type *));
	ret->list_size = 0;
	ret->list_cap = 8;
	ret->compare_id++;

	nodeAST * list = AST->nodeValue.structType.structDec; //This is the field_decl list, which we need to add
	nodeAST * id_list;
	type * added;

	for(nodeAST * i = list; i != NULL; i = i->nodeValue.structTypeDecList.next){
		added = get_var_type(i->nodeValue.structTypeDecList.declare->nodeValue.structTypeDec.type);
		id_list = i->nodeValue.structTypeDecList.declare->nodeValue.structTypeDec.identifierList;
		for(nodeAST * j = id_list; j != NULL; j = j->nodeValue.identifierList.next){
			ret->list[ret->list_size] = type_cpy(added);
			ret->id[ret->list_size++] = j->nodeValue.identifierList.identifier->nodeValue.identifier;
			if(ret->list_size == ret->list_cap){
				ret->list = ralloc(ret->list, ret->list_size * 2 * sizeof(char *));
				ret->id = ralloc(ret->id, ret->list_size * 2 * sizeof(char *));
			}
		}
		free(added);
	}
	return ret;
}

void free_type(type * garbage){
	free(garbage->id);
	free(garbage->list);
	free(garbage);
}

type * get_basic_type(nodeAST * node){
		switch(node->nodeValue.basicType){
	    case BASIC_INT: return new_int_type();
        case BASIC_FLOAT: return new_float_type();
        case BASIC_RUNE: return new_rune_type();
        case BASIC_STRING: return new_string_type();
        case BASIC_BOOL: return new_bool_type();
        default: return NULL;
    	}
}

type * get_var_type(nodeAST * node){
	switch(node->nodeType){
		case LITERAL_INT: return new_int_type();
		case LITERAL_FLOAT: return new_float_type();
		case LITERAL_RUNE: return new_rune_type();
		case LITERAL_STRING: return new_string_type();
		case BASIC_TYPE: return new_basic_type(node);
        case ARRAY_TYPE: return new_array_type(node);
        case SLICE_TYPE: return new_slice_type(node);
        case STRUCT_TYPE: return new_struct_type(node);
        case PROG_FUNCTION: return get_func_type(node);
        default: return NULL;
	}
}

type * get_func_type(nodeAST * node){
	if(node->nodeType != PROG_FUNCTION){
		sprintf(err_msg, "Invalid Node Type given to get_func_type");
		return NULL;
	}
	type * ret = (type *)alloc(1, sizeof(type));
	ret->type = PROG_FUNCTION;
	ret->id = (char **)alloc(8, sizeof(char *));
	ret->list = (type **)alloc(8, sizeof(type *));
	ret->list_size = 0;
	ret->list_cap = 8;
	ret->compare_id++;

	// func test
	//Test if we have a return type
	//The first list[0] will always store the return type!

	if(node->nodeValue.function.type != NULL)
		ret->list[0] = get_var_type(node->nodeValue.function.type);

	ret->id[ret->list_size++] = node->nodeValue.function.identifier->nodeValue.identifier;

	//Next, we need to add the params and their id to the type information
	nodeAST * current = node->nodeValue.function.pramList;
	nodeAST * id_list;
	type * added;
	if(current != NULL){
		for(nodeAST * i = current; i != NULL; i = i->nodeValue.pramDeclareList.next){
			id_list = i->nodeValue.pramDeclareList.pram->nodeValue.pramDeclare.idList;
			added = get_var_type(i->nodeValue.pramDeclareList.pram->nodeValue.pramDeclare.type);
			for(nodeAST * j = id_list; j != NULL; j = j->nodeValue.identifierList.next){
				ret->list[ret->list_size] = type_cpy(added);
				ret->id[ret->list_size++] = j->nodeValue.identifierList.identifier->nodeValue.identifier;
				if(ret->list_size == ret->list_cap){
					ret->list = ralloc(ret->list, ret->list_size * 2 * sizeof(char *));
					ret->id = ralloc(ret->id, ret->list_size * 2 * sizeof(char *));
				}
			}
			free(added);
		}
	}
    return ret;
}
/*
* TO DO...
* Requires Symbol Table
*/

type * get_expr_type(nodeAST * node){
	if(node->nodeType != EXPR_UTILITY_EXPRLIST){
		sprintf(err_msg, "Invalid Node Type given to get_expr_type");
		return NULL;
	}

	for(nodeAST * i = node; i != NULL; i = node->nodeValue.exprList.next){
		switch(i->nodeValue.exprList.expr->nodeType){
			case LITERAL_INT: printf("Test\n");
		}
	}
}

/*
* Returns -1 if false
* Returns 0 if true
*/
int compare_type(type * arg0, type * arg1){
	if(arg0->type != arg1->type)
		return -1;
	switch(arg0->type){
		case ARRAY_TYPE: return compare_type(arg0->list[0], arg1->list[0]);
		case SLICE_TYPE: return compare_type(arg0->list[0], arg1->list[0]);
		case STRUCT_TYPE:
						 if(arg0->compare_id == arg1->compare_id)
						 	return 0;
						 return -1;
		case PROG_FUNCTION:
						if(arg0->compare_id == arg1->compare_id)
						 	return 0;
						 return -1;
		case EXPR_TYPE:
						if(arg0->compare_id == arg1->compare_id)
						 	return 0;
						 return -1;
		default:
						 return 0;
	}
}

//var_decl
//func_decl
//type_decl

#endif