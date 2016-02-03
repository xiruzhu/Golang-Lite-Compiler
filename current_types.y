semi        : semi_colon_
            | new_line_
new_l       : new_line_
            | new_line_ new_l
literal     : float_lit_
            | int_lit_
            | rune_lit_
            | string_lit_
type        : type_name
            | type_lit
            | lrbrac_ type rrbrac_
type_name   : ID_
            | qualified_ID
qualified_ID: package_name dot_ ID_
package_name: ID_
type_lit    : array_type
            | struct_type
            | pointer_type
            | slice_type
array_type  : lsbrac_ array_length rsbrac_ elem_type
array_length: expression
elem_type   : type
struct_type : struct_ lcbrac_ field_decl_list rcbrac_

field_decl_list : field_decl semi
                | field_decl semi field_decl_list

field_decl  : id_list type tag
            | id_list type
            | anon_field tag
            | anon_field

tag         : string_lit_

anon_field  : mult_ type_name
            | type_name

pointer_type: mult_ base_type
base_type   : type
slice_type  : lsbrac_ rsbrac_ elem_type



