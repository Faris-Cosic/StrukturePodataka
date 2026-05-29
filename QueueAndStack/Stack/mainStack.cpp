#include "Stack.hpp"
#include <iostream>

int main (int argc, char *argv[]) {
  stack<int> s;
  s.push(1);
  s.push(2);
  s.push(3);
  std::cout << "Elementi u stacku: 1, 2, 3\nTop: " << s.top();
  s.pop();
  std::cout << "\nPop: " << s.top();
  s.top() = 50;
  std::cout << "\nPromjena top, Top: " << s.top();

  return 0;
}

