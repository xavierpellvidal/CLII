%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RegistreActivacio.h"
#include "RegistreC3A.h"
#include "gramaticay.tab.h"
#include "symtab.h"

#define YYLMAX 100

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

#define UNDEF -1
#define FUNCTION 10
#define ID_TYPEDEF 11
#define ID_STRUCT 12

#define LOCAL 0
#define GLOBAL -1

extern FILE *yyout;

/*Variables per a la taula de simbols*/
char *nom_id;
char *nom_programa;
char *nom_ambit;
char *nom_funcio;
char *punter;

char *cast;	/*per a guardar expresions de comparacions que necessitem tenir en string*/
char *castAux; /*per a guardar expresions de comparacions que necessitem tenir en string*/
char *op;

/*Punter per a afegir cometes simples als caracters*/
char *aux;
taula globalRA, localRA;
fila filaAux;
registre globalC3A, localC3A;
fil filAux;
int offsetL = 0;
int offsetG = 0;

int tipus_declaracio = UNDEF;

int isFunction = 0;
int isReturn = 0;
int isFunctionDeclaration = 0;
int numParam = 0;
int i, j;
int isStruct = 0;
int isFor = 0;

/* per controlar el numero de parametres quan inicialitzem una llista manualment "{2,3,4}" */
int nparams_initializer_list = 0;

sym_value_type info, infoAux;
int error_sym, error_sym2;
sym_scope_id ambit_actual;
sym_scope_id ambit_anterior;

extern int yylineno;
extern int yylex();
extern void yyerror(char*);

char string[100];
void inicialitzarInfo();
void mostraError(int codi,const char *lexema);
void string_output(char *, int row, int col);
void missatgeTS(char *, int row, int col);
void missatgeError(char *, int row, int col);
void missatgeWarning(char *, int row, int col);
int comprovacioTipus(int primer, int segon);
int obtenirMida(int tipus);
int obtenirMidaStruct(char * );
sym_value_type info, infoAux;

%}

%union{
	struct{
		char *lexema;
		char *lexemac3a;
		int lenght;
		int rows;
		int columns;
		int tipus;
		int* trueList;
		int nTrue;
		int* falseList;
		int nFalse;
		int* nextList;
		int nNext;
		int quad;
		int valor;
		int sizeList;
		int tipusTypedef;
	}ident;
}

%token<ident> BREAK CASE CHAR CONTINUE DEFAULT DO DOUBLE ELSE FLOAT FOR IF INT LONG
%token<ident> RETURN SHORT SIZEOF STRUCT SWITCH TYPEDEF UNION VOID WHILE
%token<ident> IDENTIFIER CHARACTER_CONSTANT INTEGER_CONSTANT FLOATING_CONSTANT STRING
%token<ident> INC_OP DEC_OP LE_OP GE_OP EQ_OP NE_OP AND_OP OR_OP
%token<ident> MUL_ASSIG DIV_ASSIG MOD_ASSIG ADD_ASSIG SUB_ASSIG
%token<ident> TYPEDEF_IDENTIFIER '{' '}' '(' ')'

%type<ident> primary_expression constant postfix_expression argument_expression_list type_specifier declaration_specifiers additive_expression
%type<ident> function_definition declarator compound_statement init_declarator initializer init_declarator_list expression expression_statement
%type<ident> multiplicative_expression assignment_expression unary_expression assignment_operator cast_expression initializer_list m n
%type<ident> relational_expression equality_expression logical_OR_expression logical_AND_expression translation_unit typedef_name error
%type<ident> declaration_list declaration parameter_declaration conditional_expression constant_expression type_name specifier_qualifier_list statement
%type<ident> unary_operator selection_statement iteration_statement s p q statement_list struct_declaration struct_declarator_list
 

%right<ident>'='
%left<ident>'+''-'
%left<ident>'*''/''%'

/* Hem de borrar el ELSE de la llista de tokens si el tenim definit com no associatiu? */
%nonassoc IF_PREC
%nonassoc ELSE


%start translation_unit

%%
/* no cal fer res perque es passa el nom i el tipus del $1 al $$ */
primary_expression : IDENTIFIER {
								inicialitzarInfo();
								ambit_actual=sym_get_scope();
								
								if (ambit_actual==SYM_ROOT_SCOPE){
									error_sym=sym_global_lookup($1.lexema,&info);
								}
								else{
									error_sym=sym_lookup($1.lexema,&info);
								}
								
								if(error_sym == SYMTAB_OK){
									if (info.tipus == ID_TYPEDEF){
										$$.tipus = info.tipus;
										$$.tipusTypedef = info.tipusTypedef  ;
									}
									else{
									    $$.lexema = $1.lexema;
										$$.tipus = info.tipus;
									}
									
									/*-----------------C3A------------------*/
									$$.lexemac3a = $1.lexema;
								}
								else{
									sprintf(string,"ERROR. Variable %s no definida en l'ambit %d.", $1.lexema, ambit_actual);
									missatgeError(string,$1.rows, $1.columns);
									YYERROR;
								}
								sprintf(string,"primary_expression <- IDENTIFIER %s", $<ident>1.lexema);
								string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| constant 					{
								sprintf(string,"primary_expression <- constant ");
								string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| STRING 					{
		
								/*-----------------C3A------------------*/
								$$.lexemac3a = $1.lexemac3a;
								
								sprintf(string,"primary_expression <- STRING %s", $<ident>1.lexema);
								string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| '(' expression ')' 		{
								$$.tipus = $2.tipus;
								
								/*-----------------C3A------------------*/
								$$.lexemac3a = $2.lexemac3a;
								$$.trueList = $2.trueList;
								$$.nTrue = $2.nTrue;
								$$.falseList = $2.falseList;
								$$.nFalse = $2.nFalse;
								
								sprintf(string,"primary_expression <- (expression) ");
								string_output(string, $<ident>1.rows, $<ident>1.columns);}
	;

constant : INTEGER_CONSTANT {
							$$.tipus = ID_INT;
							$$.sizeList = UNDEF;
							$$.valor= ID_INT;
							
							/*-----------------C3A------------------*/
							$$.lexemac3a = $1.lexema;
							
							sprintf(string,"constant <- INTEGER_CONSTANT %s", $<ident>1.lexema);
							string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| CHARACTER_CONSTANT 	{
							$$.tipus = ID_CHAR;
							$$.sizeList = UNDEF;
							$$.valor = ID_CHAR;
							
							/*-----------------C3A------------------*/
							/*$$.lexemac3a = $1.lexema;*/
							sprintf(aux,"'%s'",$1.lexema);
							$$.lexemac3a = aux;
							
							sprintf(string,"constant <- CHARACTER_CONSTANT %s", $<ident>1.lexema);
							string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| FLOATING_CONSTANT 	{
							$$.tipus = ID_FLOAT;
							$$.sizeList = UNDEF;
							$$.valor = ID_FLOAT;
							
							/*-----------------C3A------------------*/
							$$.lexemac3a = $1.lexema;
							
							sprintf(string,"constant <- FLOATING_CONSTANT %s", $<ident>1.lexema);
							string_output(string, $<ident>1.rows, $<ident>1.columns);}
	;
	
postfix_expression : primary_expression 	{
											$$ = $1;
											sprintf(string,"postfix_expression <- primary_expression ");
											string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| postfix_expression '[' expression ']' {
											inicialitzarInfo();
											ambit_actual=sym_get_scope();
											if (ambit_actual==SYM_ROOT_SCOPE){
												error_sym=sym_global_lookup($1.lexema,&info);
											}
											else{
												error_sym=sym_lookup($1.lexema,&info);
											}
											if(error_sym == SYMTAB_OK){
												if ($3.tipus != ID_INT){
													sprintf(string,"ERROR. Index ha de ser una expressio entera.");
													missatgeError(string,$1.rows, $1.columns);
													YYERROR;
												}else if(info.sizeList != UNDEF){
													
													/*-----------------C3A------------------*/
													cast = nouTemp();
													sprintf(op,"%c",'*');
													filAux = inicialitzarFil(filAux);
													sprintf(filAux.info, "%s %s %d %s %s", cast, ":=", obtenirMida(info.tipus), obtainOp(op, info.tipus), $3.lexemac3a) ;
													localC3A = emet(filAux, localC3A);
													
													/*$$.lexemac3a = nouTemp();*/
													filAux = inicialitzarFil(filAux);
													sprintf($$.lexemac3a, "%s[%s]", $1.lexemac3a, cast);
													/*localC3A = emet(filAux, localC3A);*/
													
													sprintf(string,"(TS) Trobada la taula %s a la TS.", $1.lexema);
													missatgeTS(string,$1.rows, $1.columns);
													$$.tipus = info.tipus;
													$$.sizeList = UNDEF;
												}else{
													sprintf(string,"ERROR. La variable no es una taula.");
													missatgeError(string,$1.rows, $1.columns);
													YYERROR;
												}	
											}
											else{
												sprintf(string,"ERROR. Variable no definida.");
												missatgeTS(string,$1.rows, $1.columns);
											}
											sprintf(string,"postfix_expression <- postfix_expression '[' expression ']' ");
											string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| postfix_expression '(' {
							inicialitzarInfo();
							ambit_actual = sym_get_scope();
							
							error_sym=sym_global_lookup($1.lexema,&info);
							
							if(info.tipus != FUNCTION){
								sprintf(string,"ERROR. La variable %s no es una funcio.", $1.lexema);
								missatgeError(string,$1.rows, $1.columns);
								YYERROR;
							}
							else{
								numParam = 0;
								
								nom_funcio = (char *)malloc(sizeof($1.lexema));
								strcpy(nom_funcio, $1.lexema);
							}	
							}  ')' 	{
									inicialitzarInfo();
									ambit_actual = sym_get_scope();
									
									error_sym=sym_global_lookup(nom_funcio,&info);
									
									if(numParam != info.nParamsFuncio ){
										sprintf(string,"ERROR. En numero d'arguments no coincideix amb la declaracio.");
										missatgeError(string,$1.rows, $1.columns);
										YYERROR;
									}
									
									$$.tipus = info.tipusFunction;
									
									sprintf(string,"postfix_expression <- postfix_expression '(' ')' ");
									string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| postfix_expression '(' {
								inicialitzarInfo();
								ambit_actual = sym_get_scope();
								
								error_sym=sym_global_lookup(nom_funcio,&info);
								
								if(info.tipus != FUNCTION){
									sprintf(string,"ERROR. La variable %s no es una funcio.", $1.lexema);
									missatgeError(string,$1.rows, $1.columns);
									YYERROR;
								} 
								else{
									numParam = 0;
									
									nom_funcio = (char *)malloc(sizeof($1.lexema));
									strcpy(nom_funcio, $1.lexema);
								}	
							} argument_expression_list ')' 	{
															inicialitzarInfo();
															ambit_actual = sym_get_scope();
															
															error_sym=sym_global_lookup(nom_funcio,&info);
															
															if(numParam != info.nParamsFuncio ){
																
																sprintf(string,"ERROR. En numero d'arguments no coincideix amb la declaracio.");
																missatgeError(string,$1.rows, $1.columns);
																YYERROR;
															}
															
															for(i=0;i<info.nParamsFuncio;i++){
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "PARAM %s", info.parametres[i].parametrec3a);
																localC3A = emet(filAux, localC3A);															
															}
															
															$$.tipus = info.tipusFunction;
															
															
															/*Check if function have a return statement*/
															
															if(info.tipusFunction != ID_VOID){
																$$.lexemac3a = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s := CALL %s, %d", $$.lexemac3a, nom_funcio, numParam);
																localC3A = emet(filAux, localC3A);	
																
															}else{							
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "CALL %s, %d", nom_funcio, numParam);
																localC3A = emet(filAux, localC3A);
															}
															
															/*Restart function name */
															strcpy(nom_funcio, nom_ambit);
															
															sprintf(string,"postfix_expression <- postfix_expression '(' argument_expression_list ')' ");
															string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| postfix_expression '.' IDENTIFIER 	{
											nom_id = (char *)malloc(sizeof(char)*20);
											strcpy(nom_id, $1.lexema);
											
											inicialitzarInfo();
											ambit_actual = sym_get_scope();
											
											/*Obtenim la variable creada amb el typedef struct, pero volem el valor per accedir al struct 'melon' i veure les dades*/
											error_sym=sym_lookup(nom_id,&info);
											/* Recuperem el struct original 'melon', no el creat*/
											error_sym=sym_lookup(info.valor,&infoAux);
											j = 0;
											
											for(i=0; i<infoAux.nParamsFuncio; i++){
												printf("Param %d: tipus %d  -> mida: %d\n", i,  infoAux.parametres[i].type, obtenirMida(infoAux.parametres[i].type));
												j += obtenirMida(infoAux.parametres[i].type);
												if (strcmp(infoAux.parametres[i].lexema, $3.lexema) == 0){
													$$.tipus = infoAux.parametres[i].type;
													j -= obtenirMida(infoAux.parametres[i].type);
													break;
												}
											}
											
											sprintf($$.lexemac3a, "%s[%d]", nom_id, j);
											
											sprintf(string,"postfix_expression <- postfix_expression '.' IDENTIFIER ");
											string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| postfix_expression INC_OP 			{sprintf(string,"postfix_expression <- postfix_expression INC_OP  ");
											string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| postfix_expression DEC_OP 			{sprintf(string,"postfix_expression <- postfix_expression DEC_OP ");
											string_output(string, $<ident>1.rows, $<ident>1.columns);}
	;
	
argument_expression_list : assignment_expression 	{
													inicialitzarInfo();
															
													/*Recuperem la funcio per guardar-hi el parametre*/
													error_sym=sym_global_lookup(nom_funcio,&info);
													
													if(info.parametres[numParam].type != $1.tipus){
														sprintf(string,"ERROR. El tipus del parametre %d no coincideix amb la declaracio.", numParam + 1);
														missatgeError(string,$1.rows, $1.columns);
														YYERROR;
													}
													else{
														/*******************C3A******************/
														strcpy(info.parametres[numParam].parametrec3a, $1.lexemac3a);
														
														sym_global_remove(nom_funcio);
														sym_global_add(nom_funcio,&info);
														
														numParam++;
													}
													
													sprintf(string,"argument_expression_list <- assignment_expression ");
													string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| argument_expression_list ',' assignment_expression 	{
															inicialitzarInfo();
															/*Recuperem la funcio per guardar-hi el parametre*/
															error_sym=sym_global_lookup(nom_funcio,&info);
															
															if(info.parametres[numParam].type != $3.tipus){
																sprintf(string,"ERROR. El tipus del parametre %d no coincideix amb la declaracio.", numParam + 1);
																missatgeError(string,$3.rows, $3.columns);
																YYERROR;
															}
															else{
																/*******************C3A******************/
																strcpy(info.parametres[numParam].parametrec3a, $3.lexemac3a);
																sym_global_remove(nom_funcio);
																sym_global_add(nom_funcio,&info);
																numParam++;
															}
															sprintf(string,"argument_expression_list <- argument_expression_list ',' assignment_expression");
															string_output(string, $<ident>1.rows, $<ident>1.columns);}
	;
	
unary_expression : postfix_expression 	{
										$$ = $1;
										sprintf(string,"unary_expression <- postfix_expression ");
										string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| INC_OP unary_expression 			{sprintf(string,"unary_expression <- INC_OP unary_expression ");
										string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| DEC_OP unary_expression 			{sprintf(string,"unary_expression <- DEC_OP unary_expression ");
										string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| unary_operator cast_expression 	{
										if ($2.tipus != ID_CHAR){
											$$.tipus = $2.tipus;
											
											if ( $1.lexema[0] == '-' ){
												/*-----------------C3A------------------*/
												$$.lexemac3a = nouTemp();
												filAux = inicialitzarFil(filAux);
												sprintf(filAux.info, "%s %s %s %s", $$.lexemac3a, ":=", signChange($2.tipus), $2.lexemac3a);
												localC3A = emet(filAux, localC3A);
											} else if  ( $1.lexema[0] == '!' ){
												$$.trueList = $2.falseList;
												$$.nTrue = $2.nFalse;
												$$.falseList = $2.trueList;
												$$.nFalse = $2.nTrue;
											}
											
											
										}
										sprintf(string,"unary_expression <- unary_operator cast_expression ");
										string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| SIZEOF unary_expression 			{sprintf(string,"unary_expression <- SIZEOF unary_expression ");
										string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| SIZEOF '(' type_name ')' 			{sprintf(string,"unary_expression <- SIZEOF '(' type_name ')' ");
										string_output(string, $<ident>1.rows, $<ident>1.columns);}
	;
	
unary_operator : '+' 	{sprintf(string,"unary_operator <- '+' ");
						string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| '-' 				{sprintf(string,"unary_operator <- '-' ");
						string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| '!' 				{sprintf(string,"unary_operator <- '!' ");
						string_output(string, $<ident>1.rows, $<ident>1.columns);}
	;
	
cast_expression : unary_expression 		{
										$$ = $1;
										sprintf(string,"cast_expression <- unary_expression");
										string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| '(' type_name ')' cast_expression {
										if(($2.tipus != UNDEF)&&($4.tipus != UNDEF)) {
											
											int comprovacio = 0;
											comprovacio = comprovacioTipus($2.tipus, $4.tipus);
											
											switch (comprovacio) {
												case COMPTIPUS_IGUALS:
													$$.tipus = $2.tipus;
													sprintf(string,"(Cast) Sense efecte algun.");
													missatgeTS(string,$2.rows, $2.columns);
												break;
												case COMPTIPUS_DIF_RED_PRIMER:
													$$.tipus = $2.tipus;
													
													/*-----------------C3A------------------*/
													cast = nouTemp();
													filAux = inicialitzarFil(filAux);
													sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast($2.tipus, $4.tipus, COMPTIPUS_DIF_RED_PRIMER), $4.lexemac3a);
													localC3A = emet(filAux, localC3A);
													
													sprintf(string,"(Cast) a tipus %d.", $2.tipus);
													missatgeWarning(string,$1.rows, $1.columns);
												break;
												case COMPTIPUS_DIF_RED_SEGON:
													$$.tipus = $2.tipus;
													
													/*-----------------C3A------------------*/
													cast = nouTemp();
													filAux = inicialitzarFil(filAux);
													sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast($2.tipus, $4.tipus, COMPTIPUS_DIF_RED_SEGON), $2.lexemac3a);
													localC3A = emet(filAux, localC3A);
													
													sprintf(string,"(Cast) a tipus %d.", $2.tipus);
													missatgeWarning(string,$1.rows, $1.columns);
												break;
												case COMPTIPUS_DIF_NO_RED:
													sprintf(string,"ERROR. (Cast) - Impossible fer cast a tipus %d.", $2.tipus);
													missatgeError(string,$2.rows, $2.columns);
													YYERROR;
												break;
											}
										}
										else{
											sprintf(string,"ERROR. Variable sense tipus.");
											missatgeError(string,$1.rows, $1.columns);
											YYERROR;
										}	
													
										
										sprintf(string,"cast_expression <- '(' type_name ')' cast_expression ");
										string_output(string, $<ident>1.rows, $<ident>1.columns);}
	;
	
multiplicative_expression : cast_expression {
											$$ = $1;
											sprintf(string,"multiplicative_expression <- cast_expression");
											string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| multiplicative_expression '*' cast_expression {
													if(($1.tipus != UNDEF)&&($3.tipus != UNDEF)) {
														
														int comprovacio = 0;
														comprovacio = comprovacioTipus($1.tipus, $3.tipus);
														
														switch (comprovacio) {
															case COMPTIPUS_IGUALS:
																$$.tipus = $1.tipus;
																
																/*-----------------C3A------------------*/
																$$.lexemac3a = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s %s %s %s %s", $$.lexemac3a, ":=", $1.lexemac3a, obtainOp($2.lexema, $1.tipus), $3.lexemac3a);
																localC3A = emet(filAux, localC3A);
																
																sprintf(string,"Operacio correcta del mateix tipus. Tipus %d.", info.tipus);
																missatgeTS(string,$1.rows, $1.columns);
															break;
															case COMPTIPUS_DIF_RED_PRIMER:
																$$.tipus = $1.tipus;
																
																/*-----------------C3A------------------*/
																cast = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast($1.tipus, $3.tipus, COMPTIPUS_DIF_RED_PRIMER), $3.lexemac3a);
																localC3A = emet(filAux, localC3A);
																
																$$.lexemac3a = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s %s %s %s %s", $$.lexemac3a, ":=", $1.lexemac3a, obtainOp($2.lexema, $1.tipus), cast);
																localC3A = emet(filAux, localC3A);
																
																sprintf(string,"Comprovacio de tipus - Cast pel tipus del primer operand %d.", $1.tipus);
																missatgeWarning(string,$1.rows, $1.columns);
															break;
															case COMPTIPUS_DIF_RED_SEGON:
																$$.tipus = $3.tipus;
																
																/*-----------------C3A------------------*/
																cast = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast($1.tipus, $3.tipus, COMPTIPUS_DIF_RED_SEGON), $1.lexemac3a);
																localC3A = emet(filAux, localC3A);
																
																$$.lexemac3a = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s %s %s %s %s", $$.lexemac3a, ":=", cast, obtainOp($2.lexema, $3.tipus), $3.lexemac3a);
																localC3A = emet(filAux, localC3A);
																
																sprintf(string,"Comprovacio de tipus - Cast pel tipus del segon operand %d.", $3.tipus);
																missatgeWarning(string,$1.rows, $1.columns);
															break;
															case COMPTIPUS_DIF_NO_RED:
																sprintf(string,"ERROR. Comprovacio de tipus - Els tipus no es poden reduir.");
																missatgeError(string,$1.rows, $1.columns);
																YYERROR;
															break;
														}
														
													}
													else{
														sprintf(string,"ERROR. Variable sense tipus.");
														missatgeError(string,$1.rows, $1.columns);
														YYERROR;
													}	
													
													sprintf(string,"multiplicative_expression <- multiplicative_expression '*' cast_expression ");
													string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| multiplicative_expression '/' cast_expression {
													if(($1.tipus != UNDEF)&&($3.tipus != UNDEF)) {
														
														int comprovacio = 0;
														comprovacio = comprovacioTipus($1.tipus, $3.tipus);
														
														switch (comprovacio) {
															case COMPTIPUS_IGUALS:
																$$.tipus = $1.tipus;
																
																/*-----------------C3A------------------*/
																$$.lexemac3a = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s %s %s %s %s", $$.lexemac3a, ":=", $1.lexemac3a, obtainOp($2.lexema, $1.tipus), $3.lexemac3a);
																localC3A = emet(filAux, localC3A);
																
																sprintf(string,"Operacio correcta del mateix tipus. Tipus %d.", info.tipus);
																missatgeTS(string,$1.rows, $1.columns);
															break;
															case COMPTIPUS_DIF_RED_PRIMER:
																$$.tipus = $1.tipus;
																
																/*-----------------C3A------------------*/
																cast = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast($1.tipus, $3.tipus, COMPTIPUS_DIF_RED_PRIMER), $3.lexemac3a);
																localC3A = emet(filAux, localC3A);
																
																$$.lexemac3a = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s %s %s %s %s", $$.lexemac3a, ":=", $1.lexemac3a, obtainOp($2.lexema, $1.tipus), cast);
																localC3A = emet(filAux, localC3A);
																
																sprintf(string,"Comprovacio de tipus - Cast pel tipus del primer operand %d.", $1.tipus);
																missatgeWarning(string,$1.rows, $1.columns);
															break;
															case COMPTIPUS_DIF_RED_SEGON:
																$$.tipus = $3.tipus;
																
																/*-----------------C3A------------------*/
																cast = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast($1.tipus, $3.tipus, COMPTIPUS_DIF_RED_SEGON), $1.lexemac3a);
																localC3A = emet(filAux, localC3A);
																
																$$.lexemac3a = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s %s %s %s %s", $$.lexemac3a, ":=", cast, obtainOp($2.lexema, $3.tipus), $3.lexemac3a);
																localC3A = emet(filAux, localC3A);
																
																sprintf(string,"Comprovacio de tipus - Cast pel tipus del segon operand %d.", $3.tipus);
																missatgeWarning(string,$1.rows, $1.columns);
															break;
															case COMPTIPUS_DIF_NO_RED:
																sprintf(string,"ERROR. Comprovacio de tipus - Tipus incorrectes a la multiplicacio.");
																missatgeError(string,$1.rows, $1.columns);
																YYERROR;
															break;
														}
													}
													else {
														sprintf(string,"ERROR. Variable sense tipus.");
														missatgeError(string,$1.rows, $1.columns);
														YYERROR;
													}		
													sprintf(string,"multiplicative_expression <- multiplicative_expression '/' cast_expression ");
													string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| multiplicative_expression '%' cast_expression {
													if(($1.tipus != UNDEF)&&($3.tipus != UNDEF)) {
														
														int comprovacio = 0;
														comprovacio = comprovacioTipus($1.tipus, $3.tipus);
														
														switch (comprovacio) {
															case COMPTIPUS_IGUALS:
																$$.tipus = $1.tipus;
																
																/*-----------------C3A------------------*/
																$$.lexemac3a = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s %s %s %s %s", $$.lexemac3a, ":=", $1.lexemac3a, obtainOp($2.lexema, $1.tipus), $3.lexemac3a);
																localC3A = emet(filAux, localC3A);
																
																sprintf(string,"Operacio correcta del mateix tipus. Tipus %d.", info.tipus);
																missatgeTS(string,$1.rows, $1.columns);
															break;
															case COMPTIPUS_DIF_RED_PRIMER:
																$$.tipus = $1.tipus;
																
																/*-----------------C3A------------------*/
																cast = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast($1.tipus, $3.tipus, COMPTIPUS_DIF_RED_PRIMER), $3.lexemac3a);
																localC3A = emet(filAux, localC3A);
																
																$$.lexemac3a = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s %s %s %s %s", $$.lexemac3a, ":=", $1.lexemac3a, obtainOp($2.lexema, $1.tipus), cast);
																localC3A = emet(filAux, localC3A);
																
																sprintf(string,"Comprovacio de tipus - Cast pel tipus del primer operand %d.", $1.tipus);
																missatgeWarning(string,$1.rows, $1.columns);
															break;
															case COMPTIPUS_DIF_RED_SEGON:
																$$.tipus = $3.tipus;
																
																/*-----------------C3A------------------*/
																cast = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast($1.tipus, $3.tipus, COMPTIPUS_DIF_RED_SEGON), $1.lexemac3a);
																localC3A = emet(filAux, localC3A);
																
																$$.lexemac3a = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s %s %s %s %s", $$.lexemac3a, ":=", cast, obtainOp($2.lexema, $3.tipus), $3.lexemac3a);
																localC3A = emet(filAux, localC3A);
																
																sprintf(string,"Comprovacio de tipus - Cast pel tipus del segon operand %d.", $3.tipus);
																missatgeWarning(string,$1.rows, $1.columns);
															break;
															case COMPTIPUS_DIF_NO_RED:
																sprintf(string,"ERROR. Comprovacio de tipus - Tipus incorrectes al modul.");
																missatgeError(string,$1.rows, $1.columns);
																YYERROR;
															break;
														}	
													}
													else {
														sprintf(string,"ERROR. Variable sense tipus.");
														missatgeError(string,$1.rows, $1.columns);
														YYERROR;
													}		
													sprintf(string,"multiplicative_expression <- multiplicative_expression '%' cast_expression ");
													string_output(string, $<ident>1.rows, $<ident>1.columns);}
	; 
	
additive_expression : multiplicative_expression 		{
														$$ = $1;
														sprintf(string,"additive_expression <- multiplicative_expression ");
														string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| additive_expression '+' multiplicative_expression {
														if(($1.tipus != UNDEF)&&($3.tipus != UNDEF)) {
															
															int comprovacio = 0;
															comprovacio = comprovacioTipus($1.tipus, $3.tipus);
															
															switch (comprovacio) {
															case COMPTIPUS_IGUALS:
																$$.tipus = $1.tipus;
																
																/*-----------------C3A------------------*/
																$$.lexemac3a = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s %s %s %s %s", $$.lexemac3a, ":=", $1.lexemac3a, obtainOp($2.lexema, $1.tipus), $3.lexemac3a);
																localC3A = emet(filAux, localC3A);
																
																sprintf(string,"Operacio correcta del mateix tipus. Tipus %d.", info.tipus);
																missatgeTS(string,$1.rows, $1.columns);
															break;
															case COMPTIPUS_DIF_RED_PRIMER:
																$$.tipus = $1.tipus;
																
																/*-----------------C3A------------------*/
																cast = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast($1.tipus, $3.tipus, COMPTIPUS_DIF_RED_PRIMER), $3.lexemac3a);
																localC3A = emet(filAux, localC3A);
																
																$$.lexemac3a = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s %s %s %s %s", $$.lexemac3a, ":=", $1.lexemac3a, obtainOp($2.lexema, $1.tipus), cast);
																localC3A = emet(filAux, localC3A);
																
																sprintf(string,"Comprovacio de tipus - Cast pel tipus del primer operand %d.", $1.tipus);
																missatgeWarning(string,$1.rows, $1.columns);
															break;
															case COMPTIPUS_DIF_RED_SEGON:
																$$.tipus = $3.tipus;
																
																/*-----------------C3A------------------*/
																cast = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast($1.tipus, $3.tipus, COMPTIPUS_DIF_RED_SEGON), $1.lexemac3a);
																localC3A = emet(filAux, localC3A);
																
																$$.lexemac3a = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s %s %s %s %s", $$.lexemac3a, ":=", cast, obtainOp($2.lexema, $3.tipus), $3.lexemac3a);
																localC3A = emet(filAux, localC3A);
																
																sprintf(string,"Comprovacio de tipus - Cast pel tipus del segon operand %d.", $3.tipus);
																missatgeWarning(string,$1.rows, $1.columns);
															break;
																case COMPTIPUS_DIF_NO_RED:
																	sprintf(string,"ERROR. Comprovacio de tipus - Tipus incorrectes a la suma.");
																	missatgeError(string,$1.rows, $1.columns);
																	YYERROR;
																break;
															}
														}
														else{
															sprintf(string,"ERROR. Variable sense tipus.");
															missatgeError(string,$1.rows, $1.columns);
															YYERROR;
														}	
														sprintf(string,"additive_expression <- additive_expression '+' multiplicative_expression ");
														string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| additive_expression '-' multiplicative_expression {
														if(($1.tipus != UNDEF)&&($3.tipus != UNDEF)) {
															
															int comprovacio = 0;
															comprovacio = comprovacioTipus($1.tipus, $3.tipus);
															switch (comprovacio) {
																case COMPTIPUS_IGUALS:
																	$$.tipus = $1.tipus;
																	
																	/*-----------------C3A------------------*/
																	$$.lexemac3a = nouTemp();
																	filAux = inicialitzarFil(filAux);
																	sprintf(filAux.info, "%s %s %s %s %s", $$.lexemac3a, ":=", $1.lexemac3a, obtainOp($2.lexema, $1.tipus), $3.lexemac3a);
																	localC3A = emet(filAux, localC3A);
																	
																	sprintf(string,"Operacio correcta del mateix tipus. Tipus %d.", info.tipus);
																	missatgeTS(string,$1.rows, $1.columns);
																break;
																case COMPTIPUS_DIF_RED_PRIMER:
																	$$.tipus = $1.tipus;
																	
																	/*-----------------C3A------------------*/
																	cast = nouTemp();
																	filAux = inicialitzarFil(filAux);
																	sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast($1.tipus, $3.tipus, COMPTIPUS_DIF_RED_PRIMER), $3.lexemac3a);
																	localC3A = emet(filAux, localC3A);
																	
																	$$.lexemac3a = nouTemp();
																	filAux = inicialitzarFil(filAux);
																	sprintf(filAux.info, "%s %s %s %s %s", $$.lexemac3a, ":=", $1.lexemac3a, obtainOp($2.lexema, $1.tipus), cast);
																	localC3A = emet(filAux, localC3A);
																	
																	sprintf(string,"Comprovacio de tipus - Cast pel tipus del primer operand %d.", $1.tipus);
																	missatgeWarning(string,$1.rows, $1.columns);
																break;
																case COMPTIPUS_DIF_RED_SEGON:
																	$$.tipus = $3.tipus;
																	
																	/*-----------------C3A------------------*/
																	cast = nouTemp();
																	filAux = inicialitzarFil(filAux);
																	sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast($1.tipus, $3.tipus, COMPTIPUS_DIF_RED_SEGON), $1.lexemac3a);
																	localC3A = emet(filAux, localC3A);
																	
																	$$.lexemac3a = nouTemp();
																	filAux = inicialitzarFil(filAux);
																	sprintf(filAux.info, "%s %s %s %s %s", $$.lexemac3a, ":=", cast, obtainOp($2.lexema, $3.tipus), $3.lexemac3a);
																	localC3A = emet(filAux, localC3A);
																	
																	sprintf(string,"Comprovacio de tipus - Cast pel tipus del segon operand %d.", $3.tipus);
																	missatgeWarning(string,$1.rows, $1.columns);
																break;
																case COMPTIPUS_DIF_NO_RED:
																	sprintf(string,"ERROR. Comprovacio de tipus - Tipus incorrectes a la resta.");
																	missatgeError(string,$1.rows, $1.columns);
																	YYERROR;
																break;
															}
														}
														else{
															sprintf(string,"ERROR. Variable sense tipus.");
															missatgeError(string,$1.rows, $1.columns);
															YYERROR;
														}	
														sprintf(string,"additive_expression <- additive_expression '-' multiplicative_expression ");
														string_output(string, $<ident>1.rows, $<ident>1.columns);}
	;
	
relational_expression : additive_expression 			{sprintf(string,"relational_expression <- additive_expression ");
														string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| relational_expression '<' additive_expression 	{
														if(($1.tipus != UNDEF)&&($3.tipus != UNDEF)) {
															if(($1.sizeList != UNDEF)||($3.sizeList != UNDEF)){
																sprintf(string,"ERROR. Operacio amb tipus Llista.");
																missatgeError(string,$1.rows, $1.columns);
																YYERROR;
															}
															else {
																$$.tipus = ID_INT;
																
																int comprovacio = 0;
																comprovacio = comprovacioTipus($1.tipus, $3.tipus);
																switch (comprovacio) {
																	case COMPTIPUS_IGUALS:
																		$$.tipus = $1.tipus;
																		
																		/*-----------------C3A------------------*/
																		if (isFor == 0){	
																			filAux = inicialitzarFil(filAux);
																			
																			sprintf(cast, "%s %s %s", $1.lexemac3a, obtainCompare("LT", $1.tipus), $3.lexemac3a);
																			
																			$$.trueList = (int *)malloc(sizeof(int)*20);
																			$$.falseList = (int *)malloc(sizeof(int)*20);
																			
																			$$.trueList = crearllista($$.trueList, getSquad());
																			$$.falseList = crearllista($$.falseList, getSquad()+1);
																			
																			$$.nTrue++;
																			$$.nFalse++;
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "IF %s GOTO ", cast);
																			localC3A = emet(filAux, localC3A);
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "GOTO ");
																			localC3A = emet(filAux, localC3A);
																		}	
																		
																	break;
																	case COMPTIPUS_DIF_RED_PRIMER:
																		$$.tipus = $1.tipus;
																	
																		/*-----------------C3A------------------*/
																		if (isFor == 0){	
																			cast = nouTemp();
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast($1.tipus, $3.tipus, COMPTIPUS_DIF_RED_PRIMER), $3.lexemac3a);
																			localC3A = emet(filAux, localC3A);
																			
																			sprintf(castAux, "%s %s %s", $1.lexemac3a, obtainCompare("LT", $1.tipus), cast);
																			
																			$$.trueList = (int *)malloc(sizeof(int)*20);
																			$$.falseList = (int *)malloc(sizeof(int)*20);
																			
																			$$.trueList = crearllista($$.trueList, getSquad());
																			$$.falseList = crearllista($$.falseList, getSquad()+1);
																			
																			$$.nTrue++;
																			$$.nFalse++;
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "IF %s GOTO ", castAux);
																			localC3A = emet(filAux, localC3A);
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "GOTO ");
																			localC3A = emet(filAux, localC3A);
																		}
																		
																	break;
																	case COMPTIPUS_DIF_RED_SEGON:
																		$$.tipus = $3.tipus;
																		
																		/*-----------------C3A------------------*/
																		
																		if (isFor == 0){	
																			cast = nouTemp();
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast($1.tipus, $3.tipus, COMPTIPUS_DIF_RED_SEGON), $1.lexemac3a);
																			localC3A = emet(filAux, localC3A);
																			
																			sprintf(castAux, "%s %s %s", cast, obtainCompare("LT", $1.tipus),  $3.lexemac3a);
																			
																			$$.trueList = (int *)malloc(sizeof(int)*20);
																			$$.falseList = (int *)malloc(sizeof(int)*20);
																			
																			$$.trueList = crearllista($$.trueList, getSquad());
																			$$.falseList = crearllista($$.falseList, getSquad()+1);
																			
																			$$.nTrue++;
																			$$.nFalse++;
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "IF %s GOTO ", castAux);
																			localC3A = emet(filAux, localC3A);
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "GOTO ");
																			localC3A = emet(filAux, localC3A);
																		}
																		
																	break;
																	case COMPTIPUS_DIF_NO_RED:
																		sprintf(string,"ERROR. Comprovacio de tipus - Tipus incorrectes expressio relacional.");
																		missatgeError(string,$1.rows, $1.columns);
																		YYERROR;
																	break;
																}
															}
														}
														else{
															sprintf(string,"ERROR. Variable sense tipus.");
															missatgeError(string,$1.rows, $1.columns);
															YYERROR;
														}
														
														sprintf(string,"arelational_expression <- relational_expression '<' additive_expression ");
														string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| relational_expression '>' additive_expression 	{
														if(($1.tipus != UNDEF)&&($3.tipus != UNDEF)) {
															if(($1.sizeList != UNDEF)||($3.sizeList != UNDEF)){
																sprintf(string,"ERROR. Operacio amb tipus Llista.");
																missatgeError(string,$1.rows, $1.columns);
																YYERROR;
															}
															else {
																$$.tipus = ID_INT;
																
																int comprovacio = 0;
																comprovacio = comprovacioTipus($1.tipus, $3.tipus);
																switch (comprovacio) {
																	case COMPTIPUS_IGUALS:
																		$$.tipus = $1.tipus;
																		
																		/*-----------------C3A------------------*/
																		if (isFor == 0){	
																			filAux = inicialitzarFil(filAux);
																			
																			sprintf(cast, "%s %s %s", $1.lexemac3a, obtainCompare("GT", $1.tipus), $3.lexemac3a);
																			
																			$$.trueList = (int *)malloc(sizeof(int)*20);
																			$$.falseList = (int *)malloc(sizeof(int)*20);
																			
																			$$.trueList = crearllista($$.trueList, getSquad());
																			$$.falseList = crearllista($$.falseList, getSquad()+1);
																			
																			$$.nTrue++;
																			$$.nFalse++;
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "IF %s GOTO ", cast);
																			localC3A = emet(filAux, localC3A);
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "GOTO ");
																			localC3A = emet(filAux, localC3A);
																		}
																		
																		
																	break;
																	case COMPTIPUS_DIF_RED_PRIMER:
																		$$.tipus = $1.tipus;
																		
																		/*-----------------C3A------------------*/
																		if (isFor == 0){	
																			cast = nouTemp();
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast($1.tipus, $3.tipus, COMPTIPUS_DIF_RED_PRIMER), $3.lexemac3a);
																			localC3A = emet(filAux, localC3A);
																			
																			sprintf(castAux, "%s %s %s", $1.lexemac3a, obtainCompare("GT", $1.tipus), cast);
																			
																			$$.trueList = (int *)malloc(sizeof(int)*20);
																			$$.falseList = (int *)malloc(sizeof(int)*20);
																			
																			$$.trueList = crearllista($$.trueList, getSquad());
																			$$.falseList = crearllista($$.falseList, getSquad()+1);
																			
																			$$.nTrue++;
																			$$.nFalse++;
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "IF %s GOTO ", castAux);
																			localC3A = emet(filAux, localC3A);
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "GOTO ");
																			localC3A = emet(filAux, localC3A);
																		}
																	break;
																	case COMPTIPUS_DIF_RED_SEGON:
																		$$.tipus = $3.tipus;
																		
																		/*-----------------C3A------------------*/
																		if (isFor == 0){	
																			cast = nouTemp();
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast($1.tipus, $3.tipus, COMPTIPUS_DIF_RED_SEGON), $1.lexemac3a);
																			localC3A = emet(filAux, localC3A);
																			
																			sprintf(castAux, "%s %s %s", cast, obtainCompare("GT", $1.tipus),  $3.lexemac3a);
																			
																			$$.trueList = (int *)malloc(sizeof(int)*20);
																			$$.falseList = (int *)malloc(sizeof(int)*20);
																			
																			$$.trueList = crearllista($$.trueList, getSquad());
																			$$.falseList = crearllista($$.falseList, getSquad()+1);
																			
																			$$.nTrue++;
																			$$.nFalse++;
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "IF %s GOTO ", castAux);
																			localC3A = emet(filAux, localC3A);
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "GOTO ");
																			localC3A = emet(filAux, localC3A);
																		}
																	break;
																	case COMPTIPUS_DIF_NO_RED:
																		sprintf(string,"ERROR. Comprovacio de tipus - Tipus incorrectes expressio relacional.");
																		missatgeError(string,$1.rows, $1.columns);
																		YYERROR;
																	break;
																}
															}
														}
														else{
															sprintf(string,"ERROR. Variable sense tipus.");
															missatgeError(string,$1.rows, $1.columns);
															YYERROR;
														}
														sprintf(string,"relational_expression <- relational_expression '>' additive_expression ");
														string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| relational_expression LE_OP additive_expression 	{
														if(($1.tipus != UNDEF)&&($3.tipus != UNDEF)) {
															if(($1.sizeList != UNDEF)||($3.sizeList != UNDEF)){
																sprintf(string,"ERROR. Operacio amb tipus Llista.");
																missatgeError(string,$1.rows, $1.columns);
																YYERROR;
															}
															else {
																$$.tipus = ID_INT;
																
																int comprovacio = 0;
																comprovacio = comprovacioTipus($1.tipus, $3.tipus);
																switch (comprovacio) {
																	case COMPTIPUS_IGUALS:
																		$$.tipus = $1.tipus;
																		
																		/*-----------------C3A------------------*/
																		if (isFor == 0){	
																			filAux = inicialitzarFil(filAux);
																			
																			sprintf(cast, "%s %s %s", $1.lexemac3a, obtainCompare("LE", $1.tipus), $3.lexemac3a);
																			
																			$$.trueList = (int *)malloc(sizeof(int)*20);
																			$$.falseList = (int *)malloc(sizeof(int)*20);
																			
																			$$.trueList = crearllista($$.trueList, getSquad());
																			$$.falseList = crearllista($$.falseList, getSquad()+1);
																			
																			$$.nTrue++;
																			$$.nFalse++;
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "IF %s GOTO ", cast);
																			localC3A = emet(filAux, localC3A);
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "GOTO ");
																			localC3A = emet(filAux, localC3A);
																		}
																		
																	break;
																	case COMPTIPUS_DIF_RED_PRIMER:
																		$$.tipus = $1.tipus;
																	
																		/*-----------------C3A------------------*/
																		if (isFor == 0){	
																			cast = nouTemp();
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast($1.tipus, $3.tipus, COMPTIPUS_DIF_RED_PRIMER), $3.lexemac3a);
																			localC3A = emet(filAux, localC3A);
																			
																			sprintf(castAux, "%s %s %s", $1.lexemac3a, obtainCompare("LE", $1.tipus), cast);
																			
																			$$.trueList = (int *)malloc(sizeof(int)*20);
																			$$.falseList = (int *)malloc(sizeof(int)*20);
																			
																			$$.trueList = crearllista($$.trueList, getSquad());
																			$$.falseList = crearllista($$.falseList, getSquad()+1);
																			
																			$$.nTrue++;
																			$$.nFalse++;
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "IF %s GOTO ", castAux);
																			localC3A = emet(filAux, localC3A);
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "GOTO ");
																			localC3A = emet(filAux, localC3A);
																		}
																		
																	break;
																	case COMPTIPUS_DIF_RED_SEGON:
																		$$.tipus = $3.tipus;
																		
																		/*-----------------C3A------------------*/
																		if (isFor == 0){	
																			cast = nouTemp();
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast($1.tipus, $3.tipus, COMPTIPUS_DIF_RED_SEGON), $1.lexemac3a);
																			localC3A = emet(filAux, localC3A);
																			
																			sprintf(castAux, "%s %s %s", cast, obtainCompare("LE", $1.tipus),  $3.lexemac3a);
																			
																			$$.trueList = (int *)malloc(sizeof(int)*20);
																			$$.falseList = (int *)malloc(sizeof(int)*20);
																			
																			$$.trueList = crearllista($$.trueList, getSquad());
																			$$.falseList = crearllista($$.falseList, getSquad()+1);
																			
																			$$.nTrue++;
																			$$.nFalse++;
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "IF %s GOTO ", castAux);
																			localC3A = emet(filAux, localC3A);
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "GOTO ");
																			localC3A = emet(filAux, localC3A);
																		}
																		
																	break;
																	case COMPTIPUS_DIF_NO_RED:
																		sprintf(string,"ERROR. Comprovacio de tipus - Tipus incorrectes expressio relacional.");
																		missatgeError(string,$1.rows, $1.columns);
																		YYERROR;
																	break;
																}
															}
														}
														else{
															sprintf(string,"ERROR. Variable sense tipus.");
															missatgeError(string,$1.rows, $1.columns);
															YYERROR;
														}
														sprintf(string,"relational_expression <- relational_expression LE_OP additive_expression ");
														string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| relational_expression GE_OP additive_expression 	{
														if(($1.tipus != UNDEF)&&($3.tipus != UNDEF)) {
															if(($1.sizeList != UNDEF)||($3.sizeList != UNDEF)){
																sprintf(string,"ERROR. Operacio amb tipus Llista.");
																missatgeError(string,$1.rows, $1.columns);
																YYERROR;
															}
															else{
																$$.tipus = ID_INT;
																
																int comprovacio = 0;
																comprovacio = comprovacioTipus($1.tipus, $3.tipus);
																switch (comprovacio) {
																	case COMPTIPUS_IGUALS:
																		$$.tipus = $1.tipus;
																		
																		/*-----------------C3A------------------*/
																		if (isFor == 0){	
																			filAux = inicialitzarFil(filAux);
																			
																			sprintf(cast, "%s %s %s", $1.lexemac3a, obtainCompare("GE", $1.tipus), $3.lexemac3a);
																			
																			$$.trueList = (int *)malloc(sizeof(int)*20);
																			$$.falseList = (int *)malloc(sizeof(int)*20);
																			
																			$$.trueList = crearllista($$.trueList, getSquad());
																			$$.falseList = crearllista($$.falseList, getSquad()+1);
																			
																			$$.nTrue++;
																			$$.nFalse++;
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "IF %s GOTO ", cast);
																			localC3A = emet(filAux, localC3A);
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "GOTO ");
																			localC3A = emet(filAux, localC3A);
																		}
																		
																	break;
																	case COMPTIPUS_DIF_RED_PRIMER:
																		$$.tipus = $1.tipus;
																	
																		/*-----------------C3A------------------*/
																		if (isFor == 0){	
																			cast = nouTemp();
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast($1.tipus, $3.tipus, COMPTIPUS_DIF_RED_PRIMER), $3.lexemac3a);
																			localC3A = emet(filAux, localC3A);
																			
																			sprintf(castAux, "%s %s %s", $1.lexemac3a, obtainCompare("GE", $1.tipus), cast);
																			
																			$$.trueList = (int *)malloc(sizeof(int)*20);
																			$$.falseList = (int *)malloc(sizeof(int)*20);
																			
																			$$.trueList = crearllista($$.trueList, getSquad());
																			$$.falseList = crearllista($$.falseList, getSquad()+1);
																			
																			$$.nTrue++;
																			$$.nFalse++;
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "IF %s GOTO ", castAux);
																			localC3A = emet(filAux, localC3A);
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "GOTO ");
																			localC3A = emet(filAux, localC3A);
																		}
																		
																	break;
																	case COMPTIPUS_DIF_RED_SEGON:
																		$$.tipus = $3.tipus;
																		
																		/*-----------------C3A------------------*/
																		if (isFor == 0){	
																			cast = nouTemp();
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast($1.tipus, $3.tipus, COMPTIPUS_DIF_RED_SEGON), $1.lexemac3a);
																			localC3A = emet(filAux, localC3A);
																			
																			sprintf(castAux, "%s %s %s", cast, obtainCompare("GE", $1.tipus),  $3.lexemac3a);
																			
																			$$.trueList = (int *)malloc(sizeof(int)*20);
																			$$.falseList = (int *)malloc(sizeof(int)*20);
																			
																			$$.trueList = crearllista($$.trueList, getSquad());
																			$$.falseList = crearllista($$.falseList, getSquad()+1);
																			
																			$$.nTrue++;
																			$$.nFalse++;
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "IF %s GOTO ", castAux);
																			localC3A = emet(filAux, localC3A);
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "GOTO ");
																			localC3A = emet(filAux, localC3A);
																		}
																		
																	break;
																	case COMPTIPUS_DIF_NO_RED:
																		sprintf(string,"ERROR. Comprovacio de tipus - Tipus incorrectes expressio relacional.");
																		missatgeError(string,$1.rows, $1.columns);
																		YYERROR;
																	break;
																}
															}
														}
														else{
															sprintf(string,"ERROR. Variable sense tipus.");
															missatgeError(string,$1.rows, $1.columns);
															YYERROR;
														}
														sprintf(string,"relational_expression <- relational_expression GE_OP additive_expression ");
														string_output(string, $<ident>1.rows, $<ident>1.columns);}
	;
	
equality_expression : relational_expression 			{sprintf(string,"equality_expression <- relational_expression");
														string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| equality_expression EQ_OP relational_expression 	{
														if(($1.tipus != UNDEF)&&($3.tipus != UNDEF)) {
															if(($1.sizeList != UNDEF)||($3.sizeList != UNDEF)){
																sprintf(string,"ERROR. Operacio amb tipus Llista.");
																missatgeError(string,$1.rows, $1.columns);
																YYERROR;
															}
															else{
																$$.tipus = ID_INT;
																
																int comprovacio = 0;
																comprovacio = comprovacioTipus($1.tipus, $3.tipus);
																switch (comprovacio) {
																	case COMPTIPUS_IGUALS:
																		$$.tipus = $1.tipus;
																		
																		/*-----------------C3A------------------*/
																		if (isFor == 0){	
																			filAux = inicialitzarFil(filAux);
																			
																			sprintf(cast, "%s %s %s", $1.lexemac3a, obtainCompare("EQ", $1.tipus), $3.lexemac3a);
																			
																			$$.trueList = (int *)malloc(sizeof(int)*20);
																			$$.falseList = (int *)malloc(sizeof(int)*20);
																			
																			$$.trueList = crearllista($$.trueList, getSquad());
																			$$.falseList = crearllista($$.falseList, getSquad()+1);
																			
																			$$.nTrue++;
																			$$.nFalse++;
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "IF %s GOTO ", cast);
																			localC3A = emet(filAux, localC3A);
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "GOTO ");
																			localC3A = emet(filAux, localC3A);
																		}
																		
																	break;
																	case COMPTIPUS_DIF_RED_PRIMER:
																		$$.tipus = $1.tipus;
																	
																		/*-----------------C3A------------------*/
																		if (isFor == 0){	
																			cast = nouTemp();
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast($1.tipus, $3.tipus, COMPTIPUS_DIF_RED_PRIMER), $3.lexemac3a);
																			localC3A = emet(filAux, localC3A);
																			
																			sprintf(castAux, "%s %s %s", $1.lexemac3a, obtainCompare("EQ", $1.tipus), cast);
																			
																			$$.trueList = (int *)malloc(sizeof(int)*20);
																			$$.falseList = (int *)malloc(sizeof(int)*20);
																			
																			$$.trueList = crearllista($$.trueList, getSquad());
																			$$.falseList = crearllista($$.falseList, getSquad()+1);
																			
																			$$.nTrue++;
																			$$.nFalse++;
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "IF %s GOTO ", castAux);
																			localC3A = emet(filAux, localC3A);
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "GOTO ");
																			localC3A = emet(filAux, localC3A);
																		}
																		
																	break;
																	case COMPTIPUS_DIF_RED_SEGON:
																		$$.tipus = $3.tipus;
																		
																		/*-----------------C3A------------------*/
																		if (isFor == 0){	
																			cast = nouTemp();
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast($1.tipus, $3.tipus, COMPTIPUS_DIF_RED_SEGON), $1.lexemac3a);
																			localC3A = emet(filAux, localC3A);
																			
																			sprintf(castAux, "%s %s %s", cast, obtainCompare("EQ", $1.tipus),  $3.lexemac3a);
																			
																			$$.trueList = (int *)malloc(sizeof(int)*20);
																			$$.falseList = (int *)malloc(sizeof(int)*20);
																			
																			$$.trueList = crearllista($$.trueList, getSquad());
																			$$.falseList = crearllista($$.falseList, getSquad()+1);
																			
																			$$.nTrue++;
																			$$.nFalse++;
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "IF %s GOTO ", castAux);
																			localC3A = emet(filAux, localC3A);
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "GOTO ");
																			localC3A = emet(filAux, localC3A);
																		}
																		
																	break;
																	case COMPTIPUS_DIF_NO_RED:
																		sprintf(string,"ERROR. Comprovacio de tipus - Tipus incorrectes expressio relacional.");
																		missatgeError(string,$1.rows, $1.columns);
																		YYERROR;
																	break;
																}
															}
														}
														else{
															sprintf(string,"ERROR. Variable sense tipus.");
															missatgeError(string,$1.rows, $1.columns);
															YYERROR;
														}
														sprintf(string,"equality_expression <- equality_expression EQ_OP relational_expression ");
														string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| equality_expression NE_OP relational_expression 	{
														if(($1.tipus != UNDEF)&&($3.tipus != UNDEF)) {
															if(($1.sizeList != UNDEF)||($3.sizeList != UNDEF)){
																sprintf(string,"ERROR. Operacio amb tipus Llista.");
																missatgeError(string,$1.rows, $1.columns);
																YYERROR;
															}
															else{
																$$.tipus = ID_INT;
																
																int comprovacio = 0;
																comprovacio = comprovacioTipus($1.tipus, $3.tipus);
																switch (comprovacio) {
																	case COMPTIPUS_IGUALS:
																		$$.tipus = $1.tipus;
																		
																		/*-----------------C3A------------------*/
																		if (isFor == 0){	
																			filAux = inicialitzarFil(filAux);
																			
																			sprintf(cast, "%s %s %s", $1.lexemac3a, obtainCompare("NE", $1.tipus), $3.lexemac3a);
																			
																			$$.trueList = (int *)malloc(sizeof(int)*20);
																			$$.falseList = (int *)malloc(sizeof(int)*20);
																			
																			$$.trueList = crearllista($$.trueList, getSquad());
																			$$.falseList = crearllista($$.falseList, getSquad()+1);
																			
																			$$.nTrue++;
																			$$.nFalse++;
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "IF %s GOTO ", cast);
																			localC3A = emet(filAux, localC3A);
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "GOTO ");
																			localC3A = emet(filAux, localC3A);
																		}
																	break;
																	case COMPTIPUS_DIF_RED_PRIMER:
																		$$.tipus = $1.tipus;
																	
																		/*-----------------C3A------------------*/
																		if (isFor == 0){	
																			cast = nouTemp();
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast($1.tipus, $3.tipus, COMPTIPUS_DIF_RED_PRIMER), $3.lexemac3a);
																			localC3A = emet(filAux, localC3A);
																			
																			sprintf(castAux, "%s %s %s", $1.lexemac3a, obtainCompare("NE", $1.tipus), cast);
																			
																			$$.trueList = (int *)malloc(sizeof(int)*20);
																			$$.falseList = (int *)malloc(sizeof(int)*20);
																			
																			$$.trueList = crearllista($$.trueList, getSquad());
																			$$.falseList = crearllista($$.falseList, getSquad()+1);
																			
																			$$.nTrue++;
																			$$.nFalse++;
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "IF %s GOTO ", castAux);
																			localC3A = emet(filAux, localC3A);
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "GOTO ");
																			localC3A = emet(filAux, localC3A);
																		}
																		
																	break;
																	case COMPTIPUS_DIF_RED_SEGON:
																		$$.tipus = $3.tipus;
																		
																		/*-----------------C3A------------------*/
																		if (isFor == 0){	
																			cast = nouTemp();
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast($1.tipus, $3.tipus, COMPTIPUS_DIF_RED_SEGON), $1.lexemac3a);
																			localC3A = emet(filAux, localC3A);
																			
																			sprintf(castAux, "%s %s %s", cast, obtainCompare("NE", $1.tipus),  $3.lexemac3a);
																			
																			$$.trueList = (int *)malloc(sizeof(int)*20);
																			$$.falseList = (int *)malloc(sizeof(int)*20);
																			
																			$$.trueList = crearllista($$.trueList, getSquad());
																			$$.falseList = crearllista($$.falseList, getSquad()+1);
																			
																			$$.nTrue++;
																			$$.nFalse++;
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "IF %s GOTO ", castAux);
																			localC3A = emet(filAux, localC3A);
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "GOTO ");
																			localC3A = emet(filAux, localC3A);
																		}
																		
																	break;
																	case COMPTIPUS_DIF_NO_RED:
																		sprintf(string,"ERROR. Comprovacio de tipus - Tipus incorrectes expressio relacional.");
																		missatgeError(string,$1.rows, $1.columns);
																		YYERROR;
																	break;
																}
															}
														}
														else{
															sprintf(string,"ERROR. Variable sense tipus.");
															missatgeError(string,$1.rows, $1.columns);
															YYERROR;
														}
														sprintf(string,"equality_expression <- equality_expression NE_OP relational_expression");
														string_output(string, $<ident>1.rows, $<ident>1.columns);}
	;
	
logical_AND_expression : equality_expression 			{sprintf(string,"logical_AND_expression <- equality_expression ");
														string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| logical_AND_expression AND_OP m equality_expression {
														if(($1.tipus != UNDEF)&&($4.tipus != UNDEF)) {
															if(($1.sizeList != UNDEF)||($4.sizeList != UNDEF)){
																sprintf(string,"ERROR. Operacio amb tipus Llista.");
																missatgeError(string,$1.rows, $1.columns);
																YYERROR;
															}
															else {
																$$.tipus = ID_INT;
																$$.trueList = (int*)malloc(sizeof(int)*20);
																$$.falseList = (int*)malloc(sizeof(int)*20);
																
																localC3A = completa($1.trueList, $1.nTrue, $3.quad, localC3A);
																$$.falseList = fusiona($$.falseList, $1.falseList, $1.nFalse, $4.falseList, $4.nFalse);
																
																$$.trueList = $4.trueList;
																$$.nTrue = $4.nTrue;
																
																$$.nFalse = $1.nFalse + $4.nFalse;
															}
														}
														else{
															sprintf(string,"ERROR. Variable sense tipus.");
															missatgeError(string,$1.rows, $1.columns);
															YYERROR;
														}
														sprintf(string,"logical_AND_expression <- logical_AND_expression AND_OP equality_expression ");
														string_output(string, $<ident>1.rows, $<ident>1.columns);}
	;
	
logical_OR_expression : logical_AND_expression  			{sprintf(string,"logical_OR_expression <- logical_AND_expression");
															string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| logical_OR_expression OR_OP m logical_AND_expression 	{
															if(($1.tipus != UNDEF)&&($4.tipus != UNDEF)) {
																if(($1.sizeList != UNDEF)||($4.sizeList != UNDEF)){
																	sprintf(string,"ERROR. Operacio amb tipus Llista.");
																	missatgeError(string,$1.rows, $1.columns);
																	YYERROR;
																}
																else {
																	$$.tipus = ID_INT;
																	$$.trueList = (int*)malloc(sizeof(int)*20);
																	$$.falseList = (int*)malloc(sizeof(int)*20);
																	
																	localC3A = completa($1.falseList, $1.nFalse, $3.quad, localC3A);
																	$$.trueList = fusiona($$.trueList, $1.trueList, $1.nTrue, $4.trueList, $4.nTrue);
																	
																	$$.falseList = $4.falseList;
																	$$.nFalse = $4.nFalse;
																	
																	$$.nTrue = $1.nTrue + $4.nTrue;
																}
															}
															else{
																sprintf(string,"ERROR. Variable sense tipus.");
																missatgeError(string,$1.rows, $1.columns);
																YYERROR;
															}
															sprintf(string,"logical_OR_expression <- logical_OR_expression OR_OP logical_AND_expression  ");
															string_output(string, $<ident>1.rows, $<ident>1.columns);}
	;
	
conditional_expression : logical_OR_expression  			{
															sprintf(string,"conditional_expression <- logical_OR_expression ");
															string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| logical_OR_expression '?' expression ':' conditional_expression	{sprintf(string,"conditional_expression <- logical_OR_expression '?' expression ':' conditional_expression ");
																		string_output(string, $<ident>1.rows, $<ident>1.columns);}
	;
	
constant_expression : conditional_expression 	{
												$$ = $1;
												sprintf(string,"constant_expression <- conditional_expression ");
												string_output(string, $<ident>1.rows, $<ident>1.columns);}
	;
	
assignment_expression : conditional_expression  		{
														$$ = $1;
														sprintf(string,"assignment_expression <- conditional_expression ");
														string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| unary_expression assignment_operator assignment_expression{
																if(($1.tipus != UNDEF)&&($3.tipus != UNDEF)) {
																	int comprovacio = 0;
																	
																	comprovacio = comprovacioTipus($1.tipus, $3.tipus);
																	
																	switch (comprovacio) {
																		case COMPTIPUS_IGUALS:
																			$$.tipus = $1.tipus;
																			
																			/*-----------------C3A------------------*/
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "%s %s %s", $1.lexemac3a, ":=", $3.lexemac3a);
																			localC3A = emet(filAux, localC3A);
																			
																			sprintf(string,"Operacio correcta del mateix tipus.");
																			missatgeTS(string,$1.rows, $1.columns);
																		break;
																		case COMPTIPUS_DIF_RED_PRIMER:
																			$$.tipus = $1.tipus;
																			
																			/*-----------------C3A------------------*/
																			cast = nouTemp();
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast($1.tipus, $3.tipus, COMPTIPUS_DIF_RED_PRIMER), $3.lexemac3a);
																			localC3A = emet(filAux, localC3A);
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "%s %s %s", $1.lexemac3a, ":=", cast);
																			localC3A = emet(filAux, localC3A);
																			
																			sprintf(string,"Comprovacio de tipus - (cast) al tipus %d ", $1.tipus);
																			missatgeWarning(string,$1.rows, $1.columns);
																		break;
																		case COMPTIPUS_DIF_RED_SEGON:
																			$$.tipus = $3.tipus;
																			
																			/*-----------------C3A------------------*/
																			cast = nouTemp();
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast($3.tipus, $1.tipus, COMPTIPUS_DIF_RED_SEGON), $3.lexemac3a);
																			localC3A = emet(filAux, localC3A);
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "%s %s %s", $1.lexemac3a, ":=", cast);
																			localC3A = emet(filAux, localC3A);
																			
																			sprintf(string,"Comprovacio de tipus - Perdua de presicio en l'assignacio (cast) al tipus %d.", $1.tipus);
																			missatgeWarning(string,$1.rows, $1.columns);
																		break;
																		case COMPTIPUS_DIF_NO_RED:
																			sprintf(string,"ERROR. Comprovacio de tipus - Tipus incorrectes a la assignacio.");
																			missatgeError(string,$1.rows, $1.columns);
																			YYERROR;
																		break;
																	}
																}
																else{
																	sprintf(string,"ERROR. Variable sense tipus.");
																	missatgeError(string,$1.rows, $1.columns);
																	YYERROR;
																}	
																	
																sprintf(string,"assignment_expression <- unary_expression assignment_operator assignment_expression ");
																string_output(string, $<ident>1.rows, $<ident>1.columns);}
	;
	
assignment_operator : '='	{sprintf(string,"assignment_operator <- '=' ");
							string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| MUL_ASSIG 	{sprintf(string,"assignment_operator <- MUL_ASSIG %s", $<ident>1.lexema);
					string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| DIV_ASSIG 	{sprintf(string,"assignment_operator <- DIV_ASSIG %s", $<ident>1.lexema);
					string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| MOD_ASSIG 	{sprintf(string,"assignment_operator <- MOD_ASSIG %s", $<ident>1.lexema);
					string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| ADD_ASSIG 	{sprintf(string,"assignment_operator <- ADD_ASSIG %s", $<ident>1.lexema);
					string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| SUB_ASSIG 	{sprintf(string,"assignment_operator <- SUB_ASSIG %s", $<ident>1.lexema);
					string_output(string, $<ident>1.rows, $<ident>1.columns);}
	;
	
expression : assignment_expression  	{sprintf(string,"expression <- assignment_expression");
										string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| expression ',' assignment_expression {sprintf(string,"expression <- expression ',' assignment_expression");
											string_output(string, $<ident>1.rows, $<ident>1.columns);}
	;
	
declaration : declaration_specifiers ';' 	{sprintf(string,"declaration <- declaration_specifiers ; ");
											string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| declaration_specifiers init_declarator_list ';' 	{
														if (isFunction == 1){
															inicialitzarInfo();
															ambit_actual=sym_get_scope();
															if (ambit_actual==SYM_ROOT_SCOPE){
																error_sym=sym_global_lookup(nom_funcio,&info);
															}
															else{
																error_sym=sym_lookup(nom_funcio,&info);
															}
															sprintf(string,"Guardada la declaracio de la funcio %s",nom_funcio);
															missatgeTS(string,$1.rows, $1.columns);
															info.isFunctionDeclaration = 1;
															isFunction = 0;
															sym_remove(nom_funcio);
															sym_add(nom_funcio,&info);
														}
														if (tipus_declaracio == ID_STRUCT){
															inicialitzarInfo();
															ambit_actual=sym_get_scope();
															if (ambit_actual==SYM_ROOT_SCOPE){
																error_sym=sym_global_lookup(nom_id,&info);
															}
															else{
																error_sym=sym_lookup(nom_id,&info);
															}
															sprintf(string,"Guardat el tipus d'struct de %s amb %s",$2.lexema, $1.lexema);
															missatgeTS(string,$1.rows, $1.columns);
															
															strcpy(info.valor, $1.lexema);
															
															sym_remove(nom_id);
															sym_add(nom_id,&info);
															
															filaAux = inicialitzarFila(filaAux);
															filaAux.nom = $2.lexema;
															filaAux.mida = obtenirMidaStruct(info.valor);
															
															if (ambit_actual==SYM_ROOT_SCOPE){
																filaAux.offset = offsetG;
																offsetG = filaAux.mida + offsetG;
																globalRA = introduirFila(filaAux, globalRA);
															}
															else{
																filaAux.offset = offsetL;
																offsetL = filaAux.mida + offsetL;
																localRA = introduirFila(filaAux, localRA);
															}
															
														}
														sprintf(string,"declaration <- declaration_specifiers init_declarator_list ;");
														string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| TYPEDEF declaration_specifiers declarator ';' 	{
														if(isStruct == 0){
															inicialitzarInfo();
															ambit_actual=sym_get_scope();
															if (ambit_actual==SYM_ROOT_SCOPE){
																error_sym=sym_global_lookup($3.lexema,&info);
															}
															else{
																error_sym=sym_lookup($3.lexema,&info);
															}
															
															if(error_sym == SYMTAB_OK){
																sprintf(string,"(TS) Trobat l'identificador %s a la TS.", $3.lexema);
																missatgeTS(string,$3.rows, $3.columns);
																if(info.tipus == UNDEF){
																	info.tipus = ID_TYPEDEF;
																	info.tipusTypedef = tipus_declaracio;
																	sym_remove(nom_id);
																	sym_add(nom_id,&info);
																	sprintf(string,"Modificat el tipus de l'identificador %s amb tipus TYPEDEF que es %d", $3.lexema, info.tipusTypedef);
																	missatgeTS(string,$1.rows, $1.columns);
																}
																else{
																	sprintf(string,"ERROR. Variable ja definida.");
																	missatgeError(string,$1.rows, $1.columns);
																}	
															}
															else{
																sprintf(string,"ERROR. Variable no definida.");
																missatgeTS(string,$1.rows, $1.columns);
															}
														} 
														else{
															
															strcpy(info.lexema, $3.lexema);
															info.tipus = ID_TYPEDEF;
															info.tipusTypedef = ID_STRUCT;
															
															ambit_actual = sym_get_scope();
															if (ambit_actual==SYM_ROOT_SCOPE){
																error_sym=sym_global_add(nom_id,&info);
															}
															else{
																error_sym=sym_add(nom_id,&info);
															}
															
															sprintf(string,"TYPEDEF %s introduit a la TS com a STRUCT.", nom_id);
															missatgeTS(string,$1.rows, $1.columns);
															
															isStruct = 0;
														}
														sprintf(string,"declaration <- TYPEDEF declaration_specifiers declarator ;");
														string_output(string, $<ident>1.rows, $<ident>1.columns);} 
	|	TYPEDEF error declarator ';' {	sprintf(string,"ERROR. TYPEDEF mal declarat.");
										missatgeError(string,$1.rows, $1.columns);
										yyerrok;}
	
	|	TYPEDEF declaration_specifiers error ';' {	sprintf(string,"ERROR. TYPEDEF mal declarat.");
													missatgeError(string,$1.rows, $1.columns);
													yyerrok;}

	| error ';' {yyerrok;}
	;
	
declaration_specifiers : type_specifier 	{
											$$=$1;
											sprintf(string,"declaration_specifiers <- type_specifier ");
											string_output(string, $<ident>1.rows, $<ident>1.columns);}
	;
	
init_declarator_list : init_declarator			{sprintf(string,"init_declarator_list <- init_declarator ");
												string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| init_declarator_list ',' init_declarator 	{sprintf(string,"init_declarator_list <- init_declarator_list ',' init_declarator ");
												string_output(string, $<ident>1.rows, $<ident>1.columns);}
	;
	
init_declarator : declarator 		{
									inicialitzarInfo();
									ambit_actual=sym_get_scope();
									if (ambit_actual==SYM_ROOT_SCOPE){
										error_sym=sym_global_lookup($1.lexema,&info);
									}
									else{
										error_sym=sym_lookup($1.lexema,&info);
									}
									
									if(error_sym == SYMTAB_OK){
										sprintf(string,"(TS) Trobat l'identificador %s a la TS.", $1.lexema);
										missatgeTS(string,$1.rows, $1.columns);
										if(info.tipus == UNDEF){
											info.tipus = tipus_declaracio;
											
											sym_remove(nom_id);
											sym_add(nom_id,&info);
											sprintf(string,"Modificat el tipus de l'identificador %s amb tipus %d", $1.lexema, info.tipus);
											missatgeTS(string,$1.rows, $1.columns);
											
											filaAux = inicialitzarFila(filaAux);
											
											filaAux.nom = $1.lexema;
											
											if(info.sizeList > -1){
												filaAux.mida = obtenirMida(info.tipus);
												if (ambit_actual==SYM_ROOT_SCOPE){
													filaAux.offset = offsetG;
													offsetG = (filaAux.mida * info.sizeList) + offsetG;
													globalRA = introduirFila(filaAux, globalRA);
												}
												else{
													filaAux.offset = offsetL;
													offsetL = (filaAux.mida * info.sizeList) + offsetL;
													localRA = introduirFila(filaAux, localRA);
												}
											}else if (info.tipus != ID_STRUCT) {
												filaAux.mida = obtenirMida(info.tipus);
												if (ambit_actual==SYM_ROOT_SCOPE){
													
													filaAux.offset = offsetG;
													offsetG += filaAux.mida;
													globalRA = introduirFila(filaAux, globalRA);
													
												}
												else{
													filaAux.offset = offsetL;
													offsetL += filaAux.mida;
													localRA = introduirFila(filaAux, localRA);
												}
											}
										}
										else if (info.tipus == FUNCTION){
										}
										else{
											sprintf(string,"ERROR. Variable ja definida.");
											missatgeError(string,$1.rows, $1.columns);
										}
									}
									else{
										sprintf(string,"ERROR. Variable no definida.");
										missatgeTS(string,$1.rows, $1.columns);
									}
									
									sprintf(string,"init_declarator <- declarator ");
									string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| declarator '=' initializer 	{
									inicialitzarInfo();
									ambit_actual=sym_get_scope();
									if (ambit_actual==SYM_ROOT_SCOPE){
										error_sym=sym_global_lookup($1.lexema,&info);
									}
									else{
										error_sym=sym_lookup($1.lexema,&info);
									}
									if(error_sym == SYMTAB_OK){
										sprintf(string,"(TS) Trobat l'identificador %s a la TS.", $1.lexema);
										missatgeTS(string,$1.rows, $1.columns);
										if(info.tipus == UNDEF){
											if(info.sizeList == UNDEF){
												if($1.tipus == $3.tipus){
													$$.tipus = $3.tipus;
													info.tipus = tipus_declaracio;
													strcpy(info.valor, $3.lexema);
													sym_remove(nom_id);
													sym_add(nom_id,&info);
													sprintf(string,"Modificat el tipus de l'identificador %s amb tipus %d", $1.lexema, info.tipus);
													missatgeTS(string,$1.rows, $1.columns);
													
												}else{
													sprintf(string,"ERROR. Tipus incorrectes en l'assignacio.");
													missatgeError(string,$1.rows, $1.columns);
													YYERROR;
												}	
											}
											/* si es una llista*/
											else{
												$$.tipus = $3.tipus;
												info.tipus = tipus_declaracio;
												if(info.sizeList != nparams_initializer_list){
													sprintf(string,"ERROR. El numero de parametres no coincideix amb la declaracio.");
													missatgeWarning(string,$1.rows, $1.columns);
												}
												else {
													sym_remove(nom_id);
													sym_add(nom_id,&info);
												}
											}
										}
										else {
											sprintf(string,"ERROR. Variable ja inicialitzada.");
											missatgeError(string,$1.rows, $1.columns);
											YYERROR;
										}
										
									}
									else{
										sprintf(string,"ERROR. Variable no definida.");
										missatgeError(string,$1.rows, $1.columns);
										YYERROR;
									}
									sprintf(string,"init_declarator <- declarator '=' initializer");
									string_output(string, $<ident>1.rows, $<ident>1.columns);}
;
	
type_specifier : VOID 	{
						tipus_declaracio = ID_VOID;
						$$.tipus = ID_VOID;
						sprintf(string,"type_specifier <- VOID ");
						string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| CHAR 				{
						tipus_declaracio = ID_CHAR;
						$$.tipus = ID_CHAR;
						sprintf(string,"type_specifier <- CHAR ");
						string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| SHORT 			{
						tipus_declaracio = ID_SHORT;
						$$.tipus = ID_SHORT;
						sprintf(string,"type_specifier <- SHORT ");
						string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| INT 				{
						
						tipus_declaracio = ID_INT;
						$$.tipus = ID_INT;
						sprintf(string,"type_specifier <- INT ");
						string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| LONG 				{
						tipus_declaracio = ID_LONG;
						$$.tipus = ID_LONG;
						sprintf(string,"type_specifier <- LONG ");
						string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| FLOAT 			{
						tipus_declaracio = ID_FLOAT;
						$$.tipus = ID_FLOAT;
						sprintf(string,"type_specifier <- FLOAT ");
						string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| DOUBLE 			{
						tipus_declaracio = ID_DOUBLE;
						$$.tipus = ID_DOUBLE;
						sprintf(string,"type_specifier <- DOUBLE ");
						string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| struct_or_union_specifier {
								
								sprintf(string,"type_specifier <- struct_or_union_specifier");
								string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| typedef_name 		{
						
						sprintf(string,"type_specifier <- typedef_name ");
						string_output(string, $<ident>1.rows, $<ident>1.columns);}
	;
	
typedef_name : TYPEDEF_IDENTIFIER 	{
									inicialitzarInfo();
									
									ambit_actual=sym_get_scope();
									
									if (ambit_actual==SYM_ROOT_SCOPE){
										error_sym=sym_global_lookup($1.lexema,&info);
									}
									else{
										error_sym=sym_lookup($1.lexema,&info);
									}
									
									if(error_sym == SYMTAB_OK){
										sprintf(string,"Trobat l'identificador %s a la TS.", $1.lexema);
										missatgeTS(string,$1.rows, $1.columns);
										$$.tipus=info.tipusTypedef;
										tipus_declaracio = info.tipusTypedef;
									}
									else{
										sprintf(string,"ERROR. Variable no definida.");
										missatgeError(string,$1.rows, $1.columns);
										YYERROR;
									}
									
									sprintf(string,"typedef_name <- TYPEDEF_IDENTIFIER ");
									string_output(string, $<ident>1.rows, $<ident>1.columns);}
	;
	
struct_or_union_specifier : struct_or_union  IDENTIFIER  '{' struct_declaration_list '}' 	{
																						sprintf(string,"struct_or_union_specifier <- struct_or_union IDENTIFIER '{' struct_declaration_list '}'");
																						string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| struct_or_union '{' struct_declaration_list '}' 									{
																						
																						sprintf(string,"struct_or_union_specifier <- struct_or_union '{' struct_declaration_list '}' ");
																						string_output(string, $<ident>1.rows, $<ident>1.columns);}
	;
	
struct_or_union : STRUCT 	{
							isStruct = 1;
							
							inicialitzarInfo();
									
							info.tipus = ID_TYPEDEF;
							info.tipusFunction = STRUCT;
							info.nParamsFuncio = 0;
							
							sprintf(string,"struct_or_union <- STRUCT ");
							string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| UNION 				{sprintf(string,"struct_or_union <- UNION ");
							string_output(string, $<ident>1.rows, $<ident>1.columns);}
	;
	
struct_declaration_list : struct_declaration 		{sprintf(string,"struct_declaration_list <- struct_declaration ");
													string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| struct_declaration_list struct_declaration	{sprintf(string,"struct_declaration_list <- struct_declaration_list struct_declaration ");
													string_output(string, $<ident>1.rows, $<ident>1.columns);}
	;
	
struct_declaration : specifier_qualifier_list struct_declarator_list ';' 	{
																			info.parametres[info.nParamsFuncio].lexema = (char *)malloc(sizeof(char)*20);
																			strcpy(info.parametres[info.nParamsFuncio].lexema, $2.lexema);
																			info.parametres[info.nParamsFuncio].type = $1.tipus;
																			info.nParamsFuncio++;
																			
																			
																			sprintf(string,"Parametre %s de tipus %d introduit al struct.", $2.lexema, $1.tipus);
																			missatgeTS(string,$2.rows, $2.columns);
																			
																			
																			sprintf(string,"struct_declaration <- specifier_qualifier_list struct_declarator_list ';' ");
																			string_output(string, $<ident>1.rows, $<ident>1.columns);}
	;
	
struct_declarator_list : struct_declarator 			{sprintf(string,"struct_declarator_list <- struct_declarator");
													string_output(string, $<ident>1.rows, $<ident>1.columns);}
	| struct_declarator_list ',' struct_declarator	{sprintf(string,"struct_declarator_list <- struct_declarator_list ',' struct_declarator");
													string_output(string, $<ident>1.rows, $<ident>1.columns);}
	;

struct_declarator : declarator 	{
									
									
									sprintf(string,"struct_declarator <- declarator");
									string_output(string,$<ident>1.rows,$<ident>1.columns);}
	;
	
declarator : IDENTIFIER 	{
							nom_id=(char *)malloc(sizeof(char)*$1.lenght);
							strncpy(nom_id, $1.lexema, $1.lenght);
							if (isStruct == 0){
								inicialitzarInfo();
								ambit_actual = sym_get_scope();
								
								
								strcpy(info.lexema, nom_id);
								info.tipus = UNDEF;
								
								$$.tipus = tipus_declaracio;
								
								info.ambit = ambit_actual;
								
								if(isFunction == 0){
										
										if (ambit_actual == SYM_ROOT_SCOPE){            
											error_sym = sym_global_add(nom_id,&info);
										}                                                
										else{                                            
											error_sym = sym_add(nom_id,&info);        
										}                                          
										if(error_sym == SYMTAB_OK){
											if(isFunction == 0){
												if(ambit_actual == SYM_ROOT_SCOPE ){
													sprintf(string,"Creada l'entrada a la TS dins de l'ambit global %s per a l'identificador %s ",nom_programa,$1.lexema);
													missatgeTS(string,$1.rows, $1.columns);
												}
												else{
													sprintf(string,"Creada l'entrada a la TS dins de l'ambit %s per a l'identificador %s ",nom_ambit,$1.lexema);
													missatgeTS(string,$1.rows, $1.columns);
												}
											}
										}
										else{
											ambit_actual=sym_get_scope();
											error_sym=sym_global_lookup($1.lexema,&info);
											
												if(info.tipus != FUNCTION){
													sprintf(string,"ERROR. La variable ja existeix.");
													missatgeError(string,$1.rows, $1.columns);
													YYERROR;
												}
												else{
													if(tipus_declaracio != info.tipusFunction){
														sprintf(string,"ERROR. La funcio retorna un tipus incoherent a la declaracio anterior.");
														missatgeError(string,$1.rows, $1.columns);
														
														/*YYERROR;*/
													}
													else{
														numParam = 0;
														/*isFunctionDeclaration = 1;*/
													}
												}
											
										}
									
								}
								else{
									sprintf(string,"Parametre de la funcio de nom %s ", nom_id);
									missatgeTS(string,$1.rows, $1.columns);
								}
							}else{ /* quan es una declaracio dins de struct*/
								$$.tipus = tipus_declaracio;
							}
							
							sprintf(string,"declarator <- IDENTIFIER %s ", $<ident>1.lexema);
							string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| '(' declarator ')' 	{sprintf(string,"declarator <- '(' declarator ')'");
							string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| declarator '[' INTEGER_CONSTANT ']' 	{
											inicialitzarInfo();
											nparams_initializer_list = 0;
											ambit_actual=sym_get_scope();
											if (ambit_actual==SYM_ROOT_SCOPE){
												error_sym=sym_global_lookup($1.lexema,&info);
											}
											else{
												error_sym=sym_lookup($1.lexema,&info);
											}
											
											if(error_sym == SYMTAB_OK){
												sprintf(string,"(TS) Trobat l'identificador %s a la TS.", $1.lexema);
												missatgeTS(string,$1.rows, $1.columns);
												if(info.tipus == UNDEF){
													$$.tipus = $3.tipus;
													info.tipus = UNDEF;
													info.sizeList = atoi($3.lexema);
													sym_remove(nom_id);
													sym_add(nom_id,&info);
													sprintf(string,"Modificat el tipus de l'identificador %s a Llista %d posicions.", $1.lexema, info.sizeList);
													missatgeTS(string,$1.rows, $1.columns);
													
												}
												else{
													sprintf(string,"ERROR. Variable ja definida.");
													missatgeError(string,$1.rows, $1.columns);
													YYERROR;
												}	
											}
											else{
												sprintf(string,"ERROR. Variable no definida.");
												missatgeError(string,$1.rows, $1.columns);
												YYERROR;
											}
											sprintf(string,"declarator <- declarator '[' INTEGER_CONSTANT ']'");
											string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| declarator '(' {
						inicialitzarInfo();
						ambit_actual=sym_get_scope();
						if (ambit_actual==SYM_ROOT_SCOPE){
							error_sym=sym_global_lookup($1.lexema,&info);
						}
						else{
							error_sym=sym_lookup($1.lexema,&info);
						}
						
						isFunction = 1;
						
						
						nom_funcio=(char *)malloc(sizeof(char)*$1.lenght);
						strcpy(nom_funcio, $1.lexema);
						
						if(error_sym == SYMTAB_OK){
							inicialitzarInfo();
							error_sym=sym_global_lookup(nom_funcio,&info);
							if(info.isFunctionDeclaration == 0){
								info.tipus = FUNCTION;
								info.tipusFunction = tipus_declaracio;
								
								filaAux = inicialitzarFila(filaAux);
								filaAux.nom = "return";
										
								filaAux.mida = obtenirMida(info.tipusFunction);
								filaAux.offset = offsetL;
									
								offsetL += filaAux.mida;
								
								localRA = introduirFila(filaAux, localRA);
								
								info.nParamsFuncio = 0;
								sym_remove(nom_funcio);
								sym_global_add(nom_funcio,&info);
								sprintf(string,"Modificat el tipus de l'identificador %s. Es una funcio.", $1.lexema);
								missatgeTS(string,$1.rows, $1.columns);
								isFunction = 1;
							}
						}
						
					} parameter_list ')' 	{
											/*isFunction = 0;*/
											
											sprintf(string,"declarator <- declarator '(' parameter_list ')'");
											string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| declarator '(' identifier_list ')' 	{sprintf(string,"declarator <- declarator '(' identifier_list ')'");
											string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| declarator '(' ')' 					{
											inicialitzarInfo();
											ambit_actual=sym_get_scope();
											if (ambit_actual==SYM_ROOT_SCOPE){
												error_sym=sym_global_lookup($1.lexema,&info);
											}
											else{
												error_sym=sym_lookup($1.lexema,&info);
											}
											
											nom_funcio=(char *)malloc(sizeof(char)*$1.lenght);
											strcpy(nom_funcio, $1.lexema);
											
											if(error_sym == SYMTAB_OK){
												if(info.tipus == UNDEF){
													info.tipus = FUNCTION;
													info.tipusFunction = tipus_declaracio;
													
													/*Funcio de CL2*/
													if (info.tipusFunction != ID_VOID){
														filaAux = inicialitzarFila(filaAux);
														filaAux.nom = "return";
																
														filaAux.mida = obtenirMida(info.tipusFunction);
														filaAux.offset = offsetL;
															
														offsetL += filaAux.mida;
														
														localRA = introduirFila(filaAux, localRA);
													}
													
													info.nParamsFuncio = 0;
													sym_global_remove(nom_id);
													sym_global_add(nom_id,&info);
													sprintf(string,"Modificat el tipus de l'identificador %s. Es una funcio.", $1.lexema);
													missatgeTS(string,$1.rows, $1.columns);
													
												}
											}
											
											
											isFunction = 0;
											sprintf(string,"declarator <- declarator '(' ')'");
											string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| declarator '(' error ')' {yyerrok;}
	;
	
parameter_list : parameter_declaration 			{sprintf(string,"parameter_list <- parameter_declaration");
												string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| parameter_list ',' parameter_declaration 	{sprintf(string,"parameter_list <- parameter_list ',' parameter_declaration");
												string_output(string,$<ident>1.rows,$<ident>1.columns);}
	;
	
parameter_declaration : declaration_specifiers declarator {
											inicialitzarInfo();
											/*Recuperem la funcio per guardar-hi el parametre*/
											error_sym = sym_global_lookup(nom_funcio,&info);
											if(info.isFunctionDeclaration == 1){
													inicialitzarInfo();
												
													/*Recuperem la funcio per guardar-hi el parametre*/
													error_sym=sym_global_lookup(nom_funcio,&info);
												
												if (info.parametres[numParam].type != $1.tipus){
													if (numParam >= info.nParamsFuncio){
														sprintf(string,"ERROR. El parametre numero %d de la funcio no esta a la declaracio.", numParam+1);
														missatgeError(string,$1.rows, $1.columns);
														info.nParamsFuncio++;
													}
													else{
														sprintf(string,"ERROR. El tipus de la variable %d no coincideix amb la declaracio.", numParam+1);
														missatgeError(string,$1.rows, $1.columns);
													}
													info.parametres[numParam].lexema = (char *)malloc(sizeof($2.lexema));
													info.parametres[numParam].hasName = 1;
													info.parametres[numParam].type = $1.tipus;
													strcpy(info.parametres[numParam].lexema, $2.lexema);
													sym_global_remove(nom_funcio);
													sym_global_add(nom_funcio,&info);
													numParam++;
												}
												else{
													info.parametres[numParam].lexema = (char *)malloc(sizeof($2.lexema));
													info.parametres[numParam].hasName = 1;
													strcpy(info.parametres[numParam].lexema, $2.lexema);
													sym_global_remove(nom_funcio);
													sym_global_add(nom_funcio,&info);
													numParam++;
												}
											}
											else if (isFunction == 1){
												inicialitzarInfo();
												
												/*Recuperem la funcio per guardar-hi el parametre*/
												error_sym=sym_global_lookup(nom_funcio,&info);
												info.parametres[info.nParamsFuncio].lexema = (char *)malloc(sizeof($2.lexema)+1);
												
												info.parametres[info.nParamsFuncio].type= $1.tipus;
												info.parametres[info.nParamsFuncio].hasName = 1;
												
												strcpy(info.parametres[info.nParamsFuncio].lexema, $2.lexema);
												
												info.nParamsFuncio++;
												numParam++;
												
												sym_global_remove(nom_funcio);
												sym_global_add(nom_funcio,&info);
												
												filaAux = inicialitzarFila(filaAux);
												filaAux.nom = $2.lexema;
												
												filaAux.mida = obtenirMida($1.tipus);
												filaAux.offset = offsetL;
												offsetL += filaAux.mida;
												localRA = introduirFila(filaAux, localRA);
												
												sprintf(string,"Guardat l'identificador %s com a parametre de la funcio %s.", $2.lexema, nom_funcio);
												missatgeTS(string,$1.rows, $1.columns);
											}
											sprintf(string,"parameter_declaration <- declaration_specifiers declarator");
											string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| declaration_specifiers abstract_declarator {sprintf(string,"parameter_declaration <- declaration_specifiers abstract_declarator");
									string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| declaration_specifiers {
							inicialitzarInfo();
							/*Recuperem la funcio per guardar-hi el parametre*/
							error_sym = sym_global_lookup(nom_funcio,&info);
							if(info.isFunctionDeclaration == 1){
								inicialitzarInfo();
								
								/*Recuperem la funcio per guardar-hi el parametre*/
								error_sym=sym_global_lookup(nom_funcio,&info);
								
								if (info.parametres[numParam].type != $1.tipus){
									sprintf(string,"ERROR. Variable no definida.");
									missatgeError(string,$1.rows, $1.columns);
									numParam++;
								}
								else{
									numParam++;
								}
							}
							else if (isFunction == 1){
								inicialitzarInfo();
								/*Recuperem la funcio per guardar-hi el parametre*/
								error_sym=sym_global_lookup(nom_funcio,&info);
								
								info.parametres[info.nParamsFuncio].lexema = (char *)malloc(sizeof(4)+1);
								
								info.parametres[info.nParamsFuncio].type= $1.tipus;
								info.parametres[info.nParamsFuncio].hasName = 0;
								strcpy(info.parametres[info.nParamsFuncio].lexema, "NULL");
								
								info.nParamsFuncio++;
								sym_global_remove(nom_funcio);
								sym_global_add(nom_funcio,&info);
								
								filaAux = inicialitzarFila(filaAux);
								filaAux.nom = "NULL";
								
								filaAux.mida = obtenirMida($1.tipus);
								filaAux.offset = offsetL;
								
								offsetL += filaAux.mida;
								
								localRA = introduirFila(filaAux, localRA);
								
								sprintf(string,"Guardat el tipus %d com a parametre de la funcio %s.", $1.tipus, nom_funcio);
								missatgeTS(string,$1.rows, $1.columns);
							}
							sprintf(string,"parameter_declaration <- declaration_specifiers");
							string_output(string,$<ident>1.rows,$<ident>1.columns);}
	;
	
identifier_list : IDENTIFIER {		
									sprintf(string,"identifier_list <- IDENTIFIER");
									string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| identifier_list ',' IDENTIFIER {
									
									sprintf(string,"identifier_list <- identifier_list ',' IDENTIFIER ");
									string_output(string,$<ident>1.rows,$<ident>1.columns);}
	;
	
type_name : specifier_qualifier_list {
									$$ = $1;
									sprintf(string,"type_name <- specifier_qualifier_list");
									string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| specifier_qualifier_list abstract_declarator {sprintf(string,"type_name <- specifier_qualifier_list abstract_declarator");
									string_output(string,$<ident>1.rows,$<ident>1.columns);}
	;
	
specifier_qualifier_list : type_specifier specifier_qualifier_list {sprintf(string,"specifier_qualifier_list <- type_specifier specifier_qualifier_list");
									string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| type_specifier {sprintf(string,"specifier_qualifier_list <- type_specifier");
									string_output(string,$<ident>1.rows,$<ident>1.columns);}
	;
	
abstract_declarator : '(' abstract_declarator ')' {sprintf(string,"abstract_declarator <- '(' abstract_declarator ')'");
									string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| '[' INTEGER_CONSTANT ']' {sprintf(string,"abstract_declarator <- '[' INTEGER_CONSTANT ']'");
									string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| abstract_declarator '[' INTEGER_CONSTANT ']' {sprintf(string,"abstract_declarator <- abstract_declarator '[' INTEGER_CONSTANT ']'");
									string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| '(' ')' {sprintf(string,"abstract_declarator <- '(' ')'");
									string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| '(' parameter_list ')' {sprintf(string,"abstract_declarator <- '(' parameter_list ')'");
									string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| abstract_declarator '(' ')' {sprintf(string,"abstract_declarator <- abstract_declarator '(' ')'");
									string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| abstract_declarator '(' parameter_list ')' {sprintf(string,"abstract_declarator <- abstract_declarator '(' parameter_list ')'");
									string_output(string,$<ident>1.rows,$<ident>1.columns);}
	;
	
initializer : assignment_expression {sprintf(string,"initializer <- assignment_expression");
									string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| '{' initializer_list '}' {sprintf(string,"initializer <- '{' initializer_list '}'");
								string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| '{' initializer_list ',' '}' {sprintf(string,"initializer <- '{' initializer_list ',' '}'");
									string_output(string,$<ident>1.rows,$<ident>1.columns);}
	;
	
initializer_list : initializer  {
								if($1.tipus == tipus_declaracio){
									nparams_initializer_list ++;
									$$.tipus = $1.tipus;
								}else{
									sprintf(string,"ERROR. Tipus incorrectes en la incialitzacio de la taula.");
									missatgeError(string,$1.rows, $1.columns);
									YYERROR;
								}
								sprintf(string,"initializer_list <- initializer");
								string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| initializer_list ',' initializer 	{
										if($3.tipus == tipus_declaracio){
											nparams_initializer_list ++;
											$$.tipus = $3.tipus;
										}else{
											sprintf(string,"ERROR. Tipus incorrectes en la incialitzacio de la taula.");
											missatgeError(string,$1.rows, $1.columns);
											YYERROR;
										}
										sprintf(string,"initializer_list <- initializer_list ',' initializer ");
										string_output(string,$<ident>1.rows,$<ident>1.columns);}
	;
	
statement : labeled_statement 	{sprintf(string,"statement <- abeled_statement");
								string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| compound_statement 		{sprintf(string,"statement <- compound_statement");
								string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| expression_statement 		{sprintf(string,"statement <- expression_statement");
								string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| selection_statement 		{sprintf(string,"statement <- selection_statement");
								string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| iteration_statement 		{sprintf(string,"statement <- iteration_statement");
								string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| jump_statement 			{sprintf(string,"statement <- jump_statement");
								string_output(string,$<ident>1.rows,$<ident>1.columns);}
	;
	
labeled_statement : CASE constant_expression ':' statement 	{sprintf(string,"labeled_statement <- CASE constant_expression ':' statement");
															string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| DEFAULT ':' statement		{sprintf(string,"labeled_statement <- DEFAULT ':' statement");
								string_output(string,$<ident>1.rows,$<ident>1.columns);}
	;
	
compound_statement : '{' { 
							if(isReturn == 0){
							/* buscar el nom de la funcio i mirar el tipus, si no es void < warning */
							inicialitzarInfo();
							
							ambit_actual=sym_get_scope();
							error_sym=sym_global_lookup(nom_funcio,&info);
							
							if(error_sym == SYMTAB_OK){
								if(info.tipusFunction != ID_VOID){
									sprintf(string,"No hi ha sentencia RETURN. falta retornar un valor de tipus %d ", info.tipusFunction);
									missatgeWarning(string,$1.rows, $1.columns);
								}
							}
						  }
						}
						'}'  	{sprintf(string,"compound_statement <- '{' '}' ");
								string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| 	'{' 	declaration_list  {
								if(isReturn == 0){
								  	/* buscar el nom de la funcio i mirar el tipus, si no es void return warning */
								  	inicialitzarInfo();
							
									ambit_actual=sym_get_scope();
									error_sym=sym_global_lookup(nom_funcio,&info);
									
									if(error_sym == SYMTAB_OK){
										if(info.tipusFunction != ID_VOID){
											sprintf(string,"No hi ha sentencia RETURN. falta retornar un valor de tipus %d ", info.tipusFunction);
											missatgeWarning(string,$1.rows, $1.columns);
										}
									}
								}
								}	'}'  {sprintf(string,"compound_statement <- '{' declaration_list '}'");
								string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| '{' statement_list '}' 	{			$$.nextList = (int *) malloc(sizeof(int)*20);
												$$.nextList = $2.nextList;
												$$.nNext = $2.nNext;
												
												sprintf(string,"compound_statement <- '{' statement_list '}' ");
												string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| '{'  declaration_list statement_list {  
										  if(isReturn == 0){
										  	/* buscar el nom de la funcio i mirar el tipus, si no es void return warning */
										  	inicialitzarInfo();
									
											ambit_actual=sym_get_scope();
											error_sym=sym_global_lookup(nom_funcio,&info);
											
											if(error_sym == SYMTAB_OK){
												if(info.tipusFunction != ID_VOID){
													sprintf(string,"No hi ha sentencia RETURN. Falta retornar un valor de tipus %d ", info.tipusFunction);
													missatgeWarning(string,$1.rows, $1.columns);
												}
											}
										  }
										  } '}' {sprintf(string,"compound_statement <- '{' declaration_list statement_list '}'");
												string_output(string,$<ident>1.rows,$<ident>1.columns);}
	;
	
statement_list : statement  	{
								
								/* la llista de seguentes es copia */
								
								sprintf(string,"statement_list <- statement ");
								string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| statement_list m statement  {
									
									localC3A = completa($1.nextList, $1.nNext, $2.quad, localC3A);
									
									$$.nextList = $3.nextList;
									$$.nNext = $3.nNext;
									
									sprintf(string,"statement_list <- statement_list statement ");
									string_output(string,$<ident>1.rows,$<ident>1.columns);}
	;
	
expression_statement : ';'  	{sprintf(string,"expression_statement <- ';' ");
								string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| expression ';' 			{sprintf(string,"expression_statement <- expression ';' ");
								string_output(string,$<ident>1.rows,$<ident>1.columns);}
	;

m : {
		 $$.quad = getSquad();
	}
	;

n : {
		$$.nextList = (int*)malloc(20*sizeof(int));
		$$.nextList = crearllista($$.nextList, getSquad());
		$$.nNext++;
		
		filAux = inicialitzarFil(filAux);
		sprintf(filAux.info, "GOTO ");
		localC3A = emet(filAux, localC3A);	 
	}
	;
	
selection_statement : IF '(' expression ')' m  statement  %prec IF_PREC	{
															
															/*------------------------C3A----------------------*/
															localC3A = completa($3.trueList, $3.nTrue, $5.quad, localC3A);
															
															$$.nextList = (int*)malloc(20*sizeof(int));
															$$.nextList = fusiona($$.nextList, $3.falseList, $3.nFalse, $6.nextList, $6.nNext);
															
															$$.nNext = $3.nFalse + $6.nNext;
															
															/*localC3A = completa($3.falseList, $3.nFalse, $7.quad, localC3A);*/
															
															sprintf(string,"selection_statement <- aux_selected_statement");
															string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| IF '(' expression ')' m  statement  ELSE  n  m  statement 	{
														
														/*------------------------C3A----------------------*/
														localC3A = completa($3.trueList, $3.nTrue, $5.quad, localC3A);
														localC3A = completa($3.falseList, $3.nFalse, $9.quad, localC3A);
														
														$$.nextList = (int *)malloc(sizeof(int)*20);
														
														/* utilitzada per a llista auxiliar per als dos fusiona*/
														$2.nextList = (int *)malloc(sizeof(int)*20);
														
														$2.nextList = fusiona($2.nextList, $8.nextList, $8.nNext, $10.nextList, $10.nNext);
														$2.nNext = $8.nNext + $10.nNext;
														
														$$.nextList = fusiona($$.nextList, $6.nextList, $6.nNext, $2.nextList, $2.nNext);
														$$.nNext = $6.nNext + $2.nNext;
														
														/*localC3A = completa($9.nextList, $9.nNext, $12.quad, localC3A);*/
														
														sprintf(string,"selection_statement <- IF '(' expression ')' statement ELSE statement");
														string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| SWITCH '(' expression ')' statement  				{sprintf(string,"selection_statement <- SWITCH '(' expression ')' statement");
														string_output(string,$<ident>1.rows,$<ident>1.columns);}
	;
	
q : '(' expression ';' {
							/* activem el detector de fors */
							isFor = 1;
							/*filAux = inicialitzarFil(filAux);*/
							/*sprintf(filAux.info, "%s", $2.lexemac3a);*/
							/*localC3A = emet(filAux, localC3A);	 */
							$$.lexemac3a = $2.lexemac3a;
							
							sprintf(string,"q <- FOR m '(' expression ';' ");
							string_output(string,$<ident>1.rows,$<ident>1.columns);
						}
	;	
	
p : q expression ';' {
						isFor = 0;
						$$.lexemac3a = $1.lexemac3a;
						$$.quad = getSquad();
						
						sprintf(cast, "%s %s %s", $1.lexemac3a, obtainCompare("LE", $2.tipus), $2.lexemac3a);
						
						filAux = inicialitzarFil(filAux);
						sprintf(filAux.info, "IF %s GOTO %d", cast, $$.quad + 2);
						localC3A = emet(filAux, localC3A); 
						
						$$.nextList = (int *)malloc(sizeof(int)*20);
						$$.nextList = crearllista($$.nextList, getSquad());
						$$.nNext++;
						
						filAux = inicialitzarFil(filAux);
						sprintf(filAux.info, "GOTO ");
						localC3A = emet(filAux, localC3A);
						
						sprintf(string,"p <- q expression ';' ");
						string_output(string,$<ident>1.rows,$<ident>1.columns);
					}
	;
	
s : p expression ')' statement 	{
									/* completa la llista de seguents del statement cap al increment i el salt al principi del for */
									localC3A = completa($4.nextList, $4.nNext, getSquad(), localC3A);
									
									filAux = inicialitzarFil(filAux);
									sprintf(filAux.info, "%s := %s + 1", $1.lexemac3a, $1.lexemac3a);
									localC3A = emet(filAux, localC3A); 
									
									filAux = inicialitzarFil(filAux);
									sprintf(filAux.info, "GOTO %d", $1.quad);
									localC3A = emet(filAux, localC3A);
									
									$$.nextList = $1.nextList;
									$$.nNext = $1.nNext;
									
									localC3A = completa($1.nextList, $1.nNext, getSquad(), localC3A);
									
									
									
									sprintf(string,"s <- p expression ')' statement ");
									string_output(string,$<ident>1.rows,$<ident>1.columns);
								}
	;
	
iteration_statement : WHILE '(' m expression ')' m statement {
															
															localC3A = completa($4.trueList, $4.nTrue, $6.quad, localC3A);
															localC3A = completa($7.nextList, $7.nNext, $3.quad, localC3A);
															
															$$.nextList = $4.falseList;
															$$.nNext = $4.nFalse;
															
															filAux = inicialitzarFil(filAux);
															sprintf(filAux.info, "GOTO %d", $3.quad);
															localC3A = emet(filAux, localC3A);	 
															
															/* el getQuad apunta a la seguent lina despres del while i no posem m a la regla */
															/* com a les altres per no haver de partir la regla*/
															/*localC3A = completa($4.falseList, $4.nFalse, getSquad(), localC3A);*/
															
															sprintf(string,"iteration_statement <- WHILE '(' expression ')' statement");
															string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| DO statement WHILE '(' expression ')' ';' 			{sprintf(string,"iteration_statement <- DO statement WHILE '(' expression ')' ';'");
															string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| FOR s 												{sprintf(string,"iteration_statement <- FOR s ");
															string_output(string,$<ident>1.rows,$<ident>1.columns);
															}
		
	| FOR '(' ';' expression ';' expression ')' statement 	{sprintf(string,"iteration_statement <- FOR '(' ';' expression ';' expression ')' statement ");
															string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| FOR '(' ';' ';' expression ')' statement				{sprintf(string,"iteration_statement <- FOR '(' ';' ';' expression ')' statement ");
															string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| FOR '(' ';' ';' ')' statement 						{sprintf(string,"iteration_statement <- FOR '(' ';' ';' ')' statement");
															string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| FOR '(' expression ';' ';' expression ')' statement 	{sprintf(string,"iteration_statement <- FOR '(' expression ';' ';' expression ')' statement ");
															string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| FOR '(' expression ';' ';' ')' statement				{sprintf(string,"iteration_statement <- FOR '(' expression ';' ';' ')' statement ");
															string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| FOR '(' ';' expression ';' ')' statement 				{sprintf(string,"iteration_statement <- FOR '(' ';' expression ';' ')' statement ");
															string_output(string,$<ident>1.rows,$<ident>1.columns);}
	;
	
jump_statement : CONTINUE ';' {sprintf(string,"jump_statement <- CONTINUE ';'");
								string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| BREAK ';' {sprintf(string,"jump_statement <- BREAK ';'");
				string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| RETURN ';' {
				/* buscar el nom de la funcio i mirar el tipus, si no es void return warning */
				inicialitzarInfo();
				
				ambit_actual=sym_get_scope();
				error_sym=sym_global_lookup(nom_funcio,&info);
				
				if(error_sym == SYMTAB_OK){
					if(info.tipusFunction != ID_VOID){
						sprintf(string,"La sentencia RETURN no retorna cap valor. Ha de retornar un valor de tipus %d", info.tipusFunction);
						missatgeWarning(string,$1.rows, $1.columns);
					}
					isReturn = 1;
				}
				sprintf(string,"jump_statement <- RETURN ';'");
				string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| RETURN expression ';' {
							/* buscar el nom de la funcio i mirar el tipus, si no es void return warning */
							inicialitzarInfo();
							
							ambit_actual=sym_get_scope();
							error_sym=sym_global_lookup(nom_funcio,&info);
							
							if(error_sym == SYMTAB_OK){
							
								if(info.tipusFunction != $2.tipus){
								
									int comprovacio = 0;
																	
									comprovacio = comprovacioTipus(info.tipusFunction, $2.tipus);
									
									switch (comprovacio) {
										case COMPTIPUS_DIF_RED_PRIMER:
											/*-----------------C3A------------------*/
											cast = nouTemp();
											filAux = inicialitzarFil(filAux);
											sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast(info.tipusFunction, $2.tipus, COMPTIPUS_DIF_RED_PRIMER), $2.lexemac3a);
											localC3A = emet(filAux, localC3A);
											
											filAux = inicialitzarFil(filAux);
											sprintf(filAux.info, "%s %s %s", $2.lexemac3a, ":=", cast);
											localC3A = emet(filAux, localC3A);
											
											sprintf(string,"Comprovacio de tipus - (cast) al tipus %d ", $1.tipus);
											missatgeWarning(string,$2.rows, $2.columns);
										break;
										case COMPTIPUS_DIF_RED_SEGON:
											/*-----------------C3A------------------*/
											cast = nouTemp();
											filAux = inicialitzarFil(filAux);
											sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast(info.tipusFunction, $2.tipus, COMPTIPUS_DIF_RED_SEGON), $2.lexemac3a);
											localC3A = emet(filAux, localC3A);
											
											filAux = inicialitzarFil(filAux);
											sprintf(filAux.info, "%s %s %s", $2.lexemac3a, ":=", cast);
											localC3A = emet(filAux, localC3A);
											
											sprintf(string,"Comprovacio de tipus - Perdua de presicio en l'assignacio (cast) al tipus %d.", $1.tipus);
											missatgeWarning(string,$2.rows, $2.columns);
										break;
										case COMPTIPUS_DIF_NO_RED:
											sprintf(string,"ERROR. Comprovacio de tipus - Tipus incorrectes a la assignacio.");
											missatgeError(string,$1.rows, $1.columns);
											YYERROR;
										break;
									}
								
									sprintf(string,"La sentencia RETURN retorna un valor que no es del tipus de la funcio.");
									missatgeWarning(string,$1.rows, $1.columns);
								}
								
								isReturn = 1;
							}
							
							filAux = inicialitzarFil(filAux);
							sprintf(filAux.info, "RETURN %s", $2.lexemac3a);
							localC3A = emet(filAux, localC3A);	
							
							sprintf(string,"jump_statement <- RETURN expression ';'");
							string_output(string,$<ident>1.rows,$<ident>1.columns);}
	;
	
translation_unit : external_declaration {sprintf(string,"translation_unit <- external_declaration");
										string_output(string,$<ident>1.rows,$<ident>1.columns);
										}
	| translation_unit external_declaration {sprintf(string,"translation_unit <- translation_unit external_declaration");
											string_output(string,$<ident>1.rows,$<ident>1.columns);
											/*imprimirTaula(globalRA, "Taula global");*/}
	| translation_unit error ')' {yyerrok;}
	;
	
external_declaration : function_definition {sprintf(string,"external_declaration <- function_definition");
											string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| declaration {sprintf(string,"external_declaration <- declaration");
					string_output(string,$<ident>1.rows,$<ident>1.columns);}
	;
function_definition : declarator {
									error_sym = sym_get_scope();
									
									isFunction = 0;
									
									nom_ambit=(char *)malloc(sizeof(nom_funcio));
									strcpy(nom_ambit, nom_funcio);
									
									punter = (char *)malloc(50);
									
									error_sym=sym_push_scope();
									ambit_actual=sym_get_scope();
									
									if (error_sym!=SYMTAB_OK)
										mostraError(error_sym,(const char *)&nom_ambit);
									else {
										
										/*-----------------C3A------------------*/																				
										filAux = inicialitzarFil(filAux);
										sprintf(filAux.info, "%s %s ", "START", nom_funcio);
										localC3A = emet(filAux, localC3A);
										
										sprintf(string, "Apilat el nou ambit per a la funcio %s amb codi %d",nom_ambit,ambit_actual);
										missatgeTS(string, $1.rows, $1.columns);
									}
									
									error_sym = sym_get_scope();
									ambit_actual = sym_get_scope();
									
									inicialitzarInfo();
									
									error_sym=sym_global_lookup(nom_funcio,&info);
									
									if(error_sym == SYMTAB_OK){
										for(i = 0; i < info.nParamsFuncio; i++){
											if (info.parametres[i].hasName == 0){
												sprintf(string,"ERROR. Declaracio del parametre %d de la funcio es erroni.", i+1);
												missatgeError(string,$1.rows, $1.columns);
											} else{
												infoAux.tipus = info.parametres[i].type;
												punter = info.parametres[i].lexema;
												error_sym = sym_remove(punter);
												error_sym = sym_add(punter, &infoAux);
												sprintf(string, "Parametre %s de la funcio %s guardat com a varible local de la funcio", info.parametres[i].lexema, nom_ambit);
												missatgeTS(string,$1.rows, $1.columns);
											}
										}
										
									}
									error_sym=sym_global_lookup(nom_funcio,&info);
									if((numParam != info.nParamsFuncio) && (info.isFunctionDeclaration == 1)){
											sprintf(string,"ERROR. Numero de parametres incompatible amb la declaracio.");
											missatgeError(string,$1.rows, $1.columns);
											/*YYERROR;*/
									}
									else{
										if(info.isFunctionDeclaration == 0){
											info.tipusFunction = ID_VOID;
											error_sym = sym_global_remove(nom_funcio);
											error_sym = sym_global_add(nom_funcio, &info);
										}
										else{
											if (info.tipusFunction != ID_VOID){
												sprintf(string,"ERROR. La funcio previament declarada no es void, retorna un valor de tipus %d", info.tipusFunction);
												missatgeError(string,$1.rows, $1.columns);
												/*YYERROR;*/
											}
										}
									}
								} compound_statement {
													ambit_actual = sym_get_scope();
													error_sym = sym_pop_scope();
													
													error_sym=sym_global_lookup(nom_funcio,&info);
																										
													if (error_sym!=SYMTAB_OK){
														sprintf(string,"ERROR. No s'ha pogut desapilar el ambit %s.", nom_ambit);
														missatgeError(string,$1.rows, $1.columns);
														YYERROR;
													}else{
													
													
														sprintf(string, "Desapilat correctament l'ambit %s amb codi %d",nom_ambit,ambit_actual);
														
														
														missatgeTS(string,$1.rows, $1.columns);
														sprintf(string, "Funcio %s", nom_funcio);
														
														
														
														/*-----------------C3A----------------*/
														imprimirTaula(localRA, string, info.nParamsFuncio + 1 );
														imprimirT(localC3A);
														
														localRA = esborrarTaula(localRA);
														localC3A = esborrarT(localC3A);
														
														offsetL = 0;
													}
													isReturn = 0;
											
													sprintf(string,"function_definition <- declarator compound_statement");
													string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| declaration_specifiers declarator declaration_list compound_statement {sprintf(string,"function_definition <- declarator_specifier declarator declaration_list compound_statement");
													string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| declaration_specifiers declarator {
											isFunction = 0;
											error_sym = sym_get_scope();
											
											nom_ambit=(char *)malloc(sizeof(nom_funcio));
											strcpy(nom_ambit, nom_funcio);
											
											punter = (char *)malloc(50);
											
											error_sym=sym_push_scope();
											ambit_actual=sym_get_scope();
											
											if (error_sym!=SYMTAB_OK)
												mostraError(error_sym,(const char *)&nom_ambit);
											else {
												/*-----------------C3A------------------*/																								
												filAux = inicialitzarFil(filAux);
												sprintf(filAux.info, "%s %s ", "START", nom_funcio);
												localC3A = emet(filAux, localC3A);
												
												sprintf(string, "Apilat el nou ambit per a la funcio %s amb codi %d",nom_ambit,ambit_actual);
												missatgeTS(string, $2.rows, $2.columns);
											}
											
											error_sym = sym_get_scope();
											ambit_actual = sym_get_scope();
											
											inicialitzarInfo();
											
											error_sym=sym_global_lookup(nom_funcio,&info);
											
											if((numParam != info.nParamsFuncio) && (info.isFunctionDeclaration == 1)){ 
												sprintf(string,"ERROR. Numero de parametres incompatible amb la declaracio.");
												missatgeError(string,$2.rows, $2.columns);
												/*YYERROR;*/
											}
											if(error_sym == SYMTAB_OK){
												for(i = 0; i < info.nParamsFuncio; i++){
													if(i >= numParam){
													
													}
													else if (info.parametres[i].hasName == 0){
														sprintf(string,"ERROR. Declaracio del parametre %d de la funcio es erroni.", i+1);
														missatgeError(string,$2.rows, $2.columns);
														/*YYERROR;*/
													} else {
														infoAux.tipus = info.parametres[i].type;
														punter = info.parametres[i].lexema;
														error_sym = sym_remove(punter);
														error_sym = sym_add(punter, &infoAux);
														sprintf(string, "Parametre %s de la funcio %s guardat com a varible local de la funcio", punter, nom_ambit);
														missatgeTS(string,$2.rows, $2.columns);
													}
												}
											}
										}	compound_statement {
															
															ambit_actual = sym_get_scope();
															error_sym = sym_pop_scope();
															
															error_sym=sym_global_lookup(nom_funcio,&info);
															
															
															if (error_sym!=SYMTAB_OK){
																sprintf(string,"ERROR. No s'ha pogut desapilar el ambit %s.", nom_ambit);
																missatgeError(string,$2.rows, $2.columns);
															}else{
															
															
																sprintf(string, "Desapilat correctament l'ambit %s amb codi %d",nom_ambit,ambit_actual);
																
																missatgeTS(string,$2.rows, $2.columns);
																sprintf(string, "Funcio %s", nom_funcio);
																
																if (info.tipusFunction == ID_VOID || info.tipusFunction == UNDEF){
																	filAux = inicialitzarFil(filAux);
																	sprintf(filAux.info, "RETURN");
																	localC3A = emet(filAux, localC3A);
																}
																
																/*-----------------C3A----------------*/
																imprimirTaula(localRA, string, info.nParamsFuncio + 1);
																imprimirT(localC3A);
																																
																localRA = esborrarTaula(localRA);
																localC3A = esborrarT(localC3A);
																offsetL = 0;
															}
															isReturn = 0;
															sprintf(string,"function_definition <- declaration_specifiers declarator compound_statement");
															string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| declarator declaration_list compound_statement {sprintf(string,"function_definition <- declarator declaration_list compound_statement");
													string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| declaration_specifiers error compound_statement {yyerrok;}

	| error compound_statement {yyerrok;}
	;
	
declaration_list : declaration {
								sprintf(string,"declaration_list <- declaration");
								string_output(string,$<ident>1.rows,$<ident>1.columns);}
	| declaration_list declaration {
									sprintf(string,"declaration_list <- declaration_list declaration");
									string_output(string,$<ident>1.rows,$<ident>1.columns);}
	;
	
%%

void string_output(char *string, int row, int column){
	char *aux;
	aux = (char *)malloc(sizeof(char *)*200);
	sprintf(aux,"Linia %d.%d\t(Regla) %s\n",row,column, string);
	printf(aux);
	/*fprintf (yyout, aux);*/
}

void missatgeTS(char *string, int row, int column){
	char *aux;
	aux = (char *)malloc(sizeof(char *)*200);
	sprintf(aux,"Linia %d.%d\t(TS)  \t%s\n",row,column, string);
	printf(aux);
	/*fprintf (yyout, aux);*/
}

int init_analisi_sintactic(char* filename){
	char string[20];
	int i=0;
	
	strcpy(string,"");
	
	for(i=0;i<20;i++){
		if(filename[i]=='.'){
			filename[i] = '\0';
			i =20;
		}
	}
	
	localRA = inicialitzarTaula(localRA);
	globalRA = inicialitzarTaula(globalRA);
	inicialitzarFitxer(filename);
	
	globalC3A = inicialitzarT(globalC3A);
	localC3A = inicialitzarT(localC3A);
	inicialitzarFit(filename);
	
	cast = (char *)malloc(20*sizeof(char));
	castAux = (char *)malloc(20*sizeof(char));
	op = (char *)malloc(5*sizeof(char));
	aux = (char *)malloc(20*sizeof(char));
	
	nom_programa = (char *)malloc(sizeof(filename));
	strcpy(nom_programa, filename);
	
	return 0;
}

int analisi_semantic(){
	int error;
	if (yyparse() == 0)
	{
	error =  EXIT_SUCCESS;
	} else {
	error =  EXIT_FAILURE;
	}
	return error;
}

int end_analisi_sintactic(){
	int error;
	
	imprimirTaula(globalRA, "Taula global", 0);
	imprimirT(globalC3A);
	
	error = fclose(yyout);
	
	if(error == 0){
	 error = EXIT_SUCCESS;
	}else{
	 error = EXIT_FAILURE;
	}
	return error;
}

void inicialitzarInfo(){
	strcpy(info.lexema, "");
	strcpy(info.lexemac3a, "");
	info.lenght = 1;
	info.rows = 0;
	info.columns = 0;
	info.tipus = UNDEF;
	info.sizeList = UNDEF;
	info.tipusTypedef = UNDEF;
	info.tipusFunction = UNDEF;
	info.nParamsFuncio = UNDEF;
	info.isFunctionDeclaration = 0;
	
	strcpy(infoAux.lexema, "");
	strcpy(infoAux.lexemac3a, "");
	infoAux.lenght = 1;
	infoAux.rows = 0;
	infoAux.columns = 0;
	infoAux.tipus = UNDEF;
	infoAux.sizeList = UNDEF;
	infoAux.tipusTypedef = UNDEF;
	infoAux.tipusFunction = UNDEF;
	infoAux.nParamsFuncio = UNDEF;
	infoAux.isFunctionDeclaration = 0;
	
	
}

void mostraError(int codi,const char *lexema)
{ 
	switch (codi){
	
	case SYMTAB_NO_MEMORY:	fprintf(stderr, "Error de gestio de la taula de simbols. Memoria insuficient no es pot crear l'entrada per a l'identificador %s !!! \n", lexema);
		break;

	case SYMTAB_DUPLICATE:	fprintf(stderr, "Error de gestio de la taula de simbols. L'entrada a la taula per a l'identificador %s ja existeix !!! \n", lexema);
		break;

	case SYMTAB_STACK_OVERFLOW:	fprintf(stderr, "Error de gestio de la taula de simbols. No es pot crear el nou ambit per al subprograma %s !!! \n",lexema);
		break;

	case SYMTAB_STACK_UNDERFLOW:	fprintf(stderr, "Error de gestio de la taula de simbols. No es pot desapilar l'ambit global %s !!! \n",lexema);
		break;

	case SYMTAB_NOT_TOP:	fprintf(stderr, "Error de gestio de la taula de simbols. No es permet desapilar l'ambit %s encara no tancat !!! \n",lexema);
		break;
	
	case SYMTAB_NOT_FOUND:	fprintf(stderr, "Error de gestio de la taula de simbols. L'entrada a la taula per a l'identificador %s no existeix !!! \n", lexema);
		break;
	}
}

void missatgeError(char *string, int row, int column){
	char *aux;
	aux = (char *)malloc(sizeof(char *)*200);
	sprintf(aux,"Linia %d.%d\t(ERROR) %s\n",row,column, string);
	printf(aux);
	fprintf (yyout, aux);
}

void missatgeWarning(char *string, int row, int column){
	char *aux;
	aux = (char *)malloc(sizeof(char *)*200);
	sprintf(aux,"Linia %d.%d\t(WARNING)  %s\n",row,column, string);
	printf(aux);
	fprintf (yyout, aux);
}

int comprovacioTipus(int primer, int segon){
	int valor=-2;
	
	/* Si son variables hem de buscar el tipus al symtab 
	primer = simplificar_tipus_variable(primer, lex_primer);
	segon = simplificar_tipus_variable(segon, lex_segon);*/

	if (primer == segon){
		/* La comparacio sera a nivell*/
		valor = COMPTIPUS_IGUALS;
	} else {
		if (primer < segon && segon <= ID_DOUBLE){
			valor = COMPTIPUS_DIF_RED_SEGON; 
		} else if (primer > segon && primer <= ID_DOUBLE) {
			valor = COMPTIPUS_DIF_RED_PRIMER;
		} else {
			valor = COMPTIPUS_DIF_NO_RED;	
		}
	}
	return valor;
}

int obtenirMida(int tipus){
	switch(tipus){
		case ID_CHAR:
			return 1;
			break;
		case ID_SHORT:
			return 2;
			break;
		case ID_INT:
			return 4;
			break;
		case ID_LONG: 
			return 8;
			break;	
		case ID_FLOAT:
			return 4;
			break;
		case ID_DOUBLE: 
			return 8;
			break;
		case UNDEF:
			return 0;
		break;	
		case ID_VOID:
			return 0;
		break;
	}
	return -1;
}

int obtenirMidaStruct(char * nomStruct){
	int x = 0;
	int mida = 0;
	
	inicialitzarInfo();
	ambit_actual=sym_get_scope();
	if (ambit_actual==SYM_ROOT_SCOPE){
		error_sym=sym_global_lookup(nomStruct,&info);
	}
	else{
		error_sym=sym_lookup(nomStruct,&info);
	}
	
	for(x=0;x<info.nParamsFuncio; x++){
		mida += obtenirMida(info.parametres[x].type);
	}
	
	return mida;
}


void yyerror(char *explanation){	
	fflush(yyout);
}