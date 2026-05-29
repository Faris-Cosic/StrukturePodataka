#include "sudoku.hpp"
#include <iostream>
#include <string>
#include <vector>

int main () {
  sudoku game("ploca.txt");
  std::vector<sudoku> proslaStanja;
  std::vector<sudoku> buducaStanja;
  unsigned y, number;
  char x;
  while(!game.isWon()){
    game.displayBoard();
    std::cout << "\nZa unos broja unesi red, kolonu, broj\nZa undo unesi 'u'\nZa redo unesi 'r'\nUnos: ";
    std::cin >> x;
    if(x == 'u'){
      if(proslaStanja.empty()){
        std::cout << "\nNema proslog stanja!\n";
        continue;
      }
      buducaStanja.push_back(game);
      game = proslaStanja.back();
      proslaStanja.pop_back();
      continue;
    }
    else if (x == 'r'){
      if(buducaStanja.empty()){
        std::cout << "\nNemoguce izvršiti redo!\n";
        continue;
      }
      proslaStanja.push_back(game);
      game = buducaStanja.back();
      buducaStanja.pop_back();
      continue;
    }

    std::cin >> y >> number;
    proslaStanja.push_back(game);
    bool goodInput = game.insert((unsigned)x - '0', y, number);
    if(!goodInput)
      std::cout << "\nNevalidan unos!\n";
    else
      buducaStanja.clear();
  }
  std::cout << "Čestitamo, sudoku je riješen!";
  return 0;
}
