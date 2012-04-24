typedef struct fila {
	int offset;
	int mida;
	char nom[100];
} fila;
	
typedef struct taula {
	int nFiles;
	fila registre[100];
} taula; 

taula introduirFila(fila, taula);
void imprimirTaula(taula, char*);
void inicialitzarFila(fila);
void inicialitzarTaula(taula);
void inicialitzarFitxer();
taula esborrarTaula(taula);