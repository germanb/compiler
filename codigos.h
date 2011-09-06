/***********************************************************
           CODIGOS PARA UTILIZAR EN EL SCANNER
***********************************************************/
/*  39 TOKEN DE USO EN EL SCANNER */

#define NADA  0L
#define UNO   1L
#define FLAG  (UNO<<30)

#define CVOID       UNO       /* 1 */
#define CCHAR      (UNO<<1)   /* 2 */
#define CINT       (UNO<<2)   /* 4 */
#define CFLOAT     (UNO<<3)   /* 8 */
#define CAMPER     (UNO<<4)   /* 16 */
#define CCOR_ABR   (UNO<<5)   /* 32 */
#define CCOR_CIE   (UNO<<6)   /* 64 */
#define CCOMA      (UNO<<7)   /* 128 */
#define CPYCOMA    (UNO<<8)   /* 256 */
#define CASIGNAC   (UNO<<9)   /* 512 */
#define CLLA_ABR   (UNO<<10)  /* 1024 */
#define CLLA_CIE   (UNO<<11)  /* 2048 */
#define CWHILE     (UNO<<12)  /* 4096 */
#define CPAR_ABR   (UNO<<13)  /* 8192 */
#define CPAR_CIE   (UNO<<14)  /* 16384 */
#define CIF        (UNO<<15)  /* 32768 */
#define CELSE      (UNO<<16)  /* 65536 */
#define CIN       (UNO<<17)   /* 131072 */
#define COUT      (UNO<<18)   /* 262144 */
#define CSHL      (UNO<<19)	/* c<< */  /* 524288 */
#define CSHR      (UNO<<20)     /* c>> */  /* 1048576 */

#define CDISTINTO  (UNO|FLAG)     /* */
#define CIGUAL     (UNO<<1|FLAG)  /* */ 
#define CMENOR     (UNO<<2|FLAG)  /* */ 
#define CMEIG      (UNO<<3|FLAG)  /* */
#define CMAYOR     (UNO<<4|FLAG)
#define CMAIG      (UNO<<5|FLAG)
#define CMAS       (UNO<<6|FLAG)
#define CMENOS     (UNO<<7|FLAG)
#define COR        (UNO<<8|FLAG)
#define CMULT      (UNO<<9|FLAG)
#define CDIV       (UNO<<10|FLAG)
#define CAND       (UNO<<11|FLAG)
#define CIDENT     (UNO<<12|FLAG)
#define CNEG       (UNO<<13|FLAG)
#define CCONS_ENT  (UNO<<14|FLAG)
#define CCONS_FLO  (UNO<<15|FLAG)
#define CCONS_CAR  (UNO<<16|FLAG)
#define CCONS_STR  (UNO<<17|FLAG)
#define CRETURN    (UNO<<18|FLAG)
  
#define CEOF       (UNO<<19|FLAG)
#define SEGUIR     (UNO<<20|FLAG)





