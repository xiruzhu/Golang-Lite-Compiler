#include "abstract_tree.h"

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
node * create_node( int exact_type, int line_num, int char_num){
		node * ret = (node *)calloc(1, sizeof(node));
		if(ret == NULL)
			exit(1);
		ret->child_list = create_vector();
		ret->exact_type = exact_type;
		ret->parent = NULL;
		ret->gen_type = -1;
		ret->line_num = line_num;
		ret->char_num = char_num;
		return ret;
}

//Creates a node for int
node * create_node_int(node * parent, int exact_type, int val, int line_num, int char_num){
	//Given a type and a union value
	node * ret = (node *)calloc(1, sizeof(node));
	if(ret == NULL)
		exit(1);
	ret->child_list = create_vector();
	ret->exact_type = exact_type;
	ret->val.int_val = val;
	ret->parent = NULL;
	ret->gen_type = -1;
	ret->line_num = line_num;
	ret->char_num = char_num;
	add_node(parent, ret);
	return ret;
}

node * create_node_float(node * parent, int exact_type, float val, int line_num, int char_num){
	//Given a type and a union value
	node * ret = (node *)calloc(1, sizeof(node));
	if(ret == NULL)
		exit(1);
	ret->child_list = create_vector();
	ret->exact_type = exact_type;
	ret->val.float_val = val;
	ret->parent = NULL;
	ret->gen_type = -1;
	ret->line_num = line_num;
	ret->char_num = char_num;
	add_node(parent, ret);
	return ret;
}

node * create_node_str(node * parent, int exact_type, char * val, int line_num, int char_num){
	//Given a type and a union value
	node * ret = (node *)calloc(1, sizeof(node));
	if(ret == NULL)
		exit(1);
	ret->child_list = create_vector();
	ret->exact_type = exact_type;
	ret->val.str_val = val;
	ret->parent = NULL;
	ret->gen_type = -1;
	ret->line_num = line_num;
	ret->char_num = char_num;
	add_node(parent, ret);
	return ret;
}

void set_gen_type(node * ret, int gen_type){
	ret->gen_type = gen_type;
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

int main(){
	printf("Test\n");
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
	switch(current->exact_type){
		case go_prog: return print_go_prog(current);
		case list: return print_list(current);
		case block: return print_block(current);
		case pckg: return print_pckg(current);
		case top_decl: return print_top_decl(current);
		case func_decl: return print_func_decl(current);
		case var_decl: return print_var_decl(current);
		case var_spec: return print_var_spec(current);
		case type_decl: return print_type_decl(current);
		case field_decl: return print_field_decl(current);
		case type_spec: return print_type_spec(current);
		case stmt: return print_stmt(current);
		case simple_stmt: return print_simple_stmt(current);
		case assign_stmt: return print_assign_stmt(current);
		case short_decl: return print_short_decl(current);
		case print_stmt: return print_stmt(current);
		case println_stmt: return println_stmt(current);
		case if_stmt: return print_if_stmt(current);
		case for_stmt: return print_for_stmt(current);
		case condition: return print_condition(current);
		case for_clause: return print_for_clause(current);
		case switch_stmt: return print_switch(current);
		case case_clause: return print_case_clause(current);
		case switch_cond: return print_switch_cond(current);
		case expr: return print_expr(current);
		case operand: return print_operand(current);
		case func_call: return print_func_call(current);
		case selector: return print_selector(current);
		case type_cast: return print_type_cast(current);
		case slice: return print_slice(current);
		default: return print_primitive(current);
	}
}
