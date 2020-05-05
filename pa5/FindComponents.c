/*------------------------------------------------|
 |  FindComponents.c
 |  Client File to Graph ADT                      |
 |  By: Milad Farazian                            |
 |-----------------------------------------------*/

#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){

	FILE *in, *out;
	char str[10];
	char* token;

	if(argc !=3){
		printf("Usage: %s <input file> <output file>\n", argv[1]);
	}

	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	if(in==NULL){
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	if(out==NULL){
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}

	fgets(str, 10, in);

	Graph G = newGraph(atoi(str));

	while(fgets(str, 10, in) != NULL){
		token = strtok(str," ");
		int vertex1 = atoi(token);
		token = strtok(NULL, "  ");
		int vertex2 = atoi(token);
		if(vertex1 == 0 && vertex2 == 0){
			break;
		}
		addArc(G, vertex1, vertex2);

	}

	fprintf(out,"Adjacency list representation of G:\n");
	printGraph(out,G);
	fprintf(out,"\n");

	List L = newList();
	for(int i = 1; i <= getOrder(G); i++){
		append(L, i);
	}
	DFS(G,L);

	Graph P = transpose(G);

	DFS(P,L);

	//printList(out, L);

	int SCC = 0;
	int i = 0;

	moveFront(L);
	List K = newList();
	while(index(L) != -1){
		i = get(L);
		if(getParent(P,i) == NIL){
			SCC += 1;
		}
		moveNext(L);
	}

	fprintf(out, "G contains %d strongly connected components:", SCC);

	moveBack(L);
	int count = 1;
	while(index(L) != -1){
		i = get(L);
		prepend(K,i);
		if(getParent(P,i) == NIL){
			fprintf(out, "\nComponent %d: ", count);
			count++;
			printList(out, K);
			clear(K);
		}
		movePrev(L);
	}
}
