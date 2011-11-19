%{
  #define EXTERNA
  
  #include <stdio.h>  
  #include <string.h>
  #include "codigos.h"
  #include "var_globales.h"
  #define M 25 
  #define N 11
  #define ident 1
  #define string 2
  #define entero 3
  #define simbolo 4
  #define real 5

  
 char cons1,cons2,str[100];
 int i=0, p, vez;
 

 char reservadas[N][6]={"char","int","float","void","while","if","else","cin","cout","return"};/*tabla 10*/

%}

cons_num {digito}+
cons_real {digito}+[.]{digito}+
palabra {identificador}
identificador {letra}({letra}|{digito})*
letra [a-zA-Z]
digito [0-9]


%%


\n {nro_linea++; /* Tambien sirve como separador*/
    error_handler(COD_IMP_ERRORES);
    liberar=linea;
    linea = (char *) malloc (2);
    strcpy(linea, "");
    free ( (void *) liberar);
    vez = 0;
   } 


\#  {char c;
 for (;(c=input()) != '#'  && c != EOF; ) if (c=='\n') nro_linea++; 
     if (c == EOF) {
       error_handler(1);
       error_handler(COD_IMP_ERRORES);
       exit(1);  
     } else {
       token1.codigo=SEGUIR;
       return 1;
     }  
    }


\"  {int i=0; char c;
     while ( i<TAM_LEXEMA-2 && (c=token1.lexema[i]=input()) != '"' ) { 
       if (c=='\n') {
	 nro_linea++; 
	 error_handler(COD_IMP_ERRORES);
	 liberar = linea;
	 linea = (char *) malloc (2);
	 strcpy(linea, "");
	 free ((void *)liberar);
       }
       i++;
     }
     token1.lexema[i]='\0';
     if (i >= TAM_LEXEMA-2) {
       error_handler(2);
       error_handler(COD_IMP_ERRORES);
       exit(1);
     }
     token1.codigo=CCONS_STR;
     vez = 0;
     return 1;
    }

{cons_num} {token1.codigo=CCONS_ENT;
            strcpy(token1.lexema,yytext);
            vez = 0;
            return 1;
           }

{cons_real} {
           token1.codigo=CCONS_FLO;
           strcpy(token1.lexema,yytext);
           vez = 0;
           return 1;
}


\'  {cons1=input();  /*caracter que sigue a la comilla simple*/
     cons2=input();  /*caracter que sigue al contenido de cons1*/
     if(strcmp(&cons2,"\'")!=0) {
       error_handler(3);
       cons2=input(); 
       while(strcmp(&cons2,"\n")!=0) cons2=input();
       nro_linea++;
       error_handler(COD_IMP_ERRORES);
       liberar = linea;
       linea = (char *) malloc (2);
       strcpy(linea, "");
       free ((void *)liberar); 
    }
     token1.codigo=CCONS_CAR;
     strcpy(token1.lexema,&cons1);
     vez = 0;
     return 1;
    } 

&& {token1.codigo=CAND;
     strcpy(token1.lexema, yytext);
     vez = 0;
     return 1;
    } 

\|\| {token1.codigo=COR;
     strcpy(token1.lexema,yytext);
     vez = 0;
     return 1;
    } 

\[  {token1.codigo=CCOR_ABR;
     strcpy(token1.lexema,yytext);
     vez = 0;
     return 1;
    } 

\]  {token1.codigo=CCOR_CIE;
     strcpy(token1.lexema,yytext);
     vez = 0;
     return 1;
    } 

\&  {token1.codigo=CAMPER;
     strcpy(token1.lexema,yytext);
     vez = 0;
     return 1;
    } 

\>\> {token1.codigo=CSHR;
      strcpy(token1.lexema,yytext); 
      vez = 0;
      return 1;
     } 


\<\< {token1.codigo=CSHL;
      strcpy(token1.lexema,yytext);
      vez = 0; 
      return 1;
     } 

\!=  {token1.codigo=CDISTINTO;
      strcpy(token1.lexema,yytext); 
      vez = 0;
      return 1;
     } 

\==  {token1.codigo=CIGUAL;
      strcpy(token1.lexema,yytext);
      vez = 0;
      return 1;
     } 

\<  {token1.codigo=CMENOR;
     strcpy(token1.lexema,yytext);
     vez = 0;
     return 1;
     } 

\<\=  {token1.codigo=CMEIG;
       strcpy(token1.lexema,yytext);  
       vez = 0;
       return 1;
       } 

\>\=  {token1.codigo=CMAIG;
       strcpy(token1.lexema,yytext); 
       vez = 0;
       return 1;
       } 

\>   {token1.codigo=CMAYOR;
     strcpy(token1.lexema,yytext);
     vez = 0;
     return 1;
     } 

\+   {token1.codigo=CMAS;
      strcpy(token1.lexema,yytext);  
      vez = 0;
      return 1;
     } 

\-    {token1.codigo=CMENOS;
      strcpy(token1.lexema,yytext); 
      vez = 0;
      return 1;
      }  

\/  {token1.codigo=CDIV;
      strcpy(token1.lexema,yytext); 
      vez = 0;
      return 1;
     } 

\*  {token1.codigo=CMULT; 
      strcpy(token1.lexema,yytext); 
      vez = 0;
      return 1;
     } 

\{  {token1.codigo=CLLA_ABR;
     strcpy(token1.lexema,yytext);
     vez = 0; 
     return 1;
    } 

\} {token1.codigo=CLLA_CIE;
     strcpy(token1.lexema,yytext);
     vez = 0; 
     return 1;
    } 

[(] {token1.codigo=CPAR_ABR;
     strcpy(token1.lexema,yytext); 
     vez = 0;
     return 1;
    } 

[)]  {token1.codigo=CPAR_CIE;
     strcpy(token1.lexema,yytext); 
     vez = 0;
     return 1;
    } 


\!  {token1.codigo=CNEG;
     strcpy(token1.lexema,yytext);  
     vez = 0;
     return 1;
     } 

\=  {token1.codigo=CASIGNAC;
      strcpy(token1.lexema,yytext); 
      vez = 0;
      return 1;
     } 

\;  {token1.codigo=CPYCOMA;
     strcpy(token1.lexema,yytext); 
     vez = 0;
     return 1;
    } 

\,  {token1.codigo=CCOMA;
     strcpy(token1.lexema,yytext); 
     vez = 0;
     return 1;
    }

{palabra} {i=0; 
           while ((i<N) && (strcmp(reservadas[i],yytext)!=0))
            i++;
           if (i<N) 
	     switch(i) {
	       case 0: token1.codigo=CCHAR;
		 strcpy(token1.lexema,yytext); 
		 break;
	       case 1: token1.codigo=CINT;
		 strcpy(token1.lexema,yytext); 
		 break;
	       case 2: token1.codigo=CFLOAT;
		 strcpy(token1.lexema,yytext); 
		 break;
	       case 3: token1.codigo=CVOID;
		 strcpy(token1.lexema,yytext); 
		 break;
	       case 4: token1.codigo=CWHILE;
		 strcpy(token1.lexema,yytext); 
		 break;
	       case 5: token1.codigo=CIF;
		 strcpy(token1.lexema,yytext); 
		 break;
	       case 6: token1.codigo=CELSE;
		 strcpy(token1.lexema,yytext); 
		 break;
	       case 7: token1.codigo=CIN;
		 strcpy(token1.lexema,yytext); 
		 break;
	       case 8: token1.codigo=COUT;
		 strcpy(token1.lexema,yytext); 
		 break;
	       case 9: token1.codigo=CRETURN;
		 strcpy(token1.lexema,yytext); 
		 break;

             }
	   else
	     {token1.codigo=CIDENT;
                 if (yyleng>8) error_handler(4);
                 strncpy(token1.lexema,yytext, 8);
                 token1.lexema[8]='\0';
             }
	   vez = 0;
	   return 1;
         }




[ ] {if (vez == 0) {
      strcat(linea, " ");
      vez=1;
     }  
    } /* No toma accion pero sirve como separador entre tokens*/

. {error_handler(5);
   vez = 0;
  }

%%

int yywrap(){
	return 1;
}


/*
int main( int argc,char *argv[]) {
  int i=1;
*/
  /* el alumno debera inicializar la variable yyin segun corresponda */
/*  nro_linea=0; 

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
  
  while (yylex()) {  
    if (token1.codigo != SEGUIR) {
      printf("%d.- (codigo, lexema) = [%d , %s]\n", i, token1.codigo, token1.lexema );
      i++;
    }
  }

}
*/
























