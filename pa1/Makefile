#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 1
#
#       make                   makes Lex
#       make ListClient        makes ListClient
#------------------------------------------------------------------------------
ADT = List
SOURCES = README Makefile $(CSOURCES) List.h
CSOURCES = $(ADT).c Lex.c $(ADT)Client.c

Lex : Lex.o List.o
	gcc -o Lex Lex.o List.o

Lex.o : Lex.c List.h
	gcc -c -std=c99 -Wall Lex.c

ListClient: ListClient.o List.o
	gcc -o ListClient ListClient.o List.o

ListClient.o : ListClient.c List.h
	gcc -c -std=c99 -Wall ListClient.c

List.o : List.c List.h
	gcc -c -std=c99 -Wall List.c

clean :
	rm -f Lex ListClient Lex.o ListClient.o List.o

checksubmit :
	ls  /afs/cats.ucsc.edu/class/cse101-pt.f19/pa1/mfarazia

submit:
	submit  cse101-pt.f19 pa1 $(SOURCES)
