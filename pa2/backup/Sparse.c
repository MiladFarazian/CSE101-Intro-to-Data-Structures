//----------------------------------------------------------------------
// Sparse.c
// Sparses input file and displays in output file
// By: Milad Farazian
// CruzID: mfarazia      ID#: 1693852
//----------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Matrix.h"

int main(int argc, char* argv[]){

	int n = 0; int count = 0;
	int lengthA = 0;
	int lengthB = 0;
	FILE *in, *out;
	Matrix A, B, C, D, E, F, G, H, I, J;
	int r = 0; int c = 0; double x = 0;

	if(argc != 3){
		printf("Usage: %s <input file> <output file>\n",argv[1]);
		exit(1);
	}

	in = fopen(argv[1],"r");
	out = fopen(argv[2],"w");
	if(in == NULL){
		printf("Unable to open file %s for reading\n",argv[1]);

	}
	if(out==NULL){
		printf("Unable to open file %s for writing\n",argv[2]);
	}


	fscanf(in,"%d %d %d\n", &n, &lengthA, &lengthB);
	//fprintf(out,"%d %d %d\n",n, lengthA, lengthB);
	A = newMatrix(n);
	B = newMatrix(n);

	//printf("%d",n);

	fscanf(in,"\n");

	for(int i = 1; i<=lengthA; i++){
		fscanf(in,"%d %d %lf", &r, &c, &x);
		//fprintf(out,"changeEntry(A, %d, %d, %1f)\n", r, c, x);
		changeEntry(A, r, c, x);
		//fscanf(in,"\n");
	}

	fscanf(in,"\n");

	for(int i = 1; i<=lengthB; i++){
		fscanf(in,"%d %d %lf", &r, &c, &x);
		//fprintf(out,"changeEntry(B, %d, %d, %1f)\n", r, c, x);
		changeEntry(B, r, c, x);
		//fscanf(in,"\n");
	}

	fclose(in);


	fprintf(out,"A has %d non-zero entries:\n",NNZ(A));
	printMatrix(out,A);
	fprintf(out,"\n");

	fprintf(out,"B has %d non-zero entries:\n",NNZ(B));
	printMatrix(out,B);
	fprintf(out,"\n");

	fprintf(out,"(1.5)*A =\n");
	C = scalarMult(1.5,A);
	printMatrix(out,C);
	fprintf(out,"\n");

	fprintf(out,"A+B =\n");
	D = sum(A,B);
	printMatrix(out,D);
	fprintf(out,"\n");

	fprintf(out,"A+A =\n");
	E = sum(A,A);
	printMatrix(out,E);
	fprintf(out,"\n");

	fprintf(out,"B-A =\n");
	F = diff(B,A);
	printMatrix(out,F);
	fprintf(out,"\n");

	fprintf(out,"A-A =\n");
	G = diff(A,A);
	printMatrix(out, G);
	fprintf(out,"\n");

	fprintf(out,"Transpose(A) =\n");
	H = transpose(A);
	printMatrix(out,H);
	fprintf(out,"\n");

	fprintf(out,"A*B =\n");
	I = product(A,B);
	printMatrix(out,I);
	fprintf(out,"\n");

	fprintf(out,"B*B =\n");
	J = product(B,B);
	printMatrix(out,J);
	fprintf(out,"\n");

	freeMatrix(&A);
	freeMatrix(&B);
	freeMatrix(&C);
	freeMatrix(&D);
	freeMatrix(&E);
	freeMatrix(&F);
	freeMatrix(&G);
	freeMatrix(&H);
	freeMatrix(&I);
	freeMatrix(&J);
	fclose(out);
	return(0);
}
