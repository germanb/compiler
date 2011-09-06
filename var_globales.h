#define TAM_LEXEMA 200

typedef struct { long codigo;
                 char lexema[TAM_LEXEMA];
               }token;


#define COD_IMP_ERRORES -1

EXTERNA char * linea;
EXTERNA char *liberar;
EXTERNA int nro_linea;
EXTERNA token token1;







