/*-------------------------------------------|
 |  Graph.c                                  |
 |  Graph ADT Acess Functions & Operations   |
 |  By: Milad Farazian                       |
 |------------------------------------------*/

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

typedef struct GraphObj{
	List* adjacency;
	int* color;
	int* parent;
	int* discover;
	int* finish;
	int vertices; // = order
	int edges;    // = size
	int source;
}GraphObj;

Graph newGraph(int n){
	Graph G = malloc(sizeof(GraphObj));

	//Initialize all elements for BFS
	G->adjacency = malloc((n+1)*sizeof(List));
	G->color = malloc((n+1)*sizeof(int));
	G->parent = malloc((n+1)*sizeof(int));
	G->discover = malloc((n+1)*sizeof(int));
	G->finish = malloc((n+1)*sizeof(int));
	for(int i = 1; i <= n; i++){
		G->adjacency[i] = newList();
		G->color[i] = -1;     // white = -1; gray = 0; black = 1;
		G->parent[i] = NIL;   // NIL and INF defined in Graph.h
		G->discover[i] = UNDEF;
		G->finish[i] = UNDEF;
	}
	G->vertices = n;
	G->edges = 0;
	G->source = NIL;
	return(G);
}

void freeGraph(Graph* pG){
	if(pG != NULL && *pG != NULL){
		for(int i = getOrder(*pG); i>=1; i--){
			freeList(&(*pG)->adjacency[i]);
		}
		free((*pG)->adjacency);
		free((*pG)->color);
		free((*pG)->parent);
		free((*pG)->discover);
		free((*pG)->finish);
		free(*pG);
		*pG = NULL;
	}
}

// Access Functions ------------------------
void printNullError(char* s){
	printf("Graph Error: calling %s on a NULL Graph reference\n", s);
}


int getOrder(Graph G){
	if(G == NULL){
		printNullError("getOrder()");
		exit(1);
	}
	return G->vertices;
}

int getSize(Graph G){
	if(G == NULL){
		printNullError("getSize()");
		exit(1);
	}
	return G->edges;
}

int getParent(Graph G, int u){
	if(G == NULL){
		printNullError("getParent()");
		exit(1);
	}

	if(u < 1 || u > getOrder(G)){
		printf("getParent(): vertex is out of bounds and has no parent\n");
		exit(1);
	}

	return G->parent[u];
}

int getDiscover(Graph G, int u){
	if(G == NULL){
		printNullError("getDiscover()");
		exit(1);
	}

	if(u < 1 || u > getOrder(G)){
		printf("getDiscover(): vertex is out of bounds and has no distance\n");
		exit(1);
	}

	return G->discover[u];
}

int getFinish(Graph G, int u){
	if(G == NULL){
		printNullError("getFinish()");
		exit(1);
	}

	if(u < 1 || u > getOrder(G)){
		printf("getFinish(): vertex is out of bounds and has no distance\n");
		exit(1);
	}

	return G->finish[u];
}

// Manipulation procedures ----------------------------

void insertOrdered(List L ,int v){
	int i = 0;
	if(length(L) == 0){
		append(L,v);
		return;
	}
	moveFront(L);
	while(index(L) != -1){
		i = get(L);
		if(v < i){
			insertBefore(L,v);
			return;
		}
		moveNext(L);
	}
	append(L,v);
}

void addArc(Graph G, int u, int v){
	if(G == NULL){
		printNullError("addArc()");
		exit(1);
	}

	if(u < 1 || v < 1 || u > getOrder(G) || v > getOrder(G)){
		printf("addArc(): u and/or v are not in the range [1,getOrder(G)]\n");
		exit(1);
	}

	List L1 = G->adjacency[u];
	insertOrdered(L1,v);

	G->edges++;
}


void addEdge(Graph G, int u, int v){
	if(G == NULL){
		printNullError("addEdge()");
		exit(1);
	}

	if(u < 1 || v < 1 || u > getOrder(G) || v > getOrder(G)){
		printf("addEdge(): u and/or v are not in the range [1,getOrder(G)]\n");
		exit(1);
	}

	List L1 = G->adjacency[u];
	insertOrdered(L1,v);

	List L2 = G->adjacency[v];
	insertOrdered(L2,u);

	G->edges++;
}

void Visit(Graph G, List S, int i, int* t){
	G->discover[i] = ++(*t);
	G->color[i] = GRAY;

	List adj = G->adjacency[i];
	moveFront(adj);
	while(index(adj) != -1){
		int j = get(adj);
		if(G->color[j] == WHITE){
			G->parent[j] = i;
			Visit(G, S, j, t);
		}
		moveNext(adj);
	}

	G->color[i] = BLACK;
	G->finish[i] = ++(*t);
	prepend(S,i);

}

void DFS(Graph G, List S){
	if(G == NULL){
		printNullError("DFS()");
		exit(1);
	}

	if(length(S) != getOrder(G)){
		printf("DFS(): length of S does not equal order of G\n");
		exit(1);
	}

	//Get number of vertices
	int vert = getOrder(G);

	for(int i = 1; i <= vert; i++){
		G->color[i] = WHITE; // WHITE = -1
		G->discover[i] = UNDEF;
		G->finish[i] = UNDEF;
		G->parent[i] = NIL;
	}

	moveFront(S);
	int t = 0;
	int i = 0;

	while(index(S) != -1){
		i = get(S);
		if(G->color[i] == WHITE){
			Visit(G, S, i, &t);
		}
		moveNext(S);
	}

	int s = length(S)/2;
	while(s > 0){
		deleteBack(S);
		s--;
	}
}

// Other Operations ----------------------------------------

Graph transpose(Graph G){
	if(G == NULL){
		printNullError("transpose()");
		exit(1);
	}

	Graph P = newGraph(getOrder(G));
	for(int i = 1; i <= getOrder(G); i++){
		List L = G->adjacency[i];
		moveFront(L);
		while(index(L) != -1){
			int j = get(L);
			addArc(P,j,i);
			moveNext(L);
		}
	}
	return P;
}

Graph copyGraph(Graph G){
		if(G == NULL){
		printNullError("copyGraph()");
		exit(1);
	}

	Graph P = newGraph(getOrder(G));
	for(int i = 1; i <= getOrder(G); i++){
		List L = G->adjacency[i];
		moveFront(L);
		while(index(L) != -1){
			int j = get(L);
			addArc(P,i,j);
			moveNext(L);
		}
	}
	return P;

}

void printGraph(FILE* out, Graph G){
	if(G == NULL){
		printNullError("printGraph()");
		exit(1);
	}

	for(int i = 1; i<= getOrder(G); i++){
		List L = G->adjacency[i];
		fprintf(out, "%d: ", i);
		printList(out,L);
		fprintf(out, "\n");
	}
}
