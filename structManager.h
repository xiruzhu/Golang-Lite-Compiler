#ifndef structManager_h
#define structManager_h

#include "treeNode.h"
#include "type_check.h"
#include <stdbool.h>
#include <assert.h>

size_t struct_counter = 0L;
size_t struct_dump_skip = 0L;

typedef struct struct_global_entry {
    type* struct_type;
    char* alter_name;
    struct struct_global_entry* next;
} struct_global_entry;
typedef struct struct_local_entry {
    type* struct_type;
    char* alter_name;
    struct struct_local_entry* next;
} struct_local_entry;
struct_global_entry* struct_global = NULL;
struct_local_entry*  struct_local  = NULL;
bool  struct_global_is_defined  (type* _type) {
    struct_global_entry* ptr = struct_global;
    while (ptr != NULL) {
        if (valid_type_comparison(_type, ptr->struct_type) == 0) return true;
        ptr = ptr->next;
    }
    return false;
}
char* struct_global_fetch       (type* _type) {
    struct_global_entry* ptr = struct_global;
    while (ptr != NULL) {
        if (valid_type_comparison(_type, ptr->struct_type) == 0) return ptr->alter_name;
        ptr = ptr->next;
    }
    return NULL;
}
char* struct_global_insert      (type* _type) {
    if (struct_global == NULL) {
        struct_global = (struct_global_entry*)malloc(sizeof(struct_global_entry));
        struct_global->alter_name = (char*)malloc(sizeof(char)*256);
        sprintf(struct_global->alter_name, "GoLite_anonymous_%lu", struct_counter);
        struct_global->struct_type = _type;
        struct_global->next = NULL;
        struct_counter++;
        return struct_global->alter_name;
    } else {
        struct_global_entry* ptr = struct_global;
        while (ptr->next != NULL) ptr = ptr->next;
        ptr->next = (struct_global_entry*)malloc(sizeof(struct_global_entry));
        ptr = ptr->next;
        ptr->alter_name = (char*)malloc(sizeof(char)*256);
        sprintf(ptr->alter_name, "GoLite_anonymous_%lu", struct_counter);
        ptr->struct_type = _type;
        ptr->next = NULL;
        struct_counter++;
        return ptr->alter_name;
    }
}
void  struct_global_print_single(type* _type, FILE* _ostream) {
    switch (_type->type) {
        case LITERAL_INT:    fprintf(_ostream, "int");         return;
        case LITERAL_FLOAT:  fprintf(_ostream, "double");      return;
        case LITERAL_RUNE:   fprintf(_ostream, "char");        return;
        case LITERAL_STRING: fprintf(_ostream, "std::string"); return;
        case LITERAL_BOOL:   fprintf(_ostream, "bool");        return;
        case ARRAY_TYPE:     {
            fprintf(_ostream, "GoLiteArray<");
            struct_global_print_single(_type->spec_type.array_type.a_type, _ostream);
            fprintf(_ostream, ", %d>", _type->spec_type.array_type.length);
            return;
        }
        case SLICE_TYPE:     {
            fprintf(_ostream, "GoLiteSlice<");
            struct_global_print_single(_type->spec_type.slice_type.s_type, _ostream);
            fprintf(_ostream, ">");
            return;
        }
        case STRUCT_TYPE:    {
            assert(struct_global_is_defined(_type));
            char* alter_name = struct_global_fetch(_type);
            fprintf(_ostream, "%s", alter_name);
            return;
        };
        case ALIAS_TYPE:     {
            fprintf(_ostream, "%s", _type->spec_type.alias_type.id);
            return;
        }
        default:             return;
    }
}
void  struct_global_dump_all    (FILE* _ostream) {
    struct_global_entry* entry = struct_global;
    for (size_t iter = 0; iter < struct_dump_skip; iter++) entry = entry->next;
    while (entry != NULL) {
        fprintf(_ostream, "typedef struct {\n");
        type* struct_type = entry->struct_type;
        for (int iter = 0; iter < struct_type->spec_type.struct_type.list_size; iter++) {
            struct_global_print_single(struct_type->spec_type.struct_type.type_list[iter], _ostream);
            fprintf(_ostream, " %s;\n", struct_type->spec_type.struct_type.id_list[iter]);
        }
        fprintf(_ostream, "} %s;\n", entry->alter_name);
        entry = entry->next;
    }
}
void  struct_global_setIgnore   () {
    size_t iter = 0L;
    struct_global_entry* ptr = struct_global;
    while (ptr != NULL) {iter++; ptr = ptr->next;}
    struct_dump_skip = iter;
}

bool  struct_local_is_defined   (type* _type) {
    struct_local_entry* ptr = struct_local;
    if (struct_global_is_defined(_type)) return true;
    while (ptr != NULL) {
        if (struct_comparison(_type, ptr->struct_type) == 0) return true;
        ptr = ptr->next;
    }
    return false;
}
char* struct_local_fetch        (type* _type) {
    struct_local_entry* ptr = struct_local;
    char* globalAttempt = struct_global_fetch(_type);
    if (globalAttempt != NULL) return globalAttempt;
    while (ptr != NULL) {
        if (struct_comparison(_type, ptr->struct_type) == 0) return ptr->alter_name;
        ptr = ptr->next;
    }
    return NULL;
}
char* struct_local_insert       (type* _type) {
    if (struct_local == NULL) {
        struct_local = (struct_local_entry*)malloc(sizeof(struct_local_entry));
        struct_local->alter_name = (char*)malloc(sizeof(char)*256);
        sprintf(struct_local->alter_name, "GoLite_anonymous_%lu", struct_counter);
        struct_local->struct_type = _type;
        struct_local->next = NULL;
        struct_counter++;
        return struct_local->alter_name;
    } else {
        struct_local_entry* ptr = struct_local;
        while (ptr->next != NULL) ptr = ptr->next;
        ptr->next = (struct_local_entry*)malloc(sizeof(struct_local_entry));
        ptr = ptr->next;
        ptr->alter_name = (char*)malloc(sizeof(char)*256);
        sprintf(ptr->alter_name, "GoLite_anonymous_%lu", struct_counter);
        ptr->struct_type = _type;
        ptr->next = NULL;
        struct_counter++;
        return ptr->alter_name;
    }
}
void  struct_local_print_single (type* _type, FILE* _ostream) {
    switch (_type->type) {
        case LITERAL_INT:    fprintf(_ostream, "int");         return;
        case LITERAL_FLOAT:  fprintf(_ostream, "double");      return;
        case LITERAL_RUNE:   fprintf(_ostream, "char");        return;
        case LITERAL_STRING: fprintf(_ostream, "std::string"); return;
        case LITERAL_BOOL:   fprintf(_ostream, "bool");        return;
        case ARRAY_TYPE:     {
            fprintf(_ostream, "GoLiteArray<");
            struct_local_print_single(_type->spec_type.array_type.a_type, _ostream);
            fprintf(_ostream, ", %d>", _type->spec_type.array_type.length);
            return;
        }
        case SLICE_TYPE:     {
            fprintf(_ostream, "GoLiteSlice<");
            struct_local_print_single(_type->spec_type.slice_type.s_type, _ostream);
            fprintf(_ostream, ">");
            return;
        }
        case STRUCT_TYPE:    {
            assert(struct_local_is_defined(_type));
            char* alter_name = struct_local_fetch(_type);
            fprintf(_ostream, "%s", alter_name);
            return;
        };
        case ALIAS_TYPE:     {
            fprintf(_ostream, "%s", _type->spec_type.alias_type.id);
            return;
        }
        default:             return;
    }

}

type* struct_has_struct         (type* _type) {
    switch (_type->type) {
        case LITERAL_INT:    return NULL;
        case LITERAL_FLOAT:  return NULL;
        case LITERAL_RUNE:   return NULL;
        case LITERAL_STRING: return NULL;
        case LITERAL_BOOL:   return NULL;
        case ARRAY_TYPE:     return struct_has_struct(_type->spec_type.array_type.a_type);
        case SLICE_TYPE:     return struct_has_struct(_type->spec_type.slice_type.s_type);
        case STRUCT_TYPE:    return _type;
        case ALIAS_TYPE:     return NULL;
        case TYPE_UNDERSCORE:return NULL;
        default:             return NULL;
    }
}
void struct_global_scan_struct  (type* _type) {
    assert(_type->type == STRUCT_TYPE);
    if (struct_global_is_defined(_type) == true) return;
    for (int iter = 0; iter < _type->spec_type.struct_type.list_size; iter++) {
        type* sub_struct = struct_has_struct(_type->spec_type.struct_type.type_list[iter]);
        if (sub_struct != NULL) {
            struct_global_scan_struct(sub_struct);
        }
    }
    struct_global_insert(_type);
}
void struct_local_scan_struct   (type* _type, FILE* _ostream){
    assert(_type->type == STRUCT_TYPE);
    if (struct_local_is_defined(_type) == true) return;
    for (int iter = 0; iter < _type->spec_type.struct_type.list_size; iter++) {
        type* sub_struct = struct_has_struct(_type->spec_type.struct_type.type_list[iter]);
        if (sub_struct != NULL) {
            struct_local_scan_struct(sub_struct, _ostream);
        }
    }
    fprintf(_ostream, "typedef struct{\n");
    for (int iter = 0; iter < _type->spec_type.struct_type.list_size; iter++) {
        struct_local_print_single(_type->spec_type.struct_type.type_list[iter], _ostream);
        fprintf(_ostream, " %s;\n", _type->spec_type.struct_type.id_list[iter]);
    }
    fprintf(_ostream, "} %s;\n", struct_local_insert(_type));
}

void  codeGen_helper_funcSign   (nodeAST* _ast, FILE* _ostream) {
    if (_ast == NULL) return;
    switch (_ast->nodeType) {
        case PROG_PROGRAM:
            codeGen_helper_funcSign(_ast->nodeValue.program.program, _ostream);
            return;
        case PROG_LIST:
            codeGen_helper_funcSign(_ast->nodeValue.progList.prog, _ostream);
            codeGen_helper_funcSign(_ast->nodeValue.progList.next, _ostream);
            return;
        case PROG_FUNCTION: {
            type* func_type = _ast->nodeValue.function.identifier->sym_tbl_ptr;
            type* ret_type = func_type->spec_type.func_type.return_type;
            if (ret_type == NULL) {
                if (strcmp(_ast->nodeValue.function.identifier->nodeValue.identifier, "main") == 0L) {
                    fprintf(_ostream, "int");
                } else {
                    fprintf(_ostream, "void");
                }
            } else {
                    struct_global_print_single(ret_type, _ostream);
            }
            fprintf(_ostream, " %s (", _ast->nodeValue.function.identifier->nodeValue.identifier);
            nodeAST* pramList = _ast->nodeValue.function.pramList;
            while (pramList != NULL) {
                nodeAST* pram = pramList->nodeValue.pramDeclareList.pram;
                pramList = pramList->nodeValue.pramDeclareList.next;
                nodeAST* ids = pram->nodeValue.pramDeclare.idList;
                while (ids != NULL) {
                    nodeAST* id = ids->nodeValue.identifierList.identifier;
                    ids = ids->nodeValue.identifierList.next;
                    struct_global_print_single(id->sym_tbl_ptr, _ostream);
                    fprintf(_ostream, " %s", id->nodeValue.identifier);
                    if (ids != NULL || pramList != NULL) fprintf(_ostream, ", ");
                }
            }
            fprintf(_ostream, ");\n");
            return;
        }
        default: return;
    }
}
void  codeGen_helper_typeSign   (nodeAST* _ast, FILE* _ostream) {
    if (_ast == NULL) return;
    switch (_ast->nodeType) {
        case PROG_PROGRAM:
            codeGen_helper_typeSign(_ast->nodeValue.program.program, _ostream);
            return;
        case PROG_LIST:
            codeGen_helper_typeSign(_ast->nodeValue.progList.prog, _ostream);
            codeGen_helper_typeSign(_ast->nodeValue.progList.next, _ostream);
            return;
        case PROG_DECLARE_TYPE_LIST: {
            nodeAST* decList = _ast;
            while (decList != NULL) {
                nodeAST* dec_type = decList->nodeValue.typeDeclareList.typeDeclare;
                decList = decList->nodeValue.typeDeclareList.next;
                nodeAST* id = dec_type->nodeValue.typeDeclare.identifier;
                // BLANK TYPEDEF -> ignored
                if (strcmp(id->nodeValue.identifier, "_") == 0) continue;
                type* alias_type = id ->sym_tbl_ptr;
                type* sub_struct = struct_has_struct(alias_type->spec_type.alias_type.a_type);
                if (sub_struct != NULL) {
                    struct_global_scan_struct(sub_struct);
                }
                struct_global_dump_all(_ostream);
                struct_global_setIgnore();
                fprintf(_ostream, "typedef ");
                struct_global_print_single(alias_type->spec_type.alias_type.a_type, _ostream);
                fprintf(_ostream, " %s;\n", id->nodeValue.identifier);
            }
            return;
        }
        case PROG_DECLARE_VAR_LIST: {
            nodeAST* varList = _ast;
            while (varList != NULL) {
                nodeAST* cur_dec = varList->nodeValue.varDeclareList.varDeclare;
                varList = varList->nodeValue.varDeclareList.next;
                nodeAST* ids = cur_dec->nodeValue.varDeclare.idList;
                nodeAST* id = ids->nodeValue.identifierList.identifier;
                type* sub_type = NULL;
                if (id->sym_tbl_ptr != NULL)
                    sub_type = struct_has_struct(id->sym_tbl_ptr);
                if (sub_type != NULL) {
                    struct_global_scan_struct(sub_type);
                }
                struct_global_dump_all(_ostream);
                struct_global_setIgnore();
            }
            return;
        }
            
        default:
            break;
    }
}

void struct_populate_global(nodeAST* _ast) {
    if (_ast == NULL) return;
    switch (_ast->nodeType) {
        case PROG_PROGRAM:
            struct_populate_global(_ast->nodeValue.program.program);
            return;
        case PROG_LIST:
            struct_populate_global(_ast->nodeValue.progList.prog);
            struct_populate_global(_ast->nodeValue.progList.next);
            return;
        case PROG_FUNCTION: {
            nodeAST* pramList = _ast->nodeValue.function.pramList;
            while (pramList != NULL) {
                nodeAST* pram = pramList->nodeValue.pramDeclareList.pram;
                pramList = pramList->nodeValue.pramDeclareList.next;
                nodeAST* id = pram->nodeValue.pramDeclare.idList->nodeValue.identifierList.identifier;
                type* type = id->sym_tbl_ptr;
                if (struct_has_struct(type) != NULL) {
                    struct type* sub_type = struct_has_struct(type);
                    struct_global_scan_struct(sub_type);
                }
            }
            type* func_type = _ast->nodeValue.function.identifier->sym_tbl_ptr;
            type* ret_type  = func_type->spec_type.func_type.return_type;
            if (ret_type == NULL) return;
            if (struct_has_struct(ret_type) == NULL) return;
            type* sub_type = struct_has_struct(ret_type);
            struct_global_scan_struct(sub_type);
        }
        default: return;
    }
}

typedef struct codeGen_label_entry{
    char* label;
    struct codeGen_label_entry* next;
}codeGen_label_entry;

size_t codeGen_label_counter = 0L;

codeGen_label_entry* codeGen_break_label    = NULL;
codeGen_label_entry* codeGen_continue_label = NULL;

char* codeGen_push_break_label()    {
    codeGen_label_entry* new_entry = (codeGen_label_entry*)malloc(sizeof(codeGen_label_entry));
    new_entry->label = malloc(sizeof(char)*256);
    sprintf(new_entry->label, "GoLite_label_%lu", codeGen_label_counter++);
    new_entry->next = codeGen_break_label;
    codeGen_break_label = new_entry;
    return codeGen_break_label->label;
}
char* codeGen_push_continue_label() {
    codeGen_label_entry* new_entry = (codeGen_label_entry*)malloc(sizeof(codeGen_label_entry));
    new_entry->label = malloc(sizeof(char)*256);
    sprintf(new_entry->label, "GoLite_label_%lu", codeGen_label_counter++);
    new_entry->next = codeGen_continue_label;
    codeGen_continue_label = new_entry;
    return codeGen_continue_label->label;
}
char* codeGen_peep_break_label()    {return codeGen_break_label->label;}
char* codeGen_peep_continue_label() {return codeGen_continue_label->label;}
void  codeGen_pop_break_label()     {
    codeGen_label_entry* target = codeGen_break_label;
    codeGen_break_label = codeGen_break_label->next;
    free(target->label);
    free(target);
}
void  codeGen_pop_continue_label()  {
    codeGen_label_entry* target = codeGen_continue_label;
    codeGen_continue_label = codeGen_continue_label->next;
    free(target->label);
    free(target);
}

#endif
