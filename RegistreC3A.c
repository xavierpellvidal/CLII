#include <stdio.h>
#include <string.h>
#include <stdlib.h> /* requerida para malloc y free funciones */
#include "RegistreC3A.h"

/* Amb aquest defines es pot controlar com ha anat la comprovacio de tipus */
#define COMPTIPUS_IGUALS 0				/* Els parametres son iguals */
#define COMPTIPUS_DIF_RED_PRIMER 1		/* diferent tipus, pero es pot adaptar perdent precisio pel primer */
#define COMPTIPUS_DIF_RED_SEGON 2		/* diferent tipus, pero es pot adaptar perdent precisio pel segon */
#define COMPTIPUS_DIF_NO_RED -1			/* diferent tipus i no es pot adaptar */

/* Els IDs estan ordenats de forma ascendent segons la precisio, aixi comparant es podra
veure facilment qui te mes o menys precisio.*/
#define ID_CHAR 1
#define ID_SHORT 2
#define ID_INT 3
#define ID_LONG 4
#define ID_FLOAT 5
#define ID_DOUBLE 6
#define ID_VOID 9

FILE *dFile2;
int countNouTemp = 1;
int sQuad = 1;
int auxCount = 1;


void inicialitzarFit(char* nom){
	char string[20];
	strcpy(string,"");
	sprintf(string, "%s.c3a", nom);
	dFile2 = fopen(string,"w");
}

registre emet(fil fil, registre t){
	t.taula[t.row] = fil;
	t.row ++;
	sQuad++;
	return t;
}

int getSquad(){
	return sQuad;
}

char* nouTemp(){   
	char *nouTemporal = (char*)malloc(5*sizeof(char));
	char *string = (char*)malloc(2*sizeof(char));
	
	sprintf(string,"%d",countNouTemp);
	snprintf(nouTemporal,sizeof(nouTemporal),"%s%s","$t",string);
	countNouTemp++;
	return nouTemporal;
}

void imprimirT(registre t){
	int i = 0;
	fil aux;
	char string[100];
	strcpy(string,"");
	
	for(i=0; i < t.row; i++){
		aux = t.taula[i];
		sprintf(string, "%d - %s\n", auxCount, aux.info);
		auxCount++;
		fprintf(dFile2, string);
	}
	sprintf(string, "\n");
	fprintf(dFile2, string);
	
}

fil inicialitzarFil(fil fil){
	fil.nFila = -1;
	fil.info = (char*)malloc(100*sizeof(char));
	return fil;
}

registre inicialitzarT(registre t){
	int i;
	t.taula = (fil*)malloc(200*sizeof(fil));
	
	for(i = 0; i < 200; i++){
		t.taula[i].nFila = -1;
		t.taula[i].info= (char*)malloc(100*sizeof(char));
	}
	t.row = 0;
	return t;
}

registre esborrarT(registre t){
	int i;
	for(i = 0; i < t.row; i++){
		t.taula[i].nFila = -1;
		t.taula[i].info = (char*)malloc(100*sizeof(char));
	}
	t.row = 0;
	return t;
}

char* obtainCast(int tipus1, int tipus2, int typeCast){
    char t1;
    char t2;
   
    char *cast = (char*)malloc(sizeof(char)*3);
   
    if(tipus1==ID_CHAR)    t1='C';   
    else if(tipus1==ID_SHORT)t1='S';
    else if(tipus1==ID_INT)t1='I';
    else if(tipus1==ID_LONG)t1='L';
    else if(tipus1==ID_FLOAT)t1='F';
    else if(tipus1==ID_DOUBLE)t1='D';
   
    if(tipus2==ID_CHAR)    t2='C';   
    else if(tipus2==ID_SHORT)t2='S';
    else if(tipus2==ID_INT)t2='I';
    else if(tipus2==ID_LONG)t2='L';
    else if(tipus2==ID_FLOAT)t2='F';
    else if(tipus2==ID_DOUBLE)t2='D';
   
    switch (typeCast){
        case COMPTIPUS_DIF_RED_PRIMER:
            sprintf(cast,"%c%s%c",t2,"2",t1);
        break;           
        case COMPTIPUS_DIF_RED_SEGON:
            sprintf(cast,"%c%s%c",t1,"2",t2);
        break;
    }
    return cast;
}


char* obtainOp(char *op, int tipus){
    char t1;
    char *operation = (char*)malloc(sizeof(char)*3);
    char *operator = (char*)malloc(sizeof(char)*4);
  
    if(tipus==ID_CHAR)t1='C';   
    else if(tipus==ID_SHORT)t1='S';
    else if(tipus==ID_INT)t1='I';
    else if(tipus==ID_LONG)t1='L';
    else if(tipus==ID_FLOAT)t1='F';
    else if(tipus==ID_DOUBLE)t1='D';
   
    if(op[0]=='*')    operation="MUL";   
    else if(op[0]=='+')operation="ADD";
    else if(op[0]=='-')operation="SUB";
    else if(op[0]=='%')operation="MOD";
    else if(op[0]=='/')operation="DIV";
       
    sprintf(operator,"%s%c",operation,t1);
    return operator;
}

char* signChange(int tipus){
   char* change = (char*)malloc(sizeof(char)*4);
   sprintf(change,"%s","NULL");
   
   if(tipus==ID_SHORT)sprintf(change,"%s","CHSS");
   else if(tipus==ID_INT)sprintf(change,"%s","CHSI");
   else if(tipus==ID_LONG)sprintf(change,"%s","CHSL");
   else if(tipus==ID_FLOAT)sprintf(change,"%s","CHSF");
   else if(tipus==ID_DOUBLE)sprintf(change,"%s","CHSD");
   
   return change;
}

char* obtainCompare(char *op, int tipus){

       char *comp = (char*)malloc(sizeof(char)*3);
       char t1;
     
	   if(tipus==ID_CHAR)t1='C';  
	   else if(tipus==ID_SHORT)t1='S';
	   else if(tipus==ID_INT)t1='I';
	   else if(tipus==ID_LONG)t1='L';
	   else if(tipus==ID_FLOAT)t1='F';
	   else if(tipus==ID_DOUBLE)t1='D';
       
       if(strcmp (op,"GT") == 0){
               sprintf(comp,"GT%c",t1);
       }else if(strcmp (op,"GE") == 0){
               sprintf(comp,"GE%c",t1);
       }else if(strcmp (op,"LT") == 0){
               sprintf(comp,"LT%c",t1);
       }else if(strcmp (op,"LE") == 0){
               sprintf(comp,"LE%c",t1);
       }else if(strcmp (op,"EQ") == 0){
               sprintf(comp,"EQ");
       }else if(strcmp (op,"NE") == 0){
               sprintf(comp,"NE");
       }
               
       return comp;
}

registre completa(int* llista, int midaLlista, int valor, registre taula){
	int i = 0;
	char* aux = (char*)malloc(sizeof(char)*100);
	
	for(i=0; i<midaLlista; i++){
		sprintf(aux, "%s%d", taula.taula[llista[i]-1].info, valor);
		sprintf(taula.taula[llista[i]-1].info, "%s", aux);
	}
	
	return taula;
}

int* fusiona(int* newList, int* list1, int nList1, int* list2, int nList2){
	int nNewList=0;
	int i=0;
	
	for(i=0;i<nList1;i++){
	       newList[i] = list1[i];
	
	}
	
	nNewList = nList1;
	for(i=0;i<nList2;i++){
	       newList[nNewList] = list2[i];
	       nNewList++;
	}
	       
	return newList;          
}

int* crearllista(int* newList, int value){
	newList[0] = value;
	return newList;
}