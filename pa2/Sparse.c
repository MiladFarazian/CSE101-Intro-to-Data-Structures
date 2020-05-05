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

	int n = 0;
	FILE *in, *out;

	if(argc != 3){
		printf("Usage: %s <input file> <output file>\n",argv[1]);
		exit(1);
	}

	in = fopen(argv[i],"r");
	out = fopen(argv[2],"w");
	if(in == NULL){
		printf("Unable to pen file %s for reading\n",argv[1]);

	}
	if(out==NULL){
		printf("Unable to pen file %s for writing\n,argv[2]");
	}

	while(fgets(line,?, in)!==NULL){
		n++;
	}

}
