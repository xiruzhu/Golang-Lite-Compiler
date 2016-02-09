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
 id_,
 int_,
 float_,
 string_,
 rune_,
 bool_,
//literal
 int_lit_,
 float_lit_,
 rune_lit_,
 string_lit_,
//Operations
 incre_,
 decre_,
 decla_,
//Assign_op
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
      params,
    decl,
      var_decl,
        var_spec,
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
      print_stmt,
      println_stmt,
      return_stmt,
      if_stmt,
        if_only_stmt, //Two case of if stmt
        if_else_stmt,
      for_stmt,
        condition,
        for_stmt_clause,
      switch_stmt,
        switch_cond,
        case_clause,
          reg_case, //To differential between the two
          default_,
      break_stmt,
      cont_stmt,
      expr_stmt,
  //Expression Nodes Types
  expr,
    append,
    primary_expr,
      operand,
      func_call,
      type_cast,
      primary_expr,
        selector,
        type_cast,
        slice,

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
	int exact_type;
  int general_type;

  struct symbol_tbl * table;

	union value val;
	struct vector * list;
}node;

node * create_node(int type, union value val);
int add_node(node * parent, node * child);
int free_node(node * tree);
int delete_node(node * tree, node * deleted);
int adopt_children(node * new_parent, node * old_parent);

