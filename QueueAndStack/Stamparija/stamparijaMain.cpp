#include "stamparija.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

int main (int argc, char *argv[]) {
  stamparija stampa;
  std::ifstream input{"nalozi.txt"};
  if(!input.is_open())
    return 1;
  unsigned brojKorisnika;
  input >> brojKorisnika;
  for(int i = 0; i < brojKorisnika; ++i){
    std::string korisnik;
    input >> korisnik;
    stampa.dodajKorisnika(korisnik);
  }
  input >> stampa.brzina();
  input.ignore(1000, '\n');
  std::string line;
  while(std::getline(input, line)){
    std::string imeKnjiga, imeKorisnik, vrijeme;
    unsigned brojStranica;
    std::istringstream stream{line};
    stream.ignore(1);
    std::getline(stream, imeKnjiga, '"');
    stream >> imeKorisnik >> brojStranica >> vrijeme;
    std::cout << vrijeme;
    unsigned minutes, hours;
    hours = std::stoul(vrijeme.substr(0, 2));
    minutes = std::stoul(vrijeme.substr(3, 2));
    class time vr(hours, minutes);
    nalog nal(imeKnjiga, imeKorisnik, brojStranica, vr);
    stampa.dodajNalog(nal);
  }
  stampa.obradi();
  return 0;
}
