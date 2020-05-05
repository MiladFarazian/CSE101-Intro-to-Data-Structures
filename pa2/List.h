//
// List.h
// Header file for List ADT
//

#ifndef _List_H_INCLUDE_
#define _LIST_H_INCLUDE_

typedef struct ListObj* List;

typedef struct NodeObj* Node;

// Constructors-Destructors ------------------------------------------------------

//newList()
List newList(void);

//freeList()
void freeList(List* pL);

// Access Functions -------------------------------------------------------------

//length()
int length(List L);

//index()
int index(List L);

//front()
void* front(List L);

//back()
void*  back(List L);

//get()
void* get(List L);

//equals()
//int equals(List A, List B);

// Manipulation Procedures -------------------------------------------------------

void clear(List L);

void moveFront(List L);

void moveBack(List L);

void movePrev(List L);

void moveNext(List L);

void prepend(List L, void*  data);

void append(List L, void* data);

void insertBefore(List L, void* data);

void insertAfter(List L, void* data);

void deleteFront(List L);

void deleteBack(List L);

void delete(List L);

// Other Operations ---------------------------------------------------------------

//void printList(FILE* out, List L);

//List copyList(List L);

List concatList(List A, List B);

#endif
