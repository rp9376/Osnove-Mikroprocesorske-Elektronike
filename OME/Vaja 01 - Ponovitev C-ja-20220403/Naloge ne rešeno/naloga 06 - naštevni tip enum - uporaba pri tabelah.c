/*
		NAŠTEVNI TIP ENUM - UPORABA PRI TABELAH	

Pri tej nalogi bomo pokazali, kako lahko naštevni tip razumemo kot nekakšno kodiranje
informacije: s tem, ko se elemenentom naštevnega tipa priredi števila, smo pravzaprav
posamezen element naštevnega tipa "zakodirali" s številko. Ko torej delamo z elementi 
naštevnega tipa pravzaprav v ozadju delamo z nekakšnimi kodami, ki pa jih lahko uporabimo 
na različne načine. 

Pri tej vaji bomo pokazali, kako lahko te "številske kode" uporabimo za naslavljanje 
elementov v tabeli. To bomo storili na sledečem primeru: želimo ustvariti tabelo,
ki bo za nas hranila število praznikov po dnevih: torej, koliko praznikov pade na ponedeljek,
koliko na torek itd. Izhajali bomo iz naštevnega tipa, ki smo ga ustvarili pri prejšnji
nalogi in ga malenkost priredili za naše potrebe.


Sledite komentarjem spodaj in po potrebi dopolnite kodo.


*/

// Vključimo standardno C knjižnico za delo z vhodnimi/izhodnimi podatkovnimi tokovi.
#include <stdio.h>		// več na https://en.wikibooks.org/wiki/C_Programming/stdio.h


// Podobno kot prej, najprej definiramo naštevni tip z imeni vseh dni v tednu, vendar 
// tokrat malenkost drugače: na konec seznama dnevov dodamo še poseben element NUM_OF_WEEKDAYS!
// (glejte spodaj)
//
// Zakaj tako? Ta dodaten element NA KONCU SEZNAMA bo za nas hranil število dni v tednu!
// Glejte oštevilčenje spodaj. Vidite, da elementu NUM_OF_WEEKDAYS pripade število 7.
// Ravno toliko, kot je definiranih dni pred njim, saj se le-ti pričnejo šteti od 0 dalje.
//
// Definicija takega pomožnega "NUM_OF_" elementa je koristna, saj za nas hrani informacijo o tem,
// kako dolgo tabelo potrebujemo! Vrednost oz. "kodo" NUM_OF_WEEKDAYS bomo torej lahko uporabili
// že takoj pri definiciji tabele.

//              =0       =1        =2        =3       =4        =5       =6          =7     
typedef enum { Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday, NUM_OF_WEEKDAYS }  weekdays_enum_t;


// Sedaj pa pazite RAZLIKO glede na prejšnjo nalogo: sedaj sploh ne bomo definirali spremenljivke,
// ki bi hranila vrednost tipa "weekdays_enum_t"! (Tako kot smo v prejšnji nalogi definirali
// spremenljivko "day".)
//
// Sedaj bomo uporabljali zgolj elemente naštevnega tipa, torej "Monday", "Tuesday" itd. 
// Oziroma drugače: uporabljali bomo celoštevilske kode, ki pripradajo tem elementom.
// Kako jih bomo uporabljali? Tako, da bomo z njimi naslavljali celice v tabeli!
// Berite dalje in boste videli.

// Najprej moramo definirati tabelo, ki bo za nas hranila število praznikov po dnevih.
// Ker je število praznikov celo nenegativno število, je smiselno uporabiti tip "unsigned int".
// In poglejte, kako bomo definirali potrebno doližino tabele z NUM_OF_WEEKDAYS! 
unsigned int  prazniki_po_dnevih[NUM_OF_WEEKDAYS];

// Tako s pomočjo naštevnega tipa ustvarjate zelo elegantno in lepo berljivo kodo!
// Še bolj nazoren zgled sledi v nadaljevanju.


int main(void)
{
	
	// V glavnem programu pa sedaj sprogramirajmo vsebino tabele tako, da za nas
	// resnično hrani število praznikov po dnevih (številke so prave za leto 2022 :) ).
	
	// In kako pridejo sedaj v igro "kode" naštevnega tipa? Ker kode za "Monday", "Tuesday"
	// itd. tečejo od 0 dalje do 6, lahko elemente naštevnega tipa ("Monday", "Tuesday"...)
	// uporabimo kar neposredno za naslavljanje celice v tabeli! 
	//
	// Tako število praznikov za ponedeljek hranimo v tabeli na temle mestu: 
	prazniki_po_dnevih[Monday] 		= 1+1+1+1;

	// Element "Monday" je pravzaprav nekakšna koda, ki nam pove, kje v tabeli bomo hranili,
	// informacijo o številu praznikov na ponedeljek.

	// Vidite, da smo z definicijo naštevnega tipa pravzaprav hkrati definirali, na katerem
	// mestu v tabeli bomo hranili posamezno informacijo!
	
	// Torej vedno, kadar želimo nastavljati število praznikov na ponedeljek ali pa prebrati
	// število praznikov na ponedeljek, uporabimo tabelo prazniki_po_dnevih[] z indexom "Monday",
	// torej takole: prazniki_po_dnevih[Monday]. Tako se zagotovo ne bomo zmotili, na katerem
	// mestu hranimo infromacijo o praznikih na ponedeljek.
	

	// In podobno velja za preostale dni!
	prazniki_po_dnevih[DOPOLNI] 	= 1+1;		// prazniki na torek
	prazniki_po_dnevih[DOPOLNI] 	= 1;		// prazniki na sredo
	prazniki_po_dnevih[DOPOLNI] 	= 0;		// prazniki na četrtek
	prazniki_po_dnevih[DOPOLNI] 	= 0;		// prazniki na petek
	prazniki_po_dnevih[DOPOLNI] 	= 1+1;		// prazniki na soboto
	prazniki_po_dnevih[DOPOLNI] 	= 1+1+1;	// prazniki na nedeljo
	
	
	
	// In ko želimo prebrati število praznikov za posamezen dan, uporabimo
	// seveda enak princip.
	printf("število praznikov na ponedeljek: %d\n", prazniki_po_dnevih[DOPOLNI] 	);
	printf("število praznikov na torek: %d\n", 		prazniki_po_dnevih[DOPOLNI] 	);
	printf("število praznikov na sredo: %d\n", 		prazniki_po_dnevih[DOPOLNI] 	);
	printf("število praznikov na četrtek: %d\n", 	prazniki_po_dnevih[DOPOLNI] 	);
	printf("število praznikov na petek: %d\n", 		prazniki_po_dnevih[DOPOLNI] 	);
	printf("število praznikov na soboto: %d\n", 	prazniki_po_dnevih[DOPOLNI] 	);
	printf("število praznikov na nedeljo: %d\n", 	prazniki_po_dnevih[DOPOLNI] 	);
	
	
	
	// Tako vidite, kako vam lahko pametno definirani elementi naštevnega tipa 
	// pomagajo osmiliti naslavljanje celic v tabeli! Če ne bi uporabljali 
	// naštevnega tipa, potem bi npr. koda izgledala takole:
	//
	// prazniki_po_dnevih[3] = 1;		
	//
	// Je indeks 3 za sredo ali za četrtek? Ves čas morate potem biti pozorni,
	// na katerih mestih v tabeli hranite informacijo. Koda tako postane dovzetna
	// za napake, saj berljivost kode ni več tako dobra in zahteva naš napor, 
	// da sledite pomenom številskih indeksov!
	
	
	// NAUK: kadar v tabeli hranite različne informacije, je smiselno uporabiti 
	// naštevni tip, da si namesto vas zapomni, v kateri celici hranite posamezno informacijo.
	
	// Pri programiranju Miškota bomo tak pristop uporabili pri programiranju 
	// funkcij za delo z LEDicami in tipkami.
	
	
	// V naslednji nalogi pa si bomo ogledali, kako lahko spremenljivko naštevnega
	// tipa uporabimo, da za nas hrani pomembno informacijo o sistemu.
	
	
    // In še zaključimo funkcijo main().
	return 0;
	
	
}