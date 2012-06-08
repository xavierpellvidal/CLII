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

void imprimirTaula(taula t, char* nom, int nparams){
	int i = 0;
	fila aux;
	char string[100];
	
	strcpy(string,"");
	
	sprintf(string, "%s:\n", nom);
	fprintf(dFile, string);
	if(nparams > 0){
		fprintf(dFile, "Paràmetres de la funció: \n");
		for(i = 0; i < nparams; i++){
			aux = t.registre[i];
			sprintf(string, "\tNom: %s\t\t\t\t Mida: %d\t Offset: %d\t \n", aux.nom, aux.mida, aux.offset);
			fprintf(dFile, string);
		}
	}
	
	fprintf(dFile, "Variables locals de la funció: \n");
	
	for(i=i; i < t.nFiles; i++){
		aux = t.registre[i];
		sprintf(string, "\tNom: %s\t\t\t\t Mida: %d\t Offset: %d\t \n", aux.nom, aux.mida, aux.offset);
		fprintf(dFile, string);
	}
	fprintf(dFile, "------------------------------------------------ \n");
}

fila inicialitzarFila(fila fil){
	fil.offset = 990;
	fil.mida = 0;
	fil.nom = (char*)malloc(20*sizeof(char));
	
	return fil;
}

taula inicialitzarTaula(taula t){
	int i;
	
	t.registre = (fila*)malloc(100*sizeof(fila));
	
	for(i = 0; i < 100; i++){
		t.registre[i].offset = 0;
		t.registre[i].mida = 0;
		t.registre[i].nom = (char*)malloc(20*sizeof(char));
	}
	t.nFiles = 0;
	
	return t;
}

taula esborrarTaula(taula t){
	int i;
	for(i = 0; i < t.nFiles; i++){
		t.registre[i].offset = 0;
		t.registre[i].mida = 0;
		t.registre[i].nom = (char*)malloc(20*sizeof(char));
	}
	t.nFiles = 0;
	return t;
}
