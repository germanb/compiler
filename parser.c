/******************************************************************
            Este es el archivo correspondiente al PARSER
*******************************************************************/

#define EXTERNA extern

#include <stdio.h>
#include "codigos.h"
#include "var_globales.h"

/*********** prototipos *************/

void unidad_traduccion();
void declaraciones();
void especificador_tipo();
void especificador_declaracion();
void definicion_funcion();
void declaracion_variable();
void lista_declaraciones_param();
void declaracion_parametro();
void declarador_init();
void lista_declacion_init();
void constante();
void lista_inicializadores();
void lista_proposiciones();
void lista_declaraciones();
void declaracion();
void proposicion();
void proposicion_expresion();
void proposicion_compuesta();
void proposicion_seleccion();
void proposicion_iteracion();
void proposicion_e_s();
void proposicion_retorno();
void variable();
void expresion();
void expresion_asignacion();
void expresion_relacional();
void expresion_simple();
void relacion();
void termino();
void factor();
void llamada_funcion();
void lista_expresiones();


void scanner ();

/********** variables globales ************/



token *sbol;

extern FILE *yyin;


void scanner() {
  int i;

  for (;(i=yylex())!= NADA && sbol->codigo == SEGUIR;);
  if (i == NADA) sbol->codigo = CEOF;
  /* yylex retorna 0 si llego a fin de archivo */

  liberar = linea;
  linea = (char *) malloc (strlen(linea) + strlen (token1.lexema) + 3);
  strcpy(linea, liberar);
  strcat(linea, token1.lexema);
  free ( (void *) liberar);

  /* El alumno debera dar una solucion al problema que las constantes
    enteras y flotantes son entregadas como strings al parser */
}


int main( int argc,char *argv[]) {

  /* el alumno debera inicializar la variable yyin segun corresponda */
 
  linea = (char *) malloc (2);
  strcat(linea, "");

  nro_linea=0;

  if (argc != 2) {
    error_handler(6);
    error_handler(COD_IMP_ERRORES);
    exit(1);  
  }
  else {
    if ((yyin = fopen(argv[1], "r" )) == NULL) {
      error_handler(7);
      error_handler(COD_IMP_ERRORES);
      exit(1);
    }
  }
  
  sbol=&token1 ;/* la variable token */
  
  scanner();
  unidad_traduccion();
  
  if (sbol->codigo != CEOF) error_handler(8);
  
}


/********* funciones del parser ***********/

void unidad_traduccion(){

  while (sbol->codigo == CVOID || sbol->codigo == CCHAR || 
         sbol->codigo == CINT || sbol->codigo == CFLOAT) 
    declaraciones();
}

void declaraciones(){

  especificador_tipo();
  if (sbol->codigo == CIDENT) scanner();
  else error_handler(8);
  especificador_declaracion();
}

void especificador_tipo(){

  switch (sbol->codigo) {
    case CVOID: scanner(); break;
    case CCHAR: scanner(); break;
    case CINT: scanner(); break;
    case CFLOAT: scanner(); break;
    default: error_handler(8);
  }
}

void especificador_declaracion(){

  switch (sbol->codigo) {
    case CPAR_ABR: definicion_funcion(); break;
    case CASIGNAC:
    case CCOR_ABR:
    case CCOMA:
    case CPYCOMA:  declaracion_variable(); break;
    default: error_handler(8);
  }

}

void definicion_funcion(){

  if (sbol->codigo == CPAR_ABR) scanner();
  else error_handler(8);

  if (sbol->codigo == CVOID || sbol->codigo == CCHAR || 
      sbol->codigo == CINT || sbol->codigo == CFLOAT) 
   lista_declaraciones_param();

  if (sbol->codigo == CPAR_CIE) scanner();
  else error_handler(8);

  proposicion_compuesta();

}

void lista_declaraciones_param(){

  declaracion_parametro();
  
  while (sbol->codigo ==CCOMA) {
      scanner();

      declaracion_parametro();
    }
}

void declaracion_parametro() {

  especificador_tipo();

  if (sbol->codigo == CAMPER) scanner();

  if (sbol->codigo == CIDENT) scanner();
  else error_handler(8);

  if (sbol->codigo == CCOR_ABR){

      scanner();

      if (sbol->codigo == CCOR_CIE) scanner();
      else error_handler(8);
  }
}

void lista_declaraciones_init(){

  if (sbol->codigo == CIDENT) scanner();
  else error_handler(8);
  
  declarador_init();

  while (sbol->codigo == CCOMA) {
    scanner();

    if (sbol->codigo == CIDENT) scanner();
    else error_handler(8);
  
    declarador_init();
  }

}


void declaracion_variable(){

  declarador_init();

  if (sbol->codigo == CCOMA){
    scanner();

    lista_declaraciones_init();
  }

  if (sbol->codigo == CPYCOMA) scanner();
  else error_handler(8);

}


void declarador_init(){

  switch (sbol->codigo) {
      case CASIGNAC:{
               scanner();
               constante();
                break;
      }
      case CCOR_ABR:{
              scanner();

	      if (sbol->codigo == CCONS_ENT)
		constante();

	      if (sbol->codigo == CCOR_CIE) scanner();
	      else error_handler(8);

	      if (sbol->codigo == CASIGNAC){
		scanner();

		if (sbol->codigo == CLLA_ABR) scanner();
		else error_handler(8);

		lista_inicializadores();

		if (sbol->codigo == CLLA_CIE) scanner();
		else error_handler(8);
		
	      }

	      break;
      }
  }
}

void lista_inicializadores() {

  constante();

  while (sbol->codigo == CCOMA) {
    scanner();

    constante();
  }

}


void proposicion_compuesta(){

  if (sbol->codigo == CLLA_ABR) scanner();
  else error_handler(8);

  if (sbol->codigo == CVOID || sbol->codigo == CCHAR || 
      sbol->codigo == CINT || sbol->codigo == CFLOAT) 

    lista_declaraciones();

  if (sbol->codigo == CLLA_ABR || sbol->codigo == CMAS ||
      sbol->codigo == CMENOS || sbol->codigo == CIDENT || 
      sbol->codigo == CPAR_ABR || sbol->codigo == CNEG ||
      sbol->codigo == CCONS_ENT || sbol->codigo == CCONS_FLO ||
      sbol->codigo == CCONS_CAR || sbol->codigo == CCONS_STR ||
      sbol->codigo == CIF || sbol->codigo == CWHILE ||
      sbol->codigo == CIN || sbol->codigo == COUT ||
      sbol->codigo == CPYCOMA || sbol->codigo == CRETURN)

    lista_proposiciones();

  if (sbol->codigo == CLLA_CIE) scanner();
  else error_handler(8);

}
void lista_declaraciones() {
  
  declaracion();
  
  while (sbol->codigo == CVOID || sbol->codigo == CCHAR || 
         sbol->codigo == CINT || sbol->codigo == CFLOAT) 

    declaracion();
 
}

void declaracion(){

  especificador_tipo();

  lista_declaraciones_init();

  if (sbol->codigo == CPYCOMA) scanner();
  else error_handler(8);

}

void lista_proposiciones() {

  proposicion();

  while (sbol->codigo == CLLA_ABR || sbol->codigo == CMAS ||
	 sbol->codigo == CMENOS || sbol->codigo == CIDENT || 
	 sbol->codigo == CPAR_ABR || sbol->codigo == CNEG ||
	 sbol->codigo == CCONS_ENT || sbol->codigo == CCONS_FLO ||
	 sbol->codigo == CCONS_CAR || sbol->codigo == CCONS_STR ||
	 sbol->codigo == CIF || sbol->codigo == CWHILE ||
	 sbol->codigo == CIN || sbol->codigo == COUT ||
	 sbol->codigo == CPYCOMA || sbol->codigo == CRETURN)

    proposicion();

}

void proposicion(){

  switch (sbol->codigo) {
  case CLLA_ABR: proposicion_compuesta(); break;
  case CWHILE: proposicion_iteracion(); break;
  case CIF: proposicion_seleccion(); break;
  case CIN:
  case COUT: proposicion_e_s(); break;
  case CMAS:
  case CMENOS:
  case CIDENT: 
  case CPAR_ABR:
  case CNEG:
  case CCONS_ENT:
  case CCONS_FLO:
  case CCONS_CAR:
  case CCONS_STR:
  case CPYCOMA:  proposicion_expresion(); break;
  case CRETURN:  proposicion_retorno(); break;
  default: error_handler(8);
  }
}

void proposicion_iteracion() {

  if (sbol->codigo == CWHILE) scanner();
  else error_handler(8);

  if (sbol->codigo == CPAR_ABR) scanner();
  else error_handler(8);

  expresion();

  if (sbol->codigo == CPAR_CIE) scanner();
  else error_handler(8);

  proposicion();

}


void proposicion_seleccion() {

  if (sbol->codigo == CIF) scanner();
  else error_handler(8);

  if (sbol->codigo == CPAR_ABR) scanner();
  else error_handler(8);

  expresion();

  if (sbol->codigo == CPAR_CIE) scanner();
  else error_handler(8);

  proposicion();

  if (sbol->codigo == CELSE){
    scanner();
  
    proposicion();
  }
  
}

void proposicion_e_s() {

  switch(sbol->codigo) {
  case CIN: { scanner(); 
            if (sbol->codigo == CSHR) scanner();
            else error_handler(8);
            variable();
	    while (sbol->codigo == CSHR) {
               scanner();
               variable();
            }
	    if (sbol->codigo == CPYCOMA) scanner();
	    else error_handler(8);
	    break;
  }
  case COUT: {scanner();
             if (sbol->codigo == CSHL) scanner();
             else error_handler(8);
             expresion();
	     while (sbol->codigo == CSHL) {
               scanner();
               expresion();
             }
	     if (sbol->codigo == CPYCOMA) scanner();
	     else error_handler(8);
	     break;
  }
   default: error_handler(8); 
   }
}


void proposicion_retorno() {

  scanner();
  expresion();
  if (sbol->codigo == CPYCOMA) scanner();
  else error_handler(8);

}


void proposicion_expresion(){

  if (sbol->codigo == CMAS || sbol->codigo == CMENOS ||
      sbol->codigo == CIDENT || 
      sbol->codigo == CPAR_ABR || sbol->codigo == CNEG ||
      sbol->codigo == CCONS_ENT || sbol->codigo == CCONS_FLO ||
      sbol->codigo == CCONS_CAR || sbol->codigo == CCONS_STR)

    expresion();

  if (sbol->codigo == CPYCOMA) scanner();
  else error_handler(8);
}


void expresion() {
  
  expresion_simple();

  switch (sbol->codigo) {
  case CASIGNAC:{
               scanner();
	       expresion();
	       break;
  }
  case CDISTINTO:
  case CIGUAL:
  case CMENOR:
  case CMEIG:
  case CMAYOR:
  case CMAIG: {
              scanner();
              expresion();
	      break;
  }
  }
}


void expresion_simple() {

  if (sbol->codigo == CMAS || sbol->codigo == CMENOS) scanner();

  termino();

  while (sbol->codigo == CMAS || sbol->codigo == CMENOS || sbol->codigo == COR)
  { 
    scanner();
    termino();
  }

}

void termino() {

  factor();

  while (sbol->codigo == CMULT || sbol->codigo == CDIV || sbol->codigo == CAND)
  { 
    scanner();
    factor();
  }

}

void factor() {

  switch (sbol->codigo){
  case CIDENT: if (sbol->lexema[0]=='f') llamada_funcion();
               else variable();
  /************ Sacar ************/
             break; 
                 /* el alumno debera evaluar con consulta a TS 
                  si bifurca a variable o llamada a funcion */
  case CCONS_ENT:
  case CCONS_FLO:
  case CCONS_CAR: constante(); break;
  case CCONS_STR: scanner(); break;
  case CPAR_ABR: {
                 scanner();
		 expresion();
		 if (sbol->codigo == CPAR_CIE) scanner();
		 else error_handler(8);
		 break;
  }
  case CNEG: {
              scanner();
	      expresion();
	      break;
  }
  default: error_handler(8);
  }  

}

void variable(){

  if (sbol->codigo == CIDENT) scanner();
  else error_handler(8);

  /* el alumno debera verificar con una consulta a TS 
    si, siendo la variable un arreglo, corresponde o no 
    verificar la presencia del subindice */
 if (sbol->codigo == CCOR_ABR){
   scanner();
   expresion();
   if (sbol->codigo == CCOR_CIE) scanner();
   else error_handler(8);
 }

}
void llamada_funcion() {

  if (sbol->codigo == CIDENT) scanner();
  else error_handler(8);

  if (sbol->codigo == CPAR_ABR) scanner();
  else error_handler(8);

  if (sbol->codigo == CMAS || sbol->codigo == CMENOS ||
      sbol->codigo == CIDENT || 
      sbol->codigo == CPAR_ABR || sbol->codigo == CNEG ||
      sbol->codigo == CCONS_ENT || sbol->codigo == CCONS_FLO ||
      sbol->codigo == CCONS_CAR || sbol->codigo == CCONS_STR)

    lista_expresiones();

   if (sbol->codigo == CPAR_CIE) scanner();
  else error_handler(8);

}

void lista_expresiones() {

  expresion();

  while (sbol->codigo == CCOMA) {
    scanner();

    expresion();
  }

}

void constante(){

  switch (sbol->codigo) {
  case CCONS_ENT: scanner(); break;
  case CCONS_FLO: scanner(); break;
  case CCONS_CAR: scanner(); break;
  default: scanner(); /*f_error(); aca va f_error, faltan los algoritmos de conversion a las constantes numericas. */ 
  }

}














