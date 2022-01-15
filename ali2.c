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
#include "ali2.h"

TIEDOT * LueTiedot (TIEDOT * pA, char * tNimi) { 
    FILE * tiedosto;
    TIEDOT * pLoppu = NULL;
    TIEDOT * ptr;
    TIEDOT * pUusi;
    char buf[255];
    char buf2[255];
    char rivi[200];
    char *t1, *t2, *t3;
    char *p1, *p2, *p3;

    if ((tiedosto = fopen(tNimi, "r")) == NULL) { //tiedoston avaaminen
        perror("Tiedoston avaaminen epäonnistui\n") ;
        exit(1);
    }

    fgets(rivi, 200, tiedosto); //luetaan tiedostosta ensimmäinen rivi (otsikkotiedot) pois

    while ((fgets(rivi, 200, tiedosto)) != NULL) { //luetaan tiedostoa riveittäin, pilkotaan osiin strtokilla
        t1 = strtok (rivi, "/"); //päivänumero
        t2 = strtok (NULL, "/"); //kuukausi
        t3 = strtok (NULL, ","); //vuosi
        p1 = strtok (NULL, ":"); //tunti
        p1 = strtok (NULL, ";"); //minuutti
        p1 = strtok (NULL, ";");  //tehtavan nimi 
        p2 = strtok (NULL, ";"); //tehtavan numero
        p3 = strtok (NULL, "\n"); //käyttäjän ID.

        if ((pUusi = (TIEDOT*)malloc(sizeof(TIEDOT))) == NULL ) { //muistin varaus
            perror("Muistin varaus epäonnistui");
            exit (1);
        }

        if ( p1 != NULL) {  //luetaan tehtävän nimet
        strcpy(pUusi->tehtavan_nimi, p1);
        }

        struct tm tm; //luetaan aika
		memset (&tm, 0, sizeof(tm));

        tm.tm_mday = atoi(t1);
        tm.tm_mon = atoi(t2)-1 ; 
        tm.tm_year = 2000 + atoi(t3) - 1900;

        pUusi->aika = tm;
        pUusi->tehtavan_numero = atoi(p2);
        pUusi->opiskelija = atoi(p3);
        pUusi->pSeuraava  = NULL;

        if (pA == NULL){
            pA = pUusi;
            pLoppu = pUusi;
        } else {
            pLoppu->pSeuraava = pUusi;
            pLoppu = pUusi;
            }
        }

        int count = 0; //laskuri palautusten määrälle   
        ptr = pA;    
        while (ptr != NULL) { //lasketaan laskurin avulla suoritetut tehtävät
            ptr = ptr->pSeuraava;
            count++;
        }
        
        strftime(buf, sizeof(buf), "%d.%m.%Y", &pA->aika); //tulostetaan aika ja muut halutut tiedot
        strftime(buf2, sizeof(buf2), "%d.%m.%Y", &pLoppu->aika);
        printf("Yhteensä %d palautusta %s - %s väliseltä ajalta.\n", count, buf, buf2);
        printf("\n");

        fclose(tiedosto);
        
        return pA;
    }

TIEDOT * VapautaMuisti(TIEDOT * pAlku) {
	if (pAlku != NULL) {
		TIEDOT * ptr = pAlku;
    	while (ptr != NULL) {
        	pAlku = ptr->pSeuraava;
        	free(ptr);
        	ptr = pAlku;
    	}
	}
    return pAlku;
}

int AnalysoiTiedot (TIEDOT * pA, DATA * pTbl) {
    TIEDOT * ptr = pA;
    int i = 0;
    int c = 0;
    int paikka = 0 ;
    int summa = 0;
   
    if (ptr == NULL ) { //virhe mikäli tiedostoa ei ole luettu ensin
        printf("Ei analysoitavaa, lue ensin palautustiedosto.\n");
		printf("\n");
        return 0;
    } 

    for (i=0; i < 60; i++) { //alustetaan taulukko
        strcpy(pTbl[i].nimi, "Tyhjä");
        pTbl[i].yhteensa = 0;
    }

    while (ptr != NULL ) { // lasketaan suoritettujen tehtävien määrät
        paikka = ptr->tehtavan_numero;
        pTbl[paikka-1].yhteensa++;
        strcpy(pTbl[paikka-1].nimi, ptr->tehtavan_nimi);
        ptr = ptr->pSeuraava; 
    }

    for (i=0; i < 60; i++){ //lasketaan tehtävien kokonaismäärä c-muuttujan avulla
        summa = summa + pTbl[i].yhteensa;
        if ( pTbl[i].yhteensa == 0) {
            continue;
        } else {
            c++ ;
        }
    }

    printf("Palautuksia oli yhteensä %d, %d eri tehtävässä, keskimäärin %d per tehtävä.\n", summa, c, summa/c );
    printf("\n");

    return 1;
}

void TulostaTulokset(DATA * pTbl, TIEDOT * pA) {
	TIEDOT * ptr = pA;
    int i=0;
	
	if (ptr == NULL) {
		printf("Ei tulostettavaa, suorita ensin päiväanalyysi.\n");
		printf("\n");
		return;
	}

	if (pTbl != NULL ) {
	printf("Tehtävä;Lkm\n");
		for (i=0; i<60; i++) {
	    	printf("%s;%d\n", pTbl[i].nimi, pTbl[i].yhteensa);
	} }
		
    printf("\n");
    return;
}

ANALYYSI * PaivaAnalyysi(ANALYYSI * pA1, TIEDOT * pA) {
    TIEDOT * ptr = pA;
	ANALYYSI * pUusi;
	ANALYYSI * pLoppu = NULL;
	ANALYYSI * ptr1 = pA1;

    struct tm alku;
	struct tm loppu; // muuttujat kysytyn ajan alku- ja loppuhetkille
    time_t alkuEpoch, loppuEpoch, muistissaEpoch, Epoch1, Epoch2; //Epocheja kysytyille ajoille ja avuksi
	int summa = 0;
    
    char buf_alku[255]; //puskuri kysytylle alkupäivämäärälle
    char buf_loppu[255]; // puskuri kysytylle loppupävämäärälle
	char buf_puskuri[255];

    memset(&alku, 0, sizeof(alku)); //alustetaan
    memset(&loppu, 0, sizeof(loppu));
	memset(&muistissaEpoch, 0, sizeof(muistissaEpoch));
	
	if (ptr == NULL) {
		printf("Ei analysoitavaa, lue ensin palautustiedosto.\n");
		printf("\n");
		return pA1;
	}
	
    printf("Anna alku pvm (pp.mm.vvvv): ");
	scanf("%s", buf_alku);
    strptime(buf_alku, "%d.%m.%Y", &alku);
	alkuEpoch = mktime(&alku);
	muistissaEpoch = mktime(&alku);
	
    printf("Anna loppu pvm (pp.mm.vvvv): ");
    scanf("%s", buf_loppu);
    strptime(buf_loppu, "%d.%m.%Y", &loppu);    
    loppuEpoch = mktime(&loppu);
	
	while (alkuEpoch <= loppuEpoch) { //alustetaan uusi linkitetty lista päivämäärätiedoilla

	if ((pUusi = (ANALYYSI*)malloc(sizeof(ANALYYSI))) == NULL ) { //muistin varaus
	    perror("Muistin varaus epäonnistui");
	    exit (1);
	    }

	pUusi->paivamaara = alku;
	alku.tm_mday = alku.tm_mday + 1;
	pUusi->suoritusmaara = 0;
	alkuEpoch = alkuEpoch + 24*60*60; //toimii laskurina while loopille
	
	if (pA1 == NULL){
		pA1 = pUusi;
		pLoppu = pUusi;
	    } else {
		pLoppu->pSeuraava = pUusi;
		pLoppu = pUusi;
	    }
	} 

	memset(&Epoch1, 0, sizeof(Epoch1));
	memset(&Epoch2, 0, sizeof(Epoch2));

	ptr1=pA1; //analysoidaan tehtävien suoritusmäärät
	while (ptr1 != NULL) {
		if (ptr != NULL) { //tämä haara, kun alkuperäisellä listalla on vielä solmuja
			while (ptr1 != NULL && ptr != NULL){
				Epoch1 = mktime(&ptr->aika);
				Epoch2 = mktime(&ptr1->paivamaara);		
				if (Epoch1 < Epoch2) {
					ptr = ptr->pSeuraava;
				} else if (Epoch1 == Epoch2){
					summa++;
					ptr1->suoritusmaara++;
					ptr=ptr->pSeuraava;
				} else if (Epoch1 > Epoch2) {
					ptr1 = ptr1->pSeuraava;
				}}}
		if (ptr == NULL) { //tämä haara, kun alkuperäisellä listalla ei ole solmuja
			Epoch2 = mktime(&ptr1->paivamaara);
			ptr1 = ptr1->pSeuraava;
		}	
	} 					 		

	strftime(buf_puskuri, sizeof(buf_puskuri), "%d.%m.%Y", localtime(&muistissaEpoch));
	strftime(buf_loppu, sizeof(buf_loppu), "%d.%m.%Y", localtime(&loppuEpoch));
	printf("Palautuksia oli yhteensä %d aikavälillä %s - %s.\n", summa, buf_puskuri, buf_loppu);
    printf("\n");
    return pA1;
}

void TulostaPaivaAnalyysi(ANALYYSI * pA1) {
	ANALYYSI * ptr1;
	char buf[255];
    
	ptr1=pA1;
	if (ptr1 == NULL) {
		printf("Ei tulostettavaa, suorita ensin päiväanalyysi.\n");
		printf("\n");
		return;
	}
	printf("Pvm;Lkm\n" );
	while (ptr1 != NULL) {
		strftime(buf, sizeof(buf), "%d.%m.%Y", &ptr1->paivamaara);
		printf("%s;%d\n", buf, ptr1->suoritusmaara);
		ptr1 = ptr1->pSeuraava;
	}
	printf("\n");
    return;
}

ANALYYSI * TyhjennaLista(ANALYYSI * pA1) {
	if (pA1 != NULL) {
		ANALYYSI * ptr1 = pA1;
    	while (ptr1 != NULL) {
        	pA1 = ptr1->pSeuraava;
        	free(ptr1);
        	ptr1 = pA1;
    	}
	}
    return pA1;
}


/*******************************************************************/
/* eof */