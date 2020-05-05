//--------------------------------------------------------------------------------------
// Lex.c
// By: Milad Farazian
// CruzID: mfarazia ID#: 1693852
//-------------------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"

#define MAX_LEN 160

int main(int argc, char * argv[]){

	int n = 0;
	FILE *in, *out;
	char line[MAX_LEN];

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

	while(fgets(line, MAX_LEN, in)!=NULL){
		n++;
	}

	char strings [n][MAX_LEN];

	fclose(in);

	in = fopen(argv[1],"r");

	int j = 0;
	while(fgets(strings[j], MAX_LEN, in)!=NULL){
		j++;
	}

	List L = newList();

	int q = 0;
	prepend(L,q);
	moveFront(L);
	q++;
	while(q < n && index(L) != -1){
		if(strcmp(strings[q],strings[get(L)])<0){
			insertBefore(L,q);
			moveFront(L);
			q++;
		}else{
			if(get(L)==back(L)){
				insertAfter(L,q);
				moveFront(L);
				q++;
			}else{
				moveNext(L);
			}
		}
	}

	moveFront(L);
	while(index(L) != -1){
		fprintf(out, "%s\n", strings[get(L)]);
		moveNext(L);
	}

	fclose(in);
	fclose(out);
	freeList(&L);

}
