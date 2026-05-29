#include "DoubleLinkedList.hpp"
#include <iostream>

template <typename T>
std::ostream& operator<<(std::ostream& ostr, DoubleLinkedList<T>& lista);

int main(int argc, char* argv[]) {
  // Nema smetnje da priložite jedan ili više svojim main failova koje
  // ste koristili da isprobate listu.
  DoubleLinkedList<int> lista;
  lista.push_back(1);
  lista.push_back(2);
  lista.push_back(3);
  lista.insert(lista.end(), 5);
  lista.insert(lista.end(), 10);
  lista.erase(lista.begin());
  std::cout << lista << std::endl;
  lista.remove_if([](const int& v1){
      return v1 > 4; 
      });
  std::cout << lista << std::endl;
  lista.push_back(3);
  lista.push_front(22);
  lista.reverse();
  std::cout << lista << std::endl;
}

template <typename T>
std::ostream& operator<<(std::ostream& ostr, DoubleLinkedList<T>& lista){
  for(auto it = lista.begin(); it != lista.end(); ++it){
    ostr << *it << " ";
  }
  return ostr;
}
