#ifndef __GoLite__TYPES__H__
#define __GoLite__TYPES__H__

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define GoLite_True                  1L
#define GoLite_False                 0L

#define GoLite_Type_Primitive        0L
#define GoLite_Type_ReferenceArray   1L
#define GoLite_Type_ReferenceSlice   2L
#define GoLite_Type_ReferenceStruct  4L
#define GoLite_Type_ReferenceString  5L

#define GoLite_Memory_Unit           8L

#define GoLite_Error_Malloc          "GoLite Error : Malloc failure"
#define GoLite_Error_Implementation  "GoLite Error : Implementation failure"
#define GoLite_Error_ArrayOutOfBound "GoLite Error : Array Access Out Of Bound"
#define GoLite_Error_ArrayNew        "GoLite Error : Invalid Init Mode"
#define GoLite_Error_StringDump      "GoLite Error : Invalid String Dump"
#define GoLite_Error_GCTag           "GoLite Error : GC reference count error"
#define GoLite_Error_GCUnTag         "GoLite Error : GC zero reference error"
#define GoLite_Error_NotYetImplement "GoLite Error : Not Yet Implement"

void GoLite_Error(const char* _str) {
    fprintf(stderr, "%s\n", _str);
    exit(1);
    return;
}
void GoLite_Init();
void GoLite_Exit();

typedef int64_t  GoLite_Int;         // GoLite Implementation of int
typedef double   GoLite_Float64;     // GoLite Implementation of float64
typedef uint64_t GoLite_Rune;        // GoLite Implementation of rune
typedef uint64_t GoLite_Bool;        // GoLite Implementation of bool
typedef char*    GoLite_String;      // GoLite Implementation of string


#define GoLite_Memory_Hash_Size       1000L
#define GoLite_Memory_MaxCount        0xffffffffffffffff
typedef struct GoLite_Memory_Struct {
    uint64_t addr;
    uint64_t usage;
    uint64_t size;
    struct GoLite_Memory_Struct* next;
} GoLite_Memory_Struct;
GoLite_Memory_Struct* GoLite_Memory_HashTable[GoLite_Memory_Hash_Size];
uint64_t GoLite_Memory_Hasher(uint64_t _ptr) {  // Naive Approach Here
    return _ptr % GoLite_Memory_Hash_Size;
}
void     GoLite_Memory_Construct() {
    for (size_t iter = 0; iter < GoLite_Memory_Hash_Size; iter++) {
	GoLite_Memory_HashTable[iter] = NULL;
    }
}
void     GoLite_Memory_Destruct () {
    for (size_t iter = 0; iter < GoLite_Memory_Hash_Size; iter++) {
	GoLite_Memory_Struct* ptr = GoLite_Memory_HashTable[iter];
	while (ptr != NULL) {
	    GoLite_Memory_Struct* target = ptr;
	    ptr = ptr->next;
	    free(target);
	}
    }
}
uint64_t GoLite_Memory_RefernceCount (uint64_t _handle) {
    uint64_t key = GoLite_Memory_Hasher(_handle);
    if (GoLite_Memory_HashTable[key] == NULL) return GoLite_Memory_MaxCount;
    GoLite_Memory_Struct* ptr = GoLite_Memory_HashTable[key];
    while (ptr != NULL) {
	if (ptr->addr == _handle) return ptr->usage;
	ptr = ptr->next;
    }
    return GoLite_Memory_MaxCount;
}
uint64_t GoLite_Memory_Alloc  (uint64_t _size) {
    GoLite_Memory_Struct* newRef =
	(GoLite_Memory_Struct*)malloc(sizeof(GoLite_Memory_Struct));
    if (newRef == NULL) GoLite_Error(GoLite_Error_Malloc);
    newRef->addr = (uint64_t)malloc(_size);
    if (newRef->addr == (uint64_t)NULL) GoLite_Error(GoLite_Error_Malloc);
    newRef->usage = 0L;
    newRef->size = _size;
    uint64_t key = GoLite_Memory_Hasher(newRef->addr);
    newRef->next = GoLite_Memory_HashTable[key];
    GoLite_Memory_HashTable[key] = newRef;
    return newRef->addr;
}
uint64_t GoLite_Memory_Touch  (uint64_t _handle) {
    uint64_t key = GoLite_Memory_Hasher(_handle);
    if (GoLite_Memory_HashTable[key] == NULL) GoLite_Error(GoLite_Error_GCTag);
    GoLite_Memory_Struct* ptr = GoLite_Memory_HashTable[key];
    while (ptr != NULL) {
	if (ptr->addr == _handle) {
	    if (ptr->usage != 0L) return ptr->usage;
	    if (GoLite_Memory_HashTable[key] == ptr) {
		free((void*)(ptr->addr));
		GoLite_Memory_HashTable[key] = ptr->next;
		free(ptr);
		return 0L;
	    }
	    GoLite_Memory_Struct* previousPtr = GoLite_Memory_HashTable[key];
	    while (previousPtr->next != ptr) previousPtr = previousPtr->next;
	    free((void*)(ptr->addr));
	    previousPtr->next = ptr->next;
	    free(ptr);
	    return 0L;
	}
	ptr = ptr->next;
    }
    GoLite_Error(GoLite_Error_GCTag);
    return GoLite_Memory_MaxCount;
}
uint64_t GoLite_Memory_Tag    (uint64_t _handle) {
    uint64_t key = GoLite_Memory_Hasher(_handle);
    if (GoLite_Memory_HashTable[key] == NULL) GoLite_Error(GoLite_Error_GCTag);
    GoLite_Memory_Struct* ptr = GoLite_Memory_HashTable[key];
    while (ptr != NULL) {
	if (ptr->addr == _handle) {
	    ptr->usage++;
	    return ptr->usage;
	}
	ptr = ptr->next;
    }
    GoLite_Error(GoLite_Error_GCTag);
    return GoLite_Memory_MaxCount;
}
uint64_t GoLite_Memory_UnTag  (uint64_t _handle) {
    uint64_t key = GoLite_Memory_Hasher(_handle);
    if (GoLite_Memory_HashTable[key] == NULL) GoLite_Error(GoLite_Error_GCTag);
    GoLite_Memory_Struct* ptr = GoLite_Memory_HashTable[key];
    while (ptr != NULL) {
	if (ptr->addr == _handle) {
	    if (ptr->usage == 0L) GoLite_Error(GoLite_Error_GCUnTag);
	    ptr->usage--;
	    return GoLite_Memory_Touch(_handle);
	}
	ptr = ptr->next;
    }
    GoLite_Error(GoLite_Error_GCTag);
    return GoLite_Memory_MaxCount;
}
uint64_t GoLite_Memory_Reclaim() {
    uint64_t freeed = 0L;
    for (size_t iter = 0; iter < GoLite_Memory_Hash_Size; iter++) {
	GoLite_Memory_Struct* ptr = GoLite_Memory_HashTable[iter];
	while (ptr != NULL) {
	    free((void*)(ptr->addr));
	    freeed += ptr->size;
	    GoLite_Memory_Struct* next = ptr->next;
	    free(ptr);
	    ptr = next;
	}
	GoLite_Memory_HashTable[iter] = NULL;
    }
    return freeed;
}
uint64_t GoLite_Memory_Info_Entry () {
    uint64_t counter = 0L;
    for (size_t iter = 0L; iter < GoLite_Memory_Hash_Size; iter++) {
	GoLite_Memory_Struct* ptr = GoLite_Memory_HashTable[iter];
	while (ptr != NULL) {
	    counter++;
	    ptr = ptr->next;
	}
    }
    return counter;
}
uint64_t GoLite_Memory_Info_Size  () {
    uint64_t counter = 0L;
    for (size_t iter = 0L; iter < GoLite_Memory_Hash_Size; iter++) {
	GoLite_Memory_Struct* ptr = GoLite_Memory_HashTable[iter];
	while (ptr != NULL) {
	    counter += ptr->size;
	    ptr = ptr->next;
	}
    }
    return counter;
}

uint64_t GoLite_String_ConstDump (uint64_t _addr) {
    const char* address = (const char*)_addr;
    if (address == NULL) GoLite_Error(GoLite_Error_StringDump);
    uint64_t heapMem = GoLite_Memory_Alloc(sizeof(char)*(strlen(address)+1));
    strcpy((char*)heapMem, address);
    return heapMem;
}
void     GoLite_String_Scope     (uint64_t _addr) {
    GoLite_Memory_Tag(_addr);
    return;
}
void     GoLite_String_UnScope   (uint64_t _addr) {
    GoLite_Memory_UnTag(_addr);
    return;
}
uint64_t GoLite_String_Concat    (uint64_t _addrA, uint64_t _addrB) {
    const char* A = (const char*)_addrA; const size_t lengthA = strlen(A);
    const char* B = (const char*)_addrB; const size_t lengthB = strlen(B);
    size_t newLength = lengthA + lengthB + 1;
    uint64_t returnAddr = GoLite_Memory_Alloc(sizeof(char)*newLength);
    memset((void*)returnAddr, '\0', sizeof(char)*newLength);
    for (size_t iter = 0L; iter < strlen(A); iter++)
	((char*)returnAddr)[iter] = A[iter];
    for (size_t iter = 0L; iter < strlen(B); iter++)
	((char*)returnAddr)[iter+lengthA] = B[iter];
    GoLite_Memory_Touch(_addrA);
    GoLite_Memory_Touch(_addrB);
    return returnAddr;
}
uint64_t GoLite_String_Clone     (uint64_t _addr) {
    if (_addr == (uint64_t)NULL) GoLite_Error(GoLite_Error_Implementation);
    const char* str = (const char*)_addr;
    size_t strLength = strlen(str);
    uint64_t returnPtr = GoLite_Memory_Alloc(sizeof(char)*(strLength+1));
    memset((void*)returnPtr, '\0', sizeof(char)*(strLength+1));
    memcpy((void*)returnPtr, (const void*)_addr, sizeof(char)*(strLength+1));
    return returnPtr;
}

typedef struct GoLite_Array_Type {
    uint64_t memoryChunk;
    uint64_t size;
    uint64_t type;
} GoLite_Array_Type;
typedef struct GoLite_Slice_Type {
    uint64_t basePtr;
    uint64_t memoryChunk;
    uint64_t size;
    uint64_t maxSize;
    uint64_t type;
} GoLite_Slice_Type;
typedef struct GoLite_Struct_Type {
    uint64_t memoryChunk;
    uint64_t type;  // Implement by a array
    uint64_t size;
} GoLite_Struct_Type;

void    GoLite_Array_Scope   (uint64_t _addr);
void    GoLite_Slice_Scope   (uint64_t _addr);
void    GoLite_Struct_Scope  (uint64_t _addr);
void    GoLite_Array_UnScope (uint64_t _addr);
void    GoLite_Slice_UnScope (uint64_t _addr);
void    GoLite_Struct_UnScope(uint64_t _addr);
uint64_t GoLite_Array_Clone   (uint64_t _addr);
uint64_t GoLite_Slice_Clone   (uint64_t _addr);
uint64_t GoLite_Struct_Clone  (uint64_t _addr);

void    GoLite_Array_Scope   (uint64_t _addr) {
    if (_addr == (uint64_t)NULL) GoLite_Error(GoLite_Error_Implementation);
    GoLite_Array_Type* ptr = (GoLite_Array_Type*)_addr;
    GoLite_Memory_Tag(ptr->memoryChunk);
    return;
}
void    GoLite_Slice_Scope   (uint64_t _addr) {
    if (_addr == (uint64_t)NULL) GoLite_Error(GoLite_Error_Implementation);
    GoLite_Slice_Type* ptr = (GoLite_Slice_Type*)_addr;
    GoLite_Memory_Tag(ptr->basePtr);
    return;
}
void    GoLite_Struct_Scope  (uint64_t _addr) {
    if (_addr == (uint64_t)NULL) GoLite_Error(GoLite_Error_Implementation);
    GoLite_Struct_Type* ptr = (GoLite_Struct_Type*)_addr;
    GoLite_Memory_Tag(ptr->memoryChunk);
    return;
}
void    GoLite_Array_UnScope (uint64_t _addr) {
    if (_addr == (uint64_t)NULL) GoLite_Error(GoLite_Error_Implementation);
    GoLite_Array_Type* ptr = (GoLite_Array_Type*)_addr;
    switch (ptr->type) {
    case GoLite_Type_Primitive:{
	GoLite_Memory_UnTag(ptr->memoryChunk);
	free(ptr);
	return;
    }
    case GoLite_Type_ReferenceArray: {
	for (size_t iter = 0; iter < ptr->size; iter++) {
	    uint64_t ptrAddr =
		((uint64_t*)(ptr->memoryChunk))[iter];
	    if (ptrAddr == (uint64_t)NULL) continue;
	    GoLite_Array_UnScope(ptrAddr);
	}
	GoLite_Memory_UnTag(ptr->memoryChunk);
	free(ptr);
	return;
    }
    case GoLite_Type_ReferenceStruct: {
	for (size_t iter = 0; iter < ptr->size; iter++) {
	    uint64_t ptrAddr =
		((uint64_t*)(ptr->memoryChunk))[iter];
	    if (ptrAddr == (uint64_t)NULL) continue;
	    GoLite_Struct_UnScope(ptrAddr);
	}
	GoLite_Memory_UnTag(ptr->memoryChunk);
	free(ptr);
	return;
    }
    case GoLite_Type_ReferenceSlice : {
	for (size_t iter = 0; iter < ptr->size; iter++) {
	    uint64_t ptrAddr =
		((uint64_t*)(ptr->memoryChunk))[iter];
	    if (ptrAddr == (uint64_t)NULL) continue;
	    GoLite_Slice_UnScope(ptrAddr);
	}
	GoLite_Memory_UnTag(ptr->memoryChunk);
	free(ptr);
	return;
    }
    case GoLite_Type_ReferenceString : {
	for (size_t iter = 0L; iter < ptr->size; iter++) {
	    uint64_t ptrAddr =
		((uint64_t*)(ptr->memoryChunk))[iter];
	    if (ptrAddr == (uint64_t)NULL) continue;
	    GoLite_Memory_UnTag(ptrAddr);
	}
	GoLite_Memory_UnTag(ptr->memoryChunk);
	free(ptr);
	return;
    }
    }   
    return;
}
void    GoLite_Slice_UnScope (uint64_t _addr) {
     if (_addr == (uint64_t)NULL) GoLite_Error(GoLite_Error_Implementation);
     GoLite_Slice_Type* ptr = (GoLite_Slice_Type*)_addr;
     switch (ptr->type) {
     case GoLite_Type_Primitive:{
	 GoLite_Memory_UnTag(ptr->basePtr);
	 free(ptr);
	 return;
     }
     case GoLite_Type_ReferenceArray: {
	 for (size_t iter = 0; iter < ptr->size; iter++) {
	    uint64_t ptrAddr =
		((uint64_t*)(ptr->memoryChunk))[iter];
	    if (ptrAddr == (uint64_t)NULL) continue;
	    GoLite_Array_UnScope(ptrAddr);
	 }
	 GoLite_Memory_UnTag(ptr->basePtr);
	 free(ptr);
	 return;
     }
     case GoLite_Type_ReferenceStruct: {
	 for (size_t iter = 0; iter < ptr->size; iter++) {
	    uint64_t ptrAddr =
		((uint64_t*)(ptr->memoryChunk))[iter];
	    if (ptrAddr == (uint64_t)NULL) continue;
	    GoLite_Struct_UnScope(ptrAddr);
	 }
	 GoLite_Memory_UnTag(ptr->basePtr);
	 free(ptr);
	 return;
     }
     case GoLite_Type_ReferenceSlice : {
	 for (size_t iter = 0; iter < ptr->size; iter++) {
	     uint64_t ptrAddr =
		 ((uint64_t*)(ptr->memoryChunk))[iter];
	     if (ptrAddr == (uint64_t)NULL) continue;
	     GoLite_Slice_UnScope(ptrAddr);
	 }
	 GoLite_Memory_UnTag(ptr->basePtr);
	 free(ptr);
	 return;
     }
     case GoLite_Type_ReferenceString : {
	 for (size_t iter = 0L; iter < ptr->size; iter++) {
	     uint64_t ptrAddr =
		 ((uint64_t*)(ptr->memoryChunk))[iter];
	     if (ptrAddr == (uint64_t)NULL) continue;
	     GoLite_Memory_UnTag(ptrAddr);
	 }
	 GoLite_Memory_UnTag(ptr->basePtr);
	 free(ptr);
	 return;
     }
     }
     return;
}
void    GoLite_Struct_UnScope(uint64_t _addr) {
    if (_addr == (uint64_t)NULL) GoLite_Error(GoLite_Error_Implementation);
    GoLite_Struct_Type* ptr = (GoLite_Struct_Type*)_addr;
    for (size_t typeIter = 0L; typeIter < ptr->size; typeIter++) {
	uint64_t type = ((uint64_t*)(ptr->type))[typeIter];
	uint64_t addrPtr = ((uint64_t*)(ptr->memoryChunk))[typeIter];
	switch (type) {
	case GoLite_Type_Primitive: continue;
	case GoLite_Type_ReferenceArray: {
	    if (addrPtr == (uint64_t)NULL) continue;
	    GoLite_Array_UnScope(addrPtr);
	    continue;
	}
	case GoLite_Type_ReferenceSlice: {
	    if (addrPtr == (uint64_t)NULL) continue;
	    GoLite_Slice_UnScope(addrPtr);
	    continue;
	}
	case GoLite_Type_ReferenceStruct: {
	    if (addrPtr == (uint64_t)NULL) continue;
	    GoLite_Slice_UnScope(addrPtr);
	    continue;
	}
	case GoLite_Type_ReferenceString : {
	    if (addrPtr == (uint64_t)NULL) continue;
	    GoLite_String_UnScope(addrPtr);
	    continue;
	}
	default: GoLite_Error(GoLite_Error_Implementation);
	}
    }
    return;
}
uint64_t GoLite_Array_Clone  (uint64_t _addr) {
    if (_addr == (uint64_t)NULL) GoLite_Error(GoLite_Error_Implementation);
    GoLite_Array_Type* ptr = (GoLite_Array_Type*)_addr;
    uint64_t arraySize = ptr->size;
    switch (ptr->type) {
    case GoLite_Type_Primitive: {
	size_t memSize = GoLite_Memory_Unit * arraySize;
	uint64_t retMemoryChunk = GoLite_Memory_Alloc(memSize);
	GoLite_Array_Type* retPtr =
	    (GoLite_Array_Type*)malloc(sizeof(GoLite_Array_Type));
	if (retPtr == NULL) GoLite_Error(GoLite_Error_Malloc);
	memcpy((void*)retMemoryChunk, (const void*)ptr->type, memSize);
	retPtr->memoryChunk = retMemoryChunk;
	retPtr->size = ptr->size;
	retPtr->type = GoLite_Type_Primitive;
	return (uint64_t)retPtr;
    }
    case GoLite_Type_ReferenceString : {
	size_t memSize = GoLite_Memory_Unit * arraySize;
	uint64_t retMemoryChunk = GoLite_Memory_Alloc(memSize);
	GoLite_Array_Type* retPtr =
	    (GoLite_Array_Type*)malloc(sizeof(GoLite_Array_Type));
	if (retPtr == NULL) GoLite_Error(GoLite_Error_Malloc);
	for (size_t iter = 0; iter < ptr->size; iter++) {
	    uint64_t strPtr = ((uint64_t*)(ptr->memoryChunk))[iter];
	    uint64_t cpyPtr = GoLite_String_Clone(strPtr);
	    ((uint64_t*)retMemoryChunk)[iter] = cpyPtr;
	    GoLite_String_Scope(((uint64_t*)retMemoryChunk)[iter]);
	}
	retPtr->memoryChunk = retMemoryChunk;
	retPtr->size = ptr->size;
	retPtr->type = GoLite_Type_ReferenceString;
	return (uint64_t)retPtr;
    }
    case GoLite_Type_ReferenceStruct : GoLite_Error(GoLite_Error_NotYetImplement);
    case GoLite_Type_ReferenceSlice : GoLite_Error(GoLite_Error_NotYetImplement);
    case GoLite_Type_ReferenceArray : {
	uint64_t size = GoLite_Memory_Unit * ptr->size;
	if (size == 0L) {
	    GoLite_Array_Type* retAddr =
		(GoLite_Array_Type*)malloc(sizeof(GoLite_Array_Type));
	    if (retAddr == NULL) GoLite_Error(GoLite_Error_Malloc);
	    retAddr->memoryChunk = (uint64_t)NULL;
	    retAddr->type = GoLite_Type_ReferenceArray;
	    retAddr->size = 0L;
	    return (uint64_t)retAddr;
	}
	uint64_t newChunk = GoLite_Memory_Alloc(size);
	GoLite_Array_Type* retAddr =
	    (GoLite_Array_Type*)malloc(sizeof(GoLite_Array_Type));
	if (retAddr == NULL) GoLite_Error(GoLite_Error_Malloc);
	for (size_t iter = 0L; iter < size; iter++) {
	    uint64_t tempPtr = ((uint64_t*)(ptr->memoryChunk))[iter];
	    if (tempPtr == (uint64_t)NULL) {
		((uint64_t*)newChunk)[iter] = (uint64_t)NULL;
		continue;
	    } else {
		uint64_t clone = GoLite_Array_Clone(tempPtr);
		GoLite_Array_Scope(clone);
		((uint64_t*)newChunk)[iter] = clone;
		continue;
	    }
	}
	retAddr->memoryChunk = newChunk;
	retAddr->size = ptr->size;
	retAddr->type = GoLite_Type_ReferenceArray;
	return (uint64_t)retAddr;
    }
    default : GoLite_Error(GoLite_Error_Implementation);
    }
    return (uint64_t)NULL;
}
	
uint64_t GoLite_Array_Alloc  (uint64_t _size, uint64_t _type) {
    switch (_type) {
    case GoLite_Type_ReferenceArray: 
    case GoLite_Type_ReferenceSlice:
    case GoLite_Type_ReferenceStruct:
    case GoLite_Type_ReferenceString:
    case GoLite_Type_Primitive: {
	uint64_t ptr = GoLite_Memory_Alloc(GoLite_Memory_Unit*_size);
	GoLite_Array_Type* retPtr =
	    (GoLite_Array_Type*)malloc(sizeof(GoLite_Array_Type));
	if (retPtr == NULL) GoLite_Error(GoLite_Error_Malloc);
	memset((void*)ptr, 0, GoLite_Memory_Unit*_size);
	retPtr->memoryChunk = ptr;
	retPtr->type = _type;
	retPtr->size = _size;
	return (uint64_t)retPtr;
    }
    default: GoLite_Error(GoLite_Error_ArrayNew);
    }
    return (uint64_t)NULL;
}
uint64_t GoLite_Array_Load   (uint64_t _addr, uint64_t _index) {
    if (_addr == (uint64_t)NULL) GoLite_Error(GoLite_Error_Implementation);
    GoLite_Array_Type* ptr = (GoLite_Array_Type*)_addr;
    uint64_t arrayBound = ptr->size;
    if (_index >= arrayBound) GoLite_Error(GoLite_Error_ArrayOutOfBound);
    return ((uint64_t*)(ptr->memoryChunk))[_index];
}
void     GoLite_Array_Store  (uint64_t _addr, uint64_t _index, uint64_t _data) {
    if (_addr == (uint64_t)NULL) GoLite_Error(GoLite_Error_Implementation);
    GoLite_Array_Type* ptr = (GoLite_Array_Type*)_addr;
    uint64_t arrayBound = ptr->size;
    if (_index >= arrayBound) GoLite_Error(GoLite_Error_ArrayOutOfBound);
    switch (ptr->type) {
    case GoLite_Type_Primitive: {
	((uint64_t*)(ptr->memoryChunk))[_index] = _data;
	return;
    }
    case GoLite_Type_ReferenceString : {
	if (((uint64_t*)(ptr->memoryChunk))[_index] != (uint64_t)NULL)
	    GoLite_String_UnScope(((uint64_t*)(ptr->memoryChunk))[_index]);
	((uint64_t*)(ptr->memoryChunk))[_index] = _data;
	GoLite_String_Scope(((uint64_t*)(ptr->memoryChunk))[_index]);
	break;
    }
    case GoLite_Type_ReferenceArray : {
	if (((uint64_t*)(ptr->memoryChunk))[_index] != (uint64_t)NULL)
	    GoLite_Array_UnScope(((uint64_t*)(ptr->memoryChunk))[_index]);
	((uint64_t*)(ptr->memoryChunk))[_index] = _data;
	GoLite_Array_Scope(((uint64_t*)(ptr->memoryChunk))[_index]);
	break;
    }
    case GoLite_Type_ReferenceSlice: {
	if (((uint64_t*)(ptr->memoryChunk))[_index] != (uint64_t)NULL)
	    GoLite_Slice_UnScope(((uint64_t*)(ptr->memoryChunk))[_index]);
	((uint64_t*)(ptr->memoryChunk))[_index] = _data;
	GoLite_Slice_Scope(((uint64_t*)(ptr->memoryChunk))[_index]);
	break;
    }
    case GoLite_Type_ReferenceStruct : {
	if (((uint64_t*)(ptr->memoryChunk))[_index] != (uint64_t)NULL)
	    GoLite_Struct_UnScope(((uint64_t*)(ptr->memoryChunk))[_index]);
	((uint64_t*)(ptr->memoryChunk))[_index] = _data;
	GoLite_Struct_Scope(((uint64_t*)(ptr->memoryChunk))[_index]);
    }
    default: GoLite_Error(GoLite_Error_ArrayNew);
    }
    return;
}

#endif

/*int main() {
    
    GoLite_Memory_Construct();
    printf("Entry : %llu, Size : %llu\n",
	   GoLite_Memory_Info_Entry(), GoLite_Memory_Info_Size());

    uint64_t array = GoLite_Array_Alloc(100000000L, GoLite_Type_Primitive);
    GoLite_Array_Scope(array);

    for (uint64_t iter = 0; iter < 100000000; iter++) {
	printf("%lf \r", (double)iter / 100000000);
	GoLite_Array_Store(array, iter, 100000000-iter);
    }

    GoLite_Array_UnScope(array);
    
    printf("Reclaimed : %llu\n", GoLite_Memory_Reclaim());

    GoLite_Memory_Destruct();
}*/
