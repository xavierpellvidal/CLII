/***************** COMPILADORS I *******************/
/*
	Pràctica 1: ANALITZADOR LÈXIC
	Membres: Bernat Loscos i Xavier Pell
*/
/***************************************************/

%{
#include <stdio.h>
#include "gramaticay.tab.h"
#include "symtab.h"

#define ID_TYPEDEF 11
#define UNDEF -1

extern FILE *yyin;

/*Files i columnes per saber on tenim cada token*/
int rows=1;     
int columns=1; 
char string[100];

int checkReservedTokens();
int checkReservedOperators();
void clear_string(char *,char *);
int check_type();

/*Ens guardem la llargada del yytext llegit anteriorment per poder tractar els tabuladors*/
int lastyyleng=0;

%}

/*Declaracions per a trobar els comentaris*/
comment1 ("/*")
comment11 ("*/")
comment2 ("//")

/*
word, per reconèixer tots els caràcters del alfabet

digits, per reconèixer tots els digits del 0 al 9

simbols, conté tots els simbols del codi ascii

operator, conté els simbols que poden anar aparellats al nostre llenguatge
*/
/* Hem modificat "-" per \- ja no de la primera forma no funciona */

word	[a-zA-Z]	

digits 	[0-9]		

simbols [!#-&(-\+\-\/:-\<\>-@\[-`\{-~]		

opespecial [,.]

operator ["+"\-"="&"">""<""!""|""*""/""%"]		

/*
space, per identificar espais
tabulate, per identificar tabuladors
enter, per identificar salts de linea de dos tipus, els \r\n o els \n
*/

space [ ]
tabulate[\t]
enter(\r\n|\n)



/*
Definim dos condicions exclusives, on COMMNET1 tractarà els comentaris de la declaració de 
comment1 i comment11

I COMMENT2 els comentaris de la declaració de comment2

*/
%X COMMENT1
%X COMMENT2

%%

{comment1}	{columns = 1; BEGIN COMMENT1;}
{comment2}	{columns = 1; BEGIN COMMENT2;}


(\"({word}|{digits}|{simbols}|{space}|{tabulate})*\")	{columns=columns+yyleng;
														lastyyleng=yyleng;
														
														clear_string(yytext,string);
																											
														yylval.ident.lexema = (char *)malloc(sizeof(char)*strlen(string));
														strncpy(yylval.ident.lexema,string,strlen(string));
														yylval.ident.lenght = strlen(string);
														yylval.ident.rows = rows;
														yylval.ident.columns = columns;
														yylval.ident.sizeList = UNDEF;
														yylval.ident.valor = UNDEF;
														yylval.ident.tipus = UNDEF;
																						
														return STRING;
														
														}



(({word}|{digits}|{simbols}|{tabulate})*\")		|
(\"({word}|{digits}|{simbols}|{tabulate})*)		{columns=columns+yyleng;lastyyleng=yyleng;}


(\'({word}|{digits}|{simbols}|{space})\')	{int ascii = (int) yytext[1];

											columns=columns+yyleng;
											lastyyleng=yyleng;
												
											clear_string(yytext,string);
																													
											
											yylval.ident.lexema = (char *)malloc(sizeof(char)*strlen(string));
											strncpy(yylval.ident.lexema,string,strlen(string));
											yylval.ident.lenght = strlen(string);
											yylval.ident.rows = rows;
											yylval.ident.columns = columns;
											yylval.ident.sizeList = UNDEF;
											yylval.ident.valor = UNDEF;
											yylval.ident.tipus = UNDEF;
																						
											return CHARACTER_CONSTANT;
												
											}


(\'({word}|{digits}|{simbols}|{space})*\')	| 
(({word})*\')								|
(({digits})*\')								|
(({simbols})*\')  							|
(\'({word}|{digits}|{simbols})*)  	{columns=columns+yyleng;lastyyleng=yyleng;}


{tabulate}({tabulate})*	{columns=columns+((8*yyleng)-(lastyyleng%8));}

{space}({space})*	{columns=columns+yyleng; lastyyleng=yyleng;}	

({digits}+\.({word}|{simbols})*)	|
(\.{digits}+) 					{columns=columns+yyleng;lastyyleng=yyleng;}


{digits}({digits}*\.{digits}+)	{
								columns=columns+yyleng; lastyyleng=yyleng;
								yylval.ident.lexema = (char *)malloc(sizeof(char)*yyleng);
								strncpy(yylval.ident.lexema,yytext,yyleng);
								yylval.ident.lenght = yyleng;
								yylval.ident.rows = rows;
								yylval.ident.columns = columns;
								yylval.ident.sizeList = UNDEF;
								yylval.ident.valor = UNDEF;
								yylval.ident.tipus = UNDEF;
																
								return FLOATING_CONSTANT;
								
								}

{digits}({digits})*				{
								columns=columns+yyleng; lastyyleng=yyleng;
								yylval.ident.lexema = (char *)malloc(sizeof(char)*yyleng);
								strncpy(yylval.ident.lexema,yytext,yyleng);
								yylval.ident.lenght = yyleng;
								yylval.ident.rows = rows;
								yylval.ident.columns = columns;
								yylval.ident.sizeList = UNDEF;
								yylval.ident.valor = UNDEF;
								yylval.ident.tipus = UNDEF;
																
								return INTEGER_CONSTANT;}
									
({digits}){digits}*({word}|\_|{digits})+ 				{columns=columns+yyleng;lastyyleng=yyleng;}


{operator}{2} {int value=checkReservedOperators();
				columns=columns+yyleng;
				lastyyleng=yyleng;
				
					if(value!=0){
													
					
					yylval.ident.lexema = (char *)malloc(sizeof(char)*yyleng);
					strncpy(yylval.ident.lexema,yytext,yyleng);
					yylval.ident.lenght = yyleng;
					yylval.ident.rows = rows;
					yylval.ident.columns = columns;
					yylval.ident.sizeList = UNDEF;
					yylval.ident.valor = UNDEF;
					yylval.ident.tipus = UNDEF;
					
					return value;
					
					}
				
				}

({simbols}{1}|{operator}{1}|{opespecial}{1})	{ 	char *c = yytext;
												int ascii = (int) *c;
												
												columns=columns+yyleng;
												lastyyleng=yyleng;
												
												
												yylval.ident.lexema = (char *)malloc(sizeof(char)*yyleng);
												strncpy(yylval.ident.lexema,yytext,yyleng);
												yylval.ident.lenght = yyleng;
												yylval.ident.rows = rows;
												yylval.ident.columns = columns;
												yylval.ident.sizeList = UNDEF;
												yylval.ident.valor = UNDEF;
												yylval.ident.tipus = UNDEF;
																				
												return ascii;
			
											;}
({word}|\_)({digits}|\_|{word}|\$)*	{int value=checkReservedTokens();
									int type;
									lastyyleng=yyleng;
									columns=columns+yyleng;
									
										yylval.ident.lexema = (char *)malloc(sizeof(char)*yyleng);
										strncpy(yylval.ident.lexema,yytext,yyleng);
										yylval.ident.lenght = yyleng;
										yylval.ident.rows = rows;
										yylval.ident.columns = columns;
										yylval.ident.sizeList = UNDEF;
										yylval.ident.valor = UNDEF;
										yylval.ident.tipus = UNDEF;
													

									if(value!=0){
										return value;
									}								
									else {		
									
										type=check_type();
										
										return type;
										/*
										if(type==IDENTIFIER){
											return IDENTIFIER;
										}
										else{
																						
											switch(type){
												case 1:
													return CHAR;
												break;
												case 2:
													return SHORT;
												break;
												case 3:
													return INT;
												break;
												case 4:
													return LONG;
												break;
												case 5:
													return FLOAT;
												break;
												case 6:
													return DOUBLE;
												break;											
												case 9:
													return VOID;
												break;											
											}
										
											
										}
										*/
									}
}
		


<COMMENT1>{comment11}	{BEGIN 0;}
<COMMENT1>{enter}	{rows++;}
<COMMENT1>.	

<COMMENT2>{enter}	{rows++; BEGIN 0;}
<COMMENT2>.

{enter} {rows++ ;columns = 1;lastyyleng=0;}

. {columns=columns+yyleng;lastyyleng=yyleng;}

%%
/*
Aquesta funció es l'encarregada de modificar la cadena rebuda per parametre que conté les cometes dobles al inici
i final de cadena i deixar-la neta per imprimir-la.

*/
void clear_string(char *str,char *newString)
{
	
	int i;
	char copy[100];
	
	strcpy(copy,str);
	
	
	
   for(i=0; i<100; i++)
   {
	 if(copy[i]=='\0')
	 {
	 	copy[i-1]='\0';
	 	sprintf(newString,"%s",&copy[1]);	
	   
	 }
   }
	
  
	
}

/*
Comprova si la cadena obtinguda forma part del operadors reservats.
Si ho es, creem el missatge pertinent i el mostrem, sino ho es, donem error, ja que no
permetem dos simbols junts que no estiguin dins la taula de operadors reservats.

*/
int checkReservedOperators()
{
	int words=13;
	int i=0;
	int cols=2;
	
	char *reservedOperators[words][cols];
	
	reservedOperators[0][0]="++";
	reservedOperators[1][0]="--";
	reservedOperators[2][0]="<=";
	reservedOperators[3][0]=">=";
	reservedOperators[4][0]="==";
	reservedOperators[5][0]="!=";
	reservedOperators[6][0]="&&";
	reservedOperators[7][0]="||";
	reservedOperators[8][0]="*=";
	reservedOperators[9][0]="/=";
	reservedOperators[10][0]="%/";
	reservedOperators[11][0]="+=";
	reservedOperators[12][0]="-=";
	     
	reservedOperators[0][1]="285";
	reservedOperators[1][1]="286";
	reservedOperators[2][1]="287";
	reservedOperators[3][1]="288";
	reservedOperators[4][1]="289";
	reservedOperators[5][1]="290";
	reservedOperators[6][1]="291";
	reservedOperators[7][1]="292";
	reservedOperators[8][1]="293";
	reservedOperators[9][1]="294";
	reservedOperators[10][1]="295";
	reservedOperators[11][1]="296";
	reservedOperators[12][1]="297";
	
		
	for(i=0;i<words;i++){
		if (strcmp(yytext,reservedOperators[i][0])==0)
		{
			/*sprintf(string,"Fila:  %d.%d\t%s\t\t%s\t\t\t-\n", rows, columns, yytext, reservedOperators[i][1]);
			string_output(string);*/
									
			return atoi(reservedOperators[i][1]);
		}	
	}
	
	return 0;
	
	/*sprintf(string,"Fila:  %d.%d\t%s\t\tERROR\t\t\t%s\n", rows, columns, yytext, yytext);
	string_output(string);*/
	
}

/*
Comprovem si la cadena obtinguda dins yytext, es un token reservat
Retornem 1 si localitzem el toquen, per tant tot es correcte
Retornem 0, si no a sigut localitzat dins la taula.

*/
int checkReservedTokens()
{
	int words=22;
	int cols = 2;
	int i=0;
	char *reservedWords[words][cols];
	
	reservedWords[0][0]="break";
	reservedWords[1][0]="case";
	reservedWords[2][0]="char";
	reservedWords[3][0]="continue";
	reservedWords[4][0]="default";
	reservedWords[5][0]="do";
	reservedWords[6][0]="double";
	reservedWords[7][0]="else";
	reservedWords[8][0]="float";
	reservedWords[9][0]="for";
	reservedWords[10][0]="if";
	reservedWords[11][0]="int";
	reservedWords[12][0]="long";
	reservedWords[13][0]="return";
	reservedWords[14][0]="short";
	reservedWords[15][0]="sizeof";
	reservedWords[16][0]="struct";
	reservedWords[17][0]="switch";
	reservedWords[18][0]="typedef";
	reservedWords[19][0]="union";
	reservedWords[20][0]="void";
	reservedWords[21][0]="while";
	
	reservedWords[0][1]="258";
	reservedWords[1][1]="259";
	reservedWords[2][1]="260";
	reservedWords[3][1]="261";
	reservedWords[4][1]="262";
	reservedWords[5][1]="263";
	reservedWords[6][1]="264";
	reservedWords[7][1]="265";
	reservedWords[8][1]="266";
	reservedWords[9][1]="267";
	reservedWords[10][1]="268";
	reservedWords[11][1]="269";
	reservedWords[12][1]="270";
	reservedWords[13][1]="271";
	reservedWords[14][1]="272";
	reservedWords[15][1]="273";
	reservedWords[16][1]="274";
	reservedWords[17][1]="275";
	reservedWords[18][1]="276";
	reservedWords[19][1]="277";
	reservedWords[20][1]="278";
	reservedWords[21][1]="279";
	

	for(i=0;i<words;i++){
		if (strcmp(yytext,reservedWords[i][0])==0)
		{
			/*sprintf(string,"Fila:  %d.%d\t%s\t\t%s\t\t\t-\n", rows, columns, yytext, reservedWords[i][1]);
			string_output(string);*/
								
			return atoi(reservedWords[i][1]);
		}	
	}
	return 0;
}


/*
Aquesta funció rep per paràmetre l'arxiu que ha de carregar a l'entrada per
posteriorment ser analitzat. Si tot es correcte retorna EXIT_SUCCESS, sino 
no es pot carregar l'arxiu retorna l'error EXIT_FAILURE.

*/
int init_analisi_lexic(char *file_name)
{

int error;

yyin=fopen(file_name,"r");

	if(yyin == NULL){
		error = EXIT_FAILURE;
	}else{
		error = EXIT_SUCCESS;
		
	}

return error;

}

/*
Aquesta funció s'encarrega de tancar l'arxiu d'entrada obert.

*/
int end_analisi_lexic(){

int error;

error = fclose(yyin);

	if (error == 0){	
		error = EXIT_SUCCESS;
	}else{
		error = EXIT_FAILURE;
	}

return error;
}

/*
Si el trobem a la taula i definit com TYPEDEF, retornem el seu tipus(int, float...)
Retornem IDENTIFIER, sino esta a la taula, o no es TYPEDEF.
*/
int check_type()
{
        sym_value_type info;
        
        if (sym_global_lookup(yytext, &info)==SYMTAB_OK){
            /* Si existeix a la taula */
            if(info.tipus==ID_TYPEDEF){
				return TYPEDEF_IDENTIFIER;
			}
		}
		
		return(IDENTIFIER);			
        
}

