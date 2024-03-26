/* ONȚICĂ Alexandra-Elena - 311CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functii_tema1.h"

#define L_MAX_COMANDA 14
// de scos -Wall -Werror din Makefile la final
int main() {
    FILE *fin = fopen("tema1.in", "r");

    if (fin == NULL) {
        fprintf(stderr, "Fisierul de intrare nu a fost deschis\n");
        return 0;
    }

    FILE *fout = fopen("tema1.out", "w");

    if (fout == NULL) {
        fprintf(stderr, "Fisierul de iesire nu a fost deschis\n");
        fclose(fin);
        return 0;
    }

    TTren *tren = InitTren();
    if (!tren) {
        fprintf(stderr, "Crearea trenului nu a reusit\n");
        CloseFiles(fin, fout);
        return 0;
    }

    TCoada *coada = InitQ();
    if (!coada) {
        // free tren - de scris functie
        fprintf(stderr, "Crearea cozii nu a reusit\n");
        CloseFiles(fin, fout);
        return 0;
    }

    int nr_comenzi = 0, i = 0;
    char comanda[L_MAX_COMANDA + 1];

    fscanf(fin, "%d", &nr_comenzi);

    for(i = 0; i < nr_comenzi; i++) {
        fscanf(fin, "%s", comanda);

        if (strcmp(comanda, "SHOW") == 0) {
            Show(fout, tren);
        } else if (strcmp(comanda, "SHOW_CURRENT") == 0) {
            ShowCurrent(fout, tren);
        } else if (strncmp(comanda, "WRITE", 5) == 0) {
            // adaug in coada
        }
    }

    // de eliberat tot ce am alocat: tren, coada, 

    CloseFiles(fin, fout);

    return 0;
}
