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
#define MAX_ID_LENGTH	256
#define FILE_PATH	"log.txt"

extern nodeAST* _ast;
struct type_check_data * tcsystem;

struct msg_list head;
struct msg_list * current;

typedef struct msg_list{
	int line;
	char * msg;
	struct msg_list * next;
}msg_list;

typedef struct type_check_data{
	sym_tbl * current_tbl; //Current scope we are working with
	sym_tbl * root_tbl;
	int hash_table_size;
	int level;
}type_check;

/*
* Method List
* ___________________________________________________________________________________________________________
*/
type_check * new_type_check(int size);
void free_type_check(type_check *);
void free_msg_list(msg_list *);

int add_msg(char * msg, msg_list *);
int add_msg_line(char * msg, msg_list *, int line);
int print_err_msg(msg_list head);
int type_check_prog();
int type_check_prog_list(nodeAST * node, sym_tbl * scope);
int type_check_func(nodeAST * node, sym_tbl * scope);
int type_check_type(nodeAST * node, sym_tbl * scope);
int type_check_var_decl_list(nodeAST * node , sym_tbl * scope);
int type_check_var_decl(nodeAST * node , sym_tbl * scope);
type * type_check_expr(nodeAST * node, sym_tbl * scope);

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
	current = &head;
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
	added->msg = alloc(256, sizeof(char));
	strcpy(added->msg, msg);
	added->next = NULL;
	current_node->next = added;
	current_node = added;

	return 0;
}

int print_err_msg(msg_list head){
	msg_list * i = &head;
	for(i; i != NULL; i = i->next){
		printf("%s at line %d\n", i->msg, i->line);
	}

	return 0;
}

int type_check_prog(){
	if(_ast->nodeType != PROG_PROGRAM){
		fprintf(stderr, "Start Node Invalid\n");
	}
	tcsystem = new_type_check(DEFAULT_SIZE);
	tcsystem->current_tbl = new_sym_tbl(DEFAULT_SIZE);
	add_child_sym_tbl(tcsystem->root_tbl, tcsystem->current_tbl);
	//At this point We should have two things
	//returnNode->nodeValue.program.package = _package;
    //returnNode->nodeValue.program.program = _program;

    //The package has nothing we need to add so we ignore that
    type_check_prog_list(_ast->nodeValue.program.program, tcsystem->current_tbl); //Every type check error will be added to the err_msg list
    print_err_msg(head);
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
    for(nodeAST * i = node; i != NULL; i = node->nodeValue.progList.next){
    	switch(i->nodeValue.progList.next->nodeType){
    		case PROG_DECLARE_VAR_LIST: type_check_var_decl_list(i->nodeValue.progList.prog, scope); break;
    		case PROG_DECLARE_TYPE_LIST: type_check_type(i->nodeValue.progList.prog, scope); break;
    		case PROG_FUNCTION: type_check_func(i->nodeValue.progList.prog, scope); break;
    		default: add_msg_line("Error Unexpected NodeType at prog_list", current, node->lineNumber); break;
    	}
    }
    return 0;
}

int type_check_var_decl_list(nodeAST * node, sym_tbl * scope){
	//PROG_DECLARE_VAR_LIST
	//returnNode->nodeValue.varDeclareList.varDeclare = _varDeclare;
    //returnNode->nodeValue.varDeclareList.next = _next;
    //_varDeclare is either newVarDeclareList or newVarDeclare
	for(nodeAST * i = node; i != NULL; i = node->nodeValue.varDeclareList.next, scope){
		switch(i->nodeValue.varDeclareList.varDeclare->nodeType){
			case PROG_DECLARE_VAR: type_check_var_decl(i->nodeValue.varDeclareList.varDeclare, scope); break;
			case PROG_DECLARE_VAR_LIST: type_check_var_decl_list(i->nodeValue.varDeclareList.varDeclare, scope); break;
			default: add_msg_line("Error Unexpected NodeType at type_check_var", current, node->lineNumber); break;
		}
	}
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

	msg_list * id_list = prepare_id_list(node->nodeValue.varDeclare.idList); //var_decl must have an id_list
	if(node->nodeValue.varDeclare.initExpr == NULL){
		type * expr_type = type_check_expr(node->nodeValue.varDeclare.initExpr, scope);
		//Now that we have all the types
		int type_iterator = 0;
		for(msg_list * i = id_list; i != NULL; i = i->next){
			if(type_iterator > expr_type->list_size){
				add_msg_line("var declaration number of id does not max number of expr type", current, node->lineNumber);
				break;
			}
			tbl_entry * current_entry = sym_tbl_find_entry(i->msg, scope);
			if(current != NULL){ //Redeclaration in the same scope
				add_msg_line("Redeclaration of ID", current, node->lineNumber);
				break;
			}else if(expr_type->list[type_iterator] == NULL){
				add_msg_line("Invalid Type", current, node->lineNumber);
				break;
			}else{//Everything is good
				//We need to add these things to the symbol table
				sym_tbl_add_entry(new_tbl_entry(i->msg, i->line, NULL, expr_type->list[type_iterator]), scope);
			}
			type_iterator++;
		}
		if(type_iterator != expr_type->list_size){
			add_msg_line("var declaration number of id does not max number of expr type", current, node->lineNumber);
		}
	}
	else if(node->nodeValue.varDeclare.type == NULL){

	}
	else{

	}
}

msg_list * prepare_id_list(nodeAST * node){
	msg_list * head = alloc(1, sizeof(msg_list));
	msg_list * current = head;
	// returnNode->nodeValue.identifierList.identifier = _identifier;
    // returnNode->nodeValue.identifierList.next = _next;
    head->msg = alloc(MAX_ID_LENGTH, sizeof(char)); //MAX_ID of 256
    strcpy(head->msg, node->nodeValue.identifierList.identifier->nodeValue.identifier);
    for(nodeAST * i = node->nodeValue.identifierList.next; i != NULL; i = i->nodeValue.identifierList.next){
    	add_msg_line(i->nodeValue.identifierList.identifier->nodeValue.identifier, current, i->nodeValue.identifierList.identifier->lineNumber);
    }
    return head;
}
#endif