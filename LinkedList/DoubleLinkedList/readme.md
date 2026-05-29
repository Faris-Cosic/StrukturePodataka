# Zadatak 1

Implementirati generički kontejner DoubleLinkedList.
Neophodno je implementirati sve deklarisane metode da bi svi testovi uspješno prošli.
Za način implementacije svakog od metoda provjeriti odgovarajući test gdje je navedeno ponašanje svakog od metoda.
Napisati testni program u fajlu main.cpp gdje je neophodno testirati svaki od metoda, te uspostaviti analogiju sa std::list kontejnerom.

## Kako koristiti skriptu run_tests.sh

Skripta `run_tests.sh` omogućava automatsko kompajliranje i pokretanje testova:

### Pokretanje svih testova:
```bash
./run_tests.sh
```
Ova komanda će pokrenuti sve testove redom i prikazati sažetak rezultata.

### Pokretanje specifičnog testa:
```bash
./run_tests.sh 01
```
Ova komanda će pokrenuti samo Test01.cpp (zamijeni 01 sa 02, 03, itd. za druge testove).

**Napomena:** Testovi se kompajliraju sa `-fsanitize=address` flagom za detekciju memorijskih grešaka.

## Metode koje lista treba da ima

Vaš DoubleLinkedList kontejner treba da implementira sljedeće metode:

### Konstruktori i destruktor:
- Podrazumijevani konstruktor
- Konstruktor kopije
- Move konstruktor
- Destruktor

### Operatori dodjele:
- Operator dodjele kopiranjem
- Move operator dodjele

### Dodavanje elemenata:
- `push_front` - dodaje element na početak liste
- `push_back` - dodaje element na kraj liste
- `insert` - ubacuje element na određenu poziciju

### Uklanjanje elemenata:
- `pop_front` - uklanja element sa početka liste
- `pop_back` - uklanja element sa kraja liste
- `erase` - uklanja element(e) na određenoj poziciji
- `remove_if` - uklanja sve elemente koji zadovoljavaju uslov
- `clear` - uklanja sve elemente iz liste

### Pristup elementima:
- `front` - vraća referencu na prvi element
- `back` - vraća referencu na posljednji element

### Informacije o listi:
- `size` - vraća broj elemenata u listi
- `empty` - provjerava da li je lista prazna

### Iteratori:
- `begin` - iterator na početak liste
- `end` - iterator na kraj liste (iza posljednjeg elementa)
- Iterator klasa sa operatorima: `*`, `->`, `++`, `--`, `==`, `!=`

### Ostale metode:
- `reverse` - obrće redoslijed elemenata u listi
- `find` - traži element u listi
