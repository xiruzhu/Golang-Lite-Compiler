#ifndef __GoLiteCompiler__TYPECHECK__H__
#define __GoLiteCompiler__TYPECHECK__H__

#include "symbol_table.h"
#include "type.h"
#include "mem_sys.h"
#include "treeNode.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_SIZE	2048
#define MAX_ID_LENGTH	512
#define MAX_ERR_MSG		512
#define WHITE_COLOR  "\033[1m\033[37m"
#define RED_COLOR "\033[1m\033[31m"
#define RESET_COLOR "\e[m"
#define FILE_PATH	"log.txt"

extern nodeAST* _ast;

int scope_flag;
FILE * stream;

char err_buf[MAX_ERR_MSG];
char type_buf[MAX_ERR_MSG];
char type_buf_extra[MAX_ERR_MSG];

struct type_check_data * tcsystem;

struct msg_list head;
struct msg_list * current;

struct func_block_queue * current_queue;

typedef struct msg_list{
	size_t line;
	char * msg;
	struct msg_list * next;
}msg_list;

typedef struct type_check_data{
	sym_tbl * current_tbl; //Current scope we are working with
	sym_tbl * root_tbl;
	int hash_table_size;
	int level;
}type_check;

typedef struct func_block_queue{
	sym_tbl * scope;
	nodeAST * block;
	struct func_block_queue * next;
}fn_blk_que;

int first_pass;
/*
* Method List
* ___________________________________________________________________________________________________________
*/
type_check * new_type_check(int size);
void free_type_check(type_check *);
void free_msg_list(msg_list *);
int add_to_queue(nodeAST * node, sym_tbl * new_scope);

int add_msg(char * msg, msg_list *);
int add_msg_line(char * msg, msg_list *, size_t line);
int print_err_msg(msg_list head);
int type_check_prog(nodeAST * node, int scoped_flag, FILE * stream);
int type_check_prog_list(nodeAST * node, sym_tbl * scope);
int type_check_func(nodeAST * node, sym_tbl * scope);
int type_check_type_decl_list(nodeAST * node, sym_tbl * scope);
type * type_check_type(nodeAST * node, sym_tbl * scope);
int type_check_var_decl_list(nodeAST * node , sym_tbl * scope);
int type_check_var_decl(nodeAST * node , sym_tbl * scope);
type * type_check_expr(nodeAST * node, sym_tbl * scope);
type * type_check_expr_list(nodeAST * node, sym_tbl * scope);
type * type_check_params_list(nodeAST * node, sym_tbl * scope);
int type_check_block(nodeAST * node, sym_tbl * scope);
type * type_basic_type(nodeAST * node);
int type_check_slice_expr(nodeAST * node, sym_tbl * scope);

type * type_check_alias_type(nodeAST * node, sym_tbl * scope);
type * type_check_expr_id(nodeAST * node, sym_tbl * scope);
type * type_check_expr_func(nodeAST * node, sym_tbl * scope);
type * type_check_expr_index(nodeAST * node, sym_tbl * scope);
type * type_check_expr_cast(nodeAST * node, sym_tbl * scope);
type * type_check_expr_select(nodeAST * node, sym_tbl * scope);
type * type_check_expr_slice(nodeAST * node, sym_tbl * scope);
type * type_check_expr_mul(nodeAST * node, sym_tbl * scope);
type * type_check_expr_div(nodeAST * node, sym_tbl * scope);
type * type_check_expr_mod(nodeAST * node, sym_tbl * scope);
type * type_check_expr_sub(nodeAST * node, sym_tbl * scope);
type * type_check_expr_add(nodeAST * node, sym_tbl * scope);
type * type_check_expr_and(nodeAST * node, sym_tbl * scope);
type * type_check_expr_or(nodeAST * node, sym_tbl * scope);
type * type_check_expr_xor(nodeAST * node, sym_tbl * scope);
type * type_check_expr_bitOr(nodeAST * node, sym_tbl * scope);
type * type_check_expr_lshift(nodeAST * node, sym_tbl * scope);
type * type_check_expr_rshift(nodeAST * node, sym_tbl * scope);
type * type_check_expr_bitAnd(nodeAST * node, sym_tbl * scope);
type * type_check_expr_bitAndNot(nodeAST * node, sym_tbl * scope);
type * type_check_expr_unary_pos(nodeAST * node, sym_tbl * scope);
type * type_check_expr_unary_neg(nodeAST * node, sym_tbl * scope);
type * type_check_expr_bitNot(nodeAST * node, sym_tbl * scope);
type * type_check_expr_not(nodeAST * node, sym_tbl * scope);
type * type_check_expr_eq(nodeAST * node, sym_tbl * scope);
type * type_check_expr_neq(nodeAST * node, sym_tbl * scope);
type * type_check_expr_lt(nodeAST * node, sym_tbl * scope);
type * type_check_expr_gt(nodeAST * node, sym_tbl * scope);
type * type_check_expr_lteq(nodeAST * node, sym_tbl * scope);
type * type_check_expr_gteq(nodeAST * node, sym_tbl * scope);
type * type_check_expr_append(nodeAST * node, sym_tbl * scope);
int type_check_stmt(nodeAST * node, sym_tbl * scope);
int type_check_print_stmt(nodeAST * node, sym_tbl * scope);
int type_check_ret_stmt(nodeAST * node, sym_tbl * scope);
int type_check_if_stmt(nodeAST * node, sym_tbl * scope);
int type_check_if_cond(nodeAST * node, sym_tbl * scope);
int type_check_if_else_stmt(nodeAST * node, sym_tbl * scope);
int type_check_simple_stmt(nodeAST * node, sym_tbl * scope);
int type_check_switch_stmt(nodeAST * node, sym_tbl * scope);
int type_check_for_stmt(nodeAST * node, sym_tbl * scope);
int type_check_short_decl(nodeAST * node, sym_tbl * scope);

msg_list * prepare_id_list(nodeAST * node);
/*
* -----------------------------------------------------------------------------------------------------------
* Constructors and Destructors
* -----------------------------------------------------------------------------------------------------------
*/

type_check * new_type_check(int size){

	type_check * ret = (type_check *)alloc(1, sizeof(type_check));

	ret->hash_table_size = size;
	ret->current_tbl = new_sym_tbl(size);
	ret->root_tbl = ret->current_tbl;
	ret->level = 0;
	//This will be our global scope symbol table, the parent of all symbol tables
	//Now we need to add the two precompiled values, true and false
	sym_tbl_add_entry(new_tbl_entry("true", 0, NULL, new_bool_type()), ret->current_tbl);
	sym_tbl_add_entry(new_tbl_entry("false", 0, NULL, new_bool_type()), ret->current_tbl);
	sym_tbl_add_entry(new_tbl_entry("_", 0, NULL, new_underscore_type()), ret->current_tbl);
	current = &head;
	current->msg = NULL;

	return ret;
}

void free_type_check(type_check * val){
	free_sym_tbl(val->root_tbl);
	free(val);
}

void free_msg_list(msg_list * head){
	if(head != NULL){
		free(head->msg);
		free_msg_list(head->next);
	}
}


/*
* -----------------------------------------------------------------------------------------------------------
* Methods
* -Build up the symbol table
* -type_check
* -----------------------------------------------------------------------------------------------------------
*/

int add_msg(char * msg, msg_list * current_node){
	msg_list * added = alloc(1, sizeof(msg_list));
	added->msg = alloc(MAX_ERR_MSG, sizeof(char));
	strcpy(added->msg, msg);
	added->next = NULL;
	current_node->next = added;
	current_node = added;

	return 0;
}

int add_msg_line(char * msg, msg_list * current_node, size_t line_num){
	current->msg = alloc(MAX_ERR_MSG, sizeof(char));
	strcpy(current_node->msg, msg);
	current->next = alloc(1, sizeof(msg_list));
	current->line = line_num;
	current = current_node->next;
	current->msg = NULL;
	return 0;
}
/*
* Has Neat Colors
*
*/
int print_err_msg(msg_list head){
	int count = 0;
	printf("\n-----------------------------Type Checking Error-------------------------------------\n" );
	for(msg_list * i = &head; i != NULL; i = i->next){
		if(i != NULL){
			if(i->msg != NULL){
				printf("\nError""[%d]: ", count++);
				printf("%s\n",i->msg);
			}
		}
	}
	printf( "\n-------------------------------END-----------------------------------------------------\n\n" );
	return 0;
}

int add_to_queue(nodeAST * node, sym_tbl * new_scope){
	current_queue->block = node;
	current_queue->scope = new_scope;
	current_queue->next = alloc(1, sizeof(fn_blk_que));
	current_queue = current_queue->next;
	current_queue->block = NULL;
	return 0;
}

int type_check_prog(nodeAST * node, int sf, FILE * s){
	fn_blk_que * blk_queue;
	stream = s;
	if(node == NULL){
		fprintf(stderr, "Start Node Invalid\n");
		exit(1);
	}
	if(node->nodeType != PROG_PROGRAM){
		fprintf(stderr, "Start Node Invalid\n");
		exit(1);
	}
	scope_flag = sf;
	init_table();
	tcsystem = new_type_check(DEFAULT_SIZE);
	sym_tbl * scope = tcsystem->current_tbl;
	tcsystem->current_tbl= new_sym_tbl_parent(scope, DEFAULT_SIZE);
	//At this point We should have two things
	//returnNode->nodeValue.program.package = _package;
    //returnNode->nodeValue.program.program = _program;

    //The package has nothing we need to add so we ignore that
    type_check_prog_list(node->nodeValue.program.program, tcsystem->current_tbl); //Every type check error will be added to the err_msg list

    //Second pass for the function blocks
    if(sf == 1)
    	print_sym_tbl_scoped(tcsystem->current_tbl, stream);
    print_err_msg(head);
    return 0;
}

int type_check_prog_list(nodeAST * node, sym_tbl * scope){
	/*
    returnNode->nodeValue.progList.prog = _prog;
    returnNode->nodeValue.progList.next = _next;
    The possible value of node->nodeValue

    newVarDeclareList
    newTypeDeclareList
    newFunction
    These are the three type _prog can have
    */
    // So the problem with this is in fact, we need to process this information
    for(nodeAST * i = node; i != NULL; i = i->nodeValue.progList.next){
    	if(i != NULL){
    		if(i->nodeValue.progList.prog != NULL){
    		switch(i->nodeValue.progList.prog->nodeType){
    			case PROG_DECLARE_VAR_LIST: type_check_var_decl_list(i->nodeValue.progList.prog, scope); break;
    			case PROG_DECLARE_TYPE_LIST: type_check_type_decl_list(i->nodeValue.progList.prog, scope); break;
    			case PROG_FUNCTION: type_check_func(i->nodeValue.progList.prog, scope); break;
    			default:
    				sprintf(err_buf, "Error Unexpected NodeType at line %zd", node->lineNumber);
    				add_msg_line(err_buf, current, node->lineNumber); break;
    		}
    		}
    	}
    }

    return 0;
}

int type_check_var_decl_list(nodeAST * node, sym_tbl * scope){
	//PROG_DECLARE_VAR_LIST
	//returnNode->nodeValue.varDeclareList.varDeclare = _varDeclare;
    //returnNode->nodeValue.varDeclareList.next = _next;
    //_varDeclare is either newVarDeclareList or newVarDeclare
	for(nodeAST * i = node; i != NULL; i = i->nodeValue.varDeclareList.next){
		if(i != NULL){
		switch(i->nodeValue.varDeclareList.varDeclare->nodeType){
			case PROG_DECLARE_VAR: type_check_var_decl(i->nodeValue.varDeclareList.varDeclare, scope); break;
			case PROG_DECLARE_VAR_LIST: type_check_var_decl_list(i->nodeValue.varDeclareList.varDeclare, scope); break;
			default:
    					sprintf(err_buf, "Error Unexpected NodeType at line %zd", node->lineNumber);
    					add_msg_line(err_buf, current, node->lineNumber); break;
		}
		}
	}
	return 0;
}

int type_check_var_decl(nodeAST * node, sym_tbl * scope){
	//PROG_DECLARE_VAR
    //returnNode->nodeValue.varDeclare.idList = _idList;
    //returnNode->nodeValue.varDeclare.initExpr = _initExpr;
    //returnNode->nodeValue.varDeclare.type = _type;
    /*
var_spec            : id_list '=' expr_list                       {$$ = newVarDeclare($1, $3, NULL, _treeNodeAllocator);}
                    | id_list type '=' expr_list                  {$$ = newVarDeclare($1, $4, $2, _treeNodeAllocator);}
                    | id_list type                                {$$ = newVarDeclare($1, NULL, $2, _treeNodeAllocator);}

	*/
	//msg_list * id_list = prepare_id_list(node->nodeValue.varDeclare.idList); //var_decl must have an id_list
	/*
    h->msg = alloc(MAX_ID_LENGTH, sizeof(char)); //MAX_ID of 256
    strcpy(h->msg, node->nodeValue.identifierList.identifier->nodeValue.identifier);
    for(nodeAST * i = node->nodeValue.identifierList.next; i != NULL; i = i->nodeValue.identifierList.next){
    	if(i != NULL){
    	add_msg_line(i->nodeValue.identifierList.identifier->nodeValue.identifier, c, i->nodeValue.identifierList.identifier->lineNumber);
    	}
    }
	*/
	if(node->nodeValue.varDeclare.type == NULL){
		type * expr_type = type_check_expr_list(node->nodeValue.varDeclare.initExpr, scope);
		//Now that we have all the types
		int type_iterator = 0;
		for(nodeAST * i = node->nodeValue.varDeclare.idList; i != NULL; i = i->nodeValue.identifierList.next){
			if(i != NULL){
			tbl_entry * current_entry = sym_tbl_find_entry_scoped(i->nodeValue.identifierList.identifier->nodeValue.identifier, scope);
			if(current_entry != NULL){ //Redeclaration in the same scope
				sprintf(err_buf, "Redeclaration of %s when declaring id at line %zd. \nPrevious declaration at line %zd", i->nodeValue.identifierList.identifier->nodeValue.identifier, node->lineNumber, current_entry->line_num);
				add_msg_line(err_buf, current, node->lineNumber);
				break;
			}else{//Everything is good
				//We need to add these things to the symbol table
				if(strcmp(i->nodeValue.identifierList.identifier->nodeValue.identifier, "_") != 0)
					sym_tbl_add_entry(new_tbl_entry(i->nodeValue.identifierList.identifier->nodeValue.identifier, i->lineNumber, i->nodeValue.identifierList.identifier, (expr_type->spec_type.list_type.type_list[type_iterator])), scope);
			}
			type_iterator++;
			}
		}
	}
	else if(node->nodeValue.varDeclare.initExpr == NULL){

		type * type_decl = (type_check_type(node->nodeValue.varDeclare.type, scope));
		int type_iterator = 0;

		for(nodeAST * i = node->nodeValue.varDeclare.idList; i != NULL; i = i->nodeValue.identifierList.next){
			if(i != NULL){
			tbl_entry * current_entry = sym_tbl_find_entry_scoped(i->nodeValue.identifierList.identifier->nodeValue.identifier, scope);
			if(current_entry != NULL){ //Redeclaration in the same scope
				sprintf(err_buf, "Redeclaration of %s when declaring id at line %zd. \nPrevious declaration at line %zd", i->nodeValue.identifierList.identifier->nodeValue.identifier, node->lineNumber, current_entry->line_num);
				add_msg_line(err_buf, current, node->lineNumber);
				break;
			}else{//Everything is good
				//We need to add these things to the symbol table
				if(strcmp(i->nodeValue.identifierList.identifier->nodeValue.identifier, "_") != 0)
					sym_tbl_add_entry(new_tbl_entry(i->nodeValue.identifierList.identifier->nodeValue.identifier, i->lineNumber, i->nodeValue.identifierList.identifier, (type_decl)), scope);
			}
			type_iterator++;
			}
		}
	}
	else{
		type * expr_decl = type_check_expr_list(node->nodeValue.varDeclare.initExpr, scope);
		type * type_decl = (type_check_type(node->nodeValue.varDeclare.type, scope));
		int type_iterator = 0;
		for(nodeAST * i = node->nodeValue.varDeclare.idList; i != NULL; i = i->nodeValue.identifierList.next){
			if(i != NULL){
			if(strcmp(i->nodeValue.identifierList.identifier->nodeValue.identifier, "_") == 0){
				continue;
			}
			if(valid_type_comparison(type_decl, expr_decl->spec_type.list_type.type_list[type_iterator]) == -1 && valid_type_comparison(type_decl, expr_decl->spec_type.list_type.type_list[type_iterator]) == -1){
    					print_type_to_string(type_decl, type_buf);
    					print_type_to_string(expr_decl->spec_type.list_type.type_list[type_iterator], type_buf_extra);
            			sprintf(err_buf, "Declared is %s and Expression is %s. They do not match at line %zd", type_buf, type_buf_extra, node->lineNumber);
            			add_msg_line(err_buf, current, node->lineNumber);
            			break;
			}
			tbl_entry * current_entry = sym_tbl_find_entry_scoped(i->nodeValue.identifierList.identifier->nodeValue.identifier, scope);
			if(current_entry != NULL){ //Redeclaration in the same scope
				sprintf(err_buf, "Redeclaration of %s when declaring id at line %zd. \nPrevious declaration at line %zd", i->nodeValue.identifierList.identifier->nodeValue.identifier, node->lineNumber, current_entry->line_num);
				add_msg_line(err_buf, current, node->lineNumber);
				break;
			}else{//Everything is good
				//We need to add these things to the symbol table
				sym_tbl_add_entry(new_tbl_entry(i->nodeValue.identifierList.identifier->nodeValue.identifier, i->lineNumber, i->nodeValue.identifierList.identifier, (type_decl)), scope);
			}
			type_iterator++;
			}
		}
	}
	return 0;
}

int type_check_func(nodeAST * node, sym_tbl * scope){
	/*
	returnNode->nodeType = PROG_FUNCTION;
    returnNode->nodeValue.function.identifier = _identifer;
    returnNode->nodeValue.function.pramList = _pram;
    returnNode->nodeValue.function.type = _type;
    returnNode->nodeValue.function.block = _block;
	*/

	tbl_entry * current_entry = sym_tbl_find_entry_scoped(node->nodeValue.function.identifier->nodeValue.identifier, scope);
	if(current_entry != NULL){ //Redeclaration in the same scope
		sprintf(err_buf, "Redeclaration of %s when declaring function at line %zd. \nPrevious declaration at line %zd", node->nodeValue.function.identifier->nodeValue.identifier, node->lineNumber, current_entry->line_num);
		add_msg_line(err_buf, current, node->lineNumber);
		return 0;
	}
	type * function = new_func_type();
	type * return_type = NULL;
	//add it to the new scope immediately to allow for recursion
	if(strcmp(node->nodeValue.function.identifier->nodeValue.identifier, "_") != 0){
		current_entry = new_tbl_entry(node->nodeValue.function.identifier->nodeValue.identifier, node->lineNumber, node, function);
		node->nodeValue.function.identifier->sym_tbl_ptr = current_entry->type_info;
		sym_tbl_add_entry(current_entry, scope);
	}

	sym_tbl * new_scope = new_sym_tbl_parent(scope, DEFAULT_SIZE);
	if(node->nodeValue.function.type != NULL)
		return_type = type_check_type(node->nodeValue.function.type, new_scope);
	type * param_type = type_check_params_list(node->nodeValue.function.pramList, new_scope);
	//This should be a list
	function->spec_type.func_type.params_type = param_type;
	function->spec_type.func_type.return_type = return_type;
	//Now we actually need to add the return type to the new scope
	if(return_type != NULL)
		sym_tbl_add_entry(new_tbl_entry("return", node->lineNumber, node, (return_type)), new_scope);

	//We do not type check the block the first pass
	//Instead we add it to the current_queue
	type_check_block(node->nodeValue.function.block, new_scope);
	//add_to_queue(node->nodeValue.function.block, new_scope);

	return 0;
}

type * type_check_params_list(nodeAST * node, sym_tbl * scope){
	/*
    returnNode->nodeType = PROG_PRAM_DEC_LIST;
    returnNode->nodeValue.pramDeclareList.pram = _parm;
    returnNode->nodeValue.pramDeclareList.next = _next;
	*/

	//Params is
	/*
	PROG_PRAM_DEC
    returnNode->nodeValue.pramDeclare.idList = _idList;
    returnNode->nodeValue.pramDeclare.type = _type;
	*/
	type * param_list = new_list_type(); //Initializes thew new empty list_type
	int size = 0;
    for(nodeAST * i = node; i != NULL; i = i->nodeValue.pramDeclareList.next){
    	if(i != NULL){
    		type * id_list_type = (type_check_type(i->nodeValue.pramDeclareList.pram->nodeValue.pramDeclare.type, scope));
    	//Get the type of the id_list type

    		for(nodeAST * j = i->nodeValue.pramDeclareList.pram->nodeValue.pramDeclare.idList; j != NULL; j = j->nodeValue.identifierList.next){
    			if(j != NULL){

    				if(strcmp(j->nodeValue.identifierList.identifier->nodeValue.identifier, "_") != 0){
    					tbl_entry * value = sym_tbl_find_entry_scoped(j->nodeValue.identifierList.identifier->nodeValue.identifier, scope);
    					if(value != NULL){
							sprintf(err_buf, "Redeclaration of %s when declaring id at line %zd. \nPrevious declaration at line %zd", j->nodeValue.identifierList.identifier->nodeValue.identifier, node->lineNumber, value->line_num);
							add_msg_line(err_buf, current, node->lineNumber);
    					}else{
    						value = new_tbl_entry(j->nodeValue.identifierList.identifier->nodeValue.identifier, j->nodeValue.identifierList.identifier->lineNumber, j->nodeValue.identifierList.identifier, id_list_type);
    					}
    					sym_tbl_add_entry(value, scope);

    					if(size == param_list->spec_type.list_type.list_cap){
    						param_list->spec_type.list_type.type_list = ralloc(param_list->spec_type.list_type.type_list, size *2);
    						param_list->spec_type.list_type.list_cap *= 2;
    					}
    					param_list->spec_type.list_type.type_list[size++] = id_list_type;
    				}else{
    					if(size == param_list->spec_type.list_type.list_cap){
    						param_list->spec_type.list_type.type_list = ralloc(param_list->spec_type.list_type.type_list, size *2);
    						param_list->spec_type.list_type.list_cap *= 2;
    					}
    					param_list->spec_type.list_type.type_list[size++] = id_list_type;

    					}
    				}
    			}
    	}
    }
    param_list->spec_type.list_type.list_size = size;
    return param_list;
}

int type_check_type_decl_list(nodeAST * node, sym_tbl * scope){
	/*
    returnNode->nodeType = PROG_DECLARE_TYPE_LIST;
    returnNode->nodeValue.typeDeclareList.typeDeclare = _typeDeclare;
    returnNode->nodeValue.typeDeclareList.next = _next;

    returnNode->nodeType = RROG_DECLARE_TYPE;
    returnNode->nodeValue.typeDeclare.identifier = _identifier;
    returnNode->nodeValue.typeDeclare.type = _type;
	*/
	type * alias_type;
	tbl_entry * name;
    for(nodeAST * i = node; i != NULL; i = i->nodeValue.typeDeclareList.next){
    	if(i != NULL){
    		alias_type = new_alias_type();
    		alias_type->spec_type.alias_type.id = i->nodeValue.typeDeclareList.typeDeclare->nodeValue.typeDeclare.identifier->nodeValue.identifier;
    		alias_type->spec_type.alias_type.a_type = (type_check_type(i->nodeValue.typeDeclareList.typeDeclare->nodeValue.typeDeclare.type, scope));
    		name = sym_tbl_find_entry_scoped(alias_type->spec_type.alias_type.id, scope);
    		if(name != NULL){
				sprintf(err_buf, "Redeclaration of %s when declaring type at line %zd. \nPrevious declaration at line %zd", alias_type->spec_type.alias_type.id, i->lineNumber, name->line_num);
				add_msg_line(err_buf, current, i->lineNumber);
				return 0;
    		}
    		if(strcmp(alias_type->spec_type.alias_type.id, "_") != 0)
    			name = new_tbl_entry(alias_type->spec_type.alias_type.id, i->nodeValue.typeDeclareList.typeDeclare->lineNumber, i->nodeValue.typeDeclareList.typeDeclare, alias_type);
    			i->nodeValue.typeDeclareList.typeDeclare->sym_tbl_ptr = name->type_info;
    			sym_tbl_add_entry(name, scope);
    	}
    }
    return 0;
}

type * type_check_alias_type(nodeAST * node, sym_tbl * scope){
						 tbl_entry * entry = sym_tbl_find_entry(node->nodeValue.identifier, scope);
						 if(entry == NULL || entry->type_info->type != ALIAS_TYPE){
						 	sprintf(err_buf, "Type alias %s not found at line %zd", node->nodeValue.identifier, node->lineNumber);
				      		add_msg_line(err_buf, current, node->lineNumber);
						 	return new_invalid_type(); //Invalid Type
						 }
						 else if(entry->type_info->type != ALIAS_TYPE){
						 	sprintf(err_buf, "Invalid type alias %s not found at line %zd", node->nodeValue.identifier, node->lineNumber);
				      		add_msg_line(err_buf, current, node->lineNumber);
						 	return new_invalid_type(); //Invalid Type
						 }
						 node->sym_tbl_ptr = entry->type_info;
						return (entry->type_info);
}

type * type_check_type(nodeAST * node, sym_tbl * scope){
/*
type                : basic_type                                  {$$ = $1;}
                    | '[' ']' type                                {$$ = newSliceType($3, _treeNodeAllocator);}
                    | struct_ '{' field_decl_list '}'             {$$ = newStruct($3, _treeNodeAllocator);}
                    | '[' int_lit_ ']' type                       {$$ = newArrayType(newLiteralInt($2, _treeNodeAllocator), $4, _treeNodeAllocator);}
                    | id_                                         {$$ = newIdentifier($1, _treeNodeAllocator);}
*/	type * ret;
	switch(node->nodeType){
		case BASIC_TYPE: ret = type_basic_type(node);
						 return ret;
		//    returnNode->nodeValue.sliceType.type = _type;
		case SLICE_TYPE: ret = new_slice_type();
						 ret->spec_type.slice_type.s_type = type_check_type(node->nodeValue.sliceType.type, scope);
						 return ret;
		case ARRAY_TYPE: ret = new_array_type();
						/*
    					returnNode->nodeValue.arrayType.capacity = _capacity;
    					returnNode->nodeValue.arrayType.type = _type;
						*/
						 ret->spec_type.array_type.a_type = type_check_type(node->nodeValue.arrayType.type, scope);
						 return ret;
		case IDENTIFIER: //This is a aliased type
		//    returnNode->nodeValue.identifier = (char*)mallocList(sizeof(char)*(strlen(_identifier)+1), _allocator);
						return type_check_alias_type(node, scope);
		case STRUCT_TYPE:{
						//    returnNode->nodeValue.structType.structDec = _declareList;
							ret = new_struct_type();
							nodeAST * cur = node->nodeValue.structType.structDec;
							nodeAST * field_decl;
							type * field_decl_type;
						/*
    					returnNode->nodeType = STRUCT_TYPE_DEC_LIST;
   		 				returnNode->nodeValue.structTypeDecList.declare = _declare;
    					returnNode->nodeValue.structTypeDecList.next = _next;

    					returnNode->nodeType = STRUCT_TYPE_DEC;
    					returnNode->nodeValue.structTypeDec.identifierList = _identifierList;
    					returnNode->nodeValue.structTypeDec.type = _type;
						*/
							for(nodeAST * i = cur; i != NULL; i = i->nodeValue.structTypeDecList.next){
								if(i != NULL){
								field_decl = i->nodeValue.structTypeDecList.declare;
								field_decl_type = type_check_type(field_decl->nodeValue.structTypeDec.type, scope);
								for(nodeAST * j = field_decl->nodeValue.structTypeDec.identifierList; j != NULL; j = j->nodeValue.identifierList.next){
									if(j != NULL){
									char * id = j->nodeValue.identifierList.identifier->nodeValue.identifier;
									if(strcmp("_", id) != 0){
										for(int k = 0; k < ret->spec_type.struct_type.list_size; k++){
											if(strcmp(ret->spec_type.struct_type.id_list[k], id) == 0){
												sprintf(err_buf, "Redeclaration of id %s when declaring struct fields at line %zd.", id, j->lineNumber);
												add_msg_line(err_buf, current, node->lineNumber);
												return new_invalid_type();
											}
										}
									}

									if(ret->spec_type.struct_type.list_size == ret->spec_type.struct_type.list_cap){
										ret->spec_type.struct_type.type_list = ralloc(ret->spec_type.struct_type.type_list, sizeof(type *) * ret->spec_type.struct_type.list_size * 2);
										ret->spec_type.struct_type.list_cap *= 2;
									}
									//printf("Decl type %d\n", field_decl_type->type);
									ret->spec_type.struct_type.type_list[ret->spec_type.struct_type.list_size] = field_decl_type;
									ret->spec_type.struct_type.id_list[ret->spec_type.struct_type.list_size++] = id;


									}
								}
								}
							}
							return ret;
						}
		default: 	return new_invalid_type();
	}
}

type * type_basic_type(nodeAST * node){
		switch(node->nodeValue.basicType){
	    	case BASIC_INT: return new_int_type();
        	case BASIC_FLOAT: return new_float_type();
        	case BASIC_RUNE: return new_rune_type();
        	case BASIC_STRING: return new_string_type();
        	case BASIC_BOOL: return new_bool_type();
        	default: return NULL;
    	}
}

type * type_check_expr_list(nodeAST * node, sym_tbl * scope){
	/*
    returnNode->nodeType = EXPR_UTILITY_EXPRLIST;
    returnNode->nodeValue.exprList.expr = _expr;
    returnNode->nodeValue.exprList.next = _next;
    */
    type * to_be_added;
    type * expr_list_type = new_list_type();
    for(nodeAST * i = node; i != NULL; i = i->nodeValue.exprList.next){
    	if(i != NULL){
    	type * to_be_added = type_check_expr(i->nodeValue.exprList.expr, scope);
    	if(to_be_added != NULL){
			if(expr_list_type->spec_type.list_type.list_size == expr_list_type->spec_type.list_type.list_cap){
				expr_list_type->spec_type.list_type.type_list = ralloc(expr_list_type->spec_type.list_type.type_list, sizeof(type *) * expr_list_type->spec_type.struct_type.list_size * 2);
				expr_list_type->spec_type.list_type.list_cap *= 2;
				}
			expr_list_type->spec_type.list_type.type_list[expr_list_type->spec_type.list_type.list_size++] = to_be_added;
    	}

    	node->sym_tbl_ptr = to_be_added;
    	to_be_added = NULL;
    	}

    }
    return expr_list_type;
}
    						/*
							bool || bool bool
							bool && bool bool
							comparable == comparable bool
							comparable != comparable bool
							ordered < ordered bool
							ordered <= ordered bool
							ordered > ordered bool
							ordered >= ordered bool
							numeric or string + numeric or string numeric or string
							numeric - numeric numeric
							numeric * numeric numeric
							numeric / numeric numeric
							numeric % numeric numeric
							integer | integer integer
							integer & integer integer
							integer << integer integer
							integer >> integer integer
							integer &ˆ integer integer
							integer ˆ integer integer
    						*/

type * type_check_expr_id(nodeAST * node, sym_tbl * scope){
	//We need to find it first in the hash_table
    		tbl_entry * entry = sym_tbl_find_entry( node->nodeValue.identifier,scope);
    			if(entry == NULL){
					sprintf(err_buf, "Undeclared id %s at line %zd", node->nodeValue.identifier, node->lineNumber);
					add_msg_line(err_buf, current, node->lineNumber);
    				return new_invalid_type();
    			}
    			node->sym_tbl_ptr = entry->type_info;
    			return (entry->type_info);
    		}

type * type_check_expr_func(nodeAST * node, sym_tbl * scope){
				/*
				returnNode->nodeType = EXPR_FUNC_CALL;
    			returnNode->nodeValue.funcCall.target = _target;
    			returnNode->nodeValue.funcCall.expr = _expr;
				func_call           : id_ '(' expr_list ')'                       {$$ = newFuncCall(newIdentifier($1, _treeNodeAllocator), $3, _treeNodeAllocator);}
                 				    | id_ '(' ')'
    			*/

                 	    //Since it's a function call, check if the function exists!
                 	tbl_entry * entry = sym_tbl_find_entry( node->nodeValue.funcCall.target->nodeValue.identifier,scope);
    				if(entry == NULL){
						sprintf(err_buf, "Undeclared function %s at line %zd", node->nodeValue.funcCall.target->nodeValue.identifier, node->lineNumber);
						add_msg_line(err_buf, current, node->lineNumber);
    					return new_invalid_type();
    				}else if(entry->type_info->type == ALIAS_TYPE){
    					if(node->nodeValue.funcCall.expr == NULL){
							sprintf(err_buf, "Invalid type conversion from void to type alias at line %zd", node->lineNumber);
							add_msg_line(err_buf, current, node->lineNumber);
							return new_invalid_type();
    					}
    					type * input = type_check_expr_list(node->nodeValue.funcCall.expr, scope);
    					type * entry_type = get_alias_type(entry->type_info);
    					if(valid_type_conversion(entry_type, input->spec_type.list_type.type_list[0]) == 0 && input->spec_type.list_type.list_size == 1){
    						return entry->type_info;
    					}else{
    						print_type_to_string(input, type_buf);
    						print_type_to_string(entry->type_info, type_buf_extra);
							sprintf(err_buf, "Invalid type conversion %s from %s to %s at line %zd", node->nodeValue.funcCall.target->nodeValue.identifier, type_buf, type_buf_extra, node->lineNumber);
							add_msg_line(err_buf, current, node->lineNumber);
    						return new_invalid_type();
    					}
    				}else if(entry->type_info->type != FUNC_TYPE){
						sprintf(err_buf, "Undeclared function %s at line %zd", node->nodeValue.funcCall.target->nodeValue.identifier, node->lineNumber);
						add_msg_line(err_buf, current, node->lineNumber);
    					return new_invalid_type();
    				}
    				else{
    					//Check the params type to see if it matches
    					type * params = entry->type_info->spec_type.func_type.params_type;
    					if(node->nodeValue.funcCall.expr != NULL){
    						type * input = type_check_expr_list(node->nodeValue.funcCall.expr, scope);
    						if(params->spec_type.list_type.list_size != input->spec_type.list_type.list_size){
								sprintf(err_buf, "Argument number does not match function requirements at line %zd",  node->lineNumber);
								add_msg_line(err_buf, current, node->lineNumber);
    							return new_invalid_type();
    						}
    						for(int i = 0; i < input->spec_type.list_type.list_size; i++){
    							if(valid_type_comparison(input->spec_type.list_type.type_list[i], params->spec_type.list_type.type_list[i]) == -1 && valid_type_comparison(input->spec_type.list_type.type_list[i], get_alias_type(params->spec_type.list_type.type_list[i])) && valid_type_comparison(get_alias_type(input->spec_type.list_type.type_list[i]), params->spec_type.list_type.type_list[i])){
									sprintf(err_buf, "Argument type does not match function argument type at line %zd",  node->lineNumber);
									add_msg_line(err_buf, current, node->lineNumber);
    								return new_invalid_type();
    							}
    						}
    					}else if(params->spec_type.list_type.list_size != 0){
							sprintf(err_buf, "Argument number does not match function requirements at line %zd",  node->lineNumber);
							add_msg_line(err_buf, current, node->lineNumber);
    						return new_invalid_type();
    					}
    					if(entry->type_info->spec_type.func_type.return_type == NULL)
    						return new_invalid_type();
    					else{
    						node->sym_tbl_ptr = entry->type_info->spec_type.func_type.return_type;
    						return (entry->type_info->spec_type.func_type.return_type);
    					}
    					//The type of a function call is its return type
    				}
}

type * type_check_expr_index(nodeAST * node, sym_tbl * scope){
            				/*
    						returnNode->nodeType = EXPR_INDEX;
    						returnNode->nodeValue.index.target = _target;
    						returnNode->nodeValue.index.entry = _entry;
            				*/
            				//This would type check only when the primary_expr [ expr ]
            				// where primary_expr needs to be array or slice type and
            					type * ret = type_check_expr(node->nodeValue.index.target, scope);
            					type * target = get_alias_type(ret);
            					if(target->type != ARRAY_TYPE && target->type != SLICE_TYPE){
            						print_type_to_string(target, type_buf);
            						sprintf(err_buf, "Primary Expression is of %s is not a Array or Slice type %zd", type_buf, node->lineNumber);
									add_msg_line(err_buf, current, node->lineNumber);
    								return new_invalid_type();
            					}
            					type * entry = get_alias_type(type_check_expr(node->nodeValue.index.entry, scope));
            					if(entry->type != LITERAL_INT && entry->type != LITERAL_RUNE){
            						print_type_to_string(entry, type_buf);
            					    sprintf(err_buf, "Expression inside brackets is of %s. It must be of INT type at line %zd",  type_buf, node->lineNumber);
									add_msg_line(err_buf, current, node->lineNumber);
    								return new_invalid_type();
            					}
            					//So everything is valid so this returns the type of the slice/array
            					if(target->type == ARRAY_TYPE){
            						node->sym_tbl_ptr = ret->spec_type.array_type.a_type;
            						return (ret->spec_type.array_type.a_type);
            					}
            					node->sym_tbl_ptr = (ret->spec_type.slice_type.s_type);
            					return (ret->spec_type.slice_type.s_type);
}

type * type_check_expr_select(nodeAST * node, sym_tbl * scope){
            				/*
            					primary_expr '.' id_
    							returnNode->nodeType = EXPR_SELECTOR;
    							returnNode->nodeValue.selector.target = _target;
   	 							returnNode->nodeValue.selector.entry = _entry;
							*/
   	 							type * current_struct = get_alias_type(type_check_expr(node->nodeValue.selector.target, scope));
   	 							char * id = node->nodeValue.selector.entry->nodeValue.identifier;
   	 							if(current_struct->type != STRUCT_TYPE){
            						print_type_to_string(current_struct, type_buf);
            					    sprintf(err_buf, "Expecting a struct type at line %zd. Found %s",  node->lineNumber, type_buf);
									add_msg_line(err_buf, current, node->lineNumber);
    								return new_invalid_type();
   	 							}
   	 							if(strcmp(id, "_") == 0){
            					    sprintf(err_buf, "Trying to access an underscore id at line %zd",  node->lineNumber);
									add_msg_line(err_buf, current, node->lineNumber);
   	 							}
   	 							//Next we need to scan all the members of the struct id_list to get that specific id type if found
   	 							for(int i = 0; i < current_struct->spec_type.struct_type.list_size; i++){
   	 								if(strcmp(id, current_struct->spec_type.struct_type.id_list[i]) == 0){//Found the id
   	 										node->sym_tbl_ptr = current_struct->spec_type.struct_type.type_list[i];
   	 										return (current_struct->spec_type.struct_type.type_list[i]);
   	 								}
   	 							}
            					sprintf(err_buf, "ID %s not found in the struct at line %zd", id,  node->lineNumber);
								add_msg_line(err_buf, current, node->lineNumber);
    							return new_invalid_type();
}

type * type_check_expr_slice(nodeAST * node, sym_tbl * scope){
   	 						/*
    							returnNode->nodeType = EXPR_SLICE;
    							returnNode->nodeValue.slice.target = _target;
    							returnNode->nodeValue.slice.entry = _entry;
   	 						*/
    						//Okay so primary_expr slice, primary_expr must be of type slice
    							type * ret = type_check_expr(node->nodeValue.slice.target, scope);
    							type * current_slice = get_alias_type(ret);
    							if(current_slice->type != SLICE_TYPE){
            						print_type_to_string(current_slice, type_buf);
            					    sprintf(err_buf, "Slice type expected at line %zd. Found %s",  node->lineNumber, type_buf);
									add_msg_line(err_buf, current, node->lineNumber);
    								return new_invalid_type();
    							}
    							type_check_slice_expr(node->nodeValue.slice.entry, scope); //IF invalid type_checking, err_msg will be added inside
    							//This returns the type of the slice
    							node->sym_tbl_ptr = ret;
    							return (ret);

}

type * type_check_expr_mul(nodeAST * node, sym_tbl * scope){
    						type * left = type_check_expr(node->nodeValue.mul.left, scope);
    						type * right = type_check_expr(node->nodeValue.mul.right, scope);

    						if(valid_type_comparison(left, right) == 0 && valid_type_numeric(left) == 0 && valid_type_numeric(right) == 0){
    							node->sym_tbl_ptr = left;
    							return left;
    						}
    						else{
    							print_type_to_string(left, type_buf);
    							print_type_to_string(right, type_buf_extra);
            					sprintf(err_buf, "Left is %s, Right is %s . They do not match or are invalid at line %zd", type_buf, type_buf_extra, node->lineNumber);
								add_msg_line(err_buf, current, node->lineNumber);
    							return new_invalid_type();
    						}
}

type * type_check_expr_div(nodeAST * node, sym_tbl * scope){
    						type * left = type_check_expr(node->nodeValue.mul.left, scope);
    						type * right = type_check_expr(node->nodeValue.mul.right, scope);

    						if(valid_type_comparison(left, right) == 0 && valid_type_numeric(left) == 0 && valid_type_numeric(right) == 0){
    							node->sym_tbl_ptr = left;
    							return left;
    						}
    						else{
    							print_type_to_string(left, type_buf);
    							print_type_to_string(right, type_buf_extra);
            					sprintf(err_buf, "Left is %s, Right is %s . They do not match or are invalid at line %zd", type_buf, type_buf_extra, node->lineNumber);
								add_msg_line(err_buf, current, node->lineNumber);
    							return new_invalid_type();
    						}
}

type * type_check_expr_mod(nodeAST * node, sym_tbl * scope){
    						type * left = type_check_expr(node->nodeValue.mul.left, scope);
    						type * right = type_check_expr(node->nodeValue.mul.right, scope);

    						if(valid_type_comparison(left, right) == -1 || (left->type != LITERAL_INT && right->type != LITERAL_RUNE) ){
								print_type_to_string(left, type_buf);
    							print_type_to_string(right, type_buf_extra);
    							if(left->type == LITERAL_FLOAT || right->type == LITERAL_FLOAT)
            						sprintf(err_buf, "Cannot mod with a float. Left is %s, Right is %s . They do not match or are invalid at line %zd", type_buf, type_buf_extra, node->lineNumber);
    							else
            						sprintf(err_buf, "Left is %s, Right is %s . They do not match or are invalid at line %zd", type_buf, type_buf_extra, node->lineNumber);
								add_msg_line(err_buf, current, node->lineNumber);
    							return new_invalid_type();
    						}
    						else{
    							node->sym_tbl_ptr = left;
    							return left;
    						}
}

type * type_check_expr_sub(nodeAST * node, sym_tbl * scope){
    						type * left = type_check_expr(node->nodeValue.mul.left, scope);
    						type * right = type_check_expr(node->nodeValue.mul.right, scope);

    						if(valid_type_comparison(left, right) == 0 && valid_type_numeric(left) == 0 && valid_type_numeric(right) == 0){
    							node->sym_tbl_ptr = left;
    							return left;
    						}
    						else{
    							print_type_to_string(left, type_buf);
    							print_type_to_string(right, type_buf_extra);
            					sprintf(err_buf, "Left is %s, Right is %s . They do not match or are invalid at line %zd", type_buf, type_buf_extra, node->lineNumber);
								add_msg_line(err_buf, current, node->lineNumber);
    							return new_invalid_type();
    						}
}

type * type_check_expr_add(nodeAST * node, sym_tbl * scope){
    						type * left = type_check_expr(node->nodeValue.add.left, scope);
    						type * right = type_check_expr(node->nodeValue.add.right, scope);
    						if(valid_type_comparison(left, right) == 0 && valid_type_numeric(left) == 0 && valid_type_numeric(right) == 0){
    							node->sym_tbl_ptr = left;
    							return left;
    						}
    						else if( left->type == LITERAL_STRING && right->type == LITERAL_STRING ){
    							node->sym_tbl_ptr = left;
    							return left;
    						}else{
    							print_type_to_string(left, type_buf);
    							print_type_to_string(right, type_buf_extra);
            					sprintf(err_buf, "Left is %s, Right is %s . They do not match or are invalid at line %zd", type_buf, type_buf_extra, node->lineNumber);								add_msg_line(err_buf, current, node->lineNumber);
    							return new_invalid_type();
    						}

    						/*
    						returnNode->nodeType = EXPR_BINARY_OP_ADD;
    						returnNode->nodeValue.add.left = _left;
    						returnNode->nodeValue.add.right = _right;
    						*/
}

type * type_check_expr_and(nodeAST * node, sym_tbl * scope){
    						type * left = type_check_expr(node->nodeValue.logicAnd.left, scope);
    						type * right = type_check_expr(node->nodeValue.logicAnd.right, scope);
    						//Both must be boolean for and
    						if( (left->type == LITERAL_BOOL && right->type == LITERAL_BOOL) ){
    							node->sym_tbl_ptr = new_bool_type();
    							return node->sym_tbl_ptr;
    						}
    						else{
    							print_type_to_string(left, type_buf);
    							print_type_to_string(right, type_buf_extra);
            					sprintf(err_buf, "Left is %s, Right is %s . They are not boolean at line %zd", type_buf, type_buf_extra, node->lineNumber);								add_msg_line(err_buf, current, node->lineNumber);
    							return new_invalid_type();
    						}

    						/*
   		 					returnNode->nodeType = EXPR_BINARY_OP_LOGIC_AND;
    						returnNode->nodeValue.logicAnd.left = _left;
    						returnNode->nodeValue.logicAnd.right = _right;
    						*/
}

type * type_check_expr_or(nodeAST * node, sym_tbl * scope){
    						type * left = type_check_expr(node->nodeValue.logicOr.left, scope);
    						type * right = type_check_expr(node->nodeValue.logicOr.right, scope);
    						if( (left->type == LITERAL_BOOL && right->type == LITERAL_BOOL) ){
    							node->sym_tbl_ptr = new_bool_type();
    							return node->sym_tbl_ptr;
    						}
    						else{
    							print_type_to_string(left, type_buf);
    							print_type_to_string(right, type_buf_extra);
            					sprintf(err_buf, "Left is %s, Right is %s . They are not boolean at line %zd", type_buf, type_buf_extra, node->lineNumber);											add_msg_line(err_buf, current, node->lineNumber);
    							return new_invalid_type();
    						}

    						/*
    						returnNode->nodeType = EXPR_BINARY_OP_LOGIC_OR;
    						returnNode->nodeValue.logicOr.left = _left;
    						returnNode->nodeValue.logicOr.right = _right;
    						*/
}

type * type_check_expr_xor(nodeAST * node, sym_tbl * scope){
    						type * left = type_check_expr(node->nodeValue.bitXor.left, scope);
    						type * right = type_check_expr(node->nodeValue.bitXor.right, scope);
    						if(valid_type_comparison(left, right) == 0 && (left->type == LITERAL_INT || left->type == LITERAL_RUNE) ){
    							node->sym_tbl_ptr = new_int_type();
    							return node->sym_tbl_ptr;
    						}
    						else{
    							print_type_to_string(left, type_buf);
    							print_type_to_string(right, type_buf_extra);
            					sprintf(err_buf, "Left is %s, Right is %s . They are not boolean at line %zd", type_buf, type_buf_extra, node->lineNumber);											add_msg_line(err_buf, current, node->lineNumber);
    							return new_invalid_type();
    						}

    						/*
    						returnNode->nodeType = EXPR_BINARY_OP_XOR;
    						returnNode->nodeValue.bitXor.left = _left;
    						returnNode->nodeValue.bitXor.right = _right;
    						*/
}

type * type_check_expr_bitOr(nodeAST * node, sym_tbl * scope){
    						type * left = type_check_expr(node->nodeValue.bitOr.left, scope);
    						type * right = type_check_expr(node->nodeValue.bitOr.right, scope);
    						if(valid_type_comparison(left, right) == 0 && (left->type == LITERAL_INT || left->type == LITERAL_RUNE) ){
    							node->sym_tbl_ptr = new_int_type();
    							return node->sym_tbl_ptr;
    						}
    						else{
    							print_type_to_string(left, type_buf);
    							print_type_to_string(right, type_buf_extra);
            					sprintf(err_buf, "Left is %s, Right is %s . They are not Integer at line %zd", type_buf, type_buf_extra, node->lineNumber);											add_msg_line(err_buf, current, node->lineNumber);
    							return new_invalid_type();
    						}

    						/*
    						returnNode->nodeType = EXPR_BINARY_OP_OR;
    						returnNode->nodeValue.bitOr.left = _left;
    						returnNode->nodeValue.bitOr.right = _right;
    						*/
}

type * type_check_expr_lshift(nodeAST * node, sym_tbl * scope) {
    						type * left = type_check_expr(node->nodeValue.shiftLeft.left, scope);
    						type * right = type_check_expr(node->nodeValue.shiftLeft.right, scope);
    						if(valid_type_comparison(left, right) == 0 && (left->type == LITERAL_INT || left->type == LITERAL_RUNE) ){
    							node->sym_tbl_ptr = new_int_type();
    							return node->sym_tbl_ptr;
    						}
    						else{
    							print_type_to_string(left, type_buf);
    							print_type_to_string(right, type_buf_extra);
            					sprintf(err_buf, "Left is %s, Right is %s . They are not Integer at line %zd", type_buf, type_buf_extra, node->lineNumber);									add_msg_line(err_buf, current, node->lineNumber);
    							return new_invalid_type();
    						}

    						/*
    						returnNode->nodeType = EXPR_BINARY_OP_LSHIFT;
    						returnNode->nodeValue.shiftLeft.left = _left;
    						returnNode->nodeValue.shiftLeft.right = _right;
    						*/
}

type * type_check_expr_rshift(nodeAST * node, sym_tbl * scope){
    						type * left = type_check_expr(node->nodeValue.shiftRight.left, scope);
    						type * right = type_check_expr(node->nodeValue.shiftRight.right, scope);
    						if(valid_type_comparison(left, right) == 0 && (left->type == LITERAL_INT || left->type == LITERAL_RUNE) ){
    							node->sym_tbl_ptr = new_int_type();
    							return node->sym_tbl_ptr;
    						}
    						else{
    							print_type_to_string(left, type_buf);
    							print_type_to_string(right, type_buf_extra);
            					sprintf(err_buf, "Left is %s, Right is %s . They are not Integer at line %zd", type_buf, type_buf_extra, node->lineNumber);									add_msg_line(err_buf, current, node->lineNumber);
    							return new_invalid_type();
    						}

    						/*
    						returnNode->nodeType = EXPR_BINARY_OP_RSHIFT;
    						returnNode->nodeValue.shiftRight.left = _left;
    						returnNode->nodeValue.shiftRight.right = _right;
    						*/
}
type * type_check_expr_bitAnd(nodeAST * node, sym_tbl * scope){
    						type * left = type_check_expr(node->nodeValue.bitAnd.left, scope);
    						type * right = type_check_expr(node->nodeValue.bitAnd.right, scope);
    						if(valid_type_comparison(left, right) == 0 && (left->type == LITERAL_INT || left->type == LITERAL_RUNE) ){
    							node->sym_tbl_ptr = new_int_type();
    							return node->sym_tbl_ptr;
    						}
    						else{
    							print_type_to_string(left, type_buf);
    							print_type_to_string(right, type_buf_extra);
            					sprintf(err_buf, "Left is %s, Right is %s . They are not Integer at line %zd", type_buf, type_buf_extra, node->lineNumber);									add_msg_line(err_buf, current, node->lineNumber);
    							return new_invalid_type();
    						}

    						/*
    						returnNode->nodeType = EXPR_BINARY_OP_AND;
    						returnNode->nodeValue.bitAnd.left = _left;
    						returnNode->nodeValue.bitAnd.right = _right;
    						*/
}

type * type_check_expr_bitAndNot(nodeAST * node, sym_tbl * scope){
    						type * left = type_check_expr(node->nodeValue.shiftRight.left, scope);
    						type * right = type_check_expr(node->nodeValue.shiftRight.right, scope);
    						if(valid_type_comparison(left, right) == 0 && (left->type == LITERAL_INT || left->type == LITERAL_RUNE) ){
    							node->sym_tbl_ptr = new_int_type();
    							return node->sym_tbl_ptr;
    						}
    						else{
    							print_type_to_string(left, type_buf);
    							print_type_to_string(right, type_buf_extra);
            					sprintf(err_buf, "Left is %s, Right is %s . They are not Integer at line %zd", type_buf, type_buf_extra, node->lineNumber);									add_msg_line(err_buf, current, node->lineNumber);
    							return new_invalid_type();
    						}

    						/*
    						returnNode->nodeType = EXPR_BINARY_OP_ANDNOT;
    						returnNode->nodeValue.bitAndNot.left = _left;
    						returnNode->nodeValue.bitAndNot.right = _right;
    						*/
}

type * type_check_expr_unary_pos(nodeAST * node, sym_tbl * scope){
    						//Characters are not allowed as part of unary expression
    						type * left = type_check_expr(node->nodeValue.pos.expr, scope);
    						if( left->type == LITERAL_INT || left->type == LITERAL_FLOAT || left->type == LITERAL_RUNE ){
    							node->sym_tbl_ptr = left;
    							return (left);
    						}
    						else{
    							print_type_to_string(left, type_buf);
            					sprintf(err_buf, "Invalid Unary Operator + for %s at line %zd",  type_buf, node->lineNumber);
								add_msg_line(err_buf, current, node->lineNumber);
    							return new_invalid_type();
    						}

    						/*
    						nodeAST* returnNode = allocateNode(_allocator);
    						returnNode->nodeType = EXPR_UNIARY_OP_POS;
    						returnNode->nodeValue.pos.expr = _expr;
    						*/
}

type * type_check_expr_unary_neg(nodeAST * node, sym_tbl * scope){
    						//Characters are not allowed as part of unary expression
    						type * left = type_check_expr(node->nodeValue.neg.expr, scope);
    						if( left->type == LITERAL_INT || left->type == LITERAL_FLOAT || left->type == LITERAL_RUNE ){
    							node->sym_tbl_ptr = left;
    							return (left);
    						}
    						else{
    							print_type_to_string(left, type_buf);
            					sprintf(err_buf, "Invalid Unary Operator - for %s at line %zd",  type_buf, node->lineNumber);
								add_msg_line(err_buf, current, node->lineNumber);
    							return new_invalid_type();
    						}

    						/*
    						nodeAST* returnNode = allocateNode(_allocator);
    						returnNode->nodeType = EXPR_UNIARY_OP_NEG;
    						returnNode->nodeValue.neg.expr = _expr;
    						*/
}

type * type_check_expr_bitNot(nodeAST * node, sym_tbl * scope){
    						//Floats are not allowed as part of unary expression
    						type * left = type_check_expr(node->nodeValue.bitNot.expr, scope);
    						if( (left->type == LITERAL_INT || left->type == LITERAL_RUNE) ){
    							node->sym_tbl_ptr = new_int_type();
    							return node->sym_tbl_ptr;
    						}
    						else{
    							print_type_to_string(left, type_buf);
            					sprintf(err_buf, "Invalid Unary Operator ^ for %s at line %zd",  type_buf, node->lineNumber);
								add_msg_line(err_buf, current, node->lineNumber);
    							return new_invalid_type();
    						}

    						/*
    						nodeAST* returnNode = allocateNode(_allocator);
    						returnNode->nodeType = EXPR_UNIARY_OP_NOT;
    						returnNode->nodeValue.bitNot.expr = _expr;
    						*/
}
type * type_check_expr_not(nodeAST * node, sym_tbl * scope){
    						//Characters are not allowed as part of unary expression
    						type * left = type_check_expr(node->nodeValue.logicNot.expr, scope);
    						if( left->type == LITERAL_BOOL ){
    							node->sym_tbl_ptr = new_bool_type();
    							return node->sym_tbl_ptr;
    						}
    						else{
    							print_type_to_string(left, type_buf);
            					sprintf(err_buf, "Invalid Unary Operator ! for %s at line %zd",  type_buf, node->lineNumber);
								add_msg_line(err_buf, current, node->lineNumber);
    							return new_invalid_type();
    						}

    						/*
    						returnNode->nodeType = EXPR_UNIARY_OP_LOGIC_NOT;
    						returnNode->nodeValue.logicNot.expr = _expr;
    						*/
}
type * type_check_expr_eq(nodeAST * node, sym_tbl * scope){
    						type * left = type_check_expr(node->nodeValue.equal.left, scope);
    						type * right = type_check_expr(node->nodeValue.equal.right, scope);
    						if(valid_type_comparison(left, right) == -1){
    								print_type_to_string(left, type_buf);
    								print_type_to_string(right, type_buf_extra);
            						sprintf(err_buf, "Left is %s and Right is %s and they cannot be compared at line %zd", type_buf, type_buf_extra, node->lineNumber);
									add_msg_line(err_buf, current, node->lineNumber);
    								return new_invalid_type();
    						}else if(left->type == SLICE_TYPE || right->type == SLICE_TYPE){
            					sprintf(err_buf, "Slice type detected. Slice cannot be compared. This occured at line %zd", node->lineNumber);
								add_msg_line(err_buf, current, node->lineNumber);
    						}
    						node->sym_tbl_ptr = new_bool_type();
    						return node->sym_tbl_ptr;
    						/*
    						    returnNode->nodeType = EXPR_BINARY_OP_EQUAL;
    							returnNode->nodeValue.equal.left = _left;
    							returnNode->nodeValue.equal.right = _right;

    						*/
}
type * type_check_expr_neq(nodeAST * node, sym_tbl * scope){
    						type * left = type_check_expr(node->nodeValue.nequal.left, scope);
    						type * right = type_check_expr(node->nodeValue.nequal.right, scope);
    						if(valid_type_comparison(left, right) == -1){
    							print_type_to_string(left, type_buf);
    							print_type_to_string(right, type_buf_extra);
            					sprintf(err_buf, "Left is %s and Right is %s and they cannot be compared at line %zd", type_buf, type_buf_extra, node->lineNumber);
								add_msg_line(err_buf, current, node->lineNumber);
    							return new_invalid_type();
    						}else if(left->type == SLICE_TYPE || right->type == SLICE_TYPE){
            					sprintf(err_buf, "Slice type detected. Slice cannot be compared. This occured at line %zd", node->lineNumber);
								add_msg_line(err_buf, current, node->lineNumber);
    						}
    						node->sym_tbl_ptr = new_bool_type();
    						return node->sym_tbl_ptr;
    						/*
    						returnNode->nodeType = EXPR_BINARY_OP_NEQUAL;
    						returnNode->nodeValue.nequal.left = _left;
    						returnNode->nodeValue.nequal.right = _right;
    						*/
}
type * type_check_expr_lt(nodeAST * node, sym_tbl * scope){
    						type * left = type_check_expr(node->nodeValue.less.left, scope);
    						type * right = type_check_expr(node->nodeValue.less.right, scope);
    						if(valid_type_ordered(left, right) == -1){
    							print_type_to_string(left, type_buf);
    							print_type_to_string(right, type_buf_extra);
            					sprintf(err_buf, "Left is %s and Right is %s and they are not ordered at line %zd", type_buf, type_buf_extra, node->lineNumber);								add_msg_line(err_buf, current, node->lineNumber);
    							return new_invalid_type();
    						}
    						node->sym_tbl_ptr = new_bool_type();
    						return node->sym_tbl_ptr;
    						/*
    						returnNode->nodeType = EXPR_BINARY_OP_LESS;
    						returnNode->nodeValue.less.left = _left;
    						returnNode->nodeValue.less.right = _right;
    						*/
}
type * type_check_expr_gt(nodeAST * node, sym_tbl * scope){
    						type * left = type_check_expr(node->nodeValue.great.left, scope);
    						type * right = type_check_expr(node->nodeValue.great.right, scope);
    						if(valid_type_ordered(left, right) == -1){
    							print_type_to_string(left, type_buf);
    							print_type_to_string(right, type_buf_extra);
            					sprintf(err_buf, "Left is %s and Right is %s and they are not ordered at line %zd", type_buf, type_buf_extra, node->lineNumber);								add_msg_line(err_buf, current, node->lineNumber);
    							return new_invalid_type();
    						}
    						node->sym_tbl_ptr = new_bool_type();
    						return node->sym_tbl_ptr;
    						/*
    						returnNode->nodeType = EXPR_BINARY_OP_GREAT;
    						returnNode->nodeValue.great.left = _left;
    						returnNode->nodeValue.great.right = _right;
    						*/
}

type * type_check_expr_lteq(nodeAST * node, sym_tbl * scope){
    						type * left = type_check_expr(node->nodeValue.less.left, scope);
    						type * right = type_check_expr(node->nodeValue.less.right, scope);
    						if(valid_type_ordered(left, right) == -1){
    							print_type_to_string(left, type_buf);
    							print_type_to_string(right, type_buf_extra);
            					sprintf(err_buf, "Left is %s and Right is %s and they are not ordered at line %zd", type_buf, type_buf_extra, node->lineNumber);								add_msg_line(err_buf, current, node->lineNumber);
    							return new_invalid_type();
    						}
    						node->sym_tbl_ptr = new_bool_type();
    						return node->sym_tbl_ptr;
    						/*
    						returnNode->nodeType = EXPR_BINARY_OP_LESSEQUAL;
    						returnNode->nodeValue.less.left = _left;
    						returnNode->nodeValue.less.right = _right;
    						*/
}
type * type_check_expr_gteq(nodeAST * node, sym_tbl * scope){
    						type * left = type_check_expr(node->nodeValue.greatEqual.left, scope);
    						type * right = type_check_expr(node->nodeValue.greatEqual.right, scope);
    						if(valid_type_ordered(left, right) == -1){
    							print_type_to_string(left, type_buf);
    							print_type_to_string(right, type_buf_extra);
            					sprintf(err_buf, "Left is %s and Right is %s and they are not ordered at line %zd", type_buf, type_buf_extra, node->lineNumber);								add_msg_line(err_buf, current, node->lineNumber);
    							return new_invalid_type();
    						}
    						node->sym_tbl_ptr = new_bool_type();
    						return node->sym_tbl_ptr;
    						/*
  							returnNode->nodeType = EXPR_BINARY_OP_GREATEQUAL;
    						returnNode->nodeValue.greatEqual.left = _left;
    						returnNode->nodeValue.greatEqual.right = _right;
    						*/
}
/*
*	Returns  0 if proper type
*   Returns -1 if invalid type
*/

int type_check_slice_expr(nodeAST * node, sym_tbl * scope){
/*
slice               : '[' expr ':' expr ']'                       {$$ = newAddressSlice($2, $4, _treeNodeAllocator);}
                    | '[' expr ':'  ']'                           {$$ = newAddressSlice($2, NULL, _treeNodeAllocator);}
                    | '['  ':' expr ']'                           {$$ = newAddressSlice(NULL, $3, _treeNodeAllocator);}
                    | '['  ':'  ']'                               {$$ = newAddressSlice(NULL, NULL, _treeNodeAllocator);}
                    | '[' expr ':' expr ':' expr ']'              {$$ = newAddressSliceFull($2, $4, $6, _treeNodeAllocator);}
                    | '['  ':' expr ':' expr ']'                  {$$ = newAddressSliceFull(NULL, $3, $5, _treeNodeAllocator);}

    				returnNode->nodeType = EXPR_ADDRESS_SLICE;
    				returnNode->nodeValue.addressSlice.start = _start;
    				returnNode->nodeValue.addressSlice.end = _end;

    				returnNode->nodeType = EXPR_ADDRESS_SLICE_FULL;
    				returnNode->nodeValue.addressSliceFull.start = _start;
    				returnNode->nodeValue.addressSliceFull.end = _end;
    				returnNode->nodeValue.addressSliceFull.max = _max;
*/
    				type * value;
    				if( node->nodeType == EXPR_ADDRESS_SLICE ){
    					if(node->nodeValue.addressSlice.start != NULL){
    						value = get_alias_type(type_check_expr(node->nodeValue.addressSlice.start, scope));
    						if(value->type != LITERAL_INT){
            					sprintf(err_buf, "Expecting a int type for slice indexing at line %zd", node->lineNumber);
								add_msg_line(err_buf, current, node->lineNumber);
    							return -1;
    						}
    					}
    					if(node->nodeValue.addressSlice.end != NULL){
    						value = get_alias_type(type_check_expr(node->nodeValue.addressSlice.start, scope));
    						if(value->type != LITERAL_INT){
            					sprintf(err_buf, "Expecting a int type for slice indexing at line %zd", node->lineNumber);
								add_msg_line(err_buf, current, node->lineNumber);
    							return -1;
    						}
    					}
    					return 0;
    				}else{
    					if(node->nodeValue.addressSliceFull.start != NULL){
    						value = get_alias_type(type_check_expr(node->nodeValue.addressSlice.start, scope));
    						if(value->type != LITERAL_INT){
            					sprintf(err_buf, "Expecting a int type for slice indexing at line %zd", node->lineNumber);
								add_msg_line(err_buf, current, node->lineNumber);
    							return -1;
    						}
    					}
    					if(node->nodeValue.addressSliceFull.end != NULL){
    						value = get_alias_type(type_check_expr(node->nodeValue.addressSlice.start, scope));
    						if(value->type != LITERAL_INT){
            					sprintf(err_buf, "Expecting a int type for slice indexing at line %zd", node->lineNumber);
								add_msg_line(err_buf, current, node->lineNumber);
    							return -1;
    						}
    					}
    					if(node->nodeValue.addressSliceFull.max != NULL){
    						value = get_alias_type(type_check_expr(node->nodeValue.addressSlice.start, scope));
    						if(value->type != LITERAL_INT){
            					sprintf(err_buf, "Expecting a int type for slice indexing at line %zd", node->lineNumber);
								add_msg_line(err_buf, current, node->lineNumber);
    							return -1;
    						}
    					}
    					return 0;
    				}
}

type * type_check_expr_cast(nodeAST * node, sym_tbl * scope){
/*
: basic_type '(' expr ')'
returnNode->nodeType = EXPR_CAST;
returnNode->nodeValue.cast.target = _target;
returnNode->nodeValue.cast.expr = _expr;
*/
    type * left = type_basic_type(node->nodeValue.cast.target);
    type * right = type_check_expr(node->nodeValue.cast.expr, scope);
    if(valid_type_conversion(left, right) == -1){
       print_type_to_string(left, type_buf);
       print_type_to_string(right, type_buf_extra);
       sprintf(err_buf, "Invalid Cast. Attemped to cast %s to %s at line %zd", type_buf, type_buf_extra, node->lineNumber);
	   add_msg_line(err_buf, current, node->lineNumber);
       return new_invalid_type();
    }
    node->sym_tbl_ptr = left;
    return (left);
}

type * type_check_expr_append(nodeAST * node, sym_tbl * scope){
/*
    returnNode->nodeType = EXPR_APPEND;
    returnNode->nodeValue.append.target = _target;
    returnNode->nodeValue.append.expr = _expr;
    | append_ '(' primary_expr ',' expr_list ')'           {$$ = newAppend($3, $5, _treeNodeAllocator);}
    | append_ '(' primary_expr ',' expr_list ')' '[' expr ']'
					        {$$ = newIndex(newAppend($3, $5, _treeNodeAllocator), $8, _treeNodeAllocator);}
    | append_ '(' primary_expr ',' expr_list ')' slice
					        {$$ = newSlice(newAppend($3, $5, _treeNodeAllocator), $7, _treeNodeAllocator);}
*/
	type * ret = type_check_expr(node->nodeValue.append.target, scope);
	type * target = get_alias_type(type_check_expr(node->nodeValue.append.target, scope));
	type * expr;
	if(target->type != SLICE_TYPE){
		print_type_to_string(target, type_buf);
       	sprintf(err_buf, "First Argument Appended must be Slice. It is currently of %s at line %zd", type_buf ,node->lineNumber);
		add_msg_line(err_buf, current, node->lineNumber);
    	return new_invalid_type();
	}
	expr = type_check_expr_list(node->nodeValue.append.expr, scope); //This is an expression list
	if(expr->type != LIST_TYPE){
       	sprintf(err_buf, "Expected expression at line %zd",node->lineNumber);
		add_msg_line(err_buf, current, node->lineNumber);
    	return new_invalid_type();
	}
	//Here we deviate from golite to allow append(x, 1,2,3,4,4,5)
	for(int i = 0; i < expr->spec_type.list_type.list_size; i++){
		if(valid_type_comparison(expr->spec_type.list_type.type_list[i], get_alias_type(target->spec_type.slice_type.s_type)) == -1 && valid_type_comparison(expr->spec_type.list_type.type_list[i], (target->spec_type.slice_type.s_type)) == -1){
			print_type_to_string(get_alias_type(target->spec_type.slice_type.s_type), type_buf);
			print_type_to_string(expr->spec_type.list_type.type_list[i], type_buf_extra);
       		sprintf(err_buf, "Subsequent arguments must match %s. It is currently of %s at line %zd", type_buf, type_buf_extra ,node->lineNumber);
			add_msg_line(err_buf, current, node->lineNumber);
    		return new_invalid_type();
		}
	}
	node->sym_tbl_ptr = ret;
	return (ret);
}
type * type_check_expr(nodeAST * node, sym_tbl * scope){
	    	switch(node->nodeType){
    		case IDENTIFIER: return type_check_expr_id(node, scope);
    		case LITERAL_INT: return new_int_type();
    						/*
   	 						returnNode->nodeType = LITERAL_INT;
    						returnNode->nodeValue.intValue = _intValue;
							*/
			case LITERAL_FLOAT: return new_float_type();
			case LITERAL_RUNE: return new_rune_type();
			case LITERAL_STRING: return new_string_type();
			case EXPR_FUNC_CALL: return type_check_expr_func(node, scope);
            case EXPR_CAST:
            				return type_check_expr_cast(node, scope);
            case EXPR_INDEX:
            				return type_check_expr_index(node, scope);
            case EXPR_SELECTOR:
            				return type_check_expr_select(node, scope);
   	 		case EXPR_SLICE:
   	 						return type_check_expr_slice(node, scope);
    		case EXPR_BINARY_OP_MUL:
    						return type_check_expr_mul(node, scope);
    		case EXPR_BINARY_OP_DIV:
    						return type_check_expr_div(node, scope);
    		case EXPR_BINARY_OP_MOD:
    						return type_check_expr_mod(node, scope);
    		case EXPR_BINARY_OP_SUB:
    						return type_check_expr_sub(node, scope);
    		case EXPR_BINARY_OP_ADD:
    						return type_check_expr_add(node, scope);
    		case EXPR_BINARY_OP_LOGIC_AND:
    						return type_check_expr_and(node, scope);
    		case EXPR_BINARY_OP_LOGIC_OR:
    						return type_check_expr_or(node, scope);
    		case EXPR_BINARY_OP_XOR:
    						return type_check_expr_xor(node, scope);
    		case EXPR_BINARY_OP_OR:
    						return type_check_expr_bitOr(node, scope);
    		case EXPR_BINARY_OP_LSHIFT:
    						return type_check_expr_lshift(node, scope);
    		case EXPR_BINARY_OP_RSHIFT:
    						return type_check_expr_rshift(node, scope);
    		case EXPR_BINARY_OP_ANDNOT:
    						return type_check_expr_bitNot(node, scope);
    		case EXPR_UNIARY_OP_POS:
    						return type_check_expr_unary_pos(node, scope);
    		case EXPR_UNIARY_OP_NEG:
    						return type_check_expr_unary_neg(node, scope);
    		case EXPR_UNIARY_OP_NOT:
    						return type_check_expr_bitNot(node, scope);
    		case EXPR_UNIARY_OP_LOGIC_NOT:
    						return type_check_expr_not(node, scope);
    		case EXPR_BINARY_OP_EQUAL:
    						return type_check_expr_eq(node, scope);
    		case EXPR_BINARY_OP_NEQUAL:
    						return type_check_expr_neq(node, scope);
    		case EXPR_BINARY_OP_LESS:
    						return type_check_expr_lt(node, scope);
    		case EXPR_BINARY_OP_GREAT:
    						return type_check_expr_gt(node, scope);
    		case EXPR_BINARY_OP_LESSEQUAL:
    						return type_check_expr_lteq(node, scope);
    		case EXPR_BINARY_OP_GREATEQUAL:
    						return type_check_expr_gteq(node, scope);
    		case EXPR_BINARY_OP_AND:
    						return type_check_expr_bitAnd(node, scope);
    		case EXPR_APPEND:
    						return type_check_expr_append(node, scope);
    		default: return new_invalid_type();
    	}
}
int type_check_block(nodeAST * node, sym_tbl * scope){  //Also known as stmt_list
	/*
	stmt_list           : stmt  stmt_list                             {$$ = newStateList($1, $2, _treeNodeAllocator);}
                    	|                                             {$$ = NULL;}
    returnNode->nodeType = STATE_UTILITY_STATELIST;
    returnNode->nodeValue.stateList.state = _state;
    returnNode->nodeValue.stateList.next = _next;
	*/
	if(node == NULL)
		return 0;
    for(nodeAST * i = node; i != NULL; i = i->nodeValue.stateList.next){
    	if(i != NULL){
    		type_check_stmt(i->nodeValue.stateList.state, scope);
    	}
    }
    if(scope_flag == 1)
    	print_sym_tbl_scoped(scope, stream);

	return 0;
}

int type_check_print_stmt(nodeAST * node, sym_tbl * scope){
	/*
print_stmt          : print_ '(' expr_list ')' ';'                {$$ = newPrint($3, _treeNodeAllocator);}
                    | print_ '(' ')' ';'                          {$$ = newPrint(NULL, _treeNodeAllocator);}
    returnNode->nodeType = STATE_PRINT;
    returnNode->nodeValue.print.expr = _expr;
	*/
    if(node->nodeValue.print.expr != NULL){
    	type * list = type_check_expr_list(node->nodeValue.print.expr, scope);
    	for(int i = 0; i < list->spec_type.list_type.list_size; i ++){
    		if(list->spec_type.list_type.type_list[i]->type == INVALID_TYPE){
       		sprintf(err_buf, "Invalid expression inside print stmt line %zd", node->lineNumber);
			add_msg_line(err_buf, current, node->lineNumber);
    		}
    	}
    }

	return 0;
}

int type_check_ret_stmt(nodeAST * node, sym_tbl * scope){
	/*
    returnNode->nodeType = STATE_RETURN;
    returnNode->nodeValue.ret.expr = _expr;
	*/
	//We need to check if the return stmt is equivalent to the function return
	tbl_entry * ret_entry = sym_tbl_find_entry("return", scope);
	type * act_ret;
	if(node->nodeValue.ret.expr != NULL)
		act_ret = (type_check_expr(node->nodeValue.ret.expr, scope));
	else
		act_ret = NULL;
	if(ret_entry == NULL && act_ret != NULL){
		print_type_to_string(act_ret, type_buf_extra);
       	sprintf(err_buf, "Return statement must match void type. It is currently of %s at line %zd", type_buf_extra ,node->lineNumber);
		add_msg_line(err_buf, current, node->lineNumber);
		return 0;
	}else if(ret_entry != NULL && act_ret == NULL){
		print_type_to_string(ret_entry->type_info, type_buf_extra);
       	sprintf(err_buf, "Return statement must match %s. It is currently of void type at line %zd", type_buf_extra ,node->lineNumber);
		add_msg_line(err_buf, current, node->lineNumber);
		return 0;
	}else if(ret_entry == NULL && act_ret == NULL)
		return 0;
	type * ret_type = (ret_entry->type_info);
	if(valid_type_comparison(act_ret, ret_type) == -1 && valid_type_comparison(get_alias_type(act_ret), ret_type) == -1 && valid_type_comparison(act_ret, get_alias_type(ret_type)) == -1){
		print_type_to_string(act_ret, type_buf);
		print_type_to_string(ret_type, type_buf_extra);
       	sprintf(err_buf, "Return statement must match %s. It is currently of %s at line %zd", type_buf_extra, type_buf ,node->lineNumber);
		add_msg_line(err_buf, current, node->lineNumber);
	}
	return 0;
}

int type_check_if_cond(nodeAST * node, sym_tbl * scope){
	/*

if_cond             : expr                                        {$$ = newIfCondition(NULL, $1, _treeNodeAllocator);}
                    | simple_stmt expr                            {$$ = newIfCondition($1, $2, _treeNodeAllocator);}
    returnNode->nodeType = STATE_IF_CONDITION;
    returnNode->nodeValue.ifCondition.state = _state;
    returnNode->nodeValue.ifCondition.expr = _expr;
	*/
	if(node->nodeValue.ifCondition.state != NULL){
		type_check_simple_stmt(node->nodeValue.ifCondition.state, scope);
	}

	type * if_expr = get_alias_type(type_check_expr(node->nodeValue.ifCondition.expr, scope));
	if(if_expr->type != LITERAL_BOOL){
			print_type_to_string(if_expr, type_buf);
       		sprintf(err_buf, "If statement expression must be Boolean. It is currently of %s at line %zd",type_buf ,node->lineNumber);
			add_msg_line(err_buf, current, node->lineNumber);
	}
	return 0;
}

int type_check_if_stmt(nodeAST * node, sym_tbl * scope){
	/*
    returnNode->nodeType = STATE_IF;
    returnNode->nodeValue.ifBlock.condition = _condition;
    returnNode->nodeValue.ifBlock.block_true = _block_true;
if_stmt             : if_ if_cond block                           {$$ = newIfBlock($2, $3, _treeNodeAllocator);}
	*/
	sym_tbl * if_scope = new_sym_tbl_parent(scope, DEFAULT_SIZE);
	sym_tbl * block_scope = new_sym_tbl_parent(if_scope, DEFAULT_SIZE);
	type_check_if_cond(node->nodeValue.ifBlock.condition, if_scope);

	type_check_block(node->nodeValue.ifBlock.block_true, block_scope);
	if(scope_flag == 1)
    	print_sym_tbl_scoped(if_scope, stream);
	return 0;
}

int type_check_if_else_stmt(nodeAST * node, sym_tbl * scope){
	/*
    returnNode->nodeType = STATE_IF_ELSE;
    returnNode->nodeValue.ifElseBlock.condition = _condition;
    returnNode->nodeValue.ifElseBlock.block_true = _block_ture;
    returnNode->nodeValue.ifElseBlock.block_false = _block_false;
    | if_ if_cond '{' stmt_list '}' else_ else_block          {$$ = newIfElseBlock($2, $4, $7, _treeNodeAllocator);} //CHECK HERE
	else_block          : block                                       {$$ = $1;}
                    | if_stmt                                     {$$ = $1;}
	*/
	sym_tbl * new_scope = new_sym_tbl_parent(scope, DEFAULT_SIZE);
	type_check_if_cond(node->nodeValue.ifElseBlock.condition, new_scope);
	type_check_block(node->nodeValue.ifElseBlock.block_true, new_scope);

	if(node->nodeValue.ifElseBlock.block_false == NULL){ //Must be block
    	return 0;
    }
    type_check_stmt(node->nodeValue.ifElseBlock.block_false, scope);
    return 0;

}

int type_check_short_decl(nodeAST * node, sym_tbl * scope){
									int counter = 0;
									int num_added = 0;
									type * right = type_check_expr_list(node->nodeValue.shortDeclare.right, scope);
      								if(right->type == INVALID_TYPE)
      									return 0;
      								//type * left = type_check_expr_list(node->nodeValue.shortDeclare.left, scope);
      								for(nodeAST * i = node->nodeValue.shortDeclare.left; i != NULL; i = i->nodeValue.exprList.next){
										nodeAST * id = i->nodeValue.exprList.expr;

										if(id->nodeType != IDENTIFIER){
											sprintf(err_buf, "Non identifier in short declaration left side at line %zd" ,node->lineNumber);
											add_msg_line(err_buf, current, node->lineNumber);
											return 0;
										}else if(right->spec_type.list_type.list_size == counter){
											sprintf(err_buf, "ID list and expression list size do not match at line %zd" ,node->lineNumber);
											add_msg_line(err_buf, current, node->lineNumber);
											return 0;
										}else{
											tbl_entry * entry = sym_tbl_find_entry_scoped(id->nodeValue.identifier, scope);
											if(strcmp(id->nodeValue.identifier, "_") == 0){

											}
											else if(entry == NULL){
												sym_tbl_add_entry(new_tbl_entry(id->nodeValue.identifier, id->lineNumber  ,id , right->spec_type.list_type.type_list[counter]), scope);
												num_added++;
											}else{
												if(valid_type_comparison(entry->type_info, right->spec_type.list_type.type_list[counter]) == -1){ //Need to check that type with type_check_expr_list
													print_type_to_string(entry->type_info, type_buf);
													print_type_to_string(right->spec_type.list_type.type_list[counter], type_buf_extra);
													sprintf(err_buf, "ID %s was previous declared with type %s. Assigned type is %s at line %zd" ,id->nodeValue.identifier,  type_buf, type_buf_extra ,node->lineNumber);
													add_msg_line(err_buf, current, node->lineNumber);
												return 0;
												}
											}

										}
										counter++;
									}
      								if(num_added == 0){
										sprintf(err_buf, "No new names on left hand side of := at line %zd" ,node->lineNumber);
										add_msg_line(err_buf, current, node->lineNumber);
      								}
      								return 0;
}


int type_check_simple_stmt(nodeAST * node, sym_tbl * scope){
/*
simple_stmt_v       : expr                                        {$$ = $1;}
                    | expr incre_                                 {$$ = newInc($1, _treeNodeAllocator);}
                    | expr decre_                                 {$$ = newDec($1, _treeNodeAllocator);}
                    | assign_stmt                                 {$$ = $1;}
                    | short_decl                                  {$$ = $1;}
                    |                                             {$$ = NULL;}
    returnNode->nodeType = STATE_INC;
    returnNode->nodeValue.inc.expr = _expr;
*/	    				if(node == NULL)
    					return 0;
                    switch(node->nodeType){
                    	case STATE_INC:
                    					{
                    						type * inc_type = get_alias_type(type_check_expr(node->nodeValue.inc.expr, scope));
                    						if(inc_type->type != LITERAL_INT && inc_type->type != LITERAL_FLOAT && inc_type->type != LITERAL_RUNE){
                    							print_type_to_string(inc_type, type_buf);
       											sprintf(err_buf, "Cannot convert 1 to %s at line %zd",type_buf ,node->lineNumber);
												add_msg_line(err_buf, current, node->lineNumber);
                    						}
                    						break;
                    					}
                    	case STATE_DEC:{
                    						type * dec_type = get_alias_type(type_check_expr(node->nodeValue.dec.expr, scope));
                    						if(dec_type->type != LITERAL_INT && dec_type->type != LITERAL_FLOAT && dec_type->type != LITERAL_RUNE){
                    							print_type_to_string(dec_type, type_buf);
       											sprintf(err_buf, "Cannot convert 1 to %s at line %zd",type_buf ,node->lineNumber);
												add_msg_line(err_buf, current, node->lineNumber);
                    						}
                    						break;
                    					}
//short_decl          : expr_list decla_ expr_list                  {$$ = newShortDeclare($1, $3, _treeNodeAllocator);}
/*
    returnNode->nodeType = STATE_SHORT_DECLARE;
    returnNode->nodeValue.shortDeclare.left = _left;
    returnNode->nodeValue.shortDeclare.right = _right;
*/
    /*
assign_stmt         : expr_list '=' expr_list                     {$$ = newAssign($1, $3, _treeNodeAllocator);}
                    | expr add_eq_ expr                           {$$ = newAssignAdd($1, $3, _treeNodeAllocator);}
                    | expr minus_eq_ expr                         {$$ = newAssignSub($1, $3, _treeNodeAllocator);}
                    | expr mult_eq_ expr                          {$$ = newAssignMul($1, $3, _treeNodeAllocator);}
                    | expr div_eq_ expr                           {$$ = newAssignDiv($1, $3, _treeNodeAllocator);}
                    | expr mod_eq_ expr                           {$$ = newAssignMod($1, $3, _treeNodeAllocator);}
                    | expr amp_eq_ expr                           {$$ = newAssignAnd($1, $3, _treeNodeAllocator);}
                    | expr vb_eq_ expr                            {$$ = newAssignOr($1, $3, _treeNodeAllocator);}
                    | expr caret_eq_ expr                         {$$ = newAssignXor($1, $3, _treeNodeAllocator);}
                    | expr ls_eq_ expr                            {$$ = newAssignShiftLeft($1, $3, _treeNodeAllocator);}
                    | expr rs_eq_ expr                            {$$ = newAssignShiftRight($1, $3, _treeNodeAllocator);}
                    | expr unknown_eq_ expr                       {$$ = newAssignAndNot($1, $3, _treeNodeAllocator);}
*/

                    	case STATE_SHORT_DECLARE: type_check_short_decl(node, scope); break;
                    	case STATE_ASSIGN:  {
                    						type * left = type_check_expr_list(node->nodeValue.assign.left, scope);
      										type * right = type_check_expr_list(node->nodeValue.assign.right, scope);
      										if(left->spec_type.list_type.list_size != right->spec_type.list_type.list_size){
												sprintf(err_buf, "Expression list size does not match at line %zd" ,node->lineNumber);
												add_msg_line(err_buf, current, node->lineNumber);
      										}else{

      										for(int i = 0; i < left->spec_type.list_type.list_size; i++){
    											if(left->spec_type.list_type.type_list[i]->type != TYPE_UNDERSCORE){
      											if(valid_type_comparison(left->spec_type.list_type.type_list[i], right->spec_type.list_type.type_list[i]) == -1){
      												print_type_to_string(left->spec_type.list_type.type_list[i], type_buf);
      												print_type_to_string(right->spec_type.list_type.type_list[i], type_buf_extra);
													sprintf(err_buf, "Invalid type. Left Argument is of %s. Right is currently of %s at line %zd",type_buf , type_buf_extra,node->lineNumber);
													add_msg_line(err_buf, current, node->lineNumber);
													return 0;
      												}
      											}
      											}
      										}
      										break;
      										}
                    	case STATE_ASSIGN_ADD: {
                    							type * left = type_check_expr(node->nodeValue.assignAdd.left, scope);
                    							type * right = type_check_expr(node->nodeValue.assignAdd.right, scope);
                    							if(valid_type_comparison(left, right) == -1 || (left->type != LITERAL_INT && left->type != LITERAL_RUNE && left->type != LITERAL_FLOAT)){
                    								print_type_to_string(left, type_buf);
      												print_type_to_string(right, type_buf_extra);
													sprintf(err_buf, "Invalid type. Left Argument is of %s. Right is currently of %s at line %zd",type_buf , type_buf_extra,node->lineNumber);
													add_msg_line(err_buf, current, node->lineNumber);
                    							}
                    							break;
                    						   }
                    	case STATE_ASSIGN_SUB: {
                    							type * left = type_check_expr(node->nodeValue.assignSub.left, scope);
                    							type * right = type_check_expr(node->nodeValue.assignSub.right, scope);
                    							if(valid_type_comparison(left, right) == -1 || (left->type != LITERAL_INT && left->type != LITERAL_RUNE && left->type != LITERAL_FLOAT)){
                    								print_type_to_string(left, type_buf);
      												print_type_to_string(right, type_buf_extra);
													sprintf(err_buf, "Invalid type. Left Argument is of %s. Right is currently of %s at line %zd",type_buf , type_buf_extra,node->lineNumber);
													add_msg_line(err_buf, current, node->lineNumber);
                    							}
                    							break;
                    						   }
                    	case STATE_ASSIGN_MUL: {
                    							type * left = type_check_expr(node->nodeValue.assignMul.left, scope);
                    							type * right = type_check_expr(node->nodeValue.assignMul.right, scope);
                    							//printf("%d %d %d\n", left->type, node->nodeValue.assignMul.right->nodeType, EXPR_BINARY_OP_ADD);
                    							if(valid_type_comparison(left, right) == -1 || (left->type != LITERAL_INT && left->type != LITERAL_RUNE && left->type != LITERAL_FLOAT)){
                    								print_type_to_string(left, type_buf);
      												print_type_to_string(right, type_buf_extra);
													sprintf(err_buf, "Invalid type. Left Argument is of %s. Right is currently of %s at line %zd",type_buf , type_buf_extra,node->lineNumber);
													add_msg_line(err_buf, current, node->lineNumber);
                    							}
                    							break;
                    						   }
                    	case STATE_ASSIGN_DIV: {
                    							type * left = type_check_expr(node->nodeValue.assignDiv.left, scope);
                    							type * right = type_check_expr(node->nodeValue.assignDiv.right, scope);
                    							if(valid_type_comparison(left, right) == -1 || (left->type != LITERAL_INT && left->type != LITERAL_RUNE && left->type != LITERAL_FLOAT)){
                    								print_type_to_string(left, type_buf);
      												print_type_to_string(right, type_buf_extra);
													sprintf(err_buf, "Invalid type. Left Argument is of %s. Right is currently of %s at line %zd",type_buf , type_buf_extra,node->lineNumber);
													add_msg_line(err_buf, current, node->lineNumber);
                    							}
                    							break;
                    						   }
                    	case STATE_ASSIGN_MOD: {
                    							type * left = type_check_expr(node->nodeValue.assignMod.left, scope);
                    							type * right = type_check_expr(node->nodeValue.assignMod.right, scope);
                    							if(valid_type_comparison(left, right) == -1 || (left->type != LITERAL_INT && left->type != LITERAL_RUNE)){
                    								print_type_to_string(left, type_buf);
      												print_type_to_string(right, type_buf_extra);
													if(left->type != LITERAL_FLOAT)
														sprintf(err_buf, "Invalid type. Left Argument is of %s. Right is currently of %s at line %zd",type_buf , type_buf_extra,node->lineNumber);
													else
														sprintf(err_buf, "Mod cannot be used by floats. Left Argument is of %s. Right is currently of %s at line %zd",type_buf , type_buf_extra,node->lineNumber);
													add_msg_line(err_buf, current, node->lineNumber);
                    							}
                    							break;
                    						   }
                    	case STATE_ASSIGN_AND: {
                    							type * left = type_check_expr(node->nodeValue.assignAnd.left, scope);
                    							type * right = type_check_expr(node->nodeValue.assignAnd.right, scope);
                    							if(valid_type_comparison(left, right) == -1 || (left->type != LITERAL_INT && left->type != LITERAL_RUNE)){
                    								print_type_to_string(left, type_buf);
      												print_type_to_string(right, type_buf_extra);
													sprintf(err_buf, "Must be boolean type. Left Argument is of %s. Right is %s at line %zd",type_buf , type_buf_extra,node->lineNumber);
													add_msg_line(err_buf, current, node->lineNumber);
                    							}
                    							break;
                    						   }
                    	case STATE_ASSIGN_OR:	   {
                    							type * left = type_check_expr(node->nodeValue.assignOr.left, scope);
                    							type * right = type_check_expr(node->nodeValue.assignOr.right, scope);
                    							if(valid_type_comparison(left, right) == -1 || (left->type != LITERAL_INT && left->type != LITERAL_RUNE) ){
                    								print_type_to_string(left, type_buf);
      												print_type_to_string(right, type_buf_extra);
													sprintf(err_buf, "Must be boolean type. Left Argument is of %s. Right is %s at line %zd",type_buf , type_buf_extra,node->lineNumber);
													add_msg_line(err_buf, current, node->lineNumber);
                    							}
                    							break;
                    						   }
                    	case STATE_ASSIGN_XOR: {
                    							type * left = type_check_expr(node->nodeValue.assignXor.left, scope);
                    							type * right = type_check_expr(node->nodeValue.assignXor.right, scope);
                    							if(valid_type_comparison(left, right) == -1 || (left->type != LITERAL_INT && left->type != LITERAL_RUNE) ){
                    								print_type_to_string(left, type_buf);
      												print_type_to_string(right, type_buf_extra);
													sprintf(err_buf, "Must be boolean type. Left Argument is of %s. Right is %s at line %zd",type_buf , type_buf_extra,node->lineNumber);
													add_msg_line(err_buf, current, node->lineNumber);
                    							}
                    							break;
                    						   }
                    	case STATE_ASSIGN_SHIFTLEFT: {
                    							type * left = type_check_expr(node->nodeValue.assignMod.left, scope);
                    							type * right = type_check_expr(node->nodeValue.assignMod.right, scope);
                    							if(valid_type_comparison(left, right) == -1 || (left->type != LITERAL_INT && left->type != LITERAL_RUNE) ){
                    								print_type_to_string(left, type_buf);
      												print_type_to_string(right, type_buf_extra);
													sprintf(err_buf, "Must be of int type. Left Argument is of %s. Right is %s at line %zd",type_buf , type_buf_extra,node->lineNumber);
													add_msg_line(err_buf, current, node->lineNumber);
                    							}
                    							break;
                    						   }
                    	case STATE_ASSIGN_SHIFTRIGHT: {
                    							type * left = type_check_expr(node->nodeValue.assignMod.left, scope);
                    							type * right = type_check_expr(node->nodeValue.assignMod.right, scope);
                    							if(valid_type_comparison(left, right) == -1 || (left->type != LITERAL_INT && left->type != LITERAL_RUNE)){
                    								print_type_to_string(left, type_buf);
      												print_type_to_string(right, type_buf_extra);
													sprintf(err_buf, "Must be int type. Left Argument is of %s. Right is %s at line %zd",type_buf , type_buf_extra,node->lineNumber);
													add_msg_line(err_buf, current, node->lineNumber);
                    							}
                    							break;
                    						   }
                    	case STATE_ASSIGN_ANDNOT: {
                    							type * left = type_check_expr(node->nodeValue.assignMod.left, scope);
                    							type * right = type_check_expr(node->nodeValue.assignMod.right, scope);
                    							if(valid_type_comparison(left, right) == -1 || (left->type != LITERAL_INT && left->type != LITERAL_RUNE) ){
                    								print_type_to_string(left, type_buf);
      												print_type_to_string(right, type_buf_extra);
													sprintf(err_buf, "Must be boolean type. Left Argument is of %s. Right is %s at line %zd",type_buf , type_buf_extra,node->lineNumber);
													add_msg_line(err_buf, current, node->lineNumber);
                    							}
                    							break;
                    						   }
                    	default: type_check_expr(node, scope); break;
                    }
                    return 0;
}

int type_check_switch_stmt(nodeAST * node, sym_tbl * scope){
/*
    returnNode->nodeType = STATE_SWITCH;
    returnNode->nodeValue.switchBlock.condition = _condition;
    returnNode->nodeValue.switchBlock.block = _block;
switch_stmt         : switch_ switch_cond '{' case_clause_list '}'{$$ = newSwitchBlock($2, $4, _treeNodeAllocator);}

switch_cond         : simple_stmt  expr                           {$$ = newSwitchCondition($1, $2, _treeNodeAllocator);}
                    | simple_stmt                                 {$$ = newSwitchCondition($1, NULL, _treeNodeAllocator);}
                    | expr                                        {$$ = newSwitchCondition(NULL, $1, _treeNodeAllocator);}
                    |                                             {$$ = newSwitchCondition(NULL, NULL, _treeNodeAllocator);}
    returnNode->nodeValue.switchCondition.state = _state;
    returnNode->nodeValue.switchCondition.expr = _expr;
case_clause_list    : case_clause case_clause_list                {$$ = newCaseList($1, $2, _treeNodeAllocator);}
                    |                                             {$$ = NULL;}
    returnNode->nodeValue.caseList.state = _state;
    returnNode->nodeValue.caseList.next = _next;
case_clause         : case_ expr_list ':' stmt_list               {$$ = newCaseClause($2, $4, _treeNodeAllocator);}
			        | default_ ':' stmt_list                      {$$ = newCaseClause(NULL, $3, _treeNodeAllocator);}
	returnNode->nodeValue.caseClause.expr = _expr;
    returnNode->nodeValue.caseClause.state = _state;
*/
    type * switch_expr;
	sym_tbl * switch_scope = new_sym_tbl_parent(scope, DEFAULT_SIZE);
	sym_tbl * new_scope;
	nodeAST * switch_cond = node->nodeValue.forBlock.condition;
	if(switch_cond->nodeValue.switchCondition.state != NULL){
		type_check_simple_stmt(switch_cond->nodeValue.switchCondition.state, switch_scope);
	}
	if(switch_cond->nodeValue.switchCondition.expr != NULL){
		switch_expr = type_check_expr(switch_cond->nodeValue.switchCondition.expr, switch_scope);
	}else{
		switch_expr = new_bool_type();
	}
	if(node->nodeValue.switchBlock.block != NULL){
		nodeAST * switch_block = node->nodeValue.switchBlock.block;
		for(nodeAST * i = switch_block; i != NULL; i = i->nodeValue.caseList.next){
			if(i != NULL){
				nodeAST * case_cls = i->nodeValue.caseList.state;
				new_scope = new_sym_tbl_parent(switch_scope, DEFAULT_SIZE);
				type_check_block(case_cls->nodeValue.caseClause.state, new_scope);
				if(case_cls->nodeValue.caseClause.expr != NULL){

					sym_tbl * case_scope = new_sym_tbl_parent(new_scope, DEFAULT_SIZE);
					type * case_type_list = type_check_expr_list(case_cls->nodeValue.caseClause.expr, case_scope);
					for(int j = 0; j < case_type_list->spec_type.list_type.list_size; j++){
						if(switch_expr != NULL){
						//Compare the type
							if( valid_type_comparison( switch_expr, case_type_list->spec_type.list_type.type_list[j]) == -1 && valid_type_comparison(get_alias_type(switch_expr), case_type_list->spec_type.list_type.type_list[j]) == -1 && valid_type_comparison( switch_expr, get_alias_type(case_type_list->spec_type.list_type.type_list[j])) == -1){
								print_type_to_string(switch_expr, type_buf);
								print_type_to_string(case_type_list->spec_type.list_type.type_list[j], type_buf_extra);
       							sprintf(err_buf, "Switch statment expression must match case expression %s. It is currently of %s at line %zd", type_buf, type_buf_extra ,case_cls->nodeValue.caseClause.expr->lineNumber);
								add_msg_line(err_buf, current, node->lineNumber);
							}
						}
					}
   					if(scope_flag == 1)
    					print_sym_tbl_scoped(switch_scope, stream);

				}

			}
		}
	}

    if(scope_flag == 1)
    	print_sym_tbl_scoped(switch_scope, stream);
	return 0;
}

int type_check_for_stmt(nodeAST * node, sym_tbl * scope){
/*
    returnNode->nodeType = STATE_FOR;
    returnNode->nodeValue.forBlock.condition = _condition;
    returnNode->nodeValue.forBlock.block = _block;

    returnNode->nodeType = STATE_UTILITY_FOR_CLAUSE;
    returnNode->nodeValue.forClause.init = _init;
    returnNode->nodeValue.forClause.condition = _condition;
    returnNode->nodeValue.forClause.step = _step;
for_stmt_clause     : simple_stmt_v ';' condition ';' simple_stmt_v {$$ = newForCluase($1, $3, $5, _treeNodeAllocator);}
for_stmt            : for_ for_clause block                       {$$ = newForBlock($2, $3, _treeNodeAllocator);}

*/
	sym_tbl * for_scope = new_sym_tbl_parent(scope, DEFAULT_SIZE);
	sym_tbl * new_scope = new_sym_tbl_parent(for_scope, DEFAULT_SIZE);
	nodeAST * for_cond = node->nodeValue.forBlock.condition;
	type * cond = NULL;
	if(for_cond != NULL){
		if(for_cond->nodeType == STATE_UTILITY_FOR_CLAUSE){
			if(for_cond->nodeValue.forClause.init != NULL)
				type_check_simple_stmt(for_cond->nodeValue.forClause.init, for_scope);
			if(for_cond->nodeValue.forClause.condition != NULL)
				cond = type_check_expr(for_cond->nodeValue.forClause.condition, for_scope);
			else
				cond = new_bool_type();
			//printf("Type : %d %d %d\n", for_cond->nodeValue.forClause.condition->nodeType, EXPR_BINARY_OP_LESSEQUAL, node->lineNumber);

			if(for_cond->nodeValue.forClause.step != NULL)
				type_check_simple_stmt(for_cond->nodeValue.forClause.step, for_scope);

		}
		else{ //Otherwise it is just an expression
			cond = get_alias_type(type_check_expr(for_cond, scope));
		}

		if(cond->type != LITERAL_BOOL){
			print_type_to_string(cond, type_buf);
       		sprintf(err_buf, "For statement expression must be Boolean. It is currently of %s at line %zd",type_buf ,for_cond->lineNumber);
			add_msg_line(err_buf, current, node->lineNumber);
		}


	}
	type_check_block(node->nodeValue.forBlock.block, new_scope);

    if(scope_flag == 1){
    	print_sym_tbl_scoped(for_scope, stream);
    }
	return 0;
}

int type_check_stmt(nodeAST * node, sym_tbl * scope){
	/*
stmt                : var_decl                                    {$$ = $1;}
                    | type_decl                                   {$$ = $1;}
                    | block                                       {$$ = $1;}
                    | print_stmt                                  {$$ = $1;}
                    | println_stmt                                {$$ = $1;}
                    | return_stmt                                 {$$ = $1;}
                    | if_stmt                                     {$$ = $1;}
                    | simple_stmt                                 {$$ = $1;}
                    | switch_stmt                                 {$$ = $1;}
                    | for_stmt                                    {$$ = $1;}
                    | break_ ';'                                  {$$ = newControlBreak(_treeNodeAllocator);}
                    | continue_ ';'                               {$$ = newControlContinue(_treeNodeAllocator);}
	*/
    if(node == NULL)
    	return 0;
   	switch(node->nodeType){
   		case PROG_DECLARE_VAR_LIST: type_check_var_decl_list(node, scope); break;
   		case PROG_DECLARE_TYPE_LIST: type_check_type_decl_list(node, scope); break;
   		case STATE_UTILITY_STATELIST: 	{
   										sym_tbl * new_scope = new_sym_tbl_parent(scope, DEFAULT_SIZE);
   										type_check_block(node, new_scope); break;
   										}
   		case STATE_PRINT: type_check_print_stmt(node, scope); break;
   		case STATE_PRINTLN: type_check_print_stmt(node, scope); break;
   		case STATE_RETURN: type_check_ret_stmt(node, scope); break;
   		case STATE_IF: type_check_if_stmt(node, scope); break;
   		case STATE_IF_ELSE: type_check_if_else_stmt(node, scope); break;
   		case STATE_SWITCH: type_check_switch_stmt(node, scope); break;
   		case STATE_FOR: type_check_for_stmt(node, scope); break;
   		case STATE_CONTROL_BREAK: break;
   		case STATE_CONTROL_CONTINUE: break;
   		default: type_check_simple_stmt(node, scope); break;
   	}

	return 0;
}


#endif