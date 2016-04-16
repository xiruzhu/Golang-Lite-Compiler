#ifndef __GoLiteCompiler__SYMBOLTABLE__H__
#define __GoLiteCompiler__SYMBOLTABLE__H__

#include "mem_sys.h"
#include "treeNode.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "type.h"

#define DEFAULT_HASH_SIZE 2048
#define DEFAULT_HASH_LIST_SIZE	4
#define DEFAULT_SYM_TBL_CHILD_CAP 16
#define WHITE_COLOR  "\033[1m\033[37m"
#define RED_COLOR "\033[1m\033[31m"
#define RESET_COLOR "\e[m"

//This is the memory collector utilized.
//Helps keep track of all allocated items

/*
 * So the symbol entry table will include a few things
 * The symbol ID
 * The line number of the declaration
 * The type of the value
 */

typedef struct table_entry{
    char * id; //The human name for it
    nodeAST * node_ptr;
    
    unsigned int line_num;
    type * type_info;
}tbl_entry;

/*
 * The actual table itself is composed of a HashTable of these values
 * They can be found by hashing the String ID of the name
 * The table also contains a pointer to the parent symbol table
 * It also has all the sub tables for printing the symbol table
 */

typedef struct symbol_table{
    struct symbol_table * parent;
    
    struct symbol_table ** childs;
    unsigned int num_childs;
    unsigned int max_childs;
    
    struct hash_table * tbl;
}sym_tbl;

/*
 * The hash table used to find an entry
 * This will be a simple implementation of an hashed value to an array
 * That array will be searched linearly
 */
typedef struct hash_table{
    tbl_entry *** hash_system;
    
    unsigned int max_size; //As in how big we want it. For example 1024, would lead to 1024 mappings
    int * entry_list_size;
    int * entry_list_size_cap;
}hash_tbl;

/*
 * Method List
 * ___________________________________________________________________________________________________________
 */
tbl_entry * new_tbl_entry(char * identifier, int line_num, nodeAST * node, type* nodeType);
sym_tbl * new_sym_tbl(int hash_tbl_size);
sym_tbl * new_sym_tbl_parent(sym_tbl * parent, int hash_tbl_size);
hash_tbl * new_hash_tbl();
hash_tbl * new_hash_tbl_size(int size);

void free_tbl_entry(tbl_entry *);
void free_sym_tbl(sym_tbl *);
void free_hash_tbl(hash_tbl *);


unsigned long hash_func(char *str, int max_size);
int add_hash_entry(tbl_entry * entry, hash_tbl * table);
tbl_entry * find_hash_entry_node(nodeAST * node, hash_tbl * table);
tbl_entry * find_hash_entry_id(char * id, hash_tbl * table);
int add_child_sym_tbl(sym_tbl * child, sym_tbl * parent);
tbl_entry * sym_tbl_find_entry(char * id, sym_tbl * table);
tbl_entry * sym_tbl_find_entry_scoped(char * id, sym_tbl * table);
int sym_tbl_add_entry(tbl_entry * entry, sym_tbl * table);
int print_sym_tbl_init(sym_tbl * table, char * file_path);
int print_sym_tbl(sym_tbl * table, FILE * file);
int print_hash_tbl(hash_tbl * tbl, FILE * file);
int print_sym_tbl_scoped(sym_tbl * table, FILE * file);
type * find_type(nodeAST * node);

/*
 * -----------------------------------------------------------------------------------------------------------
 * Constructors and Destructors
 * -----------------------------------------------------------------------------------------------------------
 */

tbl_entry * new_tbl_entry(char * identifier, int line_num, nodeAST * node, type* nodeType){
    if(identifier == NULL){
        fprintf(stderr, "Null identifier. new_tbl_entry failed\n");
        return NULL;
    }
    tbl_entry * ret = (tbl_entry *)alloc(1, sizeof(tbl_entry));
    ret->line_num = line_num;
    ret->type_info = nodeType;
    ret->id = identifier;
    ret->node_ptr = node;
    if(node != NULL)
        node->sym_tbl_ptr = nodeType;
    return ret;
}

sym_tbl * new_sym_tbl(int hash_tbl_size){
    sym_tbl * ret = (sym_tbl *)alloc(1, sizeof(sym_tbl));
    ret->parent = NULL;
    ret->childs = (sym_tbl **)alloc(DEFAULT_SYM_TBL_CHILD_CAP, sizeof(sym_tbl *));
    ret->num_childs = 0;
    ret->max_childs = DEFAULT_SYM_TBL_CHILD_CAP;
    ret->tbl = new_hash_tbl_size(hash_tbl_size);
    return ret;
}

sym_tbl * new_sym_tbl_parent(sym_tbl * parent, int hash_tbl_size){
    if(parent == NULL){
        fprintf(stderr, "Null parent. new_sym_tbl failed\n");
        return NULL;
    }
    sym_tbl * ret = (sym_tbl *)alloc(1, sizeof(sym_tbl));
    ret->parent = parent;
    add_child_sym_tbl(ret, parent);
    
    ret->childs = (sym_tbl **)alloc(DEFAULT_SYM_TBL_CHILD_CAP, sizeof(sym_tbl *));
    ret->num_childs = 0;
    ret->max_childs = DEFAULT_SYM_TBL_CHILD_CAP;
    ret->tbl = new_hash_tbl_size(hash_tbl_size);
    return ret;
}

hash_tbl * new_hash_tbl(){
    hash_tbl * ret = (hash_tbl *)alloc(1, sizeof(sym_tbl));
    ret->hash_system = (tbl_entry ***)alloc(DEFAULT_HASH_SIZE, sizeof(tbl_entry **));
    for(int i = 0; i < DEFAULT_HASH_SIZE; i++)
        ret->hash_system[i] = (tbl_entry **)alloc(DEFAULT_HASH_LIST_SIZE, sizeof(tbl_entry *));
    ret->max_size = DEFAULT_HASH_SIZE;
    ret->entry_list_size = (int *)alloc(DEFAULT_HASH_SIZE,sizeof(int));
    ret->entry_list_size_cap = (int *)alloc(DEFAULT_HASH_SIZE, sizeof(int));
    for(int i = 0; i < DEFAULT_HASH_SIZE; i++){
        ret->entry_list_size[i] = 0;
        ret->entry_list_size_cap[i] = DEFAULT_HASH_LIST_SIZE;
    }
    return ret;
}

hash_tbl * new_hash_tbl_size(int size){
    hash_tbl * ret = (hash_tbl *)alloc(1, sizeof(sym_tbl));
    ret->hash_system = (tbl_entry ***)alloc(size, sizeof(tbl_entry **));
    for(int i = 0; i < size; i++){
        ret->hash_system[i] = (tbl_entry **)alloc(DEFAULT_HASH_LIST_SIZE, sizeof(tbl_entry *));
    }
    ret->max_size = size;
    ret->entry_list_size = (int *)alloc(size, sizeof(int));
    ret->entry_list_size_cap = (int *)alloc(size, sizeof(int));
    for(int i = 0; i < DEFAULT_HASH_SIZE; i++){
        ret->entry_list_size[i] = 0;
        ret->entry_list_size_cap[i] = DEFAULT_HASH_LIST_SIZE;
    }
    return ret;
}

void free_tbl_entry(tbl_entry * entry){
    free(entry);
    //We don't want to free the id since we did not allocate it here
}

void free_hash_tbl(hash_tbl * table){
    for(int i = 0; i < table->max_size; i++){
        free(table->hash_system[i]);
    }
    free(table->hash_system);
    free(table->entry_list_size);
    free(table->entry_list_size_cap);
    free(table);
}

void free_sym_tbl(sym_tbl * table){
    free_hash_tbl(table->tbl);
    for(int i = 0; i < table->num_childs; i++)
        free_sym_tbl(table->childs[i]);
    free(table->childs);
    free(table);
}


/*
 * -----------------------------------------------------------------------------------------------------------
 * Hash Table Methods
 * -----------------------------------------------------------------------------------------------------------
 */

/*
 * The hash function, will return us an int given a string and max_size
 */
unsigned long hash_func(char *str, int max_size)
{
    unsigned long hash = 0;
    int c;
    while ((c = *str++))
        hash = c + (hash << 6) + (hash << 16) - hash;
    return hash % max_size;
}

/*
 * This will add a tbl_entry to the hash table
 * Will return 0 for success
 * Will return -1 for failure
 */
int add_hash_entry(tbl_entry * entry, hash_tbl * table){
    int index;
    if(entry == NULL || table == NULL){
        fprintf(stderr, "Null entry or table. add_hash_entry failed\n");
        return -1;
    }
    //First step is to get the entry hash value
    index = hash_func(entry->id, table->max_size);
    //Next we check if that entry is already filled up
    //printf("Alive %p %d %d\n", table->hash_system[index], table->entry_list_size[index], table->entry_list_size_cap[index]);
    if(table->entry_list_size[index] == table->entry_list_size_cap[index]){
        table->hash_system[index] = ralloc(table->hash_system[index], table->entry_list_size_cap[index] * 2);// Realloc stuff, Need to talk to K9
        table->entry_list_size_cap[index] *= 2;
    }
    //Now we can add the entry
    table->hash_system[index][table->entry_list_size[index]++] = entry;
    return 0;
}

/*
 * This will find a tbl_entry in the hash table
 * Will return pointer to entry on success
 * Will return Null for failure
 */
tbl_entry * find_hash_entry_node(nodeAST * node, hash_tbl * table){
    int index;
    if(node == NULL || table == NULL){
        fprintf(stderr, "Null node or table. find_hash_entry failed\n");
        return NULL;
    }
    else if(node->nodeValue.identifier){
        fprintf(stderr, "Null node identifier. find_hash_entry failed\n");
        return NULL;
    }
    index = hash_func(node->nodeValue.identifier, table->max_size);
    
    for(int i = 0; i < table->entry_list_size[index]; i++){
        if(strcmp(table->hash_system[index][i]->id, node->nodeValue.identifier) == 0)
            return table->hash_system[index][i];
    }
    return NULL;
}

tbl_entry * find_hash_entry_id(char * id, hash_tbl * table){
    int index;
    if(id == NULL || table == NULL){
        fprintf(stderr, "Null id or table. find_hash_entry failed\n");
        return NULL;
    }
    index = hash_func(id, table->max_size);
    for(int i = 0; i < table->entry_list_size[index]; i++){
        
        if(strcmp(table->hash_system[index][i]->id, id) == 0)
            return table->hash_system[index][i];
    }
    return NULL;
}

/*
 * -----------------------------------------------------------------------------------------------------------
 * Symbol Table Methods
 * -----------------------------------------------------------------------------------------------------------
 */

/*
 * This will link a sym_tbl to another in a parent/child relation
 * Will return 0 on success
 * Will return -1 for failure
 */
int add_child_sym_tbl(sym_tbl * child, sym_tbl * parent){
    if(child == NULL || parent == NULL){
        fprintf(stderr, "Null child or parent. add_child_sym_tbl failed\n");
        return -1;
    }
    child->parent = parent;
    
    //Realloc crap to deal with
    if(parent->num_childs == parent->max_childs){
        parent->childs = (sym_tbl **)ralloc(parent->childs, parent->max_childs * 2);// Realloc stuff, Need to talk to K9
        parent->max_childs *= 2;
    }
    parent->childs[parent->num_childs++] = child;
    return 0;
}

/*
 * Find tbl_entry given an id
 * Will return address to entry on success
 * Will return NULL for failure
 */
tbl_entry * sym_tbl_find_entry(char * id, sym_tbl * table){
    tbl_entry * ret;
    if(id == NULL || table == NULL){
        fprintf(stderr, "Null id or table. sym_tbl_find_entry failed\n");
        return NULL;
    }
    for(sym_tbl * current = table; current != NULL; current = current->parent){
        if(current != NULL){
            ret = find_hash_entry_id(id, current->tbl);
            if(ret != NULL)
                return ret;
        }
    }
    return NULL;
}
/*
 * Find tbl_entry given an id in current scope only
 * Will return address to entry on success
 * Will return NULL for failure
 */
tbl_entry * sym_tbl_find_entry_scoped(char * id, sym_tbl * table){
    tbl_entry * ret;
    if(id == NULL || table == NULL){
        fprintf(stderr, "Null id or table. sym_tbl_find_entry failed\n");
        return NULL;
    }
    ret = find_hash_entry_id(id, table->tbl);
    return ret;
}

/*
 * Adds a tbl_entry
 * Will return 0 to entry on success
 * Will return -1 for failure
 */
int sym_tbl_add_entry(tbl_entry * entry, sym_tbl * table){
    if(entry == NULL || table == NULL){
        fprintf(stderr, "Null entry or table. sym_tbl_add_entry failed\n");
        return -1;
    }
    return add_hash_entry(entry, table->tbl);
}

/*
 * Given a table and a file name, will attempt to output the sym_tbl to such file
 * Will return 0 on success
 * Will return -1 for failure
 */
int print_sym_tbl_init(sym_tbl * table, char * file_path){
    FILE * file;
    if(file_path == NULL || table == NULL){
        fprintf(stderr, "Null file_path. print_sym_tbl failed\n");
        return -1;
    }
    file = fopen(file_path, "w+");
    if(file == NULL){
        fprintf(stderr, "Null file_path. print_sym_tbl failed\n");
        return -1;
    }
    fprintf(file, "--------------------------------------------------------------------------------------\nSymbol Table Dump\
            \n--------------------------------------------------------------------------------------\n\n");
    print_hash_tbl(table->tbl, file);
    for(int i = 0; i < table->num_childs; i++){
        print_sym_tbl(table->childs[i], file);
    }
    
    fclose(file);
    return 0;
}

/*
 * Given a table and a file stream, will attempt to output the sym_tbl to such file
 * Will return 0 on success
 * Will return -1 for failure
 */
int print_sym_tbl(sym_tbl * table, FILE * file){
    if(file == NULL || table == NULL){
        fprintf(stderr, "Null file stream. print_sym_tbl failed\n");
        return -1;
    }
    fprintf(file,"--------------------------------------------------------------------------------------\nSymbol Table Dump\
            \n--------------------------------------------------------------------------------------\n\n");
    print_hash_tbl(table->tbl, file);
    for(int i = 0; i < table->num_childs; i++){
        print_sym_tbl(table->childs[i], file);
    }
    return 0;
}

/*
 * Given a table and a file stream, will attempt to output the sym_tbl to such file
 * Will return 0 on success
 * Will return -1 for failure
 */
int print_sym_tbl_scoped(sym_tbl * table, FILE * file){
    if(file == NULL || table == NULL){
        fprintf(stderr, "Null file stream. print_sym_tbl failed\n");
        return -1;
    }
    fprintf(file, "\n--------------------------------------------------------------------------------------\nSymbol Table Dump\
            \n--------------------------------------------------------------------------------------\n");
    print_hash_tbl(table->tbl, file);
    return 0;
}


/*
 * Given a table and a file stream, will attempt to output the hash_tbl to such file
 * Will return 0 on success
 * Will return -1 for failure
 */
int print_hash_tbl(hash_tbl * tbl, FILE * file){
    fprintf(file, "\n______________________________________________________________________________________\nHash Table Dump\
            \n______________________________________________________________________________________\n\n");
    for(int i = 0; i < tbl->max_size; i++){
        for(int j = 0; j < tbl->entry_list_size[i]; j++){
            fprintf(file, "[ ID: %s | Line: %d | ", tbl->hash_system[i][j]->id, tbl->hash_system[i][j]->line_num);
            print_type_to_file(tbl->hash_system[i][j]->type_info, file);
            fprintf(file, "]\n");
        }
    }
    return 0;
}

#endif