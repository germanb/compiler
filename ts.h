/*
======================================================================
			COMPILADORES
	  PROGRAMAS FUENTES ENTREGADOS POR LA CATEDRA

       HEADER PARA EL ADMINISTRADOR DE TABLA DE SIMBOLOS 2002
======================================================================
*/

/*
======================================================================
	 Definiciones de constantes usadas por la tabla de simbolos
======================================================================
*/

# define TAM_ID     15
# define TAM_TS    200
# define TAM_HASH  100
# define TAM_BLOQ   30
# define BASE_TS    -1
# define BASE_TB    -1
# define NIL        -1         // indica que no apunto a ningun tipo


/* ========= Definicion de las clases de identificadores =========*/

			// CLASES CORRESPONDIENTES A:

#define CLASTYPE   1    // identificador de tipo
#define CLASVAR    2    // identificador de variable
#define CLASFUNC   3    // identificador de funcion
#define CLASPAR    4    // identificador de parametro formal




/*

======================================================================
 Definiciones de tipos del administrador de tabla de simbolos
======================================================================
*/


/*   LAS SIGUIENTES ESTRUCTURAS FORMAN PARTE DEL DESCRIPTOR
     DE UNA ENTRADA EN LA TABLA DE SIMBOLOS         */



// ----------------------- TIPO_INF_RES -------------------------
//   Estructura que forma la lista con informacion resumida de parametros

 typedef struct inf_res{
   int ptero_tipo;              // tipo del parametro
   char tipo_pje;               // tipo de pasaje: valor o referncia
   struct inf_res  *ptr_sig;    // siguiente parametro
 }tipo_inf_res;




// ------------------------- STC_TS ---------------------------
//   Estructura propia de: variables (anonimas), subrutinas y par metros


typedef struct {
  int nivel;  // nivel lexicografico del objeto computacional
  int despl;  // desplazamiento dentro del registro de activacion
              // usado solamente para identificadores de clase
              // "variable" y  "parametro"

  union {
	      // si es un identificador de parametro
    char tipo_pje;    // tipo de pasaje de este parametro

    struct {  // si es un identificador de funcion

      int dir_cod;   // direccion del codigo
      int cant_par;  // cantidad de parametros
      tipo_inf_res *ptr_inf_res; // puntero a la lista que mantiene 
                     //informacion acerca de los parametros
      
    } sub;

    struct {  // si es una variable de tipo arreglo
      
      int ptero_tipo_base;  // tipo de los elementos
      int cant_elem;        // cantidad de elementos

    } arr;

  } part_var;          // fin de la union de la parte variante

} stc_TS;


/* LA SIGUIENTE ESTRUCTURA FORMA UNA ENTRADA EN LA TABLA DE SIMBOLOS*/


// ------------------------ ENTRADA_TS ---------------------------
//          Estructura de una entrada en la tabla de s¡mbolos

typedef struct{

  char nbre[TAM_ID];  // nombre del identificador

  int clase;         // clase de objeto computacional:
		     // vble., funcion, param., tipo.
  
  int ptr_tipo;      // puntero al tipo del identificador
                     // apunta a la tabla de simbolos
                     // tambien puede ser usado para indicar
                     // el tipo del valor retornado por una funcion

  int cant_byte;     // cantidad de bytes del objeto computacional
 
  stc_TS  desc;      // descriptor de variable, funcion o parametro

} entrada_TS;


// ---------------------------- TIPO_TS -----------------------------
//          Estructura que define el tipo de la tabla de s¡mbolos

typedef struct {

  int ptr_sinon;         // puntero que encadena los sinonimos
  entrada_TS *ets;       // entrada_TS particular

} tipo_TS;


/*

========================================================
 Definicion de variables globales
========================================================
*/

extern   entrada_TS *inf_id;
extern tipo_TS   ts[TAM_TS];     // tabla de simbolos


/*			FIN			*/

