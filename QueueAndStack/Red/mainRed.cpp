#include "Red.hpp"
#include <iostream>


int main (int argc, char *argv[]) {
  red<int> r;
  r.push(2).push(3).push(4);
  std::cout << "\nZadnji: " << r.back() << ", Prednji: " << r.front();
  r.pop();
  std::cout << "\nIzbacen prednji, novi prednji: " << r.front();
  red<int> r1 = r;
  red<int> r2(r1);
  red<int> r3({1, 2, 3});


  r.front() = 10;
  std::cout << "\nPromjenjen prednji u 10: " << r.front();



  return 0;
}
