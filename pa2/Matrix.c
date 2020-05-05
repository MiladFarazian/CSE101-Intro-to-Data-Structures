#include<stdio.h>
#include<stdlib.h>
#include"Matrix.h"
#include"List.h"

//structs --------------------------------------------------------------------------

typedef struct EntryObj{
	int column;
	double data;
}EntryObj;

typedef struct MatrixObj{
	List* row;
	int size;
	int nnz;
}MatrixObj;

Entry newEntry(int col, double d){
	Entry E = malloc(sizeof(EntryObj));
	E->column = col;
	E->data = d;
	return(E);
}

void freeEntry(Entry* pE){
	if(pE != NULL && *pE != NULL){
		free(*pE);
		*pE=NULL;
	}
}

Matrix newMatrix(int n){
	Matrix M;
	M = malloc(sizeof(MatrixObj));
	M->size = n;
	M->nnz = 0;
	M->row = malloc((n+1)*sizeof(List));
	for(int i= 0; i <= n; i++ ){
		M->row[i] = newList();
	}
	return(M);
}

void freeMatrix(Matrix* pM){
	if(pM != NULL && *pM != NULL){
		for(int i = size(*pM); i>=0; i--){
			freeList(&(*pM)->row[i]);
		}
		free((*pM) -> row);
		free(*pM);
		*pM = NULL;
	}
}

// Access Functions ----------------------------------------------------------------

int size(Matrix M){
	if(M == NULL){
		printf("Matrix Error: calling size() on a NULL Matrix reference\n");
		exit(1);
	}
	return M->size;
}

int NNZ(Matrix M){
	if(M == NULL){
		printf("Matrix Error: calling NNZ() on a NULL MAtrix reference\n");
		exit(1);
	}
	return M->nnz;
}

int equals(Matrix A, Matrix B){

	if(A == NULL || B == NULL){
		printf("Matrix Error: calling equals on a NULL Matrix reference\n");
		exit(1);
	}

	if(size(A) != size(B) || NNZ(A) != NNZ(B)){
		return 0;
	}


	if(A==B){
		return 1;
	}

	int i=1;
	Entry E1, E2;

	while(i<=size(A)){
		List L1 = A->row[i];
		List L2 = B->row[i];
		moveFront(L1);
		moveFront(L2);
		while(index(L1) != -1 && index(L2) != -1){
			E1 = (Entry)get(L1);
			E2 = (Entry)get(L2);
			if((E1->column == E2->column) && (E1->data == E2->data)){
				moveNext(L1);
				moveNext(L2);
			}else{
				return 0;
			}
		}
		if(index(L1) == -1 && index(L2)== -1){
			i++;
		}else{
			return 0;
		}
	}
	return 1;
}

//Works like a clear
void makeZero(Matrix M){
	if(M == NULL){
		printf("Matrix Error: calling makeZero on a NULL Matrix reference\n");
		exit(1);
	}

	int i=1;
	while(i<=size(M)){
		clear(M->row[i]);
		i++;
	}

	M->nnz = 0;
}

void changeEntry(Matrix M, int i, int j, double x){
	//printf("Called with i %d j %d x %f\n", i,j,x);
	if(M == NULL){
		printf("Matrix Error: calling changeEntry on a NULL Matrix reference\n");
		exit(1);
	}

	if(i<1 || i>size(M)){
		printf("Matrix Error: Value of i does not work within 1<=i<=size(M)\n");
		exit(1);
	}

	if(j<1 || j>size(M)){
		printf("Matrix Error: Value of j does not work within 1<=j<=size(M)\n");
		exit(1);
	}

	int q = 0;
	Entry E = NULL;
	List L = M->row[i];

	moveFront(L);

	while(index(L) >= 0 && q == 0){
		E = (Entry) get(L);
		if(E->column >= (j)){
			q = 1;
			break;
		}
		moveNext(L);
	}

	if(index(L) == -1 ){
		if((x+1) > 0 && (x-1) < 0){
//		if (x == 0){

		}else{
			append(L,newEntry(j,x));
			M->nnz++;

		}

	}else if(E->column > j && x!=0){
		insertBefore(L,newEntry(j,x));
		M->nnz++;

	}else if(E->column == j){
		if(x == 0){
			delete(M->row[i]);
			M->nnz--;
		}else{
			E->data = x;
		}
	}
}

// Matrix Arithmetic Operations ---------------------------------------------------------

Matrix copy(Matrix A){
	if(A == NULL){
		printf("Matrix Error: calling copy on a NULL Matrix reference\n");
		exit(1);
	}

	Matrix copy = newMatrix(size(A));
	Entry E;
	for(int i = 1; i <= size(A); i++){
		List L = A->row[i];
		for(moveFront(L); index(L) > -1; moveNext(L)){
			E = (Entry)get(L);
			changeEntry(copy, i, E->column, E->data);

		}
	}
	copy->nnz = NNZ(A);
	return copy;

}

Matrix transpose(Matrix A){
	if(A == NULL){
		printf("Matrix Error: calling transpose on a NULL Matrix reference\n");
		exit(1);
	}

	Matrix transpose = newMatrix(size(A));
	Entry E;
	for(int i = 1; i<=size(A); i++){
		List L = A->row[i];
		moveFront(L);

		while(index(L)> -1){
			E = (Entry)get(L);
			changeEntry(transpose,E->column,i,E->data);
			moveNext(L);
		}
	}
	transpose->nnz = A->nnz;
	return transpose;
}

Matrix scalarMult(double x, Matrix A){
	if(A == NULL){
		printf("Matrix Error: calling scalarMult on a NULL Matrix reference\n");
		exit(1);
	}

	Entry E;
	Matrix mult = copy(A);
	List L;

	for(int i = 1; i <= size(A) ;++i){
		L =A->row[i];
		moveFront(L);
		while(index(L) !=  -1){
			E = (Entry)get(L);
			changeEntry(mult, i, E->column, (x * E->data));
			moveNext(L);
		}
	}
	return mult;
}


Matrix sum(Matrix A, Matrix B){
	if(A == NULL || B == NULL){
		printf("Matrix Error: calling sum on a NULL Matrix reference\n");
		exit(1);
	}

	if(size(A) != size(B)){
		printf("Matrix Error: calling sum on different sized Matrices\n");
		exit(1);
	}

	//printf("sum\n");
	Matrix M; // = newMatrix(size(A));
	List L1;
	List L2;
	Entry E1;
	Entry E2;
	double x;
	if(equals(A,B) == 1){
		//printf("inside if\n");
		M = scalarMult(2,A);
		return M;
	}
	for(int i = 1; i<size(A);i++){
		M = newMatrix(size(A));
		L1 = A->row[i];
		L2 = B->row[i];
		if(length(L1) == 0 && length(L2) != 0){
			moveFront(L2);
			while(index(L2) != -1){
				E2 = (Entry)get(L2);
				changeEntry(M,i,E2->column,E2->data);
				moveNext(L2);
			}
		}
		else if(length(L1) != 0 && length(L2) == 0){
			moveFront(L1);
			while(index(L1) != -1){
				E1 = (Entry)get(L1);
				changeEntry(M,i,E1->column,E1->data);
				moveNext(L1);
			}

		}else if(length(L1) !=0 && length(L2) !=0){
			moveFront(L1);
			moveFront(L2);
			while(index(L1) != -1 && index(L2) != -1){
				E1 = (Entry)get(L1);
				E2 = (Entry)get(L2);
				if(E1->column == E2->column){
					x = E1->data + E2->data;
					changeEntry(M,i,E1->column,x);
					moveNext(L1);
					moveNext(L2);
				}else if(E1->column < E2->column){
					changeEntry(M, i, E1->column,E1->data);
					moveNext(L1);
				}else if(E1->column > E2->column){
					changeEntry(M, i, E2->column, E2->data);
					moveNext(L2);
				}
			}

			while(index(L1) != -1){
				E1 = (Entry)get(L1);
				changeEntry(M,i,E1->column,E1->data);
				moveNext(L1);
			}

			while(index(L2) != -1){
				E2 = (Entry)get(L2);
				changeEntry(M,i,E2->column,E2->data);
				moveNext(L2);
			}
		}
	}
	return M;
}

Matrix diff(Matrix A, Matrix B){
	if(A == NULL || B == NULL){
		printf("Matrix Error: calling diff on a NULL Matrix reference\n");
		exit(1);
	}

	if(size(A) != size(B)){
		printf("Matrix Error: calling diff on different sized Matrices\n");
		exit(1);
	}
	//Matrix M = newMatrix(size(A));
	Matrix M;

	if(equals(A,B) == 1){
		M = newMatrix(size(A));
		makeZero(M);
	}else{
		Matrix negB = scalarMult(-1, B);
		M = sum(A, negB);
		freeMatrix(&negB);
	}
	return M;
}

double dot(List A, List B){
	double x;
	moveFront(A);
	moveFront(B);
	Entry E1;
	Entry E2;
	while(index(A) >= 0 && index(B) >= 0){
		E1 = (Entry)get(A);
		E2 = (Entry)get(B);
		if(E1->column <  E2->column){
			moveNext(A);
		}else if(E1->column > E2->column){
			moveNext(B);
		}else{
			x += (E1->data * E2->data);
			moveNext(A);
			moveNext(B);
		}
	}
	return x;
}

Matrix product(Matrix A, Matrix B){
	//printf("product");
	if(A == NULL||B == NULL){
		printf("Matrix Error: calling product on a NULL Matrix reference\n");
		exit(1);
	}

	if(size(A) != size(B)){
		printf("Matrix Error: calling product on different sized Matrices\n");
		exit(1);
	}

	//printf("product");
	Matrix M1 = newMatrix(size(A));
	Matrix M2 = transpose(B);
	double d;

	for(int i=1; i <= size(A); i++){
		if(length(A->row[i])!= 0){
			for(int j=1; j <= size(A); j++){
				if(length(M2->row[j])!=0){
					d = dot(A->row[i],M2->row[j]);
					changeEntry(M1, i, j, d);
				}
			}
		}
	}
	freeMatrix(&M2);
	return M1;
}

void printMatrix(FILE* out, Matrix M){
	List L = NULL;
	Entry E = NULL;

	if(M ==NULL){
		printf("Matrix Error: calling printMatrix() on NULL Matrix reference\n");
		exit(1);
	}

	for(int i = 1;i<=size(M);i++){
		L = M->row[i];
		if(length(L) > 0){
			moveFront(L);
			fprintf(out,"%d:",i);
			while(index(L) >= 0){
				E = (Entry)get(L);
				fprintf(out,"(%d, %.1f) ",E->column, E->data);
				moveNext(L);
			}
			fprintf(out,"\n");
		}
	}
}
