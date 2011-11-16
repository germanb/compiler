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
#include "set.h"
#include "error.h"
#include "soporte_ejecucion.h"
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
struct Tipo constante();
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
struct Tipo variable();
struct Tipo expresion();
void expresion_asignacion();
void expresion_relacional();
struct Tipo expresion_simple();
void relacion();
struct Tipo termino();
struct Tipo factor();
struct Tipo llamada_funcion();
void lista_expresiones();
void test(set cjto1, set cjto2, int n);
char *getStringINST(int INST);

void scanner ();

/********** variables globales ************/

int isReturn= 0;
int isLlamadafuncion= 0;
int isINOUT= 0;
int llamolista_ini= 0;
int isConstante= 0;
int isdeffuncion= 0;
extern char error;
int vengodeIF =0;
int sentencia= 0;
int control= 0;

char *archivo;

char *codigo[15000]; //Para mostrar
char *codigoMostrar[15000]; //Para mostrar por pantalla
char *newLine;
int  newLineMAC= 0;

char posID= 0;
int constEntera= -1;
int cantConstantess= 0;
int cantParametros= 0;
int en_tabla_funcion= NIL;
int en_tabla_funcion_Llama= NIL;

int segVar= 2;


token *sbol;


int posTabla;
int cantPar;
int tamARR=0;
char lexema[17];
int bandera;
int posicionTS;
int esParametro = 0;
char *archivo;


int esIndice = 0;

enum noTerminales{
lista_declaracion_de_parametro, definicion_de_funcio, lista_declaraciones_ini, lista_de_inicializadore, proposicion_compuest, lista_de_proposicione, proposicio,proposicion_de_iteracio, proposicion_de_seleccio, proposicion_e_, proposicion_de_retorn, proposicion_expresio, expresio,declaracione, especificador_de_tip, expresion_simpl, lista_de_expresione, termin, facto, variabl, llamada_a_funcio, declaracion_de_parametr, lista_de_declaracione, declaracio, especificador_de_declaracione,relacio, declaracion_de_variabl, constant, declarador_ini, unidad_traduccio
};

enum typeExpresion {variables,
unaVariable,
Constant,
vars_consts,
funcion,
Const_iToStr};


extern FILE *yyin;
extern int despl;

extern float P[];
extern int lp;
extern int lc;
extern char C[];
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
struct Tipo{
    enum    typeExpresion typeExpresionresion;
    int    tipo;
    int    tipo_base;
    float   valor;
    char    sValor[150];
    int     nivel;
    int     despl;
};
int toInt(char t[]){
int res= 0, Ti= strlen(t)-1, piso= 0;

    if (t[0]== '-') piso= 1;

    for (; Ti>=piso; Ti--) res+= (t[Ti]-48)*elev(10,strlen(t)-(Ti+1));

    return (t[0]== '-')? -res : res;
}

int elev(int x, int y){
int Rstado=1;
	for (;y>0;y--) Rstado *= x;
return Rstado;
}

char *deReversa(char cadena[]){
    int i;
    char temp;

    for (i= 0; i < strlen(cadena)/2; i++){
        temp= cadena[i];
        cadena[i]= cadena[strlen(cadena) -1 - i];
        cadena[strlen(cadena) -1 - i]= temp;
    }
    return cadena;
}

char *concatString(char s1[], char s2[]){
    newLine= (char *) calloc(1, 50);
    strcat(newLine, s1);
    strcat(newLine, " ");

    return strcat(newLine, s2);;
}

char *unionST(char s1[], char s2[]){
    newLine= (char *) calloc(1, 50);
    strcat(newLine, s1);
    return strcat(newLine, s2);
}

//**********************************************************
char *strmplN(char *s1){
    int i,j;

    for (i= 0; s1[i]!= 0; i++)
        if (s1[i] == 92 && s1[i+1] == 'n'){
            s1[i++]= '\n';
            for (j= i; s1[j] && s1[j+1]; j++)
                s1[j]=s1[j+1];
            s1[j]= 0;
        }

    return s1;
}

char *strmplT(char *s1){
    int i,j;

    for (i= 0; s1[i]!= 0; i++)
        if (s1[i] == 92 && s1[i+1] == 't'){
            s1[i++]= '\t';
            for (j= i; s1[j] && s1[j+1]; j++)
                s1[j]=s1[j+1];
            s1[j]= 0;
        }

    return s1;
}
//**********************************************************


char *iToStr(int num){
char *salida= (char *)calloc (1, TAM_LEXEMA);
int i=0;
if (num >= 0){
	if (num == 0){
            salida[0]= '0';
            i= 1;
        }
        for (;num>0;i++){
            salida[i]=num%10+48;
            num/=10;
        }
        salida[i]= 0;
        return deReversa(salida);
    }else
return unionST("-",iToStr(-num));
}

void appendMAC(int INST, char linea[]){
    //printf("INSTI string:  %s\n", iToStr(INST));
    //printf("INSTI:  %d\n", INST);
    codigo[newLineMAC]= concatString(iToStr(INST),linea);
    //codigo[newLineMAC]= concatString(linea,iToStr(INST));
    codigoMostrar[newLineMAC++]= concatString(getStringINST(INST),linea);
}

void appendKMAC(int INST, char linea[], int kLinea){
    int i;

    for (i= newLineMAC-1; i >= kLinea; i--){
        codigo[i+1]= codigo[i];
        codigoMostrar[i+1]= codigoMostrar[i];
    }
    codigo[kLinea]= concatString(iToStr(INST),linea);
    codigoMostrar[kLinea]= concatString(getStringINST(INST),linea);

    newLineMAC++;
}

void appendParam(tipo_inf_res *info_param){
    tipo_inf_res *cur;

    cur= ts[en_tabla_funcion].ets->desc.part_var.sub.ptr_inf_res;

    if (cur == NULL)
       ts[en_tabla_funcion].ets->desc.part_var.sub.ptr_inf_res= info_param;
    else{
        while (cur->ptr_sig != NULL)
            cur= cur->ptr_sig;

        cur->ptr_sig= info_param;
    }

}
tipo_inf_res getParam(int k){
    int i;
    tipo_inf_res *cur, salida;

    cur= ts[en_tabla_funcion_Llama].ets->desc.part_var.sub.ptr_inf_res;

    for (i= 1; i <= k && cur != NULL; i++){
        salida= *cur;
        cur= cur->ptr_sig;
    }
    return salida;
}

void chequeoParam(struct Tipo parametroReal, int numParametro){
    tipo_inf_res parametroFormal;

  //  printf("numero de parametro..........       %d\n",numParametro);

    if (numParametro <= ts[en_tabla_funcion_Llama].ets->desc.part_var.sub.cant_par){

        parametroFormal = getParam(numParametro);

        // printf("NUMERO PARAMETRO(%d)\n",numParametro);
	/*
	printf("%d\n",parametroFormal.ptero_tipo_base);
	printf("%d\n",parametroFormal.ptero_tipo);
	printf("%c\n",parametroFormal.tipo_pje);
	*/

        if (parametroFormal.ptero_tipo == en_tabla("TIPOARREGLO")){

            if (parametroReal.typeExpresionresion != unaVariable)
                error_handler(91);
            else
            if (parametroReal.tipo != en_tabla("TIPOARREGLO") || (parametroReal.tipo_base != parametroFormal.ptero_tipo_base)){

                //printf("\n\n\nparametro real tipo... %d\n",parametroReal.tipo);
		//printf("posicion del tipo arreglo... %d\n",		en_tabla("TIPOARREGLO"));

                 //printf("numero de parametro... %d\n\n\n\n\n",numParametro);
		//printf("parametro real tipo base... %d\n",parametroReal.tipo_base);
                //printf("parametro formal tipo base... %d\n",parametroFormal.ptero_tipo_base);

                 //printf("arribaaaaaaaaaaaaa %d\n\n\n\n\n",numParametro);
                error_handler(90);
		}
        }else{

            if (parametroReal.tipo == en_tabla("TIPOARREGLO"))
                error_handler(90);
            else
            if (parametroFormal.tipo_pje == 'r' && parametroReal.typeExpresionresion != unaVariable)
                error_handler(92);

	if (parametroFormal.ptero_tipo == en_tabla("float") && (parametroReal.tipo == en_tabla("float") || parametroReal.tipo == en_tabla("char") || 				parametroReal.tipo == en_tabla("int"))){return;}
		else //error_handler(90);

	if (parametroFormal.ptero_tipo == en_tabla("int") && (parametroReal.tipo == en_tabla("char") || parametroReal.tipo == en_tabla("int"))){return;}
		else //error_handler(90);
		if (parametroFormal.ptero_tipo == en_tabla("char") && parametroReal.tipo == en_tabla("char") ){return;}
		else error_handler(90);
		}


    }
}

float charToFloat(char num[]){

    char part_ent[strlen(num)+1], part_dec[strlen(num)+1];
    int punto= 0;
    float res= 0;
    int i, decimales, piso= 0;


    if (num[0]== '-') piso= 1;//Si es negativo

    part_ent[0]= part_dec[0]= '0';
    part_ent[1]= part_dec[1]= 0;

    for (i= piso; i <= strlen(num); i++){
        if (num[i] == '.'){
            punto= 1;
            part_ent[i-piso]= 0;
        }else
            if (!punto)
                part_ent[i-piso]= num[i];
            else
                part_dec[i-piso - (strlen(part_ent)+1)]= num[i];
    }
    decimales= strlen(part_dec);
    res= (toInt(strcat(part_ent, part_dec))+.0)/elev(10, decimales);

    return (num[0]== '-')? -res : res;
}
void clearLMAC(){
    codigo[newLineMAC-1]= NULL;
    codigoMostrar[--newLineMAC]= NULL;
}

void clearKLMAC(int kLinea){
    int i;

    codigo[kLinea]= NULL;
    codigoMostrar[kLinea]= NULL;

    for (i= kLinea; i < newLineMAC-1; i++){
        codigo[i]= codigo[i+1];
        codigoMostrar[i]= codigoMostrar[i+1];
    }
    newLineMAC--;
}

void verInstrucciones(){
    int i;

    printf("\n\n MAC:\n\n\n");

    for (i= 0; i < newLineMAC; i++){
        //printf("CODIGO %d: %s\n", i, codigo[i]);
        printf("Linea %d: %s\n", i+1, codigoMostrar[i]);
    }


    printf("\n******************\n");
}

/*
void generarSalida(){

printf("ffffffffffffffffff");
FILE *PObj;


if ((PObj= fopen(strcat(archivo, ".o"), "w")) != NULL){
int i;

for (i= 0; i < dameCS(); i++)
	fprintf(PObj, "%c\n", dameC(i));

//fprintf(PObj, "$ ");

for (i= 0; i < newLineMAC; i++)
	fprintf(PObj, "%s\n", codigoMostrar[i]);

for (i= 0; i < newLineMAC; i++)
	printf(dameC(i));

	}
fclose(PObj);
}
*/




void generarSalida(){
FILE *PObj;
char arreglo[500];
int j;
int t;
int index,index2;
char aux;
char arreglo1[30];
char arreglo2[30];
int banderasa = 0;
if ((PObj= fopen(strcat(archivo, ".o"), "w")) != NULL){
	int i;
        //printf("dameCS:_________________ %c\n", dameCS());
	fprintf(PObj, "$ ");
        for (i= 0; i < newLineMAC; i++){
                //index2=0;
                //strcpy(arreglo1,codigo[i]);
                //printf("arreglo: %s\n", arreglo1);
		/*for(index = 0; arreglo1[index]!='\0'; index++){
			if(arreglo1[index]!= '_'){
				arreglo2[index2++] = arreglo1[index];
				banderasa=1;

			}else{
				banderasa=0;
                                printf("arreglo2: %s\n", arreglo2);
                                arreglo2[index2]='\0';
				fprintf(PObj, "%f\n", charToFloat(arreglo2));
                                index2=0; arreglo2[0]='\0';

			}

		}*/
	         //printf("arreglo2: %s\n", codigo[i]);
        	fprintf(PObj, "%s\n", codigo[i]);
        }

	fprintf(PObj, "$ ");


	//for(t=0;t<150;t++) printf("arreglo");

        for (i= 0,j=0; i < dameCS(); i++){
        //for (i= 0,j=0; i < dameCS()-1; i++){
        	//aux = dameC(i);
        	//printf("dameC metodo:               %c\n", dameC(i));
        	//printf("aux:               %c\n", aux);
        	//arreglo[j] = aux;
		 fprintf(PObj, "%d\n", dameC(i));
                //fwrite(&aux, sizeof(char), 1,PObj);
	}
       	fprintf(PObj, "$ ");
	//for(t=0;t<150;t++) printf("arreglo %c\n", arreglo[t]);
        //printf("arreglo %s\n", *arreglo);

        //aux =   "$";
        //fwrite(&aux, sizeof(char), 1,PObj);
	}
fclose(PObj);
}

int tam_Instr(char *Inst){
    int i, tam= 0;
    for (i= 0; i < strlen(Inst); i++)
        if (Inst[i] == ' ' && Inst[i+1] != 0) tam++;
    return tam + 1;
}

int calcularDespl(int LineaO, int LineaSalto){
    int i, despl= 0;
    if (LineaO <= LineaSalto){
        for (i= LineaO ; i < LineaSalto; i++)
            despl+= tam_Instr(codigo[i]);
        return despl;
    }else
        return -(calcularDespl(LineaSalto, LineaO)+ 2 + 3);
}

char Cohersion(char tipo, char Tipo_Operado){
    char Tipo_Retorno= en_tabla("float");

    if (tipo == en_tabla("TIPOARREGLO") || Tipo_Operado == en_tabla("TIPOARREGLO"))
        return en_tabla("TIPOARREGLO");

    if (tipo == en_tabla("TIPOERROR") || Tipo_Operado == en_tabla("TIPOERROR"))
        return en_tabla("TIPOERROR");

    if (tipo == en_tabla("char"))
        Tipo_Retorno= Tipo_Operado;
    else
    if (tipo == en_tabla("int")){
        if (Tipo_Operado == en_tabla("float"))
            Tipo_Retorno= Tipo_Operado;
        else
            Tipo_Retorno= en_tabla("int");
    }

    return Tipo_Retorno;
}

char getTipo(char tipo){
    if (tipo == en_tabla("char"))
        return 0;
    else
    if (tipo == en_tabla("int")){

        return 1;
    }else{

        return 2;
    }
}

char *getStringINST(int INST){
    char *sINST= (char *)calloc (1, 13);
    strcpy(sINST, ">>ERROR<<");
    switch(INST){
        case CRCT   : strcpy(sINST, sCRCT); break;
        case CRVL   : strcpy(sINST, sCRVL); break;
        case SUM    : strcpy(sINST, sSUM); break;
        case SUB    : strcpy(sINST, sSUB); break;
        case MUL    : strcpy(sINST, sMUL); break;
        case DIV    : strcpy(sINST, sDIV); break;
        case INV    : strcpy(sINST, sINV); break;
        case AND    : strcpy(sINST, sAND); break;
        case OR     : strcpy(sINST, sOR); break;
        case NEG    : strcpy(sINST, sNEG); break;
        case POP    : strcpy(sINST, sPOP); break;
        case CAST   : strcpy(sINST, sCAST); break;
        case CMMA   : strcpy(sINST, sCMMA); break;
        case CMME   : strcpy(sINST, sCMME); break;
        case CMIG   : strcpy(sINST, sCMIG); break;
        case CMAI   : strcpy(sINST, sCMAI); break;
        case CMEI   : strcpy(sINST, sCMEI); break;
        case CMNI   : strcpy(sINST, sCMNI); break;
        case ALM    : strcpy(sINST, sALM); break;
        case LEER   : strcpy(sINST, sLEER); break;
        case IMPR   : strcpy(sINST, sIMPR); break;
        case BIFF   : strcpy(sINST, sBIFF); break;
        case BIFS   : strcpy(sINST, sBIFS); break;
        case INPP   : strcpy(sINST, sINPP); break;
        case PARAR  : strcpy(sINST, sPARAR); break;
        case ALOC   : strcpy(sINST, sALOC); break;
        case DMEM   : strcpy(sINST, sDMEM); break;
        case CRDI   : strcpy(sINST, sCRDI); break;
        case CRVLI  : strcpy(sINST, sCRVLI); break;
        case ALMI   : strcpy(sINST, sALMI); break;
        case ENPR   : strcpy(sINST, sENPR); break;
        case CHPR   : strcpy(sINST, sCHPR); break;
        case RTPR   : strcpy(sINST, sRTPR); break;
        case ENBL   : strcpy(sINST, sENBL); break;
        case FINB   : strcpy(sINST, sFINB); break;
        case IMPCS  : strcpy(sINST, sIMPCS); break;
        case CRCTS  : strcpy(sINST, sCRCTS);
    }
    return sINST;
}

void compilacion(){

    sbol=&token1 ;

    appendMAC(INPP,"");
    //appendMAC(ENBL, iToStr(get_nivel()));

    printf("\nCOMPILACION\n");

    inic_tablas();

    scanner();

    unidad_traduccion(cons(NADA, CEOF));

    if (Clase_Ident("main") != CLASFUNC){
            error_handler(15);
            error_handler(COD_IMP_ERRORES);
    }else
            if (ts[en_tabla("main")].ets->desc.part_var.sub.cant_par != 0){
                    error_handler(36);
                    error_handler(COD_IMP_ERRORES);
            }else
                    if (Tipo_Ident("main") != en_tabla("void")){
                            error_handler(35);
                            error_handler(COD_IMP_ERRORES);
                    }


    if (sbol->codigo != CEOF) error_handler(8);
    printf("\n\n\nCOMPILACION CORRECTA\n\n\n\n");
    //appendMAC(FINB, iToStr(get_nivel()));
    appendMAC(PARAR,"");
    if (error == 0){
        verInstrucciones();
        generarSalida();
    }
}

/*
void ejecucion(){
    //int j =0;
    FILE *PObj;
    char cur[25];
    printf("archivo:   %s\n",strcat(archivo, ".o"));
    PObj= fopen(strcat(archivo, ".o"), "r");
    if (PObj!= NULL){
      //  printf("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
       // while(j<=1000000){
        // printf("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
        //  j++;
     //	}
        int i;
        fscanf(PObj, "%s", cur);
        //fgets (cur , 20,PObj);
        //printf("cur: %s",&cur);
       // for (i= 0; cur!=NULL ; i++){
        //for (i= 0; strcmp(cur, "$"); i++){
            addC(toInt(cur));
            fscanf(PObj, "%s", cur);
        }

       //for (i= 0; strcmp(cur, "$"); i++){
     //   addC(toInt(cur));
           // fscanf(PObj, "%s", cur);
     // }

     //    fscanf(PObj, "%s", cur);

     //        float val = -1;
     //        for (i = 0; !feof(PObj); i++) {
     //	       printf("cur: %s",cur);
     //            //val = P[i];
     //
     //              }

        // while(!feof(PObj)){
         for (i= 0;!feof(PObj); i++){
            float cod;

             cod= charToFloat(cur);
            //printf("floAT: %f",&cod);
	    //fgets (cur ,100,PObj);
            printf("cur: %s",cur);
            pushP(&cod);

            fscanf(PObj, "%s", cur);
        }
    }else{
          //printf("zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");
    }

    fclose(PObj);

    interprete();

}

*/


void ejecucion(){
    float cod;
    FILE *PObj;
    char cur[500];
    int kk;

    if ((PObj= fopen(strcat(archivo, ".o"), "r")) != NULL){
        int i;
//      for(kk=0;kk<10000;kk++)printf("aaaaaaaaaaaaaaaaaaaaaaaaaaa\n");

        fscanf(PObj, "%s", &cur);
        fscanf(PObj, "%s", &cur);
	//for(kk=0;kk<10000;kk++) printf("PASOOOOOOOOOOOOO\n");
        for (i= 0; strcmp(cur, "$"); i++){
            cod= charToFloat(cur);
           //  printf("COD: %f\n",cod);
           // printf("CUR: %s\n",cur);
            //pushP(&cod);                 // 1) Cargar Instruccion

            P[i] = cod;
            lp++;
            fscanf(PObj, "%s", &cur);    // 2) Leer otra Instruccion
        }

       // for(kk=0;kk<10000;kk++) printf("PASOOOOOOOOOOOOOFUERAAAAAAAAAA\n");

        fscanf(PObj, "%s", &cur);

       for (i= 0; strcmp(cur, "$"); i++){   // 1) Leer y Cargar las Constanes de Strings
            addC(toInt(cur));
            fscanf(PObj, "%s", &cur);
        }

     /*
     float val = -1;
                for (i = 0; val != PARAR; i++) {
                    fscanf(obj, "%f\n", &P[i]);
                    val = P[i];
     }
    */
    //for(kk=0;kk<200;kk++) printf("P: %f\n",P[kk]);
    //for(kk=0;kk<200;kk++) printf("C: %c\n",C[kk]);
    }
    fclose(PObj);
    //28352
    interprete2();
}






int main( int argc,char *argv[]) {

linea = (char *) malloc (2);
    strcat(linea, "");

    nro_linea=0;

    if (argc != 3) {
        error_handler(6);
        error_handler(COD_IMP_ERRORES);
        exit(1);
    }
    else {
        if ((yyin = fopen(argv[2], "r" )) == NULL) {
            error_handler(7);
            error_handler(COD_IMP_ERRORES);
            exit(1);
        }
        archivo= argv[2];
        *(archivo + strlen(archivo)-2)= 0;
    }

    if (argv[1][1] == 'c'){
                compilacion();

	}
    else if (argv[1][1] == 'e'){

        ejecucion();

	}
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
    case CVOID:{
	scanner();
	posID=en_tabla("void");
	break;}
    case CCHAR:{
	scanner();
	posID=en_tabla("char");
	break;}
    case CINT:{
	scanner();
	posID=en_tabla("int");
	break;}
    case CFLOAT:{
	scanner();
	posID=en_tabla("float");
	break;}
     default: error_handler(17);
    }

    test(folset, cons(NADA,NADA), 52);

}

void especificador_declaracion(set folset){
  test(firsts[ED],folset, 53);

  switch (sbol->codigo) {
    case CPAR_ABR: {
        definicion_funcion(folset);
        break;}
    case CASIGNAC:
    case CCOR_ABR:
    case CCOMA:
    case CPYCOMA: { declaracion_variable(folset); break;}
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

    tipo_inf_res *info_res_param= NULL;
    info_res_param= (tipo_inf_res *) calloc(1, sizeof(tipo_inf_res));

  especificador_tipo(une(folset,cons(CAMPER|CCOR_ABR|CCOR_CIE,CIDENT)));

  if (sbol->codigo == CAMPER){
      inf_id->desc.part_var.tipo_pje = PAR_REFERENCIA;
       inf_id->cant_byte = ts[en_tabla("int")].ets->cant_byte;
      scanner();
  }else{
      inf_id->desc.part_var.tipo_pje = PAR_VALOR;
       inf_id->cant_byte = ts[posID].ets->cant_byte;

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
  }segVar= newLineMAC;


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
  test(une(folset,firsts[DI]), une(firsts[CON],une(firsts[LI],une(folset,cons(CCOR_CIE|CLLA_ABR|CLLA_CIE, CASIGNAC)))),58);

  if(in(sbol->codigo,firsts[CON])){
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

  constante(une(folset, une(cons(CCOMA,NADA),firsts[CON])));

  while (sbol->codigo == CCOMA || in(sbol->codigo,firsts[CON])) {
      if(in(sbol->codigo,firsts[CON])){
          error_handler(75);
      }else{
          scanner();
      }
    constante(une(folset, une(cons(CCOMA,NADA),firsts[CON])));
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

  proposicion(une(folset,firsts[PRO]));

  while (sbol->codigo == CLLA_ABR || sbol->codigo == CMAS ||
	 sbol->codigo == CMENOS || sbol->codigo == CIDENT ||
	 sbol->codigo == CPAR_ABR || sbol->codigo == CNEG ||
	 sbol->codigo == CCONS_ENT || sbol->codigo == CCONS_FLO ||
	 sbol->codigo == CCONS_CAR || sbol->codigo == CCONS_STR ||
	 sbol->codigo == CIF || sbol->codigo == CWHILE ||
	 sbol->codigo == CIN || sbol->codigo == COUT ||
	 sbol->codigo == CPYCOMA || sbol->codigo == CRETURN)

    proposicion(une(folset,firsts[PRO]));

}

void proposicion(set folset){
  test(firsts[PRO],folset,63);
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

  expresion(une(une(folset,cons(CPAR_CIE,NADA)),firsts[PRO]));

  if (sbol->codigo == CPAR_CIE) scanner();
  else error_handler(20);

  proposicion(folset);

}


void proposicion_seleccion(set folset) {

  if (sbol->codigo == CIF) scanner();
  else error_handler(27);

  if (sbol->codigo == CPAR_ABR) scanner();
  else error_handler(19);

  expresion(une(une(folset,cons(CPAR_CIE|CELSE,NADA)),firsts[PRO]));

  if (sbol->codigo == CPAR_CIE) scanner();
  else error_handler(20);

  proposicion(une(une(folset,cons(CELSE,NADA)),firsts[PRO]));

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
            variable(une(firsts[VAR], une(folset,cons(CPYCOMA|CSHR,NADA))));

             while (sbol->codigo == CSHR ) {
                scanner();
                variable(une(une(folset,cons(CSHR|CPYCOMA,NADA)),firsts[VAR]));
               
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
  test(firsts[VAR],folset,70);

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
  test(firsts[CON],folset,73);

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














