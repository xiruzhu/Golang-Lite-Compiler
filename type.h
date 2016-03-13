#ifndef __GoLiteCompiler__TYPE__H__
#define __GoLiteCompiler__TYPE__H__

#include "mem_sys.h"
#include "treeNode.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define FUNC_TYPE   10001
#define LIST_TYPE   10002
#define ALIAS_TYPE	10003

int id_generator = 0;
char err_msg[200];

typedef struct type{
	int type;
	union{
		struct{
			struct type * s_type;
		}slice_type;
		struct{
			struct type * return_type;
			struct type * params_type;
		}func_type;
		struct{
			struct type * a_type;
		}array_type;
		struct{
			char ** id_list;
			struct type ** type_list;
			int list_size;
			int list_cap;
		}struct_type;
		struct{
			struct type ** type_list;
			int list_size;
			int list_cap;
		}list_type;
		struct{
			struct type * a_type;
		}alias_type;
	}spec_type; //Special types
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
type * new_func_type(nodeAST * AST);

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
	ret->spec_type = val->spec_type;
	return ret;
}

type * new_int_type(){
	type * ret = alloc(1, sizeof(struct type));
	ret->type = VAR_INT;
	return ret;
}

type * new_float_type(){
	type * ret = alloc(1, sizeof(struct type));
	ret->type = VAR_FLOAT64;
	return ret;
}

type * new_bool_type(){
	type * ret = alloc(1, sizeof(struct type));
	ret->type = VAR_BOOL;
	return ret;
}

type * new_rune_type(){
	type * ret = alloc(1, sizeof(struct type));
	ret->type = VAR_RUNE;
	return ret;
}

type * new_string_type(){
	type * ret = alloc(1, sizeof(struct type));
	ret->type = VAR_STRING;
	return ret;
}

type * new_slice_type(nodeAST * AST){
	type * ret = alloc(1, sizeof(struct type));
	ret->type = SLICE_TYPE;
	ret->spec_type.slice_type.s_type = NULL;
	return ret;
}

type * new_array_type(nodeAST * AST){
	type * ret = alloc(1, sizeof(struct type));
	ret->type = ARRAY_TYPE;
	ret->spec_type.array_type.a_type = NULL;
	return ret;
}

type * new_func_type(nodeAST * AST){
	type * ret = alloc(1, sizeof(ret));
	ret->type = FUNC_TYPE;
	ret->spec_type.func_type.return_type = NULL;
	ret->spec_type.func_type.params_type = NULL;
	return ret;
}

type * new_list_type(nodeAST * AST){
	type * ret = alloc(1, sizeof(ret));
	ret->type = LIST_TYPE;
	ret->spec_type.list_type.type_list = alloc(8, sizeof(type *));
	ret->spec_type.list_type.list_size = 0;
	ret->spec_type.list_type.list_cap = 8;
	return ret;
}

type * new_struct_type(nodeAST * AST){
	type * ret = alloc(1, sizeof(struct type));
	ret->type = STRUCT_TYPE;
	ret->spec_type.struct_type.type_list = alloc(8, sizeof(type *));
	ret->spec_type.struct_type.id_list = alloc(8, sizeof(char *));
	ret->spec_type.struct_type.list_size = 0;
	ret->spec_type.struct_type.list_cap = 8;
	return ret;
}

type * new_alias_type(nodeAST * AST){
	type * ret = alloc(1, sizeof(struct type));
	ret->type = ARRAY_TYPE;
	ret->spec_type.alias_type.a_type = NULL;
	return ret;
}

void free_type(type * garbage){
	switch(garbage->type){
		case SLICE_TYPE: free_type(garbage->spec_type.slice_type.s_type); break;
		case ARRAY_TYPE: free_type(garbage->spec_type.array_type.a_type); break;
		case FUNC_TYPE: free_type(garbage->spec_type.func_type.return_type);
						free_type(garbage->spec_type.func_type.params_type);
						break;
		case LIST_TYPE:
						for(int i = 0; i < garbage->spec_type.list_type.list_size; i++){
						  	free_type(garbage->spec_type.list_type.type_list[i]);
						}
						break;
		case STRUCT_TYPE:
						for(int i = 0; i < garbage->spec_type.struct_type.list_size; i++){
						  	free_type(garbage->spec_type.struct_type.type_list[i]);
						}
						free(garbage->spec_type.struct_type.id_list);
						  break;
		default: break;
	}
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

/*
* Returns -1 if false
* Returns 0 if true
*/
int compare_type(type * arg0, type * arg1){
	if(arg0->type != arg1->type)
		return -1;
	switch(arg0->type){
		case ARRAY_TYPE: return compare_type(arg0->spec_type.array_type.a_type, arg1->spec_type.array_type.a_type);
		case SLICE_TYPE: return compare_type(arg0->spec_type.slice_type.s_type, arg1->spec_type.slice_type.s_type);
		case STRUCT_TYPE:
						 //Comparing the type of struct
						 //We need to test if all the ids are the same
							return 0;
		case PROG_FUNCTION:
							return 0;
		case LIST_TYPE:
							return 0;
		default:
						 return 0;
	}
}

//var_decl
//func_decl
//type_decl

#endif