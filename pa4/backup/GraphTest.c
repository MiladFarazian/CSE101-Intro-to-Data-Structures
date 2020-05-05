
#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
	Graph A = newGraph(6);
	printGraph(stdout,A);

	addEdge(A,1,2);
	addEdge(A,1,3);
	addEdge(A,2,4);
	addEdge(A,2,5);
	addEdge(A,2,6);
	addEdge(A,3,4);
	addEdge(A,4,5);
	addEdge(A,5,6);

	printGraph(stdout, A);

	BFS(A,3);

	//printGraph(stdout,A);

	printf("Source: %d\n", getSource(A));
	printf("Size: %d\n", getSize(A));
	printf("Order: %d\n", getOrder(A));
	printf("Parent: %d\n", getParent(A,5));
	printf("Distance: %d\n", getDist(A,2));

}
