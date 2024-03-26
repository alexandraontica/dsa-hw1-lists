/* ONȚICĂ Alexandra-Elena - 311CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functii_tema1.h"

void CloseFiles(FILE *fin, FILE *fout) {
    fclose(fin);
    fclose(fout);
}

TLista AlocCelula(char *elem) {
    TLista aux = (TLista)malloc(sizeof(TCelula));
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

TTren* InitTren() {
    TTren *t = (TTren *)malloc(sizeof(TTren));
    if (!t) {
        return NULL;
    }

    t->locomotiva = AlocCelula("");  // informatia din santinela nu va fi folosita
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

TCoada* InitQ() {
    TCoada *c = (TCoada *)malloc(sizeof(TCoada));
    if (!c) {
        return NULL;
    }

    c->inc = NULL;
    c->sf = NULL;

    return c;
}

void Show(FILE *fout, TTren *t) {
    for (TLista vagon = t->locomotiva->urm; vagon != t->locomotiva; vagon = vagon->urm) {
        if (t->mecanic == vagon) {
            fprintf(fout, "|%s|", vagon->info);
        } else {
            fprintf(fout, "%s", vagon->info);
        }
    }
    fprintf(fout, "\n");
}

void ShowCurrent(FILE *fout, TTren *t) {
    fprintf(fout, "%s\n", t->mecanic->info);
}

void Write(FILE *fin, TTren *t) {
    char chr_nou;
    fscanf(fin, "%c", &chr_nou);  // citeste spatiul dintre WRITE si caracter
    fscanf(fin, "%c", &chr_nou);
    t->mecanic->info[0] = chr_nou;
}
