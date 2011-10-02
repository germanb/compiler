/******************************************************************
            Este es el archivo correspondiente al PARSER
*******************************************************************/

#define EXTERNA extern

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "codigos.h"
#include "var_globales.h"
#include "ts.h"

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

//flag para ver si tiene return una funcion
int return_flag;
int function_call_flag = 0;
 int void_flag;
void scanner() {
  int i;

  for (;(i=yylex())!= NADA && sbol->codigo == SEGUIR;);
  if (i == NADA){
      nro_linea++;
      sbol->codigo = CEOF;
  }else{
    liberar = linea;
    linea = (char *) malloc (strlen(linea) + strlen (token1.lexema) + 3);
    strcpy(linea, liberar);
    strcat(linea, token1.lexema);
    free ( (void *) liberar);
  }

  /* yylex retorna 0 si llego a fin de archivo */



  /* El alumno debera dar una solucion al problema que las constantes
    enteras y flotantes son entregadas como strings al parser */
}


int main( int argc,char *argv[]) {

    //AGREGAR -C Y -E

  /* el alumno debera inicializar la variable yyin segun corresponda */
  linea = (char *) malloc (2);
  strcat(linea, "");

  nro_linea=0;
   if (argc == 30) {
 // if (argc != 3) {
    error_handler(6);
    error_handler(COD_IMP_ERRORES);
    exit(1);
  }
  else {
 //   if ((yyin = fopen(argv[2], "r" )) == NULL) {
      if ((yyin = fopen("prueba.c", "r" )) == NULL) {
      error_handler(7);
      error_handler(COD_IMP_ERRORES);
      exit(1);
    }
  }

  sbol=&token1 ;/* la variable token */

  //inicializa las tablas
  inic_tablas();

  scanner();
  unidad_traduccion();

  if(en_tabla("main") == NIL){
      error_handler(15);
  }

 // show_ts();

 // if (sbol->codigo != CEOF) error_handler(8);
  error_handler(COD_IMP_ERRORES);
}


/********* funciones del parser ***********/

void unidad_traduccion(){

  while (sbol->codigo == CVOID || sbol->codigo == CCHAR ||
         sbol->codigo == CINT || sbol->codigo == CFLOAT)
    declaraciones();
}

void declaraciones(){
  especificador_tipo();
  if (sbol->codigo == CIDENT){
      strcpy(inf_id->nbre,sbol->lexema);
      scanner();
      especificador_declaracion();
  }
  else {
      error_handler(16);
      scanner();
      while (sbol->codigo != CEOF && sbol->codigo != CVOID && sbol->codigo != CCHAR &&
         sbol->codigo != CINT && sbol->codigo != CFLOAT){
          scanner();
      }
  }
  
}

void especificador_tipo(){
    inf_id->ptr_tipo = en_tabla(sbol->lexema);
  switch (sbol->codigo) {
    case CVOID: scanner(); break;
    case CCHAR: scanner(); break;
    case CINT: scanner(); break;
    case CFLOAT: scanner(); break;
    default: error_handler(17);
  }
}

void especificador_declaracion(){

  switch (sbol->codigo) {
    case CPAR_ABR: definicion_funcion(); break;
    case CASIGNAC:
    case CCOR_ABR:
    case CCOMA:
    case CPYCOMA:  declaracion_variable(); break;
    default: error_handler(18);
  }

}
entrada_TS  *inf_id_aux;
void definicion_funcion(){

  if (sbol->codigo == CPAR_ABR) scanner();
  else error_handler(19);

  if(!strcmp(inf_id->nbre,"main") && (inf_id->ptr_tipo != en_tabla("void"))){
     error_handler(35);
  }

  void_flag = (inf_id->ptr_tipo == en_tabla("void"));

  inf_id_aux = inf_id;

  inf_id->clase = CLASFUNC;
  insertarTS();

  pushTB();
  if (sbol->codigo == CVOID || sbol->codigo == CCHAR ||
      sbol->codigo == CINT || sbol->codigo == CFLOAT) {
      lista_declaraciones_param();

      int main_pos = en_tabla("main");
      if(main_pos != NIL){
        entrada_TS main = * ts[main_pos].ets;
        if(main.desc.part_var.sub.cant_par){
            error_handler(36);
        }
      }
  }

  if (sbol->codigo == CPAR_CIE) scanner();
  else error_handler(20);

  return_flag = 0;
  proposicion_compuesta();

  if (!void_flag && !return_flag) {
     error_handler(37);
  }

  if (sbol->codigo == CLLA_CIE){
    scanner();
  }
  pop_nivel();

}

void lista_declaraciones_param(){

  declaracion_parametro();

  tipo_inf_res * eslabon = (tipo_inf_res *) calloc (1,sizeof(tipo_inf_res));
  eslabon->ptero_tipo = inf_id->ptr_tipo;
  eslabon->tipo_pje = inf_id->desc.part_var.tipo_pje;
  inf_id_aux->desc.part_var.sub.ptr_inf_res = eslabon;
  inf_id_aux->desc.part_var.sub.cant_par = 1;
  inf_id->clase = CLASPAR;
  insertarTS();
  while (sbol->codigo ==CCOMA) {
      scanner();

      declaracion_parametro();
      tipo_inf_res * eslabon = (tipo_inf_res *) calloc (1,sizeof(tipo_inf_res));
      eslabon->ptero_tipo = inf_id->ptr_tipo;
      eslabon->tipo_pje = inf_id->desc.part_var.tipo_pje;
      tipo_inf_res * eslabonAux = inf_id_aux->desc.part_var.sub.ptr_inf_res;
      while(eslabonAux->ptr_sig != NULL){
          eslabonAux = eslabonAux->ptr_sig;
      }
      eslabonAux->ptr_sig = eslabon;
      inf_id_aux->desc.part_var.sub.ptr_inf_res = eslabon;
      inf_id_aux->desc.part_var.sub.cant_par++;
      inf_id->clase = CLASPAR;
      insertarTS();

    }
}

void declaracion_parametro() {

  especificador_tipo();

  if (sbol->codigo == CAMPER){
      inf_id->desc.part_var.tipo_pje = PAR_REFERENCIA;
      scanner();
  }else{
      inf_id->desc.part_var.tipo_pje = PAR_VALOR;
  }
  if (sbol->codigo == CIDENT){
      strcpy(inf_id->nbre,sbol->lexema);
      scanner();
  }
  else error_handler(16);

  if (sbol->codigo == CCOR_ABR){
      inf_id->desc.part_var.tipo_pje = PAR_REFERENCIA;

      scanner();

      if (sbol->codigo == CCOR_CIE){
          inf_id->desc.part_var.arr.ptero_tipo_base = inf_id->ptr_tipo;
          inf_id->ptr_tipo = en_tabla("TIPOARREGLO");
          scanner();
      }
      else error_handler(21);
  }
}

void lista_declaraciones_init(){

  if (sbol->codigo == CIDENT){
      strcpy(inf_id->nbre,sbol->lexema);
      scanner();
  }
  else error_handler(16);

  declarador_init();
  inf_id->clase = CLASVAR;
  int aux;
  if(inf_id->ptr_tipo == en_tabla("TIPOARREGLO")){
    aux = inf_id->desc.part_var.arr.ptero_tipo_base;
  }else{
    aux = inf_id->ptr_tipo;
  }

  while (sbol->codigo == CCOMA) {
      insertarTS();
      inf_id->ptr_tipo = aux;
      scanner();

    if (sbol->codigo == CIDENT){
         strcpy(inf_id->nbre,sbol->lexema);
        scanner();
    }
    else error_handler(16);

    declarador_init();
  }
}


void declaracion_variable(){

  declarador_init();

  if (sbol->codigo == CCOMA){

      int aux = inf_id->ptr_tipo;
      inf_id->clase = CLASVAR;
      insertarTS();
      inf_id->ptr_tipo = aux;
      scanner();
    lista_declaraciones_init();
  }

  inf_id->clase = CLASVAR;
  insertarTS();

  if (sbol->codigo == CPYCOMA){
      scanner();
  }
  else error_handler(22);

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
              inf_id->desc.part_var.arr.ptero_tipo_base = inf_id->ptr_tipo;
              inf_id->ptr_tipo = en_tabla("TIPOARREGLO");
	      if (sbol->codigo == CCONS_ENT)
              {
                  inf_id->desc.part_var.arr.cant_elem = atoi(sbol->lexema);
                  constante();
              }
	      if (sbol->codigo == CCOR_CIE) scanner();
	      else error_handler(21);

	      if (sbol->codigo == CASIGNAC){
		scanner();

		if (sbol->codigo == CLLA_ABR) scanner();
		else error_handler(23);

		lista_inicializadores();

		if (sbol->codigo == CLLA_CIE) scanner();
		else error_handler(24);

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
  else error_handler(23);

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

  if (sbol->codigo != CLLA_CIE){
      error_handler(24);
  }
  //PONEMOS SCANNER AFUERA PARA QUE IMPRIMA BIEN LOS ERRORES!!!
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
  
  inf_id->clase = CLASVAR;
  insertarTS();

  if (sbol->codigo == CPYCOMA){
      scanner();
  }
  else error_handler(22);

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
  case CLLA_ABR:
      pushTB();
      proposicion_compuesta();
      if (sbol->codigo == CLLA_CIE){
        scanner();
      }
      popTB();
      break;
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
  default: error_handler(25);
  }
}

void proposicion_iteracion() {

  if (sbol->codigo == CWHILE) scanner();
  else error_handler(26);

  if (sbol->codigo == CPAR_ABR) scanner();
  else error_handler(19);

  expresion();

  if (sbol->codigo == CPAR_CIE) scanner();
  else error_handler(20);

  proposicion();

}


void proposicion_seleccion() {

  if (sbol->codigo == CIF) scanner();
  else error_handler(27);

  if (sbol->codigo == CPAR_ABR) scanner();
  else error_handler(19);

  expresion();

  if (sbol->codigo == CPAR_CIE) scanner();
  else error_handler(20);

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
            else error_handler(28);
            variable();
	    while (sbol->codigo == CSHR) {
               scanner();
               variable();
            }
	    if (sbol->codigo == CPYCOMA) scanner();
	    else error_handler(22);
	    break;
  }
  case COUT: {scanner();
             if (sbol->codigo == CSHL) scanner();
             else error_handler(29);
             expresion();
	     while (sbol->codigo == CSHL) {
               scanner();
               expresion();
             }
	     if (sbol->codigo == CPYCOMA) scanner();
	     else error_handler(22);
	     break;
  }
   default: error_handler(30);
   }
}


void proposicion_retorno() {

  scanner();
  expresion();
  if (sbol->codigo == CPYCOMA) scanner();
  else error_handler(22);
  return_flag = 1;
}


void proposicion_expresion(){

  if (sbol->codigo == CMAS || sbol->codigo == CMENOS ||
      sbol->codigo == CIDENT ||
      sbol->codigo == CPAR_ABR || sbol->codigo == CNEG ||
      sbol->codigo == CCONS_ENT || sbol->codigo == CCONS_FLO ||
      sbol->codigo == CCONS_CAR || sbol->codigo == CCONS_STR)

    expresion();

  if (sbol->codigo == CPYCOMA) scanner();
  else error_handler(22);
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
  case CIDENT:
      if (en_tabla(sbol->lexema) == NIL){
          error_handler(33);
          strcpy(inf_id->nbre,sbol->lexema);
          inf_id->ptr_tipo = en_tabla("TIPOERROR");

      }

      int function_pos = en_tabla(sbol->lexema);
      if(function_pos != NIL){
        entrada_TS function = * ts[function_pos].ets;
        if(function.clase == CLASFUNC){
            llamada_funcion();
            break;
        }
      }
      variable();
      break;
  case CCONS_ENT:
  case CCONS_FLO:
  case CCONS_CAR: constante(); break;
  case CCONS_STR: scanner(); break;
  case CPAR_ABR: {
                 scanner();
		 expresion();
		 if (sbol->codigo == CPAR_CIE) scanner();
		 else error_handler(20);
		 break;
  }
  case CNEG: {
              scanner();
	      expresion();
	      break;
  }
  default: error_handler(31);
  }

}

void variable(){
  char tipo_aux [TAM_ID];
  if (sbol->codigo == CIDENT){
      strcpy(tipo_aux , sbol->lexema);
      scanner();
  }
  else error_handler(16);

  /* el alumno debera verificar con una consulta a TS
    si, siendo la variable un arreglo, corresponde o no
    verificar la presencia del subindice */
 if (sbol->codigo == CCOR_ABR){
   if(inf_id->ptr_tipo == en_tabla("TIPOERROR")){
       inf_id->ptr_tipo = en_tabla("TIPOARREGLO");
       insertarTS();
   }
   if(ts[en_tabla(tipo_aux)].ets->ptr_tipo != en_tabla("TIPOARREGLO")){
       error_handler(32);
   }
   scanner();
   expresion();
   if (sbol->codigo == CCOR_CIE) scanner();
   else error_handler(21);
 }else{
     if(inf_id->ptr_tipo == en_tabla("TIPOERROR")){
        insertarTS();
    }
     if(ts[en_tabla(tipo_aux)].ets->ptr_tipo == en_tabla("TIPOARREGLO")){
         if(!function_call_flag){
            error_handler(40);
         }
     }
 }
}
void llamada_funcion() {

  if (sbol->codigo == CIDENT) scanner();
  else error_handler(16);

  if (sbol->codigo == CPAR_ABR) scanner();
  else error_handler(19);

  function_call_flag = 1;

  if (sbol->codigo == CMAS || sbol->codigo == CMENOS ||
      sbol->codigo == CIDENT ||
      sbol->codigo == CPAR_ABR || sbol->codigo == CNEG ||
      sbol->codigo == CCONS_ENT || sbol->codigo == CCONS_FLO ||
      sbol->codigo == CCONS_CAR || sbol->codigo == CCONS_STR)

    lista_expresiones();

   if (sbol->codigo == CPAR_CIE) scanner();
  else error_handler(20);
  function_call_flag = 0;
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














