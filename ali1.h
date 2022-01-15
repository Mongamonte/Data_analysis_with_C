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
#ifndef ali1_h
#define ali1_h

#include "paaohjelma.h"

void TiedostoNimi(char * fname);

void KirjoitaTiedosto(DATA * pTbl, char * tNimi, TIEDOT * pA);

void KirjoitaPaivaAnalyysi(ANALYYSI * pA1, char * nNimi);

#endif

/*******************************************************************/
/* eof */