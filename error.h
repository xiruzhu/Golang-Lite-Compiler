#ifndef __GoLiteCompiler__ERRORBUFFER__H__
#define __GoLiteCompiler__ERRORBUFFER__H__

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "memory.h"
#include "treeNode.h"

#define MAX_ERROR_MSG 10L

typedef struct errorMsgType{
    char* msg;
    size_t lineNumber;
    struct errorMsgType* next;
} errorMsgType;

errorMsgType* _errorBuffer = NULL;
extern memoryList _treeNodeAllocator;

void addErrorMsg(const char* _str, size_t _lineNumber) {
    if (_errorBuffer == NULL) {
	_errorBuffer = (errorMsgType*)malloc(sizeof(errorMsgType));
	_errorBuffer->msg = (char*)malloc(sizeof(char)*(strlen(_str)+1));
	memset(_errorBuffer->msg, '\0', sizeof(char)*(strlen(_str)+1));
	strcpy(_errorBuffer->msg, _str);
	_errorBuffer->lineNumber = _lineNumber;
	_errorBuffer->next = NULL;
	return;
    }
    errorMsgType* ptr = _errorBuffer;
    assert(ptr != NULL);
    while (ptr->next != NULL) ptr = ptr->next;
    ptr->next = (errorMsgType*)malloc(sizeof(errorMsgType));
    ptr->next->msg = (char*)malloc(sizeof(char)*(strlen(_str)+1));
    memset(ptr->next->msg, '\0', sizeof(char)*(strlen(_str)+1));
    strcpy(ptr->next->msg, _str);
    ptr->next->lineNumber = _lineNumber;
    ptr->next->next = NULL;
    return;
}

void printErrorMsg(){
    errorMsgType* ptr = _errorBuffer;
    size_t number = 0L;
    for (size_t iter = 0L; iter < MAX_ERROR_MSG; iter++) {
	if (ptr == NULL) break;
	fprintf(stderr, "\e[1;31m[Error]\e[0m ");
	if (ptr->lineNumber != 0L) {
	    fprintf(stderr, "(line: %zu) ", ptr->lineNumber);
	}
	fprintf(stderr, "%s\n", ptr->msg);
	ptr = ptr->next;
	number++;
    }
    if (number == MAX_ERROR_MSG) {
	fprintf(stderr,
		"\e[1;31m[Error] \e[0m too many errors, stop at first %zu errors\n",
		MAX_ERROR_MSG);
    }
}

void dumpErrorMsg(const char* _str, size_t _lineNumber) {
    addErrorMsg(_str, _lineNumber);
    printErrorMsg();
    // TODO: memeory stuff
    freeList(_treeNodeAllocator);
    exit(1L);
    return;
}

bool hasError() {return _errorBuffer != NULL;}

#endif

