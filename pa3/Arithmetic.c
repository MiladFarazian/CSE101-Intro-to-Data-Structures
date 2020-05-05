//--------------------------------------------------------------------
//  Arithmetic.c
//  Client for BigInteger ADT
//  By: Milad Farazian
//  CruzID: mfarazia   ID#: 1693852
//--------------------------------------------------------------------

#include<stdio.h>
#include<string.h>
#include"BigInteger.h"

#define MAXCHAR 2000000

int main(int argc, char * argv[]){

	int n = 0;
	FILE *in, *out;
	char str[MAXCHAR];

	if(argc != 3){
		printf("Usage: %s <input file> <output file\n",argv[1]);
		exit(1);
	}

	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	if(in==NULL){
		printf("Unable to open file %s for reading\n",argv[1]);
		exit(1);
	}
	if(out==NULL){
		printf("Unable to open file %s for writing\n",argv[2]);
	}

	BigInteger A = NULL;
	BigInteger B = NULL;

	while(fgets(str, MAXCHAR, in)!=NULL){
		if(n == 1){
			A = stringToBigInteger(str);
		}else if(n == 3){
			B = stringToBigInteger(str);
		}
		n++;
	}


	fclose(in);

	BigInteger TWO = stringToBigInteger("2");
	BigInteger THREE = stringToBigInteger("3");
	BigInteger NINE = stringToBigInteger("9");
	BigInteger SIXTEEN = stringToBigInteger("16");

	//A
	printBigInteger(out,A);
	fprintf(out, "\n");

	//B
	printBigInteger(out,B);
	fprintf(out, "\n");

	//A+B
	BigInteger C = sum(A,B);
	printBigInteger(out, C);
	fprintf(out, "\n");

	//A-B
	BigInteger D = diff(A,B);
	printBigInteger(out, D);
	fprintf(out, "\n");

	//A-A
	BigInteger E = diff(A,A);
	printBigInteger(out, E);
	fprintf(out, "\n");

	//3A-2B
	BigInteger F = prod(A,THREE);
	BigInteger G = prod(B,TWO);
	BigInteger H = diff(F,H);
	printBigInteger(out, H);
	fprintf(out, "\n");

	//AB
	BigInteger I = prod(A,B);
	printBigInteger(out, I);
	fprintf(out, "\n");

	//A*A
	BigInteger J = prod(A,A);
	printBigInteger(out,J);
	fprintf(out, "\n");

	//B*B
	BigInteger K = prod(B,B);
	printBigInteger(out,K);
	fprintf(out, "\n");

	//9A^4+16B^5
	BigInteger L = prod(J,J);
	BigInteger M = prod(NINE, L);

	BigInteger N = prod(K,K);
	BigInteger O = prod(N,B);
	BigInteger P = prod(SIXTEEN,O);

	BigInteger Q = sum(M,P);
	printBigInteger(out,Q);

	fclose(out);

	freeBigInteger(&A);
	freeBigInteger(&B);
	freeBigInteger(&C);
	freeBigInteger(&D);
	freeBigInteger(&E);
	freeBigInteger(&F);
	freeBigInteger(&G);
	freeBigInteger(&H);
	freeBigInteger(&I);
	freeBigInteger(&J);
	freeBigInteger(&K);
	freeBigInteger(&L);
	freeBigInteger(&M);
	freeBigInteger(&N);
	freeBigInteger(&O);
	freeBigInteger(&P);
	freeBigInteger(&Q);
	freeBigInteger(&TWO);
	freeBigInteger(&NINE);
	freeBigInteger(&SIXTEEN);
	freeBigInteger(&THREE);

}
