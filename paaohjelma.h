/*******************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
 * Otsikkotiedot:
 * Tekijä: Noora Rautio
 * Opiskelijanumero: 0523629
 * Päivämäärä: 28/03/2021
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto: Tein tehtvän yksin, lähteenä kurssimateriaali ja itse tehdyt
 * viikkotehtävät. Kysyin apua assistentiltä.
 */
/*******************************************************************/
#define _XOPEN_SOURCE
#ifndef paaohjelma_h
#define paaohjelma_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct tiedot { // määritellään tietue ja sen sisältämät tiedot
    char tehtavan_nimi[10];
    int tehtavan_numero;
    int opiskelija;
    struct tm aika; 
    struct tiedot *pSeuraava; // tähän tallennetaan seuraavan tietueen osoite
} TIEDOT ;

typedef struct TehtavaData { // Tänne kerätään tiedot datan analysointivaiheessa
    char nimi[10];
    int yhteensa;
} DATA ;

typedef struct analyysi{ //tänne kerätään päiväanalyysin tiedot
    struct tm paivamaara;
    int suoritusmaara;
	struct analyysi *pSeuraava;
} ANALYYSI ;

int valikko();

#endif

/*******************************************************************/
/* eof */