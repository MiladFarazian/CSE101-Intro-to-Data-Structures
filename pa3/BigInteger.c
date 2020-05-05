//----------------------------------------------------------------
// BigInteger.c
// BigInteger ADT Functions and Operations
// By: Milad Farazian
// CruzID: mfarazia   ID#:1693852
//----------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"BigInteger.h"

#define POWER 9
#define BASE 1000000000

typedef struct BigIntegerObj{
	int sign;
	List longs;
}BigIntegerObj;

BigInteger newBigInteger(){
	BigInteger N = malloc(sizeof(BigIntegerObj));
	N->sign = 0;
	N->longs = newList();
	return(N);
}

void freeBigInteger(BigInteger* pN){
	if(pN != NULL && *pN != NULL){
		if((*pN)->longs!=NULL)freeList(&(*pN)->longs);
		free(*pN);
		*pN = NULL;
	}
}

// Access functions------------------------------------------------------

int sign(BigInteger N){
	if(N == NULL){
		printf("BigInteger Error: calling sign() on NULL BigInteger\n");
		exit(1);
	}

	return N->sign;
}

int compare(BigInteger A, BigInteger B){

	if(A==NULL || B==NULL){
		printf("BigInteger Error: calling equals() on NULL BigInteger\n");
		exit(1);
	}

	if(A==B){
		return 0;
	}

	if(A->sign < B->sign){
		return -1;
	}else if(A->sign > B->sign){
		return 1;
	}else if(A->sign == B->sign){
		List L1 = A->longs;
		List L2 = B->longs;
		if(A->sign > 0 && B->sign>0){
			if(length(L1)< length(L2)){
				return -1;
			}else if(length(L1)>length(L2)){
				return 1;
			}else if(length(L1) == length(L2)){
				moveFront(L1);
				moveFront(L2);
				while(index(L1) > -1){
					if(get(L1)< get(L2)){
						return -1;
					}else if(get(L1) > get(L2)){
						return 1;
					}else if(get(L1) == get(L2)){
						//printf("Before moveNext 1+\n");
						moveNext(L1);
						//printf("Before moveNext 2+\n");
						moveNext(L2);
					}
				}
			}
		}else if(A->sign < 0 && B->sign < 0){
			List L1 = A->longs;
			List L2 = B->longs;
			if(length(L1)< length(L2)){
				return 1;
			}else if(length(L1)>length(L2)){
				return -1;
			}else if(length(L1) == length(L2)){
				moveFront(L1);
				moveFront(L2);
				while(index(L1) > -1 && index(L2) >-1){
					if(get(L1)< get(L2)){
						return -1;
					}else if(get(L1) > get(L2)){
						return 1;
					}else if(get(L1) == get(L2)){
						//printf("Before moveNext 1-\n");
						moveNext(L1);
						//printf("Before moveNext 2-\n");
						moveNext(L2);
					}
				}
			}
		}

	}
	return 0;
}

int equals(BigInteger A, BigInteger B){

	if(A==NULL || B==NULL){
		printf("BigInteger Error: calling equals() on NULL BigInteger\n");
		exit(1);
	}

	if(compare(A,B) == 0 && A->sign == B->sign){
		return 1;
	}
	return 0;
}

// Manipulation procedures-------------------------------------------------------

void makeZero(BigInteger N){
	if(N==NULL){
		printf("BigInteger Error: calling makeZero() on NULL BigInteger\n");
		exit(1);
	}

	N->sign = 0;
	clear(N->longs);
}

void negate(BigInteger N){
	if(N==NULL){
		printf("BigInteger Error: calling negate() on NULL BigInteger\n");
		exit(1);
	}

	if(N->sign == 1){
		N->sign = -1;
	}else if(N->sign == -1){
		N->sign = 1;
	}
}

// BigInteger Arithmetic operations------------------------------------------------

BigInteger stringToBigInteger(char* s){

	if(strlen(s)== 0){
		printf("BigInteger Error: calling stringToBigInteger() on empty String\n");
		exit(1);
	}

	BigInteger N = newBigInteger();

	int i = 0;
	long val;
	//char* str=  malloc((POWER+1)*sizeof(char));
	if(s[i]=='-'){
		N->sign = -1;
		i++;
	}else if(s[i] == '+'){
		N->sign = 1;
		i++;
	}else{
		N->sign = 1;
	}

	char* str = malloc((POWER+1)*sizeof(char));
	for(int k = strlen(s)-1; k >= i;){
		int j = POWER - 1;
		if(k < POWER){
			j = k;
		}
		str[j+1] = '\0';
		for(; j >= 0; j--){
			if (k < i){
				for(int x = j; x>= 0; x--){
					str[x] = '0';
				}
				break;
			}
			str[j] = s[k];
			k--;
		}
		val = atol(str);
		prepend(N->longs,val);

	}
	free(str);
	return N;
}

int checkZero(List L){
	moveFront(L);
	while(index(L) != -1){
		if(get(L) != 0){
			return -1;
		}
		moveNext(L);
	}
	return 1;
}

BigInteger copy(BigInteger N){

	if(N==NULL){
		printf("BigInteger Error: calling copy() on NULL BigInteger\n");
		exit(1);
	}

	BigInteger copy = newBigInteger();
	copy->sign = N->sign;
	freeList(&(copy->longs));
	copy->longs = copyList(N->longs);

	return copy;
}


BigInteger addition(BigInteger A, BigInteger B){
	BigInteger S = newBigInteger();
	List L0 = S->longs;
	List L1 = A->longs;
	List L2 = B->longs;
	int carry=0;
	long sum=0;
	moveBack(L0);
	moveBack(L1);
	moveBack(L2);
	while(index(L1)> -1 && index(L2) > -1){
		sum = get(L1) + get(L2) + carry;
		carry = 0;
		if(sum >= BASE){
			carry = 1;
			prepend(L0, (sum - BASE));
		}else{
			prepend(L0,sum);
		}
		movePrev(L1);
		movePrev(L2);
	}

	while(index(L1)>-1){
		sum = get(L1)+carry;
		carry = 0;
		if(sum >= BASE){
			carry = 1;
			prepend(L0, (sum - BASE));
		}else{
			prepend(L0, sum);
		}
		movePrev(L1);
	}

	while(index(L2) >-1){
		sum = get(L2)+carry;
		carry = 0;
		if(sum >= BASE){
			carry = 1;
			prepend(L0, (sum - BASE));
		}else{
			prepend(L0, sum);
		}
		movePrev(L2);
	}
	return S;
}

BigInteger subtraction(BigInteger A, BigInteger B){
	BigInteger D = newBigInteger();
	//D->sign = 1;
	List L0 = D->longs;
	List L1 = A->longs;
	List L2 = B->longs;
	int carry = 0;
	long diff = 0;
	moveBack(L0);
	moveBack(L1);
	moveBack(L2);
	while(index(L1)>-1 && index(L2)>-1){
		diff = get(L1) - get(L2) + carry;
		//printf("diff:%d\n",diff);
		//printf("get(L1) %d get(L2) %d\n", get(L1), get(L2));
		carry = 0;
		if(diff < 0){
			if(index(L1) == 0 && index(L2) == 0){
				diff = diff * -1;
				D->sign = -1;
				prepend(L0, diff);
			}else{
				carry = -1;
				prepend(L0, (diff + BASE));
				D->sign = 1;
			}
		}else{
			prepend(L0, diff);

		}
		movePrev(L1);
		movePrev(L2);
	}

	while(index(L1)>-1){
		diff = get(L1) + carry;
		carry = 0;
		if(diff < 0){
			carry = -1;
			prepend(L0, diff + BASE);
		}else{
			prepend(L0, diff);
		}
		movePrev(L1);
	}

	while(index(L2)>-1){
		diff = get(L2) + carry;
		carry = 0;
		if(diff < 0){
			carry = -1;
			prepend(L0, diff + BASE);
		}else{
			prepend(L0, diff);
		}
		movePrev(L2);
	}
	//printBigInteger(stdout, D);
	return D;
}


void add(BigInteger S, BigInteger A, BigInteger B){
	if(S==NULL || A==NULL || B==NULL){
		printf("BigInteger Error: calling add() on NULL BigInteger\n");
		exit(1);
	}

	if(A->longs == NULL || B->longs == NULL){
		printf("BigInteger Error: calling add() on a NULL List reference\n");
		exit(1);
	}

	BigInteger temp = sum(A,B);
	freeList(&(S->longs));

	S->longs = copyList(temp->longs);
	S->sign = temp->sign;

	freeBigInteger(&temp);

}

BigInteger sum(BigInteger A, BigInteger B){
	if(A==NULL || B==NULL){
		printf("BigInteger Error: calling sum() on NULL BigInteger\n");
		exit(1);
	}

	BigInteger S = NULL;


	if(A->sign == 1 && B->sign == 1){
		S = addition(A,B);
		S->sign = 1;
	}else if(A->sign == -1 && B->sign == 1){
		S = subtraction(B,A);
		//printf("%d\n", compare(A,B));
		negate(A);
		if(checkZero(S->longs) ==1){
			S->sign = 0;
		}else if(compare(A,B) == -1){
			S->sign = 1;
		}else if(compare(A,B) == 1){
			S->sign = -1;
		}
		negate(A);
	}else if(A->sign == 1 && B->sign == -1){
		S = subtraction(A,B);
		//printList(stdout, S->longs);
		//printf("HERE!!!!!!!!!!!!!!!!!!!!\n");
		negate(B);
		//printf("We're in this case");
		if(checkZero(S->longs)==1){
			S->sign = 0;
		}else if(compare(A,B)== 1){
			S->sign = 1;
		}else if(compare(A,B) == -1){
			S->sign = -1;
		}
		negate(B);
		//printf("S->sign: %d\n", S->sign);

	}else if(A->sign == 0){
		S = copy(B);
	}else if(B->sign == 0){
		S = copy(A);
	}else if(A->sign == -1 && B->sign == -1){
		S = addition(A,B);
		S->sign = -1;
	}

	//printBigInteger(stdout, S);
	return S;
}


void subtract(BigInteger D, BigInteger A, BigInteger B){
	if(D==NULL || A==NULL || B==NULL){
		printf("BigInteger Error: calling subtract() on NULL BigInteger\n");
		exit(1);
	}

	if(A->longs == NULL || B->longs == NULL){
		printf("BigInteger Error: calling subtract() on a NULL List reference\n");
		exit(1);
	}

	BigInteger temp = diff(A,B);
	freeList(&(D->longs));

	D->longs = copyList(temp->longs);
	D->sign = temp->sign;

	freeBigInteger(&temp);
}

BigInteger diff(BigInteger A, BigInteger B){
	if(A==NULL || B==NULL){
		printf("BigInteger Error: calling diff() on NULL BigInteger\n");
		exit(1);
	}

	BigInteger D = NULL;

	if(&A == &B){
		D = newBigInteger();
		return D;
	}


	if(A->sign == 1 && B->sign == 1){
		D = subtraction(A,B);
		if(checkZero(D->longs)== 1){
			D->sign = 0;
		}else if(compare(A,B) == -1){
			D->sign = -1;
		}else if(compare(A,B) == 1){
			D->sign = 1;
		}
	}else if(A->sign == -1 && B->sign == 1){
		D = addition(B,A);
		D->sign = -1;
	}else if(A->sign == 1 && B->sign == -1){
		D = addition(A,B);
		D->sign = 1;
	}else if(A->sign == 0){
		D = copy(B);
		negate(D);
	}else if(B->sign == 0){
		D = copy(A);
	}else if(A->sign == -1 && B->sign == -1){
		D = subtraction(A,B);
		negate(A);
		negate(B);
		if(checkZero(D->longs)==1){
			D->sign = 0;
		}else if(compare(A,B) == -1){
			D->sign = 1;
		}else if(compare(A,B) == 1){
			D->sign = -1;
		}
		negate(A);
		negate(B);

	}

	return D;

}

BigInteger multiplication(BigInteger A, BigInteger B){
	BigInteger P = newBigInteger();
	List L0 = P->longs;
	List L1 = A->longs;
	List L2 = B->longs;
	for(int i = 0; i < (length(L1)+length(L2)-1); i++){
		prepend(L0, 0);
	}
	long carry = 0;
	long product = 0;
	moveBack(L0);
	moveBack(L1);
	moveBack(L2);
	if(length(L2) > length(L1)){
		P = multiplication(B,A);
	}else{
		while(index(L2)>-1){
			long M2 = get(L2);
			while(index(L1)>-1){
				moveBack(L0);
				while(index(L0) != (index(L1)+index(L2))){
					movePrev(L0);
				}
				long M1 = get(L1);
				product = (M1 * M2) + carry + get(L0) ;
				carry = 0;
				carry = product/BASE;
				product = product%BASE;
				set(L0, product);
				movePrev(L1);
			}
			movePrev(L2);

		}

		if(carry != 0){
			prepend(L0, carry);
		}
	}
	return P;
}


void multiply(BigInteger P, BigInteger A, BigInteger B){
	if(P==NULL || A==NULL || B==NULL){
		printf("BigInteger Error: calling multiply() on NULL BigInteger\n");
		exit(1);
	}

	if(A->longs == NULL || B->longs == NULL){
		printf("BigInteger Error: calling multiply() on a NULL List reference\n");
		exit(1);
	}

	BigInteger temp = prod(A,B);
	freeList(&(P->longs));

	P->longs = copyList(temp->longs);
	P->sign = temp->sign;

	freeBigInteger(&temp);
}


BigInteger prod(BigInteger A, BigInteger B){
	if(A==NULL || B==NULL){
		printf("BigInteger Error: calling prod() on a NULL BigInteger\n");
		exit(1);
	}

	BigInteger P = newBigInteger();

	if(A->sign == B->sign){
		P = multiplication(A,B);
		P->sign = 1;
	}else if((A->sign == 1 && B->sign == -1) || (A->sign == -1 && B->sign == 1)){
		P = multiplication(A,B);
		P->sign = -1;
	}else if (A->sign == 0 || B->sign){
		makeZero(P);
	}

	return P;
}

// Other operations

void printBigInteger(FILE* out, BigInteger N){
	//printf("Testing pbi");
	int tenMult = 1;

	if(N->longs == NULL){
		printf("BigInteger Error: calling printBigInteger() on NULL List reference");
		exit(1);
	}

	List L = N->longs;
	if(N->sign == -1){
		fprintf(out, "-");
	}
	//else if (N->sign == 1){
	//	fprintf(out,"+");
	//}


	moveFront(L);
	while(length(L) != 0 && get(L) == 0){
		deleteFront(L);
		moveFront(L);
	}

	if (index(L) > -1){
		fprintf(out, "%ld", get(L));
		moveNext(L);
	}

	if (length(L) == 0){
		fprintf(out, "0");
	}

	while(index(L)>-1){
		tenMult = BASE;
		for(int j = 1; j < POWER; j++){
			if(get(L) < tenMult && index(L) != -1){
				fprintf(out, "0");
				tenMult = tenMult/10;
			}else{
				break;
			}
		}
		fprintf(out, "%ld", get(L));
		moveNext(L);
	}
	fprintf(out, "\n");
}
