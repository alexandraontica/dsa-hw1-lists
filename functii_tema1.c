/* ONȚICĂ Alexandra-Elena - 311CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functii_tema1.h"

void CloseFiles(FILE *fin, FILE *fout)
/* inchiderea fisierelor reuseste:
se transmit ca parametrii niste copii ale pointerilor,
dar aceste copii "pointeaza" catre aceleasi fisiere */
{
    fclose(fin);
    fclose(fout);
}

TLista AlocCelula(char *elem)
{
    TLista aux = (TLista)calloc(1, sizeof(TCelula));
    if (!aux) {
        return NULL;
    }

    aux->info = strdup(elem);
    if (!aux->info) {
        free(aux);
        return NULL;
    }

    aux->urm = NULL;
    aux->pre = NULL;

    return aux;
}

TTren* InitTren()
/* initializare tren: creare lista circulara cu santinela (locomotiva), atasare vagon; salvare adresa vagon 1 */
{
    TTren *t = (TTren *)calloc(1, sizeof(TTren));
    if (!t) {
        return NULL;
    }

    t->locomotiva = AlocCelula(" ");  // informatia din santinela nu va fi folosita
    if (!t->locomotiva) {
        free(t);
        return NULL;
    }
    
    TLista vagon = AlocCelula("#");  // primul vagon
    if (!vagon) {
        free(t->locomotiva->info);
        free(t->locomotiva);
        free(t);
        return NULL;
    }

    t->locomotiva->urm = vagon;
    vagon->urm = t->locomotiva;
    t->locomotiva->pre = vagon;
    vagon->pre = t->locomotiva;

    t->mecanic = vagon;

    return t;
}

TCoada* InitQ()
/* creare coada vida */
{
    TCoada *c = (TCoada *)calloc(1, sizeof(TCoada));
    if (!c) {
        return NULL;
    }

    c->inc = NULL;
    c->sf = NULL;

    return c;
}

int IntrQ(TCoada *c, char *comanda)
/* intoarce 1: introducerea comenzii in coada a reusit, 0: in caz contrar */
{ 
  TLista aux = AlocCelula(comanda);
  if (!aux) {
    return 0;
  }

  if (!c->inc) {  // e coada vida
    c->inc = aux;
    c->sf = aux;
  } else {
    c->sf->urm = aux;
    aux->pre = c->sf;
    c->sf = aux;
  }
  
  return 1;             
}

int ExtrQ(TCoada *c, char *comanda)
/* intoarce 0: coada e vida, 1: s-a extras o comanda din coada */
{
    if (!c->inc) {  // e coada vida
        return 0;
    }

    if (c->inc == c->sf) {  // coada are un element
        strcpy(comanda, c->inc->info);
        free(c->inc->info);
        free(c->inc);
        c->inc = NULL;  // devine coada vida
        c->sf = NULL;
    } else {
        TLista aux = c->inc;
        strcpy(comanda, c->inc->info);
        c->inc = c->inc->urm;
        free(aux->info);
        free(aux);
    }

    return 1;
}

void MoveLeft(TTren *t)
{
    if (t->mecanic->pre == t->locomotiva) {  // este primul vagon
        t->mecanic = t->locomotiva->pre;
    } else {
        t->mecanic = t->mecanic->pre;
    }
}

void MoveRight(TTren *t)
{
    if (t->mecanic->urm == t->locomotiva) {  // este ultimul vagon
        InsertRight(t, "#");
    } else {
        t->mecanic = t->mecanic->urm;
    }
}

void Write(TTren *t, char *comanda)
{
    t->mecanic->info[0] = comanda[strlen(comanda) - 1];
}

void ClearCell(TTren *t)
{
    if (t->mecanic->urm == t->locomotiva && t->mecanic->pre == t->locomotiva) {  // exista un singur vagon
        Write(t, "#");  // trenuletul revine la forma initiala (un singur vagon cu inscriptia "#")
        return;
    }

    TLista aux = t->mecanic;
    MoveLeft(t);

    if (aux->pre == t->locomotiva) {
        t->locomotiva->urm = aux->urm;
        aux->urm->pre = t->locomotiva;
    } else {
        t->mecanic->urm = aux->urm;
        aux->urm->pre = t->mecanic;
    }

    free(aux->info);
    free(aux);
}

void ClearAll(TTren *t)
{
    t->mecanic = t->locomotiva->pre;
    while(t->mecanic->pre != t->locomotiva) {
        ClearCell(t);
    }
    ClearCell(t);
}

int InsertLeft(FILE *fout, TTren *t, char *comanda)
/* intoarce 1: alocarea nu a reusit, 0: in caz contrar */
{
    if (t->mecanic == t->locomotiva->urm) {
        fprintf(fout, "ERROR\n");
        return 1;
        /* desi nu a fost inserat vagonul, returnez 1 deoarece
        functia afiseaza ceea ce cere cerinta */
    }
    
    char chr[2] = "";
    chr[0] = comanda[POZ_CHR_LEFT];

    TLista vagon = AlocCelula(chr);
    if(!vagon) {
        return 0;
    }

    vagon->urm = t->mecanic;
    vagon->pre = t->mecanic->pre;
    t->mecanic->pre->urm = vagon;
    t->mecanic->pre = vagon;

    t->mecanic = t->mecanic->pre;

    return 1;
}

int InsertRight(TTren *t, char *comanda)
/* intoarce 1: inserarea a reusit, 0: in caz contrar */
{
    char chr[2] = "";
    chr[0] = comanda[POZ_CHR_RIGHT];

    TLista vagon = AlocCelula(chr);
    if(!vagon) {
        return 0;
    }

    vagon->urm = t->mecanic->urm;
    vagon->pre = t->mecanic;
    t->mecanic->urm->pre = vagon;
    t->mecanic->urm = vagon;

    t->mecanic = t->mecanic->urm;

    return 1;
}

void Search(FILE *fout, TTren *t, char *comanda)
{
    char *de_cautat = comanda + POZ_SEARCH;
    char inscriptii[L_MAX_STR + 1] = "";
    strcpy(inscriptii, t->mecanic->info);

    TLista vagon = t->mecanic;
    if (vagon->urm == t->locomotiva) {
        vagon = t->locomotiva->urm;
    } else {
        vagon = vagon->urm;
    }

    int nr_chr = 1;
    int len = strlen(de_cautat);

    while (vagon != t->mecanic) {
        nr_chr++;

        if (nr_chr <= len) {
            strcat(inscriptii, vagon->info);
        } else {
            strcpy(inscriptii, inscriptii + 1);
            strcat(inscriptii, vagon->info);
        }

        if (strcmp(inscriptii, de_cautat) == 0) {
            for (int i = 1; i < nr_chr - len + 1; i++) {
                if (t->mecanic->urm == t->locomotiva) {
                    t->mecanic = t->locomotiva->urm;
                } else {
                    t->mecanic = t->mecanic->urm;
                }
            }
            return;
        }

        if (vagon->urm == t->locomotiva) {
            vagon = t->locomotiva->urm;
        } else {
            vagon = vagon->urm;
        }
    }

    fprintf(fout, "ERROR\n");
}

void SearchLeft(FILE *fout, TTren *t, char *comanda)
{
    char *de_cautat = comanda + POZ_CHR_LEFT;
    char inscriptii[L_MAX_STR + 1] = "";  // initializare sir vid
    TLista vagon = t->mecanic->pre;
    int nr_chr = 0;
    int len = strlen(de_cautat);

    while (vagon != t->locomotiva) {
        nr_chr++;

        if (nr_chr <= len) {
            strcat(inscriptii, vagon->info);
        } else {
            strcpy(inscriptii, inscriptii + 1);
            strcat(inscriptii, vagon->info);
        }
        
        char rev[strlen(inscriptii) + 1];
        int len2 = strlen(inscriptii);

        for (int i = 0; i < len2; i++) {
            rev[i] = inscriptii[len2 - i - 1];
        }
        rev[len2] = '\0';

        if (strcmp(rev, de_cautat) == 0) {
            for (int i = 1; i < nr_chr - len + 2; i++) {
                t->mecanic = t->mecanic->pre;
            }
            return;
        }

        vagon = vagon->pre;
    }

    fprintf(fout, "ERROR\n");
}

void SearchRight(FILE *fout, TTren *t, char *comanda)
{
    char *de_cautat = comanda + POZ_CHR_RIGHT;
    char inscriptii[L_MAX_STR + 1] = "";
    //strcpy(inscriptii, t->mecanic->info);
    TLista vagon = t->mecanic->urm;
    int nr_chr = 0;  
    int len = strlen(de_cautat);

    while (vagon != t->locomotiva) {
        nr_chr++;

        if (nr_chr <= len) {
            strcat(inscriptii, vagon->info);  
        } else {
            strcpy(inscriptii, inscriptii + 1);
            strcat(inscriptii, vagon->info);
        }

        char rev[strlen(inscriptii) + 1];
        int len2 = strlen(inscriptii);

        for (int i = 0; i < len2; i++) {
            rev[i] = inscriptii[len2 - i - 1];
        }
        rev[len2] = '\0';

        if (strcmp(rev, de_cautat) == 0) {
            for (int i = 1; i < nr_chr - len + 2; i++) {
                t->mecanic = t->mecanic->urm;
            }
            return;
        }

        vagon = vagon->urm;
    }

    fprintf(fout, "ERROR\n");
}

void Show(FILE *fout, TTren *t)
{
    for (TLista vagon = t->locomotiva->urm; vagon != t->locomotiva; vagon = vagon->urm) {
        if (t->mecanic == vagon) {
            fprintf(fout, "|%s|", vagon->info);
        } else {
            fprintf(fout, "%s", vagon->info);
        }
    }
    fprintf(fout, "\n");
}

void ShowCurrent(FILE *fout, TTren *t)
{
    fprintf(fout, "%s\n", t->mecanic->info);
}

void Switch(TCoada *c)  // incearca sa intelegi ce ai facut aici
{
    if (!c->inc) {  // coada vida
        return;
    }

    TLista p, ant, inc_vechi;

    inc_vechi = c->inc;
    p = c->inc->urm;
    c->inc->urm = NULL;
    c->inc->pre = p;

    while (p) {
        ant = p;
        p = p->urm;
        ant->urm = c->inc;
        ant->pre = p;
        c->inc->pre = ant;
        c->inc = ant;
    }

    c->sf = inc_vechi;
}


int Execute(FILE *fout, TCoada *c, TTren *t)
/* intoarce 1: executare reusite, 0: altfel */
{
    char comanda[L_MAX_COMANDA + L_MAX_STR + 1];
    int rez = ExtrQ(c, comanda);
    if (!rez) {
        return 0;
    }

    if (strcmp(comanda, "MOVE_LEFT") == 0) {
        MoveLeft(t);
    } else if (strcmp(comanda, "MOVE_RIGHT") == 0) {
        MoveRight(t);
    } else if (strncmp(comanda, "WRITE", 5) == 0) {
        Write(t, comanda);
    } else if (strcmp(comanda, "CLEAR_CELL") == 0) {
        ClearCell(t);
    } else if (strcmp(comanda, "CLEAR_ALL") == 0) {
        ClearAll(t);
    } else if (strncmp(comanda, "INSERT_LEFT", 11) == 0) {
        rez = InsertLeft(fout, t, comanda);
        if (!rez) {
            return 0;
        }
    } else if (strncmp(comanda, "INSERT_RIGHT", 12) == 0) {
        rez = InsertRight(t, comanda);
        if (!rez) {
            return 0;
        }
    } else if (strncmp(comanda, "SEARCH_RIGHT", 12) == 0) {
        SearchRight(fout, t, comanda);
    } else if (strncmp(comanda, "SEARCH_LEFT", 11) == 0) {
        SearchLeft(fout, t, comanda);
    } else if (strncmp(comanda, "SEARCH", 6) == 0) {
        Search(fout, t, comanda);
    }

    return 1;
}

void FreeTren(TTren **t)
/* trenul este sigur diferit de NULL; dupa ce apelez functiile de eliberare a memoriei
care atribuie lui tren NULL programul se incheie de fiecare data */
{
    ClearAll(*t);
    free((*t)->locomotiva->urm->info);
    free((*t)->locomotiva->urm);
    free((*t)->locomotiva->info);
    free((*t)->locomotiva);
    free(*t);
    *t = NULL;
}

void ResetQ(TCoada *c)
/* coada este sigur diferita de NULL; dupa ce apelez functiile de eliberare a memoriei
care atribuie cozii NULL programul se incheie de fiecare data */
{
    while (c->inc) {
        TLista aux = c->inc;
        c->inc = aux->urm;
        free(aux->info);
        free(aux);
    }
    c->sf = NULL;
}

void FreeQ(TCoada **c)
{
    ResetQ(*c);
    free(*c);
    *c = NULL;
}

void FreeAll(TTren *t, TCoada *c)
{
    FreeTren(&t);
    FreeQ(&c);
}
