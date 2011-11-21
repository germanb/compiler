#define EXTERNA extern

#include <stdio.h>
#include "error.h"
#include "var_globales.h"

char error =0;

void error_print (int ne) {
  error = 1;
  //printf("\t Error %d: *****************************************������������������\n", ne);	
  switch (ne) {
    /* errores de scanner */
  case 1:  printf("\t Error %d: Fin de comentario no encontrado\n", ne); break;
  case 2:  printf("\t Error %d: El String es demasiado largo\n", ne); break;
  case 3:  printf("\t Warning %d: falta comilla de cierre. la l�nea ser� consumida\n", ne); break;
  case 4:  printf("\t Warning %d: Identificador de mas de 8 caracteres, ser� truncado\n", ne); break;
  case 5:  printf("\t Error %d: Caracter invalido\n", ne); break;
  case 6:  printf("\t Error %d: El n�mero de argumentos no coincide. ucc programa.c \n", ne); break;
  case 7:  printf("\t Error %d: El archivo no existe\n ", ne); break;
  case 8:  printf("\t Error %d: Ocurri� un error \n", ne); break;
   /* errores de la tabla de simbolos*/
  case 9:  printf("\t Error %d: Identificador ya declarado\n", ne); break;
  case 10: printf("\t Error %d: Falta Memoria\n", ne); break;
  case 11: printf("\t Error %d: Tabla de S�mbolos vac�a\n", ne); break;
  case 12: printf("\t Error %d: Tabla de S�mbolos llena\n", ne); break;
  case 13: printf("\t Error %d: Tabla de Bloques llena\n", ne); break;
  case 14: printf("\t Error %d: Tabla de Bloques vac�a\n", ne); break;
  /* errores de parser*/
  case 15: printf("\t Error %d: Falta declarar la funcion main\n", ne); break;
  case 16: printf("\t Error %d: Falta identificador\n", ne); break;
  case 17: printf("\t Error %d: Tipo no definido \n", ne); break;
  case 18: printf("\t Error %d: En Especificar Declaraci�n\n", ne); break;
  case 19: printf("\t Error %d: Falta (\n", ne); break;
  case 20: printf("\t Error %d: Falta )\n", ne); break;
  case 21: printf("\t Error %d: Falta ]\n", ne); break;
  case 22: printf("\t Error %d: Falta ;\n", ne); break;
  case 23: printf("\t Error %d: Falta {\n", ne); break;
  case 24: printf("\t Error %d: Falta }\n", ne); break;
  case 25: printf("\t Error %d: Error en proposici�n\n", ne); break;
  case 26: printf("\t Error %d: Falta While\n", ne); break;
  case 27: printf("\t Error %d: Falta if\n", ne); break;
  case 28: printf("\t Error %d: Falta >>\n", ne); break;
  case 29: printf("\t Error %d: Falta <<\n", ne); break;
  case 30: printf("\t Error %d: Falta << o >>\n", ne); break;
  case 31: printf("\t Error %d: En factor\n", ne); break;
  case 32: printf("\t Error %d: La variable no es de tipo arreglo \n", ne); break;
  case 33: printf("\t Error %d: Identificador no declarado\n", ne); break;
  case 34: printf("\t Error %d: Se esperaba identificador de funci�n\n", ne); break;
  case 35: printf("\t Error %d: El tipo de la funcion main() debe ser void\n", ne); break;
  case 36: printf("\t Error %d: La funcion main() no lleva argumento\n", ne); break;
  case 37: printf("\t Error %d: Falta return\n", ne); break;
  case 38: printf("\t Error %d: Falta constante\n", ne); break;
  case 39: printf("\t Error %d: El identificador debe ser una variable o par�metro\n", ne); break;
  case 40: printf("\t Error %d: En una expresion, los arreglos deben ser accedidos por sus elementos\n", ne); break;


    /* errores de recuperacion de errores */
  case 50: printf("\t Error %d: Al inicio del programa. \n", ne); break;
  case 51: printf("\t Error %d: S�mbolo inesperado o falta especificador de tipo. \n", ne); break;
  case 52: printf("\t Error %d: S�mbolo inesperado despu�s de especificador de tipo. \n", ne); break;
  case 53: printf("\t Error %d: S�mbolo inesperado o falta s�mb. al comienzo de especif. de declaraci�n \n", ne); break;
  case 54: printf("\t Error %d: S�mbolo inesperado despu�s de especificador de declaraci�n \n", ne); break;
  case 55: printf("\t Error %d: S�mbolo inesperado despu�s de declarar un par�metro. \n", ne); break;
  case 56: printf("\t Error %d: S�mbolo inesperado despu�s de declarar un par�metro \n", ne); break;
  case 57: printf("\t Error %d: S�mbolo inesperado o falta s�mb. al comienzo de lista decl. init.\n", ne); break;
  case 58: printf("\t Error %d: S�mbolo inesperado al comienzo de declarador init. \n", ne); break;
  case 59: printf("\t Error %d: S�mbolo inesperado despu�s de declarador init. \n", ne); break;
  case 60: printf("\t Error %d: S�mbolo inesperado o falta s�mb. al comienzo de proposici�n compuesta. \n", ne); break;
  case 61: printf("\t Error %d: S�mbolo inesperado despu�s de proposici�n compuesta. \n", ne); break;
  case 62: printf("\t Error %d: S�mbolo inesperado despu�s de declaraci�n. \n", ne); break;
  case 63: printf("\t Error %d: S�mbolo inesperado o falta s�mb. al comienzo de proposici�n. \n", ne); break;
  case 64: printf("\t Error %d: S�mbolo inesperado despu�s de proposici�n entrada - salida. \n", ne); break;
  case 65: printf("\t Error %d: S�mbolo inesperado despu�s de proposici�n retorno. \n", ne); break;
  case 66: printf("\t Error %d: S�mbolo inesperado despu�s de proposici�n expresi�n. \n", ne); break;
  case 67: printf("\t Error %d: S�mbolo inesperado o falta s�mb. al comienzo de expresi�n simple. \n", ne); break;
  case 68: printf("\t Error %d: S�mbolo inesperado o falta s�mb. al comienzo de factor. \n", ne); break;
  case 69: printf("\t Error %d: S�mbolo inesperado despu�s de factor. \n", ne); break;
  case 70: printf("\t Error %d: S�mbolo inesperado o falta s�mb. al comienzo de variable. \n", ne); break;
  case 71: printf("\t Error %d: S�mbolo inesperado despu�s de variable. \n", ne); break;
  case 72: printf("\t Error %d: S�mbolo inesperado despu�s de llamada a funci�n. \n", ne); break;
  case 73: printf("\t Error %d: S�mbolo inesperado o falta s�mb. al comienzo de constante\n", ne); break;
  case 74: printf("\t Error %d: S�mbolo inesperado despues de constante,\n", ne); break;
  case 75: printf("\t Error %d: Falta , \n", ne); break;
  case 76: printf("\t Error %d: Falta >> \n", ne); break;
  case 77: printf("\t Error %d: Falta << \n", ne); break;
  case 78: printf("\t Error %d: Falta *, /, &&, +, -, ||, = u operador de relaci�n \n", ne); break;
  case 79: printf("\t Error %d: Falta = \n", ne); break;

  case 81: printf("\t Error %d: Un arreglo debe tener mas de un elemento \n", ne); break;
  case 82: printf("\t Error %d: Imposible asignar tipo void \n", ne); break;
  case 83: printf("\t Error %d: La cardinalidad del arreglo debe ser entera \n", ne); break;
  case 84: printf("\t Error %d: Se esperaba variable del lado izquierdo \n", ne); break;
  case 85: printf("\t Error %d: Indices invalidos \n", ne); break;
  case 86: printf("\t Error %d: Uso de String incorrecto \n", ne); break;
  case 87: printf("\t Error %d: Indice no Natural\n", ne); break;
  case 88: printf("\t Error %d: Error en la cantidad de parametros\n", ne); break;
  case 89: printf("\t Error %d: Imposible pasar un arreglo por direccion\n", ne); break;
  case 90: printf("\t Error %d: Los parametros no coinciden\n", ne); break;
  case 91: printf("\t Error %d: Mas de un identificador en parametro real\n", ne); break;
  case 92: printf("\t Error %d: Se esperaba variable\n", ne); break;
  case 93: printf("\t Error %d: Asignacion no valida.\n", ne);break;
  case 94: printf("\t Error %d: La cantidad de elementos no coincide con el tamanio del arreglo.\n", ne);break;
  case 95: printf("\t Error %d: Tipo incorrecto\n", ne);break;
  case 96: printf("\t Error %d: Asignacion invalida\n", ne);break;












 }
}


void error_handler(int ne) {
  int i;

  if (ne == COD_IMP_ERRORES) {
    printf("Linea %d - %s\n", nro_linea, linea);
    for (i=0; i < cant_errores_x_linea; i++) 
      error_print( errores_x_linea [i]);
    cant_errores_x_linea=0;
  }
  else {
    errores_x_linea [cant_errores_x_linea] = ne;
    cant_errores_x_linea++;
  }
}





/*


void f_error() {
   printf(" %d.- Ocurrio un error\n", linea);
}
*/
