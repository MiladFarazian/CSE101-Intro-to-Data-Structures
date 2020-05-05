//----------------------------------------------------------------------
// ListTest.c
// Client for Testing List.c
// By: Milad Farazian
// CruzID: mfarazia   ID#: 1693852
//----------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"List.h"

int main(int argc, char* argv[]){

	List A = newList();
	List B = newList();
	List C = NULL;
	long i;

	for(i=3000000; i<=3000040; i++){
		append(A,i);
		prepend(B,i);
	}

	printList(stdout, A);
	printf("\n");
	printList(stdout, B);
	printf("\n");

	for(moveFront(A); index(A)>= 0; moveNext(A)){
		printf("%ld ", get(A));
	}
	printf("\n");
	for(moveBack(B); index(B)>=0; movePrev(B)){
		printf("%ld ", get(B));
	}
	printf("\n");

	C = copyList(A);
	printf("%s\n", equals(A,B)?"true":"false");
	printf("%s\n", equals(B,C)?"true":"false");
	printf("%s\n", equals(C,A)?"true":"false");


	moveFront(A);
	for(i=3000000; i<3000010; i++){
		moveNext(A);
	}
	insertBefore(A,-1);
	for(i=3000000; i<3000018; i++){
		moveNext(A);
	}
	insertAfter(A,-2);
	for(i=3000000; i<3000010; i++){
		movePrev(A);
	}
	delete(A);
	printList(stdout,A);
	printf("\n");
	printf("%d\n",length(A));
	clear(A);
	printf("%d\n",length(A));

	freeList(&A);
	freeList(&B);
	freeList(&C);

	return(0);
}
