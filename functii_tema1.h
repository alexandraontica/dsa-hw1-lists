/* ONȚICĂ Alexandra-Elena - 311CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct celula {
    char *info;
    struct celula *pre, *urm;
} TCelula, *TLista;

typedef struct tren {
    TLista locomotiva;
    TLista mecanic;
} TTren;

typedef struct coada {
    TLista inc, sf;
} TCoada;

void CloseFiles(FILE *fin, FILE *fout);
TLista AlocCelula(char *elem);
TTren* InitTren();
TCoada* InitQ();
void Show(FILE *fout, TTren *t);
void ShowCurrent(FILE *fout, TTren *t);
void Write(FILE *fin, TTren *t);
