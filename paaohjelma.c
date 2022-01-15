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
#include "paaohjelma.h"
#include "ali1.h"
#include "ali2.h"
 
int valikko() {
	int nValinta = 0;
	printf("1) Lue tiedosto\n");
	printf("2) Analysoi tiedot\n");
	printf("3) Tulosta tulokset\n");
	printf("4) Suorita päiväanalyysi\n");
	printf("5) Tulosta päiväanalyysin tulokset\n");
	printf("6) Tyhjennä tuloslista\n");
	printf("0) Lopeta\n");
	printf("Valintasi: ");
	scanf("%d", &nValinta);
	return nValinta;
}

int main(void) { 
    TIEDOT * pAlku = NULL;
    DATA pTaulukko[60];
    ANALYYSI * pTaulu = NULL;
	int valinta;
    char merkki;
    char szNimi[60];
	int tarkistus = 0; //Tämä asetetaan arvoon 1. valikon kohdassa 2., jolla varmistetaan tietojen analysointi ennen tulostusta 
 	
	valinta = valikko();
	while (valinta != 0) {
		if (valinta == 1) { // avaa tiedoston, lukee tiedoston, varaa muistin, vie tiedot linkitettyyn listaan
            if (pAlku != NULL){
				pAlku = VapautaMuisti(pAlku);
			}
			TiedostoNimi(szNimi);
            pAlku = LueTiedot (pAlku, szNimi);
        } else if (valinta == 2) {
			tarkistus = AnalysoiTiedot(pAlku, pTaulukko); 
        } else if (valinta == 3 && tarkistus == 0) {
			printf("Ei tulostettavaa, tee ensin päiväanalyysu.\n");
			printf("\n");
		} else if (valinta == 3 && tarkistus == 1) {
	        printf("Tulosta tiedostoon (k/e): ");
	        scanf("%s", &merkki);
	        if ( merkki == 'k' ){ // kysy käyttäjältä tiedoston nimi aliohjelmassa ja tallenna sinne
	            TiedostoNimi(szNimi);
	            KirjoitaTiedosto(pTaulukko, szNimi, pAlku);
	        } else if ( merkki == 'e' ) { //tulostaa tulokset näytölle
	            TulostaTulokset(pTaulukko, pAlku);
	        } else {
	            printf("Virheellinen syöten"); //virhe mikäli käyttäjä antaa jonkun muun syötteen kuin e tai k
            }    
		} else if (valinta == 4) {            
            pTaulu = PaivaAnalyysi(pTaulu, pAlku);
        } else if (valinta == 5) {
			printf("Tulosta tiedostoon (k/e): ");
            scanf("%s", &merkki);
                if ( merkki == 'k' ){ // kysy käyttäjältä tiedoston nimi aliohjelmassa ja tallenna sinne
                    TiedostoNimi(szNimi);
                    KirjoitaPaivaAnalyysi(pTaulu, szNimi);
                } else if ( merkki == 'e' ) { //tulostaa tulokset näytölle
                    TulostaPaivaAnalyysi(pTaulu);
                } else {
                    printf("Virheellinen syöten"); //virhe mikäli käyttäjä antaa jonkun muun syötteen kuin e tai k
                }
         } else if (valinta == 6) {
            pTaulu = TyhjennaLista(pTaulu);
			printf("\n");
		 } else if (valinta == 0) {
			printf("Kiitos ohjelman käytöstä.\n");
			VapautaMuisti(pAlku);
			pTaulu = TyhjennaLista(pTaulu);
			printf("\n");
		 } else {
            printf("Tuntematon valinta, yritä uudestaan.\n");
			printf("\n");
		}

		valinta = valikko();
    } //alkuehdon sulkeva kaari

	printf("Kiitos ohjelman käytöstä.\n");
	pAlku = VapautaMuisti(pAlku);
	pTaulu = TyhjennaLista(pTaulu);
	printf("\n");

    return 0;
}

/*******************************************************************/
/* eof */