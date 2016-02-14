#ifndef __GoLiteCompiler__TREENODE__H__
#define __GoLiteCompiler__TREENODE__H__

#include "memory.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

extern void _func_throwError(const char*);
extern size_t _AST_LineNumber;

#define TREENODE_ERROR_MALLOC   "Malloc Error"

#define GO_IMPLEMENT_INT		int
#define GO_IMPLEMENT_FLOAT64	double
#define GO_IMPLEMENT_RUNE		char
#define GO_IMPLEMENT_STRING     GO_IMPLEMENT_RUNE*
#define GO_IMPLEMENT_BOOL       bool

size_t GO_IMPLEMENT_STRING_LEN(GO_IMPLEMENT_STRING _str) {return strlen(_str);}
GO_IMPLEMENT_STRING GO_IMPLEMENT_STRING_CPY(GO_IMPLEMENT_STRING _str, memoryList _allocator){
    size_t allocateSize = GO_IMPLEMENT_STRING_LEN(_str) + 1;
    GO_IMPLEMENT_STRING newStr = (GO_IMPLEMENT_STRING)
                                 mallocList(sizeof(GO_IMPLEMENT_RUNE)*allocateSize, _allocator);
    memset(newStr, '\0', sizeof(GO_IMPLEMENT_RUNE)*(allocateSize - 1));
    strcpy(newStr, _str);
    return newStr;
}

typedef struct{size_t capacity;size_t type;void* sliceV[];} GO_IMPLEMENT_SLICE;
typedef struct{size_t capacity;size_t type;void* arrayV[];} GO_IMPLEMENT_ARRAY;
typedef struct {
    size_t capacity;
    struct {size_t type; void* dataPtr;} structV[];
} GO_IMPLEMENT_STRUCT;

typedef enum {
	VAR_INT,                                // GO_IMPLEMENT_INT
	VAR_FLOAT64,                            // GO_IMPLEMENT_FLOAT64
	VAR_BOOL,                               // GO_IMPLEMENT_BOOL
	VAR_RUNE,                               // GO_IMPLEMENT_RUNE
	VAR_STRING,                             // GO_IMPLEMENT_STRING
	VAR_SLICE,                              // GO_IMPLEMENT_SLICE
	VAR_ARRAY,                              // GO_IMPLEMENT_ARRAY
	VAR_STRUCT,                             // GO_IMPLEMENT_STRUCT
} varTypes;

typedef struct nodeAST {
	size_t lineNumber;
	enum {
		NODE_INIT,							// Exception upon future encounter
	
		LITERAL_INT,
		LITERAL_FLOAT,						
		LITERAL_RUNE,
		LITERAL_STRING,
		IDENTIFIER,
        BASIC_TYPE,
	
		EXPR_BINARY_OP_EQUAL,				// expr == expr
		EXPR_BINARY_OP_NEQUAL,				// expr != expr
		EXPR_BINARY_OP_LESS,				// expr < expr
		EXPR_BINARY_OP_LESSEQUAL,			// expr <= expr
		EXPR_BINARY_OP_GREAT,				// expr > expr
		EXPR_BINARY_OP_GREATEQUAL,			// expr >= expr
	
		EXPR_BINARY_OP_ADD,					// expr + expr
		EXPR_BINARY_OP_SUB,					// expr - expr
		EXPR_BINARY_OP_MUL,					// expr * expr
		EXPR_BINARY_OP_DIV,					// expr / expr
		EXPR_BINARY_OP_MOD,					// expr % expr

		EXPR_BINARY_OP_AND,					// expr & expr		(bitwise)
		EXPR_BINARY_OP_OR,					// expr | expr 		(bitwise)
		EXPR_BINARY_OP_XOR,					// expr ^ expr		(bitwise)
		EXPR_BINARY_OP_ANDNOT,				// expr &^ expr		(bitwise)
	
		EXPR_BINARY_OP_LSHIFT,				// expr << expr
		EXPR_BINARY_OP_RSHIFT,				// expr >> expr
	
		EXPR_BINARY_OP_LOGIC_AND,			// expr && expr		(logical)
		EXPR_BINARY_OP_LOGIC_OR,			// expr || expr		(logical)

        EXPR_UNIARY_OP_LOGIC_NOT,			// ! expr			(logical)
		EXPR_UNIARY_OP_POS,					// + expr
		EXPR_UNIARY_OP_NEG,					// - expr	
		EXPR_UNIARY_OP_NOT,					// ^ expr 			(bitwise)
	
		EXPR_APPEND,						// append ( indentifier, expr )
		EXPR_FUNC_CALL,						// expr ( [expr_list] )
		EXPR_CAST,							// type ( expr ) 	TODO: weeding
	
		EXPR_SELECTOR,						// expr EXPR_ADDRESS_SELECTOR
		EXPR_INDEX,							// expr EXPR_ADDERSS_INDEX 
		EXPR_SLICE,							// expr EXPR_ADDRESS_SLICE
                                            // expr EXPR_ADDRESS_SLICE_FULL
	
		EXPR_ADDRESS_SLICE,					// [ expr : expr ]
		EXPR_ADDRESS_SLICE_FULL,			// [ expr : expr : expr ]
        
        EXPR_UTILITY_EXPRLIST               // expr, ... , expr
	} nodeType;
	union {
		GO_IMPLEMENT_INT		intValue;
		GO_IMPLEMENT_FLOAT64	floatValue;
		GO_IMPLEMENT_RUNE		runeValue;
		GO_IMPLEMENT_STRING     stringValue;
        char*                   identifier;
        enum basicType{
            BASIC_INT,
            BASIC_FLOAT,
            BASIC_RUNE,
            BASIC_STRING,
            BASIC_BOOL
        } basicType;
        
        struct {struct nodeAST* left; struct nodeAST* right;} equal;
        struct {struct nodeAST* left; struct nodeAST* right;} nequal;
        struct {struct nodeAST* left; struct nodeAST* right;} less;
        struct {struct nodeAST* left; struct nodeAST* right;} lessEqual;
        struct {struct nodeAST* left; struct nodeAST* right;} great;
        struct {struct nodeAST* left; struct nodeAST* right;} greatEqual;
        
        struct {struct nodeAST* left; struct nodeAST* right;} add;
        struct {struct nodeAST* left; struct nodeAST* right;} sub;
        struct {struct nodeAST* left; struct nodeAST* right;} mul;
        struct {struct nodeAST* left; struct nodeAST* right;} div;
        struct {struct nodeAST* left; struct nodeAST* right;} mod;
        
        struct {struct nodeAST* left; struct nodeAST* right;} bitAnd;
        struct {struct nodeAST* left; struct nodeAST* right;} bitOr;
        struct {struct nodeAST* left; struct nodeAST* right;} bitXor;
        struct {struct nodeAST* left; struct nodeAST* right;} bitAndNot;
        struct {struct nodeAST* expr;} bitNot;
        
        struct {struct nodeAST* left; struct nodeAST* right;} shiftLeft;
        struct {struct nodeAST* left; struct nodeAST* right;} shiftRight;
        
        struct {struct nodeAST* left; struct nodeAST* right;} logicAnd;
        struct {struct nodeAST* left; struct nodeAST* right;} logicOr;
        struct {struct nodeAST* expr;} logicNot;
        
        struct {struct nodeAST* expr;} pos;
        struct {struct nodeAST* expr;} neg;
        
        struct {struct nodeAST* target; struct nodeAST* expr;} append;
        struct {struct nodeAST* target; struct nodeAST* expr;} funcCall;
        struct {struct nodeAST* target; struct nodeAST* expr;} cast;
        
        struct {struct nodeAST* target; struct nodeAST* entry;} selector;
        struct {struct nodeAST* target; struct nodeAST* entry;} index;
        struct {struct nodeAST* target; struct nodeAST* entry;} slice;
        
        struct {struct nodeAST* start; struct nodeAST* end;} addressSlice;
        struct {struct nodeAST* start; struct nodeAST* end; struct nodeAST* max;} addressSliceFull;
        
        struct {struct nodeAST* expr; struct nodeAST* next;} exprList;
    } nodeValue;
} nodeAST;

nodeAST* allocateNode(memoryList _allocator){
    nodeAST* returnNode = (nodeAST*)mallocList(sizeof(nodeAST), _allocator);
    if (returnNode == NULL) _func_throwError(TREENODE_ERROR_MALLOC);
    returnNode->nodeType = NODE_INIT;
    returnNode->lineNumber = _AST_LineNumber;
    return returnNode;
}

nodeAST* newLiteralInt      (GO_IMPLEMENT_INT _intValue, memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = LITERAL_INT;
    returnNode->nodeValue.intValue = _intValue;
    return returnNode;
}
nodeAST* newLiteralFloat    (GO_IMPLEMENT_FLOAT64 _floatValue, memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = LITERAL_FLOAT;
    returnNode->nodeValue.floatValue = _floatValue;
    return returnNode;
}
nodeAST* newLiteralRune     (GO_IMPLEMENT_RUNE _runeValue, memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = LITERAL_RUNE;
    returnNode->nodeValue.runeValue = _runeValue;
    return returnNode;
}
nodeAST* newLiteralString   (GO_IMPLEMENT_STRING _stringValue, memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = LITERAL_STRING;
    returnNode->nodeValue.stringValue = GO_IMPLEMENT_STRING_CPY(_stringValue, _allocator);
    return returnNode;
}
nodeAST* newIdentifier      (const char* _identifier, memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = IDENTIFIER;
    returnNode->nodeValue.identifier = (char*)mallocList(sizeof(char)*(strlen(_identifier)+1), _allocator);
    if (returnNode->nodeValue.identifier == NULL) _func_throwError(TREENODE_ERROR_MALLOC);
    memset(returnNode->nodeValue.identifier, '\0', sizeof(char)*(strlen(_identifier)+1));
    strcpy(returnNode->nodeValue.identifier, _identifier);
    return returnNode;
}
nodeAST* newBasicTypeINT    (memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = BASIC_TYPE;
    returnNode->nodeValue.basicType = BASIC_INT;
    return returnNode;
}
nodeAST* newBasicTypeFloat  (memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = BASIC_TYPE;
    returnNode->nodeValue.basicType = BASIC_FLOAT;
    return returnNode;
}
nodeAST* newBasicTypeRune   (memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = BASIC_TYPE;
    returnNode->nodeValue.basicType = BASIC_RUNE;
    return returnNode;
}
nodeAST* newBasicTypeString (memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = BASIC_TYPE;
    returnNode->nodeValue.basicType = BASIC_STRING;
    return returnNode;
}
nodeAST* newBasicTypeBool   (memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = BASIC_TYPE;
    returnNode->nodeValue.basicType = BASIC_BOOL;
    return returnNode;
}

nodeAST* newEqual           (nodeAST* _left, nodeAST* _right, memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = EXPR_BINARY_OP_EQUAL;
    returnNode->nodeValue.equal.left = _left;
    returnNode->nodeValue.equal.right = _right;
    return returnNode;
}
nodeAST* newNotEqual        (nodeAST* _left, nodeAST* _right, memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = EXPR_BINARY_OP_NEQUAL;
    returnNode->nodeValue.nequal.left = _left;
    returnNode->nodeValue.nequal.right = _right;
    return returnNode;
}
nodeAST* newLess            (nodeAST* _left, nodeAST* _right, memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = EXPR_BINARY_OP_LESS;
    returnNode->nodeValue.less.left = _left;
    returnNode->nodeValue.less.right = _right;
    return returnNode;
}
nodeAST* newLessEqual       (nodeAST* _left, nodeAST* _right, memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = EXPR_BINARY_OP_LESSEQUAL;
    returnNode->nodeValue.less.left = _left;
    returnNode->nodeValue.less.right = _right;
    return returnNode;
}
nodeAST* newGreat           (nodeAST* _left, nodeAST* _right, memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = EXPR_BINARY_OP_GREAT;
    returnNode->nodeValue.great.left = _left;
    returnNode->nodeValue.great.right = _right;
    return returnNode;
}
nodeAST* newGreatEqual      (nodeAST* _left, nodeAST* _right, memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = EXPR_BINARY_OP_GREATEQUAL;
    returnNode->nodeValue.greatEqual.left = _left;
    returnNode->nodeValue.greatEqual.right = _right;
    return returnNode;
}

nodeAST* newAdd             (nodeAST* _left, nodeAST* _right, memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = EXPR_BINARY_OP_ADD;
    returnNode->nodeValue.add.left = _left;
    returnNode->nodeValue.add.right = _right;
    return returnNode;
}
nodeAST* newSub             (nodeAST* _left, nodeAST* _right, memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = EXPR_BINARY_OP_SUB;
    returnNode->nodeValue.sub.left = _left;
    returnNode->nodeValue.sub.right = _right;
    return returnNode;
}
nodeAST* newMul             (nodeAST* _left, nodeAST* _right, memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = EXPR_BINARY_OP_MUL;
    returnNode->nodeValue.mul.left = _left;
    returnNode->nodeValue.mul.right = _right;
    return returnNode;
}
nodeAST* newDiv             (nodeAST* _left, nodeAST* _right, memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = EXPR_BINARY_OP_DIV;
    returnNode->nodeValue.div.left = _left;
    returnNode->nodeValue.div.right = _right;
    return returnNode;
}
nodeAST* newMod             (nodeAST* _left, nodeAST* _right, memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = EXPR_BINARY_OP_MOD;
    returnNode->nodeValue.mod.left = _left;
    returnNode->nodeValue.mod.right = _right;
    return returnNode;
}

nodeAST* newBitAnd          (nodeAST* _left, nodeAST* _right, memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = EXPR_BINARY_OP_AND;
    returnNode->nodeValue.bitAnd.left = _left;
    returnNode->nodeValue.bitAnd.right = _right;
    return returnNode;
}
nodeAST* newBitOr           (nodeAST* _left, nodeAST* _right, memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = EXPR_BINARY_OP_OR;
    returnNode->nodeValue.bitOr.left = _left;
    returnNode->nodeValue.bitOr.right = _right;
    return returnNode;
}
nodeAST* newBitXor          (nodeAST* _left, nodeAST* _right, memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = EXPR_BINARY_OP_XOR;
    returnNode->nodeValue.bitXor.left = _left;
    returnNode->nodeValue.bitXor.right = _right;
    return returnNode;
}
nodeAST* newBitAndNot       (nodeAST* _left, nodeAST* _right, memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = EXPR_BINARY_OP_ANDNOT;
    returnNode->nodeValue.bitAndNot.left = _left;
    returnNode->nodeValue.bitAndNot.right = _right;
    return returnNode;
}
nodeAST* newBitNot          (nodeAST* _expr, memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = EXPR_UNIARY_OP_NOT;
    returnNode->nodeValue.bitNot.expr = _expr;
    return returnNode;
}

nodeAST* newShiftLeft       (nodeAST* _left, nodeAST* _right, memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = EXPR_BINARY_OP_LSHIFT;
    returnNode->nodeValue.shiftLeft.left = _left;
    returnNode->nodeValue.shiftLeft.right = _right;
    return returnNode;
}
nodeAST* newShiftRight      (nodeAST* _left, nodeAST* _right, memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = EXPR_BINARY_OP_RSHIFT;
    returnNode->nodeValue.shiftRight.left = _left;
    returnNode->nodeValue.shiftRight.right = _right;
    return returnNode;
}

nodeAST* newLogicAnd        (nodeAST* _left, nodeAST* _right, memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = EXPR_BINARY_OP_LOGIC_AND;
    returnNode->nodeValue.logicAnd.left = _left;
    returnNode->nodeValue.logicAnd.right = _right;
    return returnNode;
}
nodeAST* newLogicOr         (nodeAST* _left, nodeAST* _right, memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = EXPR_BINARY_OP_LOGIC_OR;
    returnNode->nodeValue.logicOr.left = _left;
    returnNode->nodeValue.logicOr.right = _right;
    return returnNode;
}
nodeAST* newLogicNot        (nodeAST* _expr, memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = EXPR_UNIARY_OP_LOGIC_NOT;
    returnNode->nodeValue.logicNot.expr = _expr;
    return returnNode;
}

nodeAST* newPos             (nodeAST* _expr, memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = EXPR_UNIARY_OP_POS;
    returnNode->nodeValue.pos.expr = _expr;
    return returnNode;
}
nodeAST* newNeg             (nodeAST* _expr, memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = EXPR_UNIARY_OP_NEG;
    returnNode->nodeValue.neg.expr = _expr;
    return returnNode;
}

nodeAST* newAppend          (nodeAST* _target, nodeAST* _expr, memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = EXPR_APPEND;
    returnNode->nodeValue.append.target = _target;
    returnNode->nodeValue.append.expr = _expr;
    return returnNode;
}
nodeAST* newFuncCall        (nodeAST* _target, nodeAST* _expr, memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = EXPR_FUNC_CALL;
    returnNode->nodeValue.funcCall.target = _target;
    returnNode->nodeValue.funcCall.expr = _expr;
    return returnNode;
}
nodeAST* newCast            (nodeAST* _target, nodeAST* _expr, memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = EXPR_CAST;
    returnNode->nodeValue.cast.target = _target;
    returnNode->nodeValue.cast.expr = _expr;
    return returnNode;
}

nodeAST* newSelector        (nodeAST* _target, nodeAST* _entry, memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = EXPR_SELECTOR;
    returnNode->nodeValue.selector.target = _target;
    returnNode->nodeValue.selector.entry = _entry;
    return returnNode;
}
nodeAST* newIndex           (nodeAST* _target, nodeAST* _entry, memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = EXPR_INDEX;
    returnNode->nodeValue.index.target = _target;
    returnNode->nodeValue.index.entry = _entry;
    return returnNode;
}
nodeAST* newSlice           (nodeAST* _target, nodeAST* _entry, memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = EXPR_SLICE;
    returnNode->nodeValue.slice.target = _target;
    returnNode->nodeValue.slice.entry = _entry;
    return returnNode;
}

nodeAST* newAddressSlice    (nodeAST* _start, nodeAST* _end, memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = EXPR_ADDRESS_SLICE;
    returnNode->nodeValue.addressSlice.start = _start;
    returnNode->nodeValue.addressSlice.end = _end;
    return returnNode;
}
nodeAST* newAddressSliceFull(nodeAST* _start, nodeAST* _end, nodeAST* _max, memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = EXPR_ADDRESS_SLICE_FULL;
    returnNode->nodeValue.addressSliceFull.start = _start;
    returnNode->nodeValue.addressSliceFull.end = _end;
    returnNode->nodeValue.addressSliceFull.max = _max;
    return returnNode;
}

nodeAST* newExprList        (nodeAST* _expr, nodeAST* _next, memoryList _allocator){
    nodeAST* returnNode = allocateNode(_allocator);
    returnNode->nodeType = EXPR_UTILITY_EXPRLIST;
    returnNode->nodeValue.exprList.expr = _expr;
    returnNode->nodeValue.exprList.next = _next;
    return returnNode;
}
#endif