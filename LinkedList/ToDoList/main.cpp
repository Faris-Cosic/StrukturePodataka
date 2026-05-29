#include "../DoubleLinkedList/DoubleLinkedList.hpp"
#include <iostream>
#include <string>


struct zadatak {
  std::string ime;
  std::string opis;
};

void moveUp(DoubleLinkedList<zadatak>& lista, const std::string& z1);
void moveDown(DoubleLinkedList<zadatak>& lista, const std::string& z1);
void moveNumber(DoubleLinkedList<zadatak>& lista, const std::string& z1, const int& number);
DoubleLinkedList<zadatak>::iterator find(const DoubleLinkedList<zadatak>& lista, const std::string& z);

int main (int argc, char *argv[]) {
  DoubleLinkedList<zadatak> aktivni;
  DoubleLinkedList<zadatak> korpa;
  unsigned izbor;
  do {
    std::string ime, opis;
    std::cout << "\n\n\nUnesi broj za opciju. \n"
      "1. Dodaj novi zadtak\n"
      "2. Pomjeri zadatak gore\n"
      "3. Pomjeri zadatak dolje\n"
      "4. Pomakni zadatak\n"
      "5. Obriši zadatak\n"
      "6. Vrati obrisani zadatak (undo)\n"
      "7. Prikazi aktivne zadatke\n"
      "8. Prikaži korpu\n"
      "9. Exit\n"
      "Izbor: ";
    std::cin >> izbor;
    std::cout << std::endl;
    zadatak zad;
    switch (izbor) {
      case 1:
        std::cout << "Ime zadatka: "; 
        std::cin >> zad.ime;
        std::cin.ignore(100, '\n');
        std::cout << "Opis zadatka: ";
        std::getline(std::cin, zad.opis);
        aktivni.push_back(zad);
        break;
      case 2:{
               std::cout <<  "Ime zadatka: ";
               std::cin >> ime;
               moveUp(aktivni, ime);
               std::cout << "Zadatak pomjeren 1 mjesto gore.\n";
               break;
             }
      case 3: 
             {
               std::cout << "Ime zadatka: ";
               std::cin >> ime;
               moveDown(aktivni, ime);
               std::cout << "Zadatak promjeren 1 mjesto dole.\n";
               break;
             }
      case 4:{
               std::cout << "Ime zadatka: ";
               std::cin >> ime;
               int broj;
               std::cout << "Broj mjesta za pomaknuti: ";
               std::cin >> broj;
               if(broj == 0)
                 break;
               if(broj > 0){
                 for(int i = 0; i < broj; ++i){
                   moveUp(aktivni, ime);
                 }
                 std::cout << "Zadatak pomjeren " << broj << " mjesta gore.\n";
               }
               else {
                 for(int i = 0; i > broj; --i){
                   moveDown(aktivni, ime);
                 }
                 std::cout << "Zadatak pomjeren " << broj << " mjesta dole.\n";


               }
               break;
             }

      case 5:{
               std::cout << "Ime zadatka: ";
               std::cin >> ime;
               auto selected = find(aktivni, ime);
               if(selected == aktivni.end()){
                 std::cout << "Zadatak nije pronadjen!";
                 break;
               }
               korpa.push_front(*selected);
               aktivni.erase(selected);
               std::cout << "Izbrisan zadatak.\n";
               break;
             }
      case 6:{
               if(korpa.empty()){
                 std::cout << "Nema obrisanih zadataka!";
                 break;
               }
               aktivni.push_back(korpa.front());
               korpa.pop_front();
               std::cout << "Zadatak vraćen.\n";
               break;
             }
      case 7:{
               if(aktivni.empty()){
                 std::cout << "Lista je prazna!\n";
                 break;
               }
               std::cout << "\n\nAktivni zadaci:\n";
               int count = 1;
               for(auto it = aktivni.begin(); it != aktivni.end(); ++it){
                 std::cout << count << ". " << it->ime << std::endl;
                 count++;
               }
               break;
             }
      case 8:{
               if(korpa.empty()){
                 std::cout << "Korpa je prazna!\n";
                 break;
               }
               std::cout << "\n\nKorpa:\n";
               int count = 1;
               for(auto it = korpa.begin(); it != korpa.end(); ++it){
                 std::cout << count << ". " << it->ime << std::endl;
               }
               break;
             }
      default:
             std::cout << "Nevalidan unos!\n";
    }

  }while(izbor != 9);

  return 0;
}

DoubleLinkedList<zadatak>::iterator find(const DoubleLinkedList<zadatak>& lista, const std::string& z){
  for(auto it = lista.begin(); it != lista.end(); ++it){
    if(it->ime == z){
      return it;
    }
  }
  return lista.end();
}


void moveUp(DoubleLinkedList<zadatak>& lista, const std::string& zad){
  auto it = find(lista, zad);
  if(it == lista.begin())
    return;
  auto prevIt = it;
  --prevIt;
  std::swap(*it, *prevIt);
}

void moveDown(DoubleLinkedList<zadatak>& lista, const std::string& zad){
  auto it = find(lista, zad);
  if(it == lista.end())
    return;
  auto nextIt = it;
  ++nextIt;
  if(nextIt == lista.end())
    return;
  std::swap(*it, *nextIt);
}

void moveNumber(DoubleLinkedList<zadatak>& lista, const std::string& zad, const int& number){
  auto it = find(lista, zad);
  if(it == lista.end() || number == 0)
    return;
  if(number > 0){
    for(int i = 0; i < number; ++i){
      if(it == lista.begin())
        break;
      auto prevIt = it;
      --prevIt;
      std::swap(*it, *prevIt);
      it = prevIt;
    }
  }
  else {
    for(int i = 0; i > number; --i){
      if(it == lista.end())
        break;
      auto nextIt = it;
      ++nextIt;
      std::swap(*it, *nextIt);
      it = nextIt;
    }
  }
}

