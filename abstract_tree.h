#include <stdio.h> /* for printf */
#include <stdlib.h>
#include <string.h>

typedef enum {
 list,  //This is for all list of values, of course it keeps a value called sub_type to keep track of what kind of list it is
 // All Lists
 // top_decl_list
 // params_list
 // type_spec_list
 // var_spec_list
 // id_list
 // field_decl_list
 // stmt_list
 // case_clause_list
 // expr_list
 block, //This has a Symbol Table

//------------------------------------
//Base values
 type_id, //this prints out int, float, string... not ID though
 int_,
 float_,
 string_,
 rune_,
 bool_,
//literal
 primitive, //This value encompasses all values
 id_,
 int_lit_,
 float_lit_,
 rune_lit_,
 string_lit_,
 bool_lit_,
//Operations
 incre_,
 decre_,
 decla_,
//Assign_op
 operator,
 eq_,
 add_eq_,
 minus_eq_,
 mult_eq_,
 div_eq_,
 mod_eq_,
 amp_eq_,
 vb_eq_,
 caret_eq_,
 ls_eq_,
 rs_eq_,
 unknown_eq_,

//expr_op
 mult_,
 div_,
 mod_,
 amp_,
 unknown_,
 ls_,
 rs_,
 vb_,
 caret_,
 minus_,
 add_,
 equality_,
 lt_,
 gt_,
 lteq_,
 gteq_,
 not_eq_,
 and_,
 or_,
 u_add,
 u_minus,
 u_caret,
 u_not,

//------------------------------------
//Intermediate Nodes
 go_prog, //Root Node, has a symbol table
  pckg_decl,
  top_decl,
    func_decl,
      signature,
      function,
      params,
      params_decl,
    decl,
      var_decl,
        var_spec,
          var_spec_1,
          var_spec_2,
          var_spec_3,
      type_decl,
        type_spec,
        type,
          field_decl,
  //Statement Nodes Types
    stmt,
      simple_stmt,
      assign_stmt,
      short_decl,
      inc_stmt,
      dec_stmt,
      print_stmt,
      println_stmt,
      return_stmt,
      if_stmt,
        if_cond,
        else_block,
      for_stmt,
        condition,
        for_stmt_clause,
      switch_stmt,
        switch_cond,
          switch_cond_1,
          switch_cond_2,
          switch_cond_3,
          switch_cond_4,
        case_clause,
          switch_case,
      break_stmt,
      cont_stmt,
      expr_stmt,
  //Expression Nodes Types
  expr,
    append,
    unary_op,
    primary_expr,
      operand,
      func_call,
        selector,
        type_cast,
        index,
        slice,
        slice_1,
        slice_2,
        slice_3,
        slice_4,
        slice_5,
        slice_6

}var;

union value{
  int     int_val;
  float   float_val;
  char *  str_val;
};

typedef struct symbol_tbl{
  //Currently Empty for now
}table;

typedef struct vector{
  int size;
  int capacity;
  struct node ** valAt;
}vector;

typedef struct node{
	int type;
  int exact_type;
  int line_num;
  int char_num;
	union value val;

  struct symbol_tbl * table;
  struct node * parent;
	struct vector * child_list;
}node;

node * create_node(int type, int exact_type, int line_num, int char_num);
node * create_node_int(node * parent, int type, int val, int line_num, int char_num);
node * create_node_float(node * parent, int type, float val, int line_num, int char_num);
node * create_node_str(node * parent, int type, char * val, int line_num, int char_num);
vector * create_vector();


void set_exact_type(node * ret, int exact_type);

int add_node(node * parent, node * child);
int add_element(vector * list, node * element);
int remove_element(vector * list, node * element);
int free_vector(vector * list);
int free_node(node * tree);

//pretty printing functions
int print_node(node * current);
int print_primitive(node * current);
int print_go_prog(node * current);
int print_block(node * current);
int print_list(node * current);
int print_pckg(node * current);
int print_top_decl(node * current);
int print_decl(node * current);
int print_func_decl(node * current);
int print_params_decl(node * current);
int print_params(node * current);
int print_var_decl(node * current);
int print_var_spec(node * current);
int print_type_decl(node * current);
int print_field_decl(node * current);
int print_type(node * current);
int print_type_spec(node * current);
int print_a_stmt(node * current);
int print_simple_stmt(node * current);
int print_assign_stmt(node * current);
int print_short_decl(node * current);
int print_if_stmt(node * current);
int print_if_cont(node * current);
int print_for_stmt(node * current);
int print_for_stmt_clause(node * current);
int print_switch_stmt(node * current);
int print_switch_case(node * current);
int print_case_clause(node * current);
int print_switch_cond(node * current);
int print_expr(node * current);
int print_primary_expr(node * current);
int print_operand(node * current);
int print_func_call(node * current);
int print_type_cast(node * current);
int print_slice(node * current);
int print_operator(node * current);
int print_type_id(node * current);
int print_signature(node * current);
int print_function(node * current);

//Not sure if needed
//int delete_node(node * tree, node * deleted);
//int adopt_children(node * new_parent, node * old_parent);

table * create_symbol_table();
int add_symbol(node * symb, table * sym_tbl);
int find_symbol(node * symb, table * sym_tbl);
