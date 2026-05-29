#include "stamparija.hpp"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <string>

class time& time::operator+=(const time& other) {
  unsigned totalMinutes = (minutes + other.minutes);
  hours = (hours + other.hours + totalMinutes / 60) % 24;
  minutes = totalMinutes % 60;
  return *this; 
}

class time time::operator+(const time& other) {
  return *this += other;
}

std::ostream& operator<<(std::ostream& ostr, const class time& vrijeme){
  std::string formatHours = vrijeme.hours < 10 ? (std::string("0") + std::to_string(vrijeme.hours)) : std::to_string(vrijeme.hours);
  std::string formatMinutes = vrijeme.minutes < 10 ? (std::string("0") + std::to_string(vrijeme.minutes)) : std::to_string(vrijeme.minutes);
  ostr << formatHours << ":" << formatMinutes;
  return ostr;
}

std::ostream& operator<<(std::ostream& ostr, const nalog& nalog){
  ostr << "Knjiga: " << nalog.imeKnjiga  << std::endl 
    << "Korisnik: " << nalog.imeKorisnik << std::endl
    << "Zaprimljeno: " << nalog.primljeno_ << std::endl
    << "Završeno: " << nalog.zavrseno << std::endl;
  return ostr;
}

void stamparija::obradi() {
  vrijeme = nalozi.front().primljeno();
  while(!nalozi.empty()){
    auto& trenutni = nalozi.front();
    unsigned vrijemeStampeMinute = std::ceil(double(trenutni.brojStranica()) / brzina_);
    class time vrijemeStampe(0, vrijemeStampeMinute);
    vrijeme += vrijemeStampe;
    trenutni.setZavrseno(vrijeme);
    std::cout << trenutni << std::endl;
    nalozi.pop();
  }
}

void stamparija::dodajNalog(nalog nalog){  
  if(std::find(registrovani.begin(), registrovani.end(), nalog.korisnik()) != registrovani.end()){
    nalozi.push(nalog);
  }
}


void stamparija::dodajKorisnika(const std::string& korisnik){
  registrovani.push_back(korisnik);
}

