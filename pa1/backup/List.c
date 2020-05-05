/*---------------------------------------------------------------------------------
 * List.c
 * By: Milad Farazian
 * CruzID: mfarazia ID#: 1693852
 *--------------------------------------------------------------------------------*/

#include<stdio.h>
#include<stdlib.h>
#include"List.h"

//structs --------------------------------------------------------------------------

typedef struct NodeObj{
	int data;
	struct NodeObj* next;
	struct NodeObj* prev;
}NodeObj;

typedef NodeObj* next;

typedef NodeObj* prev;

typedef struct ListObj{
	Node front;
	Node back;
	Node cursor;
	int length;
	int index;
}ListObj;

Node newNode(int data){
	Node N = malloc(sizeof(NodeObj));
	N->data = data;
	N->next = NULL;
	N->prev = NULL;
	return(N);
}

void freeNode(Node* pN){
	if(pN != NULL && *pN != NULL){
		free(*pN);
		*pN = NULL;
	}
}

List newList(void){
	List L;
	L = malloc(sizeof(ListObj));
	L->front = L->back = NULL;
	L->length = 0;
	L->index = -1;
	return(L);
}

void freeList(List* pL){
	if(pL != NULL && *pL != NULL){
		while(length(*pL)>0){
			deleteFront(*pL);
		}
		free(*pL);
		*pL = NULL;
	}
}

// Access Functions ---------------------------------------------------

int length(List L){
	if(L==NULL){
		printf("List Error: calling length() on NULL List reference\n");
		exit(1);
	}
	return(L->length);
}

int index(List L){
	if(L==NULL){
		printf("List Error: calling index() on NULL List reference\n");
		exit(1);
	}
	return(L->index);
}

int front(List L){
	if(L==NULL){
		printf("List Error: calling front() on NULL List reference\n");
		exit(1);
	}
	if(length(L)== 0){
		printf("List Error: calling front() on an empty List\n");
		exit(1);
	}
	return(L->front->data);
}

int back(List L){
	if(L==NULL){
		printf("List Error: calling back() on NULL List reference\n");
		exit(1);
	}
	if(length(L)== 0){
		printf("List Error: calling back() on an empty List\n");
		exit(1);
	}
	return (L->back->data);
}

int get(List L){
	if(L==NULL){
		printf("List Error: calling get() on NULL List reference\n");
		exit(1);
	}
	if(length(L)<=0 || index(L)<0){
		printf("List Error: calling get() on an empty List\n");
		exit(1);
	}
	return(L->cursor->data);
}

int equals(List A, List B){
	int eq = 0;
	Node N = NULL;
	Node M= NULL;

	if(A==NULL||B==NULL){
		printf("List Error: calling equals on a NULL List reference\n");
		exit(1);
	}

	eq = (A->length == B->length);
	N = A->front;
	M = B->front;
	while(eq && N!=NULL){
		eq = (N->data==M->data);
		N = N->next;
		M = M->next;
	}
	return eq;
}

// Manipulation procedures -------------------------------------------------------

void clear(List L){
	if( L==NULL ){
		 printf("List Error: calling clear() on NULL List reference\n");
     		 exit(1);
   	}

   	if(length(L) == 0){
     		 return;
   	}

	while(L->front != NULL){
		deleteFront(L);
	}


}

void moveFront(List L){
	if(L==NULL){
      		printf("List Error: calling moveFront() on NULL List reference\n");
      		exit(1);
   	}

	if(length(L)>0){
		L->cursor = L->front;
		L->index = 0;
	}
}

void moveBack(List L){
	if(L==NULL){
      		printf("List Error: calling moveBack() on NULL List reference\n");
      		exit(1);
   	}

	if(length(L)>0){
		L->cursor = L->back;
		L->index = L->length -1;
	}
}

void movePrev(List L){
	if(L==NULL){
      		printf("List Error: calling movePrev() on NULL List reference\n");
      		exit(1);
   	}

	if(L->cursor == NULL){
		printf("List Error: calling movePrev() on NULL cursor reference\n");
		exit(1);
	}

	if(L->cursor == L->front){
		L->cursor = NULL;
		L->index = -1;
	}else{
		L->cursor = L->cursor->prev;
		L->index--;
	}
}

void moveNext(List L){
	if(L==NULL){
      		printf("List Error: calling moveNext() on NULL List reference\n");
      		exit(1);
   	}

	if(L->cursor == NULL){
		printf("List Error: calling moveNext() on NULL cursor reference\n");
		exit(1);
	}

	if(L->cursor == L->back){
		L->cursor = NULL;
		L->index = -1;
	}else{
		L->cursor = L->cursor->next;
		L->index++;
	}
}

void prepend(List L, int data){
	Node N = newNode(data);

   	if(L==NULL){
      		printf("List Error: calling prepend() on NULL List reference\n");
      		exit(1);
   	}
   	if(length(L) == 0 ) {
      		L->front = L->back = N;
   	}else{
      		L->front->prev = N;
		N->next = L->front;
      		L->front = N;
   	}
   	L->length++;
	L->index++;

}

void append(List L, int data){
	Node N = newNode(data);

   	if(L==NULL ){
      		printf("List Error: calling append() on NULL List reference\n");
      		exit(1);
   	}
   	if(length(L) == 0 ) {
      		L->front = L->back = N;
   	}else{
      		L->back->next = N;
		N->prev = L->back;
      		L->back = N;
   	}
   	L->length++;
}

void insertBefore(List L, int data){
	if(L==NULL ){
		 printf("List Error: calling insertBefore() on NULL List reference\n");
     		 exit(1);
   	}

   	if(length(L) == 0){
     		 printf("List Error: calling insertBefore() on an empty List\n");
     		 exit(1);
	}

	if(index(L)<0){
		printf("List Error: calling insertBefore() on a NULL index\n");
		exit(1);
	}


	if(L->cursor==L->front){
		prepend(L, data);
	}else{
		Node N = newNode(data);
		Node P = L->cursor->prev;
		P->next = N;
		N->prev = P;
		N->next = L->cursor;
		L->cursor->prev = N;

		L->length++;
		L->index++;
	}
}

void insertAfter(List L, int data){
	if(L==NULL ){
		 printf("List Error: calling insertAfter() on NULL List reference\n");
     		 exit(1);
   	}

   	if(length(L) == 0){
     		 printf("List Error: calling insertAfter() on an empty List\n");
     		 exit(1);
	}

	if(index(L)<0){
		printf("List Error: calling insertAfter() on a NULL index\n");
		exit(1);
	}

	if(L->cursor == L->back){
		append(L,data);
	}else{
		Node N = newNode(data);
		Node P = L->cursor->next;
		P->prev = N;
		N->next = P;
		N->prev = L->cursor;
		L->cursor->next = N;

		L->length++;
	}
}

void deleteFront(List L){
	if( L==NULL ){
		 printf("List Error: calling deleteFront() on NULL List reference\n");
     		 exit(1);
   	}

   	if(length(L) == 0){
     		 printf("List Error: calling deleteFront() on an empty List\n");
     		 exit(1);
   	}

  	Node N = L->front;
	//L->front = L->front->next;
	if(length(L)>1) {
    		L->front = L->front->next;
		L->front->prev = NULL;
 	}else{
     		L->front = L->back = NULL;
  	}
   	L->length--;
	L->index--;
   	freeNode(&N);

	if(L->index<-1){
		L->index = -1;
	}

}

void deleteBack(List L){
   	if( L==NULL ){
      		printf("List Error: calling deleteBack()  on NULL List reference\n");
      		exit(1);
   	}
	if(length(L)==0 ){
      		printf("List Error: calling deleteBack() on an empty List\n");
      		exit(1);
   	}

   	Node N = L->back;
	if(length(L) == 2){
		L->back = L->front;
		L->front->next = NULL;
	}else if( length(L)>2 ) {
      		L->back = L->back->prev;
		L->back->next = NULL;
   	}else{
      		L->front = L->back = NULL;
   	}
   	L->length--;
	if(L->index == L->length){
		L->index = -1;
	}
   	freeNode(&N);
}

void delete(List L){
	if( L==NULL ){
		 printf("List Error: calling delete() on NULL List reference\n");
     		 exit(1);
   	}

   	if(length(L) == 0){
     		 printf("List Error: calling delete() on an empty List\n");
     		 exit(1);
	}

	if(index(L)<0){
		printf("List Error: calling delete() on a NULL index\n");
		exit(1);
	}

	if(L->cursor == L->front){
		deleteFront(L);
	}else if(L->cursor == L->back){
		deleteBack(L);
	}else{
		Node P = L->cursor->prev;
		Node N = L->cursor->next;
		P->next = N;
		N->prev = P;
		free(L->cursor);
		L->cursor = NULL;
		L->index = -1;
		L->length--;
	}
}

// Other operations--------------------------------------------------------------------

void printList(FILE* out, List L){
	Node N = NULL;

  	 if( L==NULL ){
   		printf("List Error: calling printList() on NULL List reference\n");
      		exit(1);
   	}

   	for(N = L->front; N != NULL; N = N->next){
      		fprintf(out, "%d ", N->data);
	}
	fprintf(out,"\n");
	freeNode(&N);
}

List copyList(List L){
	List K = newList();

  	if( L==NULL ){
   		printf("List Error: calling copyList() on NULL List reference\n");
      		exit(1);
   	}

   	for(Node N = L->front; N != NULL; N = N->next){
      		append(K,N->data);
	}
	return K;
}
