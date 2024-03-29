/* ONȚICĂ Alexandra-Elena - 311CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functii_tema1.h"
// de scos -Wall -Werror din Makefile la final
int main()
{
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
        fprintf(fout, "Crearea trenului nu a reusit\n");
        CloseFiles(fin, fout);
        return 0;
    }

    TCoada *coada = InitQ();
    if (!coada) {
        // free tren - de scris functie
        fprintf(fout, "Crearea cozii pentru comenzi nu a reusit\n");
        CloseFiles(fin, fout);
        return 0;
    }

    int nr_comenzi = 0, i = 0;
    char *comanda = (char *)malloc(L_MAX_STR + L_MAX_COMANDA + 1);

    fscanf(fin, "%d", &nr_comenzi);
    //fgetc(fin);

    for(i = 0; i <= nr_comenzi; i++) {
        //fscanf(fin, "%s", comanda);
        fgets(comanda, L_MAX_STR + L_MAX_COMANDA + 1, fin);
        if (comanda[strlen(comanda) - 1] == '\n') comanda[strlen(comanda) - 1] = '\0';
        printf("%s\n", comanda);

        if (strcmp(comanda, "SHOW") == 0) {
            Show(fout, tren);
        } else if (strcmp(comanda, "SHOW_CURRENT") == 0) {
            ShowCurrent(fout, tren);
        } else if (strncmp(comanda, "WRITE", 5) == 0 || strncmp(comanda, "INSERT_RIGHT", 12) == 0
                   || strncmp(comanda, "INSERT_LEFT", 11) == 0 || strncmp(comanda, "SEARCH", 6) == 0
                   || strncmp(comanda, "SEARCH_RIGHT", 12) == 0) {  // cred ca poti sa bagi aici si search left si right
            // char arg[L_MAX_STR + 1];  // am presupus ca string-ul pe care il caut nu este mai lung de 200 de caractere
            // fscanf(fin, "%s", arg);  // citeste caracterul care trebuie inscriptionat pe vagon
            // // citirea merge doar daca string ul de la search nu are spatii, vezi daca iti trec testele

            // if (strlen(comanda) + strlen(arg) > L_MAX_STR + L_MAX_COMANDA) {
            //     char *aux = (char *)realloc(comanda, strlen(comanda) + strlen(arg) + 10);
            //     if (!aux) {
            //         // elibereaza memoria alocata
            //         // mesaj eroare
            //         CloseFiles(fin, fout);
            //         return 0;
            //     }
            //     comanda = aux;
            // }
            // strcat(comanda, arg);
            // printf("%s %ld\n", arg, strlen(arg));
            // // char str[strlen(comanda) + strlen(arg) + 2];
            // // strcpy(str, comanda);
            // // strcat(str, arg);
            // // printf("%s\n", str);

            int rez = IntrQ(coada, comanda);
            if (!rez) {
                // elibereaza memoria alocata
                fprintf(fout, "Adaugarea in coada nu a reusit\n");
                CloseFiles(fin, fout);
                return 0;
            }
        } else if (strcmp(comanda, "MOVE_RIGHT") == 0 || strcmp(comanda, "MOVE_LEFT") == 0
                   || strcmp(comanda, "CLEAR_CELL") == 0 || strcmp(comanda, "CLEAR_ALL") == 0) {
            int rez = IntrQ(coada, comanda);
            if (!rez) {
                // elibereaza memoria alocata
                fprintf(fout, "Adaugarea in coada nu a reusit\n");
                CloseFiles(fin, fout);
                return 0;
            }
        } else if (strcmp(comanda, "EXECUTE") == 0) {
            int rez = Execute(fout, coada, tren);
            if (!rez) {
                // elibereaza memoria alocata
                fprintf(fout, "Executarea unei comenzi nu a reusit\n");
                CloseFiles(fin, fout);
                return 0;
            }
        } else if (strcmp(comanda, "SWITCH") == 0) {
            Switch(coada);
        }
    }

    // de eliberat tot ce am alocat: tren, coada (cel mai bine faci o functie)

    CloseFiles(fin, fout);

    return 0;
}
