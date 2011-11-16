
/* ***************************************************************
       DEFINICIONES Y CONSTANTES DEL SISTEMA DE EJECUCION
****************************************************************** */



/* ================= DEFINICION DE CONSTANTES ==================== */

/* ---------------- TAMA�OS PARA LAS ESTRUCTURAS ----------------- */

# define TAM_PROG    5000
# define TAM_STACK  15000
//# define TAM_HEAP     127  // debido al rango permitido por el ptro. char
# define TAM_BLQ       30
# define TAM_CTES     500
# define TAM_DISP      15
    
/* ------------- CODIGOS PARA LAS INSTRUCCIONES MOPA ------------- */

/* --------------- instrucciones b�sicas ------------------------- */
# define CRCT   1     // cargar una constante
# define CRVL   2     // cargar el valor de una variable
# define sCRCT  "CRCT"
# define sCRVL  "CRVL"
/* ------------ instrucciones para las operaciones --------------- */
# define SUM    3     // suma de enteros
# define SUB    4     // resta de enteros
# define MUL    5     // multiplicaci�n de enteros
# define DIV    6     // divisi�n de enteros
# define INV    7     // cambio de signo de un entero
# define AND    8     // operador l�gico and
# define OR     9     // operador l�gico or
# define NEG    10    // operador l�gico not
# define POP    100   // elimina el valor en el tope del stack.
# define CAST   101   // conversion de tipo. 
# define CMMA   11    // operador relacional aritm�tico por mayor
# define CMME   12    // operador relacional aritm�tico por menor
# define CMIG   13    // operador relacional aritm�tico por igual
# define CMAI   14    // operador relacional aritm�tico por mayor o igual
# define CMEI   15    // operador relacional aritm�tico por menor o igual
# define CMNI   16    // operador relacional aritm�tico por no igual
# define sSUM   "SUM"
# define sSUB   "SUB"
# define sMUL   "MUL"
# define sDIV   "DIV"
# define sINV   "INV"
# define sAND   "AND"
# define sOR    "OR"
# define sNEG   "NEG"
# define sPOP   "POP"
# define sCAST  "CAST"
# define sCMMA  "CMMA"
# define sCMME  "CMME"
# define sCMIG  "CMIG"
# define sCMAI  "CMAI"
# define sCMEI  "CMEI"
# define sCMNI  "CMNI"
/* --------------- instrucciones b�sicas ------------------------- */
# define ALM    17    // almacenar un valor a una variable
# define sALM   "ALM"
/* -------------------- instrucciones para E / S ----------------- */
# define LEER   18    // lee un char, int o float
# define IMPR   19    // imprime un entero o char o float o constantes de los tipos anteriores
# define sLEER  "LEER"
# define sIMPR  "IMPR"

//# define ESLN   75    // baja de linea

/* ---------- instrucciones para control de secuencia ------------ */
# define BIFF   20    // bifurca por falso
# define BIFS   21    // bifurca siempre
# define sBIFF  "BIFF"
# define sBIFS  "BIFS"
/* --------------- instrucciones b�sicas ------------------------- */
# define INPP   22    // inicia el programa
# define PARAR  23    // termina el programa
# define ALOC   24    // asigna memoria para vbles y las inicializa
# define DMEM   25    // libera memoria
# define sINPP  "INPP"    // inicia el programa
# define sPARAR "PARAR"    // termina el programa
# define sALOC  "ALOC"    // asigna memoria para vbles y las inicializa
# define sDMEM  "DMEM"    // libera memoria
/* ------------ instrucciones para manipular subrutinas ---------- */
# define CRDI   26    // carga la direcci�n de una variable
# define CRVLI  27    // cargar valor indirecto
# define ALMI   28    // almacenar indirecto
# define ENPR   29    // guardar el viejo D[k]
# define CHPR   30    // invocar a un  procedimiento
# define RTPR   31    // retorno de un procedimiento
# define ENBL   102   // Entrada a Bloque
# define FINB   103   // Salida de Bloque
# define sCRDI  "CRDI"
# define sCRVLI "CRVLI"
# define sALMI  "ALMI"
# define sENPR  "ENPR"
# define sCHPR  "CHPR"
# define sRTPR  "RTPR"
# define sENBL  "ENBL"
# define sFINB  "FINB"
/* ------------ instrucciones para manipular arreglos ------------ */
//# define CRVV   32    // cargar valor de un elemento del vector
//# define ALMV   33    // almacenar valor de un elemento del vector
//# define CRDIV  34    // cargar direcci�n de un elemento del vector
//# define CRDIVI 76    // cargar direcci�n de un elemento del vector indirecto
//# define CRVVI  35    // cargar indirecto de un elemento del vector
//# define ALMVI  36    // almacenar indirecto de un elemento del vector
/* ------------ instrucciones para manipular strings ------------- */
# define IMPCS  49    // imprime una constante string
# define CRCTS  52    // carga la posicion de comienzo de una cte string
# define sIMPCS "IMPCS"
# define sCRCTS "CRCTS"

























































