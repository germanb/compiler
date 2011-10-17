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
#include "set.c"
#include "error.h"

/*********** prototipos *************/

void unidad_traduccion(set folset);
void declaraciones(set folset);
void especificador_tipo(set folset);
void especificador_declaracion(set folset);
void definicion_funcion(set folset);
void declaracion_variable(set folset);
void lista_declaraciones_param(set folset);
void declaracion_parametro(set folset);
void declarador_init(set folset);
void lista_declaraciones_init(set folset);
void constante();
void lista_inicializadores();
void lista_proposiciones();
void lista_declaraciones();
void declaracion();
void proposicion();
void proposicion_expresion();
void proposicion_compuesta(set folset);
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
void test(set cjto1, set cjto2, int n);

void scanner ();

/********** variables globales ************/



token *sbol;

extern FILE *yyin;

//flag para ver si tiene return una funcion
int return_flag;
int function_call_flag = 0;
int ident_not_exists_flag = 0;
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
 //  if (argc == 30) {
  if (argc != 3) {
    error_handler(6);
    error_handler(COD_IMP_ERRORES);
    exit(1);
  }
  else {
    if ((yyin = fopen(argv[2], "r" )) == NULL) {
 //     if ((yyin = fopen("prueba.c", "r" )) == NULL) {
      error_handler(7);
      error_handler(COD_IMP_ERRORES);
      exit(1);
    }
  }

  sbol=&token1 ;/* la variable token */

  //inicializa las tablas
  inic_tablas();
  initFirsts();
  
  scanner();
  
  set folset = cons(NADA,CEOF);

  unidad_traduccion(folset);

  if(en_tabla("main") == NIL){
      error_handler(15);
  }

 // show_ts();

 // if (sbol->codigo != CEOF) error_handler(8);
  error_handler(COD_IMP_ERRORES);
}


/********* funciones del parser ***********/

void unidad_traduccion(set folset){

  test(une(folset,firsts[UT]),folset,50);

  while (sbol->codigo == CVOID || sbol->codigo == CCHAR ||
         sbol->codigo == CINT || sbol->codigo == CFLOAT)
    declaraciones(une(folset,firsts[DE]));
}

void declaraciones(set folset){
  especificador_tipo(une(une(folset,cons(NADA,CIDENT)), firsts[ED]));
  if (sbol->codigo == CIDENT){
      strcpy(inf_id->nbre,sbol->lexema);
      scanner();
  }
  else {
      error_handler(16);
      ident_not_exists_flag = 1;
  }
  especificador_declaracion(folset);
}

void especificador_tipo(set folset){

    test(firsts[ET],folset,51);

    inf_id->ptr_tipo = en_tabla(sbol->lexema);
    switch (sbol->codigo) {
        case CVOID: scanner(); break;
        case CCHAR: scanner(); break;
        case CINT: scanner(); break;
        case CFLOAT: scanner(); break;
        default: error_handler(17);
    }

    test(folset, cons(NADA,NADA), 52);

}

void especificador_declaracion(set folset){
  test(firsts[ED],folset, 53);

  switch (sbol->codigo) {
    case CPAR_ABR: definicion_funcion(folset); break;
    case CASIGNAC:
    case CCOR_ABR:
    case CCOMA:
    case CPYCOMA:  declaracion_variable(folset); break;
    default: error_handler(18);
  }

}
entrada_TS  *inf_id_aux;
void definicion_funcion(set folset){

  if (sbol->codigo == CPAR_ABR) scanner();
  else error_handler(19);

  if(!strcmp(inf_id->nbre,"main") && (inf_id->ptr_tipo != en_tabla("void"))){
     error_handler(35);
  }

  void_flag = (inf_id->ptr_tipo == en_tabla("void"));

  inf_id_aux = inf_id;

  if(ident_not_exists_flag == 0){
    inf_id->clase = CLASFUNC;
    insertarTS();
  }else{
      ident_not_exists_flag = 0;
  }

  pushTB();
  if (sbol->codigo == CVOID || sbol->codigo == CCHAR ||
      sbol->codigo == CINT || sbol->codigo == CFLOAT || sbol->codigo == CIDENT || sbol->codigo == CAMPER ) {

      lista_declaraciones_param(une(folset, une(firsts[PC], cons(CPAR_CIE,NADA))));

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
  proposicion_compuesta(folset);

  if (!void_flag && !return_flag) {
     error_handler(37);
  }

  if (sbol->codigo == CLLA_CIE){
    scanner();
  }
  pop_nivel();

  //por que sacamos el scanner de proposicion compuesta pongo el test aca
  test(folset,cons(NADA,NADA),61);

}

void lista_declaraciones_param(set folset){

  declaracion_parametro(une(folset,une(cons(CCOMA,NADA),firsts[DP])));

  tipo_inf_res * eslabon = (tipo_inf_res *) calloc (1,sizeof(tipo_inf_res));
  eslabon->ptero_tipo = inf_id->ptr_tipo;
  eslabon->tipo_pje = inf_id->desc.part_var.tipo_pje;
  inf_id_aux->desc.part_var.sub.ptr_inf_res = eslabon;
  inf_id_aux->desc.part_var.sub.cant_par = 1;
  inf_id->clase = CLASPAR;
  insertarTS();
  while (sbol->codigo ==CCOMA || in(sbol->codigo, firsts[DP])) {

      if(in(sbol->codigo, firsts[DP])){
          error_handler(75);
      }else{
           scanner();
      }
      
      declaracion_parametro(une(folset,une(cons(CCOMA,NADA),firsts[DP])));
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

void declaracion_parametro(set folset) {

  especificador_tipo(une(folset,cons(CAMPER|CCOR_ABR|CCOR_CIE,CIDENT)));

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

      inf_id->desc.part_var.arr.ptero_tipo_base = inf_id->ptr_tipo;
      inf_id->ptr_tipo = en_tabla("TIPOARREGLO");

      if (sbol->codigo == CCOR_CIE){
          scanner();
      }
      else error_handler(21);
  }
  test(folset,cons(CCOMA,NADA),55);
}

void lista_declaraciones_init(set folset){
  test(firsts[LDI],une(une(folset,firsts[DI]),cons(CCOMA,CIDENT)),57);

  if (sbol->codigo == CIDENT){
      strcpy(inf_id->nbre,sbol->lexema);
      scanner();
  }
  else error_handler(16);

  declarador_init(une(folset,une(cons(CCOMA,CIDENT),firsts[DI])));
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

    declarador_init(une(folset,une(cons(CCOMA,CIDENT),firsts[DI])));
  }
}


void declaracion_variable(set folset){

  declarador_init(une(une(folset,cons(CCOMA|CPYCOMA,NADA)),firsts[LDI]));

  if (sbol->codigo == CCOMA){

      int aux = inf_id->ptr_tipo;
      inf_id->clase = CLASVAR;
      insertarTS();
      inf_id->ptr_tipo = aux;
      scanner();
    lista_declaraciones_init(une(folset,cons(CPYCOMA,NADA)));
  }

  if(ident_not_exists_flag == 0){
    inf_id->clase = CLASVAR;
    insertarTS();
  }else{
      ident_not_exists_flag = 0;
  }

  if (sbol->codigo == CPYCOMA){
      scanner();
  }
  else error_handler(22);
  
  test(folset,cons(NADA,NADA),62);
}


void declarador_init(set folset){
  test(une(folset,firsts[DI]), une(firsts[C],une(firsts[LI],une(folset,cons(CCOR_CIE|CLLA_ABR|CLLA_CIE, CASIGNAC)))),58);

  if(in(sbol->codigo,firsts[C])){
	error_handler(79);
	constante(folset);
  }else{
  switch (sbol->codigo) {
      case CASIGNAC:{
               scanner();
               constante(folset);
                break;
      }
      case CCOR_ABR:{
              scanner();
              inf_id->desc.part_var.arr.ptero_tipo_base = inf_id->ptr_tipo;
              inf_id->ptr_tipo = en_tabla("TIPOARREGLO");
	      if (sbol->codigo == CCONS_ENT)
              {
                  inf_id->desc.part_var.arr.cant_elem = atoi(sbol->lexema);
                  constante(une(firsts[LI],une(folset,cons(CCOR_CIE, CASIGNAC))));
              }
	      if (sbol->codigo == CCOR_CIE) scanner();
	      else error_handler(21);

	      if (sbol->codigo == CASIGNAC){
		scanner();

		if (sbol->codigo == CLLA_ABR) scanner();
		else error_handler(23);

		lista_inicializadores(une(folset,cons(CLLA_CIE,NADA)));

		if (sbol->codigo == CLLA_CIE) scanner();
		else error_handler(24);

	      }

	      break;
      }
  }
}
 test(folset,cons(NADA,NADA),59);
}
void lista_inicializadores(set folset) {

  constante(une(folset, une(cons(CCOMA,NADA),firsts[C])));

  while (sbol->codigo == CCOMA || in(sbol->codigo,firsts[C])) {
      if(in(sbol->codigo,firsts[C])){
          error_handler(75);
      }else{
          scanner();
      }
    constante(une(folset, une(cons(CCOMA,NADA),firsts[C])));
  }

}


void proposicion_compuesta(set folset){
  test(firsts[PC], une(une(une(folset,firsts[LD]),firsts[LP]),cons(CLLA_CIE, NADA)) ,60);

  if (sbol->codigo == CLLA_ABR) scanner();
  else error_handler(23);

  if (sbol->codigo == CVOID || sbol->codigo == CCHAR ||
      sbol->codigo == CINT || sbol->codigo == CFLOAT)

    lista_declaraciones(une(une(folset,firsts[LP]),cons(CLLA_CIE,NADA)));

  if (sbol->codigo == CLLA_ABR || sbol->codigo == CMAS ||
      sbol->codigo == CMENOS || sbol->codigo == CIDENT ||
      sbol->codigo == CPAR_ABR || sbol->codigo == CNEG ||
      sbol->codigo == CCONS_ENT || sbol->codigo == CCONS_FLO ||
      sbol->codigo == CCONS_CAR || sbol->codigo == CCONS_STR ||
      sbol->codigo == CIF || sbol->codigo == CWHILE ||
      sbol->codigo == CIN || sbol->codigo == COUT ||
      sbol->codigo == CPYCOMA || sbol->codigo == CRETURN)

    lista_proposiciones(une(folset, cons(CLLA_CIE,NADA)));

  if (sbol->codigo != CLLA_CIE){
      error_handler(24);
  }
  //PONEMOS SCANNER AFUERA PARA QUE IMPRIMA BIEN LOS ERRORES!!!
}
void lista_declaraciones(set folset) {

  declaracion(une(folset,firsts[D]));

  while (sbol->codigo == CVOID || sbol->codigo == CCHAR ||
         sbol->codigo == CINT || sbol->codigo == CFLOAT)

    declaracion(une(folset,firsts[D]));

}

void declaracion(set folset){

  especificador_tipo(une(une(folset, firsts[LDI]),cons(CPYCOMA,NADA)));

  lista_declaraciones_init(une(folset, cons(CPYCOMA,NADA)));
  
  inf_id->clase = CLASVAR;
  insertarTS();

  if (sbol->codigo == CPYCOMA){
      scanner();
  }
  else error_handler(22);

  test(folset,cons(NADA,NADA),62);
}

void lista_proposiciones(set folset) {

  proposicion(une(folset,firsts[P]));

  while (sbol->codigo == CLLA_ABR || sbol->codigo == CMAS ||
	 sbol->codigo == CMENOS || sbol->codigo == CIDENT ||
	 sbol->codigo == CPAR_ABR || sbol->codigo == CNEG ||
	 sbol->codigo == CCONS_ENT || sbol->codigo == CCONS_FLO ||
	 sbol->codigo == CCONS_CAR || sbol->codigo == CCONS_STR ||
	 sbol->codigo == CIF || sbol->codigo == CWHILE ||
	 sbol->codigo == CIN || sbol->codigo == COUT ||
	 sbol->codigo == CPYCOMA || sbol->codigo == CRETURN)

    proposicion(une(folset,firsts[P]));

}

void proposicion(set folset){
  test(firsts[P],folset,63);
  switch (sbol->codigo) {
  case CLLA_ABR:
      pushTB();
      proposicion_compuesta(folset);
      if (sbol->codigo == CLLA_CIE){
        scanner();
      }
      popTB();
      //por que sacamos el scanner de proposicion compuesta pongo el test aca
      test(folset,cons(NADA,NADA),61);
      break;
  case CWHILE: proposicion_iteracion(folset); break;
  case CIF: proposicion_seleccion(folset); break;
  case CIN:
  case COUT: proposicion_e_s(folset); break;
  case CMAS:
  case CMENOS:
  case CIDENT:
  case CPAR_ABR:
  case CNEG:
  case CCONS_ENT:
  case CCONS_FLO:
  case CCONS_CAR:
  case CCONS_STR:
  case CPYCOMA:  proposicion_expresion(folset); break;
  case CRETURN:  proposicion_retorno(folset); break;
  default: error_handler(25);
  }
}

void proposicion_iteracion(set folset) {

  if (sbol->codigo == CWHILE) scanner();
  else error_handler(26);

  if (sbol->codigo == CPAR_ABR) scanner();
  else error_handler(19);

  expresion(une(une(folset,cons(CPAR_CIE,NADA)),firsts[P]));

  if (sbol->codigo == CPAR_CIE) scanner();
  else error_handler(20);

  proposicion(folset);

}


void proposicion_seleccion(set folset) {

  if (sbol->codigo == CIF) scanner();
  else error_handler(27);

  if (sbol->codigo == CPAR_ABR) scanner();
  else error_handler(19);

  expresion(une(une(folset,cons(CPAR_CIE|CELSE,NADA)),firsts[P]));

  if (sbol->codigo == CPAR_CIE) scanner();
  else error_handler(20);

  proposicion(une(une(folset,cons(CELSE,NADA)),firsts[P]));

  if (sbol->codigo == CELSE){
    scanner();

    proposicion(folset);
  }

}

void proposicion_e_s(set folset) {

  switch(sbol->codigo) {
  case CIN: { scanner();
            if (sbol->codigo == CSHR) scanner();
            else error_handler(28);
            variable(une(firsts[V], une(folset,cons(CPYCOMA|CSHR,NADA))));

             while (sbol->codigo == CSHR ) {
                scanner();
                variable(une(une(folset,cons(CSHR|CPYCOMA,NADA)),firsts[V]));
               
            }

	    if (sbol->codigo == CPYCOMA) scanner();
	    else error_handler(22);
	    break;
  }
  case COUT: {scanner();
             if (sbol->codigo == CSHL) scanner();
             else error_handler(29);
             expresion(une(firsts[E], une(folset,cons(CPYCOMA|CSHL,NADA))));

             while (sbol->codigo == CSHL){
                        scanner();
               
             expresion(une(une(folset,cons(CSHL|CPYCOMA,NADA)),firsts[E]));
             }
	     if (sbol->codigo == CPYCOMA) scanner();
	     else error_handler(22);
	     break;
  }
   default: error_handler(30);
   }

  test(folset, cons(NADA,NADA) ,64);
}


void proposicion_retorno(set folset) {

  scanner();
  expresion(une(folset,cons(CPYCOMA,NADA)));
  if (sbol->codigo == CPYCOMA) scanner();
  else error_handler(22);
  return_flag = 1;

  test(folset, cons(NADA,NADA), 65);
}


void proposicion_expresion(set folset){

  if (sbol->codigo == CMAS || sbol->codigo == CMENOS ||
      sbol->codigo == CIDENT ||
      sbol->codigo == CPAR_ABR || sbol->codigo == CNEG ||
      sbol->codigo == CCONS_ENT || sbol->codigo == CCONS_FLO ||
      sbol->codigo == CCONS_CAR || sbol->codigo == CCONS_STR)

    expresion(une(folset,cons(CPYCOMA,NADA)));

  if (sbol->codigo == CPYCOMA) scanner();
  else error_handler(22);

  test(folset,cons(NADA,NADA), 66);
}


void expresion(set folset) {

  expresion_simple(une(une(folset,firsts[E]),cons(CASIGNAC, CDISTINTO|CIGUAL|CMENOR|CMEIG|CMAYOR|CMAIG)));

  if(in(sbol->codigo,firsts[E])){
      error_handler(78);
      expresion(folset);
  }else{

  switch (sbol->codigo) {
  case CASIGNAC:{
               scanner();
	       expresion(folset);
	       break;
  }
  case CDISTINTO:
  case CIGUAL:
  case CMENOR:
  case CMEIG:
  case CMAYOR:
  case CMAIG: {
              scanner();
              expresion(folset);
	      break;
  }
  }
  }
}


void expresion_simple(set folset) {

  test(firsts[ES],une(une(folset,cons(NADA,CMAS|CMENOS|COR)),firsts[T]),67);

  if (sbol->codigo == CMAS || sbol->codigo == CMENOS) scanner();

  termino(une(une(folset,cons(NADA,CMAS|CMENOS|COR)),firsts[T]));

  while (sbol->codigo == CMAS || sbol->codigo == CMENOS || sbol->codigo == COR)
  {
    if(in(sbol->codigo, firsts[T])){
        error_handler(78);
    }else{
        scanner();
    }
    termino(une(une(folset,cons(NADA,CMAS|CMENOS|COR)),firsts[T]));
  }

}

void termino(set folset) {

  factor(une(une(folset,cons(NADA,CMULT|CDIV|CAND)),firsts[F]));

  while (sbol->codigo == CMULT || sbol->codigo == CDIV || sbol->codigo == CAND)
  {
    	if(in(sbol->codigo,firsts[F])){
              error_handler(78);
	}else{
	    scanner();
	}
    factor(une(une(folset,cons(NADA,CMULT|CDIV|CAND)),firsts[F]));
  }

}

void factor(set folset) {

  test(firsts[F],une(folset, une(firsts[E],cons(CPAR_CIE,NADA))),68);

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
            llamada_funcion(folset);
            break;
        }
      }
      variable(folset);
      break;
  case CCONS_ENT:
  case CCONS_FLO:
  case CCONS_CAR: constante(folset); break;
  case CCONS_STR: scanner(); break;
  case CPAR_ABR: {
                 scanner();
		 expresion(une(folset,cons(CPAR_CIE, NADA)));
		 if (sbol->codigo == CPAR_CIE) scanner();
		 else error_handler(20);
		 break;
  }
  case CNEG: {
              scanner();
	      expresion(folset);
	      break;
  }
  default: error_handler(31);
  }

  test(folset,cons(NADA,NADA),69);

}

void variable(set folset){
  test(firsts[V],folset,70);

  char tipo_aux [TAM_ID] = "";
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
   if(strcmp(tipo_aux,"") != 0 && ts[en_tabla(tipo_aux)].ets->ptr_tipo != en_tabla("TIPOARREGLO")){
       error_handler(32);
   }
   scanner();
   expresion(une(folset,cons(CCOR_CIE,NADA)));
   if (sbol->codigo == CCOR_CIE) scanner();
   else error_handler(21);
 }else{
     if(inf_id->ptr_tipo == en_tabla("TIPOERROR")){
        insertarTS();
    }
     
        if(en_tabla(tipo_aux) == NIL &&(sbol->codigo!=CCONS_ENT)){
            error_handler(33);
        }else if(strcmp(tipo_aux,"") != 0  && ts[en_tabla(tipo_aux)].ets->ptr_tipo == en_tabla("TIPOARREGLO")){
            if(!function_call_flag){
                error_handler(40);
            }
        }
      
 }
  test(folset,cons(NADA,NADA),71);
}
void llamada_funcion(set folset) {

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

    lista_expresiones(une(folset,cons(CPAR_CIE,NADA)));

   if (sbol->codigo == CPAR_CIE) scanner();
  else error_handler(20);
  function_call_flag = 0;

  test(folset, cons(NADA,NADA),72);
}

void lista_expresiones(set folset) {

  expresion(une(firsts[E],une(folset,cons(CCOMA,NADA))));

  while (sbol->codigo == CCOMA){

                scanner();      

  expresion(une(une(folset,cons(CCOMA,NADA)),firsts[E]));
 }
  
}

void constante(set folset){
  test(firsts[C],folset,73);

  switch (sbol->codigo) {
  case CCONS_ENT: scanner(); break;
  case CCONS_FLO: scanner(); break;
  case CCONS_CAR: scanner(); break;
  default: error_handler(38); //scanner(); /*f_error(); aca va f_error, faltan los algoritmos de conversion a las constantes numericas. */
  }

}

void test(set cjto1, set cjto2, int n){
    if (in(sbol->codigo, cjto1) == 0){
        error_handler(n);
        cjto1 = une(cjto1,cjto2);
        while (!in(sbol->codigo, cjto1)) // ahora cjto1 es el conjunto de
        {
             scanner();
        }
    }
}














