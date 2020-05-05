//-----------------------------------------------------------------------------
// BigIntegerTest.c
// Test BigIntegerTest.c's operations and functions
// By: Milad Farazian
// CruzID: mfarazia   ID#: 1693852
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"BigInteger.h"

int main(){
	// test making negative big integers 
	/*BigInteger A = newBigInteger();
	char* str4 = "-111122223333";
	A = stringToBigInteger(str4);
	printBigInteger(stdout,A);

	return 0;
}*/

	BigInteger A = newBigInteger();
	BigInteger B = newBigInteger();
	BigInteger C = newBigInteger();
	BigInteger D = newBigInteger();
	BigInteger E = newBigInteger();
	BigInteger F = newBigInteger();
	BigInteger G = newBigInteger();
	BigInteger H = newBigInteger();
	BigInteger I = newBigInteger();
	BigInteger J = newBigInteger();
	BigInteger K = newBigInteger();
	BigInteger L = newBigInteger();
	BigInteger M = newBigInteger();
	BigInteger N = newBigInteger();




	char* str0 = "100001000001234567890";
	printf("\nPrint: %s\n  ", str0);
	A = stringToBigInteger(str0);
	printBigInteger(stdout,A);


	char* str1 = "+123456789123456789";
	char* str2 = "-123456789123456789";
	B = stringToBigInteger(str1);
	C = stringToBigInteger(str2);
	printf("\nAdd(Test 1):\n");
	printf("  ");
	printBigInteger(stdout, B);
	printf("+ ");
	printBigInteger(stdout,C);
	printf("---------------------------\n ");
	D = sum(B,C);
	printBigInteger(stdout, D);

	
	printf("\nNegation of Sum:\n ");
	negate(D);
	printBigInteger(stdout, D);
	negate(D);


	printf("\nSubtract(Test 1):\n");
	printf("  ");
	printBigInteger(stdout, D);
	printf("- ");
	printBigInteger(stdout,A);
	printf("---------------------------\n  ");
	E = diff(D,A);
	printBigInteger(stdout, E);


	printf("\nCompare Equal BigInts:\n");
	printf("  ");
	printBigInteger(stdout, A);
	printf("= ");
	printBigInteger(stdout,A);
	printf("---------------------------\n  ");
	int comp = compare(A,A);
	if(comp == -1){
		printf("A is less than B\n");
	}else if(comp == 1){
		printf("A is greater than B\n");
	}else{
		printf("BigIntegers are equal\n");
	}

	int result = compare(B, C);
	printf("  result is %d\n", result);
	printf("\n");


	char* str3 = "+111122223333";
	char* str4 = "-111122223333";
	F = stringToBigInteger(str3);
	G = stringToBigInteger(str4);
	printf("\nAdd (Test 2):\n");
	printf("  ");
	printBigInteger(stdout, F);
	printf("+ ");
	printBigInteger(stdout,G);
	printf("---------------------------\n  ");
	add(H,F,G);
	printBigInteger(stdout, H);
	//printf("Sign:%d\n", sign(H));

	char* str6 = "-110122223333";
	K = stringToBigInteger(str6);
	printf("\nAdd(Test 3):\n");
	printf("  ");
	printBigInteger(stdout, F);
	printf("+ ");
	printBigInteger(stdout,K);
	printf("---------------------------\n ");
	L = sum(F,K);
	printBigInteger(stdout, L);
	printf(" Sign:%d\n", sign(L));





	char* str5 = "112122223333";
	I = stringToBigInteger(str5);
	printf("\nSub (Test 4):\n");
	printf("  ");
	printBigInteger(stdout, F);
	printf("- ");
	printBigInteger(stdout,I);
	printf("---------------------------\n ");
	J = diff(F,I);
	printBigInteger(stdout, J);
	printf(" Sign:%d\n", sign(J));

	//G
	char* str7 = "-112122223333";
	M = stringToBigInteger(str7);
	printf("\nDiff (Test 2):\n");
	printf("  ");
	printBigInteger(stdout, G);
	printf("- ");
	printBigInteger(stdout,M);
	printf("---------------------------\n ");
	N = diff(G,M);
	printBigInteger(stdout, N);
	printf(" Sign:%d\n", sign(N));
	




}


