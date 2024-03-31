/* ONȚICĂ Alexandra-Elena - 311CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define L_MAX_COMANDA 12
#define L_MAX_STR 200
#define POZ_CHR_RIGHT 12
#define POZ_CHR_LEFT 11
#define POZ_SEARCH 6

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
int IntrQ(TCoada *c, char *comanda);
int ExtrQ(TCoada *c, char *comanda);
void MoveLeft(TTren *t);
void MoveRight(TTren *t);
void Write(TTren *t, char *comanda);
void ClearCell(TTren *t);
void ClearAll(TTren *t);
int InsertLeft(FILE *fout, TTren *t, char *comanda);
int InsertRight(TTren *t, char *comanda);
void Search(FILE *fout, TTren *t, char *comanda);
void ReverseStr(char **rev, char *inscriptii);
void SearchLeft(FILE *fout, TTren *t, char *comanda);
void SearchRight(FILE *fout, TTren *t, char *comanda);
void Show(FILE *fout, TTren *t);
void ShowCurrent(FILE *fout, TTren *t);
void Switch(TCoada *c);
int Execute(FILE *fout, TCoada *c, TTren *t);
void FreeTren(TTren **t);
void ResetQ(TCoada *c);
void FreeQ(TCoada **c);
void FreeAll(TTren *t, TCoada *c);
