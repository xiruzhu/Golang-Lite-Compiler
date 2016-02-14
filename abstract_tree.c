#include "abstract_tree.h"

/*

*/
vector * create_vector(){
	vector * ret = (vector *)calloc(1, sizeof(vector *));
	if(ret == NULL)
			exit(1);
	ret->valAt = (node **)calloc(4, sizeof(node *));
	if(ret->valAt == NULL)
			exit(1);
	ret->size = 0;
	ret->capacity = 4;
	return ret;
}

//Returns -1 for failure
int add_element(vector * list, node * element){
	if(list == NULL || element == NULL)
		return -1;
	if(list->size == list->capacity){
		list->valAt = (node **)realloc(list->valAt, list->size * 2 * sizeof(node *));
		if(list->valAt == NULL)
			exit(1);
	}
	list->valAt[list->size++] = element;
	return 0;
}

int remove_element(vector * list, node * element){
	for(int i = 0; i < list->size; i++){
		if(element == list->valAt[i]){
			for(int j = i; j < list->size - 1; j++){
				list->valAt[j] = list->valAt[j + 1];
			}
			list->valAt[list->size - 1] == NULL;
			list->size--;
		}
	}
	return 0;
}

int free_vector(vector * list){
	for(int i = 0; i < list->size; i++)
		free_node(list->valAt[i]);
	free(list);
}

//Creates a general intermediate node
node * create_node( int type, int exact_type, int line_num, int char_num){
		node * ret = (node *)calloc(1, sizeof(node));
		if(ret == NULL)
			exit(1);
		ret->child_list = create_vector();
		ret->type = type;
		ret->parent = NULL;
		ret->exact_type = exact_type;
		ret->line_num = line_num;
		ret->char_num = char_num;
		return ret;
}

//Creates a node for int
node * create_node_int(node * parent, int type, int val, int line_num, int char_num){
	//Given a type and a union value
	node * ret = (node *)calloc(1, sizeof(node));
	if(ret == NULL)
		exit(1);
	ret->child_list = create_vector();
	ret->type = type;
	ret->val.int_val = val;
	ret->parent = NULL;
	ret->exact_type = -1;
	ret->line_num = line_num;
	ret->char_num = char_num;
	add_node(parent, ret);
	return ret;
}

node * create_node_float(node * parent, int type, float val, int line_num, int char_num){
	//Given a type and a union value
	node * ret = (node *)calloc(1, sizeof(node));
	if(ret == NULL)
		exit(1);
	ret->child_list = create_vector();
	ret->type = type;
	ret->val.float_val = val;
	ret->parent = NULL;
	ret->exact_type = -1;
	ret->line_num = line_num;
	ret->char_num = char_num;
	add_node(parent, ret);
	return ret;
}

node * create_node_str(node * parent, int type, char * val, int line_num, int char_num){
	//Given a type and a union value
	node * ret = (node *)calloc(1, sizeof(node));
	if(ret == NULL)
		exit(1);
	ret->child_list = create_vector();
	ret->type = type;
	ret->val.str_val = val;
	ret->parent = NULL;
	ret->exact_type = -1;
	ret->line_num = line_num;
	ret->char_num = char_num;
	add_node(parent, ret);
	return ret;
}

void set_exact_type(node * ret, int exact_type){
	ret->exact_type = exact_type;
}

// Add a child node to parent node
int add_node(node * parent, node * child){
	if(parent == NULL || child == NULL){
		return -1;
	}
	//We can't add a node if either child or parent is null
	child->parent = parent;
	if(add_element(parent->child_list, child) == 0)
		return -1;

	return 0;
}

//Free festival
int free_node(node * tree){
	node * parent = tree->parent;
	free_vector(tree->child_list);
	//So this can cause some pretty nasty problem because if we free a branch but not the whole tree we'd have a dangling pointer
	remove_element(parent->child_list, tree);
	free(tree);
	return 0;
}

/*
//Given a node pointer, we delete it from tree. We are assuming each tree has a unique node and not reused ones which may improve efficiency
//but make my life harder
//Returns 0 on success
//Returns 1 on failure
int delete_node(node * tree, node * deleted){
	int ret;
	if(tree == deleted){
		free_node(tree);
		return 0;
	}

	for(int i = 0; i < tree->num_child_nodes; i++){
		if((ret = delete_node(tree->childs[i], deleted)) == 0) //is zero
			return 0;
	}
	return 1;
}

//The purpose of this function is the transfer all children of old parent to new parent
int adopt_children(node * new_parent, node * old_parent){
	if(new_parent == NULL || old_parent == NULL)
		return 1; //Failure if either parent is equal to NULL
	for(int i = 0; i < old_parent->num_child_nodes; i++){
		add_node(new_parent, old_parent->childs[i]);
	}
	//now we free the old parent since it's pretty useless
	free_node(old_parent);
	return 0;
}

int main(){
	printf("Test\n");
	union value test;
	test.int_val = 5;
	node * root = create_node(int_val, test);
	free(root);
}
*/


int pretty_print(node * current){
	switch(current->type){
		case go_prog: //pckg_decl ';' top_decl_list;
									if(pretty_print(current->child_list->valAt[0]) == -1)
											return -1;
									if(pretty_print(current->child_list->valAt[1]) == -1)
											return -1;
		case list: return print_list(current);
		case block: return print_block(current);
		case pckg_decl: //: package_ id_
										printf("package ");
										if(print_primitive(current->child_list->valAt[0]) == -1)
												return -1;
										printf(";\n");
										return 0;
		case top_decl: return print_top_decl(current);
		case func_decl: return print_func_decl(current);
		case var_decl: return print_var_decl(current);
		case var_spec: return print_var_spec(current);
		case type_decl: return print_type_decl(current);
		case field_decl: return print_field_decl(current);
		case type_spec: return print_type_spec(current);
		case stmt: return print_a_stmt(current);
		case simple_stmt: return print_simple_stmt(current);
		case assign_stmt: return print_assign_stmt(current);
		case short_decl: return print_short_decl(current);
		case if_stmt: return print_if_stmt(current);
		case for_stmt: return print_for_stmt(current);
		case for_stmt_clause: return print_for_stmt_clause(current);
		case switch_stmt: return print_switch(current);
		case case_clause: return print_case_clause(current);
		case switch_case: return print_switch_case(current);
		case switch_cond: return print_switch_cond(current);
		case expr: return print_expr(current);
		case primary_expr: return print_primary_expr(current);
		case operand: return print_operand(current);
		case func_call: return print_func_call(current);
		case type_cast: return print_type_cast(current);
		case slice: return print_slice(current);
		case primitive: return print_primitive(current);
		case operator: return print_operator(current);
		case type_id: return print_type_id(current);
	  case params_decl: return print_params_decl(current);
		case params: return print_params(current);
		case type: return print_type(current);
		default: return -1;
	}
}
// top_decl            : decl | func_decl;
int print_top_decl(node * current){
	if(current->exact_type == decl)
		return print_decl(current->child_list->valAt[0]);
	else
		return print_func_decl(current->child_list->valAt[0]);
}

int print_decl(node * current){
	if(current->exact_type == var_decl)
		return print_var_decl(current->child_list->valAt[0]);
	else
		return print_type_decl(current->child_list->valAt[0]);
}

int print_var_decl(node * current){
		printf("var ");
		if(current->child_list->valAt[0]->type == var_spec){
			if(print_var_spec(current->child_list->valAt[0]) == -1)
				return -1;
		}
		else{
			printf("(");
			if(print_list(current->child_list->valAt[0]) == -1)
				return -1;
			printf(")");
		}
		printf(";\n");
		return 0;
}

int print_func_decl(node * current){
	printf("func ");
	print_primitive(current->child_list->valAt[0]); //id
	if(current->child_list->valAt[1]->type == signature)
		return print_signature(current->child_list->valAt[1]);
	else
	 return print_function(current->child_list->valAt[1]);
}

int print_signature(node * current){
	if(print_params(current->child_list->valAt[0]) == -1)
		return -1;
	if(current->child_list->size == 2)
		return print_type(current->child_list->valAt[1]);
	return 0;
}

int print_params(node * current){
		printf("( ");
		if(current->child_list->size == 1)
			if(print_list(current->child_list->valAt[0]) == -1)
				return -1;
		printf(")");
		return 0;
}

int print_params_decl(node * current){
	if(print_list(current->child_list->valAt[0]) == -1)
		return -1;
	if(print_type(current->child_list->valAt[1]) == -1)
		return -1;
	return 0;
}

int print_function(node * current){
	if(print_signature(current->child_list->valAt[0]) == -1)
		return -1;
	return print_block(current->child_list->valAt[1]);
}

/*
stmt                : decl
                    | block
                    | print_stmt
                    | println_stmt
                    | return_stmt
                    | if_stmt
                    | simple_stmt
                    | switch_stmt
                    | for_stmt
                    | break_stmt
                    | cont_stmt
*/
int print_a_stmt(node * current){
	switch(current->exact_type){
		case decl: return print_decl(current);
		case block: return print_block(current);
		case print_stmt: /*
		print_stmt      : print_ '(' expr_list ')' ';'
                    | print_ '(' ')' ';'
										 */
										 printf("print(");
										 if(print_list(current->child_list->valAt[0]) == -1)
										 		return -1;
										 printf(");\n");
										 return 0;
		case println_stmt:
										printf("println(");
										if(current->child_list->size == 1)
											if(print_list(current->child_list->valAt[0]) == -1)
			 									return -1;
										printf(");\n");
										return 0;
		case return_stmt:
										printf("return ");
										if(current->child_list->size == 1)
											if(print_expr(current->child_list->valAt[0]) == -1)
												return -1;
										printf(";\n");
										return 0;
		case if_stmt: return print_if_stmt(current);
		case simple_stmt: return print_simple_stmt(current->child_list->valAt[0]);
		case switch_stmt: return print_switch_stmt(current);
		case for_stmt: return print_for_stmt(current);
		case break_stmt: printf("break;\n");
										 return 0;
		case cont_stmt:  printf("continue;\n");
										 return 0;
		default: return -1;
	}
}
int print_switch_stmt(node * current){
	printf("switch");
	if(print_switch_cond(current->child_list->valAt[0]) == -1)
		return -1;
	printf("{\n");
	if(print_list(current->child_list->valAt[0]) == -1)
		return -1;
	printf("}\n");
	return 0;
}

int print_switch_cond(node * current){
	switch(current->exact_type){
		case switch_cond_1:
												if(print_simple_stmt(current->child_list->valAt[0]) == -1)
													return -1;
												printf(";");
												if(print_expr(current->child_list->valAt[1]) == -1)
													return -1;
											  return 0;
    case switch_cond_2:
												if(print_simple_stmt(current->child_list->valAt[0]) == -1)
												  return -1;
												printf(";");
												return 0;
		case switch_cond_3:
		 										return print_expr(current->child_list->valAt[0]);
		case switch_cond_4: printf(" ");
												return 0;
		default:						return -1;
	}
}

int print_case_clause(node * current){
	if(print_switch_case(current->child_list->valAt[0]) == -1)
		return -1;
	printf(" : ");
	if(print_list(current->child_list->valAt[1]) == -1)
		return -1;
	printf("\n");
	return 0;
}

int print_switch_case(node * current){
	if(current->child_list->valAt[0]->child_list->size == 1){
		printf("case ");
		if(print_expr(current->child_list->valAt[0]) == -1)
			return -1;
	}
	else
		printf("default ");
	return 0;
}

/*
for_stmt            : for_ for_clause block

for_clause          : condition | for_stmt_clause

condition           :
                    | expr

for_stmt_clause     : simple_stmt_v ';' condition ';' simple_stmt_v
*/
print_for_stmt(node * current){
	printf("for");
	if(current->exact_type == condition){
		//
		printf(" ");
		if(current->child_list->valAt[0]->child_list->size == 1)//not empty
			if(print_expr(current->child_list->valAt[0]) == -1)
				return -1;
		printf(" ");
	}
	else{
		if(print_for_stmt_clause(current->child_list->valAt[0]) == -1)
			return -1;
	}
	return print_block(current->child_list->valAt[2]);
}

print_for_stmt_clause(node * current){
	if(print_simple_stmt(current->child_list->valAt[0]) == -1)
		return -1;
	printf(" ");
	if(current->child_list->valAt[1]->child_list->size == 1)//not empty
		if(print_expr(current->child_list->valAt[1]) == -1)
			return -1;
	printf(" ");
	if(print_simple_stmt(current->child_list->valAt[2]) == -1)
		return -1;
}

int print_if_stmt(node * current){
	if(current->child_list->size == 2) {//so a simple if statement without else
		printf("if ");
		if(print_if_cont(current->child_list->valAt[0]) == -1)
			return -1;
		if(print_block(current->child_list->valAt[1]) == -1)
			return -1;
	}
	else{
		printf("if ");
		if(print_if_cont(current->child_list->valAt[0]) == -1)
			return -1;
		if(print_block(current->child_list->valAt[1]) == -1)
			return -1;
		printf("else ");
		if(current->child_list->valAt[2]->type == block){
			if(print_block(current->child_list->valAt[2]) == -1)
				return -1;
			}
		else
			if(print_if_stmt(current->child_list->valAt[2]) == -1)
				return -1;
	}
	return 0;
}
/*
if_cond             : expr
                    | simple_stmt expr
*/
int print_if_cont(node * current){
	if(current->child_list->size == 1){
		return print_expr(current->child_list->valAt[0]);
	}
	if(print_simple_stmt(current->child_list->valAt[0]) == -1)
		return -1;
	return print_expr(current->child_list->valAt[1]);
}
/*
| expr_stmt
| inc_stmt
| dec_stmt
| assign_stmt
| short_decl
*/
int print_simple_stmt(node * current){
	switch(current->type){
		case expr_stmt: if(print_expr(current) == -1)
											return -1;
										printf(";\n");
										return 0;
		case inc_stmt: if(print_expr(current) == -1)
											return -1;
									 printf("++;\n");
									 return 0;
		case dec_stmt: if(print_expr(current) == -1)
						 	 				return -1;
						 	 		 printf("++;\n");
						 	 		 return 0;
		case assign_stmt:
									//expr_list assign_op expr_list
									if(print_list(current->child_list->valAt[0]) == -1)
										return -1;
									print_operator(current->child_list->valAt[1] == -1);
									if(print_list(current->child_list->valAt[0]) == -1)
										return -1;
								  printf(";\n");
									return 0;
		case short_decl:
									//short_decl          : expr_list decla_ expr_list
									if(print_list(current->child_list->valAt[0]) == -1)
										return -1;
									printf(":=");
									if(print_list(current->child_list->valAt[0]) == -1)
										return -1;
									printf(";\n");
									return 0;
		default: return -1;
	}
}

int print_block(node * current){
	printf("{\n");
	print_list(current->child_list->valAt[0]);
	printf("}\n");
	return 0;
}

int print_expr(node * current){
	switch(current->exact_type){
		case primary_expr: return print_primary_expr(current->child_list->valAt[0]);
		case operator: if(print_expr(current->child_list->valAt[0]) == -1)
											return -1;
									 print_operator(current->child_list->valAt[1]);
									 if(print_expr(current->child_list->valAt[2]) == -1)
								  		return -1;
									 return 0;
		case append: 	 printf("append ( %s, ", current->child_list->valAt[0]);
									 if(print_list(current->child_list->valAt[1]) == -1)
									 	  return -1;
									 printf(")");
									 return 0;
		case unary_op: print_operator(current->child_list->valAt[0]);
									 if(print_expr(current->child_list->valAt[1]) == -1)
			 					 			return -1;
									 return 0;
		default: 	return -1;
	}
}

int print_list(node * current){
	for(int i = 0; i < current->child_list->size; i++){
		if(pretty_print(current->child_list->valAt[i]) == -1)
			return -1;
	}
	return 0;
}

int print_primary_expr(node * current){
	switch(current->exact_type){
			case operand: return print_operand(current->child_list->valAt[0]);
			case func_call: return print_func_call(current->child_list->valAt[0]);
			case type_cast:	//basic_type '(' expr ')'
										 print_type_id(current->child_list->valAt[0]);
										 printf("(");
										 if(print_expr(current->child_list->valAt[1]) == -1)
							 					return -1;
										 printf(")");
										 return 0;
			case selector: if(print_primary_expr(current->child_list->valAt[0]) == -1)
												return -1;
										 printf(".");
										 return print_primitive(current->child_list->valAt[1]);
			case index:    if(print_primary_expr(current->child_list->valAt[0]) == -1)
												return -1;
										 printf("[");
										 if(print_expr(current->child_list->valAt[1]) == -1)
										 		return -1;
										 printf("]");
										 return 0;
			case slice:		 if(print_primary_expr(current->child_list->valAt[0]) == -1)
												return -1;
										 return print_slice(current->child_list->valAt[1]);
			default: return -1;
	}
}
int print_func_call(node * current){
		if(print_primary_expr(current->child_list->valAt[0]) == -1)
			return -1;
		if(current->child_list->size == 2){ //primary_expr '(' expr_list ')'
			printf("(");
			if(print_list(current->child_list->valAt[1]) == -1)
				return -1;
			printf(")");
		}
		else{ //primary_expr '(' ')'
			printf("(");
			printf(")");
		}
		return 0;
}
/*
operand             : '(' expr ')'
                    | operand_name -> it's and id_
                    | literal;
*/
int print_operand(node * current){
	switch(current->child_list->valAt[0]->type){
		case expr: return print_expr(current->child_list->valAt[0]);
		case primitive: return print_primitive(current->child_list->valAt[0]);
	}
}
/*
slice               : '[' expr ':' expr ']'
                    | '[' expr ':'  ']'
                    | '['  ':' expr ']'
                    | '['  ':'  ']'
                    | '[' expr ':' expr ':' expr ']'
                    | '['  ':' expr ':' expr ']'
*/
int print_slice(node * current){
	printf("[ ");
	switch(current->exact_type){
		case slice_1: //: '[' expr ':' expr ']'
						if(print_expr(current->child_list->valAt[1]) == -1)
							 return -1;
						printf(" : ");
						if(print_expr(current->child_list->valAt[1]) == -1)
							 return -1;
						break;
		case slice_2: //'[' expr ':'  ']'
						if(print_expr(current->child_list->valAt[1]) == -1)
			 				 return -1;
						printf(" : ");
						break;
		case slice_3: //'['  ':' expr ']'
		 				printf(" : ");
						if(print_expr(current->child_list->valAt[1]) == -1)
							 return -1;
						break;
		case slice_4: //'['  ':'  ']'
						printf(" : ");
						break;
		case slice_5: //'[' expr ':' expr ':' expr ']'
						if(print_expr(current->child_list->valAt[1]) == -1)
			 					return -1;
						printf(" : ");
					  if(print_expr(current->child_list->valAt[1]) == -1)
								return -1;
						printf(" : ");
						if(print_expr(current->child_list->valAt[1]) == -1)
							  return -1;
						break;
		case slice_6: //'['  ':' expr ':' expr ']'
						printf(" : ");
						if(print_expr(current->child_list->valAt[1]) == -1)
								return -1;
						printf(" : ");
						if(print_expr(current->child_list->valAt[1]) == -1)
								return -1;
						break;
	}
	printf(" ]");
	return 0;
}

int print_primitive(node * current){
		switch(current->exact_type){
			case bool_lit_: printf("%s", current->val.str_val); break;
			case int_lit_: printf("%d", current->val.int_val); break;
			case string_lit_: printf("%s", current->val.str_val); break;
			case float_lit_: printf("%f", current->val.float_val); break;
			case rune_lit_: printf("%s", current->val.str_val); break;
			case id_: printf("%s", current->val.str_val); break;
			default: return -1;
		}
		return 0;
}

int print_type_id(node * current){
		printf("%s", current->val.str_val);
		return 0;
}

int print_operator(node * current){
		printf("%s", current->val.str_val);
		return 0;
}


int main(){
	printf("Test\n");
}
