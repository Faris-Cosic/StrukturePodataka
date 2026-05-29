# Zadatak 2

Implementirati TODO aplikaciju koja čuva informacije o zadacima i obavezama
korisnika. Za implementaciju koristiti dvostruko linkanu listu koju ste
implementirali kao prvi zadatak. Ako implementacija liste nije kompletna,
dozvoljeno je uzeti std::list.

Ako ocijenite da je potrebno, možete dodati nove metode u listu koji bi
olakšali ovaj zadatak.

Prioritet zadatka određuje njegovom pozicijom u listi (viša pozicija =
veći prioritet).

Potrebno je u programu instancirati **dvije** odvojene liste:

1. Listu aktivnih zadataka
2. Listu obrisanih zadataka (`Korpa`)

Jedan zadatak (podaci u čvoru) je opisan sa minimalno sljedećim informacijama:

1. Kratko ime zadatka (služi i za pretragu)
2. Opis zadatka (opis može biti prazan)

Prilikom pokretanja programa, korisniku se ispisuje meni sa sljedećim opcijama:

* Dodaj novi zadatak
* Pomjeri zadatak gore
* Pomjeri zadatak dolje
* Pomakni zadatak
* Obriši zadatak
* Vrati obrisani zadatak (Undo)
* Prikaži aktivne zadatke
* Prikaži korpu

Svaka od opcija je opisana ispod:

**Dodaj novi zadatak** - Učitava informacije o zadatku sa standardnog ulaza i dodaje zadatak na **kraj** liste aktivnih zadataka (najniži prioritet).

**Pomjeri zadatak gore** - Korisnik unosi ime zadatka ili dio imena zadatka. Program pronalazi taj zadatak i mijenja mu poziciju sa zadatkom koji se nalazi neposredno *ispred* njega u listi. (Povećava mu prioritet). Ako bi bilo više zadataka istog imena uzeti prvi koji se pronađe.

**Pomjeri zadatak dolje** - Korisnik unosi ime zadatka. Program pronalazi taj zadatak i mijenja mu poziciju sa zadatkom koji se nalazi neposredno *iza* njega u listi. (Smanjuje mu prioritet).

**Pomakni zadatak** - Korisnik unosi ime zadatka i broj za koliko mjesta gore (pozitivan broj) ili dole (negativan broj) pomjera zadatak u listi. Staviti zadatak na kraj ili na pocetak liste ako bi korisnik unio broj koji je preveliki ili premali.

**Obriši zadatak** - Korisnik unosi ime zadatka. Program isijeca taj zadatak iz liste aktivnih zadataka i prebacuje ga (umeće) na **početak** (vrh) liste `Korpa`.

**Vrati obrisani zadatak (Undo)** - Program uzima posljednje obrisani zadatak sa vrha `Korpe`, isijeca ga iz nje, i vraća ga na **kraj** liste aktivnih zadataka.

**Prikaži aktivne zadatke** - Ispisuje sve zadatke u redoslijedu u kojem se trenutno nalaze u listi aktivnih.

**Prikaži korpu** - Ispisuje sve zadatke koji su obrisani, počevši od nedavno obrisanih.

Ako neke opcije nisu dovoljno precizne u formulaciji zadatka, slobodno procijenite šta bi bio najbolji izbor u tom slučaju i implementirajte tako.

### Dodatni zadatak
Proizvoljno, studentima se preporučuje da implementiraju mehanizam kojim bi se
obje liste (Aktivni i Korpa) spremile u datoteku, i pri narednom pokretanju
aplikacije ponovo učitale, kako bi se program mogao nastaviti koristiti
nesmetano.

