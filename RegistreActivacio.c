#include <stdio.h>
#include <string.h>
#include "RegistreActivacio.h"

FILE *dFile;

void inicialitzarFitxer(char* nom){
	char string[20];
	strcpy(string,"");
	sprintf(string, "%s.ra", nom);
	dFile = fopen(string,"w");
}

taula introduirFila(fila fil, taula t){
	t.registre[t.nFiles] = fil;
	t.nFiles ++;
	return t;
}

void imprimirTaula(taula t, char* nom){
	int i = 0;
	fila aux;
	char string[20];
	
	strcpy(string,"");
	
	sprintf(string, "%s:\n", nom);
	fprintf(dFile, string);
	for(i = 0; i < t.nFiles; i++){
		aux = t.registre[i];
		sprintf(string, "Nom: %s\t\t\t\t Mida: %d\t Offset: %d\t \n", aux.nom, aux.mida, aux.offset);
		fprintf(dFile, string);
	}
	fprintf(dFile, "------------------------------------------------ \n");
}

void inicialitzarFila(fila fil){
	fil.offset = 0;
	fil.mida = 0;
	strcpy(fil.nom, " ");
}

void inicialitzarTaula(taula t){
	t.nFiles = 0;
}

taula esborrarTaula(taula t){
	int i;
	for(i = 0; i < t.nFiles; i++){
		t.registre[i].offset = 0;
		t.registre[i].mida = 0;
		strcpy(t.registre[i].nom, " ");
	}
	t.nFiles = 0;
	return t;
}
