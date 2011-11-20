/******************************************************************
            Este es el archivo correspondiente al PARSER
 *******************************************************************/

#define EXTERNA extern
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ts.h"
#include "set.c"
#include "codigos.h"
#include "var_globales.h"
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
void lista_inicializadores(set folset);
void lista_proposiciones(set folset);
void lista_declaraciones(set folset);
void declaracion(set folset);
void proposicion(set folset);
void proposicion_expresion(set folset);
void proposicion_compuesta(set folset);
void proposicion_seleccion(set folset);
void proposicion_iteracion(set folset);
void proposicion_e_s(set folset);
void proposicion_retorno(set folset);
struct typeAux expresion(set folset);
struct typeAux expresion_simple(set folset);
struct typeAux termino(set folset);
struct typeAux factor(set folset);
struct typeAux variable(set folset);
struct typeAux llamada_funcion(set folset);
void lista_expresiones(set folset);
struct typeAux constante(set folset);

char *obtenerInst(int INST);
void scanner ();
extern FILE *yyin;
extern int despl;
extern float P[];
extern int lp;
extern int lc;
extern char C[];
extern char error;
int isReturn= 0;
int isLlamadafuncion= 0;
int isINOUT= 0;
int llamolista_ini= 0;
int isConstante= 0;
int isdeffuncion= 0;
int sentencia= 0;
int control= 0;
char *archivo;
char *codigo[15000];
char *codigoMostrar[15000];
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

enum typeExpresion {
    variables,
    unaVariable,
    Constant,
    vars_consts,
    funcion,
    Const_iToStr
};

void scanner() {
  int i;
  for (;(i=yylex())!= NADA && sbol->codigo == SEGUIR;);
  if (i == NADA) sbol->codigo = CEOF;
  liberar = linea;
  linea = (char *) malloc (strlen(linea) + strlen (token1.lexema) + 3);
  strcpy(linea, liberar);
  strcat(linea, token1.lexema);
  free ( (void *) liberar);
}

struct typeAux{
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
    codigo[newLineMAC]= concatString(iToStr(INST),linea);
    codigoMostrar[newLineMAC++]= concatString(obtenerInst(INST),linea);
}

void appendKMAC(int INST, char linea[], int kLinea){
    int i;

    for (i= newLineMAC-1; i >= kLinea; i--){
        codigo[i+1]= codigo[i];
        codigoMostrar[i+1]= codigoMostrar[i];
    }
    codigo[kLinea]= concatString(iToStr(INST),linea);
    codigoMostrar[kLinea]= concatString(obtenerInst(INST),linea);

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

void chequeoParam(struct typeAux parametroReal, int numParametro){
    tipo_inf_res parametroFormal;

    if (numParametro <= ts[en_tabla_funcion_Llama].ets->desc.part_var.sub.cant_par){

        parametroFormal = getParam(numParametro);


        if (parametroFormal.ptero_tipo == en_tabla("TIPOARREGLO")){

            if (parametroReal.typeExpresionresion != unaVariable)
                error_handler(91);
            else
            if (parametroReal.tipo != en_tabla("TIPOARREGLO") || (parametroReal.tipo_base != parametroFormal.ptero_tipo_base)){
                            
                error_handler(90);
		}
        }else{ 

            if (parametroReal.tipo == en_tabla("TIPOARREGLO"))
                error_handler(90);
            else
            if (parametroFormal.tipo_pje == 'r' && parametroReal.typeExpresionresion != unaVariable)
                error_handler(92);
            
	if (parametroFormal.ptero_tipo == en_tabla("float") && (parametroReal.tipo == en_tabla("float") || parametroReal.tipo == en_tabla("char") || 				parametroReal.tipo == en_tabla("int"))){return;}
		else 

	if (parametroFormal.ptero_tipo == en_tabla("int") && (parametroReal.tipo == en_tabla("char") || parametroReal.tipo == en_tabla("int"))){return;}
		else 
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

    if (num[0]== '-') piso= 1;

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

        printf("Linea %d: %s\n", i+1, codigoMostrar[i]);    	
    }
    printf("\n******************\n");
}

void generarSalida(){
FILE *PObj;
int j;
if ((PObj= fopen(strcat(archivo, ".o"), "w")) != NULL){
	int i;
        
	fprintf(PObj, "$ ");
        for (i= 0; i < newLineMAC; i++){ 
        	fprintf(PObj, "%s\n", codigo[i]);                         
        }

	fprintf(PObj, "$ "); 

        for (i= 0,j=0; i < dameCS(); i++){ 

		 fprintf(PObj, "%d\n", dameC(i));
	}
       	fprintf(PObj, "$ "); 

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

char *obtenerInst(int INST){
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
    appendMAC(PARAR,"");
    if (error == 0){
        verInstrucciones();
        generarSalida();
    }
}

void ejecucion() {

    float cod;
    FILE *PObj;
    char cur[500];
    if ((PObj = fopen(strcat(archivo, ".o"), "r")) != NULL) {
        int i;
        fscanf(PObj, "%s", cur);
        fscanf(PObj, "%s", cur);

        for (i = 0; strcmp(cur, "$"); i++) {
            cod = charToFloat(cur);

            P[i] = cod;
            lp++;
            fscanf(PObj, "%s", cur);
        }

        fscanf(PObj, "%s", cur);

        for (i = 0; strcmp(cur, "$"); i++) {
            addC(toInt(cur));
            fscanf(PObj, "%s", cur);
        }
    }
    fclose(PObj);

    interprete2();
}

void test(set conjunto, set puntosRecuperacion, int error){
    if(in(sbol->codigo, conjunto)==0){
        error_handler(error);	
        conjunto=une(conjunto, puntosRecuperacion);
        while (in(sbol->codigo,conjunto)==0){
            scanner();
	}
    }
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
    initFirsts();
    if (argv[1][1] == 'c'){ 
                compilacion();
	
	}
    else if (argv[1][1] == 'e'){  
        
        ejecucion();

	}
}

int chartoInt(char str[]){
	int num;
	
	num = atoi(str); 

return num;
}

/********* funciones del parser ***********/

void unidad_traduccion(set folset) {
    test(firsts[DE], folset, 50);
    while (sbol->codigo == CVOID || sbol->codigo == CCHAR || sbol->codigo == CINT || sbol->codigo == CFLOAT) {
        declaraciones(une(folset, firsts[DE]));
        test(firsts[DE], folset, 51);
    }
}

void declaraciones(set folset) {
    especificador_tipo(une(folset, une(cons(NADA, CIDENT), firsts[ED])));
    if (sbol->codigo == CIDENT) {
        strcpy(inf_id->nbre, sbol->lexema);
        scanner();
    } else error_handler(16);
    especificador_declaracion(folset);
}

void especificador_tipo(set folset) {

    test(firsts[ET], folset, 51);
    switch (sbol->codigo) {
        case CVOID:
        {
            scanner();
            posID = en_tabla("void");
            break;
        }
        case CCHAR:
        {
            scanner();
            posID = en_tabla("char");
            break;
        }
        case CINT:
        {
            scanner();
            posID = en_tabla("int");
            break;
        }
        case CFLOAT:
        {
            scanner();
            posID = en_tabla("float");
            break;
        }
        default: error_handler(17);
    }
    test(folset, cons(NADA, NADA), 52);
}

void especificador_declaracion(set folset) {
    test(firsts[ED], folset, 53);
    switch (sbol->codigo) {
        case CPAR_ABR:
        {
            definicion_funcion(folset);
            break;
        }
        case CASIGNAC:
        case CCOR_ABR:
        case CCOMA:
        case CPYCOMA:
        {
            declaracion_variable(folset);
            break;
        }
        default: error_handler(18);
    }
    test(folset, cons(NADA, NADA), 54);
}

void definicion_funcion(set folset) {
    isdeffuncion = 1;
    isReturn = 0;
    inf_id->clase = CLASFUNC;
    inf_id->ptr_tipo = posID;
    inf_id->cant_byte = ts[posID].ets->cant_byte;

    en_tabla_funcion = insertarTS();
    pushTB();

    if (sbol->codigo == CPAR_ABR) scanner();
    else error_handler(19);

    cantParametros = 0;

    if (sbol->codigo == CVOID || sbol->codigo == CCHAR ||
            sbol->codigo == CINT || sbol->codigo == CFLOAT || sbol->codigo == CIDENT)
        lista_declaraciones_param(une(une(cons(CPAR_CIE, NADA), folset), firsts[PC]));

    ts[en_tabla_funcion].ets->desc.part_var.sub.cant_par = cantParametros;

    if (sbol->codigo == CPAR_CIE) scanner();
    else error_handler(20);

    proposicion_compuesta(folset);
    en_tabla_funcion = NIL;
}

void declaracion_variable(set folset) {
    declarador_init(une(une(cons(CCOMA | CPYCOMA, NADA), firsts[LDI]), folset));

    if (sbol->codigo == CCOMA) {
        scanner();
        lista_declaraciones_init(une(folset, cons(CPYCOMA, NADA)));
    }
    segVar = newLineMAC;

    if (sbol->codigo == CPYCOMA) scanner();
    else error_handler(22);
}

void lista_declaraciones_param(set folset) {

    declaracion_parametro(une(une(cons(CCOMA, NADA), folset), firsts[DP]));

    while (sbol->codigo == CCOMA || in(sbol->codigo, firsts[DP])) {
        if (in(sbol->codigo, firsts[DP])) {
            error_handler(75);
        } else scanner();
        declaracion_parametro(une(une(cons(CCOMA, NADA), folset), firsts[DP]));
    }
}

void declaracion_parametro(set folset) {
    tipo_inf_res *info_res_param = NULL;
    info_res_param = (tipo_inf_res *) calloc(1, sizeof (tipo_inf_res));
    especificador_tipo(une(folset, cons(CAMPER | CCOR_ABR | CCOR_CIE, CIDENT)));
    inf_id->clase = CLASPAR;
    if (posID == en_tabla("void")) {
        error_handler(82);
        inf_id->ptr_tipo = en_tabla("TIPOERROR");
    } else inf_id->ptr_tipo = posID;
    if (sbol->codigo == CAMPER) {
        scanner();
        inf_id->desc.part_var.tipo_pje = 'r';
        inf_id->cant_byte = ts[en_tabla("int")].ets->cant_byte;
    } else {
        inf_id->desc.part_var.tipo_pje = 'v';
        inf_id->cant_byte = ts[posID].ets->cant_byte;
    }
    if (sbol->codigo == CIDENT) {
        strcpy(inf_id->nbre, sbol->lexema);
        scanner();
    } else error_handler(16);
    if (sbol->codigo == CCOR_ABR) {
        if (inf_id->desc.part_var.tipo_pje == 'r')
            error_handler(89);

        inf_id->desc.part_var.tipo_pje == 'r';
        inf_id->desc.part_var.arr.ptero_tipo_base = inf_id->ptr_tipo;
        inf_id->ptr_tipo = en_tabla("TIPOARREGLO");

        scanner();
        if (sbol->codigo == CCOR_CIE) scanner();
        else error_handler(21);
    }

    cantParametros++;
    info_res_param->ptero_tipo = inf_id->ptr_tipo;
    info_res_param->tipo_pje = inf_id->desc.part_var.tipo_pje;
    info_res_param->ptero_tipo_base = inf_id->desc.part_var.arr.ptero_tipo_base;
    info_res_param->ptr_sig = NULL;
    appendParam(info_res_param);
    insertarTS();
    test(folset, cons(NADA, NADA), 55);
}

void declarador_init(set folset) {
    char t;
    struct typeAux TipoC;
    TipoC.tipo = NIL;
    test(une(firsts[DI], folset), firsts[CON], 58);

    if (posID == en_tabla("void")) {
        error_handler(82);
        inf_id->ptr_tipo = en_tabla("TIPOERROR");
    } else inf_id->ptr_tipo = posID;

    inf_id->cant_byte = ts[inf_id->ptr_tipo].ets->cant_byte;


    if (in(sbol->codigo, firsts[CON])) {
        error_handler(79);
        constante(folset);
    } else
        switch (sbol->codigo) {
            case CASIGNAC:
                scanner();
                if (sbol->codigo == CCONS_STR) {
                    scanner();
                    error_handler(86);
                }
                TipoC = constante(folset);

                break;
            case CCOR_ABR:
                scanner();
                constEntera = -1;
                if (sbol->codigo == CCONS_ENT) {
                    constEntera = toInt(sbol->lexema);
                    if (constEntera <= 0) error_handler(80);
                    scanner();
                } else {

                    scanner();
                }
                if (sbol->codigo == CCOR_CIE) scanner();
                else error_handler(21);

                if (sbol->codigo == CASIGNAC || sbol->codigo == CLLA_ABR) {
                    if (sbol->codigo == CLLA_ABR) error_handler(79);
                    else scanner();

                    if (sbol->codigo == CLLA_ABR)
                        scanner();
                    else
                        error_handler(23);

                    cantConstantess = 0;
                    lista_inicializadores(une(folset, cons(CLLA_CIE, NADA)));

                    if (constEntera == -1) constEntera = cantConstantess;
                    else if (cantConstantess != constEntera) error_handler(94);

                    if (sbol->codigo == CLLA_CIE) scanner();
                    else error_handler(24);
                }

                inf_id->desc.part_var.arr.cant_elem = constEntera;

                inf_id->desc.part_var.arr.ptero_tipo_base = inf_id->ptr_tipo;


                if (constEntera == -1) {
                    error_handler(83);
                    inf_id->desc.part_var.arr.ptero_tipo_base = en_tabla("TIPOERROR");
                }

                inf_id->ptr_tipo = en_tabla("TIPOARREGLO");
                inf_id->cant_byte = (inf_id->desc.part_var.arr.cant_elem)*(ts[posID].ets->cant_byte);

                break;
        };

    inf_id->clase = CLASVAR;

    inf_id->desc.nivel = get_nivel();

    inf_id->desc.despl = despl;
    despl += inf_id->cant_byte;

    appendMAC(ALOC, iToStr(inf_id->cant_byte));
    if (TipoC.tipo != NIL) {

        t = getTipo(inf_id->ptr_tipo);

        if (t == 2)
            appendMAC(CRCT, concatString(iToStr(t), TipoC.sValor));
        else
            appendMAC(CRCT, concatString(iToStr(t), iToStr((int) TipoC.valor)));
        appendMAC(ALM, concatString(concatString(iToStr(inf_id->desc.nivel), iToStr(inf_id->desc.despl)), iToStr(t)));
        appendMAC(POP, iToStr(t));
    }

    insertarTS();
    test(folset, cons(NADA, NADA), 59);
}

void lista_declaraciones_init(set folset) {

    test(firsts[LDI], une(une(folset, cons(CCOMA, NADA)), firsts[DI]), 57);
    if (sbol->codigo == CIDENT) {
        strcpy(inf_id->nbre, sbol->lexema);
        scanner();
    } else error_handler(16);

    declarador_init(une(une(cons(CCOMA, CIDENT), firsts[DI]), folset));

    while (sbol->codigo == CCOMA || sbol->codigo == CIDENT) {

        if (sbol->codigo == CIDENT) {
            error_handler(75);
        } else scanner();
        if (sbol->codigo == CIDENT) {
            strcpy(inf_id->nbre, sbol->lexema);
            scanner();
        } else error_handler(16);

        declarador_init(une(une(cons(CCOMA, CIDENT), firsts[DI]), folset));
    }
}

void lista_inicializadores(set folset) {
    llamolista_ini = 1;
    constante(une(une(firsts[CON], folset), cons(CCOMA, NADA)));
    llamolista_ini = 0;
    while (sbol->codigo == CCOMA || in(sbol->codigo, firsts[CON])) {
        if (in(sbol->codigo, firsts[CON])) {
            error_handler(75);
        } else {
            scanner();
        }
        constante(une(une(firsts[CON], folset), cons(CCOMA, NADA)));
    }
}

void lista_proposiciones(set folset) {

    proposicion(une(folset, firsts[PRO]));

    while (sbol->codigo == CLLA_ABR || sbol->codigo == CMAS ||
            sbol->codigo == CMENOS || sbol->codigo == CIDENT ||
            sbol->codigo == CPAR_ABR || sbol->codigo == CNEG ||
            sbol->codigo == CCONS_ENT || sbol->codigo == CCONS_FLO ||
            sbol->codigo == CCONS_CAR || sbol->codigo == CCONS_STR ||
            sbol->codigo == CIF || sbol->codigo == CWHILE ||
            sbol->codigo == CIN || sbol->codigo == COUT ||
            sbol->codigo == CPYCOMA || sbol->codigo == CRETURN)

        proposicion(une(folset, firsts[PRO]));
}

void lista_declaraciones(set folset) {

    declaracion(une(folset, firsts[D]));

    while (sbol->codigo == CVOID || sbol->codigo == CCHAR ||
            sbol->codigo == CINT || sbol->codigo == CFLOAT)

        declaracion(une(folset, firsts[D]));
}

void declaracion(set folset) {

    especificador_tipo(une(une(folset, firsts[LDI]), cons(CPYCOMA, NADA)));

    lista_declaraciones_init(une(folset, cons(CPYCOMA, NADA)));

    if (sbol->codigo == CPYCOMA) scanner();
    else error_handler(22);

    test(folset, cons(NADA, NADA), 62);

}

void proposicion(set folset) {

    test(firsts[PRO], folset, 63);
    switch (sbol->codigo) {
        case CLLA_ABR: proposicion_compuesta(folset);
            break;
        case CWHILE: proposicion_iteracion(folset);
            break;
        case CIF: proposicion_seleccion(folset);
            break;
        case CIN:
        case COUT: proposicion_e_s(folset);
            break;
        case CMAS:
        case CMENOS:
        case CIDENT:
        case CPAR_ABR:
        case CNEG:
        case CCONS_ENT:
        case CCONS_FLO:
        case CCONS_CAR:
        case CCONS_STR:
        case CPYCOMA: proposicion_expresion(folset);
            break;
        case CRETURN: proposicion_retorno(folset);
            break;
        default: error_handler(25);
    }
}

void proposicion_expresion(set folset) {
    sentencia = 1;
    control = -1;

    if (sbol->codigo == CMAS || sbol->codigo == CMENOS ||
            sbol->codigo == CIDENT ||
            sbol->codigo == CPAR_ABR || sbol->codigo == CNEG ||
            sbol->codigo == CCONS_ENT || sbol->codigo == CCONS_FLO ||
            sbol->codigo == CCONS_CAR || sbol->codigo == CCONS_STR)

        expresion(une(folset, cons(CPYCOMA, NADA)));

    if (sbol->codigo == CPYCOMA) scanner();
    else error_handler(22);
    test(folset, cons(NADA, NADA), 66);
    sentencia = 0;
}

void proposicion_compuesta(set folset) {
    int finBloqueVars;

    test(firsts[PC], une(une(une(firsts[LD], firsts[LP]), folset), cons(CLLA_CIE, NADA)), 60);

    if (sbol->codigo == CLLA_ABR) scanner();
    else error_handler(23);

    if (!isdeffuncion)
        pushTB();
    else
        isdeffuncion = 0;

    appendMAC(ENBL, iToStr(get_nivel()));

    if (sbol->codigo == CVOID || sbol->codigo == CCHAR ||
            sbol->codigo == CINT || sbol->codigo == CFLOAT)

        lista_declaraciones(une(folset, une(firsts[LP], cons(CLLA_CIE, NADA))));

    finBloqueVars = newLineMAC;
    if (sbol->codigo == CLLA_ABR || sbol->codigo == CMAS ||
            sbol->codigo == CMENOS || sbol->codigo == CIDENT ||
            sbol->codigo == CPAR_ABR || sbol->codigo == CNEG ||
            sbol->codigo == CCONS_ENT || sbol->codigo == CCONS_FLO ||
            sbol->codigo == CCONS_CAR || sbol->codigo == CCONS_STR ||
            sbol->codigo == CIF || sbol->codigo == CWHILE ||
            sbol->codigo == CIN || sbol->codigo == COUT ||
            sbol->codigo == CPYCOMA || sbol->codigo == CRETURN) {

        lista_proposiciones(une(folset, cons(CLLA_CIE, NADA)));
    }

    if (sbol->codigo == CLLA_CIE) {
        if (en_tabla_funcion != NIL && (ts[en_tabla_funcion].ets->ptr_tipo != en_tabla("void")) && (!isReturn))
            error_handler(37);

        scanner();
    } else error_handler(24);

    appendMAC(FINB, iToStr(get_nivel()));
    pop_nivel();

    test(folset, cons(NADA, NADA), 61);
}

void proposicion_seleccion(set folset) {
    struct typeAux TipoEx;
    int lineaBIFF, lineaBIFS, d1;
    if (sbol->codigo == CIF) scanner();
    else error_handler(27);
    if (sbol->codigo == CPAR_ABR) scanner();
    else error_handler(19);
    TipoEx = expresion(une(une(folset, firsts[PRO]), cons(CPAR_CIE | CELSE, NADA)));
    if (sbol->codigo == CPAR_CIE) scanner();
    else error_handler(20);
    lineaBIFF = newLineMAC;
    proposicion(une(une(cons(CELSE, NADA), folset), firsts[PRO]));
    d1 = calcularDespl(lineaBIFF, newLineMAC);
    if (sbol->codigo == CELSE) {
        lineaBIFS = newLineMAC;
        scanner();
        proposicion(folset);
        d1 = calcularDespl(lineaBIFS, newLineMAC);

        appendKMAC(BIFS, iToStr(d1), lineaBIFS);
        d1 = calcularDespl(lineaBIFF, lineaBIFS + 1);

    }

    appendKMAC(BIFF, concatString(iToStr(getTipo(TipoEx.tipo)), iToStr(d1)), lineaBIFF);
}

void proposicion_iteracion(set folset) {
    if (sbol->codigo == CWHILE) scanner();
    else error_handler(26);

    if (sbol->codigo == CPAR_ABR) scanner();
    else error_handler(19);

    expresion(une(une(folset, firsts[PRO]), cons(CPAR_CIE, NADA)));

    if (sbol->codigo == CPAR_CIE) scanner();
    else error_handler(20);

    proposicion(folset);

}

void proposicion_e_s(set folset) {

    struct typeAux TipoExp;
    char t;

    isINOUT = 1;

    switch (sbol->codigo) {
        case CIN:
        {
            scanner();
            if (sbol->codigo == CSHR) scanner();
            else error_handler(28);
            TipoExp = variable(une(une(folset, cons(CSHR | CPYCOMA, NADA)), firsts[VAR]));

            clearLMAC();

            t = getTipo(TipoExp.tipo);

            appendMAC(LEER, iToStr(getTipo(TipoExp.tipo)));
            appendMAC(ALM, concatString(concatString(iToStr(TipoExp.nivel), iToStr(TipoExp.despl)), iToStr(t)));
            appendMAC(POP, iToStr(t));



            while (sbol->codigo == CSHR || in(sbol->codigo, firsts[VAR])) {
                if (in(sbol->codigo, firsts[VAR])) error_handler(76);
                else scanner();

                TipoExp = variable(une(une(folset, cons(CSHR | CPYCOMA, NADA)), firsts[VAR]));

                clearLMAC();

                t = getTipo(TipoExp.tipo);

                appendMAC(LEER, iToStr(getTipo(TipoExp.tipo)));
                appendMAC(ALM, concatString(concatString(iToStr(TipoExp.nivel), iToStr(TipoExp.despl)), iToStr(t)));
                appendMAC(POP, iToStr(t));
            }

            if (sbol->codigo == CPYCOMA) scanner();
            else error_handler(22);
            break;
        }
        case COUT:
        {
            scanner();
            if (sbol->codigo == CSHL) scanner();
            else error_handler(29);


            TipoExp = expresion(une(une(folset, cons(CSHL | CPYCOMA, NADA)), firsts[E]));
            if (TipoExp.typeExpresionresion == Const_iToStr)
                appendMAC(IMPCS, "");
            else
                appendMAC(IMPR, iToStr(getTipo(TipoExp.tipo)));

            while (sbol->codigo == CSHL || in(sbol->codigo, firsts[E])) {
                if (in(sbol->codigo, firsts[E])) {
                    error_handler(77);
                } else {
                    scanner();
                }
                TipoExp = expresion(une(une(folset, cons(CSHL | CPYCOMA, NADA)), firsts[E]));
                if (TipoExp.typeExpresionresion == Const_iToStr)
                    appendMAC(IMPCS, "");
                else
                    appendMAC(IMPR, iToStr(getTipo(TipoExp.tipo)));

            }
            if (sbol->codigo == CPYCOMA) scanner();
            else error_handler(22);
            break;
        }
        default: error_handler(30);
    }
    test(folset, cons(NADA, NADA), 64);
    isINOUT = 0;
}

void proposicion_retorno(set folset) {
    scanner();
    expresion(une(folset, cons(CPYCOMA, NADA)));
    if (sbol->codigo == CPYCOMA) scanner();
    else error_handler(22);
    isReturn = 1;
    test(folset, cons(NADA, NADA), 65);
}

struct typeAux expresion(set folset) {  
    struct typeAux Tipo_Retorno,TipoE;
    char tvar,t;
    int nLineaCast;
    long int op;

    control++;

    Tipo_Retorno=   expresion_simple(une(une(folset,firsts[E]),cons(CASIGNAC, CDISTINTO|CIGUAL|CMENOR|CMEIG|CMAYOR|CMAIG)));
    nLineaCast= newLineMAC;
    
    TipoE.tipo= en_tabla("char");

    if (in(sbol->codigo, firsts[E])){
        error_handler(78);
        TipoE= expresion(folset);
    }else
        switch (sbol->codigo) {

            case CASIGNAC:
                            scanner();
                            if (Tipo_Retorno.typeExpresionresion != unaVariable)
                                error_handler(84);

                            clearLMAC(); 

                            TipoE= expresion(folset);

                            if (TipoE.tipo > Tipo_Retorno.tipo)
                                error_handler(93);

                            Tipo_Retorno.valor= TipoE.valor;

                            tvar= getTipo(Tipo_Retorno.tipo);
                            t= getTipo(TipoE.tipo);

                            if (t != tvar)
                                appendMAC(CAST,concatString( iToStr(t), iToStr(tvar)));

                            appendMAC(ALM, concatString(concatString(iToStr(Tipo_Retorno.nivel),  iToStr(Tipo_Retorno.despl)), iToStr(tvar)));
			    //
		            appendMAC(POP, iToStr(tvar));
                            appendMAC(CRVL, concatString(concatString(iToStr(Tipo_Retorno.nivel),  iToStr(Tipo_Retorno.despl)), iToStr(tvar)));  
			    //	
                            if (sentencia && control == 0) 
                                appendMAC(POP, iToStr(tvar)); 

                            break;
            case CDISTINTO:
            case CIGUAL:
            case CMENOR:
            case CMEIG:
            case CMAYOR:
            case CMAIG:
                            op= sbol->codigo;

                            scanner();
                            TipoE= expresion(folset);

                            t= getTipo(Tipo_Retorno.tipo);
                            tvar= getTipo(TipoE.tipo);


                            if (tvar < t)  
                                appendMAC(CAST, concatString(iToStr(tvar), iToStr(t)));
                            else   
                                if (tvar > t){
                                    appendKMAC(CAST, concatString(iToStr(t), iToStr(tvar)), nLineaCast);
                                    t= tvar;
                                }

                            switch(op){
                                case CDISTINTO:
                                    appendMAC(CMNI, iToStr(t));
                                    break;
                                case CIGUAL:
                                    appendMAC(CMIG, iToStr(t));
                                    break;
                                case CMENOR:
                                    appendMAC(CMME, iToStr(t));
                                    //appendMAC(CMMA, iToStr(t));
                                    break;
                                case CMEIG:
                                    appendMAC(CMEI, iToStr(t));
                                    break;
                                case CMAYOR:
                                    appendMAC(CMMA, iToStr(t));
                                    //appendMAC(CMME, iToStr(t));
                                    break;
                                case CMAIG:
                                    appendMAC(CMAI, iToStr(t));
                            }
                            break;
        };

    Tipo_Retorno.tipo= Cohersion(Tipo_Retorno.tipo,TipoE.tipo);
    control--;
    
    return Tipo_Retorno;
}

struct typeAux expresion_simple(set folset) {
    struct typeAux TipoT, Tipo_Retorno;
   int masMenos= 0;
    long int op= CMAS;
    char t, tvar;
    int nLineaCast;
    
      test(firsts[ES],une(une(firsts[T],cons(NADA,COR)),folset),67);

    if (sbol->codigo == CMAS || sbol->codigo == CMENOS){
        op= sbol->codigo;
        scanner();
        masMenos= 1;
    }

    Tipo_Retorno= termino(une(une(folset,cons(NADA,CMAS|CMENOS|COR)),firsts[T]));
    nLineaCast= newLineMAC;


    if (op == CMENOS){
        Tipo_Retorno.valor = -Tipo_Retorno.valor;
        appendMAC(INV, iToStr(getTipo(Tipo_Retorno.tipo)));
    }
    
    if (Tipo_Retorno.typeExpresionresion == unaVariable && masMenos)
        Tipo_Retorno.typeExpresionresion= variables;

    while (sbol->codigo == CMAS || sbol->codigo == CMENOS || sbol->codigo == COR || in(sbol->codigo, firsts[T])){
        op= sbol->codigo;

        if (in(sbol->codigo, firsts[T])) error_handler(78);
        else scanner();
        TipoT= termino(une(une(folset,cons(NADA,CMAS|CMENOS|COR)),firsts[T]));
        
        t= getTipo(Tipo_Retorno.tipo);
        tvar= getTipo(TipoT.tipo);


        if (tvar < t)
            appendMAC(CAST, concatString(iToStr(tvar), iToStr(t)));
        else    
            if (tvar > t){  
                appendKMAC(CAST, concatString(iToStr(t), iToStr(tvar)), nLineaCast);
                t= tvar;
            }

        
        switch(op){
            case CMAS:
                appendMAC(SUM, iToStr(t));
                break;
            case CMENOS:
                appendMAC(SUB, iToStr(t));
                break;
            case COR:
                appendMAC(OR, iToStr(t));
        }


        Tipo_Retorno.tipo= Cohersion(Tipo_Retorno.tipo, TipoT.tipo);
        Tipo_Retorno.typeExpresionresion= (Tipo_Retorno.typeExpresionresion == unaVariable ||
                                     (TipoT.typeExpresionresion != Tipo_Retorno.typeExpresionresion))?
                                     vars_consts : TipoT.typeExpresionresion;

        if (Tipo_Retorno.typeExpresionresion == Constant && (Tipo_Retorno.tipo == en_tabla("int") || Tipo_Retorno.tipo == en_tabla("char"))){
            switch(op){
                case CMAS:
                    Tipo_Retorno.valor+= TipoT.valor;
                    break;
                case CMENOS:
                    Tipo_Retorno.valor-= TipoT.valor;
                    break;
                case COR:
                    Tipo_Retorno.valor= Tipo_Retorno.valor || TipoT.valor;
            }
        }
        nLineaCast= newLineMAC;
    }

    return Tipo_Retorno;
}

struct typeAux termino(set folset) { 
    long int op;
    struct typeAux Tipo_Retorno, TipoF;
    char t, tvar;
    int nLineaCast;

    Tipo_Retorno= factor(une(une(folset,cons(NADA,CMULT|CDIV|CAND)),firsts[F]));
     nLineaCast= newLineMAC;

    if (Tipo_Retorno.typeExpresionresion == variables)
        Tipo_Retorno.typeExpresionresion= unaVariable;	 

  while ((sbol->codigo == CMULT || sbol->codigo == CDIV || sbol->codigo == CAND)|| in(sbol->codigo,firsts[F]))
  { 
	op= sbol->codigo;
	if(in(sbol->codigo,firsts[F])){
              error_handler(78);	
	}else{
	    scanner();
	}
	   TipoF= factor(une(une(folset,cons(NADA,CMULT|CDIV|CAND)),firsts[F]));

        t= getTipo(Tipo_Retorno.tipo);
        tvar= getTipo(TipoF.tipo);

        if (tvar < t)  
            appendMAC(CAST, concatString(iToStr(tvar), iToStr(t)));
        else  
            if (tvar > t){
                appendKMAC(CAST, concatString(iToStr(t), iToStr(tvar)), nLineaCast);
                t= tvar;
            }



        switch(op){
            case CMULT:
                appendMAC(MUL, iToStr(t));
                break;
            case CDIV:
                appendMAC(DIV, iToStr(t));
                break;
            case CAND:
                appendMAC(AND, iToStr(t));
        }

        Tipo_Retorno.tipo= Cohersion(Tipo_Retorno.tipo, TipoF.tipo);
        Tipo_Retorno.typeExpresionresion= (TipoF.typeExpresionresion != Tipo_Retorno.typeExpresionresion)? vars_consts : TipoF.typeExpresionresion;

        if (Tipo_Retorno.typeExpresionresion == Constant && (Tipo_Retorno.tipo == en_tabla("int") || Tipo_Retorno.tipo == en_tabla("char"))){
            switch(op){
                case CMULT: Tipo_Retorno.valor*= TipoF.valor; break;
                case CDIV: Tipo_Retorno.valor= (int)(Tipo_Retorno.valor / TipoF.valor); break;
                case CAND: Tipo_Retorno.valor= Tipo_Retorno.valor && TipoF.valor;
            }
        }
        nLineaCast= newLineMAC;
    }

    return Tipo_Retorno;
 
}

struct typeAux factor(set folset) {
    char lexema[TAM_LEXEMA], t;
    struct typeAux Tipo_Retorno;
    int i,j;
    char* s1;	

    test(firsts[F], folset, 68);
    
    switch (sbol->codigo){
        case CIDENT:
                        if (Clase_Ident(sbol->lexema) == NIL){	

                            strcpy(lexema, sbol->lexema);

                            scanner();

                            error_handler(33);

                            if (sbol->codigo == CPAR_ABR){

                                strcpy(inf_id->nbre, lexema);
                                inf_id->clase = CLASFUNC;
                                inf_id->ptr_tipo = en_tabla("TIPOERROR");

                                scanner();

                                if (sbol->codigo == CMAS      || sbol->codigo == CMENOS    ||
                                    sbol->codigo == CIDENT    || sbol->codigo == CPAR_ABR  ||
                                    sbol->codigo == CNEG      || sbol->codigo == CCONS_ENT ||
                                    sbol->codigo == CCONS_FLO || sbol->codigo == CCONS_CAR ||
                                    sbol->codigo == CCONS_STR)
                                                lista_expresiones(une(folset, cons(CPAR_CIE, NADA)));

                                if (sbol->codigo == CPAR_CIE) scanner();
                                else error_handler(20);

                            }else{
                                strcpy(inf_id->nbre, lexema);
                                inf_id->clase = CLASVAR;
                                inf_id->ptr_tipo = en_tabla("TIPOERROR");


                                if (sbol->codigo == CCOR_ABR){	

                                        inf_id->desc.part_var.arr.ptero_tipo_base= inf_id->ptr_tipo;
                                        inf_id->ptr_tipo = en_tabla("TIPOARREGLO");

                                        scanner();
                                        expresion(une(folset, cons(CCOR_CIE, NADA)));

                                        if (sbol->codigo == CCOR_CIE) scanner();
                                        else error_handler(21);
                                }

                            }
                            insertarTS();

                        }else
                            if (Clase_Ident(sbol->lexema) == CLASFUNC)
                                Tipo_Retorno= llamada_funcion(folset);
                            else
                                Tipo_Retorno= variable(folset);

                        break;
        case CCONS_ENT:
        case CCONS_FLO:
        case CCONS_CAR:                         
                        Tipo_Retorno= constante(folset);
                        t= getTipo(Tipo_Retorno.tipo);
                        if (t == 2)
                            appendMAC(CRCT, concatString(iToStr(t),  Tipo_Retorno.sValor));
                        else
                            appendMAC(CRCT, concatString(iToStr(t), Tipo_Retorno.sValor));
                        break;
        case CCONS_STR: 
                        if (!isINOUT)
                            error_handler(86);

                        appendMAC(CRCTS, iToStr(dameCS())); 

                        strmplN(sbol->lexema);
                        strmplT(sbol->lexema);
                         
                        pushCS(sbol->lexema);

                        Tipo_Retorno.typeExpresionresion= Const_iToStr;
                        strcpy(Tipo_Retorno.sValor, sbol->lexema);
                        scanner();
                        break;
        case CPAR_ABR:
                        scanner();
                        Tipo_Retorno= expresion(une(folset, cons(CPAR_CIE, NADA)));

                        if (sbol->codigo == CPAR_CIE) scanner();
                        else error_handler(20);

                        break;
        case CNEG:
                        scanner();
                        Tipo_Retorno= expresion(folset);
                        t= getTipo(Tipo_Retorno.tipo);
                        
                        appendMAC(NEG, iToStr(t));
                        break;
        default: 
                        error_handler(31);
                        Tipo_Retorno.tipo= en_tabla("TIPOERROR");
    }

    test(folset, cons(NADA,NADA), 69);

    return Tipo_Retorno;
}


struct typeAux variable(set folset){   
char lexema[TAM_LEXEMA], t;
int Iden_No_Declarado= 0;
struct typeAux TipoE, Tipo_Retorno;


    test(firsts[VAR], folset, 70);

    if (sbol->codigo == CIDENT){

        strcpy(lexema, sbol->lexema);

        Iden_No_Declarado= (Clase_Ident(sbol->lexema) == NIL)? 1 : 0;

        scanner();

        if (Iden_No_Declarado){	

            error_handler(33);

            if (sbol->codigo == CPAR_ABR){ 

                strcpy(inf_id->nbre, lexema);
                inf_id->clase = CLASFUNC;
                inf_id->ptr_tipo = en_tabla("TIPOERROR");

                scanner();

                if (sbol->codigo == CMAS 	  || sbol->codigo == CMENOS    ||
                        sbol->codigo == CIDENT    || sbol->codigo == CPAR_ABR  ||
                        sbol->codigo == CNEG      || sbol->codigo == CCONS_ENT ||
                        sbol->codigo == CCONS_FLO || sbol->codigo == CCONS_CAR ||
                        sbol->codigo == CCONS_STR)
                                lista_expresiones(une(folset, cons(CPAR_CIE, NADA)));

                if (sbol->codigo == CPAR_CIE) scanner();
                else error_handler(20);

            }else{
                strcpy(inf_id->nbre, lexema);
                inf_id->clase = CLASVAR;
                inf_id->ptr_tipo = en_tabla("TIPOERROR");


                if (sbol->codigo == CCOR_ABR){	

                        inf_id->desc.part_var.arr.ptero_tipo_base= inf_id->ptr_tipo;
                        inf_id->ptr_tipo = en_tabla("TIPOARREGLO");
                        inf_id->desc.part_var.arr.cant_elem= 99999; //inicializo con un nro grande

                        scanner();
                        expresion(une(folset, cons(CCOR_CIE, NADA)));

                        if (sbol->codigo == CCOR_CIE) scanner();
                        else error_handler(21);
                }

            }

            insertarTS();

        }else{  
            if (sbol->codigo == CCOR_ABR){
                scanner();
                TipoE= expresion(une(folset, cons(CCOR_CIE, NADA)));

                if (TipoE.typeExpresionresion == Constant){
                    if (TipoE.tipo == en_tabla("float") || TipoE.valor < 0)
                        error_handler(85);
                    else
                    if (TipoE.valor >= ts[en_tabla(lexema)].ets->desc.part_var.arr.cant_elem)
                        error_handler(85);
                }
                
                if (sbol->codigo == CCOR_CIE) scanner();
                else error_handler(21);


                if (Tipo_Ident(lexema) != en_tabla("TIPOARREGLO"))
                    error_handler(32);
                else{
                    Tipo_Retorno.tipo= ts[en_tabla(lexema)].ets->desc.part_var.arr.ptero_tipo_base;
		    //printf("retorno de base arreglo: %d\n",Tipo_Retorno.tipo);
                    //printf("lexema arreglo: %s\n",lexema); 	
                  }
            }else  
                if (Tipo_Ident(lexema) == en_tabla("TIPOARREGLO")&&!isLlamadafuncion)	
                        error_handler(43);
                else{                    

                    Tipo_Retorno.tipo= Tipo_Ident(lexema);
         
                    t= getTipo(Tipo_Retorno.tipo);
			
                    appendMAC(CRVL, concatString(concatString(iToStr(ts[en_tabla(lexema)].ets->desc.nivel), iToStr(ts[en_tabla(lexema)].ets->desc.despl)), iToStr(t)));

                    if (Tipo_Retorno.tipo == en_tabla("TIPOARREGLO"))
                        Tipo_Retorno.tipo_base= ts[en_tabla(lexema)].ets->desc.part_var.arr.ptero_tipo_base;
                }
        }

        Tipo_Retorno.typeExpresionresion= variables;
        Tipo_Retorno.despl= ts[en_tabla(lexema)].ets->desc.despl;
        Tipo_Retorno.nivel= ts[en_tabla(lexema)].ets->desc.nivel;
    }else
        error_handler(16);

    test(folset, cons(NADA,NADA), 71);

    return Tipo_Retorno;
}


struct typeAux llamada_funcion(set folset) {
    char lexema[TAM_LEXEMA];
    struct typeAux Tipo_Retorno;
    isLlamadafuncion= 1;
    
    en_tabla_funcion_Llama= en_tabla(sbol->lexema);
    
    if (sbol->codigo == CIDENT){
        strcpy(lexema, sbol->lexema);
        scanner();
    }else error_handler(16);

    if (sbol->codigo == CPAR_ABR) scanner();
    else error_handler(19);

    cantParametros= 0; 

    if (sbol->codigo == CMAS 	  || sbol->codigo == CMENOS    ||
        sbol->codigo == CIDENT    || sbol->codigo == CPAR_ABR  ||
        sbol->codigo == CNEG      || sbol->codigo == CCONS_ENT ||
        sbol->codigo == CCONS_FLO || sbol->codigo == CCONS_CAR ||
        sbol->codigo == CCONS_STR)
            lista_expresiones(une(folset, cons(CPAR_CIE, NADA)));

    if (cantParametros != ts[en_tabla(lexema)].ets->desc.part_var.sub.cant_par)
        error_handler(88);

    if (sbol->codigo == CPAR_CIE) scanner();
    else error_handler(20);

    isLlamadafuncion= 0;

    test(folset, cons(NADA,NADA), 72);

    Tipo_Retorno.tipo= Tipo_Ident(lexema);
    Tipo_Retorno.typeExpresionresion= funcion;

    return Tipo_Retorno;
}


void lista_expresiones(set folset){
    struct typeAux TipoE;
    cantParametros= 0;
    
    TipoE= expresion(une(une(folset,cons(CCOMA,NADA)),firsts[E])); 
    cantParametros++;

    chequeoParam(TipoE, cantParametros);

    while (sbol->codigo == CCOMA || in(sbol->codigo, firsts[E])){
        if (in(sbol->codigo, firsts[E])) error_handler(75);
        else scanner();

      TipoE= expresion(une(une(folset,cons(CCOMA,NADA)),firsts[E]));
        cantParametros++;

       chequeoParam(TipoE, cantParametros);
    }
}

struct typeAux constante(set folset){   
  struct typeAux Tipo_Retorno;

  Tipo_Retorno.typeExpresionresion= Constant;  

  test(firsts[CON],folset,73);	
  switch (sbol->codigo) {
            case CCONS_ENT:

                            Tipo_Retorno.valor= atoi(sbol->lexema);
                            strcpy(Tipo_Retorno.sValor, sbol->lexema);

                            cantConstantess++;
                            scanner();
                            Tipo_Retorno.tipo= en_tabla("int");
                            break;
            case CCONS_FLO:
                            Tipo_Retorno.valor= charToFloat(sbol->lexema);
                            strcpy(Tipo_Retorno.sValor, sbol->lexema);

                            cantConstantess++;
                            scanner();
                            Tipo_Retorno.tipo= en_tabla("float");
                            break;
            case CCONS_CAR:
                            Tipo_Retorno.valor= sbol->lexema[1];
                            strcpy(Tipo_Retorno.sValor, iToStr(Tipo_Retorno.valor));

                            cantConstantess++;
                            scanner();
                            Tipo_Retorno.tipo= en_tabla("char");
                            break;
  default: error_handler(38);

  }
  test(folset,cons(NADA,NADA),74);
  return Tipo_Retorno;	

}