*ONȚICĂ Alexandra-Elena - 311CB*

Imi definesc tipul de date TLista ca pointer la o structura cu 3 campuri 
(info, urm si pre).
Pentru a putea folosi acelasi tip si pentru trenulet si pentru coada, 
campul info este de tip char * (privit ca string). Acest camp va retine 
pentru trenulet un string cu un singur caracter.
TTren are doua campuri de tipul TLista, unul care retine adresa santinelei 
si unul pentru adresa mecanicului.
TCoada contine pointeri catre inceputul, respectiv sfarsitul unui liste ce 
reprezinta coada.

In main.c, deschid fisierele de intrare si iesire si initializez trenul si 
coada, verificand de fiecare data daca a reusit operatia. Citesc, apoi, pe 
rand comenzile din fisierul de intrare, identific comanda folosindu-ma de 
strcmp/strncmp si, in functie de tipul ei, o adaug in coada sau o execut. 
In cazul comenzilor ce primesc argument, intai citesc argumentul, il 
concatenez la comanda si apoi adaug in coada string-ul obtinut. La final 
eliberez memoria alocata pentru coada si trenulet si inchid fisierele.

Despre functiile folosite:

MoveLeft:

Verific daca mecanicul se afla in primul vagon; in caz afirmativ, il mut in 
celula dinaintea santinelei, adica in ultimul vagon al trenului (lista 
circulara). Altfel, mut mecanicul in celula anterioara lui.

MoveRight:

Verific daca mecanicul se afla in ultimul vagon; in caz afirmativ, ma 
folosesc de functia definita ulterior InsertRight, care imi creeaza si 
leaga un vagon nou cu instriptia #. Altfel, mut mecanicul in celula ce 
urmeaza dupa mecanic.

Write:

Atribui informatiei vagonului in care se afla mecanicul ultimul caracter 
din comanda primita ca parametru.

ClearCell:

Daca exista un singur vagon in lista, doar schimb inscriptia acestuia in #.
Altfel, salvez pozitia mecanicului intr-o variabila auxiliara aux, mut 
mecanicul folosindu-ma de MoveLeft, rup legaturile celulei de eliminat (aux)
si eliberez memoria alocata pentru aux.

ClearAll:

Apelez functia ClearCell cat timp trenul are mai mult de un vagon si la
final inca o data ca sa schimb in # inscriptia vagonului ramas.

InsertLeft:

Afisez ERROR daca mecanicul se afla in celula ce urmeaza dupa santinela.
Altfel, salvez intr-un string (cu o pozitie) ultimul caracter din comanda
primita ca parametru. Acest string il folosesc ca parametru pentru functia
AlocCelula care imi creeaza vagonul ce trebuie inserat. Fac legaturile intre
noua celula si tren si mut mecanicul in celula noua.

InsertRight:

Similara cu InsertLeft (doar ca aici nu exista "caz de eroare"). 

Search:

Salvez argumentul comenzii SEARCH intr-un string. Creez un vector  de 
lungimea string-ului cautat cu inscriptiile intalnite prin parcurgerea 
trenului; cand vectorul de inscriptii atinge lungimea string-ului cautat, 
acesta functioneaza dupa principiul unei cozi. Am facut aceste operatii 
pentru ca nu stiu cate vagoane are trenul, deci nu as stii sa declar/aloc 
un string care sa contina toate inscriptiile trenului fara sa numar inainte
vagoanele.
Daca sirul cautat este gasit, mut mecanicul pe pozitia de unde incepe
acesta, avand grija sa sar peste locomotiva.

SearchLeft si SearchRight:

Functioneaza dupa acelasi principiu ca la Search, sunt modificate doar 
conditiile impuse de cerinta (cautarea se opreste la locomotiva, pozitia 
mecanicului, sensul de parcurgere).

Switch:

Parcurg coada incepand de la al doilea element.
c->inc este o lista. Fiecare celula parcursa va fi adaugata, pe rand, la 
inceputul acestei liste, c->inc. 
Modific apoi si pointerul c->sf, care acum trebuie sa indice vechiul
inceput al listei.

Execute:
Extrag din coada un element, pe care il compar cu posibilele comenzi pe care
le pot intalni in fisierul de input. Dupa de identific comanda, apelez 
functia corespunzatoare. Verific valoarea returnata (1/0; 0 = cod de eroare)
unde este cazul (functiile care aloca memorie dinamic).
