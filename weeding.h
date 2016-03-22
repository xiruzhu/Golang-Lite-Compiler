#ifndef __GoLiteCompiler__WEEDING__H__
#define __GoLiteCompiler__WEEDING__H__

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "treeNode.h"

extern void yyerror(const char*);

bool weedingFunctionReturned(nodeAST* _funcNode) {
    if (_funcNode == NULL) return false;
    switch (_funcNode->nodeType) {
    case STATE_INC:     return false;
    case STATE_DEC:     return false;
    case STATE_PRINT:   return false;
    case STATE_PRINTLN: return false;
    case STATE_RETURN:  return true;
    case STATE_CONTROL_BREAK:    return false;
    case STATE_CONTROL_CONTINUE: return false;
    case STATE_UTILITY_STATELIST: {
	nodeAST* current = _funcNode->nodeValue.stateList.state;
	nodeAST* next    = _funcNode->nodeValue.stateList.next;
	if (current->nodeType == STATE_CONTROL_BREAK) return false;;
	if (current->nodeType == STATE_CONTROL_CONTINUE) return false;
	return weedingFunctionReturned(current) ||
	    weedingFunctionReturned(next);
    }
    case STATE_IF: return _funcNode->nodeValue.ifBlock.block_true;
    case STATE_IF_ELSE:
	return _funcNode->nodeValue.ifElseBlock.block_true &&
	    _funcNode->nodeValue.ifElseBlock.block_false;
    case STATE_SWITCH:
	return weedingFunctionReturned(_funcNode->nodeValue.switchBlock.block);
    case STATE_UTILITY_CASE_CLAUSE:
	return weedingFunctionReturned(_funcNode->nodeValue.caseClause.state);
    case STATE_UTILITY_CASE_LIST: {
	nodeAST* ptr = _funcNode;
	while (ptr != NULL) {
	    if (!weedingFunctionReturned(ptr->nodeValue.stateList.state)) {
		return false;
	    }
	    ptr = ptr->nodeValue.stateList.next;
	}
	return true;
    }
    case STATE_FOR:
	return weedingFunctionReturned(_funcNode->nodeValue.forBlock.block);
    case PROG_DECLARE_VAR: return false;
    case PROG_DECLARE_VAR_LIST: return false;
    case RROG_DECLARE_TYPE: return false;
    case PROG_DECLARE_TYPE_LIST: return false;
    case STATE_SHORT_DECLARE: return false;
    default: return false;
    }
}
void weedingFunction(nodeAST* _prog){
    if (_prog==NULL) return;
    switch (_prog->nodeType) {
    case PROG_PACKAGE: return;
    case PROG_PROGRAM: {weedingFunction(_prog->nodeValue.program.program); return;}
    case PROG_LIST: {
	weedingFunction(_prog->nodeValue.progList.prog);
	weedingFunction(_prog->nodeValue.progList.next);
	return;
    }
    case PROG_FUNCTION: {
	if (_prog->nodeValue.function.type == NULL) return;
        if (!weedingFunctionReturned(_prog->nodeValue.function.block)) {
	    yyerror("missing return at end of function");
	    return;
	}
	return;
    }
    case PROG_DECLARE_VAR_LIST: return;
    case PROG_DECLARE_TYPE_LIST: return;
    case PROG_PRAM_DEC_LIST: return;
    default: return;
    }
}

size_t lenExprList(nodeAST* _exprList) {
    assert(_exprList != NULL);
    assert(_exprList->nodeType == EXPR_UTILITY_EXPRLIST);
    size_t length = 0L;
    nodeAST* ptr = _exprList;
    while (ptr != NULL) {
	length++;
	ptr = ptr->nodeValue.exprList.next;
    }
    return length;
}
size_t lenIdList(nodeAST* _idList) {
    assert(_idList != NULL);
    assert(_idList->nodeType == IDENTIFIER_LIST);
    size_t length = 0L;
    nodeAST* ptr = _idList;
    while (ptr != NULL) {
	length++;
	ptr = ptr->nodeValue.identifierList.next;
    }
    return length;
}

void weedingExpr(nodeAST* _ASTExpr) {
    if (_ASTExpr == NULL) return;
    switch (_ASTExpr->nodeType) {
    case LITERAL_INT:               {return;}
    case LITERAL_FLOAT:             {return;}
    case LITERAL_RUNE:              {return;}
    case LITERAL_STRING:            {
	GO_IMPLEMENT_STRING stringLiteral = _ASTExpr->nodeValue.stringValue;
	size_t length = GO_IMPLEMENT_STRING_LEN(stringLiteral);
	for (size_t iter = 0; iter < length-1; iter++) {
	    GO_IMPLEMENT_RUNE runeChar = stringLiteral[iter];
	    if (runeChar == '\\') {
		GO_IMPLEMENT_RUNE nextChar = stringLiteral[iter+1];
		switch (nextChar) {
		    // @https://en.wikipedia.org/wiki/Escape_character
		case '\'':         return;  // single quote
		case '\"':         return;  // double quote
		case '\\':         return;  // backslash
		case 'n':          return;  // new line
		case 'r':          return;  // carriage return
		case 't':          return;  // tab
		case 'b':          return;  // backspace
		case 'f':          return;  // form feed
		case 'v':          return;  // vertical tab
		case '0':          return;  // null character
		default: {
		    yyerror("invalid escape character");
		    return;
		}
		}
	    }
	}
	return;
    }
    case IDENTIFIER:                {
	if (strcmp(_ASTExpr->nodeValue.identifier, "_") == 0) {
	    yyerror("blank identifier can not be used during evaluation");
	    return;
	}
	return;
    }
    case IDENTIFIER_LIST:           {
	weedingExpr(_ASTExpr->nodeValue.identifierList.identifier);
	weedingExpr(_ASTExpr->nodeValue.identifierList.next);
	return;
    }
    case EXPR_BINARY_OP_EQUAL:      {
	weedingExpr(_ASTExpr->nodeValue.equal.left);
	weedingExpr(_ASTExpr->nodeValue.equal.right);
	return;
    }
    case EXPR_BINARY_OP_NEQUAL:     {
	weedingExpr(_ASTExpr->nodeValue.nequal.left);
	weedingExpr(_ASTExpr->nodeValue.nequal.right);
    }
    case EXPR_BINARY_OP_LESS:       {
	weedingExpr(_ASTExpr->nodeValue.less.left);
	weedingExpr(_ASTExpr->nodeValue.less.right);
	return;
    }
    case EXPR_BINARY_OP_LESSEQUAL:  {
	weedingExpr(_ASTExpr->nodeValue.lessEqual.left);
	weedingExpr(_ASTExpr->nodeValue.lessEqual.right);
	return;
    }
    case EXPR_BINARY_OP_GREAT:      {
	weedingExpr(_ASTExpr->nodeValue.great.left);
	weedingExpr(_ASTExpr->nodeValue.great.right);
	return;
    }
    case EXPR_BINARY_OP_GREATEQUAL: {
	weedingExpr(_ASTExpr->nodeValue.greatEqual.left);
	weedingExpr(_ASTExpr->nodeValue.greatEqual.right);
	return;
    }
    case EXPR_BINARY_OP_ADD:        {
	weedingExpr(_ASTExpr->nodeValue.add.left);
	weedingExpr(_ASTExpr->nodeValue.add.right);
	return;
    }
    case EXPR_BINARY_OP_SUB:        {
	weedingExpr(_ASTExpr->nodeValue.sub.left);
	weedingExpr(_ASTExpr->nodeValue.sub.right);
	return;
    }
    case EXPR_BINARY_OP_MUL:        {
	weedingExpr(_ASTExpr->nodeValue.mul.left);
	weedingExpr(_ASTExpr->nodeValue.mul.right);
	return;
    }
    case EXPR_BINARY_OP_DIV:        {
	weedingExpr(_ASTExpr->nodeValue.div.left);
	weedingExpr(_ASTExpr->nodeValue.div.right);
	return;
    }
    case EXPR_BINARY_OP_MOD:        {
	weedingExpr(_ASTExpr->nodeValue.mod.left);
	weedingExpr(_ASTExpr->nodeValue.mod.right);
	return;
    }
    case EXPR_BINARY_OP_LSHIFT:     {
	weedingExpr(_ASTExpr->nodeValue.shiftLeft.left);
	weedingExpr(_ASTExpr->nodeValue.shiftLeft.right);
	return;
    }
    case EXPR_BINARY_OP_RSHIFT:     {
	weedingExpr(_ASTExpr->nodeValue.shiftRight.left);
	weedingExpr(_ASTExpr->nodeValue.shiftRight.right);
	return;
    }
    case EXPR_BINARY_OP_AND:        {
	weedingExpr(_ASTExpr->nodeValue.bitAnd.left);
	weedingExpr(_ASTExpr->nodeValue.bitAnd.right);
	return;
    }
    case EXPR_BINARY_OP_OR:         {
	weedingExpr(_ASTExpr->nodeValue.bitOr.left);
	weedingExpr(_ASTExpr->nodeValue.bitOr.right);
	return;
    }
    case EXPR_BINARY_OP_XOR:        {
	weedingExpr(_ASTExpr->nodeValue.bitXor.left);
	weedingExpr(_ASTExpr->nodeValue.bitXor.right);
	return;
    }
    case EXPR_BINARY_OP_ANDNOT:     {
	weedingExpr(_ASTExpr->nodeValue.bitAndNot.left);
	weedingExpr(_ASTExpr->nodeValue.bitAndNot.right);
	return;
    }
    case EXPR_BINARY_OP_LOGIC_AND:  {
	weedingExpr(_ASTExpr->nodeValue.logicAnd.left);
	weedingExpr(_ASTExpr->nodeValue.logicAnd.right);
	return;
    }
    case EXPR_BINARY_OP_LOGIC_OR:   {
	weedingExpr(_ASTExpr->nodeValue.logicOr.left);
	weedingExpr(_ASTExpr->nodeValue.logicOr.right);
	return;
    }
    case EXPR_UNIARY_OP_LOGIC_NOT:  {
	weedingExpr(_ASTExpr->nodeValue.logicNot.expr);
	return;
    }
    case EXPR_UNIARY_OP_NEG:        {
	weedingExpr(_ASTExpr->nodeValue.neg.expr);
	return;
    }
    case EXPR_UNIARY_OP_NOT:        {
	weedingExpr(_ASTExpr->nodeValue.logicNot.expr);
	return;
    }
    case EXPR_UNIARY_OP_POS:        {
	weedingExpr(_ASTExpr->nodeValue.pos.expr);
	return;
    }
    case EXPR_APPEND:               {
	weedingExpr(_ASTExpr->nodeValue.append.target);
	weedingExpr(_ASTExpr->nodeValue.append.expr);
	return;
    }
    case EXPR_FUNC_CALL:            {
	nodeAST* target = _ASTExpr->nodeValue.funcCall.target;
	if (target->nodeType != IDENTIFIER) {
	    yyerror("identifier expected, funcall failed");
	    return;
	}
	weedingExpr(_ASTExpr->nodeValue.funcCall.expr);
	return;
    }
    case EXPR_CAST:                 {
	weedingExpr(_ASTExpr->nodeValue.cast.expr);
	return;
    }
    case EXPR_SELECTOR:             {
	weedingExpr(_ASTExpr->nodeValue.selector.target);
	weedingExpr(_ASTExpr->nodeValue.selector.entry);
	return;
    }
    case EXPR_INDEX:                {
	weedingExpr(_ASTExpr->nodeValue.index.target);
	weedingExpr(_ASTExpr->nodeValue.index.entry);
	return;
    }
    case EXPR_SLICE:                {
	weedingExpr(_ASTExpr->nodeValue.slice.target);
	weedingExpr(_ASTExpr->nodeValue.slice.entry);
	return;
    }
    case EXPR_ADDRESS_SLICE:        {
	weedingExpr(_ASTExpr->nodeValue.addressSlice.start);
	weedingExpr(_ASTExpr->nodeValue.addressSlice.end);
	return;
    }
    case EXPR_ADDRESS_SLICE_FULL:   {
	weedingExpr(_ASTExpr->nodeValue.addressSliceFull.start);
	weedingExpr(_ASTExpr->nodeValue.addressSliceFull.end);
	weedingExpr(_ASTExpr->nodeValue.addressSliceFull.max);
	return;
    }
    case EXPR_UTILITY_EXPRLIST:     {
	weedingExpr(_ASTExpr->nodeValue.exprList.expr);
	weedingExpr(_ASTExpr->nodeValue.exprList.next);
	return;
    }
    default:                         return;
    }
}

bool weedingAssignableExpr(nodeAST* _AST) {
    if (_AST == NULL) return false;
    switch (_AST->nodeType) {
    case IDENTIFIER:    return true;  // id        = expr
    case EXPR_INDEX:    return true;  // id[index] = expr
    case EXPR_SELECTOR: return true;  // id.entry  = expr
    case EXPR_SLICE:    return true;  // id[]      = expr
    default:            return false; //
    }
    return false;
}

bool weedingAssignableExprList(nodeAST* _AST) {
    assert(_AST != NULL);
    assert(_AST->nodeType == EXPR_UTILITY_EXPRLIST);
    nodeAST* ptr = _AST;
    while (ptr != NULL) {
	if (!weedingAssignableExpr(ptr->nodeValue.exprList.expr)) return false;
	ptr = ptr->nodeValue.exprList.next;
    }
    return true;
}

void weedingAssign(nodeAST* _AST) {
    if (_AST == NULL) return;
    switch (_AST->nodeType) {
    case STATE_ASSIGN:              {
	size_t lenLeftExpr  = lenExprList(_AST->nodeValue.assign.left);
	size_t lenRightExpr = lenExprList(_AST->nodeValue.assign.right);
	if (lenLeftExpr != lenRightExpr) {
	    yyerror("Assign Expr, left length and right length miss matched");
	    return;
	}
	if (!weedingAssignableExprList(_AST->nodeValue.assign.left)) {
	    yyerror("Assign Expr, left part not assignable");
	    return;
	}
	return;
    }
    case STATE_ASSIGN_ADD:          {
	if (!weedingAssignableExpr(_AST->nodeValue.assignAdd.left)) {
	    yyerror("Assign Expr, left part not assignable");
	    return;
	}
	return;
    }
    case STATE_ASSIGN_SUB:          {
	if (!weedingAssignableExpr(_AST->nodeValue.assignSub.left)) {
	    yyerror("Assign Expr, left part not assignable");
	    return;
	}
	return;
    }
    case STATE_ASSIGN_MUL:          {
	if (!weedingAssignableExpr(_AST->nodeValue.assignMul.left)) {
	    yyerror("Assign Expr, left part not assignable");
	    return;
	}
	return;
    }
    case STATE_ASSIGN_DIV:          {
	if (!weedingAssignableExpr(_AST->nodeValue.assignDiv.left)) {
	    yyerror("Assign Expr, left part not assignable");
	    return;
	}
	return;
    }
    case STATE_ASSIGN_MOD:          {
    	if (!weedingAssignableExpr(_AST->nodeValue.assignMod.left)) {
	    yyerror("Assign Expr, left part not assignable");
	    return;
	}
	return;
    }
    case STATE_ASSIGN_AND:          {
	if (!weedingAssignableExpr(_AST->nodeValue.assignAnd.left)) {
	    yyerror("Assign Expr, left part not assignable");
	    return;
	}
	return;
    }
    case STATE_ASSIGN_OR:           {
    	if (!weedingAssignableExpr(_AST->nodeValue.assignOr.left)) {
	    yyerror("Assign Expr, left part not assignable");
	    return;
	}
	return;
    }
    case STATE_ASSIGN_XOR:          {
	if (!weedingAssignableExpr(_AST->nodeValue.assignXor.left)) {
	    yyerror("Assign Expr, left part not assignable");
	    return;
	}
	return;
    }
    case STATE_ASSIGN_SHIFTLEFT:    {
	if (!weedingAssignableExpr(_AST->nodeValue.assignShiftLeft.left)) {
	    yyerror("Assign Expr, left part not assignable");
	    return;
	}
	return;
    }
    case STATE_ASSIGN_SHIFTRIGHT:   {
	if (!weedingAssignableExpr(_AST->nodeValue.assignShiftRight.left)) {
	    yyerror("Assign Expr, left part not assignable");
	    return;
	}
	return;
    }
    case STATE_ASSIGN_ANDNOT:       {
	if (!weedingAssignableExpr(_AST->nodeValue.assignAndNot.left)) {
	    yyerror("Assign Expr, left part not assignable");
	    return;
	}
	return;
    }
    default: return;
    }
}

typedef struct weedingEnvironment{
    bool FLAG_FOR;
    bool FLAG_SWITCH;
    bool FLAG_IF;
} weedingEnvironment;
void weedingStatement(nodeAST* _state, weedingEnvironment _env) {
    if (_state == NULL) return;
    switch (_state->nodeType) {
    case STATE_INC:     weedingExpr(_state->nodeValue.inc.expr); return;
    case STATE_DEC:     weedingExpr(_state->nodeValue.dec.expr); return;
    case STATE_PRINT:   weedingExpr(_state->nodeValue.print.expr); return;
    case STATE_PRINTLN: weedingExpr(_state->nodeValue.println.expr); return;
    case STATE_RETURN:  weedingExpr(_state->nodeValue.ret.expr); return;
    case STATE_ASSIGN:
    case STATE_ASSIGN_ADD:
    case STATE_ASSIGN_SUB:
    case STATE_ASSIGN_MUL:
    case STATE_ASSIGN_DIV:
    case STATE_ASSIGN_MOD:
    case STATE_ASSIGN_AND:
    case STATE_ASSIGN_OR:
    case STATE_ASSIGN_XOR:
    case STATE_ASSIGN_SHIFTLEFT:
    case STATE_ASSIGN_SHIFTRIGHT:
    case STATE_ASSIGN_ANDNOT: {
	weedingAssign(_state);
	return;
    }
    case STATE_CONTROL_BREAK: {
	if (!(_env.FLAG_FOR || _env.FLAG_SWITCH)) {
	    yyerror("break is not in a loop");
	    return;
	}
	return;
    }
    case STATE_CONTROL_CONTINUE: {
	if (!_env.FLAG_FOR) {
	    yyerror("continue is not in a loop");
	    return;
	}
	return;
    }
    case STATE_UTILITY_STATELIST: {
	nodeAST* ptr = _state;
	while (ptr != NULL) {
	    weedingStatement(ptr->nodeValue.stateList.state, _env);
	    ptr = ptr->nodeValue.stateList.next;
	}
	return;
    }
    case STATE_IF: {
	nodeAST* condition = _state->nodeValue.ifBlock.condition;
	switch (condition->nodeValue.ifCondition.state->nodeType) {
	case STATE_CONTROL_BREAK: {
	    yyerror("unexpected break, expecting expression");
	    return;
	}
	case STATE_CONTROL_CONTINUE: {
	    yyerror("unexpected continue, expecting expression");
	    return;
	}
	default: {
	    weedingStatement(condition->nodeValue.ifCondition.state, _env);
	    weedingExpr(condition->nodeValue.ifCondition.expr);
	    weedingEnvironment newFrame = _env;
	    newFrame.FLAG_IF = true;
	    weedingStatement(_state->nodeValue.ifBlock.block_true, newFrame);
	    return;
	}
	}
    }
    case STATE_IF_ELSE: {
	nodeAST* condition = _state->nodeValue.ifElseBlock.condition;
	switch (condition->nodeValue.ifCondition.state->nodeType) {
	case STATE_CONTROL_BREAK: {
	    yyerror("unexpected break, expecting expression");
	    return;
	}
	case STATE_CONTROL_CONTINUE: {
	    yyerror("unexpected continue, expecting expression");
	    return;
	}
	default: {
	    weedingStatement(condition->nodeValue.ifCondition.state, _env);
	    weedingExpr(condition->nodeValue.ifCondition.expr);
	    weedingEnvironment newFrame = _env;
	    newFrame.FLAG_IF = true;
	    weedingStatement(_state->nodeValue.ifElseBlock.block_true, newFrame);
	    weedingStatement(_state->nodeValue.ifElseBlock.block_false, newFrame);
	    return;
	}
	}
    }
    case STATE_SWITCH : {
	nodeAST* condition = _state->nodeValue.switchBlock.condition;
	switch (condition->nodeValue.switchBlock.condition->nodeType) {
	case STATE_CONTROL_BREAK: {
	    yyerror("unexpected break, expecting expression");
	    return;
	}
	case STATE_CONTROL_CONTINUE: {
	    yyerror("unexpected continue, expecting expression");
	    return;
	}
	default: {
	    weedingStatement(condition->nodeValue.switchCondition.state, _env);
	    weedingExpr(condition->nodeValue.switchCondition.expr);
	    weedingEnvironment newFrame = _env;
	    newFrame.FLAG_SWITCH = true;
	    weedingStatement(_state->nodeValue.switchBlock.block, newFrame);
	    return;
	}
	}
    }
    case STATE_UTILITY_CASE_CLAUSE: {
	weedingExpr(_state->nodeValue.caseClause.expr);
	weedingStatement(_state->nodeValue.caseClause.state, _env);
	return;
    }
    case STATE_UTILITY_CASE_LIST: {
	nodeAST* ptr = _state;
	bool defaultExist = false;
	while (ptr != NULL) {
	    nodeAST* clause = ptr->nodeValue.caseList.state;
	    if (clause->nodeValue.caseClause.expr == NULL) {
		if (defaultExist) {
		    yyerror("multiple defaults in switch");
		    return;
		}
		defaultExist = true;
	    }
	    weedingStatement(clause, _env);
	    ptr = ptr->nodeValue.caseList.next;
	}
	return;
    }
    case STATE_FOR: {
	nodeAST* condition = _state->nodeValue.forBlock.condition;
	if (condition->nodeValue.forClause.init->nodeType == STATE_CONTROL_BREAK) {
	    yyerror("unexpected break, expecting expression");
	    return;
	}
	if (condition->nodeValue.forClause.step->nodeType == STATE_CONTROL_BREAK) {
	    yyerror("unexpected break, expecting expression");
	    return;
	}
	if (condition->nodeValue.forClause.init->nodeType ==
	    STATE_CONTROL_CONTINUE) {
	    yyerror("unexpected continue, expecting expression");
	    return;
	}
	if (condition->nodeValue.forClause.step->nodeType ==
	    STATE_CONTROL_CONTINUE) {
	    yyerror("unexpected continue, expecting expression");
	    return;
	}
	weedingStatement(condition->nodeValue.forClause.init, _env);
	weedingExpr(condition->nodeValue.forClause.condition);
	weedingStatement(condition->nodeValue.forClause.step, _env);
	weedingEnvironment newFrame = _env;
	newFrame.FLAG_FOR = true;
	weedingStatement(_state->nodeValue.forBlock.block, newFrame);
	return;
    }
    case PROG_DECLARE_VAR: {
	size_t idLength = lenIdList(_state->nodeValue.varDeclare.idList);
	size_t exprLength = 0L;
	if (_state->nodeValue.varDeclare.initExpr == NULL) {
	    exprLength = idLength;
	} else {
	    exprLength = lenExprList(_state->nodeValue.varDeclare.initExpr);
	}
	if (idLength != exprLength) {
	    yyerror("assignment count mismatch");
	    return;
	}
	weedingExpr(_state->nodeValue.varDeclare.initExpr);
	return;
    }
    case PROG_DECLARE_VAR_LIST: {
	weedingStatement(_state->nodeValue.varDeclareList.varDeclare, _env);
	weedingStatement(_state->nodeValue.varDeclareList.next, _env);
	return;
    }
    case RROG_DECLARE_TYPE: return;
    case PROG_DECLARE_TYPE_LIST: return;
    case STATE_SHORT_DECLARE: {
	size_t idLength = lenExprList(_state->nodeValue.shortDeclare.left);
	size_t exprLength = lenExprList(_state->nodeValue.shortDeclare.right);
	if (idLength != exprLength) {
	    yyerror("assignment count mismatch");
	    return;
	}
	nodeAST* ptr = _state->nodeValue.shortDeclare.left;
	while (ptr != NULL) {
	    if (ptr->nodeValue.exprList.expr->nodeType != IDENTIFIER) {
		yyerror("non-name on left side of :=");
		return;
	    }
	    ptr = ptr->nodeValue.exprList.next;
	}
	weedingExpr(_state->nodeValue.shortDeclare.right);
	return;
    }
    default: return;
    }
}

void weedingInit(nodeAST* _program) {
    if (_program == NULL) return;
    weedingEnvironment initEnv;
    initEnv.FLAG_FOR = false;
    initEnv.FLAG_SWITCH = false;
    initEnv.FLAG_IF = false;
    switch (_program->nodeType) {
    case PROG_PACKAGE: return;
    case PROG_PROGRAM: {weedingInit(_program->nodeValue.program.program); return;}
    case PROG_LIST: {
	weedingInit(_program->nodeValue.progList.prog);
	weedingInit(_program->nodeValue.progList.next);
	return;
    }
    case PROG_FUNCTION: {
	if (_program->nodeValue.function.type != NULL) {
	    if (!weedingFunctionReturned(_program->nodeValue.function.block)) {
		yyerror("missing return at end of function");
		return;
	    }
	}
	weedingStatement(_program->nodeValue.function.block, initEnv);
	weedingInit(_program->nodeValue.function.pramList);
    }
    case PROG_DECLARE_VAR_LIST: weedingStatement(_program,initEnv); return;
    case PROG_DECLARE_TYPE_LIST: weedingStatement(_program, initEnv); return;
    case PROG_PRAM_DEC: return;
    case PROG_PRAM_DEC_LIST: return;
    default: break;
    }
}

#endif
