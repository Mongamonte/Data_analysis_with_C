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
#include "ali1.h"

void TiedostoNimi(char * fname) { //Aliohjelma kysyy käyttäjältä halutun tiedoston nimen
    printf("Anna tiedoston nimi: ");
    scanf("%s", fname);   
    return;
}

void KirjoitaTiedosto(DATA * pTbl, char * tNimi, TIEDOT * pA) {
    FILE *tiedosto;
	TIEDOT *ptr=pA;
    int i = 0;	

	if (ptr == NULL) {
		printf("Ei tulostettavaa, suorita ensin päiväanalyysi.\n");
		printf("\n");
		return;
	}

    if ((tiedosto = fopen (tNimi, "w")) == NULL) {
        perror ("Tiedostoon kirjoittaminen epäonnistui");
        exit(1);
    }
	
	printf("\n");

    fprintf(tiedosto, "Tehtävä;Lkm\n" );
    for (i=0; i<60; i++) {
        fprintf(tiedosto, "%s;%d\n", pTbl[i].nimi, pTbl[i].yhteensa );
    }
	
    fclose(tiedosto);
    return;
}

void KirjoitaPaivaAnalyysi(ANALYYSI * pA1, char * nNimi) {
	FILE *tiedosto;
	ANALYYSI * ptr1;
	char buf[255];

    if ((tiedosto = fopen (nNimi, "w")) == NULL) {
        perror ("Tiedostoon kirjoittaminen epäonnistui");
        exit(1);
    }		
	ptr1=pA1;
	if (ptr1 == NULL) {
		printf("Ei tulostettavaa, suorita ensin päiväanalyysi.\n");
		printf("\n");
		return;
	}
	fprintf(tiedosto, "Pvm;Lkm\n" );
	ptr1=pA1;
	while (ptr1 != NULL) {
		strftime(buf, sizeof(buf), "%d.%m.%Y", &ptr1->paivamaara);
		fprintf(tiedosto, "%s;%d\n", buf, ptr1->suoritusmaara);
		ptr1 = ptr1->pSeuraava;
	}

	printf("\n");
    fclose(tiedosto);
    return;
}

/*******************************************************************/
/* eof */