#include <stdio.h>
#include <stdlib.h>

typedef struct fil {
	char *info;
	int nFila;
} fil;
	
typedef struct registre {
	int sQuad;
	fil *taula;
} registre; 

registre emet(fil, registre);
void imprimirT(registre);
fil inicialitzarFil(fil);
registre  inicialitzarT(registre);
void inicialitzarFit();
registre esborrarT(registre);
char* nouTemp();
char* obtainCast(int, int, int);
char* obtainOp(char*, int);
char* signChange(int);
