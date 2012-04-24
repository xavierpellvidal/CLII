all : flex bison gcc
	
flex:
	flex -n -o lex.yy.c Prac1.l
	
bison:
	bison -d -v -o gramaticay.tab.c gramatica.y
	
gcc:		
	gcc -o prac1 -ansi -Wall -g lex.yy.c gramaticay.tab.c main.c RegistreActivacio.c symtab.c -lc -ly -lfl
	
clean : 
	rm -f lex.yy.c Prac1
