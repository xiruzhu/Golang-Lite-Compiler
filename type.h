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
#define INVALID_TYPE 10004
#define LITERAL_BOOL 10005
#define TYPED_INT 10006
#define TYPED_FLOAT 10007
#define TYPED_RUNE 10008
#define TYPED_STRING 10009

#define WHITE_COLOR  "\033[1m\033[37m"
#define RED_COLOR "\033[1m\033[31m"
#define RESET_COLOR "\e[m"

int id_generator = 0;
char err_msg[256];
char extra_buf[256];

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
			char * id;
			int alias_id;
		}alias_type;
	}spec_type; //Special types
}type;

type * make_typed(type * val);
type * type_cpy(type * val);
type * new_int_type();
type * new_float_type();
type * new_bool_type();
type * new_rune_type();
type * new_string_type();
type * new_typed_int_type();
type * new_typed_float_type();
type * new_typed_rune_type();
type * new_slice_type();
type * new_array_type();
type * new_struct_type();
type * new_func_type();
type * new_alias_type();
type * new_invalid_type();

void free_type(type * garbage);

type * get_var_type(nodeAST * AST);
type * get_func_type(nodeAST * node);
type * get_typedef_type(nodeAST * node);
int compare_type(type * arg0, type * arg1);
int print_type_to_file(type * to_print, FILE * file);
int print_type_to_string(type * to_print, char * buf);
int valid_type_conversion(type * t1, type* t2);
int valid_type_comparison(type * t1, type* t2);
int valid_type_assign(type * t1, type * t2);

/*
* -----------------------------------------------------------------------------------------------------------
* Constructors and Destructors
* -----------------------------------------------------------------------------------------------------------
*/
type * make_typed(type * val){
	if(val == NULL)
		return NULL;
	if(val->type == LITERAL_RUNE)
		val->type = TYPED_RUNE;
	else if(val->type == LITERAL_INT)
		val->type = TYPED_INT;
	else if(val->type == LITERAL_FLOAT)
		val->type = TYPED_FLOAT;
	else if(val->type == LITERAL_STRING)
		val->type = TYPED_STRING;
	else if(val->type == LIST_TYPE){
		for(int i = 0; i < val->spec_type.list_type.list_size; i++){
			make_typed(val->spec_type.list_type.type_list[i]);
		}
	}
	else if(val->type == ALIAS_TYPE){
		make_typed(val->spec_type.alias_type.a_type);
	}
	else if(val->type == ARRAY_TYPE){
		make_typed(val->spec_type.array_type.a_type);
	}
	else if(val->type == SLICE_TYPE){
		make_typed(val->spec_type.slice_type.s_type);
	}
	else if(val->type == STRUCT_TYPE){
		for(int i = 0; i < val->spec_type.struct_type.list_size; i++){
			make_typed(val->spec_type.struct_type.type_list[i]);
		}
	}
	else if(val->type == FUNC_TYPE){
		make_typed(val->spec_type.func_type.params_type);
		make_typed(val->spec_type.func_type.return_type);
	}
	return val;
}

type * type_cpy(type * val){
	if(val == NULL)
		new_invalid_type();
	type * ret = alloc(1, sizeof(struct type));
	if(val->type == LITERAL_RUNE)
		ret->type = TYPED_RUNE;
	else if(val->type == LITERAL_INT)
		ret->type = TYPED_INT;
	else if(val->type == LITERAL_FLOAT)
		ret->type = TYPED_FLOAT;
	else if(val->type == LITERAL_STRING)
		ret->type = TYPED_STRING;
	else
		ret->type = val->type;
	ret->spec_type = val->spec_type;
	return ret;
}

type * new_invalid_type(){
	type * ret = alloc(1, sizeof(struct type));
	ret->type = INVALID_TYPE;
	return ret;
}

type * new_int_type(){
	type * ret = alloc(1, sizeof(struct type));
	ret->type = LITERAL_INT;
	return ret;
}

type * new_float_type(){
	type * ret = alloc(1, sizeof(struct type));
	ret->type = LITERAL_FLOAT;
	return ret;
}

type * new_bool_type(){
	type * ret = alloc(1, sizeof(struct type));
	ret->type = LITERAL_BOOL;
	return ret;
}

type * new_rune_type(){
	type * ret = alloc(1, sizeof(struct type));
	ret->type = LITERAL_RUNE;
	return ret;
}

type * new_string_type(){
	type * ret = alloc(1, sizeof(struct type));
	ret->type = LITERAL_STRING;
	return ret;
}

type * new_typed_rune_type(){
	type * ret = alloc(1, sizeof(struct type));
	ret->type = TYPED_RUNE;
	return ret;
}

type * new_typed_int_type(){
	type * ret = alloc(1, sizeof(struct type));
	ret->type = TYPED_INT;
	return ret;
}

type * new_typed_float_type(){
	type * ret = alloc(1, sizeof(struct type));
	ret->type = TYPED_FLOAT;
	return ret;
}

type * new_typed_string_type(){
	type * ret = alloc(1, sizeof(struct type));
	ret->type = TYPED_STRING;
	return ret;
}


type * new_slice_type(){
	type * ret = alloc(1, sizeof(struct type));
	ret->type = SLICE_TYPE;
	ret->spec_type.slice_type.s_type = NULL;
	return ret;
}

type * new_array_type(){
	type * ret = alloc(1, sizeof(struct type));
	ret->type = ARRAY_TYPE;
	ret->spec_type.array_type.a_type = NULL;
	return ret;
}

type * new_func_type(){
	type * ret = alloc(1, sizeof(ret));
	ret->type = FUNC_TYPE;
	ret->spec_type.func_type.return_type = NULL;
	ret->spec_type.func_type.params_type = NULL;
	return ret;
}

type * new_list_type(){
	type * ret = alloc(1, sizeof(ret));
	ret->type = LIST_TYPE;
	ret->spec_type.list_type.type_list = alloc(8, sizeof(type *));
	ret->spec_type.list_type.list_size = 0;
	ret->spec_type.list_type.list_cap = 8;
	return ret;
}

type * new_struct_type(){
	type * ret = alloc(1, sizeof(struct type));
	ret->type = STRUCT_TYPE;
	ret->spec_type.struct_type.type_list = alloc(8, sizeof(type *));
	ret->spec_type.struct_type.id_list = alloc(8, sizeof(char *));
	ret->spec_type.struct_type.list_size = 0;
	ret->spec_type.struct_type.list_cap = 8;
	return ret;
}

type * new_alias_type(){
	type * ret = alloc(1, sizeof(struct type));
	ret->type = ALIAS_TYPE;
	ret->spec_type.alias_type.a_type = NULL;
	ret->spec_type.alias_type.id = NULL;
	ret->spec_type.alias_type.alias_id = id_generator++;
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

/*
* Returns -1 if false
* Returns 0 if true
*/
int compare_type(type * arg0, type * arg1){
	if(arg0 == NULL || arg1 == NULL)
		return -1;
	if(arg0->type == arg1->type)
		return 0;
	switch(arg0->type){
		case TYPED_INT:   if(arg1->type == LITERAL_RUNE || arg1->type == LITERAL_INT || arg1->type == LITERAL_FLOAT || arg1->type == TYPED_INT)
								return 0;
							return -1;
		case TYPED_RUNE:	if(arg1->type == LITERAL_RUNE || arg1->type == LITERAL_INT || arg1->type == LITERAL_FLOAT || arg1->type == TYPED_RUNE)
								return 0;
							return -1;
		case TYPED_STRING:if(arg1->type == LITERAL_STRING || arg1->type == TYPED_STRING)
								return 0;
							return -1;
		case TYPED_FLOAT: if(arg1->type == LITERAL_INT || arg1->type == LITERAL_FLOAT || arg1->type == LITERAL_RUNE || arg1->type == TYPED_FLOAT)
								return 0;
							return -1;
		case LITERAL_INT: if(arg1->type == TYPED_INT || arg1->type == TYPED_RUNE || arg1->type == TYPED_FLOAT || arg1->type == LITERAL_RUNE || arg1->type == LITERAL_INT || arg1->type == LITERAL_FLOAT)
							return 0;
						  return -1;
		case LITERAL_RUNE: if(arg1->type == TYPED_INT || arg1->type == TYPED_RUNE || arg1->type == TYPED_FLOAT || arg1->type == LITERAL_RUNE || arg1->type == LITERAL_INT || arg1->type == LITERAL_FLOAT)
							return 0;
						  return -1;
		case LITERAL_FLOAT:	if(arg1->type == TYPED_INT || arg1->type == TYPED_RUNE || arg1->type == TYPED_FLOAT || arg1->type == LITERAL_RUNE || arg1->type == LITERAL_INT || arg1->type == LITERAL_FLOAT)
							return 0;
						  return -1;
		case LITERAL_STRING: if(arg1->type == LITERAL_STRING || arg1->type == TYPED_STRING)
								return 0;
							return -1;
		case ARRAY_TYPE: 	return compare_type(arg0->spec_type.array_type.a_type, arg1->spec_type.array_type.a_type);
		case SLICE_TYPE: 	return compare_type(arg0->spec_type.slice_type.s_type, arg1->spec_type.slice_type.s_type);
		case STRUCT_TYPE:
						 //Comparing the type of struct
						 //We need to test if all the ids are the same
							if(arg0->spec_type.struct_type.list_size != arg1->spec_type.struct_type.list_size)
								return -1;
							for(int i = 0; i < arg0->spec_type.struct_type.list_size; i++){
								if(strcmp(arg0->spec_type.struct_type.id_list[i], arg1->spec_type.struct_type.id_list[i]) == -1)
									return -1;
								if(compare_type(arg0->spec_type.struct_type.type_list[i], arg1->spec_type.struct_type.type_list[i]) == -1)
									return -1;
							}
							return 0;
		case FUNC_TYPE:
							if(compare_type(arg0->spec_type.func_type.params_type, arg1->spec_type.func_type.params_type) == -1)
								return -1;
							if(compare_type(arg0->spec_type.func_type.return_type, arg1->spec_type.func_type.return_type) == -1)
								return -1;
							return 0;
		case ALIAS_TYPE:
							if(arg0->spec_type.alias_type.alias_id == arg1->spec_type.alias_type.alias_id)
								return 0;
							return compare_type(arg0->spec_type.alias_type.a_type, arg1->spec_type.alias_type.a_type);
							/*
							if(strcmp(arg0->spec_type.alias_type.id,arg1->spec_type.alias_type.id) != 0)
								return -1;
							if(compare_type(arg0->spec_type.alias_type.a_type, arg1->spec_type.alias_type.a_type) != 0)
								return -1;
							*/
							//return 0;
		case LIST_TYPE:
							if(arg0->spec_type.list_type.list_size != arg1->spec_type.list_type.list_size)
								return -1;
							for(int i = 0; i < arg0->spec_type.list_type.list_size; i++){
								if(compare_type(arg0->spec_type.list_type.type_list[i], arg1->spec_type.list_type.type_list[i]) == -1)
									return -1;
							}
							return 0;
		case INVALID_TYPE: 	return -1;
		default:
						 return -1;
	}
}

int print_type_to_file(type * to_print, FILE * file){
	switch(to_print->type){
	    case LITERAL_INT: fprintf(file, "Int Type"); break;
        case LITERAL_FLOAT: fprintf(file, "Float Type"); break;
        case LITERAL_RUNE: fprintf(file, "Rune Type"); break;
        case LITERAL_STRING: fprintf(file, "String Type"); break;
        case TYPED_INT: fprintf(file, "Int Type"); break;
        case TYPED_FLOAT: fprintf(file, "Float Type"); break;
        case TYPED_RUNE: fprintf(file, "Rune Type"); break;
        case TYPED_STRING: fprintf(file, "String Type"); break;
        case LITERAL_BOOL: fprintf(file, "Bool Type"); break;
		case ARRAY_TYPE: fprintf(file, "Array Type[");
						 print_type_to_file(to_print->spec_type.array_type.a_type, file);
						 fprintf(file, "] ");
						 break;
		case SLICE_TYPE: fprintf(file, "Slice Type[");
						 print_type_to_file(to_print->spec_type.slice_type.s_type, file);
						 fprintf(file, "] ");
						 break;
		case STRUCT_TYPE: fprintf(file, "Struct Type"); break;
		case FUNC_TYPE: fprintf(file, "Function Type"); break;
		case ALIAS_TYPE: fprintf(file, "Alias Type %s:", to_print->spec_type.alias_type.id);
						 print_type_to_file(to_print->spec_type.alias_type.a_type, file);
						 break;
		case LIST_TYPE: fprintf(file, "( ");
						for(int i = 0; i < to_print->spec_type.list_type.list_size; i++){
							print_type_to_file(to_print->spec_type.list_type.type_list[i], file);
							if(i != to_print->spec_type.list_type.list_size -1)
							fprintf(file, " , ");
						}
						fprintf(file, " )");
						break; //Technically List doesn't have a type
		case INVALID_TYPE: fprintf(file, "Invalid Type"); break;
		default: break;
	}
	return 0;
}

int print_type_to_string(type * to_print, char * buf){
	switch(to_print->type){
	    case LITERAL_INT: sprintf(buf, "Int Type"); break;
        case LITERAL_FLOAT: sprintf(buf, "Float Type"); break;
        case LITERAL_RUNE: sprintf(buf, "Rune Type"); break;
        case LITERAL_STRING: sprintf(buf, "String Type"); break;
        case LITERAL_BOOL: sprintf(buf, "Bool Type"); break;
        case TYPED_INT: sprintf(buf, "Int Type"); break;
        case TYPED_FLOAT: sprintf(buf, "Float Type"); break;
        case TYPED_RUNE: sprintf(buf, "Rune Type"); break;
        case TYPED_STRING: sprintf(buf, "String Type"); break;
		case ARRAY_TYPE:
						 print_type_to_string(to_print->spec_type.array_type.a_type, extra_buf);
						 sprintf(buf, "Array Type[%s]", extra_buf);
						 break;
		case SLICE_TYPE:
						 print_type_to_string(to_print->spec_type.array_type.a_type, extra_buf);
						 sprintf(buf, "Slice Type[%s]", extra_buf);
						 break;
						 break;
		case STRUCT_TYPE: sprintf(buf, "Struct Type"); break;
		case FUNC_TYPE: sprintf(buf, "Function Type"); break;
		case ALIAS_TYPE:
						 print_type_to_string(to_print->spec_type.alias_type.a_type, extra_buf);
				         sprintf(buf, "Alias Type %s:%s", to_print->spec_type.alias_type.id, extra_buf);
				         break;
		case LIST_TYPE:{
						char buffer[256];
						int incr;
						incr = sprintf(buffer, "( ");
						for(int i = 0; i < to_print->spec_type.list_type.list_size; i++){
							print_type_to_string(to_print->spec_type.list_type.type_list[i], buf);
							incr += sprintf(buffer + incr, "%s", buf);
							if(i != to_print->spec_type.list_type.list_size -1)
								incr += sprintf(buffer + incr, " , ");
						}
						sprintf(buffer + incr, " )");
						sprintf(buf, "%s", buffer);

						break; //Technically List doesn't have a type
					}
		case INVALID_TYPE: sprintf(buf, "Invalid Type"); break;
		default: break;
	}
	return 0;
}

/*
* Returns 0 if the two types are interchangeable
* Returns -1 if not
* Ordering does matter, since i am assuming t1 = t2
*/
int valid_type_conversion(type * t1, type * t2){
	//Having untyped values on the left will result in error
	switch(t1->type){
		case LITERAL_INT: switch(t2->type){
						case LITERAL_INT: return 0;
						case LITERAL_FLOAT: return 0;
						case LITERAL_RUNE: return 0;
						case TYPED_INT: return 0;
						case TYPED_FLOAT: return 0;
						case TYPED_RUNE: return 0;
						case ALIAS_TYPE: return valid_type_conversion(t1, t2->spec_type.alias_type.a_type);
						default: return -1;
						}
		case TYPED_INT:	switch(t2->type){
						case LITERAL_INT: return 0;
						case LITERAL_FLOAT: return 0;
						case LITERAL_RUNE: return 0;
						case TYPED_INT: return 0;
						case TYPED_FLOAT: return 0;
						case TYPED_RUNE: return 0;
						case ALIAS_TYPE: return valid_type_conversion(t1, t2->spec_type.alias_type.a_type);
						default: return -1;
						}
		case LITERAL_BOOL:
				switch(t2->type){
						case LITERAL_BOOL: return 0;
						case ALIAS_TYPE: return valid_type_conversion(t1, t2->spec_type.alias_type.a_type);
						default: return -1;
						}
		case TYPED_FLOAT: switch(t2->type){
						case LITERAL_INT: return 0;
						case LITERAL_FLOAT: return 0;
						case LITERAL_RUNE: return 0;
						case TYPED_INT: return 0;
						case TYPED_FLOAT: return 0;
						case TYPED_RUNE: return 0;
						case ALIAS_TYPE: return valid_type_conversion(t1, t2->spec_type.alias_type.a_type);
						default: return -1;
						}
		case LITERAL_FLOAT:
				switch(t2->type){
						case LITERAL_INT: return 0;
						case LITERAL_FLOAT: return 0;
						case LITERAL_RUNE: return 0;
						case TYPED_INT: return 0;
						case TYPED_FLOAT: return 0;
						case TYPED_RUNE: return 0;
						case ALIAS_TYPE: return valid_type_conversion(t1, t2->spec_type.alias_type.a_type);
						default: return -1;
						}
		case TYPED_STRING: switch(t2->type){
						case LITERAL_INT: return 0;
						case LITERAL_FLOAT: return 0;
						case LITERAL_RUNE: return 0;
						case TYPED_INT: return 0;
						case TYPED_FLOAT: return 0;
						case TYPED_RUNE: return 0;
						case ALIAS_TYPE: return valid_type_conversion(t1, t2->spec_type.alias_type.a_type);
						default: return -1;
						}
		case LITERAL_STRING:
				switch(t2->type){
						case ALIAS_TYPE: return valid_type_conversion(t1, t2->spec_type.alias_type.a_type);
						case LITERAL_STRING: return 0;
						default: return -1;
						}
		case TYPED_RUNE: switch(t2->type){
						case LITERAL_INT: return 0;
						case LITERAL_FLOAT: return 0;
						case LITERAL_RUNE: return 0;
						case TYPED_INT: return 0;
						case TYPED_FLOAT: return 0;
						case TYPED_RUNE: return 0;
						case ALIAS_TYPE: return valid_type_conversion(t1, t2->spec_type.alias_type.a_type);
						default: return -1;
						}
		case LITERAL_RUNE:
				switch(t2->type){
						case LITERAL_INT: return 0;
						case LITERAL_FLOAT: return 0;
						case LITERAL_RUNE: return 0;
						case TYPED_INT: return 0;
						case TYPED_FLOAT: return 0;
						case TYPED_RUNE: return 0;
						case ALIAS_TYPE: return valid_type_conversion(t1, t2->spec_type.alias_type.a_type);
						default: return -1;
						}
		case ALIAS_TYPE:
						return valid_type_conversion(t1->spec_type.alias_type.a_type, t2);
		default: return -1;
	}
}

int valid_type_assign(type * t1, type * t2){
	//Having untyped values on the left will result in error
	switch(t1->type){
		case LITERAL_INT: return -1;
		case TYPED_INT:	switch(t2->type){
						case LITERAL_INT: return 0;
						case LITERAL_RUNE: return 0;
						case TYPED_INT: return 0;
						case ALIAS_TYPE: return valid_type_conversion(t1, t2->spec_type.alias_type.a_type);
						default: return -1;
						}
		case LITERAL_BOOL:
				switch(t2->type){
						case LITERAL_BOOL: return 0;
						case ALIAS_TYPE: return valid_type_conversion(t1, t2->spec_type.alias_type.a_type);
						default: return -1;
						}
		case TYPED_FLOAT:
						switch(t2->type){
						case LITERAL_INT: return 0;
						case LITERAL_FLOAT: return 0;
						case LITERAL_RUNE: return 0;
						case TYPED_FLOAT: return 0;
						case ALIAS_TYPE: return valid_type_conversion(t1, t2->spec_type.alias_type.a_type);
						default: return -1;
						}
		case LITERAL_FLOAT: return -1;
		case TYPED_STRING:
						switch(t2->type){
							case LITERAL_STRING: return 0;
							case TYPED_STRING: return 0;
							case ALIAS_TYPE: return valid_type_conversion(t1, t2->spec_type.alias_type.a_type);
							default: return -1;
						}
		case LITERAL_STRING:return -1;
		case TYPED_RUNE: switch(t2->type){
						case LITERAL_INT: return 0;
						case LITERAL_RUNE: return 0;
						case TYPED_FLOAT: return 0;
						case ALIAS_TYPE: return valid_type_conversion(t1, t2->spec_type.alias_type.a_type);
						default: return -1;
						}
		case LITERAL_RUNE: return -1;
		case ALIAS_TYPE:
						return valid_type_conversion(t1->spec_type.alias_type.a_type, t2);
		default: return -1;
	}
}

int valid_type_ordered(type * t1, type* t2){
	switch(t1->type){
		case LITERAL_INT:
				switch(t2->type){
						case LITERAL_INT: return 0;
						case LITERAL_RUNE: return 0;
						case TYPED_INT: return 0;
						case ALIAS_TYPE:
							return valid_type_ordered(t1, t2->spec_type.alias_type.a_type);
						default: return -1;
						}
		case LITERAL_FLOAT:
				switch(t2->type){
						case LITERAL_INT: return 0;
						case LITERAL_RUNE: return 0;
						case LITERAL_FLOAT: return 0;
						case TYPED_FLOAT: return 0;
						case ALIAS_TYPE:
							return valid_type_ordered(t1, t2->spec_type.alias_type.a_type);
						default: return -1;
						}
		case LITERAL_STRING:
				switch(t2->type){
						case LITERAL_STRING: return 0;
						case TYPED_STRING: return 0;
						case ALIAS_TYPE:
							return valid_type_ordered(t1, t2->spec_type.alias_type.a_type);
						default: return -1;
						}
		case LITERAL_RUNE:
					switch(t2->type){
						case LITERAL_RUNE: return 0;
						case LITERAL_INT: return 0;
						case TYPED_RUNE: return 0;
						case ALIAS_TYPE:
							return valid_type_ordered(t1, t2->spec_type.alias_type.a_type);
						default: return -1;
						}
		case TYPED_INT: switch(t2->type){
						case LITERAL_INT: return 0;
						case LITERAL_RUNE: return 0;
						case LITERAL_FLOAT: return 0;
						case TYPED_FLOAT: return 0;
						case ALIAS_TYPE:
							return valid_type_ordered(t1, t2->spec_type.alias_type.a_type);
						default: return -1;
						}
		case TYPED_STRING:
						switch(t2->type){
						case LITERAL_STRING: return 0;
						case TYPED_STRING: return 0;
						case ALIAS_TYPE:
							return valid_type_ordered(t1, t2->spec_type.alias_type.a_type);
						default: return -1;
						}
		case TYPED_FLOAT:
						switch(t2->type){
						case LITERAL_INT: return 0;
						case LITERAL_RUNE: return 0;
						case LITERAL_FLOAT: return 0;
						case TYPED_FLOAT: return 0;
						case ALIAS_TYPE:
							return valid_type_ordered(t1, t2->spec_type.alias_type.a_type);
						default: return -1;
						}
		case TYPED_RUNE: switch(t2->type){
						case LITERAL_RUNE: return 0;
						case LITERAL_INT: return 0;
						case TYPED_RUNE: return 0;
						case ALIAS_TYPE:
							return valid_type_ordered(t1, t2->spec_type.alias_type.a_type);
						default: return -1;
						}

		case ALIAS_TYPE:
				return valid_type_ordered(t1->spec_type.alias_type.a_type, t2);
		default: return -1;
	}
}

int valid_type_numeric(type * arg0){
	switch(arg0->type){
		case LITERAL_RUNE: return 0;
		case LITERAL_INT: return 0;
		case LITERAL_FLOAT: return 0;
		case TYPED_INT: return 0;
		case TYPED_FLOAT: return 0;
		case TYPED_RUNE: return 0;
		default: return -1;
	}
}

type * get_alias_type(type * arg0){
	if(arg0->type != ALIAS_TYPE)
		return arg0;
	else{
		return get_alias_type(arg0->spec_type.alias_type.a_type);
	}
}
//var_decl
//func_decl
//type_decl

#endif