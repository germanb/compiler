int char2int(char t[]) {
    int res = 0, Ti = strlen(t) - 1, piso = 0;
    if (t[0] == '-') {
        piso = 1;
    }

    for (; Ti >= piso; Ti--) {
        int x = 10, y = strlen(t)-(Ti + 1), r = 1;
        for (; y > 0; y--) {
            r *= x;
        }
        res += (t[Ti] - 48) * r;
    }
    return (t[0] == '-') ? -res : res;
}

char *concatenateStrs(char s1[], char s2[]) {
    newLine = (char *) calloc(1, 50);
    strcat(newLine, s1);
    strcat(newLine, " ");
    return strcat(newLine, s2);
}

char *int2str(int num) {
    char *salida = (char *) calloc(1, TAM_LEXEMA);
    int i = 0;
    if (num >= 0) {
        if (num == 0) {
            salida[0] = '0';
            i = 1;
        }
        for (; num > 0; i++) {
            salida[i] = num % 10 + 48;
            num /= 10;
        }
        salida[i] = 0;

        int i; char temp;
        for (i = 0; i < strlen(salida) / 2; i++) {
            temp = salida[i];
            salida[i] = salida[strlen(salida) - 1 - i];
            salida[strlen(salida) - 1 - i] = temp;
        }
        return salida;
    } else {
        newLine = (char *) calloc(1, 50);
        strcat(newLine, "-");
        return strcat(newLine, int2str(-num));
    }
}

float char2float(char num[]) {
    char part_ent[strlen(num) + 1], part_dec[strlen(num) + 1];
    int punto = 0;
    float res = 0;
    int i, decimales, piso = 0;

    if (num[0] == '-') {
        piso = 1;
    }

    part_ent[0] = part_dec[0] = '0';
    part_ent[1] = part_dec[1] = 0;

    for (i = piso; i <= strlen(num); i++) {
        if (num[i] == '.') {
            punto = 1;
            part_ent[i - piso] = 0;
        } else if (!punto) {
            part_ent[i - piso] = num[i];
        } else {
            part_dec[i - piso - (strlen(part_ent) + 1)] = num[i];
        }
    }
    int x = 10, y = strlen(part_dec), r = 1;
    for (; y > 0; y--) {
        r *= x;
    }
    res = (char2int(strcat(part_ent, part_dec)) + .0) / r;

    return (num[0] == '-') ? -res : res;
}

char Cohersion(char tipo, char Tipo_Operado) {
    char Tipo_Retorno = en_tabla("float");

    if (tipo == en_tabla("TIPOARREGLO") || Tipo_Operado == en_tabla("TIPOARREGLO")) {
        return en_tabla("TIPOARREGLO");
    }

    if (tipo == en_tabla("TIPOERROR") || Tipo_Operado == en_tabla("TIPOERROR")) {
        return en_tabla("TIPOERROR");
    }

    if (tipo == en_tabla("char")) {
        Tipo_Retorno = Tipo_Operado;
    } else if (tipo == en_tabla("int")) {
        if (Tipo_Operado == en_tabla("float")) {
            Tipo_Retorno = Tipo_Operado;
        } else {
            Tipo_Retorno = en_tabla("int");
        }
    }
    return Tipo_Retorno;
}

char getType(char tipo) {
    if (tipo == en_tabla("char")) {
        return 0;
    } else if (tipo == en_tabla("int")) {
        return 1;
    } else {
        return 2;
    }
}

char *getInstr(int INST) {
    char *sINST = (char *) calloc(1, 13);
    strcpy(sINST, ">>ERROR<<");
    switch (INST) {
    case CRCT:
        strcpy(sINST, sCRCT);
        break;
    case CRVL:
        strcpy(sINST, sCRVL);
        break;
    case SUM:
        strcpy(sINST, sSUM);
        break;
    case SUB:
        strcpy(sINST, sSUB);
        break;
    case MUL:
        strcpy(sINST, sMUL);
        break;
    case DIV:
        strcpy(sINST, sDIV);
        break;
    case INV:
        strcpy(sINST, sINV);
        break;
    case AND:
        strcpy(sINST, sAND);
        break;
    case OR:
        strcpy(sINST, sOR);
        break;
    case NEG:
        strcpy(sINST, sNEG);
        break;
    case POP:
        strcpy(sINST, sPOP);
        break;
    case CAST:
        strcpy(sINST, sCAST);
        break;
    case CMMA:
        strcpy(sINST, sCMMA);
        break;
    case CMME:
        strcpy(sINST, sCMME);
        break;
    case CMIG:
        strcpy(sINST, sCMIG);
        break;
    case CMAI:
        strcpy(sINST, sCMAI);
        break;
    case CMEI:
        strcpy(sINST, sCMEI);
        break;
    case CMNI:
        strcpy(sINST, sCMNI);
        break;
    case ALM:
        strcpy(sINST, sALM);
        break;
    case LEER:
        strcpy(sINST, sLEER);
        break;
    case IMPR:
        strcpy(sINST, sIMPR);
        break;
    case BIFF:
        strcpy(sINST, sBIFF);
        break;
    case BIFS:
        strcpy(sINST, sBIFS);
        break;
    case INPP:
        strcpy(sINST, sINPP);
        break;
    case PARAR:
        strcpy(sINST, sPARAR);
        break;
    case ALOC:
        strcpy(sINST, sALOC);
        break;
    case DMEM:
        strcpy(sINST, sDMEM);
        break;
    case CRDI:
        strcpy(sINST, sCRDI);
        break;
    case CRVLI:
        strcpy(sINST, sCRVLI);
        break;
    case ALMI:
        strcpy(sINST, sALMI);
        break;
    case ENPR:
        strcpy(sINST, sENPR);
        break;
    case CHPR:
        strcpy(sINST, sCHPR);
        break;
    case RTPR:
        strcpy(sINST, sRTPR);
        break;
    case ENBL:
        strcpy(sINST, sENBL);
        break;
    case FINB:
        strcpy(sINST, sFINB);
        break;
    case IMPCS:
        strcpy(sINST, sIMPCS);
        break;
    case CRCTS:
        strcpy(sINST, sCRCTS);
    }
    return sINST;
}

