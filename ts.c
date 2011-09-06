/* 
======================================================================
			COMPILADORES

	  PROGRAMAS FUENTES ENTREGADOS POR LA CATEDRA

		ADMINISTRADOR DE TABLA DE SIMBOLOS 2000
======================================================================
*/

/*
=====================================================================
		#include para usar en el programa
=====================================================================
*/

#include <stdio.h>
#include <string.h>
#include "ts.h"

/* 
=====================================================================
 funciones para la administracion de la tabla de simbolos 
=====================================================================
*/

/*
NOTA: Analizar las condiciones de error y agregar los mensajes pertinentes
*/

/* PROTOTIPOS */
void inic_tablas();

int insertarTS();
int en_tabla(char *);
int en_nivel_actual(char *);
int Tipo_Ident(char *);
int Clase_Ident(char *);
 
void popTS();
int pushTS(int, entrada_TS *);

void popTB();
void pushTB();
void pop_nivel ();


/*  VARIABLES GLOBALES     */


entrada_TS  *inf_id;	 // es el puntero a la estructura que contiene la
			 // informaci¢n de un identificador, la cual es
			 // completada previamente a una insercion en TS

int       th[TAM_HASH];   // tabla de hash
tipo_TS   ts[TAM_TS];     // tabla de simbolos
int       tb[TAM_BLOQ];   // tabla de bloques
int  topeTS = BASE_TS;
int  topeTB = BASE_TB;



/* ============ FUNCION DE INICIALIZACION DE TABLAS ================ */


void inic_tablas()
{
  int i;
  char id[TAM_ID];

  //  TODOS LOS TOPES ESTAN INICIALIZADOS EN LA DECLARACION

  for (i=0; i< TAM_TS; i++)      // inicializo tabla de s¡mbolos
  {
      ts[i].ptr_sinon = NIL;
      ts[i].ets = NULL;
  };

  for (i=0; i< TAM_HASH; i++)    // inicializo tabla de hash en nil
      th[i] = NIL;

  for (i=0; i< TAM_BLOQ; i++)    // inicializo tabla de bloques en nil
      tb[i] = NIL;

  // RESERVA MEMORIA para una entrada de la TS

  inf_id = (entrada_TS *) calloc (1,sizeof(entrada_TS));


  // inicializo la entrada para el tipo base VOID
  strcpy(inf_id->nbre, "void");
  inf_id->clase = CLASTYPE;
  inf_id->ptr_tipo = NIL;
  inf_id->cant_byte = 0; 
  insertarTS();

  // inicializo la entrada para el tipo base CHAR
  strcpy(inf_id->nbre, "char");
  inf_id->clase = CLASTYPE;
  inf_id->ptr_tipo = NIL;
  inf_id->cant_byte = 1; 
  insertarTS();

  // inicializo la entrada para el tipo base INT
  strcpy(inf_id->nbre, "int");
  inf_id->clase = CLASTYPE;
  inf_id->ptr_tipo = NIL;
  inf_id->cant_byte = sizeof(int); 
  insertarTS();

  // inicializo la entrada para el tipo base FLOAT
  strcpy(inf_id->nbre, "float");
  inf_id->clase = CLASTYPE;
  inf_id->ptr_tipo = NIL;
  inf_id->cant_byte = sizeof(float);
  insertarTS();

  // inicializo la entrada para el tipo estructurado ARREGLO
  strcpy(inf_id->nbre, "TIPOARREGLO");
  inf_id->clase = CLASTYPE;
  inf_id->ptr_tipo = NIL;
  insertarTS();
 
  // inicializo la entrada para el tipo base erroneo TIPOERROR
  strcpy(inf_id->nbre, "TIPOERROR");
  inf_id->clase = CLASTYPE;
  inf_id->ptr_tipo = NIL;
  insertarTS();
 
};


/* ============ FUNCIONES DE LA TABLA DE BLOQUES ================ */

void popTB()
{
   if (topeTB == BASE_TB){
       error_handler(14);
       exit (1);
    } else {
	 tb[topeTB] = NIL;
	 topeTB --;
    }
}


void pushTB()
{                      // asumo que apunto al 1er ident del nuevo bloque
   topeTB ++;
   if (topeTB == TAM_BLOQ) {
       error_handler(13);
      exit (1);
   } else
      tb[topeTB] = topeTS + 1;
};


void pop_nivel ()      // El bloque a eliminar esta al tope de TS y TB
{
    int h;
    while (topeTS >= tb[topeTB])
    {
      h = hash(ts[topeTS].ets->nbre);
      th[h] = ts[topeTS].ptr_sinon;  // modifico la TH seg£n los sin¢nimos
      popTS();        // elimino un identificador del bloque que abandono
    };
    popTB();      // elimino el bloque que abandono
};


/* ============ FUNCIONES DE LA TABLA DE HASH ================ */

int hash(char id[])
{
   int i;
   long l=0;

   for (i=0; id[i] ; i++)
       l = 3 * l + id[i];
   l = l % TAM_HASH;
   return l;
};



/* ============ FUNCIONES DE LA TABLA DE SIMBOLOS ================ */

int insertarTS()   // la inf. del identif. esta en inf_id que es global
{
    int i,h;
    h = hash(inf_id->nbre);
    if ( th[h] != NIL )
       if ( en_nivel_actual(inf_id->nbre) >=0  )
	 {
	   error_handler(9);
           memset((void*)inf_id, 0, sizeof(entrada_TS));
	   return 0;      //al retornar 0 indico que NO lo pude insertar
         }
	  
    // inserto un nuevo identificador
    th[h]= pushTS(th[h], inf_id);

    // pido más memoria para el nuevo identificador
    inf_id = NULL;
    inf_id = (entrada_TS *) calloc(1, sizeof(entrada_TS));
    if (inf_id == NULL) {
	 error_handler(10);
	 exit(1);
    }
    return th[h];  // retorno el lugar en TS donde se inserto
};



int en_tabla(char *st)      //busca un identificador en tabla de simbolos,
{ int h;                    //retorna su posición  o NIL (si no lo encuentra)
  h=th[hash(st)];
  while (h!=NIL)
    {  if (strcmp(ts[h].ets->nbre,st)==0)
            return h;
       
       h=ts[h].ptr_sinon;
    }
  return NIL;
}


int Tipo_Ident(char *st)    //busca un identificador en tabla de simbolos,
{ int h;                     //retorna su tipo o NIL (si no lo encuentra)
  h=th[hash(st)];
  while (h!=NIL)
    {  if (strcmp(ts[h].ets->nbre,st)==0)
	   return ts[h].ets->ptr_tipo;

       h=ts[h].ptr_sinon;
    };
  return NIL; 
 
}


int Clase_Ident(char *st)   //busca un identificador en tabla de simbolos,
{ int h;                    //retorna su clase o NIL (si no lo encuentra)
  h=th[hash(st)];
  while (h!=NIL)
    {if (strcmp(ts[h].ets->nbre,st)==0)
       return ts[h].ets->clase;
     h=ts[h].ptr_sinon;
    }
  return NIL;}



int en_nivel_actual(char *id) //busca un identificador en el bloque actual
{ int h;                  //retorna su posicion o NIL (si no lo encuentra)

   h = th[hash(id)];
   while (h >= tb[topeTB])    // busco el identificador dentro del bloque
   {
      if ( ! strcmp(ts[h].ets->nbre, id) )
	 return h;     // lo encontr¢, devuelvo la posici¢n h
      h = ts[h].ptr_sinon;
   };
   return NIL;          // NO lo encontr¢ ==> ident no declarado
};



void popTS()
{
   if (topeTS == BASE_TS){
        error_handler(14);
       exit (1);
    } else {
	 ts[topeTS].ptr_sinon = NIL;
	 free((void *)ts[topeTS].ets);
	 ts[topeTS].ets = NULL;
	 topeTS --;
    };
};


int pushTS(int s, entrada_TS *ptr)
{
   topeTS ++;
   if (topeTS == TAM_TS) {
       error_handler(12);
      exit (1);        
   } else {
	 ts[topeTS].ptr_sinon = s;
	 ts[topeTS].ets = ptr;
   };
   return topeTS;   // retorno la posici¢n donde insert‚
};





