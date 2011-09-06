#define EXTERNA extern

#include <stdio.h>
#include "error.h"
#include "var_globales.h"


void error_print (int ne) {
  
  switch (ne) {
    /* errores de scanner */
  case 1:  printf("\t Error %d: Fin de comentario no encontrado\n", ne); break;
  case 2:  printf("\t Error %d: El String es demasiado largo\n", ne); break;
  case 3:  printf("\t Warning %d: falta comilla de cierre. la línea será consumida\n", ne); break;
  case 4:  printf("\t Warning %d: Identificador de mas de 8 caracteres, será truncado\n", ne); break;
  case 5:  printf("\t Error %d: Caracter invalido\n", ne); break;
  case 6:  printf("\t Error %d: El número de argumentos no coincide. ucc programa.c \n", ne); break;
  case 7:  printf("\t Error %d: El archivo no existe\n ", ne); break;
  case 8:  printf("\t Error %d: Ocurrió un error \n", ne); break;
   /* errores de la tabla de simbolos*/
  case 9:  printf("\t Error %d: Identificador ya declarado\n", ne); break;
  case 10: printf("\t Error %d: Falta Memoria\n", ne); break;
  case 11: printf("\t Error %d: Tabla de Símbolos vacía\n", ne); break;
  case 12: printf("\t Error %d: Tabla de Símbolos llena\n", ne); break;
  case 13: printf("\t Error %d: Tabla de Bloques llena\n", ne); break;
  case 14: printf("\t Error %d: Tabla de Bloques vacía\n", ne); break;
  /* errores de parser*/
  case 15: printf("\t Error %d: Falta declarar la funcion main\n", ne); break;
  case 16: printf("\t Error %d: Falta identificador\n", ne); break;
  case 17: printf("\t Error %d: Tipo no definido \n", ne); break;
  case 18: printf("\t Error %d: En Especificar Declaración\n", ne); break;
  case 19: printf("\t Error %d: Falta (\n", ne); break;
  case 20: printf("\t Error %d: Falta )\n", ne); break;
  case 21: printf("\t Error %d: Falta ]\n", ne); break;
  case 22: printf("\t Error %d: Falta ;\n", ne); break;
  case 23: printf("\t Error %d: Falta {\n", ne); break;
  case 24: printf("\t Error %d: Falta }\n", ne); break;
  case 25: printf("\t Error %d: Error en proposición\n", ne); break;
  case 26: printf("\t Error %d: Falta While\n", ne); break;
  case 27: printf("\t Error %d: Falta if\n", ne); break;
  case 28: printf("\t Error %d: Falta >>\n", ne); break;
  case 29: printf("\t Error %d: Falta <<\n", ne); break;
  case 30: printf("\t Error %d: Falta << o >>\n", ne); break;
  case 31: printf("\t Error %d: En factor\n", ne); break;
  case 32: printf("\t Error %d: La variable no es de tipo arreglo \n", ne); break;
  case 33: printf("\t Error %d: Identificador no declarado\n", ne); break;
  case 34: printf("\t Error %d: Se esperaba identificador de función\n", ne); break;
  case 35: printf("\t Error %d: El tipo de la funcion main() debe ser void\n", ne); break;
  case 36: printf("\t Error %d: La funcion main() no lleva argumento\n", ne); break;
  case 37: printf("\t Error %d: Falta return\n", ne); break;
  case 38: printf("\t Error %d: Falta constante\n", ne); break;
  case 39: printf("\t Error %d: El identificador debe ser una variable o parámetro\n", ne); break;
  case 40: printf("\t Error %d: En una expresion, los arreglos deben ser accedidos por sus elementos\n", ne); break;

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
