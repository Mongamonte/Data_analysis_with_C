# CT60A2500 C-ohjelmoinnin perusteet
# Otsikkotiedot: Harjoitustyö Makefile
# Tekijä: Noora Rautio
# Opiskelijanumero: 0523629
# Päivämäärä: 28/03/2021
# Yhteistyö ja lähteet, nimi ja yhteistyön muoto: Tein makefilen yksin, lähteenä kurssimateriaali. 

paaohjelma.exe: paaohjelma.o ali1.o ali2.o 
	gcc -o paaohjelma.exe ali1.o ali2.o paaohjelma.o
paaohjelma.o: paaohjelma.c paaohjelma.h ali1.h ali2.h
	gcc paaohjelma.c -c -std=c99 -Wall -pedantic
ali1.o: ali1.c ali1.h paaohjelma.h
	gcc ali1.c -c -std=c99 -Wall -pedantic
ali2.o: ali2.c ali2.h paaohjelma.h
	gcc ali2.c -c -std=c99 -Wall -pedantic
