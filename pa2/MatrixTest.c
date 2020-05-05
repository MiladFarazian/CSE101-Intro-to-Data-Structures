//-----------------------------------------------------------------------------
// MatrixTest.c
// A Test from the Matrix ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Matrix.h"

int main(){
	int n=100000;
	Matrix U = newMatrix(n);
	Matrix T = newMatrix(n);
	Matrix V;
	Matrix A = newMatrix(n);
	Matrix B = newMatrix(n);
	Matrix* pC;
	Matrix* pD;

/*	changeEntry(U,1,1,6);changeEntry(T,1,1,6);
	changeEntry(U,1,2,3);changeEntry(T,1,2,-3);
			     changeEntry(T,1,3,0);
	changeEntry(U,2,1,9);changeEntry(T,2,1,2);
	changeEntry(U,2,3,2);
	changeEntry(U,3,2,4);
	changeEntry(U,3,3,8);*/


  	changeEntry(A, 1, 1, -4);
        changeEntry(A, 1, 2, -2);
        changeEntry(A, 1, 3, 0);
        changeEntry(A, 2, 5, 4);
        changeEntry(A, 2, 1, -2);
        changeEntry(A, 3, 1, 2);
        changeEntry(A, 2, 2, -2);
        changeEntry(A, 3, 3, 0);
        *pC = diff(A, A);
        if (NNZ(*pC) != 0 || NNZ(A) != 6) return 1;
        changeEntry(B, 1, 1, -4);
        changeEntry(B, 1, 2, 0);
        changeEntry(B, 2, 1, 0);
        changeEntry(B, 2, 2, -2);
        changeEntry(B, 2, 4, 2);
        changeEntry(B, 3, 1, 2);
        changeEntry(B, 3, 2, 2);
        changeEntry(B, 7, 8, 5);
        *pD = diff(A, B);
        if (NNZ(*pD) != 6) return 2;
        return 0;

}


