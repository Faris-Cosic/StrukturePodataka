#pragma once
#include <string>
#include <queue>

class time {
  public:
    time(unsigned h = 0, unsigned m = 0) : hours(h), minutes(m) {}
    time& operator+=(const time&);
    time operator+(const time&);
    friend std::ostream& operator<<(std::ostream& ostr, const time&);
  private:
    unsigned hours;
    unsigned minutes;
};

class nalog {
  public:
    nalog(const std::string& imeKnjiga, const std::string& imeKorisnik, const size_t& brojStranica, const time& vrijeme)
      : imeKnjiga(imeKnjiga), imeKorisnik(imeKorisnik), brojStranica_(brojStranica), primljeno_(vrijeme) {}

    void setZavrseno(const time& vrijeme) {zavrseno = vrijeme;}
    unsigned brojStranica() {return brojStranica_;}
    std::string korisnik() {return imeKorisnik;}
    time primljeno() {return primljeno_;}

    friend std::ostream& operator<<(std::ostream& ostr, const nalog& nalog);

  private:
    std::string imeKnjiga;
    std::string imeKorisnik;
    size_t brojStranica_;
    time primljeno_;
    time zavrseno;
};

class stamparija {
  public:
    void dodajNalog(nalog nalog); 

    void dodajKorisnika(const std::string& korisnik);

    void obradi();

    unsigned& brzina() {return brzina_;}
  private:
    std::queue<nalog> nalozi;
    time vrijeme{8, 0};
    unsigned brzina_;
    std::vector<std::string> registrovani;
};


