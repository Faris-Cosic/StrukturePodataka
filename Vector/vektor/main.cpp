#include "MojVektor.hpp"
#include <iostream>
#include <stdexcept>

template<typename T>
std::ostream& operator<<(std::ostream& ostr, const MojVektor<T>& vektor){
  for(auto i = 0; i < vektor.size(); ++i){
    ostr << vektor[i] << " ";
  }
  return ostr << std::endl;
}

int main (int argc, char *argv[]) {
  MojVektor<int> vektor;
  std::cout << "Default:\n";
  std::cout << vektor << "capacity: " << vektor.capacity() << " size: " << vektor.size() << std::endl;

  std::cout << "Initializer list:\n";
  MojVektor<int> vektor1{1,2,3,4,5,6,7,8,9,10};
  std::cout << vektor1;

  std::cout << "Copy:\n";
  MojVektor<int> vektor2(vektor1);
  std::cout << vektor2;
  vektor2 = vektor1;
  std::cout << vektor2;

  std::cout << "Move:\n";
  MojVektor<int> vektor3(MojVektor<int>{3,2,1});
  std::cout << vektor3;
  vektor3 = MojVektor<int>{3, 2};
  std::cout << vektor3;


  std::cout << "push_back():\n";
  int num = 5;
  vektor.push_back(1);
  vektor.push_back(2);
  vektor.push_back(num);
  std::cout << vektor;

  std::cout << "push_front():\n";
  vektor.push_front(0);
  vektor.push_front(num);
  std::cout << vektor;

  std::cout << "size: " << vektor.size() << std::endl;
  std::cout << "empty: " << vektor.empty() << std::endl;
  std::cout << "capacity: " << vektor.capacity() << std::endl;

  std::cout << "at():\n";
  try {
    auto element = vektor.at(50);
  } 
  catch(const std::out_of_range& err) {
    std::cout << err.what() << std::endl;
  }
  auto& element = vektor.at(1);
  std::cout << "at(1): " << element << std::endl;
  element = 11;
  std::cout << "promjenjen element: " << vektor;
  
  auto& element1 = vektor[2];
  std::cout << "vektor[2]: " << element1 << std::endl;
  element1 = 12;
  std::cout << "promjenjen element: " << vektor;

  std::cout << "clear():\n";
  vektor.clear();
  std::cout << vektor;
  vektor.push_back(1).push_back(2).push_back(3);

  std::cout << "Resize():\n";
  vektor.resize(10, 5);
  std::cout << vektor;
  vektor.resize(3, 1);
  std::cout << vektor;

  std::cout << "Pop_back():\n";
  vektor.pop_back();
  std::cout << vektor;
  std::cout << "Pop_front():\n";
  vektor.pop_front();
  std::cout << vektor;
  
  vektor.push_back(3).push_back(4).push_back(5);

  auto& front = vektor.front();
  auto& back = vektor.back();
  std::cout << "Vektor: " << vektor;
  std::cout << "Front(): " << front << std::endl;
  std::cout << "Back(): " << back << std::endl;
  front = -1;
  std::cout << "Promjenjen front: " << vektor;
  back = -1;
  std::cout << "Promjenjen back: " << vektor; 

  MojVektor<int> vek1{1, 2, 3};
  MojVektor<int> vek2{1, 2};

  std::cout << "\nJednakosti: ";
  std::cout << "Vektor1: " << vek1;
  std::cout << "Vektor2: " << vek2;
  std::cout << "Vektor1 == Vektor2: " << (vek1 == vek2);
  std::cout << "\nVektor1 != Vektor2: " << (vek1 != vek2);
  
  std::cout << "\nFull(): " << vek1.full();

  std::cout << "\n Iteratori:\n";
  std::cout << "Begin(): " << *vek1.begin() << std::endl;
  std::cout << "End(): " << *vek1.end() << std::endl;

  std::cout << "Find(2): " << *vek1.find(2) << std::endl;
  vek1.erase(vek1.begin() + 1);
  std::cout << "Erase(vec.begin() + 1): " << vek1;


  MojVektor<int> vek3{1,2,3,4,5,6, 7, 8, 9};
  std::cout << "\nVektor: " << vek3;
  auto uklonjeni = *vek3.erase(vek3.find(5), --vek3.end());
  std::cout << "\nVektor erase: " << vek3;
  std::cout << "\nZadnji poslije uklonjenog: " << uklonjeni << std::endl;


  MojVektor<int> vek4{1,2,3,4,5,6};
  std::cout << "Vektor: " << vek4;
  vek4.insert(vek4.find(4), 10);
  std::cout << "Insert (na mjesto 4 stavi 10) : " << vek4;
  
  vek4.rotate();
  std::cout << "Rotate(): " << vek4;

  vek4.for_each([](auto& a) {
      ++a;
  });
  
  std::cout << "for_each (svaki element povecan za 1): " << vek4;

  vek4.remove_if([](auto& a){
    return a % 2 == 0;
  });
  std::cout << "remove_if (izbrisi sve parne brojeve): " << vek4;

  return 0;
}
