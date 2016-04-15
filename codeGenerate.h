#ifndef __GoLiteCompiler__CODEGEN__H__
#define __GoLiteCompiler__CODEGEN__H__

#include "type_check.h"
#include "type.h"
#include "treeNode.h"
#include "structManager.h"
#include "error.h"
#include <stdio.h>
#include <stdbool.h>

void  codeGen_pattern_funcBody (nodeAST* _declare, FILE* _ostream);

size_t codeGen_temp_counter = 0L;
size_t codeGen_discard_counter = 0L;

char*  codeGen_stringFix(const char* _str) {
    char* ret = (char*)malloc(sizeof(char)*(strlen(_str)+1)*2);
    if (_str[0] == '\"') {  // Trivial
        strcpy(ret, _str);
        return ret;
    } else {                // Raw Literals
        const size_t str_len = strlen(_str) - 2;
        size_t ptr = 0;
        ret[ptr++] = '\"';
        for (size_t iter = 1L; iter < str_len+1; iter++) {
            switch (_str[iter]) {
                case '\a': ret[ptr++] = '\\'; ret[ptr++] = 'a';  break;
                case '\b': ret[ptr++] = '\\'; ret[ptr++] = 'b';  break;
                case '\f': ret[ptr++] = '\\'; ret[ptr++] = 'f';  break;
                case '\n': ret[ptr++] = '\\'; ret[ptr++] = 'n';  break;
                case '\r': ret[ptr++] = '\\'; ret[ptr++] = 'r';  break;
                case '\t': ret[ptr++] = '\\'; ret[ptr++] = 't';  break;
                case '\v': ret[ptr++] = '\\'; ret[ptr++] = 'v';  break;
                case '\\': ret[ptr++] = '\\'; ret[ptr++] = '\\'; break;
                case '\'': ret[ptr++] = '\\'; ret[ptr++] = '\''; break;
                case '\"': ret[ptr++] = '\\'; ret[ptr++] = '"';  break;
                default:   ret[ptr++] = _str[iter]; break;
            }
        }
        ret[ptr++] = '\"';
        return ret;
    }
}

void   codeGen_pattern_expr(nodeAST* _expr, FILE* _ostream) {
    assert(isExpr(_expr));
    switch (_expr->nodeType) {
        case LITERAL_INT:
            fprintf(_ostream, "%d", _expr->nodeValue.intValue);
            return;
        case LITERAL_FLOAT:
            fprintf(_ostream, "%lf", _expr->nodeValue.floatValue);
            return;
        case LITERAL_RUNE: {
            switch (_expr->nodeValue.runeValue) {
                case '\a': fprintf(_ostream, "'\\a'"); return;
                case '\b': fprintf(_ostream, "'\\b'"); return;
                case '\f': fprintf(_ostream, "'\\f'"); return;
                case '\n': fprintf(_ostream, "'\\n'"); return;
                case '\r': fprintf(_ostream, "'\\r'"); return;
                case '\t': fprintf(_ostream, "'\\t'"); return;
                case '\v': fprintf(_ostream, "'\\v'"); return;
                case '\\': fprintf(_ostream, "'\\\\'"); return;
                case '\'': fprintf(_ostream, "'\\''"); return;
                case '\"': fprintf(_ostream, "'\\\"'"); return;
                default:   fprintf(_ostream, "'%c'", _expr->nodeValue.runeValue); return;
            }
            return;
        }
        case LITERAL_STRING: {
            char* str = codeGen_stringFix(_expr->nodeValue.stringValue);
            fprintf(_ostream, "%s", str);
            free(str);
            return;
        }
        case IDENTIFIER:
            fprintf(_ostream, "%s", _expr->nodeValue.identifier);
            return;
        case EXPR_BINARY_OP_EQUAL:
            fprintf(_ostream, "(");
            codeGen_pattern_expr(_expr->nodeValue.equal.left, _ostream);
            fprintf(_ostream, "==");
            codeGen_pattern_expr(_expr->nodeValue.equal.right, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_BINARY_OP_NEQUAL:
            fprintf(_ostream, "(");
            codeGen_pattern_expr(_expr->nodeValue.nequal.left, _ostream);
            fprintf(_ostream, "!=");
            codeGen_pattern_expr(_expr->nodeValue.nequal.right, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_BINARY_OP_LESS:
            fprintf(_ostream, "(");
            codeGen_pattern_expr(_expr->nodeValue.less.left, _ostream);
            fprintf(_ostream, "<");
            codeGen_pattern_expr(_expr->nodeValue.less.right, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_BINARY_OP_LESSEQUAL:
            fprintf(_ostream, "(");
            codeGen_pattern_expr(_expr->nodeValue.lessEqual.left, _ostream);
            fprintf(_ostream, "<=");
            codeGen_pattern_expr(_expr->nodeValue.lessEqual.right, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_BINARY_OP_GREAT:
            fprintf(_ostream, "(");
            codeGen_pattern_expr(_expr->nodeValue.great.left, _ostream);
            fprintf(_ostream, ">");
            codeGen_pattern_expr(_expr->nodeValue.great.right, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_BINARY_OP_GREATEQUAL:
            fprintf(_ostream, "(");
            codeGen_pattern_expr(_expr->nodeValue.greatEqual.left, _ostream);
            fprintf(_ostream, ">=");
            codeGen_pattern_expr(_expr->nodeValue.greatEqual.right, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_BINARY_OP_ADD:
            fprintf(_ostream, "(");
            codeGen_pattern_expr(_expr->nodeValue.add.left, _ostream);
            fprintf(_ostream, "+");
            codeGen_pattern_expr(_expr->nodeValue.add.right, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_BINARY_OP_SUB:
            fprintf(_ostream, "(");
            codeGen_pattern_expr(_expr->nodeValue.sub.left, _ostream);
            fprintf(_ostream, "-");
            codeGen_pattern_expr(_expr->nodeValue.sub.right, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_BINARY_OP_MUL:
            fprintf(_ostream, "(");
            codeGen_pattern_expr(_expr->nodeValue.mul.left, _ostream);
            fprintf(_ostream, "*");
            codeGen_pattern_expr(_expr->nodeValue.mul.right, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_BINARY_OP_DIV:
            fprintf(_ostream, "(");
            codeGen_pattern_expr(_expr->nodeValue.div.left, _ostream);
            fprintf(_ostream, "/");
            codeGen_pattern_expr(_expr->nodeValue.div.right, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_BINARY_OP_MOD:
            fprintf(_ostream, "(");
            codeGen_pattern_expr(_expr->nodeValue.mod.left, _ostream);
            fprintf(_ostream, "%%");
            codeGen_pattern_expr(_expr->nodeValue.mod.right, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_BINARY_OP_AND:
            fprintf(_ostream, "(");
            codeGen_pattern_expr(_expr->nodeValue.bitAnd.left, _ostream);
            fprintf(_ostream, "&");
            codeGen_pattern_expr(_expr->nodeValue.bitAnd.right, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_BINARY_OP_OR:
            fprintf(_ostream, "(");
            codeGen_pattern_expr(_expr->nodeValue.bitOr.left, _ostream);
            fprintf(_ostream, "|");
            codeGen_pattern_expr(_expr->nodeValue.bitOr.right, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_BINARY_OP_XOR:
            fprintf(_ostream, "(");
            codeGen_pattern_expr(_expr->nodeValue.bitXor.left, _ostream);
            fprintf(_ostream, "^");
            codeGen_pattern_expr(_expr->nodeValue.bitXor.right, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_BINARY_OP_ANDNOT:
            fprintf(_ostream, "(");
            codeGen_pattern_expr(_expr->nodeValue.bitAndNot.left, _ostream);
            fprintf(_ostream, "&(~");
            codeGen_pattern_expr(_expr->nodeValue.bitAndNot.right, _ostream);
            fprintf(_ostream, "))");
            return;
        case EXPR_BINARY_OP_LSHIFT:
            fprintf(_ostream, "(");
            codeGen_pattern_expr(_expr->nodeValue.shiftLeft.left, _ostream);
            fprintf(_ostream, "<<");
            codeGen_pattern_expr(_expr->nodeValue.shiftRight.right, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_BINARY_OP_RSHIFT:
            fprintf(_ostream, "(");
            codeGen_pattern_expr(_expr->nodeValue.shiftRight.left, _ostream);
            fprintf(_ostream, ">>");
            codeGen_pattern_expr(_expr->nodeValue.shiftRight.right, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_BINARY_OP_LOGIC_AND:
            fprintf(_ostream, "(");
            codeGen_pattern_expr(_expr->nodeValue.logicAnd.left, _ostream);
            fprintf(_ostream, "&&");
            codeGen_pattern_expr(_expr->nodeValue.logicAnd.right, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_BINARY_OP_LOGIC_OR:
            fprintf(_ostream, "(");
            codeGen_pattern_expr(_expr->nodeValue.logicOr.left, _ostream);
            fprintf(_ostream, "||");
            codeGen_pattern_expr(_expr->nodeValue.logicOr.right, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_UNIARY_OP_NEG:
            fprintf(_ostream, "-");
            codeGen_pattern_expr(_expr->nodeValue.neg.expr, _ostream);
            return;
        case EXPR_UNIARY_OP_NOT:
            fprintf(_ostream, "~");
            codeGen_pattern_expr(_expr->nodeValue.bitNot.expr, _ostream);
            return;
        case EXPR_UNIARY_OP_LOGIC_NOT:
            fprintf(_ostream, "!");
            codeGen_pattern_expr(_expr->nodeValue.logicNot.expr, _ostream);
            return;
        case EXPR_UNIARY_OP_POS:
            codeGen_pattern_expr(_expr->nodeValue.pos.expr, _ostream);
            return;
        case EXPR_FUNC_CALL: {
            fprintf(_ostream, "%s(", _expr->nodeValue.funcCall.target->nodeValue.identifier);
            nodeAST* prams = _expr->nodeValue.funcCall.expr;
            while (prams != NULL) {
                nodeAST* cur_pram = prams->nodeValue.exprList.expr;
                prams = prams->nodeValue.exprList.next;
                codeGen_pattern_expr(cur_pram, _ostream);
                if (prams != NULL) fprintf(_ostream, ", ");
            }
            fprintf(_ostream, ")");
            return;
        }
        case EXPR_APPEND: {
            size_t appendSize = 0L;
            nodeAST* appender = _expr->nodeValue.append.expr;
            while (appender != NULL) {
                appendSize++;
                appender = appender->nodeValue.exprList.next;
            }
            appender = _expr->nodeValue.append.expr;
            for (size_t iter = 0L; iter < appendSize; iter++) {
                fprintf(_ostream, "append(");
            }
            codeGen_pattern_expr(_expr->nodeValue.append.target, _ostream);
            fprintf(_ostream, ", ");
            while (appender != NULL) {
                nodeAST* cur = appender->nodeValue.exprList.expr;
                appender = appender->nodeValue.exprList.next;
                fprintf(_ostream, "std::unique_ptr<");
                struct_local_print_single(cur->sym_tbl_ptr, _ostream);
                fprintf(_ostream, ">(new ");
                struct_local_print_single(cur->sym_tbl_ptr, _ostream);
                fprintf(_ostream, "(");
                codeGen_pattern_expr(cur, _ostream);
                fprintf(_ostream, ")))");
                if (appender!= NULL) {fprintf(_ostream, ", ");}
            }
            return;
        }
        case EXPR_CAST: {
            type* t = _expr->sym_tbl_ptr;
            fprintf(_ostream, "static_cast<");
            struct_local_print_single(t, _ostream);
            fprintf(_ostream, ">(");
            if (_expr->nodeValue.cast.target->nodeType == BASIC_TYPE) {
                codeGen_pattern_expr(_expr->nodeValue.cast.expr, _ostream);
            } else {
                codeGen_pattern_expr(_expr->nodeValue.funcCall.expr->nodeValue.exprList.expr, _ostream);
            }
            fprintf(_ostream, ")");
            return;
        }
        case EXPR_SELECTOR: {
            nodeAST* struct_name = _expr->nodeValue.selector.target;
            codeGen_pattern_expr(struct_name, _ostream);
            fprintf(_ostream, ".%s", _expr->nodeValue.selector.entry->nodeValue.identifier);
            return;
        }
        case EXPR_INDEX: {
            nodeAST* array_name = _expr->nodeValue.index.target;
            fprintf(_ostream, "(*");
            codeGen_pattern_expr(array_name, _ostream);
            fprintf(_ostream, "[");
            codeGen_pattern_expr(_expr->nodeValue.index.entry, _ostream);
            fprintf(_ostream, "])");
            return;
        }
        case EXPR_SLICE: {
            nodeAST* address_format = _expr->nodeValue.slice.entry;
            assert(address_format->nodeType == EXPR_ADDRESS_SLICE ||
                   address_format->nodeType == EXPR_ADDRESS_SLICE_FULL);
            if (address_format->nodeType == EXPR_ADDRESS_SLICE) {
                codeGen_pattern_expr(_expr->nodeValue.slice.target, _ostream);
                fprintf(_ostream, ".slice(");
                nodeAST* begin = address_format->nodeValue.addressSlice.start;
                nodeAST* end   = address_format->nodeValue.addressSlice.end;
                if (begin == NULL) {
                    fprintf(_ostream, "0L");
                } else {
                    codeGen_pattern_expr(begin, _ostream);
                }
                fprintf(_ostream, ", ");
                if (end == NULL) {
                    codeGen_pattern_expr(_expr->nodeValue.slice.target, _ostream);
                    fprintf(_ostream, ".length()");
                } else {
                    codeGen_pattern_expr(end, _ostream);
                }
                fprintf(_ostream, ")");
            } else {
                codeGen_pattern_expr(_expr->nodeValue.slice.target, _ostream);
                fprintf(_ostream, ".slice(");
                nodeAST* begin = address_format->nodeValue.addressSliceFull.start;
                nodeAST* end   = address_format->nodeValue.addressSliceFull.end;
                nodeAST* cap   = address_format->nodeValue.addressSliceFull.max;
                if (begin == NULL) {
                    fprintf(_ostream, "0L");
                } else {
                    codeGen_pattern_expr(begin, _ostream);
                }
                fprintf(_ostream, ", ");
                codeGen_pattern_expr(end, _ostream);
                fprintf(_ostream, ", ");
                codeGen_pattern_expr(cap, _ostream);
                fprintf(_ostream, ") ");
            }
            return;
        }
        default: return;
    }
}
// TODO
void  codeGen_pattern_local_typedeclare(nodeAST* _declare, FILE* _ostream) {
    assert(_declare->nodeType == PROG_DECLARE_TYPE_LIST);
    nodeAST* declareList = _declare;
    while (declareList != NULL) {
        nodeAST* cur_declare = declareList->nodeValue.typeDeclareList.typeDeclare;
        declareList = declareList->nodeValue.typeDeclareList.next;
        // BLANK TYPEDEF -> ignored
        if (strcmp(cur_declare->nodeValue.typeDeclare.identifier->nodeValue.identifier, "_") == 0)
            continue;
        
        type* alias_type = cur_declare->nodeValue.typeDeclare.identifier->sym_tbl_ptr;
        type* sub_type = struct_has_struct(alias_type->spec_type.alias_type.a_type);
        if (sub_type != NULL)
            struct_local_scan_struct(sub_type, _ostream);
        fprintf(_ostream, "typedef ");
        struct_local_print_single(alias_type->spec_type.alias_type.a_type, _ostream);
        fprintf(_ostream, " %s;\n", cur_declare->nodeValue.typeDeclare.identifier->
                                    nodeValue.identifier);
    }
}
void  codeGen_pattern_local_vardeclare (nodeAST* _declare, FILE* _ostream) {
    assert(_declare->nodeType == PROG_DECLARE_VAR_LIST);
    while (_declare != NULL) {
        nodeAST* cur = _declare->nodeValue.varDeclareList.varDeclare;
        _declare = _declare->nodeValue.varDeclareList.next;
        nodeAST* ids = cur->nodeValue.varDeclare.idList;
        nodeAST* init_exprs = cur->nodeValue.varDeclare.initExpr;
        // TYPE are generated use typecheck info
        while (ids != NULL) {
            nodeAST* id = ids->nodeValue.identifierList.identifier;
            ids = ids->nodeValue.identifierList.next;
            type* sub_type = NULL;
            if (id->sym_tbl_ptr != NULL) sub_type = struct_has_struct(id->sym_tbl_ptr);
            if (sub_type != NULL) {
                struct_local_scan_struct(sub_type, _ostream);
            }
            if (init_exprs != NULL) {
                if (strcmp("_", id->nodeValue.identifier) == 0) {
                    struct_local_print_single(init_exprs->nodeValue.exprList.expr->sym_tbl_ptr, _ostream);
                    fprintf(_ostream, " GoLite_discard_%lu = ", codeGen_discard_counter++);
                    codeGen_pattern_expr(init_exprs->nodeValue.exprList.expr, _ostream);
                    init_exprs = init_exprs->nodeValue.exprList.next;
                } else {
                    struct_local_print_single(id->sym_tbl_ptr, _ostream);
                    fprintf(_ostream, " %s = ", id->nodeValue.identifier);
                    codeGen_pattern_expr(init_exprs->nodeValue.exprList.expr, _ostream);
                    init_exprs = init_exprs->nodeValue.exprList.next;
                }
            } else {
                struct_local_print_single(id->sym_tbl_ptr, _ostream);
                fprintf(_ostream, " %s", id->nodeValue.identifier);
            }
            fprintf(_ostream, ";\n");
        }
    }
}
void  codeGen_pattern_local_inc      (nodeAST* _inc, FILE* _ostream) {
    assert(_inc->nodeType == STATE_INC);
    nodeAST* target = _inc->nodeValue.inc.expr;
    type* target_type = target->sym_tbl_ptr;
    switch (target_type->type) {
        case LITERAL_INT:
        case LITERAL_RUNE:
        case LITERAL_FLOAT:
            codeGen_pattern_expr(target, _ostream);
            fprintf(_ostream, "++;\n");
            return;
        default:
            dumpErrorMsg("Implementation Error", target->lineNumber);
            break;
    }
}
void  codeGen_pattern_local_dec      (nodeAST* _dec, FILE* _ostream) {
    assert(_dec->nodeType == STATE_DEC);
    nodeAST* target = _dec->nodeValue.inc.expr;
    type* target_type = target->sym_tbl_ptr;
    switch (target_type->type) {
        case LITERAL_INT:
        case LITERAL_RUNE:
        case LITERAL_FLOAT:
            codeGen_pattern_expr(target, _ostream);
            fprintf(_ostream, "--;\n");
            return;
        default:
            dumpErrorMsg("Implementation Error", target->lineNumber);
            break;
    }
}
void  codeGen_pattern_local_print    (nodeAST* _print, FILE* _ostream) {
    fprintf(_ostream, "std::cout << ");
    nodeAST* printList = _print->nodeValue.print.expr;
    while (printList != NULL) {
        nodeAST* ptr = printList->nodeValue.exprList.expr;
        printList = printList->nodeValue.exprList.next;
        codeGen_pattern_expr(ptr, _ostream);
        if (printList != NULL) fprintf(_ostream, " << ' ' << ");
    }
    fprintf(_ostream, ";\n");
}
void  codeGen_pattern_local_println  (nodeAST* _println, FILE* _ostream) {
    fprintf(_ostream, "std::cout << ");
    nodeAST* printList = _println->nodeValue.print.expr;
    while (printList != NULL) {
        nodeAST* ptr = printList->nodeValue.exprList.expr;
        printList = printList->nodeValue.exprList.next;
        codeGen_pattern_expr(ptr, _ostream);
        if (printList != NULL) fprintf(_ostream, " << ' ' << ");
    }
    fprintf(_ostream, " << std::endl;\n");
}
void  codeGen_pattern_local_return   (nodeAST* _ret, FILE* _ostream) {
    assert(_ret->nodeType == STATE_RETURN);
    if (_ret->nodeValue.ret.expr == NULL) {
        fprintf(_ostream, "return;\n");
        return;
    }
    fprintf(_ostream, "return ");
    codeGen_pattern_expr(_ret->nodeValue.ret.expr, _ostream);
    fprintf(_ostream, ";\n");
    return;
}
void  codeGen_pattern_local_assign   (nodeAST* _assign, FILE* _ostream) {
    assert(_assign->nodeType == STATE_ASSIGN);
    nodeAST* left  = _assign->nodeValue.assign.left;
    nodeAST* right = _assign->nodeValue.assign.right;
    if (left->nodeValue.exprList.next == NULL) {
        codeGen_pattern_expr(left->nodeValue.exprList.expr, _ostream);
        fprintf(_ostream, " = ");
        codeGen_pattern_expr(right->nodeValue.exprList.expr, _ostream);
        fprintf(_ostream, ";\n");
        return;
    }
    size_t cur_counter = codeGen_temp_counter;
    while (right != NULL) {
        nodeAST* init_expr = right->nodeValue.exprList.expr;
        right = right->nodeValue.exprList.next;
        struct_local_print_single(init_expr->sym_tbl_ptr, _ostream);
        fprintf(_ostream, " GoLite_local_%lu", codeGen_temp_counter);
        codeGen_temp_counter++;
        fprintf(_ostream, " = ");
        codeGen_pattern_expr(init_expr, _ostream);
        fprintf(_ostream, ";\n");
    }
    left = _assign->nodeValue.assign.left;
    while (left != NULL) {
        nodeAST* id = left->nodeValue.exprList.expr;
        left  = left->nodeValue.exprList.next;
        if (id->nodeType == IDENTIFIER &&
            strcmp(id->nodeValue.identifier, "_") == 0) continue;
        codeGen_pattern_expr(id, _ostream);
        fprintf(_ostream, " = GoLite_local_%lu;\n", cur_counter);
        cur_counter++;
    }
}
void  codeGen_pattern_local_assignAdd(nodeAST* _assignAdd, FILE* _ostream) {
    assert(_assignAdd->nodeType == STATE_ASSIGN_ADD);
    codeGen_pattern_expr(_assignAdd->nodeValue.assignAdd.left, _ostream);
    fprintf(_ostream, " += ");
    codeGen_pattern_expr(_assignAdd->nodeValue.assignAdd.right, _ostream);
    fprintf(_ostream, ";\n");
    return;
}
void  codeGen_pattern_local_assignSub(nodeAST* _assignSub, FILE* _ostream) {
    assert(_assignSub->nodeType == STATE_ASSIGN_SUB);
    codeGen_pattern_expr(_assignSub->nodeValue.assignSub.left, _ostream);
    fprintf(_ostream, " -= ");
    codeGen_pattern_expr(_assignSub->nodeValue.assignSub.right, _ostream);
    fprintf(_ostream, ";\n");
    return;
}
void  codeGen_pattern_local_assignMul(nodeAST* _assignMul, FILE* _ostream) {
    assert(_assignMul->nodeType == STATE_ASSIGN_MUL);
    codeGen_pattern_expr(_assignMul->nodeValue.assignMul.left, _ostream);
    fprintf(_ostream, " *= ");
    codeGen_pattern_expr(_assignMul->nodeValue.assignMul.right, _ostream);
    fprintf(_ostream, ";\n");
    return;
}
void  codeGen_pattern_local_assignDiv(nodeAST* _assignDiv, FILE* _ostream) {
    assert(_assignDiv->nodeType == STATE_ASSIGN_DIV);
    codeGen_pattern_expr(_assignDiv->nodeValue.assignDiv.left, _ostream);
    fprintf(_ostream, " /= ");
    codeGen_pattern_expr(_assignDiv->nodeValue.assignDiv.right, _ostream);
    fprintf(_ostream, ";\n");
}
void  codeGen_pattern_local_assignMod(nodeAST* _assignMod, FILE* _ostream) {
    assert(_assignMod->nodeType == STATE_ASSIGN_MOD);
    codeGen_pattern_expr(_assignMod->nodeValue.assignMod.left, _ostream);
    fprintf(_ostream, " %%= ");
    codeGen_pattern_expr(_assignMod->nodeValue.assignMod.right, _ostream);
    fprintf(_ostream, ";\n");
    return;
}
void  codeGen_pattern_local_assignAnd(nodeAST* _assignAnd, FILE* _ostream) {
    assert(_assignAnd->nodeType == STATE_ASSIGN_AND);
    codeGen_pattern_expr(_assignAnd->nodeValue.assignAnd.left, _ostream);
    fprintf(_ostream, " &= ");
    codeGen_pattern_expr(_assignAnd->nodeValue.assignAnd.right, _ostream);
    fprintf(_ostream, ";\n");
    return;
}
void  codeGen_pattern_local_assignOr (nodeAST* _assignOr,  FILE* _ostream) {
    assert(_assignOr->nodeType == STATE_ASSIGN_OR);
    codeGen_pattern_expr(_assignOr->nodeValue.assignOr.left, _ostream);
    fprintf(_ostream, " |= ");
    codeGen_pattern_expr(_assignOr->nodeValue.assignOr.right, _ostream);
    fprintf(_ostream, ";\n");
    return;
}
void  codeGen_pattern_local_assignXor(nodeAST* _assignXor, FILE* _ostream) {
    assert(_assignXor->nodeType == STATE_ASSIGN_XOR);
    codeGen_pattern_expr(_assignXor->nodeValue.assignXor.left, _ostream);
    fprintf(_ostream, " ^= ");
    codeGen_pattern_expr(_assignXor->nodeValue.assignXor.right, _ostream);
    fprintf(_ostream, ";\n");
    return;
}
void  codeGen_pattern_local_assignSL (nodeAST* _assignSl,  FILE* _ostream) {
    assert(_assignSl->nodeType == STATE_ASSIGN_SHIFTLEFT);
    codeGen_pattern_expr(_assignSl->nodeValue.assignShiftLeft.left, _ostream);
    fprintf(_ostream, " <<= ");
    codeGen_pattern_expr(_assignSl->nodeValue.assignShiftLeft.right, _ostream);
    fprintf(_ostream, ";\n");
    return;
}
void  codeGen_pattern_local_assignRL (nodeAST* _assignRl,  FILE* _ostream) {
    assert(_assignRl->nodeType == STATE_ASSIGN_SHIFTRIGHT);
    codeGen_pattern_expr(_assignRl->nodeValue.assignShiftRight.left, _ostream);
    fprintf(_ostream, " >>= ");
    codeGen_pattern_expr(_assignRl->nodeValue.assignShiftRight.right, _ostream);
    fprintf(_ostream, ";\n");
    return;
}
void  codeGen_pattern_local_assignAndnot(nodeAST* _andNot, FILE* _ostream) {
    assert(_andNot->nodeType == STATE_ASSIGN_ANDNOT);
    codeGen_pattern_expr(_andNot->nodeValue.assignAndNot.left, _ostream);
    fprintf(_ostream, " &= ~(");
    codeGen_pattern_expr(_andNot->nodeValue.assignAndNot.right, _ostream);
    fprintf(_ostream, ");\n");
    return;
}
void  codeGen_pattern_local_if       (nodeAST* _if,        FILE* _ostream) {
    assert(_if->nodeType == STATE_IF);
    nodeAST* init_state = _if->nodeValue.ifBlock.condition->nodeValue.ifCondition.state;
    nodeAST* init_expr  = _if->nodeValue.ifBlock.condition->nodeValue.ifCondition.expr;
    if (init_state == NULL) {
        fprintf(_ostream, "if (");
        codeGen_pattern_expr(init_expr, _ostream);
        fprintf(_ostream, ") {\n");
        codeGen_pattern_funcBody(_if->nodeValue.ifBlock.block_true, _ostream);
        fprintf(_ostream, "}\n");
    } else {
        fprintf(_ostream, "{\n");
        codeGen_pattern_funcBody(init_state, _ostream);
        fprintf(_ostream, "if (");
        codeGen_pattern_expr(init_expr, _ostream);
        fprintf(_ostream, ") {\n");
        codeGen_pattern_funcBody(_if->nodeValue.ifBlock.block_true, _ostream);
        fprintf(_ostream, "}\n}\n");
    }
}
void  codeGen_pattern_local_ifelse   (nodeAST* _ifelse,    FILE* _ostream) {
    assert(_ifelse->nodeType == STATE_IF_ELSE);
    nodeAST* init_state = _ifelse->nodeValue.ifElseBlock.condition->nodeValue.ifCondition.state;
    nodeAST* init_expr  = _ifelse->nodeValue.ifElseBlock.condition->nodeValue.ifCondition.expr;
    if (init_state == NULL) {
        fprintf(_ostream, "if (");
        codeGen_pattern_expr(init_expr, _ostream);
        fprintf(_ostream, ") {\n");
        codeGen_pattern_funcBody(_ifelse->nodeValue.ifElseBlock.block_true, _ostream);
        fprintf(_ostream, "} else {\n");
        codeGen_pattern_funcBody(_ifelse->nodeValue.ifElseBlock.block_false, _ostream);
        fprintf(_ostream, "}\n");
    } else {
        fprintf(_ostream, "{\n");
        codeGen_pattern_funcBody(init_state, _ostream);
        fprintf(_ostream, "if (");
        codeGen_pattern_expr(init_expr, _ostream);
        fprintf(_ostream, ") {\n");
        codeGen_pattern_funcBody(_ifelse->nodeValue.ifElseBlock.block_true, _ostream);
        fprintf(_ostream, "} else {\n");
        codeGen_pattern_funcBody(_ifelse->nodeValue.ifElseBlock.block_false, _ostream);
        fprintf(_ostream, "}\n}\n");
    }
}
void  codeGen_pattern_local_for      (nodeAST* _for,       FILE* _ostream) {
    char* for_break_label = codeGen_push_break_label();
    char* for_continue_label = codeGen_push_continue_label();
    assert(_for->nodeType == STATE_FOR);
    nodeAST* conditon = _for->nodeValue.forBlock.condition;
    if (conditon == NULL) {
        fprintf(_ostream, "while (true) {\n");
        codeGen_pattern_funcBody(_for->nodeValue.forBlock.block, _ostream);
        fprintf(_ostream, "%s:\n", for_continue_label);
        fprintf(_ostream, "}\n");
        fprintf(_ostream, "%s: ;\n", for_break_label);
        codeGen_pop_break_label();
        codeGen_pop_continue_label();
        return;
    } else if (conditon->nodeType == STATE_UTILITY_FOR_CLAUSE) {
        // full for
        nodeAST* init_state = conditon->nodeValue.forClause.init;
        nodeAST* boundary   = conditon->nodeValue.forClause.condition;
        nodeAST* step_state = conditon->nodeValue.forClause.step;
        if (init_state == NULL && boundary == NULL && step_state == NULL) {
            fprintf(_ostream, "while (true) {\n");
            codeGen_pattern_funcBody(_for->nodeValue.forBlock.block, _ostream);
            fprintf(_ostream, "%s: ;\n", for_continue_label);
            fprintf(_ostream, "}\n");
            fprintf(_ostream, "%s: ;\n", for_break_label);
            codeGen_pop_break_label();
            codeGen_pop_continue_label();
            return;
        }
        if (init_state != NULL) fprintf(_ostream, "{\n");
        if (init_state != NULL) codeGen_pattern_funcBody(init_state, _ostream);
        fprintf(_ostream, "while(");
        if (boundary != NULL) {
            codeGen_pattern_expr(boundary, _ostream);
        } else {
            fprintf(_ostream, "true");
        }
        fprintf(_ostream, ") {\n");
        codeGen_pattern_funcBody(_for->nodeValue.forBlock.block, _ostream);
        fprintf(_ostream, "%s: ;\n", for_continue_label);
        if (step_state != NULL)  codeGen_pattern_funcBody(step_state, _ostream);
        fprintf(_ostream, "}\n");
        fprintf(_ostream, "%s: ;\n", for_break_label);
        if (init_state != NULL) fprintf(_ostream, "}\n");
        codeGen_pop_break_label();
        codeGen_pop_continue_label();
        return;
    } else {
        fprintf(_ostream, "while (");
        codeGen_pattern_expr(conditon, _ostream);
        fprintf(_ostream, ") {\n");
        codeGen_pattern_funcBody(_for->nodeValue.forBlock.block, _ostream);
        fprintf(_ostream, "%s: ;\n", for_continue_label);
        fprintf(_ostream, "}\n");
        fprintf(_ostream, "%s: ;\n", for_break_label);
        codeGen_pop_break_label();
        codeGen_pop_continue_label();
        return;
    }
}
void  codeGen_pattern_local_switch   (nodeAST* _switch,    FILE* _ostream) {
    assert(_switch->nodeType == STATE_SWITCH);
    char* switch_break_label = codeGen_push_break_label();
    nodeAST* init_state = _switch->nodeValue.switchBlock.condition->nodeValue.switchCondition.state;
    nodeAST* cond_expr  = _switch->nodeValue.switchBlock.condition->nodeValue.switchCondition.expr;
    if (init_state != NULL) fprintf(_ostream, "{\n");
    if (init_state != NULL) codeGen_pattern_funcBody(init_state, _ostream);
    if (cond_expr != NULL) {
        struct_local_print_single(cond_expr->sym_tbl_ptr, _ostream);
        char* switch_var = (char*)malloc(sizeof(char)*256);
        sprintf(switch_var, "GoLite_local_%lu", codeGen_temp_counter);
        codeGen_temp_counter++;
        fprintf(_ostream, " %s = ", switch_var);
        codeGen_pattern_expr(cond_expr, _ostream);
        fprintf(_ostream, ";\n");
        nodeAST* default_case = NULL;
        nodeAST* ptr = _switch->nodeValue.switchBlock.block;
        assert(ptr->nodeType == STATE_UTILITY_CASE_LIST);
        bool if_flag = true;
        while (ptr != NULL) {
            nodeAST* clause = ptr->nodeValue.caseList.state;
            ptr = ptr->nodeValue.caseList.next;
            if (clause->nodeValue.caseClause.expr == NULL) {
                default_case = clause;
                continue;
            }
            if (if_flag == true) {
                fprintf(_ostream, "if (");
                if_flag = false;
            } else {
                fprintf(_ostream, "else if (");
            }
            nodeAST* iter = clause->nodeValue.caseClause.expr;
            while (iter != NULL) {
                nodeAST* expr = iter->nodeValue.exprList.expr;
                iter = iter->nodeValue.exprList.next;
                fprintf(_ostream, "%s == ", switch_var);
                codeGen_pattern_expr(expr, _ostream);
                if (iter != NULL) {
                    fprintf(_ostream, " || ");
                }
            }
            fprintf(_ostream, ") {\n");
            codeGen_pattern_funcBody(clause->nodeValue.caseClause.state, _ostream);
            fprintf(_ostream, "} ");
        }
        if (default_case != NULL) {
            fprintf(_ostream, "else {\n");
            codeGen_pattern_funcBody(default_case->nodeValue.caseClause.state, _ostream);
            fprintf(_ostream, "}\n");
        } else {
            fprintf(_ostream, "\n");
        }
        free(switch_var);
    } else {
        nodeAST* default_case = NULL;
        nodeAST* ptr = _switch->nodeValue.switchBlock.block;
        assert(ptr->nodeType == STATE_UTILITY_CASE_LIST);
        bool if_flag = true;
        while (ptr != NULL) {
            nodeAST* clause = ptr->nodeValue.caseList.state;
            ptr = ptr->nodeValue.caseList.next;
            if (clause->nodeValue.caseClause.expr == NULL) {
                default_case = clause;
                continue;
            }
            if (if_flag == true) {
                fprintf(_ostream, "if (");
                if_flag = false;
            } else {
                fprintf(_ostream, "else if (");
            }
            nodeAST* iter = clause->nodeValue.caseClause.expr;
            while (iter != NULL) {
                nodeAST* expr = iter->nodeValue.exprList.expr;
                iter = iter->nodeValue.exprList.next;
                codeGen_pattern_expr(expr, _ostream);
                if (iter != NULL) {
                    fprintf(_ostream, " || ");
                }
            }
            fprintf(_ostream, ") {\n");
            codeGen_pattern_funcBody(clause->nodeValue.caseClause.state, _ostream);
            fprintf(_ostream, "} ");
        }
        if (default_case != NULL) {
            fprintf(_ostream, "else {\n");
            codeGen_pattern_funcBody(default_case->nodeValue.caseClause.state, _ostream);
            fprintf(_ostream, "}\n");
        } else {
            fprintf(_ostream, "\n");
        }
    }
    fprintf(_ostream, "%s: ;\n", switch_break_label);
    if (init_state != NULL) fprintf(_ostream, "}\n");
    codeGen_pop_break_label();
}
void  codeGen_pattern_local_shortDec (nodeAST* _shortDec,  FILE* _ostream) {
    assert(_shortDec->nodeType == STATE_SHORT_DECLARE);
    nodeAST* target_list = _shortDec->nodeValue.shortDeclare.left;
    nodeAST* init_list   = _shortDec->nodeValue.shortDeclare.right;
    size_t list_length = 0; nodeAST* ptr = target_list;
    while (ptr != NULL) {
        list_length++;
        ptr = ptr->nodeValue.exprList.next;
    }
    size_t cur_counter = codeGen_temp_counter;
    for (size_t iter = 0; iter < list_length; iter++) {
        nodeAST* cur_expr = init_list->nodeValue.exprList.expr;
        init_list = init_list->nodeValue.exprList.next;
        struct_local_print_single(cur_expr->sym_tbl_ptr, _ostream);
        fprintf(_ostream, " GoLite_local_%lu = ", codeGen_temp_counter);
        codeGen_temp_counter++;
        codeGen_pattern_expr(cur_expr, _ostream);
        fprintf(_ostream, ";\n");
    }
    for (size_t iter = 0; iter < list_length; iter++) {
        bool need_define = false;
        if (_shortDec->nodeValue.shortDeclare.new_stuff[iter] == 1) {
            need_define = true;
        } else {
            need_define = false;
        }
        nodeAST* id = target_list->nodeValue.exprList.expr;
        target_list = target_list->nodeValue.exprList.next;
        if (strcmp(id->nodeValue.identifier, "_") == 0) continue;
        if (need_define) {
            struct_local_print_single(id->sym_tbl_ptr, _ostream);
            fprintf(_ostream, " %s = GoLite_local_%lu;\n", id->nodeValue.identifier, cur_counter + iter);
        } else {
            fprintf(_ostream, "%s = GoLite_local%lu;\n", id->nodeValue.identifier, cur_counter+ iter);
        }
    }
}
void  codeGen_pattern_local_break    (nodeAST* _braek,     FILE* _ostream) {
    assert(_braek->nodeType == STATE_CONTROL_BREAK);
    char* label = codeGen_peep_break_label();
    fprintf(_ostream, "goto %s;\n", label);
    return;
}
void  codeGen_pattern_local_contine  (nodeAST* _continue,  FILE* _ostream) {
    assert(_continue->nodeType == STATE_CONTROL_CONTINUE);
    char* label = codeGen_peep_continue_label();
    fprintf(_ostream, "goto %s;\n", label);
    return;
}

void  codeGen_pattern_funcBody (nodeAST* _declare, FILE* _ostream) {
    if (_declare == NULL) return;
    if (isExpr(_declare)) {
        codeGen_pattern_expr(_declare, _ostream);
        fprintf(_ostream, ";\n");
        return;
    }
    switch (_declare->nodeType) {
        case STATE_UTILITY_STATELIST:
            if (_declare->nodeValue.stateList.state != NULL &&
                _declare->nodeValue.stateList.state->nodeType == STATE_UTILITY_STATELIST) {
                fprintf(_ostream, "{\n");
            }
            codeGen_pattern_funcBody(_declare->nodeValue.stateList.state, _ostream);
            if (_declare->nodeValue.stateList.state != NULL &&
                _declare->nodeValue.stateList.state->nodeType == STATE_UTILITY_STATELIST) {
                fprintf(_ostream, "}\n");
            }
            codeGen_pattern_funcBody(_declare->nodeValue.stateList.next, _ostream);
            return;
        case PROG_DECLARE_TYPE_LIST: codeGen_pattern_local_typedeclare(_declare, _ostream); return;
        case PROG_DECLARE_VAR_LIST: codeGen_pattern_local_vardeclare(_declare, _ostream); return;
        case STATE_INC: codeGen_pattern_local_inc(_declare, _ostream); return;
        case STATE_DEC: codeGen_pattern_local_dec(_declare, _ostream); return;
        case STATE_PRINT: codeGen_pattern_local_print(_declare, _ostream); return;
        case STATE_PRINTLN: codeGen_pattern_local_println(_declare, _ostream); return;
        case STATE_RETURN: codeGen_pattern_local_return(_declare, _ostream); return;
        case STATE_ASSIGN: codeGen_pattern_local_assign(_declare, _ostream); return;
        case STATE_ASSIGN_ADD: codeGen_pattern_local_assignAdd(_declare, _ostream); return;
        case STATE_ASSIGN_SUB: codeGen_pattern_local_assignSub(_declare, _ostream); return;
        case STATE_ASSIGN_MUL: codeGen_pattern_local_assignMul(_declare, _ostream); return;
        case STATE_ASSIGN_DIV: codeGen_pattern_local_assignDiv(_declare, _ostream); return;
        case STATE_ASSIGN_MOD: codeGen_pattern_local_assignMod(_declare, _ostream); return;
        case STATE_ASSIGN_AND: codeGen_pattern_local_assignAnd(_declare, _ostream); return;
        case STATE_ASSIGN_OR:  codeGen_pattern_local_assignOr(_declare, _ostream); return;
        case STATE_ASSIGN_XOR: codeGen_pattern_local_assignXor(_declare, _ostream); return;
        case STATE_ASSIGN_SHIFTLEFT:  codeGen_pattern_local_assignSL(_declare, _ostream); return;
        case STATE_ASSIGN_SHIFTRIGHT: codeGen_pattern_local_assignRL(_declare, _ostream); return;
        case STATE_ASSIGN_ANDNOT:     codeGen_pattern_local_assignAndnot(_declare, _ostream); return;
        case STATE_IF:                codeGen_pattern_local_if(_declare, _ostream); return;
        case STATE_IF_ELSE:           codeGen_pattern_local_ifelse(_declare, _ostream); return;
        case STATE_FOR:               codeGen_pattern_local_for(_declare, _ostream); return;
        case STATE_SWITCH:            codeGen_pattern_local_switch(_declare, _ostream); return;
        case STATE_SHORT_DECLARE:     codeGen_pattern_local_shortDec(_declare, _ostream); return;
        case STATE_CONTROL_BREAK:     codeGen_pattern_local_break(_declare, _ostream); return;
        case STATE_CONTROL_CONTINUE:  codeGen_pattern_local_contine(_declare, _ostream); return;
        default:
            break;
    }
}

void  codeGen_pattern_function(nodeAST* _function, FILE* _ostream) {
    assert(_function->nodeType == PROG_FUNCTION);
    nodeAST* pramList = _function->nodeValue.function.pramList;
    type* func_type = _function->nodeValue.function.identifier->sym_tbl_ptr;
    type* ret_type = func_type->spec_type.func_type.return_type;
    if (ret_type == NULL) {
        if (strcmp(_function->nodeValue.function.identifier->nodeValue.identifier, "main") == 0L) {
            fprintf(_ostream, "int");
        } else {
            fprintf(_ostream, "void");
        }
    } else {
        struct_global_print_single(ret_type, _ostream);
    }
    fprintf(_ostream, " %s (", _function->nodeValue.function.identifier->nodeValue.identifier);
    pramList = _function->nodeValue.function.pramList;
    while (pramList != NULL) {
        nodeAST* cur_ids = pramList->nodeValue.pramDeclareList.pram->nodeValue.pramDeclare.idList;
        pramList = pramList->nodeValue.pramDeclareList.next;
        while (cur_ids != NULL) {
            nodeAST* id = cur_ids->nodeValue.identifierList.identifier;
            cur_ids = cur_ids->nodeValue.identifierList.next;
            type*    id_type = id->sym_tbl_ptr;
            struct_global_print_single(id_type, _ostream);
            fprintf(_ostream, " %s", id->nodeValue.identifier);
            if (pramList != NULL || cur_ids != NULL) fprintf(_ostream, ", ");
        }
    }
    fprintf(_ostream, ") {\n");
    
    // FUNCTION CONTENT GENERATE HERE
    //codeGen_pattern_function_body(_function->nodeValue.function.block, _ostream);
    codeGen_pattern_funcBody(_function->nodeValue.function.block, _ostream);
    
    fprintf(_ostream, "}\n");
}

void  codeGen_pattern_global_vardeclare(nodeAST* _dec, FILE* _ostream)  {
    assert(_dec->nodeType == PROG_DECLARE_VAR_LIST);
    while (_dec != NULL) {
        nodeAST* cur = _dec->nodeValue.varDeclareList.varDeclare;
        _dec = _dec->nodeValue.varDeclareList.next;
        nodeAST* ids = cur->nodeValue.varDeclare.idList;
        nodeAST* init_exprs = cur->nodeValue.varDeclare.initExpr;
        // TYPE are generated use typecheck info
        while (ids != NULL) {
            nodeAST* id = ids->nodeValue.identifierList.identifier;
            ids = ids->nodeValue.identifierList.next;
            if (init_exprs != NULL) {
                if (strcmp(id->nodeValue.identifier, "_") == 0) {
                    struct_global_print_single(init_exprs->nodeValue.exprList.expr->sym_tbl_ptr,
                                               _ostream);
                    fprintf(_ostream, " GoLite_discard_%lu = ", codeGen_discard_counter++);
                    codeGen_pattern_expr(init_exprs->nodeValue.exprList.expr, _ostream);
                } else {
                    struct_global_print_single(id->sym_tbl_ptr, _ostream);
                    fprintf(_ostream, " %s = ", id->nodeValue.identifier);
                    codeGen_pattern_expr(init_exprs->nodeValue.exprList.expr, _ostream);
                }
                init_exprs = init_exprs->nodeValue.exprList.next;
            } else {
                struct_global_print_single(id->sym_tbl_ptr, _ostream);
                fprintf(_ostream, " %s", id->nodeValue.identifier);
            }
            fprintf(_ostream, ";\n");
        }
    }
}
void  codeGen_debug(nodeAST* _ast, FILE* _ostream) {
    if (_ast == NULL) return;
    switch (_ast->nodeType) {
        case PROG_PROGRAM:
            codeGen_debug(_ast->nodeValue.program.program, _ostream);
            return;
        case PROG_LIST:
            codeGen_debug(_ast->nodeValue.progList.prog, _ostream);
            codeGen_debug(_ast->nodeValue.progList.next, _ostream);
            return;
        case PROG_FUNCTION:
            codeGen_pattern_function(_ast, _ostream);
            return;
        case PROG_DECLARE_VAR_LIST:
            codeGen_pattern_global_vardeclare(_ast, _ostream);
            return;
        default:
            break;
    }
}
#endif
