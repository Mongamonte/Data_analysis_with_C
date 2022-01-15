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
#ifndef ali2_h
#define ali2_h

#include "paaohjelma.h"
#include <string.h>

TIEDOT * LueTiedot (TIEDOT * pA, char * tNimi);

TIEDOT * VapautaMuisti(TIEDOT * pAlku);

int AnalysoiTiedot (TIEDOT * pA, DATA * pTbl);

void TulostaTulokset(DATA * pTbl, TIEDOT * pA);

ANALYYSI * PaivaAnalyysi(ANALYYSI * pA1, TIEDOT * pA);

void TulostaPaivaAnalyysi(ANALYYSI * pA1);

ANALYYSI * TyhjennaLista(ANALYYSI * pA1);

#endif

/*******************************************************************/
/* eof */