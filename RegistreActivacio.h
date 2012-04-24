#include <stdio.h>
#include <stdlib.h>


typedef struct fila {
	int offset;
	int mida;
	char *nom;
} fila;
	
typedef struct taula {
	int nFiles;
	fila *registre;
} taula; 

taula introduirFila(fila, taula);
void imprimirTaula(taula, char*);
fila inicialitzarFila(fila);
taula inicialitzarTaula(taula);
void inicialitzarFitxer();
taula esborrarTaula(taula);