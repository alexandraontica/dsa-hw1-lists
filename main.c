/* ONȚICĂ Alexandra-Elena - 311CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functii_tema1.h"

int main()
{
    FILE *fin = fopen("tema1.in", "r");

    if (fin == NULL) {
        fprintf(stderr, "Fisierul de intrare nu a fost deschis\n");
        return 0;  // se poate intoarce si 1 (cod de eroare), dar cerinta nu specifica acest lucru
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
        fprintf(stderr, "Crearea cozii pentru comenzi nu a reusit\n");
        FreeTren(&tren);
        CloseFiles(fin, fout);
        return 0;
    }

    int nr_comenzi = 0, i = 0;
    char comanda[L_MAX_STR + L_MAX_COMANDA + 1];

    fscanf(fin, "%d", &nr_comenzi);
    
    for(i = 0; i < nr_comenzi; i++) {
        fscanf(fin, "%s", comanda);

        if (strcmp(comanda, "SHOW") == 0) {
            Show(fout, tren);
        } else if (strcmp(comanda, "SHOW_CURRENT") == 0) {
            ShowCurrent(fout, tren);
        } else if (strncmp(comanda, "WRITE", 5) == 0 || strncmp(comanda, "INSERT", 6) == 0
                   || strncmp(comanda, "SEARCH", 6) == 0) {
            char arg[L_MAX_STR + 1];  /* presupun ca string-ul pe care il caut la comenzile SEARCH 
                                         nu e mai lung de 100 caractere */
            fscanf(fin, "%s", arg);  
            strcat(comanda, arg);          

            int rez = IntrQ(coada, comanda);
            if (!rez) {
                fprintf(fout, "Adaugarea in coada nu a reusit\n");
                FreeAll(tren, coada);
                CloseFiles(fin, fout);
                return 0;
            }
        } else if (strncmp(comanda, "MOVE", 4) == 0 || strncmp(comanda, "CLEAR", 5) == 0) {
            int rez = IntrQ(coada, comanda);
            if (!rez) {
                fprintf(stderr, "Adaugarea in coada nu a reusit\n");
                FreeAll(tren, coada);
                CloseFiles(fin, fout);
                return 0;
            }
        } else if (strcmp(comanda, "EXECUTE") == 0) {
            int rez = Execute(fout, coada, tren);
            if (!rez) {
                fprintf(stderr, "Executarea unei comenzi nu a reusit\n");
                FreeAll(tren, coada);
                CloseFiles(fin, fout);
                return 0;
            }
        } else if (strcmp(comanda, "SWITCH") == 0) {
            Switch(coada);
        }
    }

    FreeAll(tren, coada);
    CloseFiles(fin, fout);

    return 0;
}
