#include <iostream>
#include "bigint.hpp"

bigint fib(const bigint& n); // O(n)
bigint factorial(bigint n); // O(n)


int main (int argc, char *argv[]) {
  std::string s1, s2;
  std::cout << "Unesi 1. broj: ";
  std::cin >> s1;
  std::cout << "Unesi 2. broj: ";
  std::cin >> s2;
  bigint broj1(s1);
  bigint broj2(s2);

  std::cout << "Zbir: " << broj1 + broj2 << std::endl;
  std::cout << "Razlika: " << broj1 - broj2 << std::endl;
  std::cout << "Prozivod: " << broj1 * broj2 << std::endl;
  std::cout << "Količnik: " << broj1 / broj2 << std::endl;
  std::cout << "Ostatak pri dijeljenju: " << broj1 % broj2 << std::endl;
  std::cout << "50-ti Fibonačijev broj: " << fib(50) << std::endl;
  std::cout << "30!: " << factorial(30) << std::endl;

    

  return 0;
}




bigint fib(const bigint& n){
  if(n < 1)
    throw std::invalid_argument("Error, invalid n!");
  bigint a("0");
  bigint b(1);
  for(bigint i = (long)0; i < n; ++i){
    bigint temp = b;
    b = a + b;
    a = temp;
  }
  return a;
}

bigint factorial(bigint n){
  if (n < long(0)) 
    throw std::invalid_argument("Error, only n >= 0");
  if(n == (long)0)
    return 1;
  bigint result = n;
  --n;
  while(n > 1){
    result *= n;
    --n;
  }
  return result;
}

