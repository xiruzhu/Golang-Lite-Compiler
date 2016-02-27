#ifndef __GoLiteCompiler__PRETTYPRINT__H__
#define __GoLiteCompiler__PRETTYPRINT__H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stdbool.h"
#include "treeNode.h"
#include "memory.h"

extern void yyerror(const char*);
bool isExpr (nodeAST* _AST){
    if (_AST == NULL) return false;
    switch (_AST->nodeType) {
        case EXPR_BINARY_OP_EQUAL:          return true;
        case EXPR_BINARY_OP_NEQUAL:         return true;
        case EXPR_BINARY_OP_LESS:           return true;
        case EXPR_BINARY_OP_LESSEQUAL:      return true;
        case EXPR_BINARY_OP_GREAT:          return true;
        case EXPR_BINARY_OP_GREATEQUAL:     return true;
        case EXPR_BINARY_OP_ADD:            return true;
        case EXPR_BINARY_OP_SUB:            return true;
        case EXPR_BINARY_OP_MUL:            return true;
        case EXPR_BINARY_OP_DIV:            return true;
        case EXPR_BINARY_OP_MOD:            return true;
        case EXPR_BINARY_OP_LSHIFT:         return true;
        case EXPR_BINARY_OP_RSHIFT:         return true;
        case EXPR_BINARY_OP_AND:            return true;
        case EXPR_BINARY_OP_OR:             return true;
        case EXPR_BINARY_OP_XOR:            return true;
        case EXPR_BINARY_OP_ANDNOT:         return true;
        case EXPR_BINARY_OP_LOGIC_AND:      return true;
        case EXPR_BINARY_OP_LOGIC_OR:       return true;
        case EXPR_UNIARY_OP_LOGIC_NOT:      return true;
        case EXPR_UNIARY_OP_NEG:            return true;
        case EXPR_UNIARY_OP_NOT:            return true;
        case EXPR_UNIARY_OP_POS:            return true;
        case EXPR_APPEND:                   return true;
        case EXPR_FUNC_CALL:                return true;
        case EXPR_CAST:                     return true;
        case EXPR_SELECTOR:                 return true;
        case EXPR_INDEX:                    return true;
        case EXPR_SLICE:                    return true;
        case EXPR_ADDRESS_SLICE:            return true;
        case EXPR_ADDRESS_SLICE_FULL:       return true;
        case EXPR_UTILITY_EXPRLIST:         return true;
        
        case LITERAL_INT:                   return true;
        case LITERAL_FLOAT:                 return true;
        case LITERAL_RUNE:                  return true;
        case LITERAL_STRING:                return true;
        case IDENTIFIER:                    return true;
        case IDENTIFIER_LIST:               return true;
        default:                            return false;
    }
}
bool isAssignment (nodeAST* _AST){
    if (_AST == NULL) return false;
    switch (_AST->nodeType) {
        case STATE_ASSIGN:              return true;
        case STATE_ASSIGN_ADD:          return true;
        case STATE_ASSIGN_SUB:          return true;
        case STATE_ASSIGN_MUL:          return true;
        case STATE_ASSIGN_DIV:          return true;
        case STATE_ASSIGN_MOD:          return true;
        case STATE_ASSIGN_AND:          return true;
        case STATE_ASSIGN_OR:           return true;
        case STATE_ASSIGN_XOR:          return true;
        case STATE_ASSIGN_SHIFTLEFT:    return true;
        case STATE_ASSIGN_SHIFTRIGHT:   return true;
        case STATE_ASSIGN_ANDNOT:       return true;
        default:                        return false;
    }
}

void prettyPrintType(nodeAST* _ASTExpr, FILE* _ostream);
void prettyPrintExpr(nodeAST* _ASTExpr, FILE* _ostream);
void prettyPrintIdList(nodeAST* _AST, FILE* _ostream);
void prettyPrintType(nodeAST* _AST, FILE* _ostream);

void prettyPrintExpr(nodeAST* _ASTExpr, FILE* _ostream){
    if (_ASTExpr == NULL) return;
    assert(_ASTExpr->nodeType != NODE_INIT);
    assert(isExpr(_ASTExpr));
    switch (_ASTExpr->nodeType) {
        case LITERAL_INT:
            fprintf(_ostream, "%d", _ASTExpr->nodeValue.intValue); return;
        case LITERAL_FLOAT:
            fprintf(_ostream, "%lf", _ASTExpr->nodeValue.floatValue); return;
        case LITERAL_RUNE:
            fprintf(_ostream, "'%c'", _ASTExpr->nodeValue.runeValue); return;
        case LITERAL_STRING:        //TODO
            fprintf(_ostream, "%s", _ASTExpr->nodeValue.stringValue); return;
        case IDENTIFIER:
            fprintf(_ostream, "%s", _ASTExpr->nodeValue.identifier); return;
        case IDENTIFIER_LIST:
            prettyPrintExpr(_ASTExpr->nodeValue.identifierList.identifier, _ostream);
            if (_ASTExpr->nodeValue.identifierList.next == NULL) return;
            fprintf(_ostream, ", ");
            prettyPrintExpr(_ASTExpr->nodeValue.identifierList.next, _ostream);
            return;
        case EXPR_BINARY_OP_EQUAL:
            fprintf(_ostream, "(");
            prettyPrintExpr(_ASTExpr->nodeValue.equal.left, _ostream);
            fprintf(_ostream, "==");
            prettyPrintExpr(_ASTExpr->nodeValue.equal.right, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_BINARY_OP_NEQUAL:
            fprintf(_ostream, "(");
            prettyPrintExpr(_ASTExpr->nodeValue.nequal.left, _ostream);
            fprintf(_ostream, "!=");
            prettyPrintExpr(_ASTExpr->nodeValue.nequal.right, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_BINARY_OP_LESS:
            fprintf(_ostream, "(");
            prettyPrintExpr(_ASTExpr->nodeValue.less.left, _ostream);
            fprintf(_ostream, "<");
            prettyPrintExpr(_ASTExpr->nodeValue.less.right, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_BINARY_OP_LESSEQUAL:
            fprintf(_ostream, "(");
            prettyPrintExpr(_ASTExpr->nodeValue.lessEqual.left, _ostream);
            fprintf(_ostream, "<=");
            prettyPrintExpr(_ASTExpr->nodeValue.lessEqual.right, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_BINARY_OP_GREAT:
            fprintf(_ostream, "(");
            prettyPrintExpr(_ASTExpr->nodeValue.great.left, _ostream);
            fprintf(_ostream, ">");
            prettyPrintExpr(_ASTExpr->nodeValue.great.right, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_BINARY_OP_GREATEQUAL:
            fprintf(_ostream, "(");
            prettyPrintExpr(_ASTExpr->nodeValue.greatEqual.left, _ostream);
            fprintf(_ostream, ">=");
            prettyPrintExpr(_ASTExpr->nodeValue.greatEqual.right, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_BINARY_OP_ADD:
            fprintf(_ostream, "(");
            prettyPrintExpr(_ASTExpr->nodeValue.add.left, _ostream);
            fprintf(_ostream, "+");
            prettyPrintExpr(_ASTExpr->nodeValue.add.right, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_BINARY_OP_SUB:
            fprintf(_ostream, "(");
            prettyPrintExpr(_ASTExpr->nodeValue.sub.left, _ostream);
            fprintf(_ostream, "-");
            prettyPrintExpr(_ASTExpr->nodeValue.sub.right, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_BINARY_OP_MUL:
            fprintf(_ostream, "(");
            prettyPrintExpr(_ASTExpr->nodeValue.mul.left, _ostream);
            fprintf(_ostream, "*");
            prettyPrintExpr(_ASTExpr->nodeValue.mul.right, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_BINARY_OP_DIV:
            fprintf(_ostream, "(");
            prettyPrintExpr(_ASTExpr->nodeValue.div.left, _ostream);
            fprintf(_ostream, "/");
            prettyPrintExpr(_ASTExpr->nodeValue.div.right, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_BINARY_OP_MOD:
            fprintf(_ostream, "(");
            prettyPrintExpr(_ASTExpr->nodeValue.mod.left, _ostream);
            fprintf(_ostream, "%%");
            prettyPrintExpr(_ASTExpr->nodeValue.mod.right, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_BINARY_OP_LSHIFT:
            fprintf(_ostream, "(");
            prettyPrintExpr(_ASTExpr->nodeValue.shiftLeft.left, _ostream);
            fprintf(_ostream, "<<");
            prettyPrintExpr(_ASTExpr->nodeValue.shiftRight.right, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_BINARY_OP_RSHIFT:
            fprintf(_ostream, "(");
            prettyPrintExpr(_ASTExpr->nodeValue.shiftRight.left, _ostream);
            fprintf(_ostream, ">>");
            prettyPrintExpr(_ASTExpr->nodeValue.shiftRight.right, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_BINARY_OP_AND:
            fprintf(_ostream, "(");
            prettyPrintExpr(_ASTExpr->nodeValue.bitAnd.left, _ostream);
            fprintf(_ostream, "&");
            prettyPrintExpr(_ASTExpr->nodeValue.bitAnd.right, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_BINARY_OP_OR:
            fprintf(_ostream, "(");
            prettyPrintExpr(_ASTExpr->nodeValue.bitOr.left, _ostream);
            fprintf(_ostream, "|");
            prettyPrintExpr(_ASTExpr->nodeValue.bitOr.right, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_BINARY_OP_XOR:
            fprintf(_ostream, "(");
            prettyPrintExpr(_ASTExpr->nodeValue.bitXor.left, _ostream);
            fprintf(_ostream, "^");
            prettyPrintExpr(_ASTExpr->nodeValue.bitXor.right, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_BINARY_OP_ANDNOT:
            fprintf(_ostream, "(");
            prettyPrintExpr(_ASTExpr->nodeValue.bitAndNot.left, _ostream);
            fprintf(_ostream, "&^");
            prettyPrintExpr(_ASTExpr->nodeValue.bitAndNot.right, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_BINARY_OP_LOGIC_AND:
            fprintf(_ostream, "(");
            prettyPrintExpr(_ASTExpr->nodeValue.logicAnd.left, _ostream);
            fprintf(_ostream, "&&");
            prettyPrintExpr(_ASTExpr->nodeValue.logicAnd.right, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_BINARY_OP_LOGIC_OR:
            fprintf(_ostream, "(");
            prettyPrintExpr(_ASTExpr->nodeValue.logicOr.left, _ostream);
            fprintf(_ostream, "||");
            prettyPrintExpr(_ASTExpr->nodeValue.logicOr.right, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_UNIARY_OP_LOGIC_NOT:
            fprintf(_ostream, "(");
            fprintf(_ostream, "!");
            prettyPrintExpr(_ASTExpr->nodeValue.logicNot.expr, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_UNIARY_OP_NEG:
            fprintf(_ostream, "(");
            fprintf(_ostream, "-");
            prettyPrintExpr(_ASTExpr->nodeValue.neg.expr, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_UNIARY_OP_NOT:
            fprintf(_ostream, "(");
            fprintf(_ostream, "!");
            prettyPrintExpr(_ASTExpr->nodeValue.logicNot.expr, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_UNIARY_OP_POS:
            fprintf(_ostream, "(");
            fprintf(_ostream, "+");
            prettyPrintExpr(_ASTExpr->nodeValue.pos.expr, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_APPEND:
            fprintf(_ostream, "(");
            fprintf(_ostream, "append(");
            prettyPrintExpr(_ASTExpr->nodeValue.append.target, _ostream);
            fprintf(_ostream, ", ");
            prettyPrintExpr(_ASTExpr->nodeValue.append.expr, _ostream);
            fprintf(_ostream, ")");
            fprintf(_ostream, ")");
            return;
        case EXPR_FUNC_CALL:
            fprintf(_ostream, "(");
            prettyPrintExpr(_ASTExpr->nodeValue.funcCall.target, _ostream);
            fprintf(_ostream, "(");
            prettyPrintExpr(_ASTExpr->nodeValue.funcCall.expr, _ostream);
            fprintf(_ostream, ")");
            fprintf(_ostream, ")");
            return;
        case EXPR_CAST:
            fprintf(_ostream, "(");
            if (_ASTExpr->nodeValue.cast.target->nodeType == BASIC_TYPE) {
                switch (_ASTExpr->nodeValue.cast.target->nodeValue.basicType) {
                    case BASIC_INT:
                        fprintf(_ostream, "int");
                        break;
                    case BASIC_BOOL:
                        fprintf(_ostream, "bool");
                        break;
                    case BASIC_RUNE:
                        fprintf(_ostream, "rune");
                        break;
                    case BASIC_FLOAT:
                        fprintf(_ostream, "float64");
                        break;
                    case BASIC_STRING:
                        fprintf(_ostream, "string");
                        break;
                }
            } else {
                prettyPrintExpr(_ASTExpr->nodeValue.cast.target, _ostream);
            }
            fprintf(_ostream, "(");
            prettyPrintExpr(_ASTExpr->nodeValue.cast.expr, _ostream);
            fprintf(_ostream, ")");
            fprintf(_ostream, ")");
            return;
        case EXPR_SELECTOR:
            fprintf(_ostream, "(");
            prettyPrintExpr(_ASTExpr->nodeValue.selector.target, _ostream);
            fprintf(_ostream, ".");
            prettyPrintExpr(_ASTExpr->nodeValue.selector.entry, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_INDEX:
            fprintf(_ostream, "(");
            prettyPrintExpr(_ASTExpr->nodeValue.index.target, _ostream);
            fprintf(_ostream, "[");
            prettyPrintExpr(_ASTExpr->nodeValue.index.entry, _ostream);
            fprintf(_ostream, "]");
            fprintf(_ostream, ")");
            return;
        case EXPR_SLICE:
            fprintf(_ostream, "(");
            prettyPrintExpr(_ASTExpr->nodeValue.slice.target, _ostream);
            prettyPrintExpr(_ASTExpr->nodeValue.slice.entry, _ostream);
            fprintf(_ostream, ")");
            return;
        case EXPR_ADDRESS_SLICE:
            fprintf(_ostream, "[");
            if (_ASTExpr->nodeValue.addressSlice.start != NULL) {
                prettyPrintExpr(_ASTExpr->nodeValue.addressSlice.start, _ostream);
            }
            fprintf(_ostream, ":");
            if (_ASTExpr->nodeValue.addressSlice.end != NULL) {
                prettyPrintExpr(_ASTExpr->nodeValue.addressSlice.end, _ostream);
            }
            fprintf(_ostream, "]");
            return;
        case EXPR_ADDRESS_SLICE_FULL:
            fprintf(_ostream, "[");
            if (_ASTExpr->nodeValue.addressSliceFull.start != NULL) {
                prettyPrintExpr(_ASTExpr->nodeValue.addressSliceFull.start, _ostream);
            }
            fprintf(_ostream, ":");
            if (_ASTExpr->nodeValue.addressSliceFull.end != NULL) {
                prettyPrintExpr(_ASTExpr->nodeValue.addressSliceFull.end, _ostream);
            }
            fprintf(_ostream, ":");
            if (_ASTExpr->nodeValue.addressSliceFull.max != NULL) {
                prettyPrintExpr(_ASTExpr->nodeValue.addressSliceFull.max, _ostream);
            }
            fprintf(_ostream, "]");
            return;
        case EXPR_UTILITY_EXPRLIST:
            prettyPrintExpr(_ASTExpr->nodeValue.exprList.expr, _ostream);
            if (_ASTExpr->nodeValue.exprList.next != NULL) {
                fprintf(_ostream, ", ");
                prettyPrintExpr(_ASTExpr->nodeValue.exprList.next, _ostream);
            }
            return;
        default:    return;
    }
}
void prettyPrintIdList(nodeAST* _AST, FILE* _ostream){
    assert(_AST->nodeType == IDENTIFIER_LIST);
    prettyPrintExpr(_AST->nodeValue.identifierList.identifier, _ostream);
    if (_AST->nodeValue.identifierList.next == NULL) return;
    fprintf(_ostream, ", ");
    prettyPrintIdList(_AST->nodeValue.identifierList.next, _ostream);
    return;
}
void prettyPrintStructDecList(nodeAST* _AST, FILE* _ostream){
    assert(_AST->nodeType == STRUCT_TYPE_DEC_LIST);
    nodeAST* currentDeclare = _AST->nodeValue.structTypeDecList.declare;
    prettyPrintIdList(currentDeclare->nodeValue.structTypeDec.identifierList, _ostream);
    fprintf(_ostream, " ");
    prettyPrintType(currentDeclare->nodeValue.structTypeDec.type, _ostream);
    fprintf(_ostream, "\n");
    if (_AST->nodeValue.structTypeDecList.next == NULL) {return;}
    prettyPrintStructDecList(_AST->nodeValue.structTypeDecList.next, _ostream);
    return;
}
void prettyPrintType(nodeAST* _AST, FILE* _ostream){
    if (_AST == NULL) return;
    switch (_AST->nodeType) {
        case BASIC_TYPE:
            switch (_AST->nodeValue.basicType) {
                case BASIC_BOOL:
                    fprintf(_ostream, "bool"); return;
                case BASIC_FLOAT:
                    fprintf(_ostream, "float64"); return;
                case BASIC_INT:
                    fprintf(_ostream, "int"); return;
                case BASIC_RUNE:
                    fprintf(_ostream, "rune"); return;
                case BASIC_STRING:
                    fprintf(_ostream, "string"); return;
            }
        case ARRAY_TYPE:
            fprintf(_ostream, "[%d]", _AST->nodeValue.arrayType.capacity->nodeValue.intValue);
            prettyPrintType(_AST->nodeValue.arrayType.type, _ostream);
            return;
        case SLICE_TYPE:
            fprintf(_ostream, "[]");
            prettyPrintType(_AST->nodeValue.sliceType.type, _ostream);
            return;
        case STRUCT_TYPE:
            fprintf(_ostream, "struct {\n");
            prettyPrintStructDecList(_AST->nodeValue.structType.structDec, _ostream);
            fprintf(_ostream, "}");
            return;
        case IDENTIFIER:
            fprintf(_ostream, "%s", _AST->nodeValue.identifier);
        default: return;
    }
}

void prettyPrintAssignStatement(nodeAST* _AST, FILE* _ostream){
    assert(isAssignment(_AST) == true);
    if (_AST == NULL) return;
    switch (_AST->nodeType) {
        case STATE_ASSIGN:{             // expr, ...., expr = expr, ..., expr
            prettyPrintExpr(_AST->nodeValue.assign.left, _ostream);
            fprintf(_ostream, " = ");
            prettyPrintExpr(_AST->nodeValue.assign.right, _ostream);
            return;
        }
        case STATE_ASSIGN_ADD:{         // expr += expr
            prettyPrintExpr(_AST->nodeValue.assignAdd.left, _ostream);
            fprintf(_ostream, " += ");
            prettyPrintExpr(_AST->nodeValue.assignAdd.right, _ostream);
            return;
        }
        case STATE_ASSIGN_SUB:{         // expr -= expr
            prettyPrintExpr(_AST->nodeValue.assignSub.left, _ostream);
            fprintf(_ostream, " -= ");
            prettyPrintExpr(_AST->nodeValue.assignSub.right, _ostream);
            return;
        }
        case STATE_ASSIGN_MUL:{         // expr *= expr
            prettyPrintExpr(_AST->nodeValue.assignMul.left, _ostream);
            fprintf(_ostream, " *= ");
            prettyPrintExpr(_AST->nodeValue.assignMul.right, _ostream);
            return;
        }
        case STATE_ASSIGN_DIV:{         // expr /= expr
            prettyPrintExpr(_AST->nodeValue.assignDiv.left, _ostream);
            fprintf(_ostream, " /= ");
            prettyPrintExpr(_AST->nodeValue.assignDiv.right, _ostream);
            return;
        }
        case STATE_ASSIGN_MOD:{         // expr %= expr
            prettyPrintExpr(_AST->nodeValue.assignMod.left, _ostream);
            fprintf(_ostream, " %%= ");
            prettyPrintExpr(_AST->nodeValue.assignMod.right, _ostream);
            return;
        }
        case STATE_ASSIGN_AND:{         // expr &= expr
            prettyPrintExpr(_AST->nodeValue.assignAnd.left, _ostream);
            fprintf(_ostream, " &= ");
            prettyPrintExpr(_AST->nodeValue.assignAnd.right, _ostream);
            return;
        }
        case STATE_ASSIGN_OR:{          // expr |= expr
            prettyPrintExpr(_AST->nodeValue.assignOr.left, _ostream);
            fprintf(_ostream, " |= ");
            prettyPrintExpr(_AST->nodeValue.assignOr.right, _ostream);
            return;
        }
        case STATE_ASSIGN_XOR:{         // expr ^= expr
            prettyPrintExpr(_AST->nodeValue.assignXor.left, _ostream);
            fprintf(_ostream, " ^= ");
            prettyPrintExpr(_AST->nodeValue.assignXor.right, _ostream);
            return;
        }
        case STATE_ASSIGN_SHIFTLEFT:{   // expr <<= expr
            prettyPrintExpr(_AST->nodeValue.assignShiftLeft.left, _ostream);
            fprintf(_ostream, " <<= ");
            prettyPrintExpr(_AST->nodeValue.assignShiftLeft.right, _ostream);
            return;
        }
        case STATE_ASSIGN_SHIFTRIGHT:{  // expr >>= expr
            prettyPrintExpr(_AST->nodeValue.assignShiftRight.left, _ostream);
            fprintf(_ostream, " >>= ");
            prettyPrintExpr(_AST->nodeValue.assignShiftRight.right, _ostream);
            return;
        }
        case STATE_ASSIGN_ANDNOT:{      // expr &^= expr
            prettyPrintExpr(_AST->nodeValue.assignAndNot.left, _ostream);
            fprintf(_ostream, " &^= ");
            prettyPrintExpr(_AST->nodeValue.assignAndNot.right, _ostream);
            return;
        }
        default: return;
    }
}
void prettyPrintStatement(nodeAST* _AST, FILE* _ostream){
    if (_AST == NULL) return;
    if (isAssignment(_AST) == true) {
        prettyPrintAssignStatement(_AST, _ostream);
        return;
    }
    if (isExpr(_AST) == true) {
        prettyPrintExpr(_AST, _ostream);
        return;
    }
    switch (_AST->nodeType) {
        case STATE_INC: {
            prettyPrintExpr(_AST->nodeValue.inc.expr, _ostream);
            fprintf(_ostream, " ++");
            return;
        }
        case STATE_DEC: {
            prettyPrintExpr(_AST->nodeValue.dec.expr, _ostream);
            fprintf(_ostream, " --");
            return;
        }
        case STATE_PRINT: {
            fprintf(_ostream, "print(");
            prettyPrintExpr(_AST->nodeValue.print.expr, _ostream);
            fprintf(_ostream, ")");
            return;
        }
        case STATE_PRINTLN: {
            fprintf(_ostream, "println(");
            prettyPrintExpr(_AST->nodeValue.println.expr, _ostream);
            fprintf(_ostream, ")");
            return;
        }
        case STATE_RETURN: {
            fprintf(_ostream, "return ");
            prettyPrintExpr(_AST->nodeValue.ret.expr, _ostream);
            return;
        }
        case STATE_CONTROL_BREAK: {
            fprintf(_ostream, "break");
            return;
        }
        case STATE_CONTROL_CONTINUE: {
            fprintf(_ostream, "continue");
            return;
        }
        case STATE_UTILITY_STATELIST: {
            nodeAST* current = _AST->nodeValue.stateList.state;
            nodeAST* next = _AST->nodeValue.stateList.next;
            if (current != NULL) {
                prettyPrintStatement(current, _ostream);
            }
            if (next != NULL) {
                fprintf(_ostream, "\n");
                prettyPrintStatement(next, _ostream);
            }
            return;
        }
        case STATE_IF: {
            nodeAST* condition = _AST->nodeValue.ifBlock.condition;
            fprintf(_ostream, "if ");
            if (condition->nodeValue.ifCondition.state != NULL) {
                prettyPrintStatement(condition->nodeValue.ifCondition.state, _ostream);
                fprintf(_ostream, "; ");
            }
            prettyPrintExpr(condition->nodeValue.ifCondition.expr, _ostream);
            fprintf(_ostream, " {\n");
            prettyPrintStatement(_AST->nodeValue.ifBlock.block_true, _ostream);
            fprintf(_ostream, "\n}");
            return;
        }
        case STATE_IF_ELSE: {
            nodeAST* condition = _AST->nodeValue.ifElseBlock.condition;
            fprintf(_ostream, "if ");
            if (condition->nodeValue.ifCondition.state != NULL) {
                prettyPrintStatement(condition->nodeValue.ifCondition.state, _ostream);
                fprintf(_ostream, "; ");
            }
            prettyPrintExpr(condition->nodeValue.ifCondition.expr, _ostream);
            fprintf(_ostream, " {\n");
            prettyPrintStatement(_AST->nodeValue.ifElseBlock.block_true, _ostream);
            fprintf(_ostream, "\n} else {\n");
            prettyPrintStatement(_AST->nodeValue.ifElseBlock.block_false, _ostream);
            fprintf(_ostream, "\n}");
            return;
        }
        case STATE_SWITCH:{
            nodeAST* condition = _AST->nodeValue.switchBlock.condition;
            fprintf(_ostream, "switch ");
            if (condition != NULL){
                if (condition->nodeValue.switchCondition.state != NULL) {
                    prettyPrintStatement(condition->nodeValue.switchCondition.state, _ostream);
                    fprintf(_ostream, "; ");
                }
                prettyPrintExpr(condition->nodeValue.switchCondition.expr, _ostream);
            }
            fprintf(_ostream, " {\n");
            if (_AST->nodeValue.switchBlock.block != NULL) {
                prettyPrintStatement(_AST->nodeValue.switchBlock.block, _ostream);
            }
            fprintf(_ostream, "\n}");
            return;
        }
        case STATE_UTILITY_CASE_CLAUSE: {
            nodeAST* caseNode = _AST->nodeValue.caseClause.expr;
            nodeAST* block = _AST->nodeValue.caseClause.state;
            if (caseNode == NULL) {
                fprintf(_ostream, "default");
            } else {
                fprintf(_ostream, "case ");
                prettyPrintExpr(caseNode, _ostream);
            }
            fprintf(_ostream, " : {\n");
            prettyPrintStatement(block, _ostream);
            fprintf(_ostream, "\n}");
            return;
        }
        case STATE_UTILITY_CASE_LIST: {
            nodeAST* current = _AST->nodeValue.caseList.state;
            nodeAST* next = _AST->nodeValue.caseList.next;
            prettyPrintStatement(current, _ostream);
            fprintf(_ostream, "\n");
            if (next != NULL) {
                prettyPrintStatement(next, _ostream);
            }
            return;
        }
        case STATE_FOR: {
            nodeAST* condition = _AST->nodeValue.forBlock.condition;
            fprintf(_ostream, "for ");
            if (condition != NULL){
                if (isExpr(condition)) {
                    prettyPrintExpr(condition, _ostream);
                } else {
                    if (condition->nodeValue.forClause.init != NULL) {
                        prettyPrintStatement(condition->nodeValue.forClause.init, _ostream);
                    }
                    fprintf(_ostream, "; ");
                    if (condition->nodeValue.forClause.condition != NULL) {
                        prettyPrintStatement(condition->nodeValue.forClause.condition, _ostream);
                    }
                    fprintf(_ostream, "; ");
                    if (condition->nodeValue.forClause.step != NULL) {
                        prettyPrintStatement(condition->nodeValue.forClause.step, _ostream);
                    }
                }
            }
            fprintf(_ostream, " {\n");
            if (_AST->nodeValue.forBlock.block != NULL) {
                prettyPrintStatement(_AST->nodeValue.forBlock.block, _ostream);
            }
            fprintf(_ostream, "\n}");
            return;
        }
        case PROG_DECLARE_VAR: {
            prettyPrintIdList(_AST->nodeValue.varDeclare.idList, _ostream);
            fprintf(_ostream, " ");
            prettyPrintType(_AST->nodeValue.varDeclare.type, _ostream);
            if (_AST->nodeValue.varDeclare.initExpr != NULL) {
                fprintf(_ostream, " = ");
                prettyPrintExpr(_AST->nodeValue.varDeclare.initExpr, _ostream);
            }
            return;
        }
        case PROG_DECLARE_VAR_LIST: {
            fprintf(_ostream, "var ");
            prettyPrintStatement(_AST->nodeValue.varDeclareList.varDeclare, _ostream);
            //fprintf(_ostream, "\n");
            prettyPrintStatement(_AST->nodeValue.varDeclareList.next, _ostream);
            return;
        }
        case RROG_DECLARE_TYPE: {
            prettyPrintExpr(_AST->nodeValue.typeDeclare.identifier, _ostream);
            fprintf(_ostream, " ");
            prettyPrintType(_AST->nodeValue.typeDeclare.type, _ostream);
            return;
        }
        case PROG_DECLARE_TYPE_LIST: {
            fprintf(_ostream, "type ");
            prettyPrintStatement(_AST->nodeValue.typeDeclareList.typeDeclare, _ostream);
            //fprintf(_ostream, "\n");
            prettyPrintStatement(_AST->nodeValue.typeDeclareList.next, _ostream);
            return;
        }
        case STATE_SHORT_DECLARE: {
            prettyPrintExpr(_AST->nodeValue.shortDeclare.left, _ostream);
            fprintf(_ostream, " := ");
            prettyPrintExpr(_AST->nodeValue.shortDeclare.right, _ostream);
            return;
        }
        default: return;
    }
}

void prettyPrint(nodeAST* _AST, FILE* _ostream){
    if (_AST == NULL) return;
    switch (_AST->nodeType) {
        case PROG_PACKAGE: {
            fprintf(_ostream, "package ");
            prettyPrintExpr(_AST->nodeValue.package.identifier, _ostream);
            return;
        }
        case PROG_PROGRAM: {
            prettyPrint(_AST->nodeValue.program.package, _ostream);
            fprintf(_ostream, "\n");
            prettyPrint(_AST->nodeValue.program.program, _ostream);
            return;
        }
        case PROG_LIST: {
            prettyPrint(_AST->nodeValue.progList.prog, _ostream);
            fprintf(_ostream, "\n");
            prettyPrint(_AST->nodeValue.progList.next, _ostream);
            return;
        }
        case PROG_FUNCTION:{
            fprintf(_ostream, "func ");
            prettyPrintExpr(_AST->nodeValue.function.identifier, _ostream);
            fprintf(_ostream, "(");
            prettyPrint(_AST->nodeValue.function.pramList, _ostream);
            fprintf(_ostream, ") ");
            prettyPrintType(_AST->nodeValue.function.type, _ostream);
            fprintf(_ostream, "{\n");
            prettyPrintStatement(_AST->nodeValue.function.block, _ostream);
            fprintf(_ostream, "\n}");
            return;
        }
        case PROG_DECLARE_VAR_LIST: prettyPrintStatement(_AST, _ostream); return;
        case PROG_DECLARE_TYPE_LIST: prettyPrintStatement(_AST, _ostream); return;
        case PROG_PRAM_DEC:{
            prettyPrintExpr(_AST->nodeValue.pramDeclare.idList, _ostream);
            fprintf(_ostream, " ");
            prettyPrintType(_AST->nodeValue.pramDeclare.type, _ostream);
            return;
        }
        case PROG_PRAM_DEC_LIST:{
            prettyPrint(_AST->nodeValue.pramDeclareList.pram, _ostream);
            if (_AST->nodeValue.pramDeclareList.next!=NULL) {
                fprintf(_ostream, ",");
                prettyPrint(_AST->nodeValue.pramDeclareList.next, _ostream);
            }
            return;
        }
        default:
            break;
    }
}
#endif
