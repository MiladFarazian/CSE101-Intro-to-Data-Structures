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
	int* distance;
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
	G->distance = malloc((n+1)*sizeof(int));
	for(int i = 1; i <= n; i++){
		G->adjacency[i] = newList();
		G->color[i] = -1;     // white = -1; gray = 0; black = 1;
		G->parent[i] = NIL;   // NIL and INF defined in Graph.h
		G->distance[i] = INF;
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
		free((*pG)->distance);
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

int getSource(Graph G){
	if(G == NULL){
		printNullError("getSource()");
		exit(1);
	}

	//Unsure of return for getSource()
	return G->source;
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

int getDist(Graph G, int u){
	if(G == NULL){
		printNullError("getDist()");
		exit(1);
	}

	if(u < 1 || u > getOrder(G)){
		printf("getDist(): vertex is out of bounds and has no distance\n");
		exit(1);
	}

	return G->distance[u];
}

void getPath(List L, Graph G, int u){
	if(G == NULL){
		printNullError("getPath()");
		exit(1);
	}

	if(u < 1 || u > getOrder(G)){
		printf("getPath(): vertex is out of bounds and has no path\n");
		exit(1);
	}

	if(getSource(G) == NIL){
		printf("getPath(): BFS()  must be called before getPath()\n");
		return;
	}

	if(u == getSource(G)){
		append(L, u);
	}else if(getParent(G,u) == NIL){
		append(L, NIL);
	}else{
		getPath(L, G, getParent(G,u));
		append(L, u);
	}
}

// Manipulation procedures ----------------------------

void makeNull(Graph G){
	if(G == NULL){
		return;
	}

	List L;

	for(int i = 1; i <= getSize(G); i++){
		L = G->adjacency[i];
		clear(L);
	}

	G->edges = 0;
}

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

void BFS(Graph G, int s){
	if(G == NULL){
		printNullError("BFS()");
		exit(1);
	}
	//Get number of vertices
	int vert = getOrder(G);

	for(int i = 1; i <= vert; i++){
		G->color[i] = -1; // Color[x] = white
		G->distance[i] = INF;
		G->parent[i] = NIL;
	}
	G->color[s] = 0; //color[s] = gray
	G->distance[s] = 0;
	G->parent[s] = NIL;
	G->source = s;
	List L = newList();
	append(L,s);
	while(length(L) != 0){
		int i = front(L);  // x = Dequeue(Q)
		deleteFront(L);
		List K = G->adjacency[i];
		moveFront(K);
		while(index(K) != -1){
			int j = get(K);
			if(G->color[j] == -1){
				G->color[j] = 0;
				G->distance[j] = G->distance[i] + 1;
				G->parent[j] = i;
				append(L, j);
				}
			moveNext(K);
		}
		G->color[i] = 1;
	}
	freeList(&L);
}

// Other Operations ----------------------------------------

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
