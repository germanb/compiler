/****************************************************************************

		       	C O M P I L A D O R E S
						   

Modelo para la implementacion de tipo set en 'C'.

En este fuente, se ve en primer termino, la definicion de las constantes 
que representan los tokens devueltos por el scanner(); luego las funciones 
que implementan operaciones sobre conjuntos de acuerdo a esas definiciones

****************************************************************************/


# include <stdio.h>
# include "codigos.h"
# include "set.h"


/****************************************************************************
						une()
****************************************************************************/
set une(set c1, set c2)
{
	set u;

	u.p1=c1.p1|c2.p1;
	u.p2=c1.p2|c2.p2;
	return u;
}
/****************************************************************************
						in()
****************************************************************************/
int in(long e,set A) { /* x pertenece a A ? */
  long r;

       if ((e & (UNO<<30)) != UNO<<30 ) {
         r= (e & A.p1);    
       }
       else {
         r=(e & A.p2);
       }
       if (e == r) return 1;
       else  return 0;

}

/****************************************************************************
						cons()
****************************************************************************/
set cons(long x,long y)
{
	set nuevo_set;

	nuevo_set.p1 = x;
	nuevo_set.p2 = y;
	return nuevo_set;
}
/***********************************************************************
                            imprime set
***********************************************************************/
void imp_set(set v){
  printf("%X\n",v.p1);
  printf("%X \n",v.p2);
};

void initFirsts(){
  firsts[UT].p1 = CVOID|CINT|CFLOAT|CCHAR;
  firsts[UT].p2 = NADA;

  firsts[DE].p1 = CVOID|CINT|CFLOAT|CCHAR;
  firsts[DE].p2 = NADA;

  firsts[ET].p1 = CVOID|CINT|CFLOAT|CCHAR;
  firsts[ET].p2 = NADA;

  firsts[ED].p1 = CPAR_ABR|CASIGNAC|CCOR_ABR|CCOMA|CPYCOMA;
  firsts[ED].p2 = NADA;

  firsts[DF].p1 = CPAR_ABR;
  firsts[DF].p2 = NADA;

  firsts[DV].p1 = CASIGNAC|CCOR_ABR|CCOMA|CPYCOMA;
  firsts[DV].p2 = NADA;

  firsts[LDP].p1 = CVOID|CINT|CFLOAT|CCHAR;
  firsts[LDP].p2 = NADA;

  firsts[DP].p1 = CVOID|CINT|CFLOAT|CCHAR;
  firsts[DP].p2 = NADA;

  firsts[DI].p1 = CASIGNAC|CCOR_ABR|CCOMA|CPYCOMA;
  firsts[DI].p2 = NADA;

  firsts[LDI].p1 = NADA;
  firsts[LDI].p2 = CIDENT;

  firsts[C].p1 = NADA;
  firsts[C].p2 = CCONS_ENT|CCONS_FLO|CCONS_CAR;

  firsts[LI].p1= NADA;
  firsts[LI].p2 = CCONS_ENT|CCONS_FLO|CCONS_CAR;

  firsts[LP].p1 = CPAR_ABR|CLLA_ABR|CIN|COUT|CIF|CWHILE|CPYCOMA;
  firsts[LP].p2=CCONS_ENT|CCONS_FLO|CCONS_CAR|CCONS_STR|CMAS|CMENOS|CNEG|CIDENT|CRETURN;

  firsts[LD].p1 = CVOID|CINT|CFLOAT|CCHAR;
  firsts[LD].p2 = NADA;

  firsts[D].p1 = CVOID|CINT|CFLOAT|CCHAR;
  firsts[D].p2 = NADA;

  firsts[P].p1 = CPAR_ABR|CLLA_ABR|CIN|COUT|CIF|CWHILE|CPYCOMA;
  firsts[P].p2=CCONS_ENT|CCONS_FLO|CCONS_CAR|CCONS_STR|CMAS|CMENOS|CNEG|CIDENT|CRETURN;

  firsts[PE].p1=CPAR_ABR;
  firsts[PE].p2=CCONS_ENT|CCONS_FLO|CCONS_CAR|CCONS_STR|CMAS|CMENOS|CNEG|CIDENT;

  firsts[PC].p1 = CLLA_ABR;
  firsts[PC].p2 = NADA;

  firsts[PS].p1 = CIF;
  firsts[PS].p2 =  NADA;

  firsts[PI].p1 = CWHILE;
  firsts[PI].p2 = NADA;

  firsts[PES].p1 = CIN|COUT;
  firsts[PES].p2 = NADA;

  firsts[PR].p1 = NADA;
  firsts[PR].p2 = CRETURN;

  firsts[V].p1 = NADA;
  firsts[V].p2 = CIDENT;

  firsts[E].p1 = CPAR_ABR;
  firsts[E].p2 = CCONS_ENT|CCONS_FLO|CCONS_CAR|CCONS_STR|CMAS|CMENOS|CNEG|CIDENT;

  firsts[ES].p1=CPAR_ABR;
  firsts[ES].p2=CCONS_ENT|CCONS_FLO|CCONS_CAR|CCONS_STR|CMAS|CMENOS|CNEG|CIDENT;

  firsts[R].p1 = NADA;
  firsts[R].p2 = CDISTINTO|CIGUAL|CMAYOR|CMENOR|CMEIG|CMAIG;

  firsts[T].p1 = CPAR_ABR;
  firsts[T].p2 = CCONS_ENT|CCONS_FLO|CCONS_CAR|CIDENT|CNEG|CCONS_STR;

  firsts[F].p1 = CPAR_ABR;
  firsts[F].p2 = CCONS_ENT|CCONS_FLO|CCONS_CAR|CIDENT|CNEG|CCONS_STR;

  firsts[LF].p1 = NADA;
  firsts[LF].p2 = CIDENT;

  firsts[LE].p1 = CPAR_ABR;
  firsts[LE].p2 = CCONS_ENT|CCONS_FLO|CCONS_CAR|CCONS_STR|CMAS|CMENOS|CNEG|CIDENT;
}

/*
int main () {
  int result;

  long l1, l2, e;
  set s1;
  set s2;

  l2= 0x40000030;
  l1= 0x00000001;

  s1=cons(l1, l2);

  e=0x40000002;
  result= in(e, s1);

  imp_set(s1);

  printf("esta %X en el set ? %d\n",e,result);
}

*/















