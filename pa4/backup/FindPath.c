/*------------------------------------------------|
 |  FindPath.c                                    |
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
		addEdge(G, vertex1, vertex2);

	}

	printGraph(out,G);
	fprintf(out,"\n");

	while(fgets(str, 10, in) != NULL){
		token = strtok(str," ");
		int vertex1 = atoi(token);
		token = strtok(NULL, "  ");
		int vertex2 = atoi(token);
		if(vertex1 == 0 && vertex2 == 0){
			break;
		}
		BFS(G,vertex1);
		int dist = getDist(G, vertex2);
		char s[10];
		sprintf(s,"%d",dist);
		if(strcmp(s,"-1") == 0){
			strcpy(s, "infinity");
		}
		List L = newList();
		getPath(L,G,vertex2);

		fprintf(out, "The distance from %d to %d is %s\n", vertex1, vertex2, s);
		if(strcmp(s,"infinity") != 0){
			fprintf(out, "A shortest %d-%d path is: ", vertex1, vertex2);
			printList(out,L);
		}else{
			fprintf(out, "No %d-%d path exists", vertex1, vertex2);

		}
		fprintf(out, "\n\n");
	}


}
