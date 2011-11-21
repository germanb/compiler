
# include <string.h>
# include <stdio.h>
# include <stdlib.h>


# include "soporte_ejecucion.h"  // Definiciones y Constantes del Sistema de Ejecuci¢n


int tc = sizeof (char); //tamano del char
int te = sizeof (int); //tamano del integer
int tf = sizeof (float); //tamano del float

/* ********************* DEFINICION DE VARIABLES ********************* */
short noerror = 1;



/* ---------------- REGISTRO DE PROXIMA INSTRUCCION -------------- */

int rpi;

/* ---------------- ZONA PARA EL PROGRAMA MOPA ------------------- */

float P[TAM_PROG];
int lp = 0; 


/* ---------------- ZONA PARA LAS CONSTANTAS ------------------- */

char C[TAM_CTES];
int lc = 0; 

/* ---------------- ZONA PARA EL VECTOR DISPLAY ------------------- */

int D[TAM_DISP];

/* -------------- ZONA PARA EL STACK DE EJECUCION ---------------- */

char S[TAM_STACK];
int ls = 0; // tope del stack


int dameCS(){ return lc;}

int pushCS(char cadena[]){
    int i;

    for (i= 0; i <= strlen(cadena); i++)
        C[lc++]= cadena[i];
    return lc;
}

void addC(char car){
    C[lc++]= car;
}

char dameC(int i){
    return C[i];
}

void pushP(float *Cod){
    P[lp++]= *(Cod);

}



void interprete2() {

    int op1, op2, op3, op4, tamentero;

    rpi = 0;

    while (P[rpi] != PARAR) {

        if (ls >= TAM_STACK) {
            printf("\nError: Overflow del Stack de Ejecuci¢n\n");
            exit(1);
        }


        if (ls < TAM_STACK - tf) {

            switch ((int) P[rpi]) {

                case CRCT: // CRCT tipo cte
                    rpi++;
                    switch ((int) P[rpi]) {
                        case 0:
                            rpi++;
                            S[ls] = (char) P[rpi];
                            ls += tc;
                            break;
                        case 1:
                            rpi++;
                            *((int*) &S[ls]) = (int) P[rpi];
                            ls += te;
                            break;
                        case 2:
                            rpi++;
                            *((float*) &S[ls]) = (float) P[rpi];

                            //printf("%f \n", *((float*) &S[ls]));

                            ls += tf;
                            break;
                    }
                    rpi++;
                    break;


                case CRVL:
                { // CRVL nivel despl tipo
                    int nivel, despl, tipo, i;

                    rpi++;
                    nivel = (int) P[rpi++];
                    despl = (int) P[rpi++];

                    switch ((int) P[rpi++]) {
                        case 0:
                            tipo = tc;
                            break;
                        case 1:
                            tipo = te;
                            break;
                        case 2:
                            tipo = tf;
                            break;
                    }

                    //printf("CRVL: D[nivel] = %d => %f\n", D[nivel], (*(float *) &S[D[nivel] + despl]) );

                    for (i = 0; i < tipo; i++) {
                        if (ls >= TAM_STACK) {
                            printf("\nError: Overflow del Stack de Ejecuci¢n\n");
                            exit(1);
                        }
                        //S[ls] = S[ D[nivel] + (despl*tipo) + i ];
                        S[ls] = S[ D[nivel] + despl + i ];
                        ls++;
                    }

                   // printf("CRVLD : D[nivel] = %d => %f\n", D[nivel], (*(float *) &S[D[nivel] + despl]) );

                    break;
                }

                case SUM: // SUM tipo
                    rpi++;
                    switch ((int) P[rpi++]) {
                        case 0:
                            (*(int *) &S[ls - 2 * tc]) = (int) S[ls - 2 * tc] + (int) S[ls - tc];
                            //(* &S[ls - 2 * tc]) =  S[ls - 2 * tc] + S[ls - tc];
                            ls = (ls - 2 * tc) + te;
                            break;
                        case 1:
                            (*(int *) &S[ls - 2 * te]) += *(int *) &S[ls - te];
                            ls = (ls - te);
                            break;
                        case 2:
                            (*(float *) &S[ls - 2 * tf]) += *(float *) &S[ls - tf];
                            ls = (ls - tf);
                            break;
                    }
                    break;

                case SUB: // SUB tipo
                    rpi++;
                    switch ((int) P[rpi++]) {
                        case 0:
                            (*(int *) &S[ls - 2 * tc]) = (int) S[ls - 2 * tc] - (int) S[ls - tc];
                            ls = (ls - 2 * tc) + te;
                            break;
                        case 1:
                            (*(int *) &S[ls - 2 * te]) -= *(int *) &S[ls - te];
                            ls = (ls - te);
                            break;
                        case 2:
                            (*(float *) &S[ls - 2 * tf]) -= *(float *) &S[ls - tf];
                            ls = (ls - tf);
                            break;
                    }
                    break;

                case MUL: // MUL tipo
                    rpi++;
                    switch ((int) P[rpi++]) {
                        case 0:
                            (*(int *) &S[ls - 2 * tc]) = (int) S[ls - 2 * tc] * (int) S[ls - tc];
                            ls = (ls - 2 * tc) + te;
                            break;
                        case 1:
                            (*(int *) &S[ls - 2 * te]) *= *(int *) &S[ls - te];
                            ls = (ls - te);
                            break;
                        case 2:
                            (*(float *) &S[ls - 2 * tf]) *= *(float *) &S[ls - tf];
                            ls = (ls - tf);
                            break;
                    }
                    break;

                case DIV: // DIV tipo
                    rpi++;
                    switch ((int) P[rpi++]) {
                        case 0:
                            (*(int *) &S[ls - 2 * tc]) = (int) S[ls - 2 * tc] / (int) S[ls - tc];
                            ls = (ls - 2 * tc) + te;
                            break;
                        case 1:
                            (*(int *) &S[ls - 2 * te]) /= *(int *) &S[ls - te];
                            ls = (ls - te);
                            break;
                        case 2:
                            (*(float *) &S[ls - 2 * tf]) /= *(float *) &S[ls - tf];
                            ls = (ls - tf);
                            break;
                    }
                    break;

                case INV: // INV tipo
                    rpi++;
                    switch ((int) P[rpi++]) {
                        case 0:
                            (*(int *) &S[ls - tc]) = -(int) S[ls - tc];
                            ls = (ls - tc) + te;
                            break;
                        case 1:
                            (*(int *) &S[ls - te]) = - * (int *) &S[ls - te];
                            break;
                        case 2:
                            (*(float *) &S[ls - tf]) = - * (float *) &S[ls - tf];
                            break;
                    }
                    break;

                case AND:// AND  tipo
                    rpi++;
                    switch ((int) P[rpi++]) {
                        case 0:
                            (*(int *) &S[ls - 2 * tc]) = S[ls - 2 * tc] && S[ls - tc];
                            ls = (ls - 2 * tc) + te;
                            break;
                        case 1:
                            (*(int *) &S[ls - 2 * te]) = (*(int *) &S[ls - 2 * te])
                                    && *(int *) &S[ls - te];
                            ls = (ls - te);
                            break;
                        case 2:
                            (*(int *) &S[ls - 2 * tf]) = (*(float *) &S[ls - 2 * tf])
                                    && *(float *) &S[ls - tf];
                            ls = (ls - 2 * tf) + te;
                            break;
                    }
                    break;

                case OR:// OR  tipo
                    rpi++;
                    switch ((int) P[rpi++]) {
                        case 0:
                            (*(int *) &S[ls - 2 * tc]) = S[ls - 2 * tc] || S[ls - tc];
                            ls = (ls - 2 * tc) + te;
                            break;
                        case 1:
                            (*(int *) &S[ls - 2 * te]) = (*(int *) &S[ls - 2 * te])
                                    || *(int *) &S[ls - te];
                            ls = (ls - te);
                            break;
                        case 2:
                            (*(int *) &S[ls - 2 * tf]) = (*(float *) &S[ls - 2 * tf])
                                    || *(float *) &S[ls - tf];
                            ls = (ls - 2 * tf) + te;
                            break;
                    }
                    break;

                case NEG: //NEG  tipo
                    rpi++;
                    switch ((int) P[rpi++]) {
                        case 0:
                            (*(int *) &S[ls - tc]) = !(int) S[ls - tc];
                            ls = (ls - tc) + te;
                            break;
                        case 1:
                            (*(int *) &S[ls - te]) = ! * (int *) &S[ls - te];
                            break;
                        case 2:
                            (*(int *) &S[ls - tf]) = ! * (float *) &S[ls - tf];
                            ls = (ls - tf) + te;
                            break;
                    }
                    break;

                case CMMA: // CMMA tipo
                    rpi++;
                    switch ((int) P[rpi++]) {
                        case 0:
                            if ((int) S[ls - 2 * tc] > (int) S[ls - tc])
                                (*(int *) &S[ls - 2 * tc]) = 1;
                            else
                                (*(int *) &S[ls - 2 * tc]) = 0;
                            ls = (ls - 2 * tc) + te;
                            break;
                        case 1:
                            if ((*(int *) &S[ls - 2 * te]) > * (int *) &S[ls - te])
                                (*(int *) &S[ls - 2 * te]) = 1;
                            else
                                (*(int *) &S[ls - 2 * te]) = 0;
                            ls = (ls - te);
                            break;
                        case 2:
                            if ((*(float *) &S[ls - 2 * tf]) > * (float *) &S[ls - tf])
                                (*(int *) &S[ls - 2 * tf]) = 1;
                            else
                                (*(int *) &S[ls - 2 * tf]) = 0;
                            ls = (ls - 2 * tf) + te;
                            break;
                    }
                    break;

                case CMME: // CMME tipo
                    rpi++;
                    switch ((int) P[rpi++]) {
                        case 0:
                            if ((int) S[ls - 2 * tc] < (int) S[ls - tc])
                                (*(int *) &S[ls - 2 * tc]) = 1;
                            else
                                (*(int *) &S[ls - 2 * tc]) = 0;
                            ls = (ls - 2 * tc) + te;
                            break;
                        case 1:
                            if ((*(int *) &S[ls - 2 * te]) < *(int *) &S[ls - te])
                                (*(int *) &S[ls - 2 * te]) = 1;
                            else
                                (*(int *) &S[ls - 2 * te]) = 0;
                            ls = (ls - te);
                            break;
                        case 2:
                            if ((*(float *) &S[ls - 2 * tf]) < *(float *) &S[ls - tf])
                                (*(int *) &S[ls - 2 * tf]) = 1;
                            else
                                (*(int *) &S[ls - 2 * tf]) = 0;
                            ls = (ls - 2 * tf) + te;
                            break;
                    }
                    break;

                case CMIG: // CMIG tipo
                    rpi++;
                    switch ((int) P[rpi++]) {
                        case 0:
                            if ((int) S[ls - 2 * tc] == (int) S[ls - tc])
                                (*(int *) &S[ls - 2 * tc]) = 1;
                            else
                                (*(int *) &S[ls - 2 * tc]) = 0;
                            ls = (ls - 2 * tc) + te;
                            break;
                        case 1:
                            if ((*(int *) &S[ls - 2 * te]) == *(int *) &S[ls - te])
                                (*(int *) &S[ls - 2 * te]) = 1;
                            else
                                (*(int *) &S[ls - 2 * te]) = 0;
                            ls = (ls - te);
                            break;
                        case 2:
                            if ((*(float *) &S[ls - 2 * tf]) == *(float *) &S[ls - tf])
                                (*(int *) &S[ls - 2 * tf]) = 1;
                            else
                                (*(int *) &S[ls - 2 * tf]) = 0;
                            ls = (ls - 2 * tf) + te;
                            break;
                    }
                    break;

                case CMAI: // CMAI tipo
                    rpi++;
                    switch ((int) P[rpi++]) {
                        case 0:
                            if ((int) S[ls - 2 * tc] >= (int) S[ls - tc])
                                (*(int *) &S[ls - 2 * tc]) = 1;
                            else
                                (*(int *) &S[ls - 2 * tc]) = 0;
                            ls = (ls - 2 * tc) + te;
                            break;
                        case 1:
                            if ((*(int *) &S[ls - 2 * te]) >= *(int *) &S[ls - te])
                                (*(int *) &S[ls - 2 * te]) = 1;
                            else
                                (*(int *) &S[ls - 2 * te]) = 0;
                            ls = (ls - te);
                            break;
                        case 2:
                            if ((*(float *) &S[ls - 2 * tf]) >= *(float *) &S[ls - tf])
                                (*(int *) &S[ls - 2 * tf]) = 1;
                            else
                                (*(int *) &S[ls - 2 * tf]) = 0;
                            ls = (ls - 2 * tf) + te;
                            break;
                    }
                    break;

                case CMEI: // CMEI tipo
                    rpi++;
                    switch ((int) P[rpi++]) {
                        case 0:
                            if ((int) S[ls - 2 * tc] <= (int) S[ls - tc])
                                (*(int *) &S[ls - 2 * tc]) = 1;
                            else
                                (*(int *) &S[ls - 2 * tc]) = 0;
                            ls = (ls - 2 * tc) + te;
                            break;
                        case 1:
                            if ((*(int *) &S[ls - 2 * te]) <= *(int *) &S[ls - te])
                                (*(int *) &S[ls - 2 * te]) = 1;
                            else
                                (*(int *) &S[ls - 2 * te]) = 0;
                            ls = (ls - te);
                            break;
                        case 2:
                            if ((*(float *) &S[ls - 2 * tf]) <= *(float *) &S[ls - tf])
                                (*(int *) &S[ls - 2 * tf]) = 1;
                            else
                                (*(int *) &S[ls - 2 * tf]) = 0;
                            ls = (ls - 2 * tf) + te;
                            break;
                    }
                    break;

                case CMNI: // CMNI tipo
                    rpi++;
                    switch ((int) P[rpi++]) {
                        case 0:
                            if ((int) S[ls - 2 * tc] != (int) S[ls - tc])
                                (*(int *) &S[ls - 2 * tc]) = 1;
                            else
                                (*(int *) &S[ls - 2 * tc]) = 0;
                            ls = (ls - 2 * tc) + te;
                            break;
                        case 1:
                            if ((*(int *) &S[ls - 2 * te]) != *(int *) &S[ls - te])
                                (*(int *) &S[ls - 2 * te]) = 1;
                            else
                                (*(int *) &S[ls - 2 * te]) = 0;
                            ls = (ls - te);
                            break;
                        case 2:
                            if ((*(float *) &S[ls - 2 * tf]) != *(float *) &S[ls - tf])
                                (*(int *) &S[ls - 2 * tf]) = 1;
                            else
                                (*(int *) &S[ls - 2 * tf]) = 0;
                            ls = (ls - 2 * tf) + te;
                            break;
                    }
                    break;


                case ALM:
                { // ALM nivel despl tipo
                    int nivel, despl, tipo, i;

                    rpi++;
                    nivel = (int) P[rpi++];
                    despl = (int) P[rpi++];

                    switch ((int) P[rpi++]) {
                        case 0:
                            tipo = tc;
                            break;
                        case 1:
                            tipo = te;
                            break;
                        case 2:
                            tipo = tf;
                            break;
                    }
                    



                    


                    ls -= tipo;
                    for (i = 0; i < tipo; i++) {
                        if (ls >= TAM_STACK) {
                            printf("\nError: Overflow del Stack de Ejecuci¢n\n");
                            exit(1);
                        }
                    
                        S[ D[nivel] + despl + i ] = S[ls];
                        ls++;
                    }

                    
                    break;
                }

                case ALOC: // ALOC cant_bytes
                    rpi++;
                    ls += (int) P[rpi++];
                    break;

                case DMEM: // DMEN cant_bytes
                    rpi++;
                    ls -= (int) P[rpi++];
                    break;

                case INPP:
                    rpi++;
                    memset(S, 0, TAM_STACK);
                    ls = 0;
                    memset(D, 0, TAM_DISP);
                    D[0] = 0;
                    break;

                case POP: //POP tipo
                    rpi++;
                    switch ((int) P[rpi++]) {
                        case 0:
                            ls -= tc;
                            break;
                        case 1:
                            ls -= te;
                            break;
                        case 2:
                            ls -= tf;
                            break;
                    }
                    break;

                case CAST:
                    rpi++;
                    switch ((int) P[rpi++]) {
                        case 0: 
                            switch ((int) P[rpi++]) {
                                case 1:
                                    (*(int *) &S[ls - tc]) = (int) S[ls - tc];
                                    ls = (ls - tc) + te;
                                    break;
                                case 2:
                                    (*(float *) &S[ls - tc]) = (int) S[ls - tc];
                                    ls = (ls - tc) + tf;
                                    break;
                            }
                            break;
                        case 1: 
                            if ((int) P[rpi++] == 2) {
                                (*(float *) &S[ls - te]) = (*(int *) &S[ls - te]);
                                ls = (ls - te) + tf;
                            }
                            break;
                    }
                    break;

                case LEER: 
                    rpi++;
                    switch ((int) P[rpi++]) {
                        case 0:
                            scanf("%c", &S[ls]);
                            ls += tc;
                            break;
                        case 1:
                            scanf("%d", (int *) &S[ls]);
                            ls += te;
                            break;
                        case 2:
                            scanf("%f", (float *) &S[ls]);
                            ls += tf;
                            break;
                    }
                    break;

                case IMPR: //IMPR tipo
                    rpi++;
                    switch ((int) P[rpi++]) {
                        case 0:
                            printf("%c", S[ls - tc]);
                            ls -= tc;
                            break;
                        case 1:
                            printf("%d", (*(int *) &S[ls - te]));
                            ls -= te;
                            break;
                        case 2:
                            printf("%f", (*(float *) &S[ls - tf]));
                            ls -= tf;
                            break;
                    }
                    break;

                case CRCTS: //CRCTS k
                    rpi++;
                    (* (int *) & S[ls]) = (int) P[rpi++];
                    ls += te;
                    break;

                case IMPCS: //IMPCS
                    rpi++;
                    printf("%s", &C[(* (int *) & S[ls - te])]);
                    ls -= te;
                    break;

                case BIFS: //BIFS desp
                    rpi++;
                    rpi += (int) P[rpi];
                    rpi++;
                    break;

                case BIFF: //BIFF tipo desp
                    rpi++;
                    switch ((int) P[rpi++]) {
                        case 0:
                            if (S[ls - tc] == 0) rpi += (int) P[rpi];
                            ls -= tc;
                            break;
                        case 1:
                            if ((* (int *) &S[ls - te]) == 0) rpi += (int) P[rpi];
                            ls -= te;
                            break;
                        case 2:
                            if ((* (float *) &S[ls - tf]) == 0) rpi += (int) P[rpi];
                            ls -= tf;
                            break;
                    }
                    rpi++;
                    break;

                case ENBL:
                {//ENBL k
                    int k;

                    rpi++;
                    k = (int) P[rpi++];
                    (* (int *) &S[ls]) = D[ k ];
                    ls += te;
                    D[ k ] = ls;
                    break;
                }

                case FINB: //FINB k
                    rpi++;
                    ls -= te;
                    D[ (int) P[rpi++] ] = (* (int *) &S[ls]);
                    break;

            } // del switch (cod_op)
            //
        }// del if ls < TAM_STACK
        else {
            printf("\nError: Overflow del Stack de Ejecuci¢n\n");
            exit(1);
        }



     
    } // del while

}




