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

char err_buf[256];

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
		printf("%s\n", i->msg);
	}

	return 0;
}

int type_check_prog(){
	if(_ast->nodeType != PROG_PROGRAM){
		fprintf(stderr, "Start Node Invalid\n");
		exit(1);
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
    		case PROG_DECLARE_TYPE_LIST: type_check_type_decl_list(i->nodeValue.progList.prog, scope); break;
    		case PROG_FUNCTION: type_check_func(i->nodeValue.progList.prog, scope); break;
    		default:
    					sprintf(err_buf, "Error Unexpected NodeType at line %d", node->lineNumber);
    					add_msg_line(err_buf, current, node->lineNumber); break;
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
			default:
    					sprintf(err_buf, "Error Unexpected NodeType at line %d", node->lineNumber);
    					add_msg_line(err_buf, current, node->lineNumber); break;
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
	if(node->nodeValue.varDeclare.type == NULL){
		type * expr_type = type_check_expr(node->nodeValue.varDeclare.initExpr, scope);
		//Now that we have all the types
		int type_iterator = 0;
		for(msg_list * i = id_list; i != NULL; i = i->next){
			tbl_entry * current_entry = sym_tbl_find_entry(i->msg, scope);
			if(current_entry != NULL){ //Redeclaration in the same scope
				sprintf(err_buf, "Redeclaration of %s when declaring id at line %d. \nPrevious declaration at line %d", i->msg, node->lineNumber, current_entry->line_num);
				add_msg_line(err_buf, current, node->lineNumber);
				break;
			}else{//Everything is good
				//We need to add these things to the symbol table
				sym_tbl_add_entry(new_tbl_entry(i->msg, i->line, NULL, expr_type->spec_type.list_type.type_list[type_iterator]), scope);
			}
			type_iterator++;
		}
	}
	else if(node->nodeValue.varDeclare.initExpr == NULL){
		type * type_decl = type_check_type(node->nodeValue.varDeclare.initExpr, scope);
		int type_iterator = 0;
		for(msg_list * i = id_list; i != NULL; i = i->next){
			tbl_entry * current_entry = sym_tbl_find_entry(i->msg, scope);
			if(current_entry != NULL){ //Redeclaration in the same scope
				sprintf(err_buf, "Redeclaration of %s when declaring id at line %d. \nPrevious declaration at line %d", i->msg, node->lineNumber, current_entry->line_num);
				add_msg_line(err_buf, current, node->lineNumber);
				break;
			}else{//Everything is good
				//We need to add these things to the symbol table
				sym_tbl_add_entry(new_tbl_entry(i->msg, i->line, NULL, type_decl), scope);
			}
			type_iterator++;
		}
	}
	else{
		type * expr_decl = type_check_expr(node->nodeValue.varDeclare.initExpr, scope);
		type * type_decl = type_check_type(node->nodeValue.varDeclare.initExpr, scope);
		int type_iterator = 0;
		for(msg_list * i = id_list; i != NULL; i = i->next){
			if(compare_type(type_decl->spec_type.list_type.type_list[type_iterator], expr_decl->spec_type.list_type.type_list[type_iterator]) != 0){
				sprintf(err_buf, "left and right type does not match at line %d", node->lineNumber);
				add_msg_line(err_buf, current, node->lineNumber);
				break;
			}
			tbl_entry * current_entry = sym_tbl_find_entry(i->msg, scope);
			if(current_entry != NULL){ //Redeclaration in the same scope
				sprintf(err_buf, "Redeclaration of %s when declaring id at line %d. \nPrevious declaration at line %d", i->msg, node->lineNumber, current_entry->line_num);
				add_msg_line(err_buf, current, node->lineNumber);
				break;
			}else{//Everything is good
				//We need to add these things to the symbol table
				sym_tbl_add_entry(new_tbl_entry(i->msg, i->line, NULL, type_decl), scope);
			}
			type_iterator++;
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
	tbl_entry * current_entry = sym_tbl_find_entry(node->nodeValue.function.identifier->nodeValue.identifier, scope);
	if(current_entry != NULL){ //Redeclaration in the same scope
		sprintf(err_buf, "Redeclaration of %s when declaring function at line %d. \nPrevious declaration at line %d", node->nodeValue.function.identifier->nodeValue.identifier, node->lineNumber, current_entry->line_num);
		add_msg_line(err_buf, current, node->lineNumber);
		return 0;
	}
	type * function = alloc(1, sizeof(type));
	type * return_type = NULL;
	//add it to the new scope immediately to allow for recursion
	sym_tbl_add_entry(new_tbl_entry(node->nodeValue.function.identifier->nodeValue.identifier, node->lineNumber, node, function), scope);
	sym_tbl * new_scope = new_sym_tbl_parent(scope, DEFAULT_SIZE);
	if(node->nodeValue.function.type != NULL)
		return_type = type_check_type(node->nodeValue.function.type, new_scope);
	type * param_type = type_check_params_list(node->nodeValue.function.pramList, new_scope);

	function->spec_type.func_type.params_type = param_type;
	function->spec_type.func_type.return_type = return_type;
	//Now we actually need to add the return type to the new scope
	sym_tbl_add_entry(new_tbl_entry("return", node->lineNumber, node, return_type), new_scope);

	type_check_block(node->nodeValue.function.block, new_scope);
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
	type * param_list = new_list_type(node); //Initializes thew new empty list_type
    for(nodeAST * i = node; i != NULL; i = i->nodeValue.pramDeclareList.next){
    	type * id_list_type = type_check_type(i->nodeValue.pramDeclareList.pram->nodeValue.pramDeclare.type, scope);
    	//Get the type of the id_list type
    	for(nodeAST * j = i->nodeValue.pramDeclare.idList; j != NULL; j = j->nodeValue.identifierList.next){
    		sym_tbl_add_entry(new_tbl_entry(j->nodeValue.identifierList.identifier->nodeValue.identifier, j->nodeValue.identifierList.identifier->lineNumber, j->nodeValue.identifierList.identifier, id_list_type), scope);
    	}
    }

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
    for(nodeAST * i = node; i != NULL; i = i->nodeValue.typeDeclareList.next){
    	alias_type = new_alias_type();
    	alias_type->spec_type.alias_type.a_type = type_check_type(i->nodeValue.typeDeclareList.typeDeclare->nodeValue.typeDeclare.type, scope);
    	alias_type->spec_type.alias_type.id = i->nodeValue.typeDeclareList.typeDeclare->nodeValue.typeDeclare.identifier->nodeValue.identifier;
    	sym_tbl_add_entry(new_tbl_entry(alias_type->spec_type.alias_type.id, i->nodeValue.typeDeclareList.typeDeclare->lineNumber, i->nodeValue.typeDeclareList.typeDeclare, alias_type), scope);
    }
    return 0;
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
		case BASIC_TYPE: return type_basic_type(node);
		//    returnNode->nodeValue.sliceType.type = _type;
		case SLICE_TYPE: ret = new_slice_type();
						 ret->spec_type.slice_type.s_type = type_check_type(node->nodeValue.sliceType.type, scope);
						 return ret;
		case ARRAY_TYPE: ret = new_array_type();
						 ret->spec_type.array_type.a_type = type_check_type(node->nodeValue.arrayType.type, scope);
						 return ret;
		case IDENTIFIER: //This is a aliased type
		//    returnNode->nodeValue.identifier = (char*)mallocList(sizeof(char)*(strlen(_identifier)+1), _allocator);
						{
						 tbl_entry * entry = sym_tbl_find_entry(node->nodeValue.identifier, scope);
						 if(ret == NULL){
						 	sprintf(err_buf, "Invalid type alias %s at line %d", node->nodeValue.identifier, node->lineNumber);
				      		add_msg_line(err_buf, current, node->lineNumber);
						 	return new_invalid_type(); //Invalid Type
						 }
						 return entry->type_info;
						}
		case STRUCT_TYPE:{
						//    returnNode->nodeValue.structType.structDec = _declareList;
							ret = new_struct_type();
							nodeAST * cur = node->nodeValue.structType.structDec;
							nodeAST * id_list_node;
						/*
    					returnNode->nodeType = STRUCT_TYPE_DEC_LIST;
   		 				returnNode->nodeValue.structTypeDecList.declare = _declare;
    					returnNode->nodeValue.structTypeDecList.next = _next;

    					returnNode->nodeType = STRUCT_TYPE_DEC;
    					returnNode->nodeValue.structTypeDec.identifierList = _identifierList;
    					returnNode->nodeValue.structTypeDec.type = _type;
						*/
							for(nodeAST * i = cur; i != NULL; i = i->nodeValue.structTypeDecList.next){
								id_list_node = i->nodeValue.structTypeDecList.declare;
								type * id_list_type = type_check_type(i->nodeValue.structTypeDec.type, scope);
								for(nodeAST * j = id_list_node->nodeValue.structTypeDec.identifierList; j != NULL; j = j->nodeValue.identifierList.next){
									char * id = j->nodeValue.identifierList.identifier->nodeValue.identifier;
									for(int k = 0; k < ret->spec_type.struct_type.list_size; k++){
										if(strcmp(ret->spec_type.struct_type.id_list[k], id) != 0){
											sprintf(err_buf, "Redeclaration of id %s when declaring struct fields at line %d.", node->nodeValue.function.identifier->nodeValue.identifier, node->lineNumber);
											add_msg_line(err_buf, current, node->lineNumber);
											return new_invalid_type();
										}
									}

									if(ret->spec_type.struct_type.list_size == ret->spec_type.struct_type.list_cap){
										ret->spec_type.struct_type.type_list = ralloc(ret->spec_type.struct_type.type_list, sizeof(type *) * ret->spec_type.struct_type.list_size * 2);
										ret->spec_type.struct_type.list_cap *= 2;
									}
									ret->spec_type.struct_type.type_list[ret->spec_type.struct_type.list_size] = id_list_type;
									ret->spec_type.struct_type.id_list[ret->spec_type.struct_type.list_size++] = id;
								}
							}

							return ret;
						}
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
    type * expr_list_type = new_list_type();
    for(nodeAST * i = node; i != NULL; i = i->nodeValue.exprList.next){
    	type * to_be_added = type_check_expr(i->nodeValue.exprList.expr, scope);

    	if(to_be_added != NULL){
			if(expr_list_type->spec_type.list_type.list_size == expr_list_type->spec_type.struct_type.list_cap){
				expr_list_type->spec_type.list_type.type_list = ralloc(expr_list_type->spec_type.struct_type.type_list, sizeof(type *) * expr_list_type->spec_type.struct_type.list_size * 2);
				expr_list_type->spec_type.list_type.list_cap *= 2;
				}
				expr_list_type->spec_type.list_type.type_list[expr_list_type->spec_type.list_type.list_size++] = to_be_added;
    	}
    	to_be_added = NULL;
    }

    return expr_list_type;
}


type * type_check_expr(nodeAST * node, sym_tbl * scope){
	    	switch(node->nodeType){
    		case IDENTIFIER:
    						{
    						//We need to find it first in the hash_table
    							tbl_entry * entry = sym_tbl_find_entry( node->nodeValue.identifier,scope);
    							if(entry == NULL){
									sprintf(err_buf, "Undeclared id %s at line %d", node->nodeValue.identifier, node->lineNumber);
									add_msg_line(err_buf, current, node->lineNumber);
    								return new_invalid_type();
    							}
    							return entry->type_info;
    						}
    		case LITERAL_INT: return new_int_type();
    						/*
   	 						returnNode->nodeType = LITERAL_INT;
    						returnNode->nodeValue.intValue = _intValue;
							*/
			case LITERAL_FLOAT: return new_float_type();
			case LITERAL_RUNE: return new_rune_type();
			case LITERAL_STRING: return new_string_type();
			case EXPR_FUNC_CALL: {
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
									sprintf(err_buf, "Undeclared function %s at line %d", node->nodeValue.funcCall.target->nodeValue.identifier, node->lineNumber);
									add_msg_line(err_buf, current, node->lineNumber);
    								return new_invalid_type();
    							}
    							else{
    								//Check the params type to see if it matches
    								if(node->nodeValue.funcCall.expr != NULL){
    									type * input = type_check_expr_list(node->nodeValue.funcCall.expr, scope);
    									if(entry->type_info->spec_type.list_type.list_size != input->spec_type.list_type.list_size){
											sprintf(err_buf, "Argument Number %d does not match function requirements %d at line %d", input->spec_type.list_type.list_size, entry->type_info->spec_type.list_type.list_size,  node->lineNumber);
											add_msg_line(err_buf, current, node->lineNumber);
    										return new_invalid_type();
    									}
    									for(int i = 0; i < input->spec_type.list_type.list_size; i++){
    										if(compare_type(input->spec_type.list_type.type_list[i], entry->type_info->spec_type.list_type.type_list[i]) == -1){
												sprintf(err_buf, "Argument type does not match function argument type at line %d",  node->lineNumber);
												add_msg_line(err_buf, current, node->lineNumber);
    											return new_invalid_type();
    										}
    									}
    								}
    								return entry->type_info->spec_type.func_type.return_type;
    								//The type of a function call is its return type
    							}
                    		}
            case EXPR_CAST:
            				//Not implemented yet
            				break;
            case EXPR_INDEX:
            				{
            				/*
    						returnNode->nodeType = EXPR_INDEX;
    						returnNode->nodeValue.index.target = _target;
    						returnNode->nodeValue.index.entry = _entry;
            				*/
            				//This would type check only when the primary_expr [ expr ]
            				// where primary_expr needs to be array or slice type and
            					type * target = type_check_expr(node->nodeValue.index.target, scope);
            					if(target->type != ARRAY_TYPE && target->type != SLICE_TYPE){
            						sprintf(err_buf, "Primary Expression is not a Array or Slice type %d",  node->lineNumber);
									add_msg_line(err_buf, current, node->lineNumber);
    								return new_invalid_type();
            					}
            					type * entry = type_check_expr(node->nodeValue.index.entry, scope);
            					if(entry->type != BASIC_TYPE || entry->type != LITERAL_INT){
            					    sprintf(err_buf, "Expression inside brackets must be of INT type at line %d",  node->lineNumber);
									add_msg_line(err_buf, current, node->lineNumber);
    								return new_invalid_type();
            					}
            					//So everything is valid so this returns the type of the slice/array
            					if(target->type == ARRAY_TYPE)
            						return target->spec_type.array_type.a_type;
            					return target->spec_type.slice_type.s_type;
            				}
            case EXPR_SELECTOR:
            				{
            				/*
            					primary_expr '.' id_
    							returnNode->nodeType = EXPR_SELECTOR;
    							returnNode->nodeValue.selector.target = _target;
   	 							returnNode->nodeValue.selector.entry = _entry;
							*/
   	 							type * current_struct = type_check_expr(node->nodeValue.selector.target, scope);
   	 							char * id = node->nodeValue.selector.entry->nodeValue.identifier;
   	 							if(current_struct->type != STRUCT_TYPE){
            					    sprintf(err_buf, "Expecting a struct type at line %d",  node->lineNumber);
									add_msg_line(err_buf, current, node->lineNumber);
    								return new_invalid_type();
   	 							}
   	 							//Next we need to scan all the members of the struct id_list to get that specific id type if found
   	 							for(int i = 0; i < current_struct->spec_type.struct_type.list_size; i++){
   	 								if(strcmp(id, current_struct->spec_type.struct_type.id_list[i]) == 0){//Found the id
   	 									return current_struct->spec_type.struct_type.type_list[i];
   	 								}
   	 							}
            					sprintf(err_buf, "ID %s not found in the struct at line %d", id,  node->lineNumber);
								add_msg_line(err_buf, current, node->lineNumber);
    							return new_invalid_type();
   	 						}
   	 		case EXPR_SLICE:
   	 						{
   	 						/*
    							returnNode->nodeType = EXPR_SLICE;
    							returnNode->nodeValue.slice.target = _target;
    							returnNode->nodeValue.slice.entry = _entry;
   	 						*/
    						//Okay so primary_expr slice, primary_expr must be of type slice
    							type * current_slice = type_check_expr(node->nodeValue.slice.target, scope);
    							if(current_slice->type != SLICE_TYPE){
            					    sprintf(err_buf, "Slice type expected at line %d",  node->lineNumber);
									add_msg_line(err_buf, current, node->lineNumber);
    								return new_invalid_type();
    							}
    							type_check_slice_expr(node->nodeValue.slice.entry, scope); //IF invalid type_checking, err_msg will be added inside
    							//This returns the type of the slice
    							return current_slice;

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
    		case EXPR_BINARY_OP_MUL:{
    						type * left = type_check_expr(node->nodeValue.mul.left, scope);
    						type * right = type_check_expr(node->nodeValue.mul.left, scope);
    						if( (left->type == LITERAL_INT || left->type == LITERAL_FLOAT) && ((right->type == LITERAL_INT || right->type == LITERAL_FLOAT)) ){
    							if(left->type == LITERAL_FLOAT)
    								return left;
    							else if(right->type == LITERAL_FLOAT)
    								return right;
    							return left;
    						}
    						else{
            					sprintf(err_buf, "Type of left and right either do not match or is invalid at line %d",  node->lineNumber);
								add_msg_line(err_buf, current, node->lineNumber);
    							return new_invalid_type();
    						}
    						/*
    						returnNode->nodeType = EXPR_BINARY_OP_MUL;
    						returnNode->nodeValue.mul.left = _left;
    						returnNode->nodeValue.mul.right = _right;
    						*/
    						}
    		case EXPR_BINARY_OP_DIV:{
    						type * left = type_check_expr(node->nodeValue.div.left, scope);
    						type * right = type_check_expr(node->nodeValue.div.left, scope);
    						if( (left->type == LITERAL_INT || left->type == LITERAL_FLOAT) && ((right->type == LITERAL_INT || right->type == LITERAL_FLOAT)) ){
    							if(left->type == LITERAL_FLOAT)
    								return left;
    							else if(right->type == LITERAL_FLOAT)
    								return right;
    							return left;
    						}
    						else{
            					sprintf(err_buf, "Type of left and right either do not match or is invalid at line %d",  node->lineNumber);
								add_msg_line(err_buf, current, node->lineNumber);
    							return new_invalid_type();
    						}
    						/*
    						returnNode->nodeType = EXPR_BINARY_OP_MUL;
    						returnNode->nodeValue.div.left = _left;
    						returnNode->nodeValue.div.right = _right;
    						*/
    						}
    		case EXPR_BINARY_OP_MOD: {
    						type * left = type_check_expr(node->nodeValue.mod.left, scope);
    						type * right = type_check_expr(node->nodeValue.mod.left, scope);
    						if( (left->type == LITERAL_INT || left->type == LITERAL_FLOAT) && ((right->type == LITERAL_INT || right->type == LITERAL_FLOAT)) ){
    							if(left->type == LITERAL_FLOAT)
    								return left;
    							else if(right->type == LITERAL_FLOAT)
    								return right;
    							return left;
    						}
    						else{
            					sprintf(err_buf, "Type of left and right either do not match or is invalid at line %d",  node->lineNumber);
								add_msg_line(err_buf, current, node->lineNumber);
    							return new_invalid_type();
    						}

    						/*
    						returnNode->nodeType = EXPR_BINARY_OP_MOD;
    						returnNode->nodeValue.mod.left = _left;
    						returnNode->nodeValue.mod.right = _right;
    						*/
    						}
    		case EXPR_BINARY_OP_SUB: {
    						type * left = type_check_expr(node->nodeValue.sub.left, scope);
    						type * right = type_check_expr(node->nodeValue.sub.left, scope);
    						if( (left->type == LITERAL_INT || left->type == LITERAL_FLOAT) && ((right->type == LITERAL_INT || right->type == LITERAL_FLOAT)) ){
    							if(left->type == LITERAL_FLOAT)
    								return left;
    							else if(right->type == LITERAL_FLOAT)
    								return right;
    							return left;
    						}
    						else{
            					sprintf(err_buf, "Type of left and right either do not match or is invalid at line %d",  node->lineNumber);
								add_msg_line(err_buf, current, node->lineNumber);
    							return new_invalid_type();
    						}

    						/*
    						returnNode->nodeType = EXPR_BINARY_OP_SUB;
    						returnNode->nodeValue.sub.left = _left;
    						returnNode->nodeValue.sub.right = _right;
    						*/
    						}
    		case EXPR_BINARY_OP_ADD: {
    						type * left = type_check_expr(node->nodeValue.add.left, scope);
    						type * right = type_check_expr(node->nodeValue.add.left, scope);
    						if( (left->type == LITERAL_INT || left->type == LITERAL_FLOAT) && ((right->type == LITERAL_INT || right->type == LITERAL_FLOAT)) ){
    							if(left->type == LITERAL_FLOAT)
    								return left;
    							else if(right->type == LITERAL_FLOAT)
    								return right;
    							return left;
    						}else if( left->type == LITERAL_STRING && right->type == LITERAL_STRING){
    							return left;
    						}
    						else{
            					sprintf(err_buf, "Type of left and right either do not match or is invalid at line %d",  node->lineNumber);
								add_msg_line(err_buf, current, node->lineNumber);
    							return new_invalid_type();
    						}

    						/*
    						returnNode->nodeType = EXPR_BINARY_OP_ADD;
    						returnNode->nodeValue.add.left = _left;
    						returnNode->nodeValue.add.right = _right;
    						*/
    						}
    		case EXPR_BINARY_OP_LOGIC_AND: {
    						type * left = type_check_expr(node->nodeValue.logicAnd.left, scope);
    						type * right = type_check_expr(node->nodeValue.logicAnd.left, scope);
    						if( (left->type == LITERAL_BOOL || right->type == LITERAL_BOOL) ){
    							return left;
    						}
    						else{
            					sprintf(err_buf, "Type of left and right either do not match or is not boolean at line %d",  node->lineNumber);
								add_msg_line(err_buf, current, node->lineNumber);
    							return new_invalid_type();
    						}

    						/*
   		 					returnNode->nodeType = EXPR_BINARY_OP_LOGIC_AND;
    						returnNode->nodeValue.logicAnd.left = _left;
    						returnNode->nodeValue.logicAnd.right = _right;
    						*/
    						}
    		case EXPR_BINARY_OP_LOGIC_OR: {
    						type * left = type_check_expr(node->nodeValue.logicOr.left, scope);
    						type * right = type_check_expr(node->nodeValue.logicOr.left, scope);
    						if( (left->type == LITERAL_BOOL || right->type == LITERAL_BOOL) ){
    							return left;
    						}
    						else{
            					sprintf(err_buf, "Type of left and right either do not match or is not boolean at line %d",  node->lineNumber);
								add_msg_line(err_buf, current, node->lineNumber);
    							return new_invalid_type();
    						}

    						/*
    						returnNode->nodeType = EXPR_BINARY_OP_LOGIC_OR;
    						returnNode->nodeValue.logicOr.left = _left;
    						returnNode->nodeValue.logicOr.right = _right;
    						*/
    						}
    		case EXPR_BINARY_OP_XOR: {
    						type * left = type_check_expr(node->nodeValue.bitXor.left, scope);
    						type * right = type_check_expr(node->nodeValue.bitXor.left, scope);
    						if( (left->type == LITERAL_INT || right->type == LITERAL_INT) ){
    							return left;
    						}
    						else{
            					sprintf(err_buf, "Type of left and right either do not match or is not boolean at line %d",  node->lineNumber);
								add_msg_line(err_buf, current, node->lineNumber);
    							return new_invalid_type();
    						}

    						/*
    						returnNode->nodeType = EXPR_BINARY_OP_XOR;
    						returnNode->nodeValue.bitXor.left = _left;
    						returnNode->nodeValue.bitXor.right = _right;
    						*/
    						}
    		case EXPR_BINARY_OP_OR: {
    						type * left = type_check_expr(node->nodeValue.bitOr.left, scope);
    						type * right = type_check_expr(node->nodeValue.bitOr.left, scope);
    						if( (left->type == LITERAL_INT || right->type == LITERAL_INT) ){
    							return left;
    						}
    						else{
            					sprintf(err_buf, "Type of left and right either do not match or is not boolean at line %d",  node->lineNumber);
								add_msg_line(err_buf, current, node->lineNumber);
    							return new_invalid_type();
    						}

    						/*
    						returnNode->nodeType = EXPR_BINARY_OP_OR;
    						returnNode->nodeValue.bitOr.left = _left;
    						returnNode->nodeValue.bitOr.right = _right;
    						*/
    						}
    		case EXPR_BINARY_OP_LSHIFT: {
    						type * left = type_check_expr(node->nodeValue.shiftLeft.left, scope);
    						type * right = type_check_expr(node->nodeValue.shiftLeft.left, scope);
    						if( (left->type == LITERAL_INT || right->type == LITERAL_INT) ){
    							return left;
    						}
    						else{
            					sprintf(err_buf, "Type of left and right either do not match or is not boolean at line %d",  node->lineNumber);
								add_msg_line(err_buf, current, node->lineNumber);
    							return new_invalid_type();
    						}

    						/*
    						returnNode->nodeType = EXPR_BINARY_OP_LSHIFT;
    						returnNode->nodeValue.shiftLeft.left = _left;
    						returnNode->nodeValue.shiftLeft.right = _right;
    						*/
    						}
    		case EXPR_BINARY_OP_RSHIFT: {
    						type * left = type_check_expr(node->nodeValue.shiftRight.left, scope);
    						type * right = type_check_expr(node->nodeValue.shiftRight.left, scope);
    						if( (left->type == LITERAL_INT || right->type == LITERAL_INT) ){
    							return left;
    						}
    						else{
            					sprintf(err_buf, "Type of left and right either do not match or is not boolean at line %d",  node->lineNumber);
								add_msg_line(err_buf, current, node->lineNumber);
    							return new_invalid_type();
    						}

    						/*
    						returnNode->nodeType = EXPR_BINARY_OP_RSHIFT;
    						returnNode->nodeValue.shiftRight.left = _left;
    						returnNode->nodeValue.shiftRight.right = _right;
    						*/
    						}
    		case EXPR_BINARY_OP_ANDNOT: {
    						type * left = type_check_expr(node->nodeValue.shiftRight.left, scope);
    						type * right = type_check_expr(node->nodeValue.shiftRight.left, scope);
    						if( (left->type == LITERAL_INT || right->type == LITERAL_INT) ){
    							return left;
    						}
    						else{
            					sprintf(err_buf, "Type of left and right either do not match or is not boolean at line %d",  node->lineNumber);
								add_msg_line(err_buf, current, node->lineNumber);
    							return new_invalid_type();
    						}

    						/*
    						returnNode->nodeType = EXPR_BINARY_OP_ANDNOT;
    						returnNode->nodeValue.bitAndNot.left = _left;
    						returnNode->nodeValue.bitAndNot.right = _right;
    						*/
    						}
    		case EXPR_UNIARY_OP_POS: {
    						//Characters are not allowed as part of unary expression
    						type * left = type_check_expr(node->nodeValue.pos.expr, scope);
    						if( (left->type == LITERAL_INT || left->type == LITERAL_FLOAT) ){
    							return left;
    						}
    						else{
            					sprintf(err_buf, "Invalid Unary Operator + at line %d",  node->lineNumber);
								add_msg_line(err_buf, current, node->lineNumber);
    							return new_invalid_type();
    						}

    						/*
    						nodeAST* returnNode = allocateNode(_allocator);
    						returnNode->nodeType = EXPR_UNIARY_OP_POS;
    						returnNode->nodeValue.pos.expr = _expr;
    						*/
    						}
    		case EXPR_UNIARY_OP_NEG: {
    						//Characters are not allowed as part of unary expression
    						type * left = type_check_expr(node->nodeValue.neg.expr, scope);
    						if( (left->type == LITERAL_INT || left->type == LITERAL_FLOAT) ){
    							return left;
    						}
    						else{
            					sprintf(err_buf, "Invalid Unary Operator - at line %d",  node->lineNumber);
								add_msg_line(err_buf, current, node->lineNumber);
    							return new_invalid_type();
    						}

    						/*
    						nodeAST* returnNode = allocateNode(_allocator);
    						returnNode->nodeType = EXPR_UNIARY_OP_NEG;
    						returnNode->nodeValue.neg.expr = _expr;
    						*/
    						}
    		case EXPR_UNIARY_OP_NOT: {
    						//Characters are not allowed as part of unary expression
    						type * left = type_check_expr(node->nodeValue.bitNot.expr, scope);
    						if( (left->type == LITERAL_INT || left->type == LITERAL_FLOAT) ){
    							return left;
    						}
    						else{
            					sprintf(err_buf, "Invalid Unary Operator ^ at line %d",  node->lineNumber);
								add_msg_line(err_buf, current, node->lineNumber);
    							return new_invalid_type();
    						}

    						/*
    						nodeAST* returnNode = allocateNode(_allocator);
    						returnNode->nodeType = EXPR_UNIARY_OP_NOT;
    						returnNode->nodeValue.bitNot.expr = _expr;
    						*/
    						}
    		case EXPR_UNIARY_OP_LOGIC_NOT: {
    						//Characters are not allowed as part of unary expression
    						type * left = type_check_expr(node->nodeValue.logicNot.expr, scope);
    						if( (left->type == LITERAL_INT || left->type == LITERAL_FLOAT) ){
    							return left;
    						}
    						else{
            					sprintf(err_buf, "Invalid Unary Operator ^ at line %d",  node->lineNumber);
								add_msg_line(err_buf, current, node->lineNumber);
    							return new_invalid_type();
    						}

    						/*
    						returnNode->nodeType = EXPR_UNIARY_OP_LOGIC_NOT;
    						returnNode->nodeValue.logicNot.expr = _expr;
    						*/
    						}

    	}
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
    				if( node->nodeType == EXPR_ADDRESS_SLICE ){
    					if(node->nodeValue.addressSlice.start != NULL){
    						if(type_check_expr(node->nodeValue.addressSlice.start, scope)->type != LITERAL_INT){
            					sprintf(err_buf, "Expecting a int type for slice indexing at line %d", node->lineNumber);
								add_msg_line(err_buf, current, node->lineNumber);
    							return -1;
    						}
    					}
    					if(node->nodeValue.addressSlice.end != NULL){
    						if(type_check_expr(node->nodeValue.addressSlice.end, scope)->type != LITERAL_INT){
            					sprintf(err_buf, "Expecting a int type for slice indexing at line %d", node->lineNumber);
								add_msg_line(err_buf, current, node->lineNumber);
    							return -1;
    						}
    					}
    					return 0;
    				}else{
    					if(node->nodeValue.addressSliceFull.start != NULL){
    						if(type_check_expr(node->nodeValue.addressSliceFull.start, scope)->type != LITERAL_INT){
            					sprintf(err_buf, "Expecting a int type for slice indexing at line %d", node->lineNumber);
								add_msg_line(err_buf, current, node->lineNumber);
    							return -1;
    						}
    					}
    					if(node->nodeValue.addressSliceFull.end != NULL){
    						if(type_check_expr(node->nodeValue.addressSliceFull.end, scope)->type != LITERAL_INT){
            					sprintf(err_buf, "Expecting a int type for slice indexing at line %d", node->lineNumber);
								add_msg_line(err_buf, current, node->lineNumber);
    							return -1;
    						}
    					}
    					if(node->nodeValue.addressSliceFull.max != NULL){
    						if(type_check_expr(node->nodeValue.addressSliceFull.max, scope)->type != LITERAL_INT){
            					sprintf(err_buf, "Expecting a int type for slice indexing at line %d", node->lineNumber);
								add_msg_line(err_buf, current, node->lineNumber);
    							return -1;
    						}
    					}
    					return 0;
    				}
}


msg_list * prepare_id_list(nodeAST * node){
	msg_list * h = alloc(1, sizeof(msg_list));
	msg_list * c = h;
	// returnNode->nodeValue.identifierList.identifier = _identifier;
    // returnNode->nodeValue.identifierList.next = _next;
    h->msg = alloc(MAX_ID_LENGTH, sizeof(char)); //MAX_ID of 256
    strcpy(h->msg, node->nodeValue.identifierList.identifier->nodeValue.identifier);
    for(nodeAST * i = node->nodeValue.identifierList.next; i != NULL; i = i->nodeValue.identifierList.next){
    	add_msg_line(i->nodeValue.identifierList.identifier->nodeValue.identifier, c, i->nodeValue.identifierList.identifier->lineNumber);
    }
    return h;
}
#endif